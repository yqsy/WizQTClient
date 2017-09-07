#ifndef WIZMARKDOWNTEMPLATEDIALOG_H
#define WIZMARKDOWNTEMPLATEDIALOG_H

#include <QDialog>
#include <QProxyStyle>
#include <QListWidgetItem>

namespace Ui {
class WizMarkdownTemplateDialog;
}
/*
class CWizTemplateItem : public QListWidgetItem
{
public:
    explicit CWizTemplateItem(QListWidget *view = 0, int type = Type);

    void draw(QPainter* p, const QStyleOptionViewItemV4* vopt) const;
    QRect drawItemBackground(QPainter* p, const QRect& rect, bool selected, bool focused) const;


    QString title() const;
    void setTitle(const QString& title);

    bool isCustom() const;
    void setIsCustom(bool isCustom);


    QString fileName() const;
    void setFileName(const QString& fileName);

    virtual bool operator<(const QListWidgetItem &other) const;

private:
    QString m_title;
    bool m_isCustom;
    QString m_fileName;
};
*/

class WizMarkdownTemplateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WizMarkdownTemplateDialog(QWidget *parent = 0);
    ~WizMarkdownTemplateDialog();

    bool getListDataFromSettings(QMap<QString, bool>& itemList, QString& selectedFile);
    bool saveListDataToSettings();
    bool getListDataFromLocalFiles(const QString& strPath, QStringList& itemList);

    void loadMarkdownHtml(const QString& strCssFile);
    void selectItemByLocation(const QString& strFileName);
public slots:
    bool initListWidget();

private slots:
    void on_pushButton_Add_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_delete_clicked();

    void on_customContextMenuRequested(const QPoint & pos);

    void on_actionSaveAs_clicked();

private:
    Ui::WizMarkdownTemplateDialog *ui;

    QMenu* m_menu;
};

#endif // WIZMARKDOWNTEMPLATEDIALOG_H
