#include <QMapIterator>
#include "Figure.h"
#include "FigureDecorator.h"
#include "Widget.h"

namespace Viewer
{

    Widget::Widget(QWidget* parent)
        : QGLWidget(parent)
    {
        _lastId = 0;
        _picking = true;
    }

    /*virtual*/
    Widget::~Widget()
    {
    }

    void
    Widget::add(Figure* figure)
    {
        _figures[++_lastId] = figure;
    }

    void
    Widget::clear()
    {
        _figures.clear();
    }

    QList<Figure*>
    Widget::figures() const
    {
        return _figures.values();
    }

    /*virtual*/ void
    Widget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        QMapIterator<int,Figure*> i(_figures);
        while (i.hasNext())
        {
            i.next();
            glPushName(i.key());
            FigureDecorator* decorator = i.value()->decorations();
            decorator->paintGL();
            delete decorator;
            glPopName();
        }
    }

    /*virtual*/ void
    Widget::resizeGL(int width, int height)
    {
        viewportGL(width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        projectionGL(width, height);
        glMatrixMode(GL_MODELVIEW);
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

        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPickMatrix(cursorX, viewport[3] - cursorY, 3, 3, viewport);
        projectionGL(geometry().x(), geometry().y());
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
            int key = *ptr;
            _figures[key]->clicked();
        }

        updateGL();
    }

    void
    Widget::setPicking(bool picking)
    {
        _picking = picking;
    }
}

