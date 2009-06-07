#include <Viewer/ComplexDecorator.h>
#include "TriangleFigure.h"
#include "Decorator/SelectedDecorator.h"
#include "Decorator/NeighborDecorator.h"

namespace App
{

    TriangleFigure::TriangleFigure(const Euclid::Triangle<Kernel>* triangle)
    {
        _triangle = triangle;
    }

    void
    TriangleFigure::paintGL() const
    {
        /// @todo implement
    }

    Viewer::FigureDecorator*
    TriangleFigure::decorations() const
    {
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        decorator->add(new SelectedDecorator(this));
        decorator->add(new NeighborDecorator(this));
        return decorator;
    }
}

