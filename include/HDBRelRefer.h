
/**
 *  @file       HDBRelRefer.h
 */

#ifndef HDB_REL_REFER_H
#define HDB_REL_REFER_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBOid.h"

class HDB_DLL_EXPORT HDBRelRefer {
public:
    HDBRelRefer() {};
    ~HDBRelRefer() {};

    HDBOid refer;
};

#endif  //HDB_REL_REFER_H