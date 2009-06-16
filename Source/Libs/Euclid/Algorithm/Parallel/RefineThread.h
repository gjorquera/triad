#pragma once

#include <iostream>
#include <QList>
#include <QMutableListIterator>
#include <QRunnable>
#include "../../Geometry/TriMesh.h"

namespace Euclid
{

    template <class Kernel>
    class RefineThread : public QRunnable
    {
    public:
        typedef typename Kernel::T      T;
        typedef typename Kernel::Point  Point;
        typedef typename Kernel::Vector Vector;
        typedef Vertex<Kernel>          VertexT;
        typedef Edge<Kernel>            EdgeT;
        typedef Triangle<Kernel>        TriangleT;
        typedef TriMesh<Kernel>         TriMesh;
        typedef LeppLibrary<Kernel>     LeppLibrary;

        RefineThread(TriMesh* trimesh, QList<TriangleT*> toRefine)
        {
            _trimesh = trimesh;
            _toRefine = toRefine;
        }

        virtual ~RefineThread()
        {
        }

        void run()
        {
                std::cout << ".";
            QMutableListIterator<TriangleT*> i(_toRefine);
            //do {
                while (i.hasNext()) {
                    TriangleT* triangle = i.next();
                    bool taken = triangle->mutex().tryLock();
                    if (! taken) continue;

                    if (0 != refineTriangle(triangle)) {
                        //triangle->setSelected(false);
                        i.remove();
                    }

                    triangle->mutex().unlock();
                }
                //i.toFront();
            //} while (_toRefine.size() > 0);
        }

    protected:
        TriangleT* refineTriangle(TriangleT* triangle)
        {
            std::cout << ".";
            TriangleT* neighbor = LeppLibrary::longestEdgeNeighbor(triangle);
            if (0 != neighbor) {
                bool taken = neighbor->mutex().tryLock();
                if (! taken) return 0;
            }

            TriangleT* refined = 0;

            do {
                if (LeppLibrary::isTerminal(triangle)) {
                    //refineTerminal(triangle);
                    refined = triangle;
                } else {
                    refined = refineTriangle(neighbor);
                }
            } while (refined != 0 && refined != triangle);

            if (0 != neighbor) {
                neighbor->mutex().unlock();
            }

            return refined;
        }

    private:
        QList<TriangleT*> _toRefine;
        TriMesh* _trimesh;
    };
}

