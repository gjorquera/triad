#pragma once

#include <Viewer/Widget.h>

namespace App
{

    /*!
     * Custom OpenGL viewer.
     */
    class DisplayWidget : public Viewer::Widget
    {
        Q_OBJECT

    public:
        DisplayWidget(QWidget *parent = 0);
    };
}

