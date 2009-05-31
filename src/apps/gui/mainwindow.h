#pragma once

#include <memory>
#include <QMainWindow>
#include <Viewer/Widget.h>
#include "ui_mainwindow.h"
#include "triangle.h"

namespace App
{

    /*!
     * The application's main window.
     */
    class MainWindow : public QMainWindow, public Ui::MainWindow
    {
        Q_OBJECT

    public:
        /*!
         * Constructs a new instance of the MainWindow class given the \b parent
         * as it's parent.
         */
        MainWindow(QWidget *parent = 0);
        /*!
         * Destructor.
         */
        ~MainWindow();

    private:
        Viewer::Widget* _viewerWidget;
    };

}

