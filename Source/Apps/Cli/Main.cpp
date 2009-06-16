#include <QDebug>
#include <QCoreApplication>
#include <QTime>
#include <Euclid/Algorithm/LeppStrategy.h>
#include <Euclid/Algorithm/PercentageCriterion.h>
#include <Euclid/Algorithm/QThreadLeppStrategy.h>
#include <Euclid/Algorithm/SelectedCriterion.h>
#include <Euclid/Geometry/M2dFormatIO.h>
#include <Euclid/Type/DefaultKernel.h>

template <class Kernel>
void benchmarkPercentage(QString& filename, Euclid::Strategy<Kernel>* strat,
    int p, bool b)
{
    Euclid::TriMesh<Kernel>* trimesh = new Euclid::TriMesh<Kernel>;
    Euclid::M2dFormatIO<Kernel> io(filename, trimesh);
    io.load();
    int vertices = trimesh->numVertices();
    int triangles = trimesh->numTriangles();
    int memory = trimesh->memory();
    strat->setTriMesh(trimesh);
    Euclid::PercentageCriterion<Kernel> pc(trimesh->triangles(), p, b);
    trimesh->select(pc);
    Euclid::SelectedCriterion<Kernel> sc;
    QTime t;
    t.start();
    strat->refine(sc);
    int elapsed = t.elapsed();
    qDebug() << "Vertices:" << vertices << "\t"
        << "Triangles:" << triangles << "\t"
        << "Memory:" << memory << "\t"
        << "Refined:" << (b ? "Biggest" : "Smallest") << p << "\t"
        << "=" << triangles * p / 100 << "\t"
        << "Elapsed:" << elapsed;
    delete trimesh;
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

    qDebug() << "PARALLEL";
    strat = new Euclid::QThreadLeppStrategy<Kernel>;
    benchmarks<Kernel>(filename, strat);
    delete strat;

    return 0;
}

