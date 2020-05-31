#include "waitbox.h"

WaitBox::WaitBox(QWidget *parent)
    : QDialog(parent),
      msgLabel(new QLabel("Please wait until the end of operation", this)),
      cancel(new QPushButton("Cancel")){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->addWidget(msgLabel);
    mainLayout->addWidget(cancel);
    setLayout(mainLayout);
    setWindowFlags(Qt::Dialog
        | Qt::WindowTitleHint
        | Qt::MSWindowsFixedSizeDialogHint);
    QObject::connect(cancel, &QPushButton::clicked, this, &WaitBox::on_cancel_button_clicked);
}
void WaitBox::show(){
    QDialog::show();
}

void WaitBox::on_cancel_button_clicked(){
    emit operation_canceled();
}

void WaitBox::on_signal_to_close(){
    emit close();
}
