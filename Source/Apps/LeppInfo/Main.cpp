#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <Euclid/Algorithm/Lepp/Library.h>
#include <Euclid/Geometry/M2dFormatIO.h>
#include <Euclid/Geometry/Triangle.h>
#include <Euclid/Geometry/TriMesh.h>
#include <Euclid/Type/DefaultKernel.h>

typedef Euclid::DefaultKernel       Kernel;
typedef Euclid::LeppLibrary<Kernel> LeppLibrary;
typedef Euclid::M2dFormatIO<Kernel> M2dFormatIO;
typedef Euclid::Triangle<Kernel>    TriangleT;
typedef Euclid::TriMesh<Kernel>     TriMesh;

QMap<int,int> calculateLepps(TriMesh* trimesh)
{
    QMap<int,int> lepps;

    QListIterator<TriangleT*> i(trimesh->triangles());
    while (i.hasNext()) {
        TriangleT* triangle = i.next();
        int lepp = 0;
        do {
            lepp++;
            if (LeppLibrary::isTerminal(triangle)) {
                if (0 != LeppLibrary::longestEdgeNeighbor(triangle)) {
                    lepp++;
                }
                triangle = 0;
            } else {
                triangle = LeppLibrary::longestEdgeNeighbor(triangle);
            }
        } while (0 != triangle);
        lepps[lepp]++;
    }

    return lepps;
}

void leppInfo(QString filename)
{
    qDebug() << "Filename";
    qDebug() << "========";
    qDebug() << filename;

    qDebug() << "";

    TriMesh* trimesh = new TriMesh;
    M2dFormatIO io(filename, trimesh);
    io.load();

    qDebug() << "";

    qDebug() << "Basic Information";
    qDebug() << "=================";

    qDebug() << "Vertices & Triangles & Memory \\";
    qDebug() << trimesh->numVertices() << "&"
        << trimesh->numTriangles() << "&"
        << trimesh->memory() << "\\";

    qDebug() << "";

    qDebug() << "Lepp Information";
    qDebug() << "================";

    qDebug() << "Lepp & Triangles & Percentage \\";
    QMap<int,int> lepps = calculateLepps(trimesh);
    QMapIterator<int,int> i(lepps);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << "&"
            << i.value() << "&"
            << i.value()*100.0/trimesh->numTriangles() << "\\";
    }

    qDebug() << "";
    qDebug() << "--";

    delete trimesh;
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    if (argc < 2) {
        qDebug() << "Usage: ./LeppInfo <filename|directory>";
        return 0;
    }

    QString param(argv[1]);

    QFileInfo info(param);
    if (! info.exists()) {
        qDebug() << "Param does not exist.";
    } else if (info.isDir()) {
        QDir path = info.absolutePath();
        QFileInfoList infoList = path.entryInfoList();
        foreach (QFileInfo info, infoList) {
            if (info.isFile()) {
                leppInfo(info.absoluteFilePath());
            }
        }
    } else if (info.isFile()) {
        leppInfo(info.absoluteFilePath());
    } else {
        qDebug() << "Unkown param type.";
    }

    return 0;
}

