#ifndef PROXYMODEL_H
#define PROXYMODEL_H
#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
   public:
    ProxyModel(QObject* parent = 0);

    void set_min_price(int min_price);
    void set_max_price(int max_price);
    void set_switch(bool state);
    void set_switch_paid(bool state_paid);
    void set_name(QString name);
    void set_category(QString category);

    int get_min_price() const
    {
        return _min_price;
    }
    int get_max_price() const
    {
        return _max_price;
    }
    bool get_switch() const
    {
        return _state;
    }
    bool get_switch_paid() const
    {
        return _state_paid;
    }
    QString get_name() const
    {
        return _name;
    }
    QString get_category() const
    {
        return _category;
    }

   protected:
    bool lessThan(const QModelIndex& one, const QModelIndex& two) const override;
    bool filterAcceptsRow(int source_row,
                          const QModelIndex& source_parent) const override;

   private:
    QString _name;
    QString _category;
    int _min_price;
    int _max_price;
    bool _state;
    bool _state_paid;
};

#endif  // PROXYMODEL_H
