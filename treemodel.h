#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "objects/object.h"
#include "objects/group.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <vector>

class TreeItem;

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit TreeModel(Group *initial_data, QObject *parent = nullptr);
    ~TreeModel();

    void update(std::vector<Group *> &data, int tick);
    int getCurrentTick();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    TreeItem *getItem(const QModelIndex &index) const;
    void addData(Group *data, TreeItem *parent);
    void setupModelData(Group *initial_data, TreeItem *parent);

    int current_tick = 0;

    TreeItem *root_item;
};

#endif // TREEMODEL_H
