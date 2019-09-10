
TEMPLATE = lib

CONFIG += qt dll warn_on

DEFINES += HDB_BUILD_DLL BOOST_DATE_TIME_NO_LIB

OBJECTS_DIR = $$(HZTBUILDDIR)/HDB/obj

DESTDIR = $$(HZTBINDIR)

TARGET = HDB

LIBPATH += \
    $$(HZTBINDIR) \
   

VPATH = $$(HZTSRCDIR)/include/HDB

INCLUDEPATH = \
    $$(HZTSRCDIR)/include \
    $$(BOOSTDIR)/include \

HEADERS += \
    HDBExport.h \
    HDataTypes.h \
    HDBDefines.h \
    HDBError.h \
    HDBMetaMap.h \
    HDBMeta.h \  
    HDBMetaImpl.h \  
    HDBMetaGenerateHeader.h \
    HDBConnection.h \
    HDBConnectionImpl.h \
    HDBOid.h \
    HDBRelChild.h \
    HDBRelParent.h \
    HDBRelRefer.h \
    HDBVariable.h \    
    HDBObject.h \
    
    
SOURCES += \
    HDBMetaMap.cpp \
    HDBMeta.cpp \    
    HDBMetaImpl.cpp \    
    HDBMetaEnum.cpp \
    HDBMetaBits.cpp \
    HDBMetaStruct.cpp \
    HDBMetaTable.cpp \
    HDBMetaGenerateHeader.cpp \
    HDBMetaEntity.cpp \
    HDBConnection.cpp \
    HDBConnectionImpl.cpp \
    HDBOid.cpp \
    HDBRelChild.cpp \
    HDBRelParent.cpp \
    HDBRelRefer.cpp \
    HDBVariable.cpp \    
    HDBObject.cpp \
