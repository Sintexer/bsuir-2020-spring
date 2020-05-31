#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filetranslator.h"
#include "filedecoder.h"
#include "filecollector.h"
#include "dialogwindow.h"
#include "waitbox.h"
#include "archivationthread.h"
#include "dearchivationthread.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QLabel>
#include <QMessageBox>
#include <QMainWindow>
#include <QFileInfo>

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
    void disableButtons();
signals:
    void close_waitBox();
private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_archiveButton_clicked();

    void on_dearchiveButton_clicked();

    void on_fileNameEntered(QString input);

    void when_archivation_complete();

    void when_archivation_canceled();

    void when_dearchivation_complete();

    void when_dearchivation_canceled();

    void on_deleteButton_clicked();

    void when_thread_exception_handled(QString e);

private:
    Ui::MainWindow *ui;
    QFileInfo *activeFile;
    QFileSystemModel *model;
    DialogWindow *dw;
    WaitBox *archiveWait;
    WaitBox *dearchiveWait;
    ArchivationThread *at;
    DearchivationThread *dt;
    QString fileName;
    const int MAX_DEPTH = 50;
    bool processing;
};
#endif // MAINWINDOW_H
