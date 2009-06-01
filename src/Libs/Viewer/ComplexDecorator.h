#pragma once

#include <QList>
#include "FigureDecorator.h"

namespace Viewer
{

    /*!
     * The ComplexDecorator class implements a decorator container.
     *
     * The IFigure, FigureDecorator and ComplexDecorator classes implements the
     * Composite Pattern.
     *
     * This pattern is implemented to be able to assign more than one decorator
     * to a figure.
     *
     * The destructor also destructs the added decorations.
     *
     * See IFigure for more information on decorators.
     */
    class ComplexDecorator : public FigureDecorator
    {
    public:
        ComplexDecorator()
            : FigureDecorator()
        {
        }

        ~ComplexDecorator()
        {
            QList<FigureDecorator*>::ConstIterator i;
            for (i = _decorations.begin(); i != _decorations.end(); i++)
            {
                delete *i;
            }
        }

        void add(FigureDecorator* decoration)
        {
            _decorations.append(decoration);
        }

        void render() const
        {
            QList<FigureDecorator*>::ConstIterator i;
            for (i = _decorations.begin(); i != _decorations.end(); i++)
            {
                (*i)->render();
            }
        }

    protected:
        QList<FigureDecorator*> _decorations;
    };
}

