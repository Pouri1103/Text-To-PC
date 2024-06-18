#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_Set_clicked()
{
    QFile f("content://com.android.externalstorage.documents/document/primary%3AADM%2FToPC%2FToPC.txt");
    if (!f.open(QIODevice::WriteOnly))
        QMessageBox::critical(this,"آدرس وجود ندارد","  لطفا این مسیر را ایجاد کنید ! \n <YourPhone/ADM/ToPC/ToPC.txt>");
    else {
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        f.resize(0);
        QTextStream set(&f);
        QString text = ui->textEdit->toPlainText();
        set<< text;

        f.close();
    }
}

void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QFile f(QFileDialog::getOpenFileName(this));
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream import(&f);
    ui->textEdit->setText(import.readAll());

    f.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QFile f(QFileDialog::getSaveFileName(this,"","","text(*.txt)"));
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&f);
    QString text = ui->textEdit->toPlainText();
    out<< text;

    f.close();
}

