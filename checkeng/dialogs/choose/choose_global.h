#pragma once

#if defined(CHOOSE_DIALOG_LIBRARY)
    #define CHOOSE_DIALOG_SHARED_EXPORT Q_DECL_EXPORT
#else
    #define CHOOSE_DIALOG_SHARED_EXPORT Q_DECL_IMPORT
#endif

