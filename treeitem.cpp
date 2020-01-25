#include "treeitem.h"

TreeItem::TreeItem(const std::vector<QVariant> &data, TreeItem *parent)
    : item_data(data), parent(parent) {
}

TreeItem::~TreeItem() {
    for (auto item : child_items) {
        delete item;
    }
}

void TreeItem::appendChild(TreeItem *item) {
    child_items.push_back(item);
}

void TreeItem::popChild() {
    if (!child_items.empty()) {
        delete child_items.back();
        child_items.pop_back();
    }
}

bool TreeItem::isChecked() {
    return checked;
}

void TreeItem::setChecked(bool checked) {
    this->checked = checked;
}

TreeItem *TreeItem::child(int row) {
    if (row < 0 || row >= (int)child_items.size())
        return nullptr;
    return child_items[row];
}

int TreeItem::childCount() const {
    return child_items.size();
}

int TreeItem::columnCount() const {
    return item_data.size();
}

QVariant TreeItem::data(int column) const {
    if (column < 0 || column >= (int)item_data.size())
        return QVariant();
    return item_data[column];
}

TreeItem *TreeItem::parentItem() {
    return parent;
}

int TreeItem::row() const {
    if (parent)
        return find(parent->child_items.begin(), parent->child_items.end(), this) - parent->child_items.begin();
    return 0;
}
