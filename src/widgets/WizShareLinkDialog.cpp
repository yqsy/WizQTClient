#include "WizShareLinkDialog.h"
#include "sync/WizToken.h"
#include "utils/WizPathResolve.h"
#include "utils/WizMisc.h"
#include "share/WizSettings.h"
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QTimer>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QMessageBox>
#include <QDebug>
#include "share/WizWebEngineView.h"
#include "sync/WizApiEntry.h"

#define ShareLinkFirstTips "ShareLinkFirstTips"

WizShareLinkDialog::WizShareLinkDialog(WizUserSettings& settings, QWidget* parent, Qt::WindowFlags f)
    : WizWebEngineViewContainerDialog(parent, f)
    , m_settings(settings)
    , m_view(new WizWebEngineView(this))
{
    setWindowFlags(Qt::CustomizeWindowHint);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_view);

    m_view->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    m_view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    //
    m_view->addToJavaScriptWindowObject("external", this);
    //m_view->addToJavaScriptWindowObject("customObject", this);

    m_animation = new QPropertyAnimation(this, "size", this);
}

WizShareLinkDialog::~WizShareLinkDialog()
{
}

QSize WizShareLinkDialog::sizeHint() const
{
    if (m_settings.locale() == ::WizGetDefaultTranslatedLocal())
    {
        return QSize(630, 337);
    }

    return QSize(541, 335);
}

void WizShareLinkDialog::shareDocument(const WIZDOCUMENTDATA& doc)
{
    m_doc = doc;
    loadHtml();
}

void WizShareLinkDialog::logAction(const QString& strAction)
{
    qDebug() << "[Share Link] " << strAction;
}

void WizShareLinkDialog::writeToLog(const QString& strLog)
{
    qDebug() << "[Share Link] " << strLog;
}

void WizShareLinkDialog::getToken()
{
    QString strToken = WizToken::token();
    m_view->page()->runJavaScript(QString("setToken('%1')").arg(strToken), [=](const QVariant& vRet){

        emit tokenObtained();

    });
}

QString WizShareLinkDialog::getKbGuid()
{
    return m_doc.strKbGUID;
}

QString WizShareLinkDialog::getGuid()
{
    return m_doc.strGUID;
}

QString WizShareLinkDialog::getTitle()
{
    return m_doc.strTitle;
}

void WizShareLinkDialog::resizeEx(int nWidth, int nHeight)
{
//    resize(nWidth, nHeight);
    QRect rec = geometry();
    rec.setHeight(nHeight);
    setGeometry(rec);
//    m_animation->stop();
//    m_animation->setDuration(100);
//    m_animation->setStartValue(geometry().size());
//    m_animation->setEndValue(QSize(nWidth, nHeight));
////    m_animation->setEasingCurve(QEasingCurve::InOutQuad);

//    m_animation->start();
}

void WizShareLinkDialog::openindefaultbrowser(const QString& url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void WizShareLinkDialog::dragcaption(int x, int y)
{
    QPoint pos = QCursor::pos();
    move(pos.x() - x, pos.y() - y);
}

void WizShareLinkDialog::copyLink(const QString& link, const QString& callBack)
{
    if (link.isEmpty())
    {
        qDebug() << "[Share link] link is empty, nothing to copy";
        return;
    }

    Utils::WizMisc::copyTextToClipboard(link);

    if (callBack.isEmpty())
        return;

    m_view->page()->runJavaScript(callBack);
}

QString WizShareLinkDialog::getShareLinkFirstTips()
{
    return m_settings.get(ShareLinkFirstTips);
}

void WizShareLinkDialog::setShareLinkFirstTips(const QString& value)
{
    m_settings.set(ShareLinkFirstTips, value);
}

QString WizShareLinkDialog::getLocalLanguage()
{
    return m_settings.locale();
}

void WizShareLinkDialog::setFormateISO8601StringParam(const QString& param)
{
    m_formateISO8601StringParam = param;
    emit formateISO8601StringChanged();
}

QString WizShareLinkDialog::formateISO8601String()
{
    QDateTime date = QDateTime::fromString(m_formateISO8601StringParam, Qt::ISODate);
    if (!date.isValid() || date.isNull())
        return m_formateISO8601StringParam;

    return date.toString(Qt::ISODate);
}

void WizShareLinkDialog::loadHtml()
{
    QUrlQuery query;
    query.addQueryItem("share_server", WizCommonApiEntry::shareServer());
    QString strFile = Utils::WizPathResolve::resourcesPath() + "files/share_link/index.html";
    QUrl url = QUrl::fromLocalFile(strFile);
    url.setQuery(query);
    m_view->load(url);
}

