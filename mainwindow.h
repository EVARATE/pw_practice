#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>
#include <chrono>
#include <QMessageBox>
#include <QClipboard>
#include <QBoxLayout>
#include <QLineEdit>
#include <QFont>
#include <QFontMetrics>
#include "misc.cpp"
#include "managed_pw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    managed_pw managedPW;

    std::string currPassword;
    int correctCounter = 0;

    std::string generatePassword(const int length,
                                 const bool lower,
                                 const bool upper,
                                 const bool numbers,
                                 const bool symbols,
                                 const bool useFewSymbols = false);

private slots:
    void setNewPW();
    void updateInterface();
    void resetInterface();
    void togglePreviewHide();

    void generateNewPassword();
    void toggleGeneratorView();
    void giveTooShortWarning();
    void viewGeneratorInfo();

    void changePWCheckboxes();
    void changeSymbolsCheckbox();
    void copyPWToClipboard();
    void setNewPWFromGen();

    // Hint system:
    void regenerateHintWidgets();

};
#endif // MAINWINDOW_H
