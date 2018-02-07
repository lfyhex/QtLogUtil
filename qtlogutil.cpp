#include "qtlogutil.h"
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QVector>
#include <QTextCodec>

static QTextStream m_text;
static QVector<QString> g_vctLevel;
static QFile m_logFile;
static QString m_strPath;
static QString m_strName;

void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString strDt = dt.toString("MM-dd:hh:mm:ss.zzz");
    QString strLogLevel = g_vctLevel[(int)type];
    QString strOther;
    QString strMessage = QString("[%1] %2 %3").arg(strDt).arg(strLogLevel).arg(msg);

    switch (type) {
    case QtCriticalMsg:
    case QtFatalMsg:
        strOther = QString('(') + context.file + " " + QString::number(context.line) + " " + context.function + QString(')');
        strMessage = strMessage + " " + strOther + "\n";
        break;
    default:
        strMessage += "\n";
        break;
    }
    m_text << strMessage;
    m_text.flush();
}

bool setLogFile(const QString &strPath, const QString &strName)
{
    if (g_vctLevel.count() == 0)
    {
        g_vctLevel << "[DEBUG]" << "[WARN]" << "[CRIT]" << "[FATAL]" << "[INFO]";
    }
    m_strPath = strPath;
    m_strName = strName;
    if (QDir(strPath).exists() && !strName.isEmpty())
    {
        if (m_strPath.endsWith("/") || m_strPath.endsWith("\\"))
        {
            m_logFile.setFileName(strPath + strName);
        }
        else
        {
            m_logFile.setFileName(strPath + "/" + strName);
        }
        if (m_logFile.open(QIODevice::WriteOnly))
        {
            m_text.setDevice(&m_logFile);
            m_text.setCodec(QTextCodec::codecForName("UTF-8"));
            m_text.setGenerateByteOrderMark(true);
            qInstallMessageHandler(logMessageHandler);
            return true;
        }
    }
    return false;
}
