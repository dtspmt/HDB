
/**
*  @file       HDBRelChild.h
*/

#ifndef HDB_REL_CHILD_H
#define HDB_REL_CHILD_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"
#include "HDBOid.h"

class HDB_DLL_EXPORT HDBRelChild
{
public:
    HDBRelChild()
    {};

    ~HDBRelChild() {}

    HDBOid parent;
};



#endif  //HDB_REL_CHILD_H