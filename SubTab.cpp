#include "SubTab.h"

SubTab::SubTab(const QString& text, QWidget* itemsWidget, QWidget* parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);

    _text = new QLabel;
    _text->setStyleSheet("font-size: 12px; color: "+style()->standardPalette().dark().color().name(QColor::HexArgb)+";"
                         "background: "+style()->standardPalette().midlight().color().name(QColor::HexArgb)+";");
    _text->setText(text);
    _text->setAlignment(Qt::AlignCenter);
    _text->setContentsMargins(4,0,4,0);

    _itemsWidget = itemsWidget == nullptr ? new QWidget() : itemsWidget;
    _itemsWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    _layout = new QVBoxLayout;
    _layout->setMargin(0);
    _layout->setSpacing(0);
    _layout->addWidget(_itemsWidget, 1);
    _layout->addWidget(_text, 0, Qt::AlignBottom);
    setLayout(_layout);

    setStyleSheet(".QWidget { border: none; background: "+style()->standardPalette().midlight().color().name(QColor::HexArgb)+"; }");
}

void SubTab::setText(const QString& text)
{
    _text->setText(text);
}

QWidget* SubTab::setItemsWidget(QWidget* itemsWidget)
{
    QWidget* prevWidget = _itemsWidget;
    _layout->removeWidget(_itemsWidget);
    _layout->insertWidget(0, itemsWidget, 1);
    _itemsWidget = itemsWidget;
    _itemsWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    return prevWidget;
}

QWidget* SubTab::itemsWidget() const
{
    return _itemsWidget;
}
