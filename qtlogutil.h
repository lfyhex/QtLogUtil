#ifndef QTLOGUTIL_H
#define QTLOGUTIL_H

#include <QtCore/qglobal.h>

#if defined(QTLOGUTIL_LIBRARY)
#  define QTLOGUTILSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTLOGUTILSHARED_EXPORT Q_DECL_IMPORT
#endif


#include <QFile>

#define g_logUtil QtLogUtil::instance()

class QTLOGUTILSHARED_EXPORT QtLogUtil
{

public:
    static QtLogUtil* instance();
    static void release();

    bool setLogFile(const QString &strPath, const QString &strName);

private:
    QtLogUtil();
    ~QtLogUtil();

private:
    static QtLogUtil *m_pInstance;
    QString m_strPath;
    QString m_strName;
    QFile m_logFile;
};

#endif // QTLOGUTIL_H
