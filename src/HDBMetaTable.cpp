
/**
*  @file       HDBMetaTable.cpp
*/

#include "HDBMetaImpl.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"



#include <stdio.h>
#include <string.h>

HDBTableGroupMap * HDBMetaImpl::getTableGroupMapHead(void) const
{
    if (NULL == m_p_meta_map) {
        return NULL;
    }

    HDBTableGroupMap * group_head = (HDBTableGroupMap *)((UInt8 *)m_p_meta_address + m_p_meta_map->table_group.head_offset);
    return group_head;
}

HDBFieldItemMap * HDBMetaImpl::getFieldItemMapHead(void) const
{
    if (NULL == m_p_meta_map) {
        return NULL;
    }

    HDBFieldItemMap * item_head = (HDBFieldItemMap *)((UInt8 *)m_p_meta_address + m_p_meta_map->field_item.head_offset);
    return item_head;
}

HDBRelationMap * HDBMetaImpl::getRelationMapHead(void) const
{
    if (NULL == m_p_meta_map) {
        return NULL;
    }

    HDBRelationMap * head = (HDBRelationMap *)((UInt8 *)m_p_meta_address + m_p_meta_map->relation.head_offset);
    return head;
}


Int32 HDBMetaImpl::getTableGroupMapIndex(HDBTableGroupMap * group) const
{
    HDBTableGroupMap * group_head = getTableGroupMapHead();
    if (NULL == group_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    return (UInt16)(group - group_head);
}

Int32 HDBMetaImpl::getFieldItemMapIndex(HDBFieldItemMap * item) const
{
    HDBFieldItemMap * item_head = getFieldItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    return (UInt16)(item - item_head);
}

Int32 HDBMetaImpl::findTableGroup(const Char * group_name) const
{
    HDBTableGroupMap * group_head = getTableGroupMapHead();
    if (NULL == group_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    for (UInt16 i = 0; i < m_p_meta_map->table_group.capacity; i++) {
        if (0 == strncmp(group_head[i].name, group_name, HDB_NAME_LEN)) {
            return i;
        }
    }
    return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
}

HDBTableGroupMap * HDBMetaImpl::getTableGroup(UInt16 index) const
{
    HDBTableGroupMap * group_head = getTableGroupMapHead();
    if (NULL == group_head) {
        return NULL;
    }

    if (index >= m_p_meta_map->table_group.capacity) {
        return NULL;
    }

    return group_head + index;
}

Int32 HDBMetaImpl::addTableGroup(const Char * group_name)
{
    if (m_p_meta_map->table_group.used_size >= m_p_meta_map->table_group.capacity) {
        return DBERR_DB_TABLE_GROUP_TOO_MORE;
    }

    if (strlen(group_name) >= HDB_NAME_LEN) {
        return DBERR_NAME_TOO_LONG;
    }

    Int32 index = findTableGroup(group_name);
    if (index >= 0) {
        return DBERR_DB_TABLE_GROUP_EXISTS;
    }

    Int32 new_index = m_p_meta_map->table_group.free_index;
    HDBTableGroupMap * group = getTableGroup(new_index);
    if (NULL == group) {
        return DBERR_DB_TABLE_GROUP_INVALID_FREE;
    }

    if (!HDBMetaMap::isRecordEmpty(group)) {
        return DBERR_DB_TABLE_GROUP_NOT_EMPTY;
    }

    strncpy(group->name, group_name, HDB_NAME_LEN);
    group->item_head = -1;
    group->item_num = 0;

    group->object_offset = 0;
    group->object_size = 0;
    group->object_capacity = 0;
    group->object_used_num = 0;
    group->object_free_index = 0;
    
    m_p_meta_map->table_group.used_size++;

    //获取新的空闲下标
    HDBTableGroupMap * group_head = getTableGroupMapHead();
    m_p_meta_map->table_group.free_index = getNextFreeIndex(group_head, m_p_meta_map->table_group.capacity, new_index);

    return new_index;
}

Int32 HDBMetaImpl::delTableGroup(const Char * group_name)
{
    Int32 group_index = findTableGroup(group_name);
    if (group_index < 0) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }
    return delTableGroup(group_index);
}

Int32 HDBMetaImpl::delTableGroup(UInt16 index)
{
    HDBTableGroupMap * group = getTableGroup(index);
    if (NULL == group) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    if (0 == group->name[0]) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    //倒序删除子项
    for (Int32 i = group->item_num - 1; i >= 0; i--) {
        Int32 ret = delFieldItem(group, i);
        if (ret < 0) {
            return ret;
        }
    }
    //删除本组
    memset(group, 0, sizeof(HDBTableGroupMap));

    m_p_meta_map->table_group.used_size--;
    return index;
}

Int32 HDBMetaImpl::findFieldItem(const Char * group_name, const Char * item_name) const
{
    Int32 group_index = findTableGroup(group_name);
    return findFieldItem(group_index, item_name);
}

Int32 HDBMetaImpl::findFieldItem(UInt16 group_index, const Char * item_name) const
{
    HDBTableGroupMap * group = getTableGroup(group_index);
    return findFieldItem(group, item_name);
}

Int32 HDBMetaImpl::findFieldItem(HDBTableGroupMap * group, const Char * item_name) const
{
    if (NULL == group) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    HDBFieldItemMap * item_head = getFieldItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (group->item_head < 0 || group->item_head >= m_p_meta_map->field_item.capacity) {
        return DBERR_DB_TABLE_GROUP_INVALID_ITEM_INDEX;
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
    return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
}

HDBFieldItemMap * HDBMetaImpl::getFieldItem(UInt16 global_index) const
{
    HDBFieldItemMap * item_head = getFieldItemMapHead();
    if (NULL == item_head) {
        return NULL;
    }

    if (global_index >= m_p_meta_map->field_item.capacity) {
        return NULL;
    }

    return item_head + global_index;
}

HDBFieldItemMap * HDBMetaImpl::getFieldItem(UInt16 group_index, UInt16 item_index) const
{
    HDBTableGroupMap * group = getTableGroup(group_index);
    if (NULL == group) {
        return NULL;
    }

    HDBFieldItemMap * item_head = getFieldItemMapHead();
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

Int32 HDBMetaImpl::addFieldItem(HDBTableGroupMap * group, const HDBFieldItemMap * item)
{
    if (NULL == m_p_meta_map) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (NULL == item) {
        return DBERR_INVALID_POINTER;
    }

    if (m_p_meta_map->field_item.used_size >= m_p_meta_map->field_item.capacity) {
        return DBERR_DB_FIELD_ITEM_TOO_MORE;
    }

    HDBFieldItemMap * item_head = getFieldItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    Int32 group_index = getTableGroupMapIndex(group);
    if (group_index < 0 || group_index >= m_p_meta_map->table_group.capacity) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    Int32 item_index = findFieldItem(group, item->name);
    if (item_index >= 0) {
        return DBERR_DB_FIELD_ITEM_EXISTS;
    }

    //获取空闲项序号
    item_index = m_p_meta_map->field_item.free_index;
    HDBFieldItemMap * target_field = item_head + item_index;
    if (!HDBMetaMap::isRecordEmpty(target_field)) {
        return DBERR_DB_FIELD_ITEM_NOT_EMPTY;
    }

    memcpy(target_field, item, sizeof(HDBFieldItemMap));
    target_field->item_next = -1;
    target_field->group_index = group_index;
        
    //插入到链表
    if (group->item_head < 0) {
        group->item_head = item_index;
        target_field->item_prev = -1;
    }
    else {
        Int32 tail_index = group->item_head;
        while (item_head[tail_index].item_next >= 0) {
            tail_index = item_head[tail_index].item_next;
        }
        item_head[tail_index].item_next = item_index;
        target_field->item_prev = tail_index;
    }

    m_p_meta_map->field_item.used_size++;
    group->item_num++;

    //寻找下一个空闲序号
    m_p_meta_map->field_item.free_index = getNextFreeIndex(item_head, m_p_meta_map->field_item.capacity, item_index);

    return item_index;
}

Int32 HDBMetaImpl::delFieldItem(HDBTableGroupMap * group, const Char * item_name)
{
    Int32 item_index = findFieldItem(group, item_name);
    if (item_index < 0) {
        return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
    }

    return delFieldItem(group, item_index);
}

Int32 HDBMetaImpl::delFieldItem(HDBTableGroupMap * group, UInt16 item_index)
{
    if (NULL == m_p_meta_map) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (NULL == group) {
        return DBERR_INVALID_POINTER;
    }

    HDBFieldItemMap * item_head = getFieldItemMapHead();
    if (NULL == item_head) {
        return DBERR_DB_NOT_MAPPED;
    }

    Int32 group_index = getTableGroupMapIndex(group);
    if (group_index < 0 || group_index >= m_p_meta_map->table_group.capacity) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    HDBFieldItemMap * item = getFieldItem(group_index, item_index);
    if (NULL == item) {
        return DBERR_DB_TABLE_GROUP_INVALID_ITEM_INDEX;
    }

    if (HDBMetaMap::isRecordEmpty(item)) {
        return DBERR_DB_FIELD_ITEM_EMPTY;
    }

    Int32 global_index = getFieldItemMapIndex(item);
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
        HDBFieldItemMap * item_prev = item_head + item->item_prev;
        item_prev->item_next = item->item_next;
    }

    group->item_num--;
    m_p_meta_map->field_item.used_size--;

    memset(item, 0, sizeof(HDBFieldItemMap));
    return global_index;
}

Int32 HDBMetaImpl::addRelContain(const Char * parent_table_name[HDB_NAME_LEN],
    UInt16 parent_table_num,
    const Char * child_table_name,
    const Char * parent_field_name,
    const Char * child_field_name,
    Bool symbiotic)
{
    //多父时，必须是共生
    if ((parent_table_num > 1) && (!symbiotic)) {
        return DBERR_DB_RELATION_MULTI_PARENT_NOT_SYMBIOTIC;
    }

    if ((strlen(child_field_name) >= HDB_NAME_LEN) || (strlen(parent_field_name) >= HDB_NAME_LEN)) {
        return DBERR_NAME_TOO_LONG;
    }

    Int32 child_table_index = findTableGroup(child_table_name);
    HDBTableGroupMap * child_table = getTableGroup(child_table_index);
    if (NULL == child_table) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }
    
    HDBFieldItemMap child_field_item;
    strncpy(child_field_item.name, child_field_name, HDB_NAME_LEN);
    child_field_item.type = HDT_CHILD;
    
    Int32 child_field_index = addFieldItem(child_table, &child_field_item);
    HDBFieldItemMap * child_field = getFieldItem(child_field_index);
    if (NULL == child_field) {
        return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
    }

    Int32 success_num = 0;
    HDBFieldItemMap * prev_parent_field = NULL;
    for (UInt16 i = 0; i < parent_table_num; i++) {
        Int32 parent_table_index = findTableGroup(parent_table_name[i]);
        HDBTableGroupMap * parent_table = getTableGroup(parent_table_index);
        if (NULL == parent_table) {
            continue;
        }

        HDBFieldItemMap parent_field_item;
        strncpy(parent_field_item.name, parent_field_name, HDB_NAME_LEN);
        parent_field_item.type = HDT_PARENT;

        Int32 parent_field_index = addFieldItem(parent_table, &parent_field_item);
        HDBFieldItemMap * parent_field = getFieldItem(parent_field_index);
        if (NULL == parent_field) {
            continue;
        }

        HDBRelationMap relation_map;
        relation_map.symbiotic = symbiotic;
        relation_map.parent_table = parent_table_index;
        relation_map.parent_field = parent_field_index;
        relation_map.child_table = child_table_index;
        relation_map.child_field = child_field_index;
        relation_map.prev = -1;
        relation_map.next = -1;
        
        Int32 relation_index = addRelation(&relation_map);
        if (relation_index < 0) {
            continue;
        }

        parent_field->sub_type = relation_index;
        //第一个需要将子域的sub_type_index指过去
        if (0 == i) {
            child_field->sub_type = relation_index;
            prev_parent_field = parent_field;
        }
        else {
            HDBRelationMap * prev_relation = getRelation(prev_parent_field->sub_type);
            prev_relation->next = relation_index;
            HDBRelationMap * current_relation = getRelation(relation_index);
            current_relation->prev = prev_parent_field->sub_type;
        }        

        success_num++;
    }
    return success_num;
}

Int32 HDBMetaImpl::delRelContain(const Char * parent_table_name[HDB_NAME_LEN],
    UInt16 parent_table_num,
    const Char * child_table_name,
    const Char * parent_field_name,
    const Char * child_field_name)
{
    //删除子表的域
    Int32 child_table_index = findTableGroup(child_table_name);
    HDBTableGroupMap * child_table = getTableGroup(child_table_index);
    if (NULL == child_table) {
        return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
    }

    Int32 ret = delFieldItem(child_table, child_field_name);
    if (ret < 0) {
        return ret;
    }

    //删除父表的域以及表域关系
    Int32 success_num = 0;
    UInt16 i = 0;
    for (i = 0; i < parent_table_num; i++) {
        Int32 parent_table_index = findTableGroup(parent_table_name[i]);
        HDBTableGroupMap * parent_table = getTableGroup(parent_table_index);
        if (NULL == parent_table) {
            return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
        }

        Int32 parent_field_index = findFieldItem(parent_table, parent_field_name);
        HDBFieldItemMap * parent_field = getFieldItem(parent_field_index);
        if (NULL == parent_field) {
            return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
        }

        ret = delRelation(parent_field->sub_type);
        if (ret < 0) {
            continue;
        }
        
        ret = delFieldItem(parent_table, parent_field_name);
        if (ret < 0) {
            continue;
        }

        success_num++;
    }
    return success_num;
}

Int32 HDBMetaImpl::addRelRefer(const Char * parent_table_name,
    const Char * child_table_name,
    const Char * parent_field_name)
{
    Int32 parent_table_index = findTableGroup(parent_table_name);
    HDBTableGroupMap * parent_table = getTableGroup(parent_table_index);
    if (NULL == parent_table) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    Int32 child_table_index = findTableGroup(child_table_name);
    HDBTableGroupMap * child_table = getTableGroup(child_table_index);
    if (NULL == child_table) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    HDBFieldItemMap parent_field_item;
    strncpy(parent_field_item.name, parent_field_name, HDB_NAME_LEN);
    parent_field_item.type = HDT_REFER;

    Int32 parent_field_index = addFieldItem(parent_table, &parent_field_item);
    if (parent_field_index < 0) {
        return parent_field_index;
    }

    HDBRelationMap relation;
    relation.parent_table = parent_table_index;
    relation.parent_field = parent_field_index;
    Int32 relation_index = addRelation(&relation);

    HDBFieldItemMap * parent_field = getFieldItem(parent_field_index);
    if (NULL == parent_field) {
        return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
    }

    parent_field->sub_type = relation_index;

    return DB_SUCCESS;
}

Int32 HDBMetaImpl::delRelRefer(const Char * parent_table_name,
    const Char * child_table_name,
    const Char * parent_field_name)
{
    Int32 parent_table_index = findTableGroup(parent_table_name);
    HDBTableGroupMap * parent_table = getTableGroup(parent_table_index);
    if (NULL == parent_table) {
        return DBERR_DB_TABLE_GROUP_NOT_EXISTS;
    }

    Int32 parent_field_index = findFieldItem(parent_table, parent_field_name);
    HDBFieldItemMap * parent_field = getFieldItem(parent_field_index);
    if (NULL == parent_field) {
        return DBERR_DB_FIELD_ITEM_NOT_EXISTS;
    }

    Int32 ret = delRelation(parent_field->sub_type);
    if (ret < 0) {
        return ret;
    }

    return delFieldItem(parent_table, parent_field_name);
}

Int32 HDBMetaImpl::addRelation(const HDBRelationMap * relation)
{
    if (NULL == m_p_meta_map) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (NULL == relation) {
        return DBERR_INVALID_POINTER;
    }

    HDBRelationMap * head = getRelationMapHead();
    if (NULL == head) {
        return DBERR_DB_NOT_MAPPED;
    }

    if (m_p_meta_map->relation.used_size >= m_p_meta_map->relation.capacity) {
        return DBERR_DB_RELATION_TOO_MORE;
    }

    Int32 relation_index = m_p_meta_map->relation.free_index;
    HDBRelationMap * new_relation = head + relation_index;
    if (!HDBMetaMap::isRecordEmpty(new_relation)) {
        return DBERR_DB_RELATION_NOT_EMPTY;
    }

    memcpy(new_relation, relation, sizeof(HDBRelationMap));
    new_relation->used = true;

    m_p_meta_map->relation.used_size++;
    m_p_meta_map->relation.free_index = getNextFreeIndex(head, m_p_meta_map->relation.capacity, relation_index);

    return relation_index;
}

HDBRelationMap * HDBMetaImpl::getRelation(UInt16 index) const
{
    if (NULL == m_p_meta_map) {
        return NULL;
    }

    if (index >= m_p_meta_map->relation.capacity) {
        return NULL;
    }

    HDBRelationMap * head = getRelationMapHead();
    if (NULL == head) {
        return NULL;
    }

    return head + index;
}

Int32 HDBMetaImpl::delRelation(UInt16 index) const
{
    HDBRelationMap * relation = getRelation(index);
    if (NULL == relation) {
        return DBERR_DB_RELATION_INVALID_INDEX;
    }

    if (HDBMetaMap::isRecordEmpty(relation)) {
        return DBERR_DB_RELATION_EMPTY;
    }

    memset(relation, 0, sizeof(HDBRelationMap));
    m_p_meta_map->relation.used_size--;

    return DB_SUCCESS;
}