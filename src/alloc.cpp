#include <new>

using word_t = intptr_t;

inline size_t align(size_t n) {
  return (n + sizeof(intptr_t) - 1) & ~(sizeof(intptr_t) - 1);
}

template <typename T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Allocator() = default;
    template <typename U>
    Allocator(const Allocator<U>&) {}

    pointer allocate(size_type n) {
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type) {
        delete p;
    }
};

template <typename T, typename U>
constexpr bool operator==(const Allocator<T>&, const Allocator<U>&) {
    return true;
}

template <typename T, typename U>
constexpr bool operator!=(const Allocator<T>&, const Allocator<U>&) {
    return false;
}
