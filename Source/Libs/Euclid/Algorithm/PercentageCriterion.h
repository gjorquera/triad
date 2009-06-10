#pragma once

#include <QtAlgorithms>
#include <QList>
#include "Criterion.h"
#include "LeppStrategy.h"
#include "../Geometry/Triangle.h"

template <class Kernel>
bool cmp(const Euclid::Triangle<Kernel>* t1, const Euclid::Triangle<Kernel>* t2)
{
    typedef typename Kernel::Vector Vector;
    Euclid::LeppStrategy<Kernel> lepp;
    const Vector* v1;
    const Vector* v2;
    v1 = lepp.longestEdge(const_cast<Euclid::Triangle<Kernel>*>(t1));
    v2 = lepp.longestEdge(const_cast<Euclid::Triangle<Kernel>*>(t2));
    bool result = v1->distance() < v2->distance();
    delete v1;
    delete v2;
    return result;
}

namespace Euclid
{

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
            _triangles = triangles;
            qSort(_triangles.begin(), _triangles.end(), cmp<Kernel>);
        }

        bool test(Triangle* triangle) const
        {
            int index = _triangles.indexOf(triangle);
            if (_biggest) {
                return index > _triangles.size() * (100 - _percentage) / 100;
            } else {
                return index < _triangles.size() * _percentage / 100;
            }
        }

    private:
        int _percentage;
        bool _biggest;
        QList<Triangle*> _triangles;
    };
}

