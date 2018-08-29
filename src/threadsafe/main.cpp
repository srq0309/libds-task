#include <threadsafe/ts_queue.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    ds::ts_queue<int> q;
    q.push(std::make_shared<int>(1));
    q.push(std::make_shared<int>(2));
    q.push(std::make_shared<int>(3));
    
    for (int i = 0; i != 4; ++i) {
        auto pData = q.pop();
        if (pData)
            std::cout << *pData << std::endl;
    }
    
    return 0;
}