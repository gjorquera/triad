#include <cassert>
#include "FigureDecorator.h"

namespace Viewer
{

    FigureDecorator::FigureDecorator(const IFigure* figure)
    {
        _figure = figure;
    }

    /*virtual*/
    FigureDecorator::~FigureDecorator()
    {
    }

    const IFigure*
    FigureDecorator::figure() const
    {
        assert(0 != _figure);
        return _figure;
    }
}

