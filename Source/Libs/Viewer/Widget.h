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
            QWidget* parent = 0)
            : QGLWidget(parent)
        {
            assert(0 != initializer && 0 != projection);
            _initializer = initializer;
            _projection = projection;
        }

        virtual ~Widget()
        {
            delete _initializer;
            delete _projection;
        }

        void add(Figure* figure)
        {
            _figures.append(figure);
        }

        void clear()
        {
            _figures.clear();
        }

    protected:
        Projection* _projection;
        Initializer* _initializer;
        QList<Figure*> _figures;

        Widget()
        {
        }

        void initializeGL()
        {
            _initializer->apply();
        }

        void paintGL()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            QList<Figure*>::ConstIterator i;
            for (i = _figures.begin(); i != _figures.end(); i++)
            {
                (*i)->render();
            }
        }

        void resizeGL(int width, int height)
        {
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            _projection->resize(width, height);
            _projection->apply();
            glMatrixMode(GL_MODELVIEW);
        }
    };
}

