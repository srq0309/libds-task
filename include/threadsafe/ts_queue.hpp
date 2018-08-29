#ifndef TS_QUEUE_H__
#define TS_QUEUE_H__

/*!
 * @file	ts_queue.hpp
 *
 * @author	梦丿无情
 * @date	2018-8-29
 *
 * @brief   基于链表和互斥锁的线程安全队列
 */

#include "ts_node.hpp"

#include <mutex>

NAME_DS_START

template<typename _Ty>
class ts_queue
{
public:
    ts_queue()
        :head_(new ts_node<_Ty>), tail_(head_)
    {
    }
    ts_queue(const ts_queue&) = delete;
    ts_queue& operator=(const ts_queue&) = delete;
    ~ts_queue()
    {
        delete head_;
    }

    // 入队
    void push(std::shared_ptr<_Ty> pData)
    {
        auto new_tail = new ts_node<_Ty>;
        std::lock_guard<std::mutex> lk(mu_tail_);
        tail_->data_ = pData;
        tail_->next_ = new_tail;
        tail_ = new_tail;
    }

    // 非等待出队，失败返回空指针
    std::shared_ptr<_Ty> pop()
    {
        ts_node<_Ty> *old_head = nullptr;   // 待出队的旧节点
        {
            std::lock_guard<std::mutex> lk(mu_head_);
            if (head_ == _get_tail()) {
                return nullptr;
            }
            old_head = head_;
            head_ = old_head->next_;
        }
        auto pData = std::move(old_head->data_);
        old_head->next_ = nullptr;
        delete old_head;
        return pData;
    }

    // 判断空
    bool empty()
    {
        std::lock_guard<std::mutex> lk(mu_head_);
        return head_ == _get_tail();
    }

protected:
    inline ts_node<_Ty> *_get_tail()
    {
        std::lock_guard<std::mutex> lk(mu_tail_);
        return tail_;
    }

private:
    ts_node<_Ty> *head_;
    std::mutex mu_head_;

    ts_node<_Ty> *tail_;
    std::mutex mu_tail_;
};

NAME_DS_END // namespace ds

#endif // TS_QUEUE_H__
