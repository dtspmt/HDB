
/**
 *  @file       HDBConnection.h
 */

#ifndef HDB_CONNECTION_H
#define HDB_CONNECTION_H

#include "HDBExport.h"
#include "HDataTypes.h"
#include "HDBDefines.h"

class HDBMeta;
class HDBMetaMap;
class HDBConnectionImpl;

class HDB_DLL_EXPORT HDBConnection
{
public:
    HDBConnection();
    ~HDBConnection();

    Int32 open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode);
    Int32 close(void);
    Int32 reconnect(void);
    HDBMeta * getMeta(void);

private:
    HDBConnectionImpl * m_p_impl;
};



#endif  //HDB_CONNECTION_H