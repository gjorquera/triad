#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "TriMesh.h"
#include "TriMeshFactory.h"
#include "../Geometry/Triangle.h"
#include "../Geometry/Vertex.h"
#include "../Type/Point.h"

namespace Euclid
{

    /*!
     * TriMesh loader from the M2D file format.
     */
    template <class Kernel>
    class M2dFactory : public TriMeshFactory<Kernel>
    {
    public:
        M2dFactory(const std::string &filename)
            : TriMeshFactory<Kernel>(filename)
        {
        }

        ~M2dFactory()
        {
        }

    protected:
        TriMesh<Kernel>* factoryMethod(const std::string &filename)
        {
            QMap<int,Triangle<Kernel>*> triangles;
            QMap<int,Vertex<Kernel>*> vertices;

            TriMesh<Kernel> *trimesh = new TriMesh<Kernel>;

            std::ifstream fin(filename.c_str());

            std::string line;
            while (std::getline(fin, line))
            {
                // Preparing the line.
                this->trimComments(line, "#");
                this->trimSpaces(line);
                if (line.size() == 0) continue;

                // Now let's process the line as a stream.
                std::stringstream sin(line);

                char type;
                int id;

                // Obtaining line type and id.
                sin >> type >> id;

                // Creating the specified type.
                if (type == 'v' || type == 'V') // Vertex.
                {
                    Point<3,float> p;
                    sin >> p[0] >> p[1] >> p[2];
                    Vertex<Kernel> *v = new Vertex<Kernel>(p);
                    trimesh->addVertex(v);
                    vertices[id] = v;
                }
                else if (type == 't' || type == 'T') // Triangle.
                {
                    int v1, v2, v3;
                    sin >> v1 >> v2 >> v3;
                    Triangle<Kernel> *t = new Triangle<Kernel>(
                        vertices[v1],
                        vertices[v2],
                        vertices[v3]);
                    trimesh->addTriangle(t);
                }
                else if (type == 'n' || type == 'N') // Neighbor.
                {
                    int n1, n2, n3;
                    sin >> n1 >> n2 >> n3;
                    if (0 != n1)
                        triangles[id]->addNeighbor(triangles[n1]);
                    if (0 != n2)
                        triangles[id]->addNeighbor(triangles[n2]);
                    if (0 != n3)
                        triangles[id]->addNeighbor(triangles[n3]);
                }
                else
                {
                    std::cout << "Warning, line not recognized:" << std::endl;
                    std::cout << "\t '" << line << "'" << std::endl;
                }
            }

            return trimesh;
        }
    };
}

