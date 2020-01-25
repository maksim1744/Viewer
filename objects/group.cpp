#include "group.h"

Group::Group() {
    type = "group";
}

Group::Group(std::string s) {
    type = "group";

    size_t ind = 0;
    while (ind < s.size() && s[ind] == ' ')
        ++ind;
    s = s.substr(ind, s.size());
    ind = 0;
    while (ind < s.size() && s[ind] != ' ')
        ++ind;
    name = s.substr(0, ind);

    while (ind < s.size()) {
        if (s.substr(ind, 2) == "t=") {
            ind += 2;
            tags.push_back(parseTag(s, ind));
        }
        while (ind < s.size() && s[ind] != ' ') ++ind;
        while (ind < s.size() && s[ind] == ' ') ++ind;
    }
}

void Group::draw(DrawProperties &draw_properties) {
    if (!needToDraw(draw_properties)) return;
    for (auto object : objects)
        if (object != nullptr)
            object->draw(draw_properties);
}

void Group::writeToTree(TreeItem *parent) {
    parent->appendChild(new TreeItem({name.c_str(), "", ""}, parent));
    tree_item = parent->child(parent->childCount() - 1);
    for (auto object : objects)
        if (object != nullptr)
            object->writeToTree(tree_item);
}

void Group::removeTreeItems() {
    tree_item = nullptr;
    for (auto object : objects)
        if (object != nullptr)
            object->removeTreeItems();
}
