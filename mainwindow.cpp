#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_PWpreview->setEchoMode(QLineEdit::Password);
    ui->widget_generator->hide();
    this->generateNewPassword();


    /* Practice UI: */
    connect(ui->pushButton_setPassword, SIGNAL(clicked()), this, SLOT(setNewPW()));
    connect(ui->lineEdit_yourPassword, SIGNAL(returnPressed()), this, SLOT(setNewPW()));
    connect(ui->lineEdit_input, SIGNAL(textChanged(const QString)), this, SLOT(updateInterface()));
    connect(ui->pushButton_toggleHide, SIGNAL(clicked()), this, SLOT(togglePreviewHide()));

    /* PW Generator UI: */
    connect(ui->pushButton_toggleGenerator, SIGNAL(clicked()), this, SLOT(toggleGeneratorView()));
    connect(ui->spinBox_PWlength, SIGNAL(valueChanged(int)), this, SLOT(giveTooShortWarning()));
    connect(ui->pushButton_newPW, SIGNAL(clicked()), this, SLOT(generateNewPassword()));

    connect(ui->checkBox_lower, SIGNAL(stateChanged(int)), this, SLOT(changePWCheckboxes()));
    connect(ui->checkBox_upper, SIGNAL(stateChanged(int)), this, SLOT(changePWCheckboxes()));
    connect(ui->checkBox_numbers, SIGNAL(stateChanged(int)), this, SLOT(changePWCheckboxes()));
    connect(ui->checkBox_fewerSyms, SIGNAL(stateChanged(int)), this, SLOT(changePWCheckboxes()));
    connect(ui->checkBox_symbols, SIGNAL(stateChanged(int)), this, SLOT(changeSymbolsCheckbox()));

    connect(ui->toolButton_GeneratorInfo, SIGNAL(clicked()), this, SLOT(viewGeneratorInfo()));
    connect(ui->pushButton_copyPW, SIGNAL(clicked()), this, SLOT(copyPWToClipboard()));
    connect(ui->pushButton_setPW_generator, SIGNAL(clicked()), this, SLOT(setNewPWFromGen()));

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
    ui->lineEdit_input->setFocus();

    // Update Counter:
    std::string countStr = "Count: " + std::to_string(this->correctCounter);
    ui->label_counter->setStyleSheet("QLabel {color: black;}");
    ui->label_counter->setText(QString::fromStdString(countStr));
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


/*--------------------------------------------------------------*/


void MainWindow::generateNewPassword(){
    bool useLower = ui->checkBox_lower->isChecked();
    bool useUpper = ui->checkBox_upper->isChecked();
    bool useNumbers = ui->checkBox_numbers->isChecked();
    bool useSymbols = ui->checkBox_symbols->isChecked();
    bool useFewSymbols = ui->checkBox_fewerSyms->isChecked();
    int length = ui->spinBox_PWlength->value();

    std::string password = this->generatePassword(length, useLower, useUpper, useNumbers, useSymbols, useFewSymbols);
    ui->lineEdit_GenPW->setText(QString::fromStdString(password));

}

void MainWindow::toggleGeneratorView(){
    if(ui->widget_generator->isHidden()){
        ui->pushButton_toggleGenerator->setText("Generator <<");
        ui->widget_generator->show();
    }else{
        ui->pushButton_toggleGenerator->setText("Generator >>");
        ui->widget_generator->hide();
    }
}

void MainWindow::giveTooShortWarning(){
    if(ui->spinBox_PWlength->value() <= 8){
        ui->spinBox_PWlength->setStyleSheet("QSpinBox {color: red;}");
    }
    else{
        ui->spinBox_PWlength->setStyleSheet("QSpinBox {color: black;}");
    }

    // Also regenerate password
    this->generateNewPassword();
}

void MainWindow::viewGeneratorInfo(){
    QMessageBox msgBox;
    msgBox.setText("Important:\nThis password generator uses the 'std::default_random_engine' which might not be cryptographically safe.");
    msgBox.exec();
}


/*------------------------------------------------------*/


void MainWindow::changePWCheckboxes(){
    //bool useLower = ui->checkBox_lower->isChecked();
    bool useUpper = ui->checkBox_upper->isChecked();
    bool useNumbers = ui->checkBox_numbers->isChecked();
    bool useSymbols = ui->checkBox_symbols->isChecked();

    if(useUpper == false &&
       useNumbers == false &&
       useSymbols == false){
        ui->checkBox_lower->setChecked(true);
        ui->checkBox_lower->setEnabled(false);
    }
    else{
        ui->checkBox_lower->setEnabled(true);
    }

    this->generateNewPassword();
}

void MainWindow::changeSymbolsCheckbox(){
    this->changePWCheckboxes();
    if(ui->checkBox_symbols->isChecked()){
        ui->checkBox_fewerSyms->setEnabled(true);
    }
    else{
        ui->checkBox_fewerSyms->setEnabled(false);
    }
}

void MainWindow::copyPWToClipboard(){
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->lineEdit_GenPW->text());
}

void MainWindow::setNewPWFromGen(){
    ui->lineEdit_yourPassword->setText(ui->lineEdit_GenPW->text());
    this->setNewPW();
}


/* PRIVATE METHODS:   ----------------------------------------------------*/


std::string MainWindow::generatePassword(const int length, const bool lower, const bool upper, const bool numbers, const bool symbols, const bool useFewSymbols){
    const std::string lowerStr = "abcdefghijklmnopqrstuvwxyz";
    const std::string upperStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string numberStr = "0123456789";
    const std::string symbolStr = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    // Use this many fewer symbols if requested:
    int symFactor = 1;
    if(useFewSymbols){symFactor = 3;}

    std::string allChars = "";      // Yeah, this is messy but who cares
    for(int i = 0; i < symFactor; ++i){
        if(lower){allChars += lowerStr;}
        if(upper){allChars += upperStr;}
        if(numbers){allChars += numberStr;}
    }
    if(symbols){allChars += symbolStr;}

    // Create generator:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distr(0, allChars.size());

    std::string passw = "";
    for(int i = 0; i < length; ++i){
        int rnd = distr(generator);
        char randChar = allChars[rnd];

        //No idea why but randChar is sometimes '\000' and noone wants that
        if(randChar == '\000'){
            i--;
        }
        else{
            passw += randChar;
        }
    }
    return passw;
}
