#pragma once

#include <memory>
#include <type_traits>

// Implementation of std::experimental::observer_ptr.
// Some behavior has changed to increase usability (e.g. non-explict construction from T*).
template <typename T>
class observer_ptr {
  public:
    using element_type = T;

    constexpr observer_ptr() noexcept : m_ptr(nullptr) {}
    constexpr observer_ptr(nullptr_t) noexcept : m_ptr(nullptr) {}
    /* explicit */ observer_ptr(element_type* ptr) noexcept : m_ptr(ptr) {}
    template <typename U, std::enable_if_t<std::is_convertible_v<U*, element_type*>> = 0>
    observer_ptr(observer_ptr<U> other) noexcept : m_ptr(other.m_ptr) {}
    observer_ptr(const observer_ptr& other) = default;
    observer_ptr(observer_ptr&& other) = default;

    // Own addition. Dangerous? Loss of meaning?
    // template <typename U, std::enable_if_t<std::is_convertible_v<U*, element_type*>> = 0>
    // observer_ptr(const std::unique_ptr<U>& ptr) noexcept : m_ptr(ptr.get()) {}

    constexpr element_type* release() noexcept {
        element_type* before = m_ptr;
        m_ptr = nullptr;
        return before;
    }

    constexpr void reset(element_type* ptr = nullptr) noexcept { m_ptr = ptr; }
    constexpr void swap(observer_ptr& other) noexcept { std::swap(m_ptr, other.m_ptr); }
    constexpr element_type* get() const noexcept { return m_ptr; }
    constexpr explicit operator bool() const noexcept { return m_ptr != nullptr; }
    constexpr std::add_lvalue_reference_t<element_type> operator*() const { return *m_ptr; }
    constexpr element_type* operator->() const noexcept { return m_ptr; }
    constexpr explicit operator element_type*() const noexcept { return m_ptr; }

  private:
    T* m_ptr;
};

template <typename T>
observer_ptr<T> make_observer(T* ptr) noexcept {
    return observer_ptr<T>(ptr);
}

template <typename T, typename U>
bool operator==(const observer_ptr<T>& p1, const observer_ptr<U>& p2) {
    return p1.get() == p2.get();
}

template <typename T, typename U>
bool operator!=(const observer_ptr<T>& p1, const observer_ptr<U>& p2) {
    return !(p1 == p2);
}

template <typename T>
bool operator==(const observer_ptr<T>& p, std::nullptr_t) noexcept {
    return !p;
}

template <typename T>
bool operator==(std::nullptr_t, const observer_ptr<T>& p) noexcept {
    return !p;
}

template <typename T>
bool operator!=(const observer_ptr<T>& p, std::nullptr_t) noexcept {
    return (bool)p;
}

template <typename T>
bool operator!=(std::nullptr_t, const observer_ptr<T>& p) noexcept {
    return (bool)p;
}

template <typename T, typename U>
bool operator<(const observer_ptr<T>& p1, const observer_ptr<U>& p2) {
    // return std::less<V>()(p1.get(), p2.get());  // where V is the composite pointer type of T* and U*
    // return std::less()(p1.get(), p2.get());  // since C++14: deducing argument and return types
    // Looks like older compilers (GCC 7/8) can't handle the above. Let's keep it simple for now:
    return p1.get() < p2.get();
}

template <typename T, typename U>
bool operator>(const observer_ptr<T>& p1, const observer_ptr<U>& p2) {
    return p2 < p1;
}

template <typename T, typename U>
bool operator<=(const observer_ptr<T>& p1, const observer_ptr<U>& p2) {
    return !(p2 < p1);
}

template <typename T, typename U>
bool operator>=(const observer_ptr<T>& p1, const observer_ptr<U>& p2) {
    return !(p1 < p2);
}