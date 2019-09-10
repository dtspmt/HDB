
/**
 *  @file       HDBError.h
 */

#ifndef HDB_ERROR_H
#define HDB_ERROR_H

enum {
    DB_SUCCESS = 0,
    DBERR_NAME_TOO_LONG = -1000,                //名称太长
    DBERR_INSUFFICIENT_MEMPRY,                  //内存不够
    DBERR_INVALID_POINTER,                      //空指针

    DBERR_DB_SIZE_TOO_SMALL,                    //数据库太小
    DBERR_DB_EXISTED,                           //数据库已存在
    DBERR_DB_NOT_EXISTED,                       //数据库不存在
    DBERR_CREATE_FILE_FAILED,                   //创建文件失败
    DBERR_INVALID_OPEN_MODE,                    //数据库打开方式无效
    DBERR_DB_NOT_MAPPED,                        //数据库未装载

    DBERR_DB_ENUM_GROUP_TOO_MORE,               //枚举组满
    DBERR_DB_ENUM_GROUP_EXISTS,                 //枚举组已存在
    DBERR_DB_ENUM_GROUP_NOT_EXISTS,             //枚举组不存在
    DBERR_DB_ENUM_GROUP_EMPTY,                  //枚举组为空
    DBERR_DB_ENUM_GROUP_NOT_EMPTY,              //枚举组非空
    DBERR_DB_ENUM_GROUP_INVALID_FREE,           //枚举组空闲下标无效
    DBERR_DB_ENUM_GROUP_INVALID_ITEM_INDEX,     //枚举组枚举项下标无效
    DBERR_DB_ENUM_ITEM_TOO_MORE,                //枚举项满
    DBERR_DB_ENUM_ITEM_EXISTS,                  //枚举项已存在
    DBERR_DB_ENUM_ITEM_NOT_EXISTS,              //枚举项不存在
    DBERR_DB_ENUM_ITEM_EMPTY,                   //枚举项为空
    DBERR_DB_ENUM_ITEM_NOT_EMPRY,               //枚举项非空
    DBERR_DB_ENUM_ITEM_INVALID_FREE,            //枚举项空闲下标无效
    DBERR_DB_ENUM_ITEM_NUM_NOT_MATCH,           //枚举项数量不匹配（遍历的数量与组中记录不一致）

    DBERR_DB_BITS_GROUP_TOO_MORE,               //位串组满
    DBERR_DB_BITS_GROUP_EXISTS,                 //位串组已存在
    DBERR_DB_BITS_GROUP_NOT_EXISTS,             //位串组不存在
    DBERR_DB_BITS_GROUP_EMPTY,                  //位串组为空
    DBERR_DB_BITS_GROUP_NOT_EMPTY,              //位串组非空
    DBERR_DB_BITS_GROUP_INVALID_FREE,           //位串组空闲下标无效
    DBERR_DB_BITS_GROUP_INVALID_ITEM_INDEX,     //位串组位串项下标无效
    DBERR_DB_BITS_GROUP_INVALID_TYPE,           //位串组类型无效（不属于UInt8/UInt16/UInt32/UInt64）
    DBERR_DB_BITS_ITEM_TOO_MORE,                //位串项满
    DBERR_DB_BITS_ITEM_EXISTS,                  //位串项已存在
    DBERR_DB_BITS_ITEM_NOT_EXISTS,              //位串项不存在
    DBERR_DB_BITS_ITEM_EMPTY,                   //位串项为空
    DBERR_DB_BITS_ITEM_NOT_EMPTY,               //位串项非空
    DBERR_DB_BITS_ITEM_INVALID_FREE,            //位串项空闲下标无效
    DBERR_DB_BITS_ITEM_NUM_NOT_MATCH,           //位串项数量不匹配（遍历的数量与组中记录不一致）
    DBERR_DB_BITS_ITEM_INVALID_SIZE,            //位串项大小无效（位串项累加大小超过位串组大小）
    
    DBERR_DB_STRUCT_GROUP_TOO_MORE,             //结构组满
    DBERR_DB_STRUCT_GROUP_EXISTS,               //结构组已存在
    DBERR_DB_STRUCT_GROUP_NOT_EXISTS,           //结构组不存在
    DBERR_DB_STRUCT_GROUP_EMPTY,                //结构组为空
    DBERR_DB_STRUCT_GROUP_NOT_EMPTY,            //结构组非空
    DBERR_DB_STRUCT_GROUP_INVALID_FREE,         //结构组空闲下标无效
    DBERR_DB_STRUCT_GROUP_INVALID_ITEM_INDEX,   //结构组结构项下标无效
    DBERR_DB_STRUCT_ITEM_TOO_MORE,              //结构项满
    DBERR_DB_STRUCT_ITEM_EXISTS,                //结构项已存在
    DBERR_DB_STRUCT_ITEM_NOT_EXISTS,            //结构项不存在
    DBERR_DB_STRUCT_ITEM_EMPTY,                 //结构项为空
    DBERR_DB_STRUCT_ITEM_NOT_EMPTY,             //结构项非空
    DBERR_DB_STRUCT_ITEM_INVALID_FREE,          //结构项空闲下标无效
    DBERR_DB_STRUCT_ITEM_NUM_NOT_MATCH,         //结构项数量不匹配（遍历的数量与组中记录不一致）

    DBERR_DB_TABLE_GROUP_TOO_MORE,              //表组满
    DBERR_DB_TABLE_GROUP_EXISTS,                //表组已存在
    DBERR_DB_TABLE_GROUP_NOT_EXISTS,            //表组不存在
    DBERR_DB_TABLE_GROUP_EMPTY,                 //表组为空
    DBERR_DB_TABLE_GROUP_NOT_EMPTY,             //表组非空
    DBERR_DB_TABLE_GROUP_INVALID_FREE,          //表组空闲下标无效
    DBERR_DB_TABLE_GROUP_INVALID_ITEM_INDEX,    //表组域项下标无效
    DBERR_DB_FIELD_ITEM_TOO_MORE,               //域项满
    DBERR_DB_FIELD_ITEM_EXISTS,                 //域项已存在
    DBERR_DB_FIELD_ITEM_NOT_EXISTS,             //域项不存在
    DBERR_DB_FIELD_ITEM_EMPTY,                  //域项为空
    DBERR_DB_FIELD_ITEM_NOT_EMPTY,              //域项非空
    DBERR_DB_FIELD_ITEM_INVALID_FREE,           //域项空闲下标无效
    DBERR_DB_FIELD_ITEM_NUM_NOT_MATCH,          //域项数量不匹配（遍历的数量与组中记录不一致）

    DBERR_DB_RELATION_ADD_FAILED,               //增加表域关系失败
    DBERR_DB_RELATION_TOO_MORE,                 //表域关系满
    DBERR_DB_RELATION_INVALID_INDEX,            //表域关系下标无效
    DBERR_DB_RELATION_NOT_EXISTS,               //表域关系不存在
    DBERR_DB_RELATION_EMPTY,                    //表域关系为空
    DBERR_DB_RELATION_NOT_EMPTY,                //表域关系非空
    DBERR_DB_RELATION_MULTI_PARENT_NOT_SYMBIOTIC,   //多父未共生

    DBERR_DB_INVALID_FIELD_SIZE,                //
};

#endif  //HDB_ERROR_H