#include <values.h>
#include <QDebug>
#include <QCoreApplication>
#include <QListIterator>
#include <QTime>
#include <Euclid/Algorithm/Lepp/Library.h>
#include <Euclid/Algorithm/LeppStrategy.h>
#include <Euclid/Algorithm/PercentageCriterion.h>
#include <Euclid/Algorithm/CircularParallelLeppStrategy.h>
#include <Euclid/Algorithm/SelectedCriterion.h>
#include <Euclid/Algorithm/NaiveValidation.h>
#include <Euclid/Geometry/M2dFormatIO.h>
#include <Euclid/Type/DefaultKernel.h>

template <class Kernel>
void leppInfo(Euclid::TriMesh<Kernel>* trimesh, int& min, int& max, int& avg)
{
    typedef Euclid::LeppLibrary<Kernel> LeppLibrary;
    min = MAXINT;
    max = 0;
    avg = 0;
    QListIterator<Euclid::Triangle<Kernel>*> i(trimesh->triangles());
    while (i.hasNext()) {
        Euclid::Triangle<Kernel>* t = i.next();
        int lepp = 0;
        do {
            lepp++;
            if (LeppLibrary::isTerminal(t)) {
                if (0 != LeppLibrary::longestEdgeNeighbor(t)) {
                    lepp++;
                }
                t = 0;
            } else {
                t = LeppLibrary::longestEdgeNeighbor(t);
            }
        } while (0 != t);
        avg += lepp;
        if (lepp < min) min = lepp;
        if (lepp > max) max = lepp;
    }
    avg /= trimesh->numTriangles();
}

template <class Kernel>
void benchmarkPercentage(QString& filename, Euclid::Strategy<Kernel>* strat,
    int p, bool b)
{
    int vertices, triangles, memory;
    int minLepp, maxLepp, avgLepp;
    int times = 1;
    bool valid = true;
    float elapsed = 0;
    for (int i=0; i<times; i++) {
        Euclid::TriMesh<Kernel>* trimesh = new Euclid::TriMesh<Kernel>;
        Euclid::M2dFormatIO<Kernel> io(filename, trimesh);
        io.load();
        leppInfo<Kernel>(trimesh, minLepp, maxLepp, avgLepp);
        vertices = trimesh->numVertices();
        triangles = trimesh->numTriangles();
        memory = trimesh->memory();
        strat->setTriMesh(trimesh);
        Euclid::PercentageCriterion<Kernel> pc(trimesh->triangles(), p, b);
        trimesh->select(pc);
        Euclid::SelectedCriterion<Kernel> sc;
        QTime t;
        t.start();
        strat->refine(sc);
        elapsed += t.elapsed();
        Euclid::NaiveValidation<Kernel> v(trimesh);
        if (! v.validate()) {
            valid = false;
        }
        delete trimesh;
    }
    elapsed /= 1.0*times;
    qDebug() << "Vertices:" << vertices << "\t"
        << "Triangles:" << triangles << "\t"
        << "Memory:" << memory << "\t"
        << "Refined:" << (b ? "Biggest" : "Smallest") << p << "\t"
        << "=" << triangles * p / 100 << "\t"
        << "Elapsed:" << elapsed << "\t"
        << "Valid:" << valid << "\t"
        << "Lepp Min:" << minLepp
        << "Max:" << maxLepp
        << "Avg:" << avgLepp;
}

template <class Kernel>
void benchmarks(QString& filename, Euclid::Strategy<Kernel>* strat)
{
    benchmarkPercentage<Kernel>(filename, strat, 2, false);
    benchmarkPercentage<Kernel>(filename, strat, 5, false);
    benchmarkPercentage<Kernel>(filename, strat, 10, false);
    benchmarkPercentage<Kernel>(filename, strat, 25, false);
    benchmarkPercentage<Kernel>(filename, strat, 2, true);
    benchmarkPercentage<Kernel>(filename, strat, 5, true);
    benchmarkPercentage<Kernel>(filename, strat, 10, true);
    benchmarkPercentage<Kernel>(filename, strat, 25, true);
}

int main(int argc, char** argv)
{
    typedef Euclid::DefaultKernel Kernel;

    QCoreApplication app(argc, argv);

    if (argc < 2) {
        qDebug() << "Usage: ./TriadCli filename";
        return 0;
    }

    QString filename(argv[1]);

    qDebug() << "SECUENTIAL";
    Euclid::Strategy<Kernel>* strat = new Euclid::LeppStrategy<Kernel>;
    benchmarks<Kernel>(filename, strat);
    delete strat;

    qDebug() << "CIRCULAR PARALLEL";
    strat = new Euclid::CircularParallelLeppStrategy<Kernel>;
    benchmarks<Kernel>(filename, strat);
    delete strat;

    return 0;
}

