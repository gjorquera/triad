#pragma once

#include <memory>
#include <QMainWindow>
#include <Viewer/Widget.h>
#include "ui_MainWindow.h"

namespace App
{

    /*!
     * The application's main window.
     */
    class MainWindow : public QMainWindow, public Ui::MainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected slots:
        void open();
        void save();

    private:
        Viewer::Widget* _viewerWidget;
    };

}

