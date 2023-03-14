
#ifndef CVFUNCTION_EXPORT_H
#define CVFUNCTION_EXPORT_H

#ifdef CVFUNCTION_STATIC_DEFINE
#  define CVFUNCTION_EXPORT
#  define CVFUNCTION_NO_EXPORT
#else
#  ifndef CVFUNCTION_EXPORT
#    ifdef cvFunction_EXPORTS
        /* We are building this library */
#      define CVFUNCTION_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CVFUNCTION_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CVFUNCTION_NO_EXPORT
#    define CVFUNCTION_NO_EXPORT 
#  endif
#endif

#ifndef CVFUNCTION_DEPRECATED
#  define CVFUNCTION_DEPRECATED __declspec(deprecated)
#endif

#ifndef CVFUNCTION_DEPRECATED_EXPORT
#  define CVFUNCTION_DEPRECATED_EXPORT CVFUNCTION_EXPORT CVFUNCTION_DEPRECATED
#endif

#ifndef CVFUNCTION_DEPRECATED_NO_EXPORT
#  define CVFUNCTION_DEPRECATED_NO_EXPORT CVFUNCTION_NO_EXPORT CVFUNCTION_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CVFUNCTION_NO_DEPRECATED
#    define CVFUNCTION_NO_DEPRECATED
#  endif
#endif

#endif /* CVFUNCTION_EXPORT_H */
