#pragma once

#include <QThreadPool>
#include "Strategy.h"
#include "../Parallel/RefineThread.h"

namespace Euclid
{

    /*!
     * Parallel version of the Lepp-Bisection algorithm implemented with
     * QThreads.
     */
    template <class Kernel>
    class QThreadLeppStrategy : public Strategy<Kernel>
    {
    public:
        typedef Triangle<Kernel>  TriangleT;
        typedef Criterion<Kernel> Criterion;
        typedef TriMesh<Kernel>   TriMesh;

        QThreadLeppStrategy(TriMesh* trimesh = 0)
            : Strategy<Kernel>(trimesh)
        {
        }

        ~QThreadLeppStrategy()
        {
        }

        void refine(const Criterion& criterion)
        {
            TriMesh* trimesh = this->trimesh();
            QListIterator<TriangleT*> i(trimesh->triangles());

            QList<TriangleT*> toRefine;
            /// @todo maybe a do-while that refines until no criteria is met.
            while (i.hasNext()) {
                TriangleT* t = i.next();
                if (criterion.test(t)) {
                    t->setSelected(true);
                    toRefine.append(t);
                }
            }

            int threads = QThreadPool::globalInstance()->maxThreadCount();
            for (int i=0; i<threads; i++) {
                QRunnable* thread = new RefineThread<Kernel>(toRefine);
                QThreadPool::globalInstance()->start(thread);
            }

            QThreadPool::globalInstance()->waitForDone();
        }
    };
}

