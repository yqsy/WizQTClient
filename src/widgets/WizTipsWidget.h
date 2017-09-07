#ifndef CWIZTIPSWIDGET_H
#define CWIZTIPSWIDGET_H

#include <functional>
#include <QList>
#include <QTimer>
#include "share/WizPopupWidget.h"

class QLabel;
class QPushButton;

class WizTipsWidget : public WizPopupWidget
{
    Q_OBJECT
public:
    explicit WizTipsWidget(const QString& id,QWidget *parent = 0);
    ~WizTipsWidget();

    void setSizeHint(const QSize& hintSize);
    virtual QSize sizeHint() const;

    static bool isTipsExists(const QString& id);

    void setAutoAdjustPosition(bool autoAdjust);
    bool isAutoAdjustPosition() const;

    void setText(const QString& title, const QString& info, const QString& buttonText = tr("OK"));
    void setButtonVisible(bool visible);

    bool bindTargetWidget(QWidget* targetWidget, int nXOff = 0, int nYOff = 0);

    void bindShowFunction(std::function<void(void)> const& f);
    void bindHideFunction(std::function<void(void)> const& f);
    void bindCloseFunction(std::function<void(void)> const& f);

    void hide();
signals:
    void finished();

public slots:
    void on_targetWidgetClicked();
    void on_timerOut();
    void on_showRequest();

protected:
    void mouseReleaseEvent(QMouseEvent* ev);
    void showEvent(QShowEvent* ev);


private:
    void closeTip();

private:
    QLabel* m_labelTitle;
    QLabel* m_labelInfo;
    QPushButton* m_btnOK;
    QWidget* m_targetWidget;
    int m_xOff;
    int m_yOff;
    QSize m_hintSize;
    QString m_id;
    bool m_autoAdjustPosition;
    QTimer m_timer;
    std::function<void(void)> m_showFunction;       //tip��ʾ��ʱ��ִ�еķ���
    std::function<void(void)> m_hideFunction;       //�û�û�е��tip������������������tip��Ӧ�ñ���ʾ��ʱ��ִ�еĲ���
    std::function<void(void)> m_closeFunction;      //�û������tipʱ��ִ�еķ���
    static QSet<QString> m_tipsList;
};

#endif // CWIZTIPSWIDGET_H
