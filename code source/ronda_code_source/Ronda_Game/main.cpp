#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    //qInfo() << qputenv("dpiawareness", "3");
    QApplication a(argc, argv);
    MainWindow w;

    QPixmap bkgnd(":/backgrounds/imgs/best_psd_1.png");
    bkgnd = bkgnd.scaled(w.size(), Qt::IgnoreAspectRatio);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);

    w.setPalette(palette);
    w.setAutoFillBackground(false);
    w.show();
    return a.exec();
}
