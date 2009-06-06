#pragma once

namespace Viewer
{
    class FigureDecorator;

    /*!
     * The Figure class defines a renderizable component.
     *
     * This class defines the \b decorate method that returns a new instance of
     * a DecoratedFigure based on this figure. This class is called by \b
     * render, to render a decorated version of it's instance.
     */
    class Figure : public IFigure
    {
    public:
        virtual ~Figure();

    protected:
        virtual FigureDecorator* decorations() const = 0;
    };
}

