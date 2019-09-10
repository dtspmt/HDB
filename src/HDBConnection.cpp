
/**
*  @file       HDBConnection.cpp
*/

#include "HDB/HDBConnection.h"
#include "HDBConnectionImpl.h"
#include "HDB/HDBError.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBMeta.h"


HDBConnection::HDBConnection()
    : m_p_impl(NULL)
{
    m_p_impl = new HDBConnectionImpl;
}

HDBConnection::~HDBConnection()
{
    HDBDELETEPOINTER(m_p_impl);
}

Int32 HDBConnection::open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode)
{
    return m_p_impl->open(db_name, db_path, open_mode);
}

Int32 HDBConnection::close(void)
{
    return m_p_impl->close();
}

Int32 HDBConnection::reconnect(void)
{
    return m_p_impl->reconnect();
}

HDBMeta * HDBConnection::getMeta(void)
{
    return m_p_impl->getMeta();
}