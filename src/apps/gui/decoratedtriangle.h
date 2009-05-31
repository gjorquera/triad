#pragma once

#include <Viewer/DecoratedFigure.h>

namespace App
{

    class DecoratedTriangle : public Viewer::DecoratedFigure
    {
    public:
        DecoratedTriangle(Viewer::IFigure* figure);

        void render();
    };
}

