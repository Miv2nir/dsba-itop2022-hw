#include "proxymodel.h"

#include <algorithm>
#include <iostream>

ProxyModel::ProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    _name = QString();
    _min_price = 0;
    _max_price = INT_MAX;
}
void ProxyModel::set_switch(bool state)
{
    _state = state;
    invalidateFilter();
}
void ProxyModel::set_switch_paid(bool state_paid)
{
    _state_paid = state_paid;
    invalidateFilter();
}

void ProxyModel::set_min_price(int min_price)
{
    _min_price = min_price;
    invalidateFilter();
}
void ProxyModel::set_max_price(int max_price)
{
    _max_price = max_price;
    invalidateFilter();
}
void ProxyModel::set_name(QString name)
{
    if (name.trimmed().isEmpty())
    {
        _name = QString();
    }
    else
    {
        _name = name;
    }
    invalidateFilter();
}
void ProxyModel::set_category(QString category)
{
    if (category.trimmed().isEmpty())
    {
        _category = QString();
    }
    else
    {
        _category = category;
    }
    invalidateFilter();
}
//TODO: fix codestyle, make sliders, replace qitemmodel with QAbstractTableModel or get rid of a vector, optional clean up filterAcceptsRow
bool locate(const QString &target, const QString &sample)
{
    return (sample.toStdString().find(target.toStdString()) != std::string::npos);
}

bool ProxyModel::filterAcceptsRow(int sourceRow,
                                  const QModelIndex &sourceParent) const
{
    // Handling Free/Paid
    QModelIndex type_index = sourceModel()->index(sourceRow, 6, sourceParent);
    std::string type = sourceModel()->data(type_index).toString().toStdString();
    bool isFree;
    if (type == "Free")
    {
        isFree = true;
    }
    else
    {
        isFree = false;
    }

    // Handling price
    QModelIndex price_index = sourceModel()->index(sourceRow, 7, sourceParent);
    float price = sourceModel()->data(price_index).toFloat();
    if ((_min_price > price) || (_max_price < price))
    {
        return false;
    }
    bool check_name = true;
    bool check_category = true;

    if (!_name.trimmed().isEmpty())
    {
        // Handling name
        QModelIndex name_index =
            sourceModel()->index(sourceRow, 0, sourceParent);

        QString name = sourceModel()->data(name_index).toString();
        check_name = locate(_name, name);
    }

    if (!_category.trimmed().isEmpty())
    {
        //Handling category
        QModelIndex category_index = sourceModel()->index(sourceRow, 1, sourceParent);

        QString category = sourceModel()->data(category_index).toString();
        check_category = locate(_category, category);
    }

    //both searches are empty
    if (this->get_switch())
    {
        return isFree && check_name && check_category;
    }
    else if (this->get_switch_paid())
    {
        return !isFree && check_name && check_category;
    }

    return check_name && check_category;
}

bool ProxyModel::lessThan(const QModelIndex &one, const QModelIndex &two) const
{
    if (one.column() == 2 || one.column() == 4 || one.column() == 7)
    {
        float a = sourceModel()->data(one).toFloat();
        float b = sourceModel()->data(two).toFloat();

        return a < b;
    }
    if (one.column() == 3)
    {
        int a = sourceModel()->data(one).toInt();
        int b = sourceModel()->data(two).toInt();

        return a < b;
    }

    QString a = sourceModel()->data(one).toString();
    QString b = sourceModel()->data(two).toString();

    return a < b;
}
