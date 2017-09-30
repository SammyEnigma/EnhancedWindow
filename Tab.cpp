#include "Tab.h"

Tab::Tab(QWidget* parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);

    _layout = new QHBoxLayout;
    _layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    _layout->setContentsMargins(0,0,1,0);
    _layout->setSpacing(1);
    setLayout(_layout);

    setStyleSheet("Tab { background: "+style()->standardPalette().background().color().name(QColor::HexArgb)+"; }");
}

SubTab* Tab::insertSubTab(const QString& text, int pos)
{
    SubTab* subtab = new SubTab(text);
    _layout->insertWidget(pos < 0 ? _layout->count() : pos, subtab);
    return subtab;
}

void Tab::insertSubTab(SubTab* subtab, int pos)
{
    _layout->insertWidget(pos < 0 ? _layout->count() : pos, subtab);
}

void Tab::removeSubTab(int pos)
{
    if(pos < 0)
        return;

    _layout->removeItem(_layout->itemAt(pos));
}

void Tab::removeSubTab(SubTab* subtab)
{
    _layout->removeWidget(subtab);
}

SubTab* Tab::subTabAt(int pos)
{
    if(pos >= 0 && pos < _layout->count())
        return qobject_cast<SubTab*>(_layout->itemAt(pos)->widget());
    else
        return nullptr;
}

void Tab::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
