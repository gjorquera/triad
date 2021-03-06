#pragma once

#include "IFigure.h"

namespace Viewer
{
    class FigureDecorator;

    /*!
     * Defines a drawable component.
     *
     * This class defines the \b decorations method that returns a new instance
     * of a FigureDecorator based on this figure. This class is created inside a
     * \b paintGL method to render a paint version of it's instance.
     */
    class Figure : public IFigure
    {
    public:
        virtual ~Figure();
        virtual void clicked() = 0;
        virtual FigureDecorator* decorations() const = 0;
    };
}

