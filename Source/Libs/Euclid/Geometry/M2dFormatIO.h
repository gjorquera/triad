#pragma once

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "TriMesh.h"
#include "TriMeshIO.h"
#include "../Geometry/Triangle.h"
#include "../Geometry/Vertex.h"
#include "../Type/Point.h"

namespace Euclid
{

    /*!
     * TriMesh loader and saver for the M2D file format.
     */
    template <class Kernel>
    class M2dFormatIO : public TriMeshIO<Kernel>
    {
    public:
        typedef TriMesh<Kernel>   TriMeshT;

        M2dFormatIO(QString& filename, TriMeshT* trimesh)
            : TriMeshIO<Kernel>(filename, trimesh)
        {
        }

        ~M2dFormatIO()
        {
        }

        void load()
        {
            QMap<int,Triangle<Kernel>*> triangles;
            QMap<int,Vertex<Kernel>*> vertices;

            TriMeshT *trimesh = this->trimesh();

            QString filename  = this->filename();
            QFile file(filename);

            if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

            while (! file.atEnd())
            {
                QString line = file.readLine();

                // Preparing the line.
                TriMeshIO<Kernel>::trimComments(line, "#");
                TriMeshIO<Kernel>::trimSpaces(line);
                if (line.length() == 0) continue;

                // Now let's process the line as a stream.
                QTextStream tin(&line);

                char type;
                int id;

                // Obtaining line type and id.
                tin >> type >> id;

                // Creating the specified type.
                if (type == 'v' || type == 'V') // Vertex.
                {
                    Point<3,float> p;
                    tin >> p[0] >> p[1] >> p[2];
                    Vertex<Kernel> *v = new Vertex<Kernel>(p);
                    trimesh->addVertex(v);
                    vertices[id] = v;
                }
                else if (type == 't' || type == 'T') // Triangle.
                {
                    int v1, v2, v3;
                    tin >> v1 >> v2 >> v3;
                    Triangle<Kernel> *t = new Triangle<Kernel>(
                        vertices[v1],
                        vertices[v2],
                        vertices[v3]);
                    trimesh->addTriangle(t);
                    triangles[id] = t;
                }
                else if (type == 'n' || type == 'N') // Neighbor.
                {
                    int n1, n2, n3;
                    tin >> n1 >> n2 >> n3;
                    if (0 != n1) {
                        triangles[id]->addNeighbor(triangles[n1]);
                    }
                    if (0 != n2) {
                        triangles[id]->addNeighbor(triangles[n2]);
                    }
                    if (0 != n3) {
                        triangles[id]->addNeighbor(triangles[n3]);
                    }
                }
                else
                {
                    qDebug() << "Warning, line not recognized:";
                    qDebug() << "\t '" + line + "'";
                }
            }
        }

        void save()
        {
            /// @todo implement save
        }
    };
}

