#include <iostream>

#include "Queue/QueueImplem.hpp"

int main()
{
    ecspressp::QueueImplem<int> queue;
    queue.Push(2);
    std::cout << "content == " << queue.Pop() << std::endl;
    std::cout << "empty == " << queue.IsEmpty() << std::endl;
    return 0;
}