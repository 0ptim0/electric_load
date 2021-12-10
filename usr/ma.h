#include "buf.h"
#include "modules.h"
#pragma once

/**
 * @brief Moving average filter for many inputs
 */
template <size_t INPUT_NUMBER, size_t SIZE, typename type_t>
class filt_ma {
public:
    filt_ma () = default;

public:
    void set_signal (input signal_num, type_t signal) {
        if (signal_num >= INPUT_NUMBER) {
            return;
        }
        inputs_[signal_num] = signal;
    }

    void update () {
        for (int i = 0; i < INPUT_NUMBER; i++) {
            buf_[i].update(inputs_[i]);
            outputs_[i] = buf_[i].get_sum() / SIZE;
        }
    }

    type_t get_signal (output signal_num) {
        if (signal_num >= OUTPUT_NUMBER) {
            return 0;
        } else {
            return outputs_[signal_num];
        }
    }

private:
    const size_t OUTPUT_NUMBER = INPUT_NUMBER;

    type_t inputs_[INPUT_NUMBER] = {};
    type_t outputs_[INPUT_NUMBER] = {};
    buffer<SIZE, type_t> buf_[INPUT_NUMBER];
};