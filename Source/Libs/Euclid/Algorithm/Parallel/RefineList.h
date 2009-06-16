#pragma once

#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include "../../Geometry/Triangle.h"

namespace Euclid
{

    template <class Kernel>
    class RefineList
    {
    public:
        typedef Triangle<Kernel> TriangleT;

        RefineList()
        {
        }

        void addTriangle(TriangleT* triangle)
        {
            QMutexLocker locker(&_mutex);
            _toRefine.append(triangle);
        }

        void removeTriangle(TriangleT* triangle)
        {
            QMutexLocker locker(&_mutex);
            _toRefine.removeOne(triangle);
        }

    private:
        QList<TriangleT*> _toRefine;
        QMutex _mutex;
    };
}

