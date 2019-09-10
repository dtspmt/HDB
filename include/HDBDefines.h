
/**
 *  @file       HDBDefines.h
 */

#ifndef HDB_DEFINES_H
#define HDB_DEFINES_H

#include "HDataTypes.h"

//���Ƴ���
static const UInt8 HDB_NAME_LEN = 32;

//���ݿ�Ĭ�ϵ�λ��С����λ�ֽ�
static const UInt32 HDB_DEFAULT_UINT_SIZE = (1024 * 1024);
//���ݿ�Ĭ�ϴ�С����λ�ֽ�
static const UInt32 HDB_DEFAULT_SIZE = (4 * HDB_DEFAULT_UINT_SIZE);
//���ݿ�Ĭ�����ݴ�С����λM
static const UInt32 HDB_DEFAULT_INCREASE_SIZE = HDB_DEFAULT_UINT_SIZE;
//Ĭ��ö��������
static const UInt16 HDB_DEFAULT_ENUM_GROUP_NUM = 0x80;
//Ĭ��ö��������
static const UInt16 HDB_DEFAULT_ENUM_ITEM_NUM = 0x400;
//Ĭ��λ��������
static const UInt16 HDB_DEFAULT_BITS_GROUP_NUM = 0x80;
//Ĭ��λ��������
static const UInt16 HDB_DEFAULT_BITS_ITEM_NUM = 0x800;
//Ĭ�Ͻṹ������
static const UInt16 HDB_DEFAULT_STRUCT_GROUP_NUM = 0x80;
//Ĭ�Ͻṹ������
static const UInt16 HDB_DEFAULT_STRUCT_ITEM_NUM = 0x400;
//Ĭ�ϱ�����
static const UInt16 HDB_DEFAULT_TABLE_NUM = 0x100;
//Ĭ��������
static const UInt16 HDB_DEFAULT_FIELD_NUM = 0x8000;
//Ĭ�Ϲ�ϵ����
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

//���뷽ʽ4�ֽ�
#define PACK_SIZE 4

//·���ָ���
#define DIR_SEPARATOR '\\'
//ͷ�ļ���׺
#define HEADER_SUFFIX ".h"

#endif  //HDB_DEFINES_H