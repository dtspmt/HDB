/**
 *  @file       HDBMetaMap.cpp
 */

#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"

#include <string.h>


Int32 HDBMetaMap::createDefault(const Char * name)
{
    memset(this, 0, sizeof(HDBMetaMap));

    if (strlen(name) >= HDB_NAME_LEN) {
        return DBERR_NAME_TOO_LONG;
    }
    strncpy(db_name, name, HDB_NAME_LEN);
    
    enum_group.capacity = HDB_DEFAULT_ENUM_GROUP_NUM;
    enum_item.capacity = HDB_DEFAULT_ENUM_ITEM_NUM;

    bits_group.capacity = HDB_DEFAULT_BITS_GROUP_NUM;
    bits_item.capacity = HDB_DEFAULT_BITS_ITEM_NUM;

    struct_group.capacity = HDB_DEFAULT_STRUCT_GROUP_NUM;
    struct_item.capacity = HDB_DEFAULT_STRUCT_ITEM_NUM;

    table_group.capacity = HDB_DEFAULT_TABLE_NUM;
    field_item.capacity = HDB_DEFAULT_FIELD_NUM;

    relation.capacity = HDB_DEFAULT_RELATION_NUM;
    
    return calcOffset();
}

Int32 HDBMetaMap::calcOffset(void)
{
    UInt32 offset = sizeof(HDBMetaMap);

    enum_group.head_offset = offset;
    enum_group.free_index = 0;
    offset += enum_group.capacity * sizeof(HDBEnumGroupMap);

    enum_item.head_offset = offset;
    enum_item.free_index = 0;
    offset += enum_item.capacity * sizeof(HDBEnumItemMap);

    bits_group.head_offset = offset;
    bits_group.free_index = 0;
    offset += bits_group.capacity * sizeof(HDBBitsGroupMap);

    bits_item.head_offset = offset;
    bits_item.free_index = 0;
    offset += bits_item.capacity * sizeof(HDBBitsItemMap);

    struct_group.head_offset = offset;
    struct_group.free_index = 0;
    offset += struct_group.capacity * sizeof(HDBStructGroupMap);

    struct_item.head_offset = offset;
    struct_item.free_index = 0;
    offset += struct_item.capacity * sizeof(HDBStructItemMap);

    table_group.head_offset = offset;
    table_group.free_index = 0;
    offset += table_group.capacity * sizeof(HDBTableGroupMap);

    field_item.head_offset = offset;
    field_item.free_index = 0;
    offset += field_item.capacity * sizeof(HDBFieldItemMap);

    relation.head_offset = offset;
    relation.free_index = 0;
    offset += relation.capacity * sizeof(HDBRelationMap);

    this->meta_size = offset;

    return offset;
}