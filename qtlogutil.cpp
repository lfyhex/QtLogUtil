#include "qtlogutil.h"
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QVector>
#include <QTextCodec>

QtLogUtil *QtLogUtil::m_pInstance = NULL;
static QTextStream m_text;
static QVector<QString> g_vctLevel;

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


QtLogUtil::QtLogUtil()
{
    if (g_vctLevel.count() == 0)
    {
        g_vctLevel << "[DEBUG]" << "[WARN]" << "[CRIT]" << "[FATAL]" << "[INFO]";
    }
}

QtLogUtil::~QtLogUtil()
{
    m_text.reset();
    m_logFile.close();
}

QtLogUtil* QtLogUtil::instance()
{
    if (!m_pInstance)
    {
        m_pInstance = new QtLogUtil;
    }
    return m_pInstance;
}

void QtLogUtil::release()
{
    if (m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

bool QtLogUtil::setLogFile(const QString &strPath, const QString &strName)
{
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
