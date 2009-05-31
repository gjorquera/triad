#pragma once

#include <Viewer/FigureDecorator.h>

namespace App
{

    class Triangle;

    class SelectedDecorator : public Viewer::FigureDecorator
    {
    public:
        SelectedDecorator(const Triangle* figure);

        void render() const;
    };
}

