#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_PWpreview->setEchoMode(QLineEdit::Password);

    connect(ui->pushButton_setPassword, SIGNAL(clicked()), this, SLOT(setNewPW()));
    connect(ui->lineEdit_input, SIGNAL(textChanged(const QString)), this, SLOT(updateInterface()));
    connect(ui->pushButton_toggleHide, SIGNAL(clicked()), this, SLOT(togglePreviewHide()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setNewPW(){
    this->currPassword = ui->lineEdit_yourPassword->text().toUtf8().constData();
    ui->lineEdit_PWpreview->setText(ui->lineEdit_yourPassword->text());
    ui->lineEdit_yourPassword->setText("");
    ui->lineEdit_input->setText("");
    this->correctCounter = 0;
    this->updateInterface();

}

void MainWindow::updateInterface(){
    std::string newInput = ui->lineEdit_input->text().toUtf8().constData();

    if(startsWith(this->currPassword, newInput)){
        // If input matches entire password:
        if(newInput == this->currPassword){
            this->correctCounter++;
            std::string countStr = "Count: " + std::to_string(this->correctCounter);
            ui->label_counter->setStyleSheet("QLabel {color: green;}");
            ui->label_counter->setText(QString::fromStdString(countStr));
            this->resetInterface();
            return;
        }else{
            // Input matches part of beginning:
            if(newInput.size() >= 1){
                ui->label_counter->setStyleSheet("QLabel {color: black;}");
            }
        }
    }else{
        this->resetInterface();
    }


}

void MainWindow::resetInterface(){
    ui->lineEdit_input->setText("");
}

void MainWindow::togglePreviewHide(){
    static bool isHidden = true;
    if(isHidden){
        ui->lineEdit_PWpreview->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->lineEdit_PWpreview->setEchoMode(QLineEdit::Password);
    }
    isHidden = !isHidden;
}
