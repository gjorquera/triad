#pragma once

#include <Viewer/DecoratedFigure.h>

namespace App
{

    class Triangle;

    class DecoratedTriangle : public Viewer::DecoratedFigure
    {
    public:
        DecoratedTriangle(const Triangle* figure);

        void render() const;
    };
}

