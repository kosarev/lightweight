
/*  Library of lightweight replacements to standard C++ facilities.
    https://github.com/kosarev/lightweight

    Copyright (C) 2019 Ivan Kosarev.
    ivan@kosarev.info

    Published under the MIT license.
*/

#ifndef LW_DOWNCAST_H
#define LW_DOWNCAST_H

namespace lw {

// Used to make sure that the called is() member function is
// not inherited from base classes.
template<typename T>
class downcast_token {};

template<typename D, typename B>
bool is(const B *b) {
    return b && D::is(downcast_token<const D>(), *b);
}

template<typename D, typename B>
D *downcast(B *b) {
    return !is<D>(b) ? nullptr : static_cast<D*>(b);
}

}  // namespace lw

#endif  // LW_DOWNCAST_H
