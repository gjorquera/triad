#pragma once

#include <fstream>
#include <sstream>
#include "TriMesh.h"
#include "TriMeshFactory.h"

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
            : TriMeshFactory(filename)
        {
        }

        ~M2dFactory()
        {
        }

    protected:
        TriMesh<Kernel>* factoryMethod(const std::string &filename)
        {
            TriMesh<Kernel> *trimesh = new TriMesh<Kernel>;

            std::ifstream fin(filename.c_str());

            std::string line;
            while (std::getline(fin, line))
            {
                // Preparing the line.
                trimComments(line, "#");
                trimSpaces(line);
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
                    sin >> p;
                    Vertex<Kernel> *v = new Vertex<Kernel>(id, p);
                    trimesh->addVertex(id, v);
                }
                else if (type == 't' || type == 'T') // Triangle.
                {
                    int v1, v2, v3;
                    sin >> v1 >> v2 >> v3;
                    Triangle<Kernel> *t = new Triangle<Kernel>(
                        id,
                        trimesh->vertex(v1),
                        trimesh->vertex(v2),
                        trimesh->vertex(v3));
                    trimesh->addTriangle(id, t);
                }
                else if (type == 'n' || type == 'N') // Neighbor.
                {
                    int n1, n2, n3;
                    sin >> n1 >> n2 >> n3;
                    if (0 != n1)
                        trimesh->triangle(id)->addNeighbor(trimesh->triangle(n1));
                    if (0 != n2)
                        trimesh->triangle(id)->addNeighbor(trimesh->triangle(n2));
                    if (0 != n3)
                        trimesh->triangle(id)->addNeighbor(trimesh->triangle(n3));
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

