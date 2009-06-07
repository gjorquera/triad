#include "Figure.h"
#include "FigureDecorator.h"
#include "Widget.h"

namespace Viewer
{

    Widget::Widget(QWidget* parent)
        : QGLWidget(parent)
    {
        _picking = false;
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

    /*virtual*/ void
    Widget::mouseReleaseEvent(QMouseEvent* event)
    {
        if (! _picking) return;

        unsigned int selectBuf[512];
        float cursorX = event->pos().x();
        float cursorY = event->pos().y();
        int viewport[4];

        glSelectBuffer(512, selectBuf);
        glRenderMode(GL_SELECT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        resizeGL(geometry().x(), geometry().y());
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPickMatrix(cursorX, viewport[3] - cursorY, 3, 3, viewport);
        glMatrixMode(GL_MODELVIEW);

        updateGL();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        int hits = glRenderMode(GL_RENDER);

        if (hits == 0) return;

        int numberOfNames = 0;
        unsigned int names, *ptr, minZ, *ptrNames = 0;

        ptr = selectBuf;
        minZ = 0xffffffff;
        for (int i = 0; i < hits; i++)
        {
            names = *ptr;
            ptr++;
            if (*ptr < minZ) {
                numberOfNames = names;
                minZ = *ptr;
                ptrNames = ptr + 2;
            }
            ptr += names + 2;
        }
        ptr = ptrNames;
        for (int j = 0; j < numberOfNames; j++, ptr++)
        {
            Figure* figure = reinterpret_cast<Figure*>(*ptr);
            figure->clicked();
        }
    }

    Widget::Iterator
    Widget::begin()
    {
        return _figures.begin();
    }

    Widget::ConstIterator
    Widget::begin() const
    {
        return _figures.begin();
    }

    Widget::Iterator
    Widget::end()
    {
        return _figures.end();
    }

    Widget::ConstIterator
    Widget::end() const
    {
        return _figures.end();
    }

    void
    Widget::setPicking(bool picking)
    {
        _picking = picking;
    }
}

