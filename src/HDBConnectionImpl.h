
/**
 *  @file       HDBConnectionImpl.h
 */

#ifndef HDB_CONNECTION_IMPL_H
#define HDB_CONNECTION_IMPL_H

#include "HDB/HDataTypes.h"
#include "HDB/HDBDefines.h"

#include <string>
using namespace std;

class HDBMeta;

class HDBConnectionImpl
{
public:
    HDBConnectionImpl();
    ~HDBConnectionImpl();

    Int32 open(const Char * db_name, const Char * db_path, OPEN_MODE open_mode);
    Int32 close(void);
    Int32 reconnect(void);
    HDBMeta * getMeta(void);

private:
    void clear(void);

private:
    std::string m_str_db_path;          //数据库文件路径
    std::string m_str_db_name;          //数据库名称
    Int32 m_n_open_mode;                //打开模式

    HDBMeta * m_p_meta;                 //元数据
};


#endif  //HDB_CONNECTION_IMPL_H