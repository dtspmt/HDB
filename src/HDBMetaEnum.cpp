
/**
*  @file       HDBMetaEnum.cpp
*/

#include "HDBMetaImpl.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"



#include <stdio.h>
#include <string.h>

HDBEnumGroupMap * HDBMetaImpl::getEnumGroupMapHead(void) const
{
    if (NULL == m_p_meta_map) {
        return NULL;
    }

    HDBEnumGroupMap * group_head = (HDBEnumGroupMap *)((UInt8 *)m_p_meta_address + m_p_meta_map->enum_group.head_offset);
    return group_head;
}

HDBEnumItemMap * HDBMetaImpl::getEnumItemMapHead(void) const
{
    if (NULL == m_p_meta_map) {
        return NULL;
    }

    HDBEnumItemMap * item_head = (HDBEnumItemMap *)((UInt8 *)m_p_meta_address + m_p_meta_map->enum_item.head_offset);
    return item_head;
}

Int32 HDBMetaImpl::getEnumGroupMapIndex(HDBEnumGroupMap * group) const
{
    HDBEnumGroupMap * group_head = getEnumGroupMapHead();
    if (NULL == group_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    return (UInt16)(group - group_head);
}

Int32 HDBMetaImpl::getEnumItemMapIndex(HDBEnumItemMap * item) const
{
    HDBEnumItemMap * item_head = getEnumItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    return (UInt16)(item - item_head);
}

Int32 HDBMetaImpl::findEnumGroup(const Char * group_name) const
{
    HDBEnumGroupMap * group_head = getEnumGroupMapHead();
    if (NULL == group_head) {
        return DBERR_DB_NOT_MAPPED;
    }
        
    for (UInt16 i = 0; i < m_p_meta_map->bits_group.capacity; i++) {
        if (0 == strncmp(group_head[i].name, group_name, HDB_NAME_LEN)) {
            return i;
        }
    }
    return DBERR_DB_ENUM_GROUP_NOT_EXISTS;
}

HDBEnumGroupMap * HDBMetaImpl::getEnumGroup(UInt16 index) const
{
    HDBEnumGroupMap * group_head = getEnumGroupMapHead();
    if (NULL == group_head) {
        return NULL;
    }

    if (index >= m_p_meta_map->enum_group.capacity) {
        return NULL;
    }

    return group_head + index;
}

Int32 HDBMetaImpl::addEnumGroup(const Char * group_name)
{
    if (m_p_meta_map->enum_group.used_size >= m_p_meta_map->enum_group.capacity) {
        return DBERR_DB_ENUM_GROUP_TOO_MORE;
    }

    if (strlen(group_name) >= HDB_NAME_LEN) {
        return DBERR_NAME_TOO_LONG;
    }

    Int32 index = findEnumGroup(group_name);
    if (index >= 0) {
        return DBERR_DB_ENUM_GROUP_EXISTS;
    }

    Int32 new_index = m_p_meta_map->enum_group.free_index;
    HDBEnumGroupMap * group = getEnumGroup(new_index);
    if (NULL == group) {
        return DBERR_DB_ENUM_GROUP_INVALID_FREE;
    }

    if (!HDBMetaMap::isRecordEmpty(group)) {
        return DBERR_DB_ENUM_GROUP_NOT_EMPTY;
    }

    strncpy(group->name, group_name, HDB_NAME_LEN);
    group->item_head = -1;
    group->item_num = 0;
    m_p_meta_map->enum_group.used_size++;

    //获取新的空闲下标
    HDBEnumGroupMap * group_head = getEnumGroupMapHead();
    m_p_meta_map->enum_group.free_index = getNextFreeIndex(group_head, m_p_meta_map->enum_group.capacity, new_index);    

    return new_index;
}

Int32 HDBMetaImpl::delEnumGroup(const Char * group_name)
{
    Int32 group_index = findEnumGroup(group_name);
    if (group_index < 0) {
        return DBERR_DB_ENUM_GROUP_NOT_EXISTS;
    }
    return delEnumGroup(group_index);
}

Int32 HDBMetaImpl::delEnumGroup(UInt16 index)
{
    HDBEnumGroupMap * group = getEnumGroup(index);
    if (NULL == group) {
        return DBERR_DB_ENUM_GROUP_NOT_EXISTS;
    }

    if (HDBMetaMap::isRecordEmpty(group)) {
        return DBERR_DB_ENUM_GROUP_EMPTY;
    }

    //倒序删除子项
    for (Int32 i = group->item_num - 1; i >= 0; i--) {
        Int32 ret = delEnumItem(group, i);
        if (ret < 0) {
            return ret;
        }
    }
    //删除本组
    memset(group, 0, sizeof(HDBEnumGroupMap));

    m_p_meta_map->enum_group.used_size--;
    return index;
}

Int32 HDBMetaImpl::findEnumItem(const Char * group_name, const Char * item_name) const
{
    Int32 group_index = findEnumGroup(group_name);
    return findEnumItem(group_index, item_name);
}

Int32 HDBMetaImpl::findEnumItem(UInt16 group_index, const Char * item_name) const
{
    HDBEnumGroupMap * group = getEnumGroup(group_index);
    return findEnumItem(group, item_name);
}

Int32 HDBMetaImpl::findEnumItem(HDBEnumGroupMap * group, const Char * item_name) const
{
    if (NULL == group) {
        return DBERR_DB_ENUM_GROUP_NOT_EXISTS;
    }

    HDBEnumItemMap * item_head = getEnumItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (group->item_head < 0 || group->item_head >= m_p_meta_map->enum_group.capacity) {
        return DBERR_DB_ENUM_GROUP_INVALID_ITEM_INDEX;
    }

    Int32 index = group->item_head;
    UInt16 i = 0;
    while ((index >= 0) && (i < group->item_num)) {
        if (0 == strcmp(item_head[index].name, item_name)) {
            return index;
        }
        i++;
        index = item_head[index].item_next;
    }
    return DBERR_DB_ENUM_ITEM_NOT_EXISTS;
}

HDBEnumItemMap * HDBMetaImpl::getEnumItem(UInt16 global_index) const
{
    HDBEnumItemMap * item_head = getEnumItemMapHead();
    if (NULL == item_head) {
        return NULL;
    }

    if (global_index >= m_p_meta_map->enum_group.capacity) {
        return NULL;
    }

    return item_head + global_index;
}

HDBEnumItemMap * HDBMetaImpl::getEnumItem(UInt16 group_index, UInt16 item_index) const
{
    HDBEnumGroupMap * group = getEnumGroup(group_index);
    if (NULL == group) {
        return NULL;
    }

    HDBEnumItemMap * item_head = getEnumItemMapHead();
    if (NULL == item_head) {
        return NULL;
    }

    Int32 index = group->item_head;
    UInt16 i = 0;
    while ((index >= 0) && (i < item_index) && (i < group->item_num)) {
        index = item_head[index].item_next;
        i++;
    }

    if ((index < 0) || (i >= group->item_num)) {
        return NULL;
    }

    return item_head + index;
}

Int32 HDBMetaImpl::addEnumItem(HDBEnumGroupMap * group, const HDBEnumItemMap * item)
{
    if (NULL == m_p_meta_map) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (NULL == item) {
        return DBERR_INVALID_POINTER;
    }

    if (m_p_meta_map->enum_item.used_size >= m_p_meta_map->enum_item.capacity) {
        return DBERR_DB_ENUM_ITEM_TOO_MORE;
    }

    HDBEnumItemMap * item_head = getEnumItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    Int32 group_index = getEnumGroupMapIndex(group);
    if (group_index < 0 || group_index >= m_p_meta_map->enum_group.capacity) {
        return DBERR_DB_ENUM_GROUP_NOT_EXISTS;
    }

    Int32 item_index = findEnumItem(group, item->name);
    if (item_index >= 0) {
        return DBERR_DB_ENUM_ITEM_EXISTS;
    }

    //获取空闲项序号
    item_index = m_p_meta_map->enum_item.free_index;
    HDBEnumItemMap * target_item = item_head + item_index;
    if (!HDBMetaMap::isRecordEmpty(target_item)) {
        return DBERR_DB_ENUM_ITEM_NOT_EMPRY;
    }

    memcpy(target_item, item, sizeof(HDBEnumItemMap));
    target_item->group_index = group_index;
    target_item->item_next = -1;

    //插入到链表
    if (group->item_head < 0) {
        group->item_head = item_index;
        target_item->item_prev = -1;
    }
    else {
        Int32 tail_index = group->item_head;
        while (item_head[tail_index].item_next >= 0) {
            tail_index = item_head[tail_index].item_next;
        }
        item_head[tail_index].item_next = item_index;
        target_item->item_prev = tail_index;
    }

    m_p_meta_map->enum_item.used_size++;
    group->item_num++;
    
    //寻找下一个空闲序号
    m_p_meta_map->enum_item.free_index = getNextFreeIndex(item_head, m_p_meta_map->enum_item.capacity, item_index);

    return item_index;
}

Int32 HDBMetaImpl::delEnumItem(HDBEnumGroupMap * group, const Char * item_name)
{
    Int32 item_index = findEnumItem(group, item_name);
    if (item_index < 0) {
        return DBERR_DB_ENUM_ITEM_NOT_EXISTS;
    }

    return delEnumItem(group, item_index);
}

Int32 HDBMetaImpl::delEnumItem(HDBEnumGroupMap * group, UInt16 item_index)
{
    if (NULL == m_p_meta_map) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (NULL == group) {
        return DBERR_INVALID_POINTER;
    }

    HDBEnumItemMap * item_head = getEnumItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    Int32 group_index = getEnumGroupMapIndex(group);
    if (group_index < 0 || group_index >= m_p_meta_map->enum_group.capacity) {
        return DBERR_DB_ENUM_GROUP_NOT_EXISTS;
    }

    HDBEnumItemMap * item = getEnumItem(group_index, item_index);
    if (NULL == item) {
        return DBERR_DB_ENUM_GROUP_INVALID_ITEM_INDEX;
    }

    if (HDBMetaMap::isRecordEmpty(item)) {
        return DBERR_DB_ENUM_ITEM_EMPTY;
    }
    
    Int32 global_index = getEnumItemMapIndex(item);
    if (global_index < 0) {
        return global_index;
    }

    //如果有下一个项
    if (item->item_next >= 0) {
        item_head[item->item_next].item_prev = item->item_prev;
    }

    //如果是队首
    if (item->item_prev == -1) {
        group->item_head = item->item_next;
    }
    else {
        HDBEnumItemMap * item_prev = item_head + item->item_prev;
        item_prev->item_next = item->item_next;
    }

    group->item_num--;
    m_p_meta_map->enum_item.used_size--;

    memset(item, 0, sizeof(HDBEnumItemMap));
    return global_index;
}

