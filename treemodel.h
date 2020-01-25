#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "object.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <vector>

class TreeItem;

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit TreeModel(std::vector<Object*> &initial_data, QObject *parent = nullptr);
    ~TreeModel();

    void update(std::vector<std::vector<Object*>> &data, int tick);

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void addData(std::vector<Object*> &data, TreeItem *parent);
    void setupModelData(std::vector<Object*> &initial_data, TreeItem *parent);

    TreeItem *root_item;
};

#endif // TREEMODEL_H
