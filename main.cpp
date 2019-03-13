#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator myappTranslator;
    myappTranslator.load("bpfk_airdrop_signer.kr.qm");
    a.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
