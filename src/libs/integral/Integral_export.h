
#ifndef INTEGRAL_EXPORT_H
#define INTEGRAL_EXPORT_H

#ifdef INTEGRAL_STATIC_DEFINE
#  define INTEGRAL_EXPORT
#  define INTEGRAL_NO_EXPORT
#else
#  ifndef INTEGRAL_EXPORT
#    ifdef integral_EXPORTS
        /* We are building this library */
#      define INTEGRAL_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define INTEGRAL_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef INTEGRAL_NO_EXPORT
#    define INTEGRAL_NO_EXPORT 
#  endif
#endif

#ifndef INTEGRAL_DEPRECATED
#  define INTEGRAL_DEPRECATED __declspec(deprecated)
#endif

#ifndef INTEGRAL_DEPRECATED_EXPORT
#  define INTEGRAL_DEPRECATED_EXPORT INTEGRAL_EXPORT INTEGRAL_DEPRECATED
#endif

#ifndef INTEGRAL_DEPRECATED_NO_EXPORT
#  define INTEGRAL_DEPRECATED_NO_EXPORT INTEGRAL_NO_EXPORT INTEGRAL_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef INTEGRAL_NO_DEPRECATED
#    define INTEGRAL_NO_DEPRECATED
#  endif
#endif

#endif /* INTEGRAL_EXPORT_H */
