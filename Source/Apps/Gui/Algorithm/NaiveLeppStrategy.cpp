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
        Euclid::TriMesh<Kernel>::Iterator i;
        for (i = trimesh->begin(); i != trimesh->end(); i++)
        {
            if ((*i)->info().selected) {
                Euclid::Triangle<Kernel>* t = *i;
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

