#include "WProtectGui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    WProtectGui ui;
    ui.show();
    return app.exec();
}


