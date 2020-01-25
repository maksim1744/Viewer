#include "scene.h"

Scene::Scene(QWidget *parent) : QWidget(parent) {
    this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    loadData();
}

void Scene::paintEvent(QPaintEvent *event) {
    if (!is_initialized) {
        initScene();
    }

    painter = new QPainter(this);
    painter->setPen(QPen(Qt::white, 30));
    painter->fillRect(event->rect(), QBrush(QColor(200, 200, 200)));
    if (initial_data != nullptr && !initial_data->hidden)
        initial_data->draw(*painter, *this);
    if (data[tick] != nullptr && !data[tick]->hidden)
        data[tick]->draw(*painter, *this);
    // for (auto object : initial_data) {
    //     if (object != nullptr && !object->hidden)
    //         object->draw(*painter, *this);
    // }
    // if (0 <= tick && tick < (int)data.size()) {
    //     for (auto object : data[tick]) {
    //         if (object == nullptr) continue;
    //         object->draw(*painter, *this);
    //     }
    // }
    painter->end();
}

int Scene::getPenWidth() {
    return pen_width;
}

int Scene::getTickCount() {
    return data.size();
}

void Scene::setTickSlider(QSlider *slider) {
    this->tick_slider = slider;
    if (slider == nullptr) return;
    connect(this->tick_slider, &QSlider::valueChanged, [&](){this->setTick(this->tick_slider->value());});
    updateTickSlider();
}

void Scene::setPlayButton(QPushButton *button) {
    play_button = button;
    connect(play_button, &QPushButton::released, [&](){this->onPlayPressed();});
}

void Scene::setObjectTree(QTreeView *object_tree) {
    this->object_tree = object_tree;
    updateObjectTree();
}

void Scene::setTickLabel(QLabel *label) {
    this->tick_label = label;
    updateTickLabel();
}

void Scene::updateTickSlider() {
    if (tick_slider == nullptr) return;
    tick_slider->setMinimum(0);
    if (data.empty()) {
        tick_slider->setMaximum(0);
    } else {
        tick_slider->setMaximum(data.size() - 1);
    }
    tick_slider->setValue(tick);
}

void Scene::updateTickLabel() {
    std::string current = std::to_string(tick + 1);
    std::string count = std::to_string(data.size());
    tick_label->setText(QString((current + " / " + count).c_str()));
}

void Scene::updateObjectTree() {
    if (!is_running) {
        TreeModel *model = new TreeModel(initial_data);
        connect(model, &QAbstractItemModel::dataChanged, [&](){update();});
        model->update(data, tick);
        auto m = object_tree->model();
        object_tree->setModel(model);
        delete m;
    }
}

void Scene::mousePressEvent(QMouseEvent *event) {
    prev_mouse_pos = event->pos();
}

void Scene::mouseMoveEvent(QMouseEvent *event) {
    QPointF mouse_pos = event->pos();
    auto delta = (mouse_pos - prev_mouse_pos) / scale;
    if (!y_zero_on_top)
        delta.ry() *= -1;
    scene_pos -= delta;
    prev_mouse_pos = mouse_pos;
    update();
}

QPointF Scene::transformPoint(QPointF point) {
    point -= scene_pos;
    point *= scale;
    if (!y_zero_on_top)
        point.ry() = size().height() - point.ry();
    return point;
}

qreal Scene::transformLength(qreal length) {
    return length * scale;
}

void Scene::loadData() {
    data.clear();
    data.push_back(new Group());

    std::string s;

    std::vector<Group *> groups;

    while (true) {
        s = "";
        bool ok = false;
        if (std::getline(std::cin, s)) ok = true;

        int current_level = 0;
        while (!s.empty() && s[current_level] == ' ')
            ++current_level;
        s = s.substr(current_level, s.size());

        while ((int)groups.size() > current_level) {
            if (groups.size() >= 2) {
                groups[groups.size() - 2]->objects.push_back(groups.back());
            } else {
                data.back()->objects.push_back(groups.back());
            }
            groups.pop_back();
        }

        if (!ok) break;

        if (s == "tick") {
            data.push_back(new Group("tick " + std::to_string(data.size())));
        } else if (s == "end") {
            break;
        } else {
            if (data.size() <= 1) {  // init
                if (s.substr(0, 4) == "size") {
                    scene_size = Object::parsePoint(s, 5);
                } else if (s.substr(0, 5) == "width") {
                    pen_width = std::strtol(&s[5], nullptr, 10);
                } else if (s.substr(0, 5) == "speed") {
                    run_speed = std::strtod(&s[5], nullptr);
                } else if (s.substr(0, 5) == "flipy") {
                    y_zero_on_top = true;
                }
            }

            Object *object = stringToObject(s);
            if (object == nullptr) continue;

            if (object->type == "group") {
                groups.push_back((Group *)object);
            } else {
                if (groups.empty())
                    data.back()->objects.push_back(object);
                else
                    groups.back()->objects.push_back(object);
            }
        }
    }

    initial_data = data[0];
    data.erase(data.begin());

    Rectangle *rect = new Rectangle();
    rect->center = scene_size / 2;
    rect->size = scene_size;
    rect->color = Qt::white;
    rect->fill = true;
    initial_data->objects.insert(initial_data->objects.begin(), rect);

    initial_data->name = "initial";

    if (data.empty()) data.emplace_back();
    updateTickSlider();
}

Object* Scene::stringToObject(std::string s) {
    std::string type;
    size_t ind = 0;
    while (ind < s.size() && s[ind] != ' ') ++ind;
    type = s.substr(0, ind);
    s = s.substr(ind, s.size());
    if (type.substr(0, 4) == "rect") return new Rectangle(s);
    else if (type == "circle") return new Circle(s);
    else if (type == "line") return new Line(s);
    else if (type == "group") return new Group(s);
    return nullptr;
}

void Scene::onPlayPressed() {
    if (!is_running) {
        if (tick + 1 == (int)data.size())
            setTick(0);
        play_button->setText("Stop");
        is_running = true;
        run_timer = new QTimer();
        run_timer->setInterval(1000.0 / run_speed);
        connect(run_timer, &QTimer::timeout, [&](){
            ++tick;
            if (tick == (int)data.size()) {
                --tick;
                is_running = false;
                play_button->setText("Play");
                run_timer->stop();
                updateObjectTree();
            }
            setTick(tick);
        });
        run_timer->start();
    } else {
        run_timer->stop();
        play_button->setText("Play");
        is_running = false;
        updateObjectTree();
    }
}

void Scene::initScene() {
    is_initialized = true;

    scene_pos = {0, 0};
    if (scene_size.x() != 0 && scene_size.y() != 0) {
        scale = std::min((qreal)size().width() / scene_size.x(), (qreal)size().height() / scene_size.y());
        scene_pos.rx() = -((qreal)size().width() / scale - scene_size.x()) / 2;
        scene_pos.ry() = -((qreal)size().height() / scale - scene_size.y()) / 2;
    }
}

void Scene::setScale(double new_scale) {
    double k = (1.0 / scale - 1.0 / new_scale) / 2;
    scene_pos.rx() += size().width() * k;
    scene_pos.ry() += size().height() * k;
    scale = new_scale;
    if (new_scale == 1) {
        initScene();
    }
    update();
}

void Scene::setTick(int new_tick) {
    if (new_tick >= (int)data.size())
        new_tick = (int)data.size() - 1;
    if (new_tick < 0)
        new_tick = 0;
    tick = new_tick;
    updateTickSlider();
    updateTickLabel();
    updateObjectTree();
    update();
}

void Scene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Equal) {
        setScale(scale * 1.5);
    } else if (event->key() == Qt::Key_Minus) {
        setScale(scale / 1.5);
    } else if (event->key() == Qt::Key_0) {
        setScale(1);
    } else if (event->key() == Qt::Key_Right) {
        setTick(tick + 1);
    } else if (event->key() == Qt::Key_Left) {
        setTick(tick - 1);
    } else if (event->key() == Qt::Key_Space) {
        onPlayPressed();
    }
}

void Scene::wheelEvent(QWheelEvent *event) {
    setScale(scale * std::pow(1.1, event->angleDelta().y() / 120.0));
}
