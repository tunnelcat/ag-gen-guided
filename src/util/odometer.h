#ifndef UTIL_ODOMETER_HPP
#define UTIL_ODOMETER_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// template<typename T>
// class Odometer_iterator;

template<typename T>
using PermSet = std::vector<std::vector<T>>;

template<typename T>
class Odometer {
    PermSet<T> perms;
    size_t idx_state = 0;
    size_t N,K;

  public:

    // typedef Odometer_iterator<T> iterator;
    // typedef ptrdiff_t difference_type;
    // typedef size_t size_type;
    // typedef T value_type;
    // typedef T* pointer;
    // typedef T& reference;

    Odometer(size_t n_in, size_t k_in) {
        N = n_in;
        K = k_in;

        size_t curr_idx = 0;
        size_t perm_idx = 0;

        std::vector<T> orig_perm(N);
        std::vector<T> &last_perm = orig_perm;

        for (auto i = 0; i < N; i++) {
            orig_perm[i] = 0;
        }

        auto len = length();
        while (perm_idx < len) {
            std::vector<T> curr_perm(N);
            for (auto i = 0; i < N; i++) {
                curr_perm[i] = last_perm[i];
            }

            perms.push_back(curr_perm);

            while (curr_idx < N && curr_perm[curr_idx] >= K - 1) {
                curr_idx++;
            }

            perm_idx++;

            if (curr_idx < N) {
                curr_perm[curr_idx]++;
                for (auto i = 0; i < curr_idx; i++) {
                    curr_perm[i] = 0;
                }
                curr_idx = 0;
                last_perm = curr_perm;
            } else {
                break;
            }
        }
    }

    void print() {
        for (std::vector<T> perm : perms) {
            for (auto num : perm) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    unsigned long length() { return pow(K, N); }

    // std::vector<T> next() { return perms[idx_state++]; }

    // const std::vector<T> &operator[](size_t idx) const { return perms[idx]; }

    // void reset() { idx_state = 0; }

    // size_t perm_length() { return N; }

    PermSet<T> get_all() { return perms; }

    // size_t get_size() { return perms.size(); }
    // std::vector<T> const &GetAt(T i) const {
    //     if (i < perms.size())
    //         return perms[i];
    //     throw std::out_of_range("index out of range");
    // }
};

// template<typename T>
// class Odometer_iterator {
//     Odometer<T> od;
//     size_t index;

//   public:
//     Odometer_iterator(Odometer<T> _od, size_t const i) : od(_od), index(i) {}

//     bool operator!=(Odometer_iterator const &other) const {
//         return index != other.index;
//     }

//     std::vector<T> const &operator*() const { return od.GetAt(index); }

//     Odometer_iterator<T> const &operator++() {
//         ++index;
//         return *this;
//     }
// };

// template<typename T>
// inline Odometer_iterator<T> begin(Odometer<T> od) { return Odometer_iterator<T>(od, 0); }

// template<typename T>
// inline Odometer_iterator<T> end(Odometer<T> od) {
//     return Odometer_iterator<T>(od, od.get_size());
// }

#endif // UTIL_ODOMETER_HPP
