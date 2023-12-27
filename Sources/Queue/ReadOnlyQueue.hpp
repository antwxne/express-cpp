//
// Created by antoine on 22/12/23.
//

#ifndef ECSPRESSP_INPUTQUEUE_HPP
#define ECSPRESSP_INPUTQUEUE_HPP

#include <optional>

namespace ecspressp {

template<typename T>
class ReadOnlyQueue {
public:
    virtual std::optional<T> Pop() = 0;
    virtual bool IsEmpty() const noexcept = 0;
};
} // ecspressp

#endif //ECSPRESSP_INPUTQUEUE_HPP
