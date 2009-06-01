#pragma once

#include <cassert>
#include <QtOpenGL>
#include <QList>
#include "Figure.h"
#include "Initializer.h"
#include "Projection.h"

namespace Viewer
{

    /*!
     * The Widget class inherits from QGLWidget to implement a custom OpenGL
     * widget viewer.
     *
     * \c QGLWidget is the default widget to display graphics through OpenGL.
     * This class customization defines a new parent structure, so inherited
     * classes works more like a scene manager rather than a event-driven
     * widget.
     *
     * This class implements the \b initializeGL, \b resizeGL and the \b paintGL
     * \c QGLWidget methods to be able to draw using OpenGL.
     *
     * This widget uses two helper classes to configure the OpenGL environment:
     * - The @ref Initializer class implements the \b apply method that is
     *   called when the \b initializeGL method is called.
     * - The @ref Projection class implements the \b apply method that is called
     *   when the \b resizeGL method is called.
     *
     * This class only draws instances of the Figure class. You can \b add
     * figures as well as \b clear all the assigned figures.
     *
     * The \b clear method does not delete the actual figures.
     *
     * @todo Maybe do a Camera abstraction. If I make a Camera abstraction, I
     * can change back the description to "viewer" instead of "mesh viewer".
     * @todo Think of a way to define a zoom value and implement a method to see
     * all the poligons in the window "maximized".
     * @see http://doc.trolltech.com/4.5/qglwidget.html
     */
    class Widget : public QGLWidget
    {
        Q_OBJECT

    public:
        Widget(Initializer* initializer, Projection* projection,
            QWidget* parent = 0);
        virtual ~Widget();
        void add(Figure* figure);
        void clear();

    protected:
        Projection* _projection;
        Initializer* _initializer;
        QList<Figure*> _figures;

        Widget();
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);
    };
}

