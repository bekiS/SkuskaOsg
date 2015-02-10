#ifndef MOJDIALOG_H
#define MOJDIALOG_H

#include <QDialog>
#include "vizualsceny2.h"

namespace Ui {
class MojDialog;
}

class MojDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MojDialog(QWidget *parent = 0);
    ~MojDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MojDialog *ui;
    VizualSceny2* _root;
};

#endif // MOJDIALOG_H
