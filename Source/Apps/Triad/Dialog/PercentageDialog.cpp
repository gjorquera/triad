#include "PercentageDialog.h"

namespace App
{

    PercentageDialog::PercentageDialog(QWidget* parent)
        : QDialog(parent), Ui::PercentageDialog()
    {
        setupUi(this);
    }

    PercentageDialog::~PercentageDialog()
    {
    }
}

