
/**
*  @file       HDBOid.h
*/

#ifndef HDB_OID_H
#define HDB_OID_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"

class HDB_DLL_EXPORT HDBOid
{
public:
    HDBOid() 
        : index(HDB_INVALID_OBJECT_INDEX),
        table_index(HDB_INVALID_TABLE_INDEX)
    {}
    ~HDBOid() {}

    UInt32 index;           //�ڶ�����е�ȫ���±�
    UInt16 table_index;     //���±�
};

#endif  //HDB_OID_H