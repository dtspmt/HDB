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

    //ʵ���ļ���С������ÿ��tableʵ���ƫ��
    UInt32 db_file_size = 0;

    //��������table
    for (i = 0; i < m_p_meta_map->table_group.capacity; i++) {
        //ÿ����Ĵ�С = ���е�������ĳߴ� * ��������
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
