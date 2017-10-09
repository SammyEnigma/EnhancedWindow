#include "Tab.h"

#include <QtDebug>

Tab::Tab(QWidget* parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QWidget* w = new QWidget;
    w->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    _subsLayout = new QHBoxLayout;
    _subsLayout->setContentsMargins(0,0,1,0);
    _subsLayout->setSpacing(1);
    w->setLayout(_subsLayout);
    w->setStyleSheet(".QWidget { background: "+style()->standardPalette().background().color().name(QColor::HexArgb)+"; }");

    _scrollArea = new QScrollArea;
    _scrollArea->setBackgroundRole(QPalette::Background);
    _scrollArea->setWidget(w);
    _scrollArea->setWidgetResizable(true);
    _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _scrollArea->setStyleSheet(".QScrollArea { border: none; } ");

    _leftBtn = new QPushButton(style()->standardIcon(QStyle::SP_ArrowLeft), "");
    _leftBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    connect(_leftBtn, &QPushButton::clicked, [=] () {
        _scrollArea->horizontalScrollBar()->setValue(_scrollArea->horizontalScrollBar()->value()-50);
    });
    _leftBtn->setVisible(false);

    _rightBtn = new QPushButton(style()->standardIcon(QStyle::SP_ArrowRight), "");
    _rightBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    connect(_rightBtn, &QPushButton::clicked, [=] () {
        _scrollArea->horizontalScrollBar()->setValue(_scrollArea->horizontalScrollBar()->value()+50);
    });
    _rightBtn->setVisible(false);

    _leftBtn->setDisabled(true);
    connect(_scrollArea->horizontalScrollBar(), &QScrollBar::valueChanged, [=] (int value) {
        _leftBtn->setDisabled(value == _scrollArea->horizontalScrollBar()->minimum());
    });
    connect(_scrollArea->horizontalScrollBar(), &QScrollBar::valueChanged, [=] (int value) {
        _rightBtn->setDisabled(value == _scrollArea->horizontalScrollBar()->maximum());
    });

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->addWidget(_leftBtn);
    layout->addWidget(_scrollArea, 1);
    layout->addWidget(_rightBtn);
    layout->setMargin(0);
    setLayout(layout);
}

void Tab::resizeEvent(QResizeEvent* event)
{
    bool showBtn = _subsLayout->sizeHint().width() > width();
    _leftBtn->setVisible(showBtn);
    _rightBtn->setVisible(showBtn);

    if(_leftBtn->isVisible() && _rightBtn->isVisible())
    {
        _leftBtn->setDisabled(_scrollArea->horizontalScrollBar()->value() == _scrollArea->horizontalScrollBar()->minimum());
        _rightBtn->setDisabled(_scrollArea->horizontalScrollBar()->value() == _scrollArea->horizontalScrollBar()->maximum());
    }

    QWidget::resizeEvent(event);
}

SubTab* Tab::insertSubTab(const QString& text, int pos)
{
    SubTab* subtab = new SubTab(text);
    _subsLayout->insertWidget(pos < 0 ? _subsLayout->count() : pos, subtab);
    return subtab;
}

void Tab::insertSubTab(SubTab* subtab, int pos)
{
    _subsLayout->insertWidget(pos < 0 ? _subsLayout->count() : pos, subtab);
}

void Tab::removeSubTab(int pos)
{
    if(pos < 0)
        return;

    _subsLayout->removeItem(_subsLayout->itemAt(pos));
}

void Tab::removeSubTab(SubTab* subtab)
{
    _subsLayout->removeWidget(subtab);
}

SubTab* Tab::subTabAt(int pos)
{
    if(pos >= 0 && pos < _subsLayout->count())
        return qobject_cast<SubTab*>(_subsLayout->itemAt(pos)->widget());
    else
        return nullptr;
}
