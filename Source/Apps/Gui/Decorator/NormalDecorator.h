#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleFigure;

    class NormalDecorator : public Viewer::FigureDecorator
    {
    public:
        NormalDecorator(const TriangleFigure* figure);
        void paintGL() const;
    };
}

