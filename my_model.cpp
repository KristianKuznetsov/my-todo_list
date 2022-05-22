#include "my_model.h"

bool cmp0(const inf &first, const inf &second) { return first.status <= second.status; }
bool cmp1(const inf &first, const inf &second) { return first.title <= second.title; }
bool cmp2(const inf &first, const inf &second) { return first.TBegin <= second.TBegin; }
bool cmp3(const inf &first, const inf &second) { return first.TEnd <= second.TEnd; }

my_model::my_model(QVector<inf> &list, QObject *parent):
    QAbstractTableModel(parent), list(list) {}

int my_model::rowCount(const QModelIndex &) const { return list.size(); }
int my_model::Size() { return list.size(); };
int my_model::columnCount(const QModelIndex &) const { return 4; }

QVariant my_model::data(const QModelIndex &index, int role) const {
    if(index.isValid() && index.row() < list.size()){
        if(index.column() != 0 && (role == Qt::DisplayRole | role == Qt::EditRole )) {
            switch (index.column()) {
               case 1: return list.at(index.row()).title; break;
               case 2: return list.at(index.row()).TBegin; break;
               case 3: return list.at(index.row()).TEnd; break;
             }
        } else if(index.column() == 0 && role == Qt::CheckStateRole)
            return (list.at(index.row()).status)? Qt::Checked : Qt::Unchecked;
        else if( role == Qt::BackgroundRole && list.at(index.row()).status == 1) return QColor(Qt::green);
        else return QVariant();
    }

    return QVariant();
}

bool my_model::setData(const QModelIndex &index, const QVariant &value, int role) {

            if (index.isValid()){
                switch (index.column()) {
                case 0: {
                    if(value == Qt::Checked) list[index.row()].status = true;
                    if(value == Qt::Unchecked) list[index.row()].status = false;
                    break;
                }
                case 1: list[index.row()].title = value.toString(); break;
                case 2: list[index.row()].TBegin = value.toTime(); break;
                case 3: list[index.row()].TEnd = value.toTime(); break;
                }
            emit dataChanged(index, index);
            return true;
        }
        return false;
};

QVariant my_model::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) return QVariant();
    if(orientation == Qt::Horizontal){
        switch (section) {
           case 0: return "status";
           case 1: return "Title";
           case 2: return "Begin Time";
           case 3: return "End Time";
         }
    } else return QVariant();
}

bool my_model::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(QModelIndex(), row, row+count-1);

    QTime temp(0,0);
    inf buf{"", temp, temp, false};
    list.push_back(buf);

    endInsertRows();
    return true;
}

Qt::ItemFlags my_model::flags(const QModelIndex &index) const {
    if(!index.isValid()) return Qt::NoItemFlags;
    switch (index.column()) {
    case 0: return Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    case 1: return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    case 2: return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    case 3: return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
}

void my_model::sort(int column, Qt::SortOrder order) {
    if(order == Qt::AscendingOrder){
        switch(column){
        case 0: std::sort(list.begin(), list.end(), cmp0); break;
        case 1: std::sort(list.begin(), list.end(), cmp1); break;
        case 2: std::sort(list.begin(), list.end(), cmp2); break;
        case 3: std::sort(list.begin(), list.end(), cmp3); break;
        }
    }
    emit dataChanged(index(0, 0), index(list.size(), 3));
}




