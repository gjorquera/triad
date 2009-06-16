#pragma once

#include <QList>
#include <QListIterator>
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
            // iterate through _toRefine refining until no isSelected triangle
            // is left.
            QListIterator<TriangleT*> i(_toRefine);
            while (i.hasNext()) {
                i.next()->setSelected(false);
            }
        }

    private:
        QList<TriangleT*> _toRefine;
    };
}

