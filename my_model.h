#ifndef MY_MODEL_H
#define MY_MODEL_H

#include <QAbstractTableModel>
#include <QTime>
#include <QColor>
#include <QBrush>

struct inf{
    QString title;
    QVariant TBegin;
    QVariant TEnd;
    bool status;
};

class my_model : public QAbstractTableModel {
public:
    my_model(QVector<inf> & list, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;//+
    int Size();
    int columnCount(const QModelIndex &parent) const;//+
    QVariant data(const QModelIndex &index, int role) const;//
    bool setData(const QModelIndex &index, const QVariant &value, int role);//
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;//+
    bool insertRows(int row, int count, const QModelIndex &parent);//
    Qt::ItemFlags flags(const QModelIndex &index) const;//
    void sort(int column, Qt::SortOrder order);//
private:
    QVector<inf> list;
};

#endif // MY_MODEL_H
