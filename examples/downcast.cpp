
#include <cassert>

#include "downcast.h"

enum class shape_kind {
    rectangle,
    square,
    last_rectangle = square,
    circle,
};

class shape {
public:
    shape(shape_kind kind)
        : kind(kind)
    {}

    shape_kind kind;
};

class rectangle : public shape {
public:
    rectangle(shape_kind kind = shape_kind::rectangle)
        : shape(kind)
    {}

    static bool is(lw::downcast_token<const rectangle>, const shape &s) {
        return s.kind >= shape_kind::rectangle &&
               s.kind <= shape_kind::last_rectangle;
    }
};

class square : public rectangle {
public:
    square()
        : rectangle(shape_kind::square)
    {}

#if 0  // Pretend that we forgot to define this predicate.
    static bool is(lw::downcast_token<const circle>, const shape &s) {
        return s.kind == shape_kind::circle;
    }
#endif
};

class circle : public shape {
public:
    circle() : shape(shape_kind::circle)
    {}

    static bool is(lw::downcast_token<const circle>, const shape &s) {
        return s.kind == shape_kind::circle;
    }
};

static void check(const shape &s) {

    if(lw::is<circle>(&s)) {
        assert(!lw::is<rectangle>(&s));
        return;
    }

    auto *r = lw::downcast<const rectangle>(&s);
    assert(r);

    // Since the 'square' inherits its 'is()' function from
    // 'rectangle', the passed and taked downcast tokens do not
    // match, thus allowing the compiler to catch the defect.
    // assert(!lw::is<square>(r));
}

int main() {
    check(rectangle());
    check(circle());
}
