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
        ComplexDecorator();
        virtual ~ComplexDecorator();
        void add(FigureDecorator* decoration);
        void paintGL() const;

    private:
        QList<FigureDecorator*> _decorations;
    };
}

