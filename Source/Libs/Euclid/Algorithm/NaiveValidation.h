#pragma once

#include <QListIterator>
#include "Validation.h"

namespace Euclid
{

    template <class Kernel>
    class NaiveValidation : public Validation<Kernel>
    {
    public:
        typedef Vertex<Kernel>   VertexT;
        typedef Triangle<Kernel> TriangleT;
        typedef TriMesh<Kernel>  TriMesh;

        NaiveValidation(TriMesh* trimesh)
            : Validation<Kernel>(trimesh)
        {
        }

        bool validate()
        {
            TriMesh* trimesh = this->trimesh();

            QListIterator<TriangleT*> i(trimesh->triangles());
            while (i.hasNext()) {
                if (! validateTriangle(i.next())) {
                    return false;
                }
            }

            return true;
        }

    private:
        bool validateTriangle(TriangleT* triangle)
        {
            for (int i=0; i<3; i++) {
                TriangleT* neighbor = triangle->neighbor(i);
                if (0 != neighbor) {
                    if (! shareVertices(triangle, i, neighbor)) {
                        return false;
                    }
                }
            }

            return true;
        }

        bool shareVertices(TriangleT* triangle, int index, TriangleT* neighbor)
        {
            for (int i=0; i<2; i++) {
                const VertexT* common = triangle->vertex((index + i + 1)%3);
                bool has = false;
                for (int i=0; i<3; i++) {
                    const VertexT* v = neighbor->vertex(i);
                    if (v == common) {
                        has = true;
                    }
                }
                if (! has) {
                    return false;
                }
            }

            return true;
        }
    };
}

