
/**
 *  @file       HDBMetaMap.h
 *  全部按4字节对齐
 *  下标均指所在数组的全局下标
 */

#ifndef H_DB_META_MAP_H
#define H_DB_META_MAP_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"


class HDB_DLL_EXPORT HDBGroupItemMap {
public:
    UInt16 capacity;                //总条数
    UInt16 used_size;               //已用条数
    Int32 head_offset;              //数组起始内存地址
    Int32 free_index;               //空闲序号

    HDBGroupItemMap()
        : capacity(0),
        used_size(0),
        head_offset(0),
        free_index(-1)
    {}
};

class HDB_DLL_EXPORT HDBMetaMap {
public:
    UInt32 meta_size;                   //元数据区大小 = 元文件大小
    UInt32 db_size;                     //对象数据区大小 = db文件大小
    UInt32 version;                     //版本
    Char db_name[HDB_NAME_LEN];         //数据库名称
    HDBGroupItemMap enum_group;         //枚举组的配置
    HDBGroupItemMap enum_item;          //枚举项的配置
    HDBGroupItemMap bits_group;         //位串组配置
    HDBGroupItemMap bits_item;          //位串项配置
    HDBGroupItemMap struct_group;       //结构组配置
    HDBGroupItemMap struct_item;        //结构项配置
    HDBGroupItemMap table_group;        //表组
    HDBGroupItemMap field_item;         //域项
    HDBGroupItemMap relation;           //表域关系

    HDBMetaMap()
        : meta_size(0)
    {
        db_name[0] = 0;
    };

    Int32 createDefault(const Char * name);

    //计算
    Int32 calcOffset(void);

    //判断记录是否为空
    static bool isRecordEmpty(void * record) {
        return (0 == ((Char *)record)[0]);
    }

};

class HDB_DLL_EXPORT HDBGroupMap {
public:
    Char name[HDB_NAME_LEN];        //组名称
    UInt16 item_num;                //项数量
    Int32 item_head;                //包含的一个项下标

    HDBGroupMap()
        : item_num(0),
        item_head(-1)
    {
        name[0] = 0;
    }


};

class HDB_DLL_EXPORT HDBItemMap {
public:
    Char name[HDB_NAME_LEN];        //项名称
    Int32 group_index;              //所属组下标
    Int32 item_prev;                //前一个项下标
    Int32 item_next;                //后一个项下标

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
    Int32 value;                    //枚举项值

    HDBEnumItemMap()
        : value(0)
    {

    }
};

class HDB_DLL_EXPORT HDBBitsGroupMap : public HDBGroupMap
{
public:
    UInt8 type;                     //类型：UInt8/UInt16/UInt32/UInt64

    HDBBitsGroupMap()
        : type(HDT_UINT8)
    {

    }
};

class HDB_DLL_EXPORT HDBBitsItemMap : public HDBItemMap
{
public:
    UInt8 size;                     //单个位域宽度，单位bit，注意总宽度不能超过位域组类型大小
    HDBBitsItemMap()
        : size(1)
    {

    }
};

class HDB_DLL_EXPORT HDBStructGroupMap : public HDBGroupMap
{
public:
    UInt32 size;                    //结构体大小，注意计算对齐
    HDBStructGroupMap()
        : size(0)
    {

    }
};

class HDB_DLL_EXPORT HDBStructItemMap : public HDBItemMap
{
public:
    UInt8 type;                     //结构项类型，简单数据类型
    Int32 sub_type;                 //自定义子类型下标
    UInt32 size;                    //数组中生效
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
    UInt32 object_offset;           //对象起始偏移（内存地址）
    UInt32 object_size;             //单个对象大小（字节）
    UInt32 object_capacity;         //对象容量（个数）           
    UInt32 object_used_num;         //对象用量（个数）
    UInt32 object_free_index;       //空闲对象下标

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
    UInt32 offset;                  //相对于对象起始地址的偏移（字节）
    UInt32 size;                    //用于数组，不支持字符串数组
    Int32 sub_type;                 //子类型，用于复杂/关系数据结构
    UInt8 type;                     //类型

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
    Bool used;                      //是否使用
    Bool symbiotic;                 //是否共生
    Int32 parent_table;             //父端表
    Int32 parent_field;             //父端域
    Int32 child_table;              //子端表下标
    Int32 child_field;              //子端域下标
    Int32 next;                     //前一个关系（用于多父共生）
    Int32 prev;                     //后一个关系（用于多父共生）
    

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