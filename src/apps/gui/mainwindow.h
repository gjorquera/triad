#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"

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
};

