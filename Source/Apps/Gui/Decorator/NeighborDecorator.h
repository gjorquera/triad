#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleDecorator;

    /*!
     * The NeighborDecorator class implements a decorator for neighbor triangles
     * of selected triangles.
     */
    class NeighborDecorator : public Viewer::FigureDecorator
    {
    public:
        NeighborDecorator(const TriangleDecorator* figure);
        void render() const;
    };
}

