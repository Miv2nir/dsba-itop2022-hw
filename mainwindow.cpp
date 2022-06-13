#include "mainwindow.h"

#include <QFileDialog>
#include <QPainter>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "./ui_mainwindow.h"
#include "cartwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createTable();

    proxy = new ProxyModel();
    proxy->setSourceModel(model);
    ui->tableView->setModel(proxy);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);

    // spinbox presets

    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(50000000);
    ui->spinBox->setValue(0);

    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(50000000);
    ui->spinBox_2->setValue(50000000);
}

std::vector<std::string> processLine(std::string line)
{
    std::vector<std::string> v = {};
    std::string piece = "";
    int count = 8;
    bool bracket = false;
    for (int i = line.size(); i >= 0; i--)
    {
        if (line[i] == '"')
        {
            bracket = !bracket;
        }
        else if (line[i] == ',' && count)
        {
            if (!bracket)
            {
                if (piece == "")
                {
                    piece = "0";
                }
                std::reverse(piece.begin(), piece.end());
                v.insert(v.begin(), piece);
                // std::cout << "processLine: piece = " << piece << std::endl;
                piece = "";
                count--;
            }
            else
            {
                piece += line[i];
            }
        }
        else
        {
            piece += line[i];
        }
    }
    std::reverse(piece.begin(), piece.end());
    v.insert(v.begin(), piece);
    // std::cout << "processLine: piece Final = " << piece << std::endl;
    return v;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    model = new QStandardItemModel(0, 9, this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Category"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Rating"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Reviews"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Size"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Installs"));
    model->setHorizontalHeaderItem(6, new QStandardItem("Type"));
    model->setHorizontalHeaderItem(7, new QStandardItem("Price"));
    model->setHorizontalHeaderItem(8, new QStandardItem("Update"));

    // ui->tableView->setModel(model);
    // ui->tableView->setEditTriggers(
    // QAbstractItemView::EditTrigger::NoEditTriggers);
    QFile table(QString::fromStdString("apps.csv"));
    table.open(QIODevice::ReadOnly);

    table.readLine();
    while (!table.atEnd())
    {
        std::string line, piece;
        line = table.readLine().toStdString();
        std::stringstream s(line);
        ////std::cout << line << std::endl;
        std::vector<std::string> v = processLine(line);

        App app;
        app.name = v[0];
        app.category = v[1];
        // //std::cout << v[2] << std::endl;

        app.rating = stof(v[2]);
        app.reviews_count = stoi(v[3]);

        app.size = stof(v[4]);
        app.installs = v[5];
        app.type = v[6];

        app.price = stof(v[7]);
        app.update = v[8];
        list.push_back(app);
        // std::cout << "Done" << std::endl;
    }
    table.close();
    for (int i = 0; i < list.size(); i++)
    {
        model->insertRows(i, 1);
        model->setData(model->index(i, 0),
                       QString::fromStdString(list[i].name));
        model->setData(model->index(i, 1),
                       QString::fromStdString(list[i].category));
        model->setData(model->index(i, 2), list[i].rating);
        model->setData(model->index(i, 3), list[i].reviews_count);
        model->setData(model->index(i, 4), list[i].size);
        model->setData(model->index(i, 5),
                       QString::fromStdString(list[i].installs));
        model->setData(model->index(i, 6),
                       QString::fromStdString(list[i].type));
        model->setData(model->index(i, 7), list[i].price);
        model->setData(model->index(i, 8),
                       QString::fromStdString(list[i].update));
    }
}

void MainWindow::on_searchThing_textChanged(const QString &arg1)
{
    // std::cout << "hi looser" << std::endl;
    proxy->set_name(arg1);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    // std::cout << "changed" << std::endl;
    if (ui->checkBox->checkState() == Qt::Checked)
    {
        proxy->set_switch(true);
    }
    else
    {
        proxy->set_switch(false);
    }
}

void MainWindow::on_checkBox_paid_stateChanged(int arg1)
{
    if (ui->checkBox_paid->checkState() == Qt::Checked)
    {
        proxy->set_switch_paid(true);
    }
    else
    {
        proxy->set_switch_paid(false);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    proxy->set_min_price(arg1);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    proxy->set_max_price(arg1);
}

void MainWindow::on_pushButton_clicked()
{
    CartWindow cartWindow;
    // std::cout << "passed? " << vcart[0].name << std::endl;

    cartWindow.obtainCart(vcart);
    cartWindow.setModelPointer(model);

    cartWindow.setModal(true);
    cartWindow.exec();
}

void MainWindow::on_pushButton_addToCart_clicked()
{
    // QItemSelectionModel *selection = ui->tableView->currentIndex().row();
    App item;

    item.name =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].name;

    item.category =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].category;
    item.rating =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].rating;
    item.reviews_count =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()]
            .reviews_count;
    item.size =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].size;
    item.installs =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].installs;
    item.type =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].type;
    item.price =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].price;
    item.update =
        list[proxy->mapToSource(ui->tableView->currentIndex()).row()].update;
    vcart.push_back(item);

    // cartWindow.obtainCart(vcart);
    /*int i = model_cart->rowCount();

    model_cart->insertRows(i, 1);
    model_cart->setData(model_cart->index(i, 0),
                        QString::fromStdString(item.name));
    model_cart->setData(model_cart->index(i, 1),
                        QString::fromStdString(item.category));
    model_cart->setData(model_cart->index(i, 2), item.rating);
    model_cart->setData(model_cart->index(i, 3), item.reviews_count);
    model_cart->setData(model_cart->index(i, 4), item.size);
    model_cart->setData(model_cart->index(i, 5),
                        QString::fromStdString(item.installs));
    model_cart->setData(model_cart->index(i, 6),
                        QString::fromStdString(item.type));
    model_cart->setData(model_cart->index(i, 7), item.price);
    model_cart->setData(model_cart->index(i, 8),
                        QString::fromStdString(item.update));*/
}

void MainWindow::on_pushButton_RemoveFromCart_clicked()
{
    for (std::vector<App>::iterator it = vcart.begin(); it < vcart.end(); it++)
    {
        if (list[proxy->mapToSource(ui->tableView->currentIndex()).row()].name == it->name)
        {
            vcart.erase(it);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(QBrush(Qt::black)));
    painter.drawLine(700, 40, 700, 120);
    painter.drawLine(700, 120, 775, 80);
    painter.drawLine(775, 80, 700, 40);
    painter.drawLine(725, 80, 650, 80);
    painter.drawLine(710, 130, 785, 90);
    painter.drawLine(785, 70, 710, 30);
}
