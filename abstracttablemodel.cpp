#include "abstracttablemodel.h"

TableModel::~TableModel()
{
    delete _alist;
}
