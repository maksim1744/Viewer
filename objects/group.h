#ifndef GROUP_H
#define GROUP_H

#include "object.h"

#include <string>
#include <vector>

class Group : public Object {
public:
    Group();
    Group(std::string s);

    void draw(DrawProperties &draw_properties) override;
    void writeToTree(TreeItem *parent) override;

    void removeTreeItems() override;

    std::vector<Object*> objects;

    std::string name = "";
};

#endif // GROUP_H
