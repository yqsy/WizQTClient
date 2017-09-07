#include "WizWebSettingsDialog.h"
#include "sync/WizToken.h"
#include "WizMainWindow.h"
#include "share/WizGlobal.h"
#include "utils/WizPathResolve.h"
#include "widgets/WizLocalProgressWebView.h"

#include <QMovie>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QNetworkReply>
#include <QWebEngineView>
#include "share/WizWebEngineView.h"


WizWebSettingsDialog::WizWebSettingsDialog(QString url, QSize sz, QWidget *parent)
    : WizWebEngineViewContainerDialog(parent)
    , m_url(url)
{
    setContentsMargins(0, 0, 0, 0);
    setFixedSize(sz);

    QPalette pal = palette();
    pal.setBrush(backgroundRole(), QBrush("#FFFFFF"));
    setPalette(pal);

    m_progressWebView = new WizLocalProgressWebView(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_progressWebView);
    setLayout(layout);

    WizWebEngineView* web = m_progressWebView->web();
    //
    WizMainWindow* mainWindow = WizGlobal::mainWindow();
    if (mainWindow) {
        web->addToJavaScriptWindowObject("WizExplorerApp", mainWindow->object());
    }
    connect(web, SIGNAL(loadFinishedEx(bool)), SLOT(on_web_loaded(bool)));
}

WizWebEngineView* WizWebSettingsDialog::web()
{
    return m_progressWebView->web();
}

void WizWebSettingsDialog::load()
{
    web()->load(m_url);
}

void WizWebSettingsDialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    //
    load();
}

void WizWebSettingsDialog::on_web_loaded(bool ok)
{
    if (ok)
    {
    }
    else
    {
        //ʧ�ܵ�ʱ��������ѭ��
        //loadErrorPage();
    }
}

void WizWebSettingsDialog::loadErrorPage()
{
    QString strFileName = Utils::WizPathResolve::resourcesPath() + "files/errorpage/load_fail.html";
    QString strHtml;
    ::WizLoadUnicodeTextFromFile(strFileName, strHtml);    
    QUrl url = QUrl::fromLocalFile(strFileName);
    web()->setHtml(strHtml, url);
}

void WizWebSettingsDialog::on_networkRequest_finished(QNetworkReply* reply)
{
    // ��ʹ���������������Ҳ�����OperationCanceledError���˴��������
    if (reply && reply->error() != QNetworkReply::NoError && reply->error() != QNetworkReply::OperationCanceledError)
    {
        showError();
    }
}

void WizWebSettingsDialog::showError()
{
    //loadErrorPage();
}

void WizWebSettingsWithTokenDialog::load()
{
    connect(WizToken::instance(), SIGNAL(tokenAcquired(const QString&)),
            SLOT(on_token_acquired(const QString&)), Qt::QueuedConnection);

    WizToken::requestToken();
}

void WizWebSettingsWithTokenDialog::on_token_acquired(const QString& token)
{
    if (token.isEmpty()) {
        showError();
        return;
    }
    //
    QString url = m_url;
    url.replace(QString(WIZ_TOKEN_IN_URL_REPLACE_PART), token);
    //
    QUrl u = QUrl::fromEncoded(url.toUtf8());
    qDebug() << " show web dialog with token : " << u;

    //
    web()->load(u);
}
