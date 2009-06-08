#include <QMutableListIterator>
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
        QMutableListIterator<FigureDecorator*> i(_decorations);
        while (i.hasNext())
        {
            delete i.next();
            i.remove();
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
        QListIterator<FigureDecorator*> i(_decorations);
        while (i.hasNext())
        {
            i.next()->paintGL();
        }
    }

}

