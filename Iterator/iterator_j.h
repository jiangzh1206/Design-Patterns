#include <iostream>
#include <initializer_list>

template<typename T, size_t N>
struct JArray
{
    T array_[N];

#if 0
    JArray(std::initializer_list<T> il)
    {
        // static_assert(il.size() == N); // error il不是常数
        size_t i = 0;
        for (auto& v : il) {
            array_[i] = v;
            ++i;
        }
    }
#endif // 0


    template<size_t M>
    JArray(const T(&list)[M])
    {
        static_assert(N == M, "size is wrong.");

        for (int i = 0; i < N; ++i) {
            array_[i] = list[i];
        }
    }

    struct Iterator
    {
        T* p_;

        Iterator(T* p) : p_(p) {}

        bool operator !=(const Iterator& other)
        {
            return p_ != other.p_;
        }

        Iterator& operator++ ()
        {
            ++p_;
            return *this;
        }

        T& operator*()
        {
            return *p_;
        }
    };

    Iterator begin()
    {
        return Iterator(array_);
    }

    Iterator end()
    {
        return Iterator(array_ + N);
    }
};

int test()
{
    JArray<char, 5> arr({'a', 'b', 'c', 'd', 'e'});

    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "-------------line----------------" << std::endl;

    for (auto& v : arr) {
        std::cout << v << std::endl;
        v = 100;
    }
    std::cout << "-------------line----------------" << std::endl;
    for (auto& v : arr) {
        std::cout << v << std::endl;
    }
}