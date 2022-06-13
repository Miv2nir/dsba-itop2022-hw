#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

#include "app.h"

namespace Ui
{
class CartWindow;
}

class CartWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit CartWindow(QWidget *parent = nullptr);
    ~CartWindow();
    void createTableCart();
    void obtainCart(std::vector<App> vcart);
    QStandardItemModel *get_model_cart() const
    {
        return model_cart;
    }

    void setModelPointer(QStandardItemModel *model_cart);

   private slots:

   private:
    Ui::CartWindow *ui;
    std::vector<App> vcart;
    QStandardItemModel *model_cart;
};

#endif  // CARTWINDOW_H
