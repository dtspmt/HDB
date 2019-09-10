
/**
 *  @file       HDBMeta.h
 *  Ԫ���ݽ������̣�
 *      1��ȷ�����ݿ�����
 *      2������λ����ö�١��ṹ�����ݽṹ
 *      3���������򣨹�ϵ����Ҫ�ڸ��ӱ���������ܽ���
 *      4��������������ļ��Ĵ�С��������ʵ����׵�ַƫ��
 *
 */

#ifndef H_DB_META_H
#define H_DB_META_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"

class HDBMetaMap;
class HDBEnumGroupMap;
class HDBEnumItemMap;
class HDBBitsGroupMap;
class HDBBitsItemMap;
class HDBStructGroupMap;
class HDBStructItemMap;
class HDBTableGroupMap;
class HDBFieldItemMap;

class HDBMetaImpl;

class HDB_DLL_EXPORT HDBMeta
{
public:
    HDBMeta();
    ~HDBMeta();

    /********************************************************
    *  ���ݿ����                                          *
    ********************************************************/
    const Char * getPath(void) const;

    const Char * getName(void) const;

    Int32 getOpenMode(void) const;

    /********************************************************
    *  ���ݿ�����                                          *
    ********************************************************/

    /**
    *  �������ݿ����ơ�·�����������ݿ�Ԫ���ݣ�����  path/name.meta
    *  @param  name    ���ݿ����ƣ�������32�ֽ�
    *  @param  path    ���ݿ��ļ�·��
    */
    static Int32 create(const Char * name, const Char * path, const HDBMetaMap * meta_info = NULL);

    /**
    *  �������ݿ�·������ģʽ�������е����ݿ�
    *  @param  db_path ���ݿ�ȫ·�����������ݿ��� xxxx/xx/xxxxxx/db
    *  @param  open_mode   @see OPEN_MODE
    */
    Int32 open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode);

    /**
    *  �ر����ݿ����ӣ��Ὣӳ��Ķ�fflush������
    */
    void close(void);

    /**
    *  ����·�������ݿ��������´�
    */
    Int32 reconnect(void);

    /********************************************************
    *  Ԫ���ݲ���                                          *
    ********************************************************/

    /********************************************************
    *  ö��                                                *
    ********************************************************/

    /**
    *   ����ö��������Ѱ����ö�����е��±�
    *   @param  group_name ö��������
    *   @return ������ö�����е��±�
    */
    Int32 findEnumGroup(const Char * group_name) const;

    /**
    *   ����ö�����±��ȡö����
    *   @param  index   ������ö�����е��±�
    *   @return �ڹ����ڴ��е�ö����ӳ��
    */
    HDBEnumGroupMap * getEnumGroup(UInt16 index) const;

    /**
    *   ����ö����
    *   @param  group_name  ö��������
    *   @return �ɹ����Ӻ󣬻��ڹ����ڴ�ö����������һ��ö��������Ϊ0��ö���飬������������ö�����е��±�
    */
    Int32 addEnumGroup(const Char * group_name);

    /**
    *   ��������ɾ��ö���飬������ö����Ҳ����ɾ��
    *   @param  group_name ö��������
    *   @return ɾ����ö����������ö�����е��±�
    */
    Int32 delEnumGroup(const Char * group_name);

    /**
    *   �����±�ɾ��ö���飬������ö����Ҳ����ɾ��
    *   @param  index ö�����±�
    *   @return ɾ����ö����������ö�����е��±�
    */
    Int32 delEnumGroup(UInt16 index);

    /**
    *   ����ö��������ö������������ö����������ö�����е��±�
    *   @param  group_name ö������
    *   @param  item_name  ö������
    *   @return Ŀ��ö����������ö�����е��±�
    */
    Int32 findEnumItem(const Char * group_name, const Char * item_name) const;

    /**
    *   ����ö�����±ꡢö������������ö����������ö�����е��±�
    *   @param  group_index ö�����±�
    *   @param  item_name  ö������
    *   @return Ŀ��ö����������ö�����е��±�
    */
    Int32 findEnumItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   ����ö���顢ö������������ö����������ö�����е��±�
    *   @param  group      ö����
    *   @param  item_name  ö������
    *   @return Ŀ��ö����������ö�����е��±�
    */
    Int32 findEnumItem(HDBEnumGroupMap * group, const Char * item_name) const;

    /**
    *   ����ö�����±�(ȫ�֣�����ȡö����
    *   @param  global_index    ������ö�����е��±�
    *   @return �����ڴ��е�ö����ӳ��
    */
    HDBEnumItemMap * getEnumItem(UInt16 global_index) const;

    /**
    *   ����ö�����±�(��ö�����У�����ȡö����
    *   @param  group_index    ö�����±�
    *   @param  item_index     ö����������ö������±�
    *   @return �����ڴ��е�ö����ӳ��
    */
    HDBEnumItemMap * getEnumItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   ��ö����������ö����
    *   @param  group    �����ڴ���ö����
    *   @param  item     ��ʱö����
    *   @return �����ڴ��е�ö����ȫ���±�
    */
    Int32 addEnumItem(HDBEnumGroupMap * group, const HDBEnumItemMap * item);

    /**
    *   ��ö������ɾ��ö����
    *   @param  group    �����ڴ���ö����
    *   @param  item_name     ö��������
    *   @return �����ڴ��е�ö����ȫ���±�
    */
    Int32 delEnumItem(HDBEnumGroupMap * group, const Char * item_name);

    /**
    *   ��ö������ɾ��ö����
    *   @param  group    �����ڴ���ö����
    *   @param  item_index     ö������ö�����е��±�
    *   @return �����ڴ��е�ö����ȫ���±�
    */
    Int32 delEnumItem(HDBEnumGroupMap * group, UInt16 item_index);

    /********************************************************
    *  λ��                                                *
    ********************************************************/

    /**
    *   ����λ��������Ѱ��������λ�����е��±�
    *   @param  group_name λ��������
    *   @return ������λ�����е��±�
    */
    Int32 findBitsGroup(const Char * group_name) const;

    /**
    *   ����λ�����±��ȡλ����
    *   @param  index   ������λ�����е��±�
    *   @return �ڹ����ڴ��е�λ����ӳ��
    */
    HDBBitsGroupMap * getBitsGroup(UInt16 index) const;

    /**
    *   ����λ����
    *   @param  group_name     λ��������
    *   @return �ɹ����Ӻ󣬻��ڹ����ڴ�λ����������һ��λ��������Ϊ0��λ���飬������������λ�����е��±�
    */
    Int32 addBitsGroup(const Char * group_name);

    /**
    *   ��������ɾ��λ���飬������λ����Ҳ����ɾ��
    *   @param  group_name λ��������
    *   @return ɾ����λ����������λ�����е��±�
    */
    Int32 delBitsGroup(const Char * group_name);

    /**
    *   �����±�ɾ��λ���飬������λ����Ҳ����ɾ��
    *   @param  index λ����ȫ���±�
    *   @return ɾ����λ����������λ�����е��±�
    */
    Int32 delBitsGroup(UInt16 index);

    /**
    *   ����λ��������λ������������λ����������λ�����е��±�
    *   @param  group_name λ������
    *   @param  item_name  λ������
    *   @return Ŀ��λ����������λ�����е��±�
    */
    Int32 findBitsItem(const Char * group_name, const Char * item_name) const;

    /**
    *   ����λ�����±ꡢλ������������λ����������λ�����е��±�
    *   @param  group_index    λ�����±�
    *   @param  item_name      λ������
    *   @return Ŀ��λ����������λ�����е��±�
    */
    Int32 findBitsItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   ����λ���顢λ������������λ����������λ�����е��±�
    *   @param  group          λ�����±�
    *   @param  item_name      λ������
    *   @return Ŀ��λ����������λ�����е��±�
    */
    Int32 findBitsItem(HDBBitsGroupMap * group, const Char * item_name) const;

    /**
    *   ����λ�����±�(ȫ�֣�����ȡλ����
    *   @param  global_index    ������λ�����е��±�
    *   @return �����ڴ��е�λ����ӳ��
    */
    HDBBitsItemMap * getBitsItem(UInt16 global_index) const;

    /**
    *   ����λ�����±�(��ö�����У�����ȡλ����
    *   @param  group_index    λ�����±�
    *   @param  item_index     λ����������λ������±�
    *   @return �����ڴ��е�λ����ӳ��
    */
    HDBBitsItemMap * getBitsItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   ��λ����������λ����
    *   @param  group    �����ڴ���λ����
    *   @param  item     ��ʱλ����
    *   @return �����ڴ��е�λ����ȫ���±�
    */
    Int32 addBitsItem(HDBBitsGroupMap * group, const HDBBitsItemMap * item);

    /**
    *   ��λ������ɾ��λ����
    *   @param  group          �����ڴ���λ����
    *   @param  item_name      λ��������
    *   @return �����ڴ��е�λ����ȫ���±�
    */
    Int32 delBitsItem(HDBBitsGroupMap * group, const Char * item_name);

    /**
    *   ��λ������ɾ��λ����
    *   @param  group          �����ڴ���λ����
    *   @param  item_index     λ������λ�����е��±�
    *   @return �����ڴ��е�λ����ȫ���±�
    */
    Int32 delBitsItem(HDBBitsGroupMap * group, UInt16 item_index);

    /********************************************************
    *  �ṹ                                                *
    ********************************************************/

    /**
    *   ���ݽṹ������Ѱ�������нṹ���е��±�
    *   @param  group_name �ṹ������
    *   @return �����нṹ���е��±�
    */
    Int32 findStructGroup(const Char * group_name) const;

    /**
    *   ���ݽṹ���±��ȡ�ṹ��
    *   @param  index   �����нṹ���е��±�
    *   @return �ڹ����ڴ��еĽṹ��ӳ��
    */
    HDBStructGroupMap * getStructGroup(UInt16 index) const;

    /**
    *   ���ӽṹ��
    *   @param  group_name   �ṹ������
    *   @return �ɹ����Ӻ󣬻��ڹ����ڴ�ṹ��������һ��λ��������Ϊ0�Ľṹ�飬�����������нṹ���е��±�
    */
    Int32 addStructGroup(const Char * group_name);

    /**
    *   ��������ɾ���ṹ�飬�����Ľṹ��Ҳ����ɾ��
    *   @param  group_name �ṹ������
    *   @return ɾ���Ľṹ�������нṹ���е��±�
    */
    Int32 delStructGroup(const Char * group_name);

    /**
    *   �����±�ɾ���ṹ�飬�����Ľṹ��Ҳ����ɾ��
    *   @param  index �ṹ��ȫ���±�
    *   @return ɾ���Ľṹ�������нṹ���е��±�
    */
    Int32 delStructGroup(UInt16 index);

    /**
    *   ���ݽṹ�������ṹ���������ҽṹ�������нṹ���е��±�
    *   @param  group_name �ṹ����
    *   @param  item_name  �ṹ����
    *   @return Ŀ��ṹ�������нṹ���е��±�
    */
    Int32 findStructItem(const Char * group_name, const Char * item_name) const;

    /**
    *   ���ݽṹ���±ꡢ�ṹ���������ҽṹ�������нṹ���е��±�
    *   @param  group_index      �ṹ���±�
    *   @param  item_name        �ṹ����
    *   @return Ŀ��ṹ�������нṹ���е��±�
    */
    Int32 findStructItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   ���ݽṹ�顢�ṹ���������ҽṹ�������нṹ���е��±�
    *   @param  group        �ṹ���±�
    *   @param  item_name    �ṹ����
    *   @return Ŀ��ṹ�������нṹ���е��±�
    */
    Int32 findStructItem(HDBStructGroupMap * group, const Char * item_name) const;

    /**
    *   ���ݽṹ���±�(ȫ�֣�����ȡ�ṹ��
    *   @param  global_index    �����нṹ���е��±�
    *   @return �����ڴ��еĽṹ��ӳ��
    */
    HDBStructItemMap * getStructItem(UInt16 global_index) const;

    /**
    *   ���ݽṹ���±�(��ö�����У�����ȡ�ṹ��
    *   @param  group_index   �ṹ���±�
    *   @param  item_index    �ṹ���������ṹ����±�
    *   @return �����ڴ��еĽṹ��ӳ��
    */
    HDBStructItemMap * getStructItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   �ڽṹ�������ӽṹ��
    *   @param  group    �����ڴ��нṹ��
    *   @param  item     ��ʱ�ṹ��
    *   @return �����ڴ��еĽṹ��ȫ���±�
    */
    Int32 addStructItem(HDBStructGroupMap * group, const HDBStructItemMap * item);

    /**
    *   �ڽṹ����ɾ���ṹ��
    *   @param  group          �����ڴ��нṹ��
    *   @param  item_name      �ṹ������
    *   @return �����ڴ��еĽṹ��ȫ���±�
    */
    Int32 delStructItem(HDBStructGroupMap * group, const Char * item_name);

    /**
    *   �ڽṹ����ɾ���ṹ��
    *   @param  group          �����ڴ��нṹ��
    *   @param  item_index     �ṹ���ڽṹ���е��±�
    *   @return �����ڴ��еĽṹ��ȫ���±�
    */
    Int32 delStructItem(HDBStructGroupMap * group, UInt16 item_index);

    /********************************************************
    *  ����                                                *
    ********************************************************/

    /**
    *   ���ݱ�������Ѱ�������б����е��±�
    *   @param  group_name ��������
    *   @return �����б����е��±�
    */
    Int32 findTableGroup(const Char * group_name) const;

    /**
    *   ���ݱ����±��ȡ����
    *   @param  index   �����б����е��±�
    *   @return �ڹ����ڴ��еı���ӳ��
    */
    HDBTableGroupMap * getTableGroup(UInt16 index) const;

    /**
    *   ���ӱ���
    *   @param  group  ��д�����ơ����͵���ʱ����ָ��
    *   @return �ɹ����Ӻ󣬻��ڹ����ڴ����������һ����������Ϊ0�ı��飬�����������б����е��±�
    */
    Int32 addTableGroup(const Char * group_name);

    /**
    *   ��������ɾ�����飬����������Ҳ����ɾ��
    *   @param  group_name ��������
    *   @return ɾ���ı��������б����е��±�
    */
    Int32 delTableGroup(const Char * group_name);

    /**
    *   �����±�ɾ�����飬����������Ҳ����ɾ��
    *   @param  index ����ȫ���±�
    *   @return ɾ���ı��������б����е��±�
    */
    Int32 delTableGroup(UInt16 index);

    /**
    *   ���ݱ����������������������������������е��±�
    *   @param  group_name ������
    *   @param  item_name  ������
    *   @return Ŀ�����������������е��±�
    */
    Int32 findFieldItem(const Char * group_name, const Char * item_name) const;

    /**
    *   ���ݱ����±ꡢ���������������������������е��±�
    *   @param  group_index    �����±�
    *   @param  item_name      ������
    *   @return Ŀ�����������������е��±�
    */
    Int32 findFieldItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   ���ݱ��顢���������������������������е��±�
    *   @param  group         ����
    *   @param  item_name     ������
    *   @return Ŀ�����������������е��±�
    */
    Int32 findFieldItem(HDBTableGroupMap * group, const Char * item_name) const;

    /**
    *   ���������±�(ȫ�֣�����ȡ����
    *   @param  global_index    �����������е��±�
    *   @return �����ڴ��е�����ӳ��
    */
    HDBFieldItemMap * getFieldItem(UInt16 global_index) const;

    /**
    *   ���������±�(��ö�����У�����ȡ����
    *   @param  group_index   �����±�
    *   @param  item_index    ����������������±�
    *   @return �����ڴ��е�����ӳ��
    */
    HDBFieldItemMap * getFieldItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   �ڱ�������������
    *   @param  group    �����ڴ��б���
    *   @param  item     ��ʱ����
    *   @return �����ڴ��е�����ȫ���±�
    */
    Int32 addFieldItem(HDBTableGroupMap * group, const HDBFieldItemMap * item);

    /**
    *   �ڱ�����ɾ������
    *   @param  group          �����ڴ��б���
    *   @param  item_name      ��������
    *   @return �����ڴ��е�����ȫ���±�
    */
    Int32 delFieldItem(HDBTableGroupMap * group, const Char * item_name);

    /**
    *   �ڱ�����ɾ������
    *   @param  group          �����ڴ��б���
    *   @param  item_index     �����ڱ����е��±�
    *   @return �����ڴ��е�����ȫ���±�
    */
    Int32 delFieldItem(HDBTableGroupMap * group, UInt16 item_index);

    /**
    *   �����ű�֮�佨�����ӹ�ϵ������Ϊ�������һ���ӱ�
    *   @param  parent_table_name   ������������
    *   @param  parent_table_num    ��������
    *   @param  child_table_name    �ӱ�����
    *   @param  parent_field_name   �ڸ����е�����
    *   @param  child_field_name    ���ֱ��е�����
    *   @param  symbiotic           �Ƿ���
    *   @return ���سɹ�������ϵ�ĸ�������
    */
    Int32 addRelContain(const Char * parent_table_name[HDB_NAME_LEN], 
        UInt16 parent_table_num, 
        const Char * child_table_name, 
        const Char * parent_field_name, 
        const Char * child_field_name, 
        Bool symbiotic = false);

    /**
    *   �����ű�֮��ɾ�����ӹ�ϵ������Ϊ�������һ���ӱ�
    *   @param  parent_table_name   ������������
    *   @param  parent_table_num    ��������
    *   @param  child_table_name    �ӱ�����
    *   @param  parent_field_name   �ڸ����е�����
    *   @param  child_field_name    ���ֱ��е�����
    *   @return ���سɹ�ɾ����ϵ�ĸ�������
    */
    Int32 delRelContain(const Char * parent_table_name[HDB_NAME_LEN],
        UInt16 parent_table_num,
        const Char * child_table_name,
        const Char * parent_field_name,
        const Char * child_field_name);

    /**
    *   �����������ù�ϵ������Ϊ����ָ���ӱ�
    *   @param  parent_table_name   ��������
    *   @param  child_table_name    �ӱ�����
    *   @param  parent_field_name   �ڸ����е�����
    *   @return ���سɹ�������ϵ�ĸ�������
    */
    Int32 addRelRefer(const Char * parent_table_name,
        const Char * child_table_name,
        const Char * parent_field_name);

    /**
    *   ɾ���������ù�ϵ������Ϊ����ָ���ӱ�
    *   @param  parent_table_name   ��������
    *   @param  child_table_name    �ӱ�����
    *   @param  parent_field_name   �ڸ����е�����
    *   @return ���سɹ�ɾ����ϵ�ĸ�������
    */
    Int32 delRelRefer(const Char * parent_table_name,
        const Char * child_table_name,
        const Char * parent_field_name);

    /********************************************************
    *   ����ʵ��ռ�ļ������                             *
    ********************************************************/
    Int32 allocEntity(void);

    /********************************************************
    *   ����ͷ�ļ� HDBMetaGenerateHeader.cpp               *
    *   pathΪĿ¼·���������ָ�������                     *
    ********************************************************/
    Int32 generateHeader(const Char * path) const;

    /********************************************************
    *  ��������                                            *
    ********************************************************/
    void print(void) const;


private:
    HDBMetaImpl * m_p_impl;
};

#endif  //H_DB_META_H