// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the ONYX32CORE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// ONYX32CORE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ONYX32CORE_EXPORTS
#define ONYX32CORE_API __declspec(dllexport)
#else
#define ONYX32CORE_API __declspec(dllimport)
#endif

// This class is exported from the dll
class ONYX32CORE_API COnyx32Core {
public:
	COnyx32Core(void);
	// TODO: add your methods here.
};

extern ONYX32CORE_API int nOnyx32Core;

ONYX32CORE_API int fnOnyx32Core(void);
