#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleFigure;

    /*!
     * Implements a decorator for neighbor triangles
     * of selected triangles.
     *
     * Neighbor triangles are drawn with green color lines.
     */
    class NeighborDecorator : public Viewer::FigureDecorator
    {
    public:
        NeighborDecorator(const TriangleFigure* figure);
        void paintGL() const;
    };
}

