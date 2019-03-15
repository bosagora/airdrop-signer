#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#ifdef Q_OS_MACOS
 #include <corefoundation/CFBundle.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator myappTranslator;

    if (QLocale::system().language() == QLocale::Korean)
    {
        QString directory;
#ifdef Q_OS_MACOS
      CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
        CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef, kCFURLPOSIXPathStyle);
        directory = CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding());
        directory += "/Contents/Resources/";
        CFRelease(appUrlRef);
        CFRelease(macPath);
#endif
        myappTranslator.load("korean.qm", directory);
        a.installTranslator(&myappTranslator);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
