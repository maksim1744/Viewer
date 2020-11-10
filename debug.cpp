#include <bits/stdc++.h>

#define VIEWER_DEBUG

namespace viewer_debug {

bool compress = true;  // encode in base64
string start_with = "!";  // start every string with this to filter after

using std::cerr, std::endl;
using std::string, std::pair, std::vector, std::shared_ptr;
using std::make_pair, std::stringstream;

string to_string(const double &x) {
    stringstream ss;
    ss.precision(5);
    ss << x;
    return ss.str();
}

string to_string(const int &x) {
    return std::to_string(x);
}

string to_string(const pair<double, double> &p) {
    return (string)"(" + to_string(p.first) + "," + to_string(p.second) + ")";
}

string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
std::unordered_map<string, int> words = {
    {"size",    0},
    {"speed",   1},
    {"flipy",   2},
    {"width",   3},
    {"font",    4},
    {"circle",  5},
    {"rect",    6},
    {"line",    7},
    {"poly",    8},
    {"text",    9},
    {"group",  10},
    {"msg",    11},
    {"tick",   12},
    {"level",  13},
};

std::unordered_map<char, int> params = {
    {'c', 0},
    {'f', 1},
    {'m', 2},
    {'p', 3},
    {'r', 4},
    {'s', 5},
    {'t', 6},
    {'w', 7},
};

const int TYPE_DOUBLE = 0;
const int TYPE_INT = 1;
const int TYPE_PAIR = 2;
const int TYPE_TAG = 3;
const int TYPE_COLOR = 4;
const int TYPE_BOOL = 5;
const int TYPE_KEEP = 6;

const int float_parts = 4;

typedef union {
    float f;
    unsigned parts;
} float_cast;
string encode_double(double value) {
    float_cast fc;
    fc.f = value;
    unsigned res = (fc.parts >> max(0, 32 - float_parts * 6));
    string s;
    for (int i = 0; i < float_parts; ++i) {
        s.push_back(base64[res & 63]);
        res >>= 6;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

// this is called only in init, so compression doesn't matter
char encode_bool(bool b) {
    return base64[b];
}

string encode_pair(pair<double, double> p) {
    return encode_double(p.first) + encode_double(p.second);
}

string encode_compressed_int(int x) {
    unsigned v = x;
    vector<int> parts;
    while (v != 0) {
        parts.push_back(v & 31);
        v >>= 5;
    }
    if (parts.empty())
        parts.push_back(0);
    string s;
    for (int i = 0; i < parts.size(); ++i) {
        if (i + 1 != parts.size())
            parts[i] += (1 << 5);
        s += base64[parts[i]];
    }
    return s;
}

string encode_int_array(vector<int> v, int ln) {
    vector<int> bits;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < ln; ++j) {
            bits.push_back(v[i] & 1);
            v[i] >>= 1;
        }
    }
    while (bits.empty() || bits.size() % 5 != 0) bits.push_back(0);
    reverse(bits.begin(), bits.end());
    string res;
    for (int i = 0; i < bits.size(); i += 5) {
        int val = 0;
        for (int j = 0; j < 5; ++j) {
            val += (bits[i + j] << (4 - j));
        }
        if (i + 5 != bits.size())
            val += (1 << 5);
        res += base64[val];
    }
    return res;
}

string encode_string(string s) {
    for (int i = 0; i < s.size(); ++i) {
        assert(s[i] < 128 && 0 <= s[i]);  // only ascii
    }
    vector<int> int_array;
    for (auto c : s) {
        int_array.push_back(c);
    }
    return encode_int_array(int_array, 7);
}

string encode_param(char param, double value) {
    assert(params.count(param));
    int c = params[param];
    // 3 bits for type, 3 for char
    c |= (TYPE_DOUBLE << 3);
    string res = base64[c] + encode_double(value);
    return res;
}

string encode_param(char param, int value) {
    assert(params.count(param));
    int c = params[param];
    // 3 bits for type, 3 for char
    c |= (TYPE_INT << 3);
    string res = base64[c] + encode_compressed_int(value);
    return res;
}

string encode_param(char param, string value) {
    assert(params.count(param));
    int c = params[param];
    // 3 bits for type, 3 for char
    c |= (TYPE_TAG << 3);
    string res = base64[c] + encode_string(value);
    return res;
}

string encode_param(char param, pair<double, double> value) {
    assert(params.count(param));
    int c = params[param];
    // 3 bits for type, 3 for char
    c |= (TYPE_PAIR << 3);
    string res = base64[c] + encode_pair(value);
    return res;
}

string encode_param(char param, bool value) {
    assert(param == 'f');
    // 3 bits for type, 3 for char
    int c = (TYPE_BOOL << 3);
    c ^= value;
    string res;
    res += base64[c];
    return res;
}

char encode_word(const string &s) {
    assert(words.count(s));
    return base64[words[s]];
}


void tick() {
#ifdef VIEWER_DEBUG
    if (compress) {
        cerr << start_with << encode_word("tick") << endl;
    } else {
        cerr << start_with << "tick" << endl;
    }
#endif
}

struct Color {
    int r = 0, g = 0, b = 0;
    int alpha = 255;

    Color(int r, int g, int b, int alpha = 255) : r(r), g(g), b(b), alpha(alpha) {}
    Color(int gray = 0) : r(gray), g(gray), b(gray), alpha(255) {}

    static const Color black;
    static const Color white;
    static const Color blue;
    static const Color green;
    static const Color red;
    static const Color yellow;
    static const Color cyan;
    static const Color magenta;
    static const Color orange;
};

const Color Color::black = Color(0, 0, 0);
const Color Color::white = Color(255, 255, 255);

const Color Color::red = Color(255, 0, 0);
const Color Color::green = Color(0, 255, 0);
const Color Color::blue = Color(0, 0, 255);

const Color Color::yellow = Color(255, 255, 0);
const Color Color::cyan = Color(0, 255, 255);
const Color Color::magenta = Color(255, 0, 255);

const Color Color::orange = Color(255, 165, 0);

string to_string(Color c) {
    string s = (string)"(" + to_string(c.r) + "," + to_string(c.g) + "," + to_string(c.b);
    if (c.alpha == 255)
        return s + ")";
    else
        return s + "," + to_string(c.alpha) + ")";
}

string encode_param(Color value) {
    int c = 0;
    // 3 bits for type, 3 for char
    c |= (TYPE_COLOR << 3);
    string res;
    vector<int> to_encode;
    if (value.r == value.g && value.g == value.b) {
        c |= 1;
        to_encode.push_back(value.r);
    } else {
        to_encode.push_back(value.r);
        to_encode.push_back(value.g);
        to_encode.push_back(value.b);
    }

    if (value.alpha == 255) {
        c |= 2;
    } else {
        to_encode.push_back(value.alpha);
    }

    reverse(to_encode.begin(), to_encode.end());
    res += base64[c];

    vector<int> bits;
    for (int i = 0; i < to_encode.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            bits.push_back(to_encode[i] & 1);
            to_encode[i] >>= 1;
        }
    }
    while (bits.empty() || bits.size() % 6 != 0) bits.push_back(0);
    reverse(bits.begin(), bits.end());
    for (int i = 0; i < bits.size(); i += 6) {
        int val = 0;
        for (int j = 0; j < 6; ++j) {
            val += (bits[i + j] << (5 - j));
        }
        res += base64[val];
    }

    return res;
}

struct Drawable {
    bool drawn = false;

    Drawable() {}

    Drawable(Drawable &other) {
        *this = other;
        other.drawn = true;
    }

    virtual void draw(int level = 0) = 0;
};

struct Init: Drawable {
    pair<double, double> size_ = {10, 10};
    int fps_ = 60;
    int width_ = 1;
    bool flipy_ = false;
    double font_size_ = 1;

    Init &size(pair<double, double> s) {
        size_ = make_pair(s.first, s.second);
        return *this;
    }

    Init &fps(int f) {
        fps_ = f;
        return *this;
    }
    Init &width(int w) {
        width_ = w;
        return *this;
    }
    Init &flipy(bool b = true) {
        flipy_ = b;
        return *this;
    }
    Init &font(double fz) {
        font_size_ = fz;
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with << encode_word("size") << encode_pair(size_) << '\n';
            cerr << start_with << encode_word("speed") << encode_compressed_int(fps_) << '\n';
            if (flipy_)
                cerr << start_with << encode_word("flipy") << encode_bool(flipy_) << '\n';
            cerr << start_with << encode_word("width") << encode_compressed_int(width_) << '\n';
            cerr << start_with << encode_word("font") << encode_double(font_size_) << '\n';
        } else {
            cerr << start_with << "size " << to_string(size_) << '\n';
            cerr << start_with << "speed " << fps_ << '\n';
            if (flipy_)
                cerr << start_with << "flipy " << flipy_ << '\n';
            cerr << start_with << "width " << width_ << '\n';
            cerr << start_with << "font " << font_size_ << '\n';
        }
        drawn = true;
#endif
    }

    ~Init() {
        if (!drawn)
            draw();
    }
};

struct Figure: Drawable {
    bool drawn = false;
    Color col;
    int w = 1;
    bool f = false;  // fill
    vector<string> tags;
    bool keep_ = false;

    Figure() {}
    Figure(Figure &f) {
        *this = f;
        f.drawn = true;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << encode_param(col);
            if (w != 1)
                cerr << encode_param('w', w);
            for (auto t : tags)
                cerr << encode_param('t', t);
            if (keep_)
                cerr << base64[TYPE_KEEP << 3];
            cerr << endl;
        } else {
            cerr << "col=" << to_string(col) << ' ';
            if (w != 1)
                cerr << "w=" << w << ' ';
            for (auto t : tags)
                cerr << "t=" << t << ' ';
            cerr << endl;
        }
        drawn = true;
#endif
    }
};

struct Circle: Figure {
    pair<double, double> c = {0, 0};
    double r = 1;

    Circle() {}
    Circle(pair<double, double> c, double r) : c(c), r(r) {}

    Circle &center(pair<double, double> c) {
        this->c = make_pair(c.first, c.second);
        return *this;
    }
    Circle &radius(double r) {
        this->r = r;
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with;
            if (level != 0) {
                cerr << encode_word("level") << encode_compressed_int(level);
            }
            cerr << encode_word("circle") << encode_param('c', c) << encode_param('r', r) << encode_param('f', f);
        } else {
            cerr << start_with << string(level, ' ');
            cerr << "circle c=" << to_string(c) << ' ' << "r=" << r << ' ';
            cerr << "f=" << f << ' ';
        }
        Figure::draw();
#endif
    }

    template<typename... Args>
    auto &color(Args... args) {
        col = Color(args...);
        return *this;
    }
    auto &tag(string t) {
        this->tags.push_back(t);
        return *this;
    }
    auto &fill(bool b = true) {
        f = b;
        return *this;
    }
    auto &width(int wi) {
        w = wi;
        return *this;
    }
    auto &alpha(int a) {
        col.alpha = a;
        return *this;
    }
    auto &keep(bool b) {
        keep_ = b;
        return *this;
    }

    ~Circle() {
        if (!drawn)
            draw();
    }
};

struct Rect: Figure {
    pair<double, double> c = {0, 0};
    pair<double, double> sz = {1, 1};

    Rect() {}
    Rect(pair<double, double> a, pair<double, double> b) {
        c = a;
        sz = b;
    }
    static Rect from_center(pair<double, double> c, pair<double, double> sz) {
        Rect r;
        r.c = c;
        r.sz = sz;
        return r;
    }
    static Rect from_corners(pair<double, double> a, pair<double, double> b) {
        Rect r;
        r.c = make_pair((a.first + b.first) / 2, (a.second + b.second) / 2);
        r.sz = make_pair(abs(a.first - b.first), abs(a.second - b.second));
        return r;
    }

    Rect &center(pair<double, double> c) {
        this->c = make_pair(c.first, c.second);
        return *this;
    }
    Rect &size(pair<double, double> s) {
        this->sz = s;
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with;
            if (level != 0) {
                cerr << encode_word("level") << encode_compressed_int(level);
            }
            cerr << encode_word("rect") << encode_param('c', c) << encode_param('s', sz) << encode_param('f', f);
        } else {
            cerr << start_with << string(level, ' ');
            cerr << "rect c=" << to_string(c) << ' ' << "s=" << to_string(sz) << ' ';
            cerr << "f=" << f << ' ';
        }
        Figure::draw();
#endif
    }

    template<typename... Args>
    auto &color(Args... args) {
        col = Color(args...);
        return *this;
    }
    auto &tag(string t) {
        this->tags.push_back(t);
        return *this;
    }
    auto &fill(bool b = true) {
        f = b;
        return *this;
    }
    auto &width(int wi) {
        w = wi;
        return *this;
    }
    auto &alpha(int a) {
        col.alpha = a;
        return *this;
    }
    auto &keep(bool b) {
        keep_ = b;
        return *this;
    }

    ~Rect() {
        if (!drawn)
            draw();
    }
};

struct Line: Figure {
    pair<double, double> s = {0, 0};
    pair<double, double> f = {0, 0};

    Line() {}
    Line(pair<double, double> s, pair<double, double> f) : s(s), f(f) {
    }

    Line &start(pair<double, double> s) {
        this->s = s;
        return *this;
    }
    Line &finish(pair<double, double> f) {
        this->f = f;
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with;
            if (level != 0) {
                cerr << encode_word("level") << encode_compressed_int(level);
            }
            cerr << encode_word("line") << encode_param('s', s) << encode_param('f', f);
        } else {
            cerr << start_with << string(level, ' ');
            cerr << "line s=" << to_string(s) << ' ' << "f=" << to_string(f) << ' ';
        }
        Figure::draw();
#endif
    }

    template<typename... Args>
    auto &color(Args... args) {
        col = Color(args...);
        return *this;
    }
    auto &tag(string t) {
        this->tags.push_back(t);
        return *this;
    }
    auto &width(int wi) {
        w = wi;
        return *this;
    }
    auto &alpha(int a) {
        col.alpha = a;
        return *this;
    }
    auto &keep(bool b) {
        keep_ = b;
        return *this;
    }

    ~Line() {
        if (!drawn)
            draw();
    }
};

struct Poly: Figure {
    vector<pair<double, double>> pts;

    Poly() {}
    Poly(vector<pair<double, double>> v) : pts(v) {
    }

    Poly &points(vector<pair<double, double>> v) {
        this->pts = v;
        return *this;
    }
    Poly &point(pair<double, double> p) {
        if (!pts.empty() && pts.back() == p) return *this;
        pts.push_back(p);
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with;
            if (level != 0) {
                cerr << encode_word("level") << encode_compressed_int(level);
            }
            cerr << encode_word("poly") << encode_param('f', f);
            for (auto point : pts)
                cerr << encode_param('p', point);
        } else {
            cerr << start_with << string(level, ' ');
            cerr << "poly ";
            for (auto point : pts) {
                cerr << "p=" << to_string(point) << ' ';
            }
            cerr << "f=" << f << ' ';
        }
        Figure::draw();
#endif
    }

    template<typename... Args>
    auto &color(Args... args) {
        col = Color(args...);
        return *this;
    }
    auto &tag(string t) {
        this->tags.push_back(t);
        return *this;
    }
    auto &fill(bool b = true) {
        f = b;
        return *this;
    }
    auto &width(int wi) {
        w = wi;
        return *this;
    }
    auto &alpha(int a) {
        col.alpha = a;
        return *this;
    }
    auto &keep(bool b) {
        keep_ = b;
        return *this;
    }

    ~Poly() {
        if (!drawn)
            draw();
    }
};

struct Text: Figure {
    string m;
    double s = 1;  // font
    pair<double, double> c = {0, 0};

    Text() {}
    Text(string s) : m(s) {
    }

    Text &msg(string s) {
        m = s;
        return *this;
    }
    Text &center(pair<double, double> p) {
        c = p;
        return *this;
    }
    Text &font(double f) {
        s = f;
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with;
            if (level != 0) {
                cerr << encode_word("level") << encode_compressed_int(level);
            }
            cerr << encode_word("text") << encode_param('m', m) << encode_param('s', s) << encode_param('c', c);
        } else {
            cerr << start_with << string(level, ' ');
            cerr << "text ";
            cerr << "m=" << m << ' ';
            cerr << "s=" << s << ' ';
            cerr << "c=" << to_string(c) << ' ';
        }
        Figure::draw();
#endif
    }

    template<typename... Args>
    auto &color(Args... args) {
        col = Color(args...);
        return *this;
    }
    auto &tag(string t) {
        this->tags.push_back(t);
        return *this;
    }
    auto &fill(bool b = true) {
        f = b;
        return *this;
    }
    auto &width(int wi) {
        w = wi;
        return *this;
    }
    auto &alpha(int a) {
        col.alpha = a;
        return *this;
    }
    auto &keep(bool b) {
        keep_ = b;
        return *this;
    }

    ~Text() {
        if (!drawn)
            draw();
    }
};

struct Group: Drawable {
    vector<shared_ptr<Drawable>> items;
    string name;

    Group() {}
    Group(string name) : name(name) {}

    template<typename T>
    Group &add(T &&d) {
        d.drawn = true;
        T *dc = new T(d);
        items.push_back(shared_ptr<Drawable>(dc));
        return *this;
    }

    template<typename T>
    Group &add(T &d) {
        d.drawn = true;
        T *dc = new T(d);
        items.push_back(shared_ptr<Drawable>(dc));
        return *this;
    }

    void draw(int level = 0) override {
#ifdef VIEWER_DEBUG
        if (compress) {
            cerr << start_with;
            if (level != 0) {
                cerr << encode_word("level") << encode_compressed_int(level);
            }
            cerr << encode_word("group") << '\n';
        } else {
            cerr << start_with << string(level, ' ');
            cerr << "group" << '\n';
        }
        for (auto p : items) {
            p->draw(level + 1);
        }
        drawn = true;
#endif
    }

    ~Group() {
        if (!drawn)
            draw();
    }
};

void Message(string s) {
#ifdef VIEWER_DEBUG
    if (compress) {
        cerr << start_with << encode_word("msg") << encode_string(s) << endl;
    } else {
        cerr << start_with << "msg " << s << endl;
    }
#endif
}

}  // viewer_debug
