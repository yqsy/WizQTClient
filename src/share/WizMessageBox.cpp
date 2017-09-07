#include "WizMessageBox.h"
#include <QPushButton>
#include <QDebug>
#include <QApplication>

QMessageBox::StandardButton WizMessageBox::critical(QWidget* parent, const QString& title,
                                                     const QString& text, QMessageBox::StandardButtons buttons,
                                                     QMessageBox::StandardButton defaultButton)
{
    return messageBox(parent, title, text, buttons, defaultButton, QMessageBox::Critical);
}

QMessageBox::StandardButton WizMessageBox::information(QWidget* parent, const QString& title,
                                                        const QString& text, QMessageBox::StandardButtons buttons,
                                                        QMessageBox::StandardButton defaultButton)
{
    return messageBox(parent, title, text, buttons, defaultButton, QMessageBox::Information);
}

QMessageBox::StandardButton WizMessageBox::question(QWidget* parent, const QString& title,
                                                     const QString& text, QMessageBox::StandardButtons buttons,
                                                     QMessageBox::StandardButton defaultButton)
{
    return messageBox(parent, title, text, buttons, defaultButton, QMessageBox::Question);
}

QMessageBox::StandardButton WizMessageBox::warning(QWidget* parent, const QString& title,
                                                    const QString& text, QMessageBox::StandardButtons buttons,
                                                    QMessageBox::StandardButton defaultButton)
{
    return messageBox(parent, title, text, buttons, defaultButton, QMessageBox::Warning);
}

QMessageBox::StandardButton WizMessageBox::critical(QWidget * parent, const QString & text,
                                     QMessageBox::StandardButtons buttons,
                                     QMessageBox::StandardButton defaultButton)
{
    return critical(parent, QApplication::applicationName(), text, buttons, defaultButton);
}

QMessageBox::StandardButton WizMessageBox::information(QWidget * parent, const QString & text,
                                        QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    return information(parent, QApplication::applicationName(), text, buttons, defaultButton);
}

QMessageBox::StandardButton WizMessageBox::question(QWidget * parent, const QString & text,
                                     QMessageBox::StandardButtons buttons,
                                     QMessageBox::StandardButton defaultButton)
{
    return question(parent, QApplication::applicationName(), text, buttons, defaultButton);
}

QMessageBox::StandardButton WizMessageBox::warning(QWidget * parent, const QString & text,
                                    QMessageBox::StandardButtons buttons,
                                    QMessageBox::StandardButton defaultButton)
{
    return warning(parent, QApplication::applicationName(), text, buttons, defaultButton);
}


QString WizMessageBox::buttonTextFromStandardButton(QMessageBox::StandardButton button)
{
    switch (button) {
    case QMessageBox::Ok:
        return QObject::tr("OK");
        break;
    case QMessageBox::Open:
        return QObject::tr("Open");
        break;
    case QMessageBox::Save:
        return QObject::tr("Save");
        break;
    case QMessageBox::Cancel:
        return QObject::tr("Cancel");
        break;
    case QMessageBox::Close:
        return QObject::tr("Close");
        break;
    case QMessageBox::Discard:
        return QObject::tr("Discard");
        break;
    case QMessageBox::Apply:
        return QObject::tr("Apply");
        break;
    case QMessageBox::Reset:
        return QObject::tr("Reset");
        break;
    case QMessageBox::RestoreDefaults:
        return QObject::tr("RestoreDefaults");
        break;
    case QMessageBox::Help:
        return QObject::tr("Help");
        break;
    case QMessageBox::SaveAll:
        return QObject::tr("Save All");
        break;
    case QMessageBox::Yes:
        return QObject::tr("Yes");
        break;
    case QMessageBox::YesToAll:
        return QObject::tr("Yes to All");
        break;
    case QMessageBox::No:
        return QObject::tr("No");
        break;
    case QMessageBox::NoToAll:
        return QObject::tr("No to All");
        break;
    case QMessageBox::Abort:
        return QObject::tr("Abort");
        break;
    case QMessageBox::Retry:
        return QObject::tr("Retry");
        break;
    case QMessageBox::Ignore:
        return QObject::tr("Ignore");
        break;
    case QMessageBox::NoButton:
        return QObject::tr("NoButton");
        break;
    default:
        return QObject::tr("Unknown");
        break;
    }
    return QObject::tr("Unknown");
}

void WizMessageBox::buttonsFromStandardButtons(QMessageBox::StandardButtons buttons,
                                                QList<QMessageBox::StandardButton>& buttonList)
{
    buttons.testFlag(QMessageBox::Ok) ? buttonList.append(QMessageBox::Ok) : (void)0;
    buttons.testFlag(QMessageBox::Open) ? buttonList.append(QMessageBox::Open) : (void)0;
    buttons.testFlag(QMessageBox::Save) ? buttonList.append(QMessageBox::Save) : (void)0;
    buttons.testFlag(QMessageBox::Cancel) ? buttonList.append(QMessageBox::Cancel) : (void)0;
    buttons.testFlag(QMessageBox::Close) ? buttonList.append(QMessageBox::Close) : (void)0;
    buttons.testFlag(QMessageBox::Discard) ? buttonList.append(QMessageBox::Discard) : (void)0;
    buttons.testFlag(QMessageBox::Apply) ? buttonList.append(QMessageBox::Apply) : (void)0;
    buttons.testFlag(QMessageBox::Reset) ? buttonList.append(QMessageBox::Reset) : (void)0;
    buttons.testFlag(QMessageBox::RestoreDefaults) ? buttonList.append(QMessageBox::RestoreDefaults) : (void)0;
    buttons.testFlag(QMessageBox::Help) ? buttonList.append(QMessageBox::Help) : (void)0;
    buttons.testFlag(QMessageBox::SaveAll) ? buttonList.append(QMessageBox::SaveAll) : (void)0;
    buttons.testFlag(QMessageBox::Yes) ? buttonList.append(QMessageBox::Yes) : (void)0;
    buttons.testFlag(QMessageBox::YesToAll) ? buttonList.append(QMessageBox::YesToAll) : (void)0;
    buttons.testFlag(QMessageBox::No) ? buttonList.append(QMessageBox::No) : (void)0;
    buttons.testFlag(QMessageBox::NoToAll) ? buttonList.append(QMessageBox::NoToAll) : (void)0;
    buttons.testFlag(QMessageBox::Abort) ? buttonList.append(QMessageBox::Abort) : (void)0;
    buttons.testFlag(QMessageBox::Retry) ? buttonList.append(QMessageBox::Retry) : (void)0;
}

QMessageBox::StandardButton WizMessageBox::messageBox(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton, QMessageBox::Icon icon)
{
    WizMessageBox msg(parent);
    msg.setIcon(icon);
    msg.setWindowTitle(title);
    msg.setText(text);
    QList<QMessageBox::StandardButton> buttonList;
    buttonsFromStandardButtons(buttons, buttonList);
    foreach (QMessageBox::StandardButton button, buttonList) {
        QPushButton* pBtn = msg.addButton(button);
        pBtn->setText(buttonTextFromStandardButton(button));
    }
    msg.setDefaultButton(defaultButton);

    //NOTE: ��Macϵͳ�£�dialog�Ի��򲻻��ڸ������о�����ʾ���˴����о��ж��봦��
#ifdef Q_OS_MAC
    QObject::connect(&msg, &WizMessageBox::resized, [&](){
        if (parent)
        {
            QPoint leftTop = parent->geometry().topLeft();
            leftTop.setX(leftTop.x() + (parent->width() - msg.width()) / 2);
            leftTop.setY(leftTop.y() + (parent->height() - msg.height()) / 2);
            msg.move(leftTop);
        }
    });
#endif

    msg.exec();

    return msg.standardButton(msg.clickedButton());
}



void WizMessageBox::resizeEvent(QResizeEvent* event)
{
    QMessageBox::resizeEvent(event);
    emit resized();
}
