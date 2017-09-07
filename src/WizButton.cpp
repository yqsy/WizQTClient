#include "WizButton.h"

#include <QStyleOptionToolButton>
#include <QPainter>

#include "WizDef.h"
#include "share/WizMisc.h"
#include "share/WizSettings.h"


WizButton::WizButton(QWidget* parent)
    : QToolButton(parent)
{
}

QSize WizButton::sizeHint() const
{
#ifdef Q_OS_LINUX
    return QSize(32, 32);
#else
    return QSize(WizSmartScaleUI(24), WizSmartScaleUI(24));
#endif
}

void WizButton::setAction(QAction* action)
{
    setDefaultAction(action);
}

void WizButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOptionToolButton opt;
    initStyleOption(&opt);

    QPainter p(this);

    QIcon::Mode mode = opt.state & QStyle::State_Enabled ? QIcon::Normal : QIcon::Disabled;
    if (mode == QIcon::Normal && (opt.state & QStyle::State_HasFocus || opt.state & QStyle::State_Sunken))
        mode = QIcon::Active;
    QIcon::State state = QIcon::Off;
    if (opt.state & QStyle::State_On)
        state = QIcon::On;

    opt.icon.paint(&p, opt.rect, Qt::AlignCenter, mode, state);
}
