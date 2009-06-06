#pragma once

#include <GL/gl.h>

namespace Viewer
{

    /*!
     * The IFigure class defines the interface for the concrete figure and it's
     * decorators.
     *
     * The IFigure, Figure and FigureDecorator classes implements the Decorator
     * Pattern.
     *
     * The only method that this interface declares is the \b paintGL method
     * which is called whenever the Widget wants to draw it's figures.
     */
    class IFigure
    {
    public:
        virtual ~IFigure();
        virtual void paintGL() const = 0;
    };
}

