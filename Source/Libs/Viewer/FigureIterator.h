#pragma once

#include <QListIterator>
#include "Widget.h"

namespace Viewer
{

    class Figure;

    class FigureIterator : public QListIterator<Figure*>
    {
    public:
        FigureIterator(const Widget& widget);
    };
}

