#include "qvariantlistlistmodel.h"

QVariantListListModel::QVariantListListModel(QObject *parent)
  : QAbstractTableModel(parent)
  ,m_varListList(NULL)
{

}

QVariantListListModel::~QVariantListListModel()
{

}

QVariant QVariantListListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayRole == role)
    {
        if(Qt::Horizontal == orientation)
        {
            return section + 1;
        }
        return section + 1;
    }
    return QVariant();
}

int QVariantListListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rowCount;
    // FIXME: Implement me!
}

int QVariantListListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
    // FIXME: Implement me!
}

QVariant QVariantListListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(NULL == m_varListList)
        return QVariant();
    if(Qt::DisplayRole == role)
    {
        const int row = index.row();
        const int col = index.column();
        if(row >= m_varListList->size())
            return QVariant();
        const int colSize = m_varListList->at(row).size();
        if(col >= colSize)
            return QVariant();
        return m_varListList->at(row).at(col);
    }
    return QVariant();
}

bool QVariantListListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column()
                && role == Qt::EditRole)
    {
        const int row = index.row();
        const int col = index.column();
        QVariant *data;
        //data.setValue(value);
        //data = m_varListList->at(row).at(col);
        //m_varListList->at(row).at(col).setValue(data);
        data = (QVariant *)(&(m_varListList->at(row).at(col)));
        data->setValue(value);

        //交换对应项的模型索引
        QModelIndex transposedIndex = createIndex(index.column(), index.row());
        //某项发生改变，发射信号( between topLeft and bottomRight inclusive)
        emit dataChanged(index, index);
        emit dataChanged(transposedIndex, transposedIndex);
        return true;
    }

    return false;
}

void QVariantListListModel::setVariantListListPtr(QList<QList<QVariant> > *ptr)
{
    if(NULL == ptr)
        return;
    m_varListList = ptr;
    updateData();
}

void QVariantListListModel::updateData()
{
    beginResetModel();
    m_rowCount = m_varListList->size();
    m_columnCount = 0;
    int colSize=0;
    for(int i=0;i<m_rowCount;++i)
    {
        colSize = m_varListList->at(i).size();
        if(colSize > m_columnCount)
        {
            m_columnCount = colSize;
        }
    }
    endResetModel();
}
