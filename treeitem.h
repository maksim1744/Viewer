#ifndef TREEITEM_H
#define TREEITEM_H

#include <QDebug>
#include <QVariant>
#include <QVector>

#include <vector>

class TreeItem {
public:
    explicit TreeItem(const std::vector<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);
    void popChild();

    bool isChecked();
    void setChecked(bool checked);

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
    bool checked = true;
};

#endif // TREEITEM_H
