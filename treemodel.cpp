#include "treemodel.h"
#include "treeitem.h"

#include <QStringList>

TreeModel::TreeModel(Group *initial_data, QObject *parent)
    : QAbstractItemModel(parent) {
    root_item = new TreeItem({tr("Object"), tr("Info"), tr("")});
    setupModelData(initial_data, root_item);
}

TreeModel::~TreeModel() {
    delete root_item;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return root_item;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    TreeItem *item = getItem(index);
    if (role == Qt::CheckStateRole) {
        if(item->isChecked())
            item->setChecked(false);
        else
            item->setChecked(true);
        emit dataChanged(index, index);
        return true;
    }

    if (role != Qt::EditRole)
        return false;
    // bool result = item->setData(index.column(), value);
    bool result = true;

    if (result)
        emit dataChanged(index, index);

    return result;
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return root_item->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 2)
        return static_cast<int>(item->isChecked() ? Qt::Checked : Qt::Unchecked);

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() == 2)
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root_item->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parent_item;

    if (!parent.isValid())
        parent_item = root_item;
    else
        parent_item = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *child_item = parent_item->child(row);
    if (child_item)
        return createIndex(row, column, child_item);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem *child_item = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parent_item = child_item->parentItem();

    if (parent_item == root_item)
        return QModelIndex();

    return createIndex(parent_item->row(), 0, parent_item);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parent_item;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parent_item = root_item;
    else
        parent_item = static_cast<TreeItem*>(parent.internalPointer());

    return parent_item->childCount();
}

void TreeModel::addData(Group *data, TreeItem *parent) {
    if (data != nullptr)
        data->writeToTree(parent);
}

void TreeModel::update(std::vector<Group *> &data, int tick) {
    while (root_item->childCount() > 1) {
        root_item->popChild();
    }
    addData(data[tick], root_item);
}

void TreeModel::setupModelData(Group *initial_data, TreeItem *parent) {
    addData(initial_data, parent);
}
