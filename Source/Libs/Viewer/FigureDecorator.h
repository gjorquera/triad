#pragma once

#include "IFigure.h"

namespace Viewer
{

    /*!
     * The FigureDecorator class defines a base class for figure decorators.
     *
     * This class's main purpose is to hold an instance of the original class
     * without the decorations.
     *
     * The \b render method only calls to it's "parent"'s render method.
     *
     * Custom decorations must inherit from this class and redefine the \b
     * render method.
     */
    class FigureDecorator : public IFigure
    {
    public:
        FigureDecorator(const IFigure* figure);
        virtual ~FigureDecorator();

    protected:
        const IFigure* _figure;

        FigureDecorator();
    };
}

