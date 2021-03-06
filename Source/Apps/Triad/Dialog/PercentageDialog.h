#pragma once

#include "ui_PercentageDialog.h"

namespace App
{

    /*!
     * Percentage criterion dialog.
     */
    class PercentageDialog : public QDialog, public Ui::PercentageDialog
    {
        Q_OBJECT

    public:
        PercentageDialog(QWidget* parent = 0);
        ~PercentageDialog();
    };
}

