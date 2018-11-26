#ifndef QVARIANTLISTLISTMODEL_H
#define QVARIANTLISTLISTMODEL_H

#include <QObject>

#include <QAbstractTableModel>
#include <QList>

class QVariantListListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QVariantListListModel(QObject *parent = 0);
    ~QVariantListListModel();

#if 0
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
#else
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
#endif

    void setVariantListListPtr(QList<QList<QVariant> >* ptr);
    void updateData();

signals:

public slots:

private:
    QList<QList<QVariant> >* m_varListList;
    int m_rowCount;
    int m_columnCount;
};

#endif // QVARIANTLISTLISTMODEL_H
