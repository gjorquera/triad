#pragma once

#include <Viewer/Figure.h>

namespace App
{

    /*!
     * The Triangle class is the renderizable figure of the Viewer section.
     *
     * This class is in charge of returning the appropiate decorations based on
     * the state of the current triangle instance.
     */
    class Triangle : public Viewer::Figure
    {
    public:
        Triangle();

    protected:
        Viewer::IFigure* decorate() const;
    };
}

