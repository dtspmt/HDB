
/**
 *  @file   HDBMetaGenerateHeader.h
 */

#ifndef HDB_META_GENERATE_HEADER_H
#define HDB_META_GENERATE_HEADER_H

#include "HDB/HDataTypes.h"
#include <stdio.h>

class HDBMetaImpl;
class HDBMetaMap;
class HDBBitsGroupMap;
class HDBEnumGroupMap;
class HDBStructGroupMap;
class HDBTableGroupMap;

class HDBMetaGenerateHeader
{
public:
    HDBMetaGenerateHeader(const Char * path, const HDBMetaImpl * db_map);
    ~HDBMetaGenerateHeader();

    Int32 generate(void);

private:
    Int32 generateEnums(void);
    Int32 generateBits(void);
    Int32 generateStructs(void);
    Int32 generateTables(void);

    Int32 generateEnum(HDBEnumGroupMap * group);
    Int32 generateBit(HDBBitsGroupMap * group);
    Int32 generateStruct(HDBStructGroupMap * group);
    Int32 generateTable(HDBTableGroupMap * group);

    Int32 generateStructItem(UInt8 type, UInt32 size, Int32 sub_type, const Char * name);
    Int32 generateStructItemBits(UInt8 type, UInt32 size, Int32 sub_type, const Char * name);
    Int32 generateStructItemStruct(UInt8 type, UInt32 size, Int32 sub_type, const Char * name);
private:
    FILE * m_p_fp;
    const HDBMetaImpl * m_p_db_meta;
};


#endif  //HDB_META_GENERATE_HEADER_H