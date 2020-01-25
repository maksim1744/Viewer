#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QVector>
#include <QDebug>

#include <vector>

class TreeItem {
public:
    explicit TreeItem(const std::vector<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);
    void popChild();

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();

private:
    std::vector<TreeItem*> child_items;
    std::vector<QVariant> item_data;
    TreeItem *parent;
};

#endif // TREEITEM_H
