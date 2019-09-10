
/**
 *  @file       HDBMeta.h
 *  元数据建立流程：
 *      1、确定数据库名称
 *      2、建立位串、枚举、结构等数据结构
 *      3、建立表、域（关系域需要在父子表都建立后才能建）
 *      4、计算对象数据文件的大小，各个表实体的首地址偏移
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
    *  数据库参数                                          *
    ********************************************************/
    const Char * getPath(void) const;

    const Char * getName(void) const;

    Int32 getOpenMode(void) const;

    /********************************************************
    *  数据库连接                                          *
    ********************************************************/

    /**
    *  根据数据库名称、路径创建空数据库元数据，生成  path/name.meta
    *  @param  name    数据库名称，不超过32字节
    *  @param  path    数据库文件路径
    */
    static Int32 create(const Char * name, const Char * path, const HDBMetaMap * meta_info = NULL);

    /**
    *  根据数据库路径，打开模式，打开已有的数据库
    *  @param  db_path 数据库全路径，包含数据库名 xxxx/xx/xxxxxx/db
    *  @param  open_mode   @see OPEN_MODE
    */
    Int32 open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode);

    /**
    *  关闭数据库连接，会将映射改动fflush到磁盘
    */
    void close(void);

    /**
    *  根据路径、数据库名称重新打开
    */
    Int32 reconnect(void);

    /********************************************************
    *  元数据操作                                          *
    ********************************************************/

    /********************************************************
    *  枚举                                                *
    ********************************************************/

    /**
    *   根据枚举组名称寻找在枚举组中的下标
    *   @param  group_name 枚举组名称
    *   @return 在所有枚举组中的下标
    */
    Int32 findEnumGroup(const Char * group_name) const;

    /**
    *   根据枚举组下标获取枚举组
    *   @param  index   在所有枚举组中的下标
    *   @return 在共享内存中的枚举组映射
    */
    HDBEnumGroupMap * getEnumGroup(UInt16 index) const;

    /**
    *   增加枚举组
    *   @param  group_name  枚举组名称
    *   @return 成功增加后，会在共享内存枚举组中增加一个枚举项数量为0的枚举组，并返回在所有枚举组中的下标
    */
    Int32 addEnumGroup(const Char * group_name);

    /**
    *   根据名称删除枚举组，包含的枚举项也跟随删除
    *   @param  group_name 枚举组名称
    *   @return 删除的枚举组在所有枚举组中的下标
    */
    Int32 delEnumGroup(const Char * group_name);

    /**
    *   根据下标删除枚举组，包含的枚举项也跟随删除
    *   @param  index 枚举组下标
    *   @return 删除的枚举组在所有枚举组中的下标
    */
    Int32 delEnumGroup(UInt16 index);

    /**
    *   根据枚举组名、枚举项名，查找枚举项在所有枚举项中的下标
    *   @param  group_name 枚举组名
    *   @param  item_name  枚举项名
    *   @return 目标枚举项在所有枚举项中的下标
    */
    Int32 findEnumItem(const Char * group_name, const Char * item_name) const;

    /**
    *   根据枚举组下标、枚举项名，查找枚举项在所有枚举项中的下标
    *   @param  group_index 枚举组下标
    *   @param  item_name  枚举项名
    *   @return 目标枚举项在所有枚举项中的下标
    */
    Int32 findEnumItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   根据枚举组、枚举项名，查找枚举项在所有枚举项中的下标
    *   @param  group      枚举组
    *   @param  item_name  枚举项名
    *   @return 目标枚举项在所有枚举项中的下标
    */
    Int32 findEnumItem(HDBEnumGroupMap * group, const Char * item_name) const;

    /**
    *   根据枚举项下标(全局），获取枚举项
    *   @param  global_index    在所有枚举项中的下标
    *   @return 共享内存中的枚举项映射
    */
    HDBEnumItemMap * getEnumItem(UInt16 global_index) const;

    /**
    *   根据枚举项下标(在枚举组中），获取枚举项
    *   @param  group_index    枚举组下标
    *   @param  item_index     枚举项在所属枚举组的下标
    *   @return 共享内存中的枚举项映射
    */
    HDBEnumItemMap * getEnumItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   在枚举组下增加枚举项
    *   @param  group    共享内存中枚举组
    *   @param  item     临时枚举项
    *   @return 共享内存中的枚举项全局下标
    */
    Int32 addEnumItem(HDBEnumGroupMap * group, const HDBEnumItemMap * item);

    /**
    *   在枚举组下删除枚举项
    *   @param  group    共享内存中枚举组
    *   @param  item_name     枚举项名称
    *   @return 共享内存中的枚举项全局下标
    */
    Int32 delEnumItem(HDBEnumGroupMap * group, const Char * item_name);

    /**
    *   在枚举组下删除枚举项
    *   @param  group    共享内存中枚举组
    *   @param  item_index     枚举项在枚举组中的下标
    *   @return 共享内存中的枚举项全局下标
    */
    Int32 delEnumItem(HDBEnumGroupMap * group, UInt16 item_index);

    /********************************************************
    *  位串                                                *
    ********************************************************/

    /**
    *   根据位串组名称寻找在所有位串组中的下标
    *   @param  group_name 位串组名称
    *   @return 在所有位串组中的下标
    */
    Int32 findBitsGroup(const Char * group_name) const;

    /**
    *   根据位串组下标获取位串组
    *   @param  index   在所有位串组中的下标
    *   @return 在共享内存中的位串组映射
    */
    HDBBitsGroupMap * getBitsGroup(UInt16 index) const;

    /**
    *   增加位串组
    *   @param  group_name     位串组名称
    *   @return 成功增加后，会在共享内存位串组中增加一个位串项数量为0的位串组，并返回在所有位串组中的下标
    */
    Int32 addBitsGroup(const Char * group_name);

    /**
    *   根据名称删除位串组，包含的位串项也跟随删除
    *   @param  group_name 位串组名称
    *   @return 删除的位串组在所有位串组中的下标
    */
    Int32 delBitsGroup(const Char * group_name);

    /**
    *   根据下标删除位串组，包含的位串项也跟随删除
    *   @param  index 位串组全局下标
    *   @return 删除的位串组在所有位串组中的下标
    */
    Int32 delBitsGroup(UInt16 index);

    /**
    *   根据位串组名、位串项名，查找位串项在所有位串项中的下标
    *   @param  group_name 位串组名
    *   @param  item_name  位串项名
    *   @return 目标位串项在所有位串项中的下标
    */
    Int32 findBitsItem(const Char * group_name, const Char * item_name) const;

    /**
    *   根据位串组下标、位串项名，查找位串项在所有位串项中的下标
    *   @param  group_index    位串组下标
    *   @param  item_name      位串项名
    *   @return 目标位串项在所有位串项中的下标
    */
    Int32 findBitsItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   根据位串组、位串项名，查找位串项在所有位串项中的下标
    *   @param  group          位串组下标
    *   @param  item_name      位串项名
    *   @return 目标位串项在所有位串项中的下标
    */
    Int32 findBitsItem(HDBBitsGroupMap * group, const Char * item_name) const;

    /**
    *   根据位串项下标(全局），获取位串项
    *   @param  global_index    在所有位串项中的下标
    *   @return 共享内存中的位串项映射
    */
    HDBBitsItemMap * getBitsItem(UInt16 global_index) const;

    /**
    *   根据位串项下标(在枚举组中），获取位串项
    *   @param  group_index    位串组下标
    *   @param  item_index     位串项在所属位串组的下标
    *   @return 共享内存中的位串项映射
    */
    HDBBitsItemMap * getBitsItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   在位串组下增加位串项
    *   @param  group    共享内存中位串组
    *   @param  item     临时位串项
    *   @return 共享内存中的位串项全局下标
    */
    Int32 addBitsItem(HDBBitsGroupMap * group, const HDBBitsItemMap * item);

    /**
    *   在位串组下删除位串项
    *   @param  group          共享内存中位串组
    *   @param  item_name      位串项名称
    *   @return 共享内存中的位串项全局下标
    */
    Int32 delBitsItem(HDBBitsGroupMap * group, const Char * item_name);

    /**
    *   在位串组下删除位串项
    *   @param  group          共享内存中位串组
    *   @param  item_index     位串项在位串组中的下标
    *   @return 共享内存中的位串项全局下标
    */
    Int32 delBitsItem(HDBBitsGroupMap * group, UInt16 item_index);

    /********************************************************
    *  结构                                                *
    ********************************************************/

    /**
    *   根据结构组名称寻找在所有结构组中的下标
    *   @param  group_name 结构组名称
    *   @return 在所有结构组中的下标
    */
    Int32 findStructGroup(const Char * group_name) const;

    /**
    *   根据结构组下标获取结构组
    *   @param  index   在所有结构组中的下标
    *   @return 在共享内存中的结构组映射
    */
    HDBStructGroupMap * getStructGroup(UInt16 index) const;

    /**
    *   增加结构组
    *   @param  group_name   结构组名称
    *   @return 成功增加后，会在共享内存结构组中增加一个位串项数量为0的结构组，并返回在所有结构组中的下标
    */
    Int32 addStructGroup(const Char * group_name);

    /**
    *   根据名称删除结构组，包含的结构项也跟随删除
    *   @param  group_name 结构组名称
    *   @return 删除的结构组在所有结构组中的下标
    */
    Int32 delStructGroup(const Char * group_name);

    /**
    *   根据下标删除结构组，包含的结构项也跟随删除
    *   @param  index 结构组全局下标
    *   @return 删除的结构组在所有结构组中的下标
    */
    Int32 delStructGroup(UInt16 index);

    /**
    *   根据结构组名、结构项名，查找结构项在所有结构项中的下标
    *   @param  group_name 结构组名
    *   @param  item_name  结构项名
    *   @return 目标结构项在所有结构项中的下标
    */
    Int32 findStructItem(const Char * group_name, const Char * item_name) const;

    /**
    *   根据结构组下标、结构项名，查找结构项在所有结构项中的下标
    *   @param  group_index      结构组下标
    *   @param  item_name        结构项名
    *   @return 目标结构项在所有结构项中的下标
    */
    Int32 findStructItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   根据结构组、结构项名，查找结构项在所有结构项中的下标
    *   @param  group        结构组下标
    *   @param  item_name    结构项名
    *   @return 目标结构项在所有结构项中的下标
    */
    Int32 findStructItem(HDBStructGroupMap * group, const Char * item_name) const;

    /**
    *   根据结构项下标(全局），获取结构项
    *   @param  global_index    在所有结构项中的下标
    *   @return 共享内存中的结构项映射
    */
    HDBStructItemMap * getStructItem(UInt16 global_index) const;

    /**
    *   根据结构项下标(在枚举组中），获取结构项
    *   @param  group_index   结构组下标
    *   @param  item_index    结构项在所属结构组的下标
    *   @return 共享内存中的结构项映射
    */
    HDBStructItemMap * getStructItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   在结构组下增加结构项
    *   @param  group    共享内存中结构组
    *   @param  item     临时结构项
    *   @return 共享内存中的结构项全局下标
    */
    Int32 addStructItem(HDBStructGroupMap * group, const HDBStructItemMap * item);

    /**
    *   在结构组下删除结构项
    *   @param  group          共享内存中结构组
    *   @param  item_name      结构项名称
    *   @return 共享内存中的结构项全局下标
    */
    Int32 delStructItem(HDBStructGroupMap * group, const Char * item_name);

    /**
    *   在结构组下删除结构项
    *   @param  group          共享内存中结构组
    *   @param  item_index     结构项在结构组中的下标
    *   @return 共享内存中的结构项全局下标
    */
    Int32 delStructItem(HDBStructGroupMap * group, UInt16 item_index);

    /********************************************************
    *  表域                                                *
    ********************************************************/

    /**
    *   根据表组名称寻找在所有表组中的下标
    *   @param  group_name 表组名称
    *   @return 在所有表组中的下标
    */
    Int32 findTableGroup(const Char * group_name) const;

    /**
    *   根据表组下标获取表组
    *   @param  index   在所有表组中的下标
    *   @return 在共享内存中的表组映射
    */
    HDBTableGroupMap * getTableGroup(UInt16 index) const;

    /**
    *   增加表组
    *   @param  group  填写了名称、类型的临时变量指针
    *   @return 成功增加后，会在共享内存表组中增加一个域项数量为0的表组，并返回在所有表组中的下标
    */
    Int32 addTableGroup(const Char * group_name);

    /**
    *   根据名称删除表组，包含的域项也跟随删除
    *   @param  group_name 表组名称
    *   @return 删除的表组在所有表组中的下标
    */
    Int32 delTableGroup(const Char * group_name);

    /**
    *   根据下标删除表组，包含的域项也跟随删除
    *   @param  index 表组全局下标
    *   @return 删除的表组在所有表组中的下标
    */
    Int32 delTableGroup(UInt16 index);

    /**
    *   根据表组名、域项名，查找域项在所有域项中的下标
    *   @param  group_name 表组名
    *   @param  item_name  域项名
    *   @return 目标域项在所有域项中的下标
    */
    Int32 findFieldItem(const Char * group_name, const Char * item_name) const;

    /**
    *   根据表组下标、域项名，查找域项在所有域项中的下标
    *   @param  group_index    表组下标
    *   @param  item_name      域项名
    *   @return 目标域项在所有域项中的下标
    */
    Int32 findFieldItem(UInt16 group_index, const Char * item_name) const;

    /**
    *   根据表组、域项名，查找域项在所有域项中的下标
    *   @param  group         表组
    *   @param  item_name     域项名
    *   @return 目标域项在所有域项中的下标
    */
    Int32 findFieldItem(HDBTableGroupMap * group, const Char * item_name) const;

    /**
    *   根据域项下标(全局），获取域项
    *   @param  global_index    在所有域项中的下标
    *   @return 共享内存中的域项映射
    */
    HDBFieldItemMap * getFieldItem(UInt16 global_index) const;

    /**
    *   根据域项下标(在枚举组中），获取域项
    *   @param  group_index   表组下标
    *   @param  item_index    域项在所属表组的下标
    *   @return 共享内存中的域项映射
    */
    HDBFieldItemMap * getFieldItem(UInt16 group_index, UInt16 item_index) const;

    /**
    *   在表组下增加域项
    *   @param  group    共享内存中表组
    *   @param  item     临时域项
    *   @return 共享内存中的域项全局下标
    */
    Int32 addFieldItem(HDBTableGroupMap * group, const HDBFieldItemMap * item);

    /**
    *   在表组下删除域项
    *   @param  group          共享内存中表组
    *   @param  item_name      域项名称
    *   @return 共享内存中的域项全局下标
    */
    Int32 delFieldItem(HDBTableGroupMap * group, const Char * item_name);

    /**
    *   在表组下删除域项
    *   @param  group          共享内存中表组
    *   @param  item_index     域项在表组中的下标
    *   @return 共享内存中的域项全局下标
    */
    Int32 delFieldItem(HDBTableGroupMap * group, UInt16 item_index);

    /**
    *   在两张表之间建立父子关系，可以为多个父表，一个子表
    *   @param  parent_table_name   父表数组名称
    *   @param  parent_table_num    父表数量
    *   @param  child_table_name    子表名称
    *   @param  parent_field_name   在父表中的域名
    *   @param  child_field_name    在字表中的域名
    *   @param  symbiotic           是否共生
    *   @return 返回成功建立关系的父表数量
    */
    Int32 addRelContain(const Char * parent_table_name[HDB_NAME_LEN], 
        UInt16 parent_table_num, 
        const Char * child_table_name, 
        const Char * parent_field_name, 
        const Char * child_field_name, 
        Bool symbiotic = false);

    /**
    *   在两张表之间删除父子关系，可以为多个父表，一个子表
    *   @param  parent_table_name   父表数组名称
    *   @param  parent_table_num    父表数量
    *   @param  child_table_name    子表名称
    *   @param  parent_field_name   在父表中的域名
    *   @param  child_field_name    在字表中的域名
    *   @return 返回成功删除关系的父表数量
    */
    Int32 delRelContain(const Char * parent_table_name[HDB_NAME_LEN],
        UInt16 parent_table_num,
        const Char * child_table_name,
        const Char * parent_field_name,
        const Char * child_field_name);

    /**
    *   建立单向引用关系（方向为父表指向子表）
    *   @param  parent_table_name   父表名称
    *   @param  child_table_name    子表名称
    *   @param  parent_field_name   在父表中的域名
    *   @return 返回成功建立关系的父表数量
    */
    Int32 addRelRefer(const Char * parent_table_name,
        const Char * child_table_name,
        const Char * parent_field_name);

    /**
    *   删除单向引用关系（方向为父表指向子表）
    *   @param  parent_table_name   父表名称
    *   @param  child_table_name    子表名称
    *   @param  parent_field_name   在父表中的域名
    *   @return 返回成功删除关系的父表数量
    */
    Int32 delRelRefer(const Char * parent_table_name,
        const Char * child_table_name,
        const Char * parent_field_name);

    /********************************************************
    *   对象实体空间的计算分配                             *
    ********************************************************/
    Int32 allocEntity(void);

    /********************************************************
    *   生成头文件 HDBMetaGenerateHeader.cpp               *
    *   path为目录路径，不带分隔符结束                     *
    ********************************************************/
    Int32 generateHeader(const Char * path) const;

    /********************************************************
    *  辅助函数                                            *
    ********************************************************/
    void print(void) const;


private:
    HDBMetaImpl * m_p_impl;
};

#endif  //H_DB_META_H