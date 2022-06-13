#include "cartwindow.h"

#include <iostream>
#include <vector>

#include "mainwindow.h"
#include "ui_cartwindow.h"

CartWindow::CartWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::CartWindow)
{
    ui->setupUi(this);
    createTableCart();
    std::vector<App> removal = {};
    ui->tableView_cart->setModel(model_cart);
    ui->tableView_cart->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

CartWindow::~CartWindow()
{
    delete ui;
}
void CartWindow::setModelPointer(QStandardItemModel* model_cart)
{
    this->model_cart = model_cart;
}

void CartWindow::obtainCart(std::vector<App> v)
{
    // std::cout << "1- " << v.size() << std::endl;
    this->vcart = v;
    // std::cout << "2-" << this->vcart.size() << std::endl;
    if (v.size() == 0)
    {
        model_cart->insertRows(0, 0);
    }
    for (int i = 0; i < v.size(); i++)
    {
        model_cart->insertRows(i, 1);
        model_cart->setData(model_cart->index(i, 0),
                            QString::fromStdString(v[i].name));
        model_cart->setData(model_cart->index(i, 1),
                            QString::fromStdString(v[i].category));
        model_cart->setData(model_cart->index(i, 2), v[i].rating);
        model_cart->setData(model_cart->index(i, 3), v[i].reviews_count);
        model_cart->setData(model_cart->index(i, 4), v[i].size);
        model_cart->setData(model_cart->index(i, 5),
                            QString::fromStdString(v[i].installs));
        model_cart->setData(model_cart->index(i, 6),
                            QString::fromStdString(v[i].type));
        model_cart->setData(model_cart->index(i, 7), v[i].price);
        model_cart->setData(model_cart->index(i, 8),
                            QString::fromStdString(v[i].update));
        std::cout << v[i].name << " - " << v[i].category << std::endl;
    }
    ui->labelDisplay->setText("Number of entries: " + QString::number(v.size()));
}

void CartWindow::createTableCart()
{
    model_cart = new QStandardItemModel(0, 9, this);
    model_cart->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model_cart->setHorizontalHeaderItem(1, new QStandardItem("Category"));
    model_cart->setHorizontalHeaderItem(2, new QStandardItem("Rating"));
    model_cart->setHorizontalHeaderItem(3, new QStandardItem("Reviews"));
    model_cart->setHorizontalHeaderItem(4, new QStandardItem("Size"));
    model_cart->setHorizontalHeaderItem(5, new QStandardItem("Installs"));
    model_cart->setHorizontalHeaderItem(6, new QStandardItem("Type"));
    model_cart->setHorizontalHeaderItem(7, new QStandardItem("Price"));
    model_cart->setHorizontalHeaderItem(8, new QStandardItem("Update"));

    // std::cout << vcart.size() << std::endl;
}
