#pragma once

#include <QThreadPool>
#include "Strategy.h"
#include "Parallel/CircularRefineThread.h"

namespace Euclid
{

    template <class Kernel>
    class CircularParallelLeppStrategy : public Strategy<Kernel>
    {
    public:
        typedef Triangle<Kernel>  TriangleT;
        typedef Criterion<Kernel> Criterion;
        typedef TriMesh<Kernel>   TriMesh;

        CircularParallelLeppStrategy(TriMesh* trimesh = 0)
            : Strategy<Kernel>(trimesh)
        {
        }

        ~CircularParallelLeppStrategy()
        {
        }

        void refine(const Criterion& criterion)
        {
            int threads = QThreadPool::globalInstance()->maxThreadCount();
            for (int i=0; i<threads; i++) {
                QRunnable* thread = new CircularRefineThread<Kernel>(
                    this->trimesh(), &criterion);
                QThreadPool::globalInstance()->start(thread);
            }
            QThreadPool::globalInstance()->waitForDone();
        }
    };
}

