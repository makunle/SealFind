#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datareader.h"
#include "findmanager.h"
#include <QSettings>

QString LAYOUT_FILE("./layout.ini");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DataReader dr("data.txt");
    QVector<Chaptor> c = dr.getAllData();


    // 载入上次配置
    QSettings settings(LAYOUT_FILE, QSettings::IniFormat);
    QVariant var = settings.value("geometry");
    if (var.isValid())
        restoreGeometry(var.toByteArray());
    var = settings.value("windowState");
    if (var.isValid())
        restoreState(var.toByteArray());
    var = settings.value("finds");
    if(var.isValid())
        ui->text_In->setText(var.toString());


    FM.setFindInfo(c);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    FM.clearFindItem();
    QStringList items = ui->text_In->toPlainText().split('\n',QString::SkipEmptyParts);
    for(int i = 0 ; i < items.size(); i++)
    {
        QStringList it = items.at(i).split(' ', QString::SkipEmptyParts);
        if(it.size()<1)continue;
        int num = 1;
        if(it.size() > 1)num = it[1].toInt();
        FM.addFindItem(it[0], num);
    }

//    QString result = FM.findWithMinSushi();
//    ui->text_Out->clear();
//    ui->text_Out->append(result);

    FM.findWithMaxNum(ui->text_Out);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(LAYOUT_FILE, QSettings::IniFormat);
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("finds",ui->text_In->toPlainText());
    QMainWindow::closeEvent(event);
}
