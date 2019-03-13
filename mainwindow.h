#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stellar/SecretKey.h"
#include <sodium.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_secretSeedInput_textChanged(const QString &arg1);
    void on_ethAddrInput_textChanged(const QString &arg1);

private:
    void checkSignature();
    QString checkSecretSeed();
    QString checkEthAddr();

    void clearState();

    stellar::SecretKey key;
    std::array<unsigned char, 40 + crypto_sign_ed25519_BYTES> resultBuffer;
    unsigned long long resultLength;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
