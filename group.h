#ifndef GROUP_H
#define GROUP_H

#include "object.h"
#include "scene.h"

#include <string>
#include <vector>

class Group : public Object {
public:
    Group();
    Group(std::string s);

    void draw(QPainter &painter, Scene &scene) override;
    void writeToTree(TreeItem *parent) override;

    std::vector<Object*> objects;

    std::string name = "";
};

#endif // GROUP_H
