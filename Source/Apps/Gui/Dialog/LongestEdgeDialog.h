#pragma once

#include "ui_LongestEdgeDialog.h"

namespace App
{

    /*!
     * Longest edge dialog.
     */
    class LongestEdgeDialog : public QDialog, public Ui::LongestEdgeDialog
    {
        Q_OBJECT

    public:
        LongestEdgeDialog(QWidget* parent = 0);
        ~LongestEdgeDialog();
    };
}

