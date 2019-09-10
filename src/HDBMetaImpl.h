
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
    *  ���ݿ����� HDBMetaImpl.cpp                          *
    ********************************************************/

    Int32 open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode);

    void close(void);

    Int32 reconnect(void);

    /********************************************************
    *  Ԫ���ݲ���                                          *
    ********************************************************/

    /********************************************************
    *  ö�� HDBMetaEnum.cpp                                *
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
    *  λ�� HDBMetaBits.cpp                                *
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
    *  �ṹ HDBMetaStruct.cpp                              *
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
    *  ���� HDBMetaTable.cpp                               *
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
    *  ����ʵ��ռ�ļ������   HDBMetaEntity.cpp          *
    ********************************************************/
    Int32 allocEntity(void);

    /********************************************************
    *  ����ͷ�ļ� HDBMetaGenerateHeader.cpp                *
    ********************************************************/
    Int32 generateHeader(const Char * path) const;

    /********************************************************
    *  ��������  HDBMetaImpl.cpp                           *
    ********************************************************/
    void print(void) const;
private:
    void clear(void);
private:
    Int32 openDb(int open_mode);

    /********************************************************
    *  ��ȡ�����顢���׵�ַ                                *
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
    *  ��ȡ�����顢���±�                                  *
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
    *  ��ӡ                                                *
    ********************************************************/
    void print_header(const Char * name, const HDBGroupItemMap & header) const;
    void print_header_enum(void) const;
    void print_header_bits(void) const;
    void print_header_struct(void) const;
    void print_header_table(void) const;
    void print_header_relation(void) const;

    /********************************************************
    *  ��������С��ƫ�� HDBMetaEntity.cpp              *
    ********************************************************/

    //������С�����������С����ƫ��
    Int32 calcTableSize(HDBTableGroupMap * table);
    //��ȡ����򵥸���Ա������ߴ�
    Int32 getTableMemberAlian(HDBTableGroupMap * table);
    //��ȡ�ṹ������Ա��������ߴ�
    Int32 getStructMemberAlian(HDBStructGroupMap * struct_group);

    //ֻ����ɾ��ϵ��ʱ���ã�������
    Int32 addRelation(const HDBRelationMap * relation);
    HDBRelationMap * getRelation(UInt16 index) const;
    Int32 delRelation(UInt16 index) const;

    //��ȡ�����±꣬���ǵ��������ļ���Ҫ���ʣ��ŵ�ͷ�ļ���
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
    std::string m_str_db_name;          //���ݿ�����
    std::string m_str_db_path;          //���ݿ��ļ�·��
    Int32 m_n_open_mode;                //��ģʽ
    file_mapping * m_p_file_map;        //ӳ���ļ�
    mapped_region * m_p_mapped_region;  //ӳ�������ļ�ȫӳ�䷽ʽ��
    HDBMetaMap * m_p_meta_map;          //ӳ���Ԫ���ݽṹ
    void * m_p_meta_address;            //ӳ����׵�ַ

    friend class HDBMetaGenerateHeader;
};



#endif  //HDB_META_IMPL_H