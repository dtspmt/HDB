
/**
 *  @file       HDBError.h
 */

#ifndef HDB_ERROR_H
#define HDB_ERROR_H

enum {
    DB_SUCCESS = 0,
    DBERR_NAME_TOO_LONG = -1000,                //����̫��
    DBERR_INSUFFICIENT_MEMPRY,                  //�ڴ治��
    DBERR_INVALID_POINTER,                      //��ָ��

    DBERR_DB_SIZE_TOO_SMALL,                    //���ݿ�̫С
    DBERR_DB_EXISTED,                           //���ݿ��Ѵ���
    DBERR_DB_NOT_EXISTED,                       //���ݿⲻ����
    DBERR_CREATE_FILE_FAILED,                   //�����ļ�ʧ��
    DBERR_INVALID_OPEN_MODE,                    //���ݿ�򿪷�ʽ��Ч
    DBERR_DB_NOT_MAPPED,                        //���ݿ�δװ��

    DBERR_DB_ENUM_GROUP_TOO_MORE,               //ö������
    DBERR_DB_ENUM_GROUP_EXISTS,                 //ö�����Ѵ���
    DBERR_DB_ENUM_GROUP_NOT_EXISTS,             //ö���鲻����
    DBERR_DB_ENUM_GROUP_EMPTY,                  //ö����Ϊ��
    DBERR_DB_ENUM_GROUP_NOT_EMPTY,              //ö����ǿ�
    DBERR_DB_ENUM_GROUP_INVALID_FREE,           //ö��������±���Ч
    DBERR_DB_ENUM_GROUP_INVALID_ITEM_INDEX,     //ö����ö�����±���Ч
    DBERR_DB_ENUM_ITEM_TOO_MORE,                //ö������
    DBERR_DB_ENUM_ITEM_EXISTS,                  //ö�����Ѵ���
    DBERR_DB_ENUM_ITEM_NOT_EXISTS,              //ö�������
    DBERR_DB_ENUM_ITEM_EMPTY,                   //ö����Ϊ��
    DBERR_DB_ENUM_ITEM_NOT_EMPRY,               //ö����ǿ�
    DBERR_DB_ENUM_ITEM_INVALID_FREE,            //ö��������±���Ч
    DBERR_DB_ENUM_ITEM_NUM_NOT_MATCH,           //ö����������ƥ�䣨���������������м�¼��һ�£�

    DBERR_DB_BITS_GROUP_TOO_MORE,               //λ������
    DBERR_DB_BITS_GROUP_EXISTS,                 //λ�����Ѵ���
    DBERR_DB_BITS_GROUP_NOT_EXISTS,             //λ���鲻����
    DBERR_DB_BITS_GROUP_EMPTY,                  //λ����Ϊ��
    DBERR_DB_BITS_GROUP_NOT_EMPTY,              //λ����ǿ�
    DBERR_DB_BITS_GROUP_INVALID_FREE,           //λ��������±���Ч
    DBERR_DB_BITS_GROUP_INVALID_ITEM_INDEX,     //λ����λ�����±���Ч
    DBERR_DB_BITS_GROUP_INVALID_TYPE,           //λ����������Ч��������UInt8/UInt16/UInt32/UInt64��
    DBERR_DB_BITS_ITEM_TOO_MORE,                //λ������
    DBERR_DB_BITS_ITEM_EXISTS,                  //λ�����Ѵ���
    DBERR_DB_BITS_ITEM_NOT_EXISTS,              //λ�������
    DBERR_DB_BITS_ITEM_EMPTY,                   //λ����Ϊ��
    DBERR_DB_BITS_ITEM_NOT_EMPTY,               //λ����ǿ�
    DBERR_DB_BITS_ITEM_INVALID_FREE,            //λ��������±���Ч
    DBERR_DB_BITS_ITEM_NUM_NOT_MATCH,           //λ����������ƥ�䣨���������������м�¼��һ�£�
    DBERR_DB_BITS_ITEM_INVALID_SIZE,            //λ�����С��Ч��λ�����ۼӴ�С����λ�����С��
    
    DBERR_DB_STRUCT_GROUP_TOO_MORE,             //�ṹ����
    DBERR_DB_STRUCT_GROUP_EXISTS,               //�ṹ���Ѵ���
    DBERR_DB_STRUCT_GROUP_NOT_EXISTS,           //�ṹ�鲻����
    DBERR_DB_STRUCT_GROUP_EMPTY,                //�ṹ��Ϊ��
    DBERR_DB_STRUCT_GROUP_NOT_EMPTY,            //�ṹ��ǿ�
    DBERR_DB_STRUCT_GROUP_INVALID_FREE,         //�ṹ������±���Ч
    DBERR_DB_STRUCT_GROUP_INVALID_ITEM_INDEX,   //�ṹ��ṹ���±���Ч
    DBERR_DB_STRUCT_ITEM_TOO_MORE,              //�ṹ����
    DBERR_DB_STRUCT_ITEM_EXISTS,                //�ṹ���Ѵ���
    DBERR_DB_STRUCT_ITEM_NOT_EXISTS,            //�ṹ�����
    DBERR_DB_STRUCT_ITEM_EMPTY,                 //�ṹ��Ϊ��
    DBERR_DB_STRUCT_ITEM_NOT_EMPTY,             //�ṹ��ǿ�
    DBERR_DB_STRUCT_ITEM_INVALID_FREE,          //�ṹ������±���Ч
    DBERR_DB_STRUCT_ITEM_NUM_NOT_MATCH,         //�ṹ��������ƥ�䣨���������������м�¼��һ�£�

    DBERR_DB_TABLE_GROUP_TOO_MORE,              //������
    DBERR_DB_TABLE_GROUP_EXISTS,                //�����Ѵ���
    DBERR_DB_TABLE_GROUP_NOT_EXISTS,            //���鲻����
    DBERR_DB_TABLE_GROUP_EMPTY,                 //����Ϊ��
    DBERR_DB_TABLE_GROUP_NOT_EMPTY,             //����ǿ�
    DBERR_DB_TABLE_GROUP_INVALID_FREE,          //��������±���Ч
    DBERR_DB_TABLE_GROUP_INVALID_ITEM_INDEX,    //���������±���Ч
    DBERR_DB_FIELD_ITEM_TOO_MORE,               //������
    DBERR_DB_FIELD_ITEM_EXISTS,                 //�����Ѵ���
    DBERR_DB_FIELD_ITEM_NOT_EXISTS,             //�������
    DBERR_DB_FIELD_ITEM_EMPTY,                  //����Ϊ��
    DBERR_DB_FIELD_ITEM_NOT_EMPTY,              //����ǿ�
    DBERR_DB_FIELD_ITEM_INVALID_FREE,           //��������±���Ч
    DBERR_DB_FIELD_ITEM_NUM_NOT_MATCH,          //����������ƥ�䣨���������������м�¼��һ�£�

    DBERR_DB_RELATION_ADD_FAILED,               //���ӱ����ϵʧ��
    DBERR_DB_RELATION_TOO_MORE,                 //�����ϵ��
    DBERR_DB_RELATION_INVALID_INDEX,            //�����ϵ�±���Ч
    DBERR_DB_RELATION_NOT_EXISTS,               //�����ϵ������
    DBERR_DB_RELATION_EMPTY,                    //�����ϵΪ��
    DBERR_DB_RELATION_NOT_EMPTY,                //�����ϵ�ǿ�
    DBERR_DB_RELATION_MULTI_PARENT_NOT_SYMBIOTIC,   //�ุδ����

    DBERR_DB_INVALID_FIELD_SIZE,                //
};

#endif  //HDB_ERROR_H