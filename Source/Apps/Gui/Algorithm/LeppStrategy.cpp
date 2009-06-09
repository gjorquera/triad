#include "LeppStrategy.h"

namespace App
{

    LeppStrategy::LeppStrategy(Euclid::TriMesh<Kernel>* trimesh)
        : Euclid::LeppStrategy<Kernel>(trimesh)
    {
    }

    LeppStrategy::~LeppStrategy()
    {
    }

    void
    LeppStrategy::highlightLepp()
    {
        Euclid::TriMesh<Kernel>* trimesh = Euclid::Strategy<Kernel>::trimesh();
        QMutableListIterator<Euclid::Triangle<Kernel>*> i(trimesh->triangles());
        while (i.hasNext())
        {
            if (i.peekNext()->info().selected) {
                Euclid::Triangle<Kernel>* t = i.peekNext();
                do
                {
                    t->info().lepp = true;
                    if (isTerminal(t)) {
                        Euclid::Triangle<Kernel>* n = longestEdgeNeighbor(t);
                        if (0 != n) {
                            n->info().lepp = true;
                        }
                        t = 0;
                    } else {
                        t = longestEdgeNeighbor(t);
                    }
                } while (0 != t);
            }
            i.next();
        }
    }
}

