#ifndef CWIZNOTEMANAGER_H
#define CWIZNOTEMANAGER_H

#include "WizDef.h"

/*
 * CWizNoteManager���ڹ���ʼ���صĲ��������紴����ɾ���ȡ���Ҫ�ڳ�������ʱ���г�ʼ��
 */
struct WIZDOCUMENTDATA;
struct WIZTAGDATA;
struct TemplateData;
class QNetworkAccessManager;

#define WIZ_DOCUMENT_TYPE_NORMAL    "document"

class WizNoteManager
{
public:
    WizNoteManager(WizDatabaseManager& dbMgr);

    //
    void createIntroductionNoteForNewRegisterAccount();
    // create note
    bool createNote(WIZDOCUMENTDATA& data);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const QString& strLocation);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const WIZTAGDATA& tag);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const QString& strLocation,
                    const WIZTAGDATA& tag);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const QString& strTitle,
                    const QString& strHtml);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const QString& strTitle,
                    const QString& strHtml, const QString& strLocation);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const QString& strTitle,
                    const QString& strHtml, const WIZTAGDATA& tag);
    bool createNote(WIZDOCUMENTDATA& data, const QString& strKbGUID, const QString& strTitle,
                    const QString& strHtml, const QString& strLocation, const WIZTAGDATA& tag);

    bool createNoteByTemplate(WIZDOCUMENTDATA& data, const WIZTAGDATA& tag, const QString& strZiw);

    void updateTemplateJS(const QString& local);
    void downloadTemplatePurchaseRecord();
    //
    static bool downloadTemplateBlocked(const TemplateData& tempData);

private:
    bool updateLocalTemplates(const QByteArray& newJsonData, QNetworkAccessManager& manager);

private:
    WizDatabaseManager& m_dbMgr;
};

#endif // CWIZNOTEMANAGER_H
