#ifndef TS_NODE_H__
#define TS_NODE_H__

/*!
 * @file	ts_node.hpp
 *
 * @author	梦丿无情
 * @date	2018-8-29
 *
 * @brief	公共链表节点
 */

#include <memory>

template<typename _Ty>
struct ts_node
{
    std::shared_ptr<_Ty> data_;
    ts_node *next_;

    ts_node(const std::shared_ptr<_Ty>& data = nullptr, ts_node *next = nullptr)
        :data_(data), next_(next)
    {
    }
    ~ts_node()
    {
        data_.reset();
        delete next_;
    }
};

#endif // TS_NODE_H__
