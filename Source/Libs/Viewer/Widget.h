#pragma once

#include <cassert>
#include <QtOpenGL>
#include <QList>

namespace Viewer
{
    class Figure;

    /*!
     * The Widget class inherits from \c QGLWidget to implement a custom OpenGL
     * widget viewer.
     *
     * \c QGLWidget is the default widget to display graphics through OpenGL.
     *
     * This class implements the \b paintGL method but the \b initializeGL and
     * the \b resizeGL must still be defined in child classes.
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
        typedef QList<Figure*>::Iterator      Iterator;
        typedef QList<Figure*>::ConstIterator ConstIterator;

        Widget(QWidget* parent = 0);
        virtual ~Widget();
        void add(Figure* figure);
        void clear();
        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;

    protected:
        virtual void paintGL();
        virtual void initializeGL() = 0;
        virtual void resizeGL(int width, int height) = 0;

    private:
        QList<Figure*> _figures;
    };
}

