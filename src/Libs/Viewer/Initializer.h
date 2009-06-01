#pragma once

#include <GL/gl.h>

namespace Viewer
{

    /*!
     * The Initializer class implements the OpenGL initialization routine.
     *
     * Different OpenGL initialization methods can be implemented extending this
     * class and redefining the \b apply method.
     *
     * This method is called when the \b initializeGL \c QGLWidget method is
     * called.
     *
     * The \b apply method is defined \c protected to avoid arbitriary calls
     * outside the OpenGL context, and Widget is defined friend to enable
     * protected method calls from Widget.
     */
    class Initializer
    {
    public:
        Initializer()
        {
        }

        virtual ~Initializer()
        {
        }

        friend class Widget;

    protected:
        virtual void apply() const
        {
            glClearColor(1.0, 1.0, 1.0, 1.0);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        }
    };
}

