#include "Figure.h"

namespace Viewer
{

    Figure::Figure()
        : IFigure()
    {
    }

    /*virtual*/
    Figure::~Figure()
    {
    }

    void
    Figure::render() const
    {
        IFigure* figure = decorate();
        figure->render();
        delete figure;
    }
}

