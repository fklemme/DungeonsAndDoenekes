#pragma once

// Find last element for which predicate p returns true. Returns "last" if no element is found.
// (It is assumed that "last" is usually std::end() and must not be accessed.)
template <typename InputIt, typename UnaryPredicate>
constexpr InputIt find_last_if(InputIt first, InputIt last, UnaryPredicate p) {
    auto it = last;
    while (it != first)
        if (p(*--it)) return it;
    return last;
}