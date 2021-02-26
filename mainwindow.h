#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "misc.cpp"

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

    std::string currPassword;

private slots:
    void setNewPW();
    void updateInterface();
    void resetInterface();
    void togglePreviewHide();
};
#endif // MAINWINDOW_H