#ifndef WAITBOX_H
#define WAITBOX_H

#include <QDialog>
#include <QThread>
#include <QLabel>
#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>

class WaitBox: public QDialog
{
    Q_OBJECT
private:
    QLabel* msgLabel;
    QPushButton *cancel;
public:
    WaitBox(QWidget *parent = nullptr);
    void show();
signals:
    void operation_canceled();
public slots:
    void on_cancel_button_clicked();
    void on_signal_to_close();
};

#endif // WAITBOX_H
