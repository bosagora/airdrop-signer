#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stellar/SecretKey.h"
#include <sodium.h>

QString dataToQString(unsigned char* data, unsigned long long length)
{
    QString result = "";
    // print string in reverse order
    QString s;
    for (unsigned long long i = 0; i < length; i++)
    {
        s = QString("%1").arg(data[i], 0, 16);
        // account for single-digit hex values (always must serialize as two digits)
        if (s.length() == 1)
            result.append("0");
        result.append(s);
    }
    return result;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->key.clear();
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_secretSeedInput_textChanged(const QString&)
{
    this->key.clear();
    this->ui->pubkeyOutput->setText("");
    this->clearState();
    if (this->ui->secretSeedInput->text().isEmpty())
        return this->clearState();
    QString msg = this->checkSecretSeed();
    if (msg.length())
        return this->ui->statusBar->showMessage(msg);
    this->checkSignature();
}
void MainWindow::on_ethAddrInput_textChanged(const QString&)
{
    this->clearState();
    // Only attempt to sign if we have a valid key
    if (this->key.isZero())
        return;
    this->checkSignature();
}

void MainWindow::clearState()
{
    this->ui->statusBar->showMessage("");
    this->ui->signatureOutput->setText("");
}

void MainWindow::checkSignature()
{
    // If one of the info is missing, no need to do anything
    if (this->ui->ethAddrInput->text().isEmpty())
        return this->clearState();
    QString errMsg = this->checkEthAddr();
    if (errMsg.length())
        return this->ui->statusBar->showMessage(errMsg);

    // If we are here, we know we already have a valid key
    auto addr = this->ui->ethAddrInput->text().toLower();
    if (addr.startsWith("0x"))
        addr.remove(0, 2);
    if (0 != this->key.sign(addr.toStdString(), this->resultBuffer.data(), this->resultLength))
        return this->ui->statusBar->showMessage(tr("Encryption library returned an error while signing the address"));
    this->ui->signatureOutput->setText(dataToQString(this->resultBuffer.data(), this->resultLength));
}

QString MainWindow::checkSecretSeed()
{
    if (this->ui->secretSeedInput->text().startsWith("G"))
        return tr("Expected secret seed (starting with 'S'), not account address");
    if (!this->ui->secretSeedInput->text().contains(QRegExp("^S[0-9A-Z]{55}$")))
        return tr("Secret seed should be all uppercase, starting with S, followed by 55 other characters");
    try {
        this->key = stellar::SecretKey::fromStrKeySeed(
                    this->ui->secretSeedInput->text().toStdString());
        this->ui->pubkeyOutput->setText(QString::fromStdString(this->key.getStrKeyPublic()));
    } catch (...) {
        return tr("Invalid secret seed");
    }
    return "";
}

// Note: This performs a very basic address verification
// One could past non-valid ETH addresses and have it pass this check
// However the airdrop server will refuse those
QString MainWindow::checkEthAddr()
{
    QString addr = this->ui->ethAddrInput->text().toLower();
    if (!addr.contains(QRegExp("^(0x)?[0-9a-f]{40}$", Qt::CaseSensitive, QRegExp::PatternSyntax::RegExp)))
        return tr("Ethereum address should be 40 hexadecimal (0-9/a-f/A-F) characters");
    return "";
}


