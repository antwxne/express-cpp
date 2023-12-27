//
// Created by antoine on 22/12/23.
//

#ifndef ECSPRESSP_QUEUEIMPLEM_HPP
#define ECSPRESSP_QUEUEIMPLEM_HPP

#include <queue>
#include <stdexcept>
#include <mutex>
#include <optional>

#include "ReadOnlyQueue.hpp"
#include "WriteOnlyQueue.hpp"

namespace ecspressp {

template<typename T>
class QueueImplem : public ReadOnlyQueue<T>, public WriteOnlyQueue<T> {
public:
    QueueImplem() = default;
    QueueImplem(std::initializer_list<T> l);
    std::optional<T> Pop();
    void Push(T &&elem);
    bool IsEmpty() const noexcept;
private:
    std::queue<T> _data;
    std::mutex _mutex;
};

template<typename T>
QueueImplem<T>::QueueImplem(std::initializer_list<T> l): _data(l), _mutex()
{
}

template<typename T>
bool QueueImplem<T>::IsEmpty() const noexcept
{
    return _data.empty();
}

template<typename T>
void QueueImplem<T>::Push(T &&elem)
{
    _mutex.lock();
    _data.push(elem);
    _mutex.unlock();
}

template<typename T>
std::optional<T> QueueImplem<T>::Pop()
{
    _mutex.lock();
    if (_data.size() == 0) {
        _mutex.unlock();
        return std::nullopt;
    }
    T front = _data.front();
    _data.pop();
    _mutex.unlock();
    return std::move(front);
}
}
#endif //ECSPRESSP_QUEUEIMPLEM_HPP
