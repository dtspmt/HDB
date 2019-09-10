/**
 *  @file       HDBMetaEntity.cpp
 */

#include "HDBMetaImpl.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"
#include "HDB/HDBOid.h"
#include "HDB/HDBRelParent.h"
#include "HDB/HDBRelChild.h"
#include "HDB/HDBRelRefer.h"

Int32 HDBMetaImpl::allocEntity(void)
{
    UInt16 i = 0;

    HDBTableGroupMap * table_header = getTableGroupMapHead();
    if (NULL == table_header) {
        return DBERR_DB_NOT_MAPPED;
    }

    //实体文件大小，兼做每个table实体的偏移
    UInt32 db_file_size = 0;

    //遍历所有table
    for (i = 0; i < m_p_meta_map->table_group.capacity; i++) {
        //每个表的大小 = 表中单个对象的尺寸 * 对象容量
        HDBTableGroupMap * table = table_header + i;
        Int32 table_size = calcTableSize(table);
        if (table_size < 0) {
            return table_size;
        }
        table->object_offset = db_file_size;
        db_file_size += table_size;
    }

    m_p_meta_map->db_size = db_file_size;
    return db_file_size;
}

Int32 HDBMetaImpl::calcTableSize(HDBTableGroupMap * table)
{
    UInt32 object_size = 0;
    UInt32 table_size = 0;
    UInt16 i = 0;

    HDBFieldItemMap * field_head = getFieldItemMapHead();


    return table_size;
}
