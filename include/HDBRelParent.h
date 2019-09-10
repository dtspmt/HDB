
/**
 *  @file       HDBRelParent.h
 */

#ifndef HDB_REL_PARENT_H
#define HDB_REL_PARENT_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"
#include "HDBOid.h"

class HDB_DLL_EXPORT HDBRelParent
{
public:
    HDBRelParent() 
        : symbiotic(false),
        child_num(0)
    {};

    ~HDBRelParent() {}

    Bool symbiotic;
    UInt16 child_num;
    HDBOid first_child;
};



#endif  //HDB_REL_PARENT_H