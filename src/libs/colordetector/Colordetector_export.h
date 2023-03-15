
#ifndef COLORDETECTOR_EXPORT_H
#define COLORDETECTOR_EXPORT_H

#ifdef COLORDETECTOR_STATIC_DEFINE
#  define COLORDETECTOR_EXPORT
#  define COLORDETECTOR_NO_EXPORT
#else
#  ifndef COLORDETECTOR_EXPORT
#    ifdef colordetector_EXPORTS
        /* We are building this library */
#      define COLORDETECTOR_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define COLORDETECTOR_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef COLORDETECTOR_NO_EXPORT
#    define COLORDETECTOR_NO_EXPORT 
#  endif
#endif

#ifndef COLORDETECTOR_DEPRECATED
#  define COLORDETECTOR_DEPRECATED __declspec(deprecated)
#endif

#ifndef COLORDETECTOR_DEPRECATED_EXPORT
#  define COLORDETECTOR_DEPRECATED_EXPORT COLORDETECTOR_EXPORT COLORDETECTOR_DEPRECATED
#endif

#ifndef COLORDETECTOR_DEPRECATED_NO_EXPORT
#  define COLORDETECTOR_DEPRECATED_NO_EXPORT COLORDETECTOR_NO_EXPORT COLORDETECTOR_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COLORDETECTOR_NO_DEPRECATED
#    define COLORDETECTOR_NO_DEPRECATED
#  endif
#endif

#endif /* COLORDETECTOR_EXPORT_H */
