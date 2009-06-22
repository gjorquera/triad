#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <Euclid/Geometry/M2dFormatIO.h>
#include <Euclid/Geometry/TriMesh.h>
#include <Euclid/Type/DefaultKernel.h>

typedef Euclid::DefaultKernel       Kernel;
typedef Euclid::M2dFormatIO<Kernel> M2dFormatIO;
typedef Euclid::TriMesh<Kernel>     TriMesh;

void leppInfo(QString filename)
{
    qDebug() << "LeppInfo on" << filename;

    TriMesh* trimesh = new TriMesh;
    M2dFormatIO io(filename, trimesh);

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

