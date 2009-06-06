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
}

