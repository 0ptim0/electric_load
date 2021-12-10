#pragma once
#include "modules.h"

/**
 * @brief Sliding buffer for filtering tasks
 * \param SIZE window
 */
template <size_t SIZE, typename type_t>
class buffer {
public:
    buffer () = default;

public:
    // add last element and move to right
    void update (type_t data) {
        sum_ -= buf_[0];
        for(int i = 0; i < SIZE - 1; i++) {
            buf_[i] = buf_[i + 1];
        }
        buf_[SIZE - 1] = data;
        sum_ += buf_[SIZE - 1];
    }

    // add element by index
    void add_elem (type_t data, uint32_t elem) {
        if(elem >= SIZE) {
            return;
        }
        buf_[elem] = data;
    }

    // insertion sort
    void sort () {
        type_t a_;
        int k = 0;
        for(int i = 0; i < SIZE; i++) {
            k = i;
            for(int j = i; j < SIZE; j++) {
                if(buf_[j] < buf_[k]) {
                    k = j;
                }
            }
            a_ = buf_[i];
            buf_[i] = buf_[k];
            buf_[k] = a_;
        }
    }

    // get sample, when 0 is current (Z), SIZE - 1 is oldest (Z^-(SIZE - 1))
    type_t get_sample (uint32_t sample) {
        if(sample > SIZE) {
            return 0;
        }
        return buf_[SIZE - sample - 1];
    }

    // get sum f
    type_t get_sum () {
        return sum_;
    }

private:
    type_t buf_[SIZE] = {};
    type_t sum_ = 0;
};
