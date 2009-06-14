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
        typedef Vertex<Kernel>   VertexT;
        typedef Triangle<Kernel> TriangleT;
        typedef TriMesh<Kernel>  TriMeshT;

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
            QMap<int,VertexT*> vertices;
            QMap<int,TriangleT*> triangles;

            TriMeshT* trimesh = this->trimesh();

            QString filename = this->filename();
            QFile file(filename);
            file.remove();

            if (! file.open(QIODevice::WriteOnly | QIODevice::Append)) return;

            QTextStream tout(&file);

            int index = 0;
            QListIterator<VertexT*> i(trimesh->vertices());
            while (i.hasNext()) {
                vertices[++index] = i.next();
            }

            index = 0;
            QListIterator<TriangleT*> j(trimesh->triangles());
            while (j.hasNext()) {
                triangles[++index] = j.next();
            }

            tout << "# Mesh saved by Triad" << endl;

            QMapIterator<int,VertexT*> k(vertices);
            while (k.hasNext()) {
                k.next();
                tout << "v " << k.key();
                for (int i=0; i<3; i++) {
                    tout << " " << k.value()->point()[i];
                }
                tout << endl;
            }

            QMapIterator<int,TriangleT*> l(triangles);
            while (l.hasNext()) {
                l.next();
                tout << "t " << l.key();
                for (int i=0; i<3; i++) {
                    VertexT* v = const_cast<VertexT*>(l.value()->vertex(i));
                    tout << " " << vertices.key(v);
                }
                tout << endl;
            }

            l.toFront();
            while (l.hasNext()) {
                l.next();
                tout << "n " << l.key();
                for (int i=0; i<3; i++) {
                    tout << " " << triangles.key(l.value()->neighbor(i));
                }
                tout << endl;
            }
        }
    };
}

