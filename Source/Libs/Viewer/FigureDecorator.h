#pragma once

#include "IFigure.h"

namespace Viewer
{

    /*!
     * Defines a base class for figure decorators.
     *
     * This class's main purpose is to hold an instance of the original class
     * without the decorations.
     *
     * The \b paintGL method only calls to it's "parent"'s \b paintGL method.
     *
     * Custom decorations must inherit from this class and redefine the \b
     * paintGL method.
     */
    class FigureDecorator : public IFigure
    {
    public:
        FigureDecorator(const IFigure* figure = 0);
        virtual ~FigureDecorator();
        const IFigure* figure() const;

    private:
        const IFigure* _figure;
    };
}

