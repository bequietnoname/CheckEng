#pragma once

#if defined(TEST1_DIALOG_LIBRARY)
    #define TEST1_DIALOG_SHARED_EXPORT Q_DECL_EXPORT
#else
    #define TEST1_DIALOG_SHARED_EXPORT Q_DECL_IMPORT
#endif

