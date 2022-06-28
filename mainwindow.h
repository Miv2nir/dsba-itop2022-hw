#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <vector>

#include "app.h"
#include "proxymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createTable();

   private slots:

    void on_searchThing_textChanged(const QString &arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_paid_stateChanged(int arg1);

    //void on_spinBox_valueChanged(int arg1);

    //void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_addToCart_clicked();

    void on_pushButton_RemoveFromCart_clicked();
    void on_actionImport_triggered();

    void on_searchCategory_textChanged(const QString &arg2);

    void on_horizontalSliderMin_sliderMoved(int position);

    void on_horizontalSliderMax_sliderMoved(int position);

   protected:
    void paintEvent(QPaintEvent *e);

   private:
    //std::vector<App> _vcart;
    Ui::MainWindow *ui;
    //std::vector<App> _list;
    QStandardItemModel *_model;
    QStandardItemModel *_model_cart;
    ProxyModel *_proxy;
    QString _filePath;
    float table_max = 1;
};
#endif  // MAINWINDOW_H
