// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the ONYX32ASYNC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// ONYX32ASYNC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ONYX32ASYNC_EXPORTS
#define ONYX32ASYNC_API __declspec(dllexport)
#else
#define ONYX32ASYNC_API __declspec(dllimport)
#endif

// This class is exported from the dll
class ONYX32ASYNC_API COnyx32Async {
public:
	COnyx32Async(void);
	// TODO: add your methods here.
};

extern ONYX32ASYNC_API int nOnyx32Async;

ONYX32ASYNC_API int fnOnyx32Async(void);
