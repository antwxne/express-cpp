//
// Created by antoine on 22/12/23.
//

#ifndef ECSPRESSP_WRITEONLYQUEUE_HPP
#define ECSPRESSP_WRITEONLYQUEUE_HPP

namespace ecspressp {

template<typename T>
class WriteOnlyQueue {
public:
    virtual void Push(T &&elem) = 0;
};
} // ecspressp

#endif //ECSPRESSP_WRITEONLYQUEUE_HPP
