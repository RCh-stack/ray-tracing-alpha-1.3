#include "authorizationwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.addLibraryPath("plugins");
    AuthorizationWindow aw;
    aw.show();

    a.setWindowIcon(QIcon(":/icons/images/main_icon.ico"));
    return a.exec();
}
