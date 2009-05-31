#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class Triangle;

    class NeighborDecorator : public Viewer::FigureDecorator
    {
    public:
        NeighborDecorator(const Triangle* figure);

        void render() const;
    };
}

