#include "dialogwindow.h"
#include "mainwindow.h"

DialogWindow::DialogWindow(QWidget* parent): QDialog(parent)
{
    message = new QLabel("&Enter archive name without extension:");
    input = new QLineEdit;
    message->setBuddy(input);
    ok = new QPushButton("&Ok");
    ok->setDisabled(true);
    ok->setDefault(true);
    cancel = new QPushButton("&Cancel");

    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addWidget(message);
    inputLayout->addWidget(input);

    QVBoxLayout *buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(ok);
    buttonsLayout->addWidget(cancel);

    QHBoxLayout *windowLayout = new QHBoxLayout;
    windowLayout->addLayout(inputLayout);
    windowLayout->addLayout(buttonsLayout);

    setLayout(windowLayout);
    setWindowTitle("Archive name input");

    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);


    connect(input, SIGNAL(textChanged(QString)), this, SLOT(on_text_changed(QString)));
    connect(ok, SIGNAL(clicked()), this, SLOT(on_ok_button_clicked()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(on_cancel_button_clicked()));
}

void DialogWindow::on_text_changed(QString str){
    ok->setEnabled(!str.isEmpty());
}

void DialogWindow::on_ok_button_clicked(){
    emit fileNameEntered(input->text());
    input->clear();
    emit close();
}

void DialogWindow::on_cancel_button_clicked(){
    input->clear();
    emit close();
}
