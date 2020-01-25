#include "treemodel.h"
#include "treeitem.h"

#include <QStringList>

TreeModel::TreeModel(std::vector<Object*> &initial_data, QObject *parent)
    : QAbstractItemModel(parent) {
    root_item = new TreeItem({tr("Object"), tr("Info")});
    setupModelData(initial_data, root_item);
}

TreeModel::~TreeModel() {
    delete root_item;
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return root_item->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
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

void TreeModel::addData(std::vector<Object*> &data, TreeItem *parent) {
    for (auto object : data) {
        if (object == nullptr) continue;
        object->writeToTree(parent);
    }
}

void TreeModel::update(std::vector<std::vector<Object*>> &data, int tick) {
    while (root_item->childCount() > 1) {
        root_item->popChild();
    }
    root_item->appendChild(new TreeItem({("tick " + std::to_string(tick + 1)).c_str(), ""}, root_item));
    addData(data[tick], root_item->child(1));
}

void TreeModel::setupModelData(std::vector<Object*> &initial_data, TreeItem *parent) {
    parent->appendChild(new TreeItem({"initial", ""}, parent));
    addData(initial_data, parent->child(0));
}
