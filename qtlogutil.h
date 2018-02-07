#ifndef QTLOGUTIL_H
#define QTLOGUTIL_H

#include <QtCore/qglobal.h>

#if defined(QTLOGUTIL_LIBRARY)
#  define QTLOGUTILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTLOGUTILSHARED_EXPORT Q_DECL_IMPORT
#endif

// ����ڹ���App֮��͵���

QTLOGUTILSHARED_EXPORT bool setLogFile(const QString &strPath, const QString &strName);

#endif // QTLOGUTIL_H
