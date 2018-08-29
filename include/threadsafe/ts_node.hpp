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

#include "../base/ds.h"

NAME_DS_START

template<typename _Ty>
struct ts_node
{
    std::shared_ptr<_Ty> data_;
    ts_node *next_;

    ts_node()
        :data_(nullptr), next_(nullptr)
    {
    }
    ts_node(const std::shared_ptr<_Ty>& data, ts_node *next)
        :data_(data), next_(next)
    {
    }
    ts_node(std::shared_ptr<_Ty>&& data, ts_node *next)
        :data_(data), next_(next)
    {
    }
};

NAME_DS_END

#endif // TS_NODE_H__
