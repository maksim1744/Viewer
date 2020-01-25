#include "group.h"

Group::Group() {
    type = "group";
}

Group::Group(std::string s) {
    type = "group";

    int ind = 0;
    while (ind < (int)s.size() && s[ind] == ' ')
        ++ind;
    name = s.substr(ind, s.size());
}

void Group::draw(QPainter &painter, Scene &scene) {
    for (auto object : objects)
        if (object != nullptr && !object->hidden)
            object->draw(painter, scene);
}

void Group::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({name.c_str(), "", ""}, parent, this));
    parent = parent->child(parent->childCount() - 1);
    for (auto object : objects)
        if (object != nullptr)
            object->writeToTree(parent);
}
