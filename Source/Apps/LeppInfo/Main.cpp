#include <QCoreApplication>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    if (argc < 2) {
        qDebug() << "Usage: ./LeppInfo <filename|directory>";
        return 0;
    }

    return 0;
}

