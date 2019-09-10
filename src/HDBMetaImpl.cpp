
/**
 *  @file       HDBMetaImpl.cpp
 */

#include "HDBMetaImpl.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBError.h"
#include "HDBMetaGenerateHeader.h"

#include <stdio.h>
#include <string.h>

using namespace boost::interprocess;

HDBMetaImpl::HDBMetaImpl()
    : m_str_db_path(""),
    m_str_db_name(""),
    m_n_open_mode(OPEN_MODE_READONLY),
    m_p_file_map(NULL),
    m_p_mapped_region(NULL),
    m_p_meta_map(NULL),
    m_p_meta_address(NULL)
{

}

HDBMetaImpl::~HDBMetaImpl()
{
    clear();
}

void HDBMetaImpl::clear(void)
{
    HDBDELETEPOINTER(m_p_mapped_region);
    HDBDELETEPOINTER(m_p_file_map);
    m_p_meta_map = NULL;
    m_p_meta_address = NULL;
}


Int32 HDBMetaImpl::open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode)
{
    m_str_db_name = db_name;
    m_str_db_path = db_path;
    m_n_open_mode = open_mode;
    return reconnect();
}

void HDBMetaImpl::close(void)
{
    clear();
}

Int32 HDBMetaImpl::reconnect(void)
{
    clear();
    switch (m_n_open_mode) {
    case OPEN_MODE_READONLY:
        return openDb(read_only);
    case OPEN_MODE_READWRITE:
        return openDb(read_write);
    default:
        return DBERR_INVALID_OPEN_MODE;
    }
}

Int32 HDBMetaImpl::generateHeader(const Char * path) const
{
    HDBMetaGenerateHeader gen(path, this);
    return gen.generate();
}

Int32 HDBMetaImpl::openDb(int open_mode)
{
    std::string meta_path = m_str_db_path;
    meta_path += DIR_SEPARATOR;
    meta_path += m_str_db_name;
    meta_path += HDB_META_FILE_SUFFIX;

    FILE * fp = fopen(meta_path.c_str(), "rb");
    if (NULL == fp) {
        return DBERR_DB_NOT_EXISTED;
    }
    fclose(fp);

    m_p_file_map = new file_mapping(meta_path.c_str(), (mode_t)open_mode);
    m_p_mapped_region = new mapped_region(*m_p_file_map, (mode_t)open_mode);

    m_p_meta_address = m_p_mapped_region->get_address();
    m_p_meta_map = static_cast<HDBMetaMap *>(m_p_meta_address);
    
    return DB_SUCCESS;
}


void HDBMetaImpl::print(void) const
{
    if (NULL == m_p_meta_map) {
        return;
    }

    printf("\n-------------------------------------------------------------------\n");

    printf("DB Name = %16s    Meta size = %8d\n", m_p_meta_map->db_name, m_p_meta_map->meta_size);
    
    print_header("Enum Group", m_p_meta_map->enum_group);
    print_header("Enum Item", m_p_meta_map->enum_item);
    print_header_enum();

    print_header("Bits Group", m_p_meta_map->bits_group);
    print_header("Bits Item", m_p_meta_map->bits_item);
    print_header_bits();

    print_header("Struct Group", m_p_meta_map->struct_group);
    print_header("Struct Item", m_p_meta_map->struct_item);
    print_header_struct();

    print_header("Table Group", m_p_meta_map->table_group);
    print_header("Field Item", m_p_meta_map->field_item);
    print_header_table();

    print_header("Relation Group", m_p_meta_map->relation);
    print_header_relation();

}

void HDBMetaImpl::print_header(const Char * name, const HDBGroupItemMap & header) const
{
    printf("%-16s:    Capacity = %-5d    Used size = %-5d    Offset = 0x%08X    Free index = %-5d\n", 
        name, header.capacity, header.used_size, header.head_offset, header.free_index);
}

void HDBMetaImpl::print_header_enum(void) const
{
    HDBEnumGroupMap * group_header = getEnumGroupMapHead();
    HDBEnumItemMap * item_header = getEnumItemMapHead();

    for (UInt16 i = 0; i < m_p_meta_map->enum_group.capacity; i++) {
        HDBEnumGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }
        printf("    %-16s    Item num = %-5d    Item head = %-5d\n", group->name, group->item_num, group->item_head);
        Int32 item_index = group->item_head;
        while (item_index >= 0) {
            HDBEnumItemMap * item = item_header + item_index;
            printf("        [%-5d]: %-16s    Group = %-5d    Prev = %-5d    Next = %-5d    Value = %-8d\n", 
                item_index, item->name, item->group_index, item->item_prev, item->item_next, item->value);

            item_index = item->item_next;
        }
    }
}

void HDBMetaImpl::print_header_bits(void) const
{
    HDBBitsGroupMap * group_header = getBitsGroupMapHead();
    HDBBitsItemMap * item_header = getBitsItemMapHead();

    for (UInt16 i = 0; i < m_p_meta_map->bits_group.capacity; i++) {
        HDBBitsGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }

        printf("    %-16s\tItem num = %-5d    Item head = %-5d    Type = %-4d\n", 
            group->name, group->item_num, group->item_head, group->type);
        Int32 item_index = group->item_head;
        while (item_index >= 0) {
            HDBBitsItemMap * item = item_header + item_index;
            printf("        [%-5d]: %-16s    Group = %-5d    Prev = %-5d    Next = %-5d    Size = %-2d\n",
                item_index, item->name, item->group_index, item->item_prev, item->item_next, item->size);

            item_index = item->item_next;
        }
    }
}

void HDBMetaImpl::print_header_struct(void) const
{
    HDBStructGroupMap * group_header = getStructGroupMapHead();
    HDBStructItemMap * item_header = getStructItemMapHead();

    for (UInt16 i = 0; i < m_p_meta_map->struct_group.capacity; i++) {
        HDBStructGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }

        printf("    %-16s    Item num = %-5d    Item head = %-5d    Size = %-4d\n", 
            group->name, group->item_num, group->item_head, group->size);
        Int32 item_index = group->item_head;
        while (item_index >= 0) {
            HDBStructItemMap * item = item_header + item_index;
            printf("        [%-5d]: %-16s    Group = %-5d    Prev = %-5d    Next = %-5d    Type = %-4d\n", 
                item_index, item->name, item->group_index, item->item_prev, item->item_next, item->type);

            item_index = item->item_next;
        }
    }
}

void HDBMetaImpl::print_header_table(void) const
{
    HDBTableGroupMap * group_header = getTableGroupMapHead();
    HDBFieldItemMap * item_header = getFieldItemMapHead();

    for (UInt16 i = 0; i < m_p_meta_map->table_group.capacity; i++) {
        HDBTableGroupMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }

        printf("    %-16s    Item num = %-5d    Item head = %-5d    ", group->name, group->item_num, group->item_head);
        printf("Offset = 0x%08X    Size = %-4d  Capacity = %-5d    Used = %-5d    Free = %-5d\n",
            group->object_offset, group->object_size, group->object_capacity, group->object_used_num, group->object_free_index);
        Int32 item_index = group->item_head;
        while (item_index >= 0) {
            HDBFieldItemMap * item = item_header + item_index;
            printf("        [%-5d]: %-16s    Group = %-5d    Prev = %-5d    Next = %-5d    ", 
                item_index, item->name, item->group_index, item->item_prev, item->item_next);
            printf("Offset = %-5d    Size = %-5d    Type = %-4d    Sub type = %-4d\n",
                item->offset, item->size, item->type, item->sub_type);
            
            item_index = item->item_next;
        }
    }
}

void HDBMetaImpl::print_header_relation(void) const
{
    HDBRelationMap * group_header = getRelationMapHead();
    HDBTableGroupMap * table_header = getTableGroupMapHead();
    HDBFieldItemMap * field_header = getFieldItemMapHead();

    for (UInt16 i = 0; i < m_p_meta_map->relation.capacity; i++) {
        HDBRelationMap * group = group_header + i;
        if (HDBMetaMap::isRecordEmpty(group)) {
            continue;
        }

        printf("    [%-5d]: Symbiotic = %d    Parent = %16s.%-16s\tChild = %16s.%-16s\tprev = %-5d\tnext = %-5d\n",
            i,
            group->symbiotic, table_header[group->parent_table].name, field_header[group->parent_field].name,
            (group->child_table >= 0) ? table_header[group->child_table].name : "---",
            (group->child_field >= 0) ? field_header[group->child_field].name : "---",
            group->prev, group->next);

    }
}
