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
        Initializer();

        virtual ~Initializer();

        friend class Widget;

    protected:
        virtual void apply() const;
    };
}

