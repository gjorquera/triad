#include "Widget.h"

namespace Viewer
{

    Widget::Widget()
    {
    }

    Widget::Widget(Initializer* initializer, Projection* projection,
        QWidget* parent)
        : QGLWidget(parent)
    {
        assert(0 != initializer && 0 != projection);
        _initializer = initializer;
        _projection = projection;
    }

    /*virtual*/
    Widget::~Widget()
    {
        delete _initializer;
        delete _projection;
    }

    void
    Widget::add(Figure* figure)
    {
        _figures.append(figure);
    }

    void
    Widget::clear()
    {
        _figures.clear();
    }

    void
    Widget::initializeGL()
    {
        _initializer->apply();
    }

    void
    Widget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        QList<Figure*>::ConstIterator i;
        for (i = _figures.begin(); i != _figures.end(); i++)
        {
            (*i)->render();
        }
    }

    void
    Widget::resizeGL(int width, int height)
    {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        _projection->resize(width, height);
        _projection->apply();
        glMatrixMode(GL_MODELVIEW);
    }
}

