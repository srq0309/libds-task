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

template<typename _Ty>
class ts_stack
{
public:
    /*！
     * @brief	初始化
     */
    ts_stack()
        :head_(nullptr)
    {
    }

    /*！
     * @brief	禁止拷贝构造
     */
    ts_stack(const ts_stack&) = delete;

    /*！
     * @brief	禁止赋值运算
     */
    ts_stack& operator=(const ts_stack&) = delete;

    /*！
     * @brief	析构整个链表
     */
    ~ts_stack()
    {
        delete head_;
    }

    /*！
     * @brief	入栈
     * @param	智能指针包裹的数据
     */
    void push(std::shared_ptr<_Ty> pData)
    {
        auto new_head = new ts_node<_Ty>(pData);

        std::lock_guard<std::mutex> lk(mu_head_);
        new_head->next_ = head_;
        head_ = new_head;
    }

    /*！
     * @brief	非等待出栈
     * @return	成功返回智能指针包裹的数据，失败返回空指针
     */
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

    /*！
     * @brief	判断空
     * @return	队列为空返回true，否则返回false
     */
    bool empty()
    {
        std::lock_guard<std::mutex> lk(mu_head_);
        return head_ == nullptr;
    }

private:
    ts_node<_Ty> *head_;
    std::mutex mu_head_;
};

#endif // TS_STACK_H__
