
/**
 *  @file       HDBMetaGenerateHeader.cpp
 */

#include "HDBMetaGenerateHeader.h"
#include "HDBMetaImpl.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"

#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;

HDBMetaGenerateHeader::HDBMetaGenerateHeader(const Char * path, const HDBMetaImpl * db_meta)
    : m_p_db_meta(db_meta),
    m_p_fp(NULL)
{
    if ((NULL == path) || (NULL == db_meta) || (NULL == db_meta->m_p_meta_map)) {
        return;
    }

    string header_path = path;
    header_path += DIR_SEPARATOR;
    header_path += db_meta->m_p_meta_map->db_name;
    header_path += HEADER_SUFFIX;

    m_p_fp = fopen(header_path.c_str(), "w");
    if (NULL == m_p_fp) {
        return;
    }
}

HDBMetaGenerateHeader::~HDBMetaGenerateHeader()
{
    if (NULL != m_p_fp) {
        fclose(m_p_fp);
        m_p_fp = NULL;
    }
}

Int32 HDBMetaGenerateHeader::generate(void)
{
    if ((NULL == m_p_fp) || (NULL == m_p_db_meta)) {
        return DBERR_INVALID_POINTER;
    }

    string header_macro = "DB_";
    header_macro += m_p_db_meta->m_p_meta_map->db_name;
    header_macro += "_H";
    transform(header_macro.begin(), header_macro.end(), header_macro.begin(), ::toupper);
    
    //重复引用
    fprintf(m_p_fp, "#ifndef %s\n"
        "#define %s\n\n", header_macro.c_str(), header_macro.c_str());

    //头文件
    fprintf(m_p_fp, "#include \"HDB/HDBOid.h\"\n");
    fprintf(m_p_fp, "#include \"HDB/HDBRelParent.h\"\n");
    fprintf(m_p_fp, "#include \"HDB/HDBRelChild.h\"\n");
    fprintf(m_p_fp, "#include \"HDB/HDBRelRefer.h\"\n");
    fprintf(m_p_fp, "\n");


    //名字空间
    fprintf(m_p_fp, "namespace dbns_%s {\n\n", m_p_db_meta->m_p_meta_map->db_name);

    fprintf(m_p_fp, "/** Enum defines **/\n");
    generateEnums();
    fprintf(m_p_fp, "/** Bit string defines **/\n");
    generateBits();
    fprintf(m_p_fp, "/** Struct defines **/\n");
    generateStructs();
    fprintf(m_p_fp, "/** Table defines **/\n");
    generateTables();

    //名字空间
    fprintf(m_p_fp, "}\n");

    //重复引用
    fprintf(m_p_fp, "\n#endif //%s\n", header_macro.c_str());

    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateEnums(void)
{
    UInt16 i = 0;

    HDBEnumGroupMap * group_header = m_p_db_meta->getEnumGroupMapHead();
    for (i = 0; i < m_p_db_meta->m_p_meta_map->enum_group.capacity; i++) {
        HDBEnumGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }
        Int32 ret = generateEnum(group);
        if (ret < 0) {
            return ret;
        }
    }
    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateBits(void)
{
    UInt16 i = 0;

    HDBBitsGroupMap * group_header = m_p_db_meta->getBitsGroupMapHead();
    for (i = 0; i < m_p_db_meta->m_p_meta_map->bits_group.capacity; i++) {
        HDBBitsGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }
        Int32 ret = generateBit(group);
        if (ret < 0) {
            return ret;
        }
    }
    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateStructs(void)
{
    UInt16 i = 0;

    HDBStructGroupMap * group_header = m_p_db_meta->getStructGroupMapHead();
    for (i = 0; i < m_p_db_meta->m_p_meta_map->struct_group.capacity; i++) {
        HDBStructGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }
        Int32 ret = generateStruct(group);
        if (ret < 0) {
            return ret;
        }
    }

    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateTables(void)
{
    UInt16 i = 0;

    HDBTableGroupMap * group_header = m_p_db_meta->getTableGroupMapHead();
    for (i = 0; i < m_p_db_meta->m_p_meta_map->table_group.capacity; i++) {
        HDBTableGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }
        Int32 ret = generateTable(group);
        if (ret < 0) {
            return ret;
        }
    }


    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateEnum(HDBEnumGroupMap * group)
{
    HDBEnumItemMap * item_header = m_p_db_meta->getEnumItemMapHead();

    fprintf(m_p_fp, "enum %s {\n", group->name);
    UInt16 i = 0;
    Int32 index = group->item_head;

    while (index >= 0) {
        HDBEnumItemMap * item = item_header + index;
        fprintf(m_p_fp, "    %s = %d,\n", item->name, item->value);
        index = item->item_next;
        i++;
    }

    if (i != group->item_num) {
        return DBERR_DB_ENUM_ITEM_NUM_NOT_MATCH;
    }

    fprintf(m_p_fp, "};\n\n");
    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateBit(HDBBitsGroupMap * group)
{
    HDBBitsItemMap * item_header = m_p_db_meta->getBitsItemMapHead();

    fprintf(m_p_fp, "struct %s {\n", group->name);
    UInt16 i = 0;
    Int32 index = group->item_head;

    const Char * bits_type = HDataTypeGetName(group->type);
    UInt8 bits_size = 0;
    switch (group->type) {
    case HDT_UINT8:
        bits_size = 8;
        break;
    case HDT_UINT16:
        bits_size = 16;
        break;
    case HDT_UINT32:
        bits_size = 32;
        break;
    case HDT_UINT64:
        bits_size = 64;
        break;
    default:
        return DBERR_DB_BITS_GROUP_INVALID_TYPE;
    }

    UInt8 total_size = 0;
    while (index >= 0) {
        HDBBitsItemMap * item = item_header + index;
        fprintf(m_p_fp, "    %s %s : %d;\n", bits_type, item->name, item->size);
        total_size += item->size;
        if (total_size > bits_size) {
            return DBERR_DB_BITS_ITEM_INVALID_SIZE;
        }
        index = item->item_next;
        i++;
    }

    if (i != group->item_num) {
        return DBERR_DB_BITS_ITEM_NUM_NOT_MATCH;
    }

    fprintf(m_p_fp, "};\n\n");
    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateStruct(HDBStructGroupMap * group)
{
    fprintf(m_p_fp, "struct %s {\n", group->name);
    HDBStructItemMap * item_header = m_p_db_meta->getStructItemMapHead();

    Int32 item_index = group->item_head;
    Int32 i = 0;

    while (item_index >= 0) {
        HDBStructItemMap * item = item_header + item_index;
        Int32 ret = generateStructItem(item->type, item->size, item->sub_type, item->name);
        if (ret < 0) {
            return ret;
        }

        item_index = item->item_next;
        i++;
    }

    if (i > group->item_num) {
        return DBERR_DB_STRUCT_ITEM_NUM_NOT_MATCH;
    }

    fprintf(m_p_fp, "};\n\n");
    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateTable(HDBTableGroupMap * group)
{
    fprintf(m_p_fp, "struct %s {\n", group->name);
    HDBFieldItemMap * item_header = m_p_db_meta->getFieldItemMapHead();

    Int32 item_index = group->item_head;
    Int32 i = 0;

    while (item_index >= 0) {
        HDBFieldItemMap * item = item_header + item_index;
        Int32 ret = generateStructItem(item->type, item->size, item->sub_type, item->name);
        if (ret < 0) {
            return ret;
        }

        item_index = item->item_next;
        i++;
    }

    if (i > group->item_num) {
        return DBERR_DB_FIELD_ITEM_NUM_NOT_MATCH;
    }

    fprintf(m_p_fp, "};\n\n");
    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateStructItem(UInt8 type, UInt32 size, Int32 sub_type, const Char * name)
{
    switch (type) {
    case HDT_BITS:
        return generateStructItemBits(type, size, sub_type, name);
    case HDT_STRUCT:
        return generateStructItemStruct(type, size, sub_type, name);
    default:
        break;
    }

    const Char * type_str = HDataTypeGetName(type);
    fprintf(m_p_fp, "    %s %s", type_str, name);
    if (size > 1) {
        fprintf(m_p_fp, "[%d]", size);
    }
    fprintf(m_p_fp, ";\n");

    return DB_SUCCESS;
}

Int32 HDBMetaGenerateHeader::generateStructItemBits(UInt8 type, UInt32 size, Int32 sub_type, const Char * name)
{
    HDBBitsGroupMap * group = m_p_db_meta->getBitsGroup(sub_type);
    if (NULL == group) {
        return DBERR_DB_BITS_GROUP_NOT_EXISTS;
    }

    fprintf(m_p_fp, "    struct %s %s", group->name, name);
    if (size > 1) {
        fprintf(m_p_fp, "[%d]", size);
    }
    fprintf(m_p_fp, ";\n");

    return DB_SUCCESS;

}

Int32 HDBMetaGenerateHeader::generateStructItemStruct(UInt8 type, UInt32 size, Int32 sub_type, const Char * name)
{
    HDBStructGroupMap * group = m_p_db_meta->getStructGroup(sub_type);
    if (NULL == group) {
        return DBERR_DB_BITS_GROUP_NOT_EXISTS;
    }

    fprintf(m_p_fp, "        struct %s %s", group->name, name);
    if (size > 1) {
        fprintf(m_p_fp, "[%d]", size);
    }
    fprintf(m_p_fp, ";\n");

    return DB_SUCCESS;
}