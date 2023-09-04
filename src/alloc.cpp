#include <new>
#include <optional>
#include <unistd.h>

using word_t = intptr_t;

struct Block {
    size_t size;
    bool used;
    Block *next;
    word_t data[1];
};

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

    auto allocate(size_type n) -> pointer {
        auto block = request_from_os(n);

        block->size = n;
        block->used = true;

        if (heap)
        return block->data;
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    auto deallocate(pointer p, size_type) -> void {
        delete p;
    }

private:
    auto request_from_os(size_type n) -> std::optional<Block*> {
        auto block = static_cast<Block*>(sbrk(0)); // current heap break
        if (sbrk(alloc_size(n)) == (void*)-1) {
            return std::nullopt;
        }
        return std::optional(block);
    }

    auto alloc_size(size_type n) -> size_type {
        return n + sizeof(Block) - sizeof(std::declval<Block>().data);
    }

    auto align(size_type n) -> size_type {
        return (n + sizeof(intptr_t) - 1) & ~(sizeof(intptr_t) - 1);
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
