
#include <cassert>

#include "downcast.h"

enum class shape_kind {
    square,
    circle,
};

class shape {
public:
    shape(shape_kind kind)
        : kind(kind)
    {}

    shape_kind kind;
};

class square : public shape {
public:
    square() : shape(shape_kind::square)
    {}

    static bool is(const shape &s) {
        return s.kind == shape_kind::square;
    }
};

class circle : public shape {
public:
    circle() : shape(shape_kind::circle)
    {}

    static bool is(const shape &s) {
        return s.kind == shape_kind::circle;
    }
};

static void check(const shape &s) {
    if(lw::is<square>(&s)) {
        assert(!lw::is<circle>(&s));
        return;
    }

    auto *c = lw::downcast<const circle>(&s);
    assert(c);
}

int main() {
    check(square());
    check(circle());
}
