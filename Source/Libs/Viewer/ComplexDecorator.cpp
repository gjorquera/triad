#include "ComplexDecorator.h"

namespace Viewer
{

    ComplexDecorator::ComplexDecorator()
        : FigureDecorator()
    {
    }

    /*virtual*/
    ComplexDecorator::~ComplexDecorator()
    {
        QList<FigureDecorator*>::ConstIterator i;
        for (i = _decorations.begin(); i != _decorations.end(); i++)
        {
            delete *i;
        }
    }

    void
    ComplexDecorator::add(FigureDecorator* decoration)
    {
        _decorations.append(decoration);
    }

    void
    ComplexDecorator::paintGL() const
    {
        QList<FigureDecorator*>::ConstIterator i;
        for (i = _decorations.begin(); i != _decorations.end(); i++)
        {
            (*i)->render();
        }
    }

}

