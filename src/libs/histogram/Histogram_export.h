
#ifndef HISTOGRAM_EXPORT_H
#define HISTOGRAM_EXPORT_H

#ifdef HISTOGRAM_STATIC_DEFINE
#  define HISTOGRAM_EXPORT
#  define HISTOGRAM_NO_EXPORT
#else
#  ifndef HISTOGRAM_EXPORT
#    ifdef histogram_EXPORTS
        /* We are building this library */
#      define HISTOGRAM_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define HISTOGRAM_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef HISTOGRAM_NO_EXPORT
#    define HISTOGRAM_NO_EXPORT 
#  endif
#endif

#ifndef HISTOGRAM_DEPRECATED
#  define HISTOGRAM_DEPRECATED __declspec(deprecated)
#endif

#ifndef HISTOGRAM_DEPRECATED_EXPORT
#  define HISTOGRAM_DEPRECATED_EXPORT HISTOGRAM_EXPORT HISTOGRAM_DEPRECATED
#endif

#ifndef HISTOGRAM_DEPRECATED_NO_EXPORT
#  define HISTOGRAM_DEPRECATED_NO_EXPORT HISTOGRAM_NO_EXPORT HISTOGRAM_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef HISTOGRAM_NO_DEPRECATED
#    define HISTOGRAM_NO_DEPRECATED
#  endif
#endif

#endif /* HISTOGRAM_EXPORT_H */
