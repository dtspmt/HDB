
#ifndef HDB_EXPORT_H
#define HDB_EXPORT_H

#ifdef HDB_BUILD_DLL
	#define HDB_DLL_EXPORT __declspec(dllexport)
#else
	#define HDB_DLL_EXPORT __declspec(dllimport)
#endif


#endif	//HDB_EXPORT_H

