#pragma once

#include "IFigure.h"

namespace Viewer
{
    class FigureDecorator;

    /*!
     * The Figure class defines a drawable component.
     *
     * This class defines the \b decorations method that returns a new instance
     * of a FigureDecoration based on this figure. This class is inside a \b
     * paintGL method to render a paint version of it's instance.
     */
    class Figure : public IFigure
    {
    public:
        virtual ~Figure();
        virtual FigureDecorator* decorations() const = 0;
    };
}

