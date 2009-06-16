#pragma once

#include <QList>
#include <QMutableListIterator>
#include <QRunnable>
#include "../Geometry/TriMesh.h"

namespace Euclid
{

    template <class Kernel>
    class RefineThread : public QRunnable
    {
    public:
        typedef Triangle<Kernel> TriangleT;

        RefineThread(QList<TriangleT*>& toRefine)
        {
            _toRefine = toRefine;
        }

        virtual ~RefineThread()
        {
        }

        void run()
        {
            QMutableListIterator<TriangleT*> i(_toRefine);
            do {
                while (i.hasNext()) {
                    TriangleT* t = i.next();
                    bool taken = t->mutex().tryLock();
                    if (! taken) continue;

                    if (refine(t)) {
                        t->setSelected(false);
                        i.remove();
                    }

                    t->mutex().unlock();
                }
            } while (_toRefine.size() > 0);
        }

    protected:
        bool refine(TriangleT* )
        {
            return true;
        }

    private:
        QList<TriangleT*> _toRefine;
    };
}

