#include "Tab.h"

Tab::Tab(QWidget* parent) : QWidget(parent)
{
    _layout = new QHBoxLayout;
    _layout->setMargin(0);
    _layout->setSpacing(0);
    setLayout(_layout);
}

SubTab* Tab::insertSubTab(const QString& text, int pos)
{
    SubTab* subtab = new SubTab(text);
    _layout->insertWidget(pos < 0 ? _layout->count() : pos, subtab);
    return subtab;
}

void Tab::insertSubTab(SubTab* tab, int pos)
{

}

void Tab::removeSubTab(int pos)
{

}

void Tab::removeSubTab(SubTab* tab)
{

}

SubTab* Tab::subTabAt(int pos)
{
    if(pos >= 0 && pos < _layout->count())
        return qobject_cast<SubTab*>(_layout->itemAt(pos)->widget());
    else
        return nullptr;
}
