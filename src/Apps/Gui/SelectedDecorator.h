#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class Triangle;

    /*!
     * The SelectedDecorator class implements a decorator for selected
     * triangles.
     */
    class SelectedDecorator : public Viewer::FigureDecorator
    {
    public:
        SelectedDecorator(const Triangle* figure);

        void render() const;
    };
}

