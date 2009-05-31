#pragma once

#include <Viewer/DecoratedFigure.h>

namespace App
{

    class Triangle;

    class NeighborDecorator : public Viewer::DecoratedFigure
    {
    public:
        NeighborDecorator(const Triangle* figure);

        void render() const;
    };
}

