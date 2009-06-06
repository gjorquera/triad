#include "Figure.h"
#include "FigureDecorator.h"
#include "Widget.h"

namespace Viewer
{

    Widget::Widget(QWidget* parent)
        : QGLWidget(parent)
    {
    }

    /*virtual*/
    Widget::~Widget()
    {
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

    /*virtual*/ void
    Widget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        QList<Figure*>::ConstIterator i;
        for (i = _figures.begin(); i != _figures.end(); i++)
        {
            FigureDecorator* decorator = (*i)->decorations();
            decorator->paintGL();
            delete decorator;
        }
    }
}

