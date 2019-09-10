
/**
 *  @file       HDataTypes.h
 */

#ifndef H_DATA_TYPES_H
#define H_DATA_TYPES_H

#include <string>

enum {
    HDT_UNKNOWN                     = 0,                        
    HDT_MIN                         = 10,   

    HDT_SIMPLE_MIN = HDT_MIN,           
    HDT_BOOL = HDT_SIMPLE_MIN,          
    HDT_CHAR,                           
    HDT_INT8,                           
    HDT_UINT8,                          
    HDT_INT16,                          
    HDT_UINT16,                         
    HDT_INT32,                          
    HDT_UINT32,                         
    HDT_INT64,                          
    HDT_UINT64,                         
    HDT_FLOAT,                          
    HDT_DOUBLE,                         
    HDT_STRING,                         
    HDT_STIME,                          
    HDT_MSTIME,                         
    HDT_SIMPLE_MAX = HDT_MSTIME,        

    HDT_COMPLEX_MIN                 = 40,                    
    HDT_ENUM = HDT_COMPLEX_MIN,         
    HDT_BITS,                           
    HDT_STRUCT,                         
    HDT_COMPLEX_MAX = HDT_STRUCT,       

    HDT_RELATION_MIN                = 100,
    HDT_OID = HDT_RELATION_MIN,
    HDT_REFER,
    HDT_PARENT,
    HDT_CHILD,
    HDT_RELATION_MAX = HDT_CHILD,

    HDT_MAX = HDT_RELATION_MAX

};

typedef bool Bool;
typedef char Char;
typedef char Int8;
typedef unsigned char UInt8;
typedef short Int16;
typedef unsigned short UInt16;
typedef int Int32;
typedef unsigned int UInt32;
typedef long long Int64;
typedef unsigned long long UInt64;
typedef float Float;
typedef double Double;
typedef unsigned int STime;
typedef unsigned long long MSTime;


inline const Char * HDataTypeGetName(Int32 type) {
    switch (type) {
    case HDT_BOOL:
        return "Bool";
    case HDT_CHAR:
        return "Char";
    case HDT_INT8:
        return "Int8";
    case HDT_UINT8:
        return "UInt8";
    case HDT_INT16:
        return "Int16";
    case HDT_UINT16:
        return "UInt16";
    case HDT_INT32:
        return "Int32";
    case HDT_UINT32:
        return "UInt32";
    case HDT_INT64:
        return "Int64";
    case HDT_UINT64:
        return "UInt64";
    case HDT_FLOAT:
        return "Float";
    case HDT_DOUBLE:
        return "Double";
    case HDT_STRING:
        return "Char";
    case HDT_STIME:
        return "STime";
    case HDT_MSTIME:
        return "MSTime";
    case HDT_ENUM:
        return "Int32";
    case HDT_OID:
        return "HDBOid";
    case HDT_REFER:
        return "HDBRelRefer";
    case HDT_PARENT:
        return "HDBRelParent";
    case HDT_CHILD:
        return "HDBRelChild";
    default:
        return "";
    }
}

#endif  //H_DATA_TYPES_H