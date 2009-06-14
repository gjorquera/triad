#pragma once

#include <cassert>
#include <QtOpenGL>
#include <QMap>

namespace Viewer
{
    class Figure;

    /*!
     * Inherits from \c QGLWidget to implement a custom OpenGL
     * widget viewer.
     *
     * This class implements the \b paintGL method but the \b initializeGL and
     * the \b resizeGL must still be implemented in inherited classes.
     *
     * This class only draws instances of the Figure class. You can \b add
     * figures as well as \b clear all the assigned figures.
     *
     * The \b clear method does not delete the actual figures.
     *
     * @see http://doc.trolltech.com/4.5/qglwidget.html
     */
    class Widget : public QGLWidget
    {
        Q_OBJECT

    public:
        Widget(QWidget* parent = 0);
        virtual ~Widget();
        void add(Figure* figure);
        void clear();
        QList<Figure*> figures() const;

    public slots:
        void setPicking(bool picking);

    protected:
        virtual void paintGL();
        virtual void mouseReleaseEvent(QMouseEvent* event);
        virtual void resizeGL(int width, int height);
        virtual void initializeGL() = 0;
        virtual void viewportGL(int width, int height) = 0;
        virtual void projectionGL(int width, int height) = 0;

    private:
        int _lastId;
        QMap<int,Figure*> _figures;
        bool _picking;
    };
}

