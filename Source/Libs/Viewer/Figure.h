#pragma once

#include "IFigure.h"

namespace Viewer
{

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
        Figure();

        virtual ~Figure();

        void render() const;

    protected:
        virtual IFigure* decorate() const = 0;
    };
}

