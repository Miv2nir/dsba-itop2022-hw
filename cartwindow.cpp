#include "cartwindow.h"

#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "ui_cartwindow.h"

CartWindow::CartWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::CartWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Cart");
    //createTableCart();
}

CartWindow::~CartWindow()
{
    delete ui;
}

void CartWindow::setModelPointer(QStandardItemModel* model_cart)
{
    _model_cart = model_cart;
    ui->tableView_cart->setModel(_model_cart);
    ui->tableView_cart->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->labelDisplay->setText("Number of entries: " + QString::number(_model_cart->rowCount()));
}
/*
void CartWindow::obtainCart(std::vector<App> v)
{
    // std::cout << "1- " << v.size() << std::endl;
    _vcart = v;
    // std::cout << "2-" << this->vcart.size() << std::endl;
    if (v.size() == 0)
    {
        _model_cart->insertRows(0, 0);
    }
    for (int i = 0; i < v.size(); i++)
    {
        _model_cart->insertRows(i, 1);
        _model_cart->setData(_model_cart->index(i, 0),
                             QString::fromStdString(v[i].name));
        _model_cart->setData(_model_cart->index(i, 1),
                             QString::fromStdString(v[i].category));
        _model_cart->setData(_model_cart->index(i, 2), v[i].rating);
        _model_cart->setData(_model_cart->index(i, 3), v[i].reviews_count);
        _model_cart->setData(_model_cart->index(i, 4), v[i].size);
        _model_cart->setData(_model_cart->index(i, 5),
                             QString::fromStdString(v[i].installs));
        _model_cart->setData(_model_cart->index(i, 6),
                             QString::fromStdString(v[i].type));
        _model_cart->setData(_model_cart->index(i, 7), v[i].price);
        _model_cart->setData(_model_cart->index(i, 8),
                             QString::fromStdString(v[i].update));
        std::cout << v[i].name << " - " << v[i].category << std::endl;
    }
    ui->labelDisplay->setText("Number of entries: " + QString::number(v.size()));
}
*/
/*
void CartWindow::createTableCart()
{
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

    // std::cout << vcart.size() << std::endl;
}*/
