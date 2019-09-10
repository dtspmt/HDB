
/**
 *  @file       HDBDefines.h
 */

#ifndef HDB_DEFINES_H
#define HDB_DEFINES_H

#include "HDataTypes.h"

//名称长度
static const UInt8 HDB_NAME_LEN = 32;

//数据库默认单位大小，单位字节
static const UInt32 HDB_DEFAULT_UINT_SIZE = (1024 * 1024);
//数据库默认大小，单位字节
static const UInt32 HDB_DEFAULT_SIZE = (4 * HDB_DEFAULT_UINT_SIZE);
//数据库默认扩容大小，单位M
static const UInt32 HDB_DEFAULT_INCREASE_SIZE = HDB_DEFAULT_UINT_SIZE;
//默认枚举组容量
static const UInt16 HDB_DEFAULT_ENUM_GROUP_NUM = 0x80;
//默认枚举项容量
static const UInt16 HDB_DEFAULT_ENUM_ITEM_NUM = 0x400;
//默认位串组容量
static const UInt16 HDB_DEFAULT_BITS_GROUP_NUM = 0x80;
//默认位串项容量
static const UInt16 HDB_DEFAULT_BITS_ITEM_NUM = 0x800;
//默认结构组容量
static const UInt16 HDB_DEFAULT_STRUCT_GROUP_NUM = 0x80;
//默认结构项容量
static const UInt16 HDB_DEFAULT_STRUCT_ITEM_NUM = 0x400;
//默认表容量
static const UInt16 HDB_DEFAULT_TABLE_NUM = 0x100;
//默认域容量
static const UInt16 HDB_DEFAULT_FIELD_NUM = 0x8000;
//默认关系数量
static const UInt16 HDB_DEFAULT_RELATION_NUM = 0x200;


#define HDBDELETEPOINTER(p) \
    if (NULL != p) {        \
        delete p;           \
        p = NULL;           \
    }


enum OPEN_MODE {
    OPEN_MODE_READONLY,
    OPEN_MODE_READWRITE,
};

#define HDB_META_FILE_SUFFIX ".meta"
#define HDB_OBJECT_FILE_SUFFIX ".db"

static const UInt32 HDB_INVALID_OBJECT_INDEX = 0xFFFFFFFF;
static const UInt16 HDB_INVALID_TABLE_INDEX = 0xFFFF;

//对齐方式4字节
#define PACK_SIZE 4

//路径分隔符
#define DIR_SEPARATOR '\\'
//头文件后缀
#define HEADER_SUFFIX ".h"

#endif  //HDB_DEFINES_H