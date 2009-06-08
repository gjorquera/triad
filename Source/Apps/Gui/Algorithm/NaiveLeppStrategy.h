#pragma once

#include <Euclid/Algorithm/NaiveLeppStrategy.h>
#include "../Kernel.h"

namespace App
{

    class NaiveLeppStrategy : public Euclid::NaiveLeppStrategy<Kernel>
    {
    public:
        NaiveLeppStrategy(Euclid::TriMesh<Kernel>* trimesh);
        ~NaiveLeppStrategy();
    };
}

