#include "WizScrollBar.h"

#include <QtGui>

WizScrollBar::WizScrollBar(QWidget* parent /* = 0 */)
    : QScrollBar(parent)
    , m_bgColor("transparent")
    , m_handleColor("#C1C1C1")
    , m_bLeftBorder(false)
{

    // FIXME:  hard code
    setHandleVisible(true);

    setMouseTracking(true);

    connect(&m_timerScrollTimeout, SIGNAL(timeout()), this, SLOT(on_scrollTimeout()));
    connect(this, SIGNAL(valueChanged(int)), SLOT(on_valueChanged(int)));

    m_timerScrollTimeout.setSingleShot(true);
    m_timerScrollTimeout.start(3000);
}

QSize WizScrollBar::sizeHint() const
{
    return m_bLeftBorder ? QSize(13, 1) : QSize(12, 1);
}

void WizScrollBar::mouseMoveEvent(QMouseEvent* event)
{
    m_timerScrollTimeout.start(3000);

    QScrollBar::mouseMoveEvent(event);
}

void WizScrollBar::syncWith(QScrollBar* source)
{
    setMinimum(source->minimum());
    setMaximum(source->maximum());
    setSliderPosition(source->sliderPosition());
    setPageStep(source->pageStep());
    setSingleStep(source->singleStep());

    connect(source, SIGNAL(valueChanged(int)), SLOT(on_sourceValueChanged(int)));
    connect(source, SIGNAL(rangeChanged(int, int)), SLOT(on_sourceRangeChanged(int, int)));

    m_scrollSyncSource = source;

}

void WizScrollBar::applyStyle(const QString& bgColorName, const QString& handleColorName, bool leftBorder)
{
    m_bgColor = bgColorName;
    m_handleColor = handleColorName;
    m_bLeftBorder = leftBorder;
}

void WizScrollBar::showHandle()
{
    if (maximum() == minimum())
        return;

    setHandleVisible(true);
    update();

//    QScrollBar::show();
    m_timerScrollTimeout.start(1000);
}

void WizScrollBar::hideHandle()
{
    setHandleVisible(false);
    update();
}

void WizScrollBar::on_sourceValueChanged(int value)
{
    setSliderPosition(value);
}

void WizScrollBar::on_sourceRangeChanged(int min, int max)
{
    setMinimum(min);
    setMaximum(max);
    setPageStep(m_scrollSyncSource->pageStep());
    setSingleStep(m_scrollSyncSource->singleStep());
}

void WizScrollBar::on_valueChanged(int value)
{
    if (m_scrollSyncSource) {
        m_scrollSyncSource->setSliderPosition(value);
    }

    showHandle();
}

void WizScrollBar::on_scrollTimeout()
{
    hideHandle();
}

void WizScrollBar::setHandleVisible(bool visible)
{
    setStyleSheet(
        QString("QScrollBar {\
            background: %1;\
            %2\
        }\
        QScrollBar::handle {\
            background: %3;\
            min-height: 30px;\
        }\
        QScrollBar::handle:vertical {\
            margin: 0px 3px 0px 3px;\
            border-radius:3px;\
            width:6px; \
        }\
        QScrollBar::add-page, QScrollBar::sub-page {\
            background: transparent;\
        }\
        QScrollBar::up-arrow, QScrollBar::down-arrow, QScrollBar::left-arrow, QScrollBar::right-arrow {\
            background: transparent;\
        }\
        QScrollBar::add-line, QScrollBar::sub-line {\
            height: 0px;\
            width: 0px;\
        }").arg(m_bgColor).arg(m_bLeftBorder ? "border-left:1px solid #e7e7e7;" : "")
        .arg(visible ? m_handleColor : "transparent"));
}


WizListWidgetWithCustomScorllBar::WizListWidgetWithCustomScorllBar(QWidget* parent)
    : QListWidget(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_vScroll = new WizScrollBar(this);
    m_vScroll->syncWith(verticalScrollBar());
}

void WizListWidgetWithCustomScorllBar::resizeEvent(QResizeEvent* event)
{
    // reset scrollbar
    m_vScroll->resize(m_vScroll->sizeHint().width(), event->size().height());
    m_vScroll->move(event->size().width() - m_vScroll->sizeHint().width(), 0);
    QListWidget::resizeEvent(event);
}
