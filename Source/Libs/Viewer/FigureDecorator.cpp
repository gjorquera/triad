#include "FigureDecorator.h"

namespace Viewer
{

    FigureDecorator::FigureDecorator()
    {
        _figure = 0;
    }

    FigureDecorator::FigureDecorator(const IFigure* figure)
    {
        _figure = figure;
    }

    /*virtual*/
    FigureDecorator::~FigureDecorator()
    {
    }
}

