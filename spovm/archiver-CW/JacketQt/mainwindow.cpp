#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath());
    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0, 350);

    this->setWindowTitle("Jacket");
    resize(size().width(), size().height()*1.2);
    setWindowIcon(QIcon("./images/jacket.ico"));

    activeFile = new QFileInfo();
    dw = new DialogWindow(this);
    archiveWait = new WaitBox(this);
    dearchiveWait = new WaitBox(this);
    at = new ArchivationThread();
    dt = new DearchivationThread();


    disableButtons();

    connect(dw, &DialogWindow::fileNameEntered, this, &MainWindow::on_fileNameEntered);
    connect(at, &QThread::finished, this, &MainWindow::when_archivation_complete);
    connect(archiveWait, &WaitBox::operation_canceled, this, &MainWindow::when_archivation_canceled);
    connect(this, &MainWindow::close_waitBox, archiveWait, &WaitBox::on_signal_to_close);
    connect(dt, &QThread::finished, this, &MainWindow::when_dearchivation_complete);
    connect(dearchiveWait, &WaitBox::operation_canceled, this, &MainWindow::when_dearchivation_canceled);
    connect(this, &MainWindow::close_waitBox, dearchiveWait, &WaitBox::on_signal_to_close);
    connect(dt, &DearchivationThread::exception_executed, this, &MainWindow::when_thread_exception_handled);
    connect(at, &ArchivationThread::exception_executed, this, &MainWindow::when_thread_exception_handled);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    disableButtons();
    if(!processing){
        *activeFile = model->fileInfo(index);
        ui->infoLabel->setText(activeFile->fileName());

        if(activeFile->suffix() == "jacket")
            ui->dearchiveButton->setEnabled(true);
        ui->archiveButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
    }
}

void MainWindow::on_archiveButton_clicked()
{
    if(!activeFile->fileName().isEmpty()){
        dw->show();
    }
    else
        QMessageBox::warning(this, "Wrong input", "Please, choose file or directory first");
}

void MainWindow::on_dearchiveButton_clicked()
{
    if(activeFile->suffix() == "jacket"){
        processing = true;
        ui->infoLabel->setText("");

        dt->setFileName(activeFile->fileName());
        dt->setFilePath(activeFile->absolutePath());
        dt->start();
        dearchiveWait->show();
    }
    else{
        QMessageBox::warning(this, "Wrong file", "Please, choose file with '.jacket' extension");
    }
}

void MainWindow::on_fileNameEntered(QString input){
    if(!input.isEmpty() && FileCollector::isCorrectFileName(input)){
        processing = true;
        ui->infoLabel->setText("");

        fileName = input;
        dw->close();

        fileName+=".jacket";
        fileName.prepend('/');
        fileName.prepend(activeFile->absolutePath());

        at->setFileName(fileName);
        at->setActiveFile(activeFile);
        at->start();
        archiveWait->show();
    }
    else {
        fileName = "";
        QMessageBox::warning(this, "Wrong input", "Please, input filename without special symbols");
    }
}

void MainWindow::when_archivation_complete(){
    emit close_waitBox();
    QString prev = model->rootPath();
    model->setRootPath(activeFile->absolutePath());
    model->setRootPath(prev);
    processing = false;
    disableButtons();
}

void MainWindow::when_archivation_canceled(){
    at->requestInterruption();
    at->wait();
    emit close_waitBox();
    QFile::remove(fileName);
    processing = false;
}


void MainWindow::when_dearchivation_complete(){
    emit close_waitBox();
    QString prev = model->rootPath();
    model->setRootPath(activeFile->absolutePath());
    model->setRootPath(prev);
    processing = false;
    disableButtons();
}

void MainWindow::when_dearchivation_canceled(){
    dt->requestInterruption();
    dt->wait();
    processing = false;
    emit close_waitBox();
}

void MainWindow::on_deleteButton_clicked()
{
    if(!activeFile->fileName().isEmpty()){
        QString what("file");
        if(activeFile->isDir()){
            if(FileCollector::dirSize(activeFile->absoluteFilePath(), 0, MAX_DEPTH)>MAX_DEPTH){
                QMessageBox::warning(this, "Bad directory", "Choosen directory depth is to big");
                return;
            }
            what = "directory";
        }
        if(QMessageBox::Yes == QMessageBox::question(this, "", "Are you sure you want to delete this " + what+ "?")){
            if(activeFile->isDir()){
                QDir temp(activeFile->absoluteFilePath());
                temp.removeRecursively();
            }
            else{
                QFile temp(activeFile->absoluteFilePath());
                temp.remove();
            }

        }
    }
    else
        QMessageBox::warning(this, "Wrong input", "Please, choose file or directory first");
    processing = false;
    disableButtons();
}

void MainWindow::disableButtons(){
    ui->archiveButton->setEnabled(false);
    ui->dearchiveButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
}

void MainWindow::when_thread_exception_handled(QString e){
    QMessageBox::critical(this, "Error", e);
}
