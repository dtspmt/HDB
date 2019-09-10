
/**
 *  @file       HDBMetaMap.h
 *  ȫ����4�ֽڶ���
 *  �±��ָ���������ȫ���±�
 */

#ifndef H_DB_META_MAP_H
#define H_DB_META_MAP_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"


class HDB_DLL_EXPORT HDBGroupItemMap {
public:
    UInt16 capacity;                //������
    UInt16 used_size;               //��������
    Int32 head_offset;              //������ʼ�ڴ��ַ
    Int32 free_index;               //�������

    HDBGroupItemMap()
        : capacity(0),
        used_size(0),
        head_offset(0),
        free_index(-1)
    {}
};

class HDB_DLL_EXPORT HDBMetaMap {
public:
    UInt32 meta_size;                   //Ԫ��������С = Ԫ�ļ���С
    UInt32 db_size;                     //������������С = db�ļ���С
    UInt32 version;                     //�汾
    Char db_name[HDB_NAME_LEN];         //���ݿ�����
    HDBGroupItemMap enum_group;         //ö���������
    HDBGroupItemMap enum_item;          //ö���������
    HDBGroupItemMap bits_group;         //λ��������
    HDBGroupItemMap bits_item;          //λ��������
    HDBGroupItemMap struct_group;       //�ṹ������
    HDBGroupItemMap struct_item;        //�ṹ������
    HDBGroupItemMap table_group;        //����
    HDBGroupItemMap field_item;         //����
    HDBGroupItemMap relation;           //�����ϵ

    HDBMetaMap()
        : meta_size(0)
    {
        db_name[0] = 0;
    };

    Int32 createDefault(const Char * name);

    //����
    Int32 calcOffset(void);

    //�жϼ�¼�Ƿ�Ϊ��
    static bool isRecordEmpty(void * record) {
        return (0 == ((Char *)record)[0]);
    }

};

class HDB_DLL_EXPORT HDBGroupMap {
public:
    Char name[HDB_NAME_LEN];        //������
    UInt16 item_num;                //������
    Int32 item_head;                //������һ�����±�

    HDBGroupMap()
        : item_num(0),
        item_head(-1)
    {
        name[0] = 0;
    }


};

class HDB_DLL_EXPORT HDBItemMap {
public:
    Char name[HDB_NAME_LEN];        //������
    Int32 group_index;              //�������±�
    Int32 item_prev;                //ǰһ�����±�
    Int32 item_next;                //��һ�����±�

    HDBItemMap()
        : group_index(-1),
        item_prev(-1),
        item_next(-1)
    {
        name[0] = 0;
    }
};

class HDB_DLL_EXPORT HDBEnumGroupMap : public HDBGroupMap
{
public:

};

class HDB_DLL_EXPORT HDBEnumItemMap : public HDBItemMap
{
public:
    Int32 value;                    //ö����ֵ

    HDBEnumItemMap()
        : value(0)
    {

    }
};

class HDB_DLL_EXPORT HDBBitsGroupMap : public HDBGroupMap
{
public:
    UInt8 type;                     //���ͣ�UInt8/UInt16/UInt32/UInt64

    HDBBitsGroupMap()
        : type(HDT_UINT8)
    {

    }
};

class HDB_DLL_EXPORT HDBBitsItemMap : public HDBItemMap
{
public:
    UInt8 size;                     //����λ���ȣ���λbit��ע���ܿ�Ȳ��ܳ���λ�������ʹ�С
    HDBBitsItemMap()
        : size(1)
    {

    }
};

class HDB_DLL_EXPORT HDBStructGroupMap : public HDBGroupMap
{
public:
    UInt32 size;                    //�ṹ���С��ע��������
    HDBStructGroupMap()
        : size(0)
    {

    }
};

class HDB_DLL_EXPORT HDBStructItemMap : public HDBItemMap
{
public:
    UInt8 type;                     //�ṹ�����ͣ�����������
    Int32 sub_type;                 //�Զ����������±�
    UInt32 size;                    //��������Ч
    HDBStructItemMap()
        : type(HDT_UINT8),
        sub_type(HDT_UNKNOWN),
        size(1)
    {

    }
};

class HDB_DLL_EXPORT HDBTableGroupMap : public HDBGroupMap
{
public:
    UInt32 object_offset;           //������ʼƫ�ƣ��ڴ��ַ��
    UInt32 object_size;             //���������С���ֽڣ�
    UInt32 object_capacity;         //����������������           
    UInt32 object_used_num;         //����������������
    UInt32 object_free_index;       //���ж����±�

    HDBTableGroupMap()
        : object_offset(0),
        object_size(0),
        object_capacity(0),
        object_used_num(0),
        object_free_index(-1)
    {}
};

class HDB_DLL_EXPORT HDBFieldItemMap : public HDBItemMap
{
public:
    UInt32 offset;                  //����ڶ�����ʼ��ַ��ƫ�ƣ��ֽڣ�
    UInt32 size;                    //�������飬��֧���ַ�������
    Int32 sub_type;                 //�����ͣ����ڸ���/��ϵ���ݽṹ
    UInt8 type;                     //����

    HDBFieldItemMap()
        : size(1),
        offset(0),
        type(HDT_UINT8),
        sub_type(-1)
    {

    }
};

class HDB_DLL_EXPORT HDBRelationMap
{
public:
    Bool used;                      //�Ƿ�ʹ��
    Bool symbiotic;                 //�Ƿ���
    Int32 parent_table;             //���˱�
    Int32 parent_field;             //������
    Int32 child_table;              //�Ӷ˱��±�
    Int32 child_field;              //�Ӷ����±�
    Int32 next;                     //ǰһ����ϵ�����ڶุ������
    Int32 prev;                     //��һ����ϵ�����ڶุ������
    

    HDBRelationMap()
        : used(false),
        symbiotic(false),
        parent_table(-1),
        parent_field(-1),
        child_table(-1),
        child_field(-1),
        next(-1),
        prev(-1)
    {

    }
};


#endif  //H_DB_META_MAP_H