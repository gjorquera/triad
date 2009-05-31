#pragma once

#include <Viewer/Figure.h>

namespace App
{

    class Triangle : public Viewer::Figure
    {
    public:
        Triangle();

    protected:
        Viewer::IFigure* decorate() const;
    };
}

