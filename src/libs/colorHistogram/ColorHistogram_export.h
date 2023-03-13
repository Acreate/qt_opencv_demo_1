
#ifndef COLORHISTOGRAM_EXPORT_H
#define COLORHISTOGRAM_EXPORT_H

#ifdef COLORHISTOGRAM_STATIC_DEFINE
#  define COLORHISTOGRAM_EXPORT
#  define COLORHISTOGRAM_NO_EXPORT
#else
#  ifndef COLORHISTOGRAM_EXPORT
#    ifdef colorHistogram_EXPORTS
        /* We are building this library */
#      define COLORHISTOGRAM_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define COLORHISTOGRAM_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef COLORHISTOGRAM_NO_EXPORT
#    define COLORHISTOGRAM_NO_EXPORT 
#  endif
#endif

#ifndef COLORHISTOGRAM_DEPRECATED
#  define COLORHISTOGRAM_DEPRECATED __declspec(deprecated)
#endif

#ifndef COLORHISTOGRAM_DEPRECATED_EXPORT
#  define COLORHISTOGRAM_DEPRECATED_EXPORT COLORHISTOGRAM_EXPORT COLORHISTOGRAM_DEPRECATED
#endif

#ifndef COLORHISTOGRAM_DEPRECATED_NO_EXPORT
#  define COLORHISTOGRAM_DEPRECATED_NO_EXPORT COLORHISTOGRAM_NO_EXPORT COLORHISTOGRAM_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COLORHISTOGRAM_NO_DEPRECATED
#    define COLORHISTOGRAM_NO_DEPRECATED
#  endif
#endif

#endif /* COLORHISTOGRAM_EXPORT_H */