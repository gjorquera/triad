#include "NaiveLeppStrategy.h"

namespace App
{

    NaiveLeppStrategy::NaiveLeppStrategy(Euclid::TriMesh<Kernel>* trimesh)
        : Euclid::NaiveLeppStrategy<Kernel>(trimesh)
    {
    }

    NaiveLeppStrategy::~NaiveLeppStrategy()
    {
    }

    void
    NaiveLeppStrategy::highlightLepp()
    {
        Euclid::TriMesh<Kernel>* trimesh = Euclid::Strategy<Kernel>::trimesh();
        QMutableListIterator<Euclid::Triangle<Kernel>*> i(trimesh->triangles());
        while (i.hasNext())
        {
            if (i.next()->info().selected) {
                Euclid::Triangle<Kernel>* t = i.next();
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
        }
    }
}

