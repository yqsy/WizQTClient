#ifndef CWIZOEMSETTINGS_H
#define CWIZOEMSETTINGS_H

#include <QSettings>

class WizOEMSettings : public QSettings
{
public:
    WizOEMSettings(const QString& strUserAccountPath);

    static bool settingFileExists(const QString& strUserAccountPath);
    //
    static void updateOEMSettings(const QString& strUserAccountPath, const QString& strOEMJSONData);

    bool isHideShareByEmail();
    bool isHidePersonalGroup();
    bool isHideFeedback();
    bool isHideRegister();
    bool isEncryptPassword();
    bool isHideSocialLogin();
    bool isHideForgotPassword();
    bool isHideShare();                         //�������з����ⲿ��ʽ
    bool isAccountPlaceholder();            //��¼����ʾ�����˺�
    bool isHideMyShare();
    bool isHideBuyVip();
    bool isForbidCreateBiz();

    //
    void setLogoPath(const QString& path);
    QString logoPath();

private:


};



#endif // CWIZOEMSETTINGS_H
