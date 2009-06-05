#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class TriangleDecorator;

    /*!
     * The SelectedDecorator class implements a decorator for selected
     * triangles.
     */
    class SelectedDecorator : public Viewer::FigureDecorator
    {
    public:
        SelectedDecorator(const TriangleDecorator* figure);
        void render() const;
    };
}

