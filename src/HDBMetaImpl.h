
/**
 *  @file       HDBMetaImpl.h
 */

#ifndef HDB_META_IMPL_H
#define HDB_META_IMPL_H

#include "HDB/HDataTypes.h"
#include "HDB/HDBDefines.h"

#include "boost/interprocess/file_mapping.hpp"
#include "boost/interprocess/mapped_region.hpp"

#include <string>
using namespace std;
using namespace boost::interprocess;

class HDBMetaMap;
class HDBGroupItemMap;
class HDBEnumGroupMap;
class HDBEnumItemMap;
class HDBBitsGroupMap;
class HDBBitsItemMap;
class HDBStructGroupMap;
class HDBStructItemMap;
class HDBTableGroupMap;
class HDBFieldItemMap;
class HDBRelationMap;

class HDBMetaImpl
{
    friend class HDBMeta;
public:
    HDBMetaImpl();
    ~HDBMetaImpl();

    /********************************************************
    *  数据库连接 HDBMetaImpl.cpp                          *
    ********************************************************/

    Int32 open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode);

    void close(void);

    Int32 reconnect(void);

    /********************************************************
    *  元数据操作                                          *
    ********************************************************/

    /********************************************************
    *  枚举 HDBMetaEnum.cpp                                *
    ********************************************************/

    Int32 findEnumGroup(const Char * group_name) const;

    HDBEnumGroupMap * getEnumGroup(UInt16 index) const;

    Int32 addEnumGroup(const Char * group_name);

    Int32 delEnumGroup(const Char * group_name);

    Int32 delEnumGroup(UInt16 index);

    Int32 findEnumItem(const Char * group_name, const Char * item_name) const;

    Int32 findEnumItem(UInt16 group_index, const Char * item_name) const;

    Int32 findEnumItem(HDBEnumGroupMap * group, const Char * item_name) const;

    HDBEnumItemMap * getEnumItem(UInt16 global_index) const;

    HDBEnumItemMap * getEnumItem(UInt16 group_index, UInt16 item_index) const;

    Int32 addEnumItem(HDBEnumGroupMap * group, const HDBEnumItemMap * item);

    Int32 delEnumItem(HDBEnumGroupMap * group, const Char * item_name);

    Int32 delEnumItem(HDBEnumGroupMap * group, UInt16 item_index);

    /********************************************************
    *  位串 HDBMetaBits.cpp                                *
    ********************************************************/

    Int32 findBitsGroup(const Char * group_name) const;

    HDBBitsGroupMap * getBitsGroup(UInt16 index) const;

    Int32 addBitsGroup(const Char * group_name);

    Int32 delBitsGroup(const Char * group_name);

    Int32 delBitsGroup(UInt16 index);

    Int32 findBitsItem(const Char * group_name, const Char * item_name) const;

    Int32 findBitsItem(UInt16 group_index, const Char * item_name) const;

    Int32 findBitsItem(HDBBitsGroupMap * group, const Char * item_name) const;

    HDBBitsItemMap * getBitsItem(UInt16 global_index) const;

    HDBBitsItemMap * getBitsItem(UInt16 group_index, UInt16 item_index) const;

    Int32 addBitsItem(HDBBitsGroupMap * group, const HDBBitsItemMap * item);

    Int32 delBitsItem(HDBBitsGroupMap * group, const Char * item_name);

    Int32 delBitsItem(HDBBitsGroupMap * group, UInt16 item_index);

    /********************************************************
    *  结构 HDBMetaStruct.cpp                              *
    ********************************************************/

    Int32 findStructGroup(const Char * group_name) const;

    HDBStructGroupMap * getStructGroup(UInt16 index) const;

    Int32 addStructGroup(const Char * group_name);

    Int32 delStructGroup(const Char * group_name);

    Int32 delStructGroup(UInt16 index);

    Int32 findStructItem(const Char * group_name, const Char * item_name) const;

    Int32 findStructItem(UInt16 group_index, const Char * item_name) const;

    Int32 findStructItem(HDBStructGroupMap * group, const Char * item_name) const;

    HDBStructItemMap * getStructItem(UInt16 global_index) const;

    HDBStructItemMap * getStructItem(UInt16 group_index, UInt16 item_index) const;

    Int32 addStructItem(HDBStructGroupMap * group, const HDBStructItemMap * item);

    Int32 delStructItem(HDBStructGroupMap * group, const Char * item_name);

    Int32 delStructItem(HDBStructGroupMap * group, UInt16 item_index);

    /********************************************************
    *  表域 HDBMetaTable.cpp                               *
    ********************************************************/

    Int32 findTableGroup(const Char * group_name) const;

    HDBTableGroupMap * getTableGroup(UInt16 index) const;

    Int32 addTableGroup(const Char * group_name);

    Int32 delTableGroup(const Char * group_name);

    Int32 delTableGroup(UInt16 index);

    Int32 findFieldItem(const Char * group_name, const Char * item_name) const;

    Int32 findFieldItem(UInt16 group_index, const Char * item_name) const;

    Int32 findFieldItem(HDBTableGroupMap * group, const Char * item_name) const;

    HDBFieldItemMap * getFieldItem(UInt16 global_index) const;

    HDBFieldItemMap * getFieldItem(UInt16 group_index, UInt16 item_index) const;

    Int32 addFieldItem(HDBTableGroupMap * group, const HDBFieldItemMap * item);

    Int32 delFieldItem(HDBTableGroupMap * group, const Char * item_name);

    Int32 delFieldItem(HDBTableGroupMap * group, UInt16 item_index);

    Int32 addRelContain(const Char * parent_table_name[HDB_NAME_LEN],
        UInt16 parent_table_num,
        const Char * child_table_name,
        const Char * parent_field_name,
        const Char * child_field_name,
        Bool symbiotic = false);

    Int32 delRelContain(const Char * parent_table_name[HDB_NAME_LEN],
        UInt16 parent_table_num,
        const Char * child_table_name,
        const Char * parent_field_name,
        const Char * child_field_name);

    Int32 addRelRefer(const Char * parent_table_name,
        const Char * child_table_name,
        const Char * parent_field_name);

    Int32 delRelRefer(const Char * parent_table_name,
        const Char * child_table_name,
        const Char * parent_field_name);

    /********************************************************
    *  对象实体空间的计算分配   HDBMetaEntity.cpp          *
    ********************************************************/
    Int32 allocEntity(void);

    /********************************************************
    *  生成头文件 HDBMetaGenerateHeader.cpp                *
    ********************************************************/
    Int32 generateHeader(const Char * path) const;

    /********************************************************
    *  辅助函数  HDBMetaImpl.cpp                           *
    ********************************************************/
    void print(void) const;
private:
    void clear(void);
private:
    Int32 openDb(int open_mode);

    /********************************************************
    *  获取各类组、项首地址                                *
    ********************************************************/
    HDBEnumGroupMap * getEnumGroupMapHead(void) const;
    HDBEnumItemMap * getEnumItemMapHead(void) const;
    HDBBitsGroupMap * getBitsGroupMapHead(void) const;
    HDBBitsItemMap * getBitsItemMapHead(void) const;
    HDBStructGroupMap * getStructGroupMapHead(void) const;
    HDBStructItemMap * getStructItemMapHead(void) const;
    HDBTableGroupMap * getTableGroupMapHead(void) const;
    HDBFieldItemMap * getFieldItemMapHead(void) const;
    HDBRelationMap * getRelationMapHead(void) const;

    /********************************************************
    *  获取各类组、项下标                                  *
    ********************************************************/
    Int32 getEnumGroupMapIndex(HDBEnumGroupMap * group) const;
    Int32 getEnumItemMapIndex(HDBEnumItemMap * item) const;
    Int32 getBitsGroupMapIndex(HDBBitsGroupMap * group) const;
    Int32 getBitsItemMapIndex(HDBBitsItemMap * item) const;
    Int32 getStructGroupMapIndex(HDBStructGroupMap * group) const;
    Int32 getStructItemMapIndex(HDBStructItemMap * item) const;
    Int32 getTableGroupMapIndex(HDBTableGroupMap * group) const;
    Int32 getFieldItemMapIndex(HDBFieldItemMap * item) const;

    /********************************************************
    *  打印                                                *
    ********************************************************/
    void print_header(const Char * name, const HDBGroupItemMap & header) const;
    void print_header_enum(void) const;
    void print_header_bits(void) const;
    void print_header_struct(void) const;
    void print_header_table(void) const;
    void print_header_relation(void) const;

    /********************************************************
    *  计算表、域大小、偏移 HDBMetaEntity.cpp              *
    ********************************************************/

    //计算表大小、单个对象大小、域偏移
    Int32 calcTableSize(HDBTableGroupMap * table);
    //获取表的域单个成员最大对齐尺寸
    Int32 getTableMemberAlian(HDBTableGroupMap * table);
    //获取结构单个成员的最大对齐尺寸
    Int32 getStructMemberAlian(HDBStructGroupMap * struct_group);

    //只在增删关系域时调用，不公开
    Int32 addRelation(const HDBRelationMap * relation);
    HDBRelationMap * getRelation(UInt16 index) const;
    Int32 delRelation(UInt16 index) const;

    //获取空闲下标，考虑到各个子文件需要访问，放到头文件里
    template <class T>
    static Int32 getNextFreeIndex(T * head, UInt16 capacity, UInt16 current)
    {
        UInt16 i = current;
        UInt16 count = 0;
        for (count = 0; count < capacity; count++) {
            i++;
            if (i >= capacity) {
                i = 0;
            }
            if (HDBMetaMap::isRecordEmpty(head + i)) {
                return i;
            }
        }
        return -1;
    }

private:
    std::string m_str_db_name;          //数据库名称
    std::string m_str_db_path;          //数据库文件路径
    Int32 m_n_open_mode;                //打开模式
    file_mapping * m_p_file_map;        //映射文件
    mapped_region * m_p_mapped_region;  //映射区域（文件全映射方式）
    HDBMetaMap * m_p_meta_map;          //映射的元数据结构
    void * m_p_meta_address;            //映射后首地址

    friend class HDBMetaGenerateHeader;
};



#endif  //HDB_META_IMPL_H