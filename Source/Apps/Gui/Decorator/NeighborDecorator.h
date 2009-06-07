#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleFigure;

    /*!
     * The NeighborDecorator class implements a decorator for neighbor triangles
     * of selected triangles.
     */
    class NeighborDecorator : public Viewer::FigureDecorator
    {
    public:
        NeighborDecorator(const TriangleFigure* figure);
        void paintGL() const;
    };
}

