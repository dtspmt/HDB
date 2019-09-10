
/**
  *      @file       HDBConnectionImpl.cpp
  */

#include "HDBConnectionImpl.h"
#include "HDB/HDBError.h"
#include "HDB/HDBMetaMap.h"
#include "HDB/HDBMeta.h"

HDBConnectionImpl::HDBConnectionImpl()
    : m_str_db_path(""),
    m_str_db_name(""),
    m_n_open_mode(OPEN_MODE_READONLY),
    m_p_meta(NULL)
{

}

HDBConnectionImpl::~HDBConnectionImpl()
{
    clear();
}

void HDBConnectionImpl::clear(void)
{
    HDBDELETEPOINTER(m_p_meta);
}

Int32 HDBConnectionImpl::open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode)
{
    clear();

    m_p_meta = new HDBMeta;

    Int32 ret = m_p_meta->open(db_name, db_path, open_mode);
    if (ret != DB_SUCCESS) {
        return ret;
    }

    m_str_db_name = db_name;
    m_str_db_path = db_path;
    m_n_open_mode = open_mode;

    return DB_SUCCESS;
}

Int32 HDBConnectionImpl::close(void)
{
    if (NULL != m_p_meta) {
        m_p_meta->close();
    }

    return DB_SUCCESS;
}

Int32 HDBConnectionImpl::reconnect(void)
{
    if (NULL == m_p_meta) {
        return DBERR_INVALID_POINTER;
    }


    Int32 ret = m_p_meta->reconnect();
    if (ret != DB_SUCCESS) {
        return ret;
    }

    return DB_SUCCESS;
}

HDBMeta * HDBConnectionImpl::getMeta(void)
{
    return m_p_meta;
}