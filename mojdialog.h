#ifndef MOJDIALOG_H
#define MOJDIALOG_H

#include <QDialog>

namespace Ui {
class MojDialog;
}

class MojDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MojDialog(QWidget *parent = 0);
    ~MojDialog();

private:
    Ui::MojDialog *ui;
};

#endif // MOJDIALOG_H
