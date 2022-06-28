#ifndef ABSTRACTTABLEMODEL_H
#define ABSTRACTTABLEMODEL_H
#include <QAbstractTableModel>
#include <vector>

#include "app.h"

class TableModel : public QAbstractTableModel
{
   public:
    TableModel(std::vector<App>& list, QObject* parent = nullptr)
    {
        *_alist = list;
    };
    TableModel(QObject* parent = nullptr)
    {
        *_alist = {};
    }
    ~TableModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

   private:
    std::vector<App>* _alist;
};

#endif  // ABSTRACTTABLEMODEL_H
