#pragma once

#include <QtAlgorithms>
#include <QList>
#include "Criterion.h"
#include "Lepp/Library.h"
#include "../Geometry/Edge.h"
#include "../Geometry/Triangle.h"

template <class Kernel>
bool cmp(const Euclid::Triangle<Kernel>* t1, const Euclid::Triangle<Kernel>* t2)
{
    typedef Euclid::Edge<Kernel>        EdgeT;
    typedef Euclid::LeppLibrary<Kernel> LeppLibrary;

    const EdgeT* v1 = LeppLibrary::longestEdge(t1);
    const EdgeT* v2 = LeppLibrary::longestEdge(t2);
    return v1->vector().distance() < v2->vector().distance();
}

namespace Euclid
{

    /*!
     * Percentage criterion.
     *
     * This class will order all the triangles based on it's longest edge. Then
     * the \b test method returns true depending on the size of it's longest
     * edge compared to the size of the other triangle's longest edge.
     */
    template <class Kernel>
    class PercentageCriterion : public Criterion<Kernel>
    {
    public:
        typedef typename Kernel::T      T;
        typedef typename Kernel::Vector Vector;
        typedef Triangle<Kernel>        Triangle;

        PercentageCriterion(QList<Triangle*> triangles, int percentage,
            bool biggest = true)
            : Criterion<Kernel>()
        {
            _percentage = percentage;
            _biggest = biggest;
            _numTriangles = triangles.size();
            QList<Triangle*> aux = triangles;
            qSort(aux.begin(), aux.end(), cmp<Kernel>);
            QListIterator<Triangle*> i(aux);
            int index = 0;
            while (i.hasNext())
            {
                _positions[i.next()] = ++index;
            }
        }

        bool test(Triangle* triangle) const
        {
            int index = _positions[triangle];
            if (_biggest) {
                return index > _numTriangles * (100 - _percentage) / 100;
            } else {
                return index < _numTriangles * _percentage / 100;
            }
        }

    private:
        int _percentage;
        int _numTriangles;
        bool _biggest;
        QMap<Triangle*,int> _positions;
    };
}

