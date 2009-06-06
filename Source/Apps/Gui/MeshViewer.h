#pragma once

#include <Viewer/Widget.h>

namespace App
{

    class MeshViewer : public Viewer::Widget
    {
        Q_OBJECT

    public:
        MeshViewer(QWidget* parent = 0);
        virtual ~MeshViewer();

    protected:
        void initializeGL();
        void resizeGL(int with, int height);
    };
}

