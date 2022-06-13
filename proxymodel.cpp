#include "proxymodel.h"

#include <iostream>

ProxyModel::ProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    name = QString();
    min_price = 0;
    max_price = INT_MAX;
}
void ProxyModel::set_switch(bool state)
{
    this->state = state;
    invalidateFilter();
}
void ProxyModel::set_switch_paid(bool state_paid)
{
    this->state_paid = state_paid;
    invalidateFilter();
}

void ProxyModel::set_min_price(int min_price)
{
    this->min_price = min_price;
    invalidateFilter();
}
void ProxyModel::set_max_price(int max_price)
{
    this->max_price = max_price;
    invalidateFilter();
}
void ProxyModel::set_name(QString name)
{
    if (name.trimmed().isEmpty())
    {
        this->name = QString();
    }
    else
    {
        this->name = name;
    }
    invalidateFilter();
}

bool locate(QString target, QString sample)
{
    return (sample.toStdString().find(target.toStdString()) != std::string::npos);
}

bool ProxyModel::filterAcceptsRow(int sourceRow,
                                  const QModelIndex &sourceParent) const
{
    // Handling Free/Paid
    QModelIndex type_index = sourceModel()->index(sourceRow, 6, sourceParent);
    std::string type = sourceModel()->data(type_index).toString().toStdString();
    bool checking;
    if (type == "Free")
    {
        checking = true;
    }
    else
    {
        checking = false;
    }

    // Handling price
    QModelIndex price_index = sourceModel()->index(sourceRow, 7, sourceParent);
    float price = sourceModel()->data(price_index).toFloat();
    if ((min_price > price) || (max_price < price))
    {
        return false;
    }

    if (!this->name.trimmed().isEmpty())
    {
        // Handling name
        QModelIndex name_index =
            sourceModel()->index(sourceRow, 0, sourceParent);

        QString name = sourceModel()->data(name_index).toString();

        if (this->get_switch())
        {
            return checking && (locate(this->name, name));
        }
        else if (this->get_switch_paid())
        {
            return !checking && (locate(this->name, name));
        }

        else
        {
            return locate(this->name, name);
        }
    }
    else
    {
        if (this->get_switch())
        {
            return checking;
        }
        else if (this->get_switch_paid())
        {
            return !checking;
        }

        return true;
    }

    /*
        if (this -> country.trimmed().isEmpty()) // if the user did not write a
       country return (min_population <= population) && (population <=
       max_population); // only filter by population else return population >=
       min_population && population <= max_population && country == this ->
       country;*/
}

bool ProxyModel::lessThan(const QModelIndex &one, const QModelIndex &two) const
{
    // returns "true" if element at the "left" goes first.

    QString A = sourceModel()->data(one).toString();
    QString B = sourceModel()->data(two).toString();

    return A < B;
}
