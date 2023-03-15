
#ifndef CONVER_EXPORT_H
#define CONVER_EXPORT_H

#ifdef CONVER_STATIC_DEFINE
#  define CONVER_EXPORT
#  define CONVER_NO_EXPORT
#else
#  ifndef CONVER_EXPORT
#    ifdef conver_EXPORTS
        /* We are building this library */
#      define CONVER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define CONVER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef CONVER_NO_EXPORT
#    define CONVER_NO_EXPORT 
#  endif
#endif

#ifndef CONVER_DEPRECATED
#  define CONVER_DEPRECATED __declspec(deprecated)
#endif

#ifndef CONVER_DEPRECATED_EXPORT
#  define CONVER_DEPRECATED_EXPORT CONVER_EXPORT CONVER_DEPRECATED
#endif

#ifndef CONVER_DEPRECATED_NO_EXPORT
#  define CONVER_DEPRECATED_NO_EXPORT CONVER_NO_EXPORT CONVER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CONVER_NO_DEPRECATED
#    define CONVER_NO_DEPRECATED
#  endif
#endif

#endif /* CONVER_EXPORT_H */
