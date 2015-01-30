#include <QApplication>

#include "mojdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MojDialog* dialog = new MojDialog();
    dialog->show();

    return app.exec();
}
