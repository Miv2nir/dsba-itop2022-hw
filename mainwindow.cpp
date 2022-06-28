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
    this->setWindowTitle("Google Play Digester");

    createTable();

    _proxy = new ProxyModel();
    _proxy->setSourceModel(_model);
    ui->tableView->setModel(_proxy);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::SortOrder::AscendingOrder);

    // spinbox presets

    /*ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(50000000);
    ui->spinBox->setValue(0);

    ui->spinBox_2->setMinimum(0);
    ui->spinBox_2->setMaximum(50000000);
    ui->spinBox_2->setValue(50000000);*/
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

void MainWindow::on_actionImport_triggered()
{
    _filePath = QFileDialog::getOpenFileName(this, "Open file", "", "Table files (*.csv)");
    QFile table(_filePath);
    table.open(QIODevice::ReadOnly);
    table.readLine();
    if (_model->rowCount() != 0)
    {
        //std::free(model);
        _model->removeRows(0, _model->rowCount());
        //_list = {};
        _proxy->setSourceModel(_model);
    }
    int i = -1;
    while (!table.atEnd())
    {
        i++;
        std::string line, piece;
        line = table.readLine().toStdString();
        std::stringstream s(line);
        ////std::cout << line << std::endl;
        std::vector<std::string> v = processLine(line);
        /*
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
        app.update = v[8];*/
        //_list.push_back(app);
        // implementation without vector
        _model->insertRows(i, 1);
        _model->setData(_model->index(i, 0), QString::fromStdString(v[0]));
        _model->setData(_model->index(i, 1), QString::fromStdString(v[1]));
        _model->setData(_model->index(i, 2), QString::fromStdString(v[2]));
        _model->setData(_model->index(i, 3), QString::fromStdString(v[3]));
        _model->setData(_model->index(i, 4), QString::fromStdString(v[4]));
        _model->setData(_model->index(i, 5), QString::fromStdString(v[5]));
        _model->setData(_model->index(i, 6), QString::fromStdString(v[6]));
        _model->setData(_model->index(i, 7), QString::fromStdString(v[7]));
        _model->setData(_model->index(i, 8), QString::fromStdString(v[8]));
        if (table_max < stof(v[7]))
        {
            table_max = stof(v[7]);
        }
    }
    table.close();

    /*
    for (int i = 0; i < _list.size(); i++)
    {
        _model->insertRows(i, 1);
        _model->setData(_model->index(i, 0),
                        QString::fromStdString(_list[i].name));
        _model->setData(_model->index(i, 1),
                        QString::fromStdString(_list[i].category));
        _model->setData(_model->index(i, 2), _list[i].rating);
        _model->setData(_model->index(i, 3), _list[i].reviews_count);
        _model->setData(_model->index(i, 4), _list[i].size);
        _model->setData(_model->index(i, 5),
                        QString::fromStdString(_list[i].installs));
        _model->setData(_model->index(i, 6),
                        QString::fromStdString(_list[i].type));
        _model->setData(_model->index(i, 7), _list[i].price);
        _model->setData(_model->index(i, 8),
                        QString::fromStdString(_list[i].update));
    }*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTable()
{
    _model = new QStandardItemModel(0, 9, this);
    _model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    _model->setHorizontalHeaderItem(1, new QStandardItem("Category"));
    _model->setHorizontalHeaderItem(2, new QStandardItem("Rating"));
    _model->setHorizontalHeaderItem(3, new QStandardItem("Reviews"));
    _model->setHorizontalHeaderItem(4, new QStandardItem("Size"));
    _model->setHorizontalHeaderItem(5, new QStandardItem("Installs"));
    _model->setHorizontalHeaderItem(6, new QStandardItem("Type"));
    _model->setHorizontalHeaderItem(7, new QStandardItem("Price"));
    _model->setHorizontalHeaderItem(8, new QStandardItem("Update"));

    //make cart table
    _model_cart = new QStandardItemModel(0, 9, this);
    _model_cart->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    _model_cart->setHorizontalHeaderItem(1, new QStandardItem("Category"));
    _model_cart->setHorizontalHeaderItem(2, new QStandardItem("Rating"));
    _model_cart->setHorizontalHeaderItem(3, new QStandardItem("Reviews"));
    _model_cart->setHorizontalHeaderItem(4, new QStandardItem("Size"));
    _model_cart->setHorizontalHeaderItem(5, new QStandardItem("Installs"));
    _model_cart->setHorizontalHeaderItem(6, new QStandardItem("Type"));
    _model_cart->setHorizontalHeaderItem(7, new QStandardItem("Price"));
    _model_cart->setHorizontalHeaderItem(8, new QStandardItem("Update"));

    // ui->tableView->setModel(model);
    // ui->tableView->setEditTriggers(
    // QAbstractItemView::EditTrigger::NoEditTriggers);
}

void MainWindow::on_searchThing_textChanged(const QString &arg1)
{
    _proxy->set_name(arg1);
}
void MainWindow::on_searchCategory_textChanged(const QString &arg2)
{
    _proxy->set_category(arg2);
}
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    // std::cout << "changed" << std::endl;
    if (ui->checkBox->checkState() == Qt::Checked)
    {
        _proxy->set_switch(true);
    }
    else
    {
        _proxy->set_switch(false);
    }
}

void MainWindow::on_checkBox_paid_stateChanged(int arg1)
{
    if (ui->checkBox_paid->checkState() == Qt::Checked)
    {
        _proxy->set_switch_paid(true);
    }
    else
    {
        _proxy->set_switch_paid(false);
    }
}
/*
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    //_proxy->set_min_price(arg1);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    //_proxy->set_max_price(arg1);
}
*/
void MainWindow::on_pushButton_clicked()
{
    CartWindow cartWindow;
    // std::cout << "passed? " << vcart[0].name << std::endl;

    //cartWindow.obtainCart(_vcart);
    cartWindow.setModelPointer(_model_cart);

    cartWindow.setModal(true);
    cartWindow.exec();
}

void MainWindow::on_pushButton_addToCart_clicked()
{
    // QItemSelectionModel *selection = ui->tableView->currentIndex().row();
    App item;
    int i = _proxy->mapToSource(ui->tableView->currentIndex()).row();
    int j = _model_cart->rowCount();

    item.name = _model->index(i, 0).data().toString().toStdString();
    std::cout << "name ->" << item.name << std::endl;
    /*item.name =
        _list[_proxy->mapToSource(ui->tableView->currentIndex()).row()].name;*/
    /*
    item.category = _model->index(i, 1).data().toString().toStdString();
    item.rating = _model->index(i, 2).data().toString().toFloat();
    item.reviews_count = _model->index(i, 3).data().toInt();
    item.size = _model->index(i, 4).data().toFloat();
    item.installs = _model->index(i, 5).data().toString().toStdString();
    item.type = _model->index(i, 6).data().toString().toStdString();
    item.price = _model->index(i, 7).data().toFloat();
    item.update = _model->index(i, 8).data().toString().toStdString();
    _vcart.push_back(item);*/
    _model_cart->insertRows(j, 1);
    _model_cart->setData(_model_cart->index(j, 0), _model->index(i, 0).data());
    _model_cart->setData(_model_cart->index(j, 1), _model->index(i, 1).data());
    _model_cart->setData(_model_cart->index(j, 2), _model->index(i, 2).data());
    _model_cart->setData(_model_cart->index(j, 3), _model->index(i, 3).data());
    _model_cart->setData(_model_cart->index(j, 4), _model->index(i, 4).data());
    _model_cart->setData(_model_cart->index(j, 5), _model->index(i, 5).data());
    _model_cart->setData(_model_cart->index(j, 6), _model->index(i, 6).data());
    _model_cart->setData(_model_cart->index(j, 7), _model->index(i, 7).data());
    _model_cart->setData(_model_cart->index(j, 8), _model->index(i, 8).data());
    std::cout << j << " " << _model->index(i, 0).data().toString().toStdString();
}

void MainWindow::on_pushButton_RemoveFromCart_clicked()
{
    /*
    for (std::vector<App>::iterator it = _vcart.begin(); it < _vcart.end(); it++)
    {
        if (_model->index(_proxy->mapToSource(ui->tableView->currentIndex()).row(), 0).data().toString().toStdString() == it->name)
        {
            _vcart.erase(it);
        }
    }
    */
    for (int i = 0; i < _model_cart->rowCount(); i++)
    {
        if (_model->index(_proxy->mapToSource(ui->tableView->currentIndex()).row(), 0).data().toString().toStdString() == _model_cart->index(i, 0).data().toString().toStdString())
        {
            std::cout << _model_cart->index(i, 0).data().toString().toStdString();
            _model_cart->removeRow(i);
            break;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //int h = ui->label_Logo->pos().y();
    int w = ui->label_Logo->pos().x() - 80;

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(QBrush(QBrush(Qt::black)));
    painter.drawLine(w, 40, w, 120);
    painter.drawLine(w, 120, w + 75, 80);
    painter.drawLine(w + 75, 80, w, 40);
    painter.drawLine(w + 25, 80, w - 50, 80);
    painter.drawLine(w + 10, 130, w + 85, 90);
    painter.drawLine(w + 85, 70, w + 10, 30);
}

void MainWindow::on_horizontalSliderMin_sliderMoved(int position)
{
    _proxy->set_min_price((position / table_max) * 400);
    std::cout << "min" << position << std::endl;
}

void MainWindow::on_horizontalSliderMax_sliderMoved(int position)
{
    _proxy->set_max_price(((400.001 - position) / table_max) * 400);
    std::cout << "max" << position << std::endl;
}
