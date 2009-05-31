#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class Triangle;

    class DecoratedTriangle : public Viewer::FigureDecorator
    {
    public:
        DecoratedTriangle(const Triangle* figure);

        void render() const;
    };
}

