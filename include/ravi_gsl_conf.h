#ifndef RAVI_GSL_CONF_H
#define RAVI_GSL_CONF_H

// This header file must be C compilable
// No C++ artifacts allowed outside of #ifdef __cplusplus
// Best to avoid

#ifdef _MSC_VER

#define RAVIGSL_DLLEXPORT __declspec(dllexport)
#define RAVIGSL_DLLIMPORT __declspec(dllimport)

#else

#define RAVIGSL_DLLEXPORT extern 
#define RAVIGSL_DLLIMPORT extern

#endif

// When compiling the library DLL this
// must be set, but when call the library
// from another program this must not be set
#ifdef RAVIGSL_IMPLEMENTATION
#define RAVIGSL_API RAVIGSL_DLLEXPORT
#else
#define RAVIGSL_API RAVIGSL_DLLIMPORT
#endif

#endif
