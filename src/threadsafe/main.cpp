#include <iostream>

#include <threadsafe/ts_queue.hpp>
#include <threadsafe/ts_stack.hpp>

using namespace std;

// ts_queue基本功能测试
void test1()
{
    ds::ts_queue<int> q;
    q.push(std::make_shared<int>(1));
    q.push(std::make_shared<int>(2));
    q.push(std::make_shared<int>(3));

    for (int i = 0; i != 4; ++i) {
        auto pData = q.pop();
        if (pData)
            cout << *pData << endl;
    }
    cout << "test1() end.\n" << endl;
}

// ts_stack基本功能测试
void test2()
{
    ds::ts_stack<int> s;
    s.push(std::make_shared<int>(1));
    s.push(std::make_shared<int>(2));
    s.push(std::make_shared<int>(3));

    for (auto i = 0; i != 4; ++i) {
        auto p_data = s.pop();
        if (p_data)
            cout << *p_data << endl;
    }
    cout << "test2() end.\n" << endl;
}

int main(int argc, char *argv[])
{
    test1();
    test2();
    return 0;
}
