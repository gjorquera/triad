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

typedef Euclid::DefaultKernel                        Kernel;
typedef Euclid::CircularParallelLeppStrategy<Kernel> CircularParallelLeppStrategy;
typedef Euclid::LeppStrategy<Kernel>                 LeppStrategy;
typedef Euclid::NaiveValidation<Kernel>              NaiveValidation;
typedef Euclid::M2dFormatIO<Kernel>                  M2dFormatIO;
typedef Euclid::PercentageCriterion<Kernel>          PercentageCriterion;
typedef Euclid::SelectedCriterion<Kernel>            SelectedCriterion;
typedef Euclid::Strategy<Kernel>                     Strategy;
typedef Euclid::TriMesh<Kernel>                      TriMesh;

void benchmarkPercentage(QString& filename, Strategy* strat, int p, bool b)
{
    int vertices, triangles, memory;
    int times = 1;
    bool valid = true;
    float elapsed = 0;
    for (int i=0; i<times; i++) {
        TriMesh* trimesh = new TriMesh;
        M2dFormatIO io(filename, trimesh);
        io.load();
        vertices = trimesh->numVertices();
        triangles = trimesh->numTriangles();
        memory = trimesh->memory();
        strat->setTriMesh(trimesh);
        PercentageCriterion pc(trimesh->triangles(), p, b);
        trimesh->select(pc);
        SelectedCriterion sc;
        QTime t;
        t.start();
        strat->refine(sc);
        elapsed += t.elapsed();
        NaiveValidation v(trimesh);
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
        << "Valid:" << valid;
}

void benchmarks(QString& filename, Strategy* strat)
{
    benchmarkPercentage(filename, strat, 2, false);
    benchmarkPercentage(filename, strat, 5, false);
    benchmarkPercentage(filename, strat, 10, false);
    benchmarkPercentage(filename, strat, 25, false);
    benchmarkPercentage(filename, strat, 2, true);
    benchmarkPercentage(filename, strat, 5, true);
    benchmarkPercentage(filename, strat, 10, true);
    benchmarkPercentage(filename, strat, 25, true);
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    if (argc < 2) {
        qDebug() << "Usage: ./Benchmarks filename";
        return 0;
    }

    QString filename(argv[1]);

    qDebug() << "SECUENTIAL";
    Strategy* strat = new LeppStrategy;
    benchmarks(filename, strat);
    delete strat;

    qDebug() << "CIRCULAR PARALLEL";
    strat = new CircularParallelLeppStrategy;
    benchmarks(filename, strat);
    delete strat;

    return 0;
}

