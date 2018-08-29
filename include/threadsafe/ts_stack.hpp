#ifndef TS_STACK_H__
#define TS_STACK_H__

/*!
 * @file	ts_stack.hpp
 *
 * @author	梦丿无情
 * @date	2018-8-29
 *
 * @brief	基于链表和互斥锁的线程安全栈
 */

#include "ts_node.hpp"

#include <mutex>

NAME_DS_START

template<typename _Ty>
class ts_stack
{
public:
    ts_stack()
        :head_(nullptr)
    {
    }
    ts_stack(const ts_stack&) = delete;
    ts_stack& operator=(const ts_stack&) = delete;
    ~ts_stack()
    {
        delete head_;
    }

    // 入栈
    void push(std::shared_ptr<_Ty> pData)
    {
        auto new_head = new ts_node<_Ty>(pData);
        
        std::lock_guard<std::mutex> lk(mu_head_);
        new_head->next_ = head_;
        head_ = new_head;
    }

    // 非等待出栈，失败返回空指针
    std::shared_ptr<_Ty> pop()
    {
        ts_node<_Ty> *old_head = nullptr;
        {
            std::lock_guard<std::mutex> lk(mu_head_);
            if (head_ == nullptr) {
                return nullptr;
            }
            old_head = head_;
            head_ = head_->next_;
        }
        auto pData = std::move(old_head->data_);
        old_head->next_ = nullptr;
        delete old_head;
        return pData;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lk(mu_head_);
        return head_ == nullptr;
    }

private:
    ts_node<_Ty> *head_;
    std::mutex mu_head_;
};

NAME_DS_END

#endif // TS_STACK_H__
