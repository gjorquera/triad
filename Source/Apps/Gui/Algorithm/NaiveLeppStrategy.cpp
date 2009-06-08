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
}

