
/**
*  @file       HDBMeta.cpp
*/

#include "HDB/HDBMeta.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"

#include "HDBMetaImpl.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HDBMeta::HDBMeta()
    : m_p_impl(NULL)
{
    m_p_impl = new HDBMetaImpl;
}

HDBMeta::~HDBMeta()
{
    HDBDELETEPOINTER(m_p_impl);
}

const Char * HDBMeta::getPath(void) const
{
    return m_p_impl->m_str_db_path.c_str();
}

const Char * HDBMeta::getName(void) const
{
    return m_p_impl->m_str_db_name.c_str();
}

Int32 HDBMeta::getOpenMode(void) const
{
    return m_p_impl->m_n_open_mode;
}

Int32 HDBMeta::create(const Char * name, const Char * path, const HDBMetaMap * meta_info)
{
    if (strlen(name) >= HDB_NAME_LEN) {
        return DBERR_NAME_TOO_LONG;
    }

    std::string meta_path = path;
    meta_path += "\\";
    meta_path += name;
    meta_path += HDB_META_FILE_SUFFIX;

    FILE * fp = fopen(meta_path.c_str(), "r");
    if (NULL != fp) {
        fclose(fp);
        return DBERR_DB_EXISTED;
    }

    fp = fopen(meta_path.c_str(), "wb");
    if (NULL == fp) {
        return DBERR_CREATE_FILE_FAILED;
    }

    HDBMetaMap new_meta_info;
    if (NULL != meta_info) {
        memcpy(&new_meta_info, meta_info, sizeof(HDBMetaMap));
        strncpy(new_meta_info.db_name, name, HDB_NAME_LEN);
        new_meta_info.calcOffset();
    }
    else {
        new_meta_info.createDefault(name);
    }
    
    fwrite(&new_meta_info, sizeof(new_meta_info), 1, fp);

    UInt32 buf_size = new_meta_info.meta_size - sizeof(new_meta_info);
    Char * buf = new Char[buf_size];
    memset(buf, 0, buf_size);
    fwrite(buf, buf_size, 1, fp);
    delete[] buf;

    fclose(fp);

     return DB_SUCCESS;
}

Int32 HDBMeta::open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode)
{
    return m_p_impl->open(db_name, db_path, open_mode);
}

void HDBMeta::close(void)
{
    m_p_impl->close();
}

Int32 HDBMeta::reconnect(void)
{
    return m_p_impl->reconnect();
}

void HDBMeta::print(void) const
{
    return m_p_impl->print();
}

/********************************************************
*  枚举                                                *
********************************************************/

Int32 HDBMeta::findEnumGroup(const Char * group_name) const
{
    return m_p_impl->findEnumGroup(group_name);
}

HDBEnumGroupMap * HDBMeta::getEnumGroup(UInt16 index) const
{
    return m_p_impl->getEnumGroup(index);
}

Int32 HDBMeta::addEnumGroup(const Char * group_name)
{
    return m_p_impl->addEnumGroup(group_name);
}

Int32 HDBMeta::delEnumGroup(const Char * group_name)
{
    return m_p_impl->delEnumGroup(group_name);
}

Int32 HDBMeta::delEnumGroup(UInt16 index)
{
    return m_p_impl->delEnumGroup(index);
}

Int32 HDBMeta::findEnumItem(const Char * group_name, const Char * item_name) const
{
    return m_p_impl->findEnumItem(group_name, item_name);
}

Int32 HDBMeta::findEnumItem(UInt16 group_index, const Char * item_name) const
{
    return m_p_impl->findEnumItem(group_index, item_name);
}

Int32 HDBMeta::findEnumItem(HDBEnumGroupMap * group, const Char * item_name) const
{
    return m_p_impl->findEnumItem(group, item_name);
}

HDBEnumItemMap * HDBMeta::getEnumItem(UInt16 global_index) const
{
    return m_p_impl->getEnumItem(global_index);
}

HDBEnumItemMap * HDBMeta::getEnumItem(UInt16 group_index, UInt16 item_index) const
{
    return m_p_impl->getEnumItem(group_index, item_index);
}

Int32 HDBMeta::addEnumItem(HDBEnumGroupMap * group, const HDBEnumItemMap * item)
{
    return m_p_impl->addEnumItem(group, item);
}

Int32 HDBMeta::delEnumItem(HDBEnumGroupMap * group, const Char * item_name)
{
    return m_p_impl->delEnumItem(group, item_name);
}

Int32 HDBMeta::delEnumItem(HDBEnumGroupMap * group, UInt16 item_index)
{
    return m_p_impl->delEnumItem(group, item_index);
}

/********************************************************
*  位串                                                *
********************************************************/

Int32 HDBMeta::findBitsGroup(const Char * group_name) const
{
    return m_p_impl->findBitsGroup(group_name);
}

HDBBitsGroupMap * HDBMeta::getBitsGroup(UInt16 index) const
{
    return m_p_impl->getBitsGroup(index);
}

Int32 HDBMeta::addBitsGroup(const Char * group_name)
{
    return m_p_impl->addBitsGroup(group_name);
}

Int32 HDBMeta::delBitsGroup(const Char * group_name)
{
    return m_p_impl->delBitsGroup(group_name);
}

Int32 HDBMeta::delBitsGroup(UInt16 index)
{
    return m_p_impl->delBitsGroup(index);
}

Int32 HDBMeta::findBitsItem(const Char * group_name, const Char * item_name) const
{
    return m_p_impl->findBitsItem(group_name, item_name);
}

Int32 HDBMeta::findBitsItem(UInt16 group_index, const Char * item_name) const
{
    return m_p_impl->findBitsItem(group_index, item_name);
}

Int32 HDBMeta::findBitsItem(HDBBitsGroupMap * group, const Char * item_name) const
{
    return m_p_impl->findBitsItem(group, item_name);
}

HDBBitsItemMap * HDBMeta::getBitsItem(UInt16 global_index) const
{
    return m_p_impl->getBitsItem(global_index);
}

HDBBitsItemMap * HDBMeta::getBitsItem(UInt16 group_index, UInt16 item_index) const
{
    return m_p_impl->getBitsItem(group_index, item_index);
}

Int32 HDBMeta::addBitsItem(HDBBitsGroupMap * group, const HDBBitsItemMap * item)
{
    return m_p_impl->addBitsItem(group, item);
}

Int32 HDBMeta::delBitsItem(HDBBitsGroupMap * group, const Char * item_name)
{
    return m_p_impl->delBitsItem(group, item_name);
}

Int32 HDBMeta::delBitsItem(HDBBitsGroupMap * group, UInt16 item_index)
{
    return m_p_impl->delBitsItem(group, item_index);
}

/********************************************************
*  结构                                                *
********************************************************/

Int32 HDBMeta::findStructGroup(const Char * group_name) const
{
    return m_p_impl->findStructGroup(group_name);
}

HDBStructGroupMap * HDBMeta::getStructGroup(UInt16 index) const
{
    return m_p_impl->getStructGroup(index);
}

Int32 HDBMeta::addStructGroup(const Char * group_name)
{
    return m_p_impl->addStructGroup(group_name);
}

Int32 HDBMeta::delStructGroup(const Char * group_name)
{
    return m_p_impl->delStructGroup(group_name);
}

Int32 HDBMeta::delStructGroup(UInt16 index)
{
    return m_p_impl->delStructGroup(index);
}

Int32 HDBMeta::findStructItem(const Char * group_name, const Char * item_name) const
{
    return m_p_impl->findStructItem(group_name, item_name);
}

Int32 HDBMeta::findStructItem(UInt16 group_index, const Char * item_name) const
{
    return m_p_impl->findStructItem(group_index, item_name);
}

Int32 HDBMeta::findStructItem(HDBStructGroupMap * group, const Char * item_name) const
{
    return m_p_impl->findStructItem(group, item_name);
}

HDBStructItemMap * HDBMeta::getStructItem(UInt16 global_index) const
{
    return m_p_impl->getStructItem(global_index);
}

HDBStructItemMap * HDBMeta::getStructItem(UInt16 group_index, UInt16 item_index) const
{
    return m_p_impl->getStructItem(group_index, item_index);
}

Int32 HDBMeta::addStructItem(HDBStructGroupMap * group, const HDBStructItemMap * item)
{
    return m_p_impl->addStructItem(group, item);
}

Int32 HDBMeta::delStructItem(HDBStructGroupMap * group, const Char * item_name)
{
    return m_p_impl->delStructItem(group, item_name);
}

Int32 HDBMeta::delStructItem(HDBStructGroupMap * group, UInt16 item_index)
{
    return m_p_impl->delStructItem(group, item_index);
}

/********************************************************
*  表域                                                *
********************************************************/

Int32 HDBMeta::findTableGroup(const Char * group_name) const
{
    return m_p_impl->findTableGroup(group_name);
}

HDBTableGroupMap * HDBMeta::getTableGroup(UInt16 index) const
{
    return m_p_impl->getTableGroup(index);
}

Int32 HDBMeta::addTableGroup(const Char * group_name)
{
    return m_p_impl->addTableGroup(group_name);
}

Int32 HDBMeta::delTableGroup(const Char * group_name)
{
    return m_p_impl->delTableGroup(group_name);
}

Int32 HDBMeta::delTableGroup(UInt16 index)
{
    return m_p_impl->delTableGroup(index);
}

Int32 HDBMeta::findFieldItem(const Char * group_name, const Char * item_name) const
{
    return m_p_impl->findFieldItem(group_name, item_name);
}

Int32 HDBMeta::findFieldItem(UInt16 group_index, const Char * item_name) const
{
    return m_p_impl->findFieldItem(group_index, item_name);
}

Int32 HDBMeta::findFieldItem(HDBTableGroupMap * group, const Char * item_name) const
{
    return m_p_impl->findFieldItem(group, item_name);
}

HDBFieldItemMap * HDBMeta::getFieldItem(UInt16 global_index) const
{
    return m_p_impl->getFieldItem(global_index);
}

HDBFieldItemMap * HDBMeta::getFieldItem(UInt16 group_index, UInt16 item_index) const
{
    return m_p_impl->getFieldItem(group_index, item_index);
}

Int32 HDBMeta::addFieldItem(HDBTableGroupMap * group, const HDBFieldItemMap * item)
{
    return m_p_impl->addFieldItem(group, item);
}

Int32 HDBMeta::delFieldItem(HDBTableGroupMap * group, const Char * item_name)
{
    return m_p_impl->delFieldItem(group, item_name);
}

Int32 HDBMeta::delFieldItem(HDBTableGroupMap * group, UInt16 item_index)
{
    return m_p_impl->delFieldItem(group, item_index);
}

Int32 HDBMeta::addRelContain(const Char * parent_table_name[HDB_NAME_LEN],
    UInt16 parent_table_num,
    const Char * child_table_name,
    const Char * parent_field_name,
    const Char * child_field_name,
    Bool symbiotic)
{
    return m_p_impl->addRelContain(parent_table_name, parent_table_num, child_table_name, parent_field_name, child_field_name, symbiotic);
}

Int32 HDBMeta::delRelContain(const Char * parent_table_name[HDB_NAME_LEN],
    UInt16 parent_table_num,
    const Char * child_table_name,
    const Char * parent_field_name,
    const Char * child_field_name)
{
    return m_p_impl->delRelContain(parent_table_name, parent_table_num, child_table_name, parent_field_name, child_field_name);
}

Int32 HDBMeta::addRelRefer(const Char * parent_table_name,
    const Char * child_table_name,
    const Char * parent_field_name)
{
    return m_p_impl->addRelRefer(parent_table_name, child_table_name, parent_field_name);
}

Int32 HDBMeta::delRelRefer(const Char * parent_table_name,
    const Char * child_table_name,
    const Char * parent_field_name)
{
    return m_p_impl->delRelRefer(parent_table_name, child_table_name, parent_field_name);
}

/********************************************************
*  对象实体空间的计算分配                              *
********************************************************/
Int32 HDBMeta::allocEntity(void)
{
    return m_p_impl->allocEntity();
}

/********************************************************
*  生成头文件 HDBMetaGenerateHeader.cpp                *
********************************************************/
Int32 HDBMeta::generateHeader(const Char * path) const
{
    return m_p_impl->generateHeader(path);
}