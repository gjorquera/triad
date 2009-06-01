#pragma once

#include <GL/gl.h>

namespace Viewer
{

    /*!
     * The Projection class defines the scene projection volume interface.
     *
     * Specific projection implementations must inherit from this class and
     * implement the pure virtual method \b apply.
     *
     * The \b apply method executes the OpenGL projection volume transformation.
     * When this method is called, the \c glMatrixMode(GL_PROJECTION) and \c
     * glLoadIdentity functions have already been called and \c
     * glMatrixMode(GL_MODELVIEW) is called automatically after this method
     * returns. This is done by the @ref Widget class.
     *
     * The \b apply method can access to the \b _width and \b _height instance
     * variables that hold the actual width and height of the visualization
     * window. If the projection instance is defined with \b DYNAMIC redimension
     * policy then each time the viewport size changes the \b _width and \b
     * _height variables will change too. Else the \b _width and \b _height
     * variables will remain the same through the program execution.
     *
     * The \b apply method is defined \c protected to avoid arbitriary calls
     * outside the OpenGL context, and Widget is defined friend to enable
     * protected method calls from Widget.
     */
    class Projection
    {
    public:
        enum RedimensionPolicy
        {
            FIXED,
            DYNAMIC
        };
        friend class Widget;

        virtual ~Projection();
        void resize(int width, int height);

    protected:
        float _width;
        float _height;

        Projection();
        Projection(float width, float height,
            RedimensionPolicy redimensionPolicy);
        virtual void apply() const = 0;

    private:
        RedimensionPolicy _redimensionPolicy;
    };
}

