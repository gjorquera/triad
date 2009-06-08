#include "FigureIterator.h"
#include "Figure.h"

namespace Viewer
{

    FigureIterator::FigureIterator(const Widget& widget)
        : QListIterator<Figure*>(widget.figures())
    {
    }
}

