#include "SubTab.h"

SubTab::SubTab(const QString& text, QWidget* parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);

    _text = new QLabel;
    _text->setStyleSheet("font-size: 12px; color: "+style()->standardPalette().dark().color().name(QColor::HexArgb)+";");
    _text->setText(text);
    _text->setAlignment(Qt::AlignCenter);
    _text->setContentsMargins(4,0,4,0);

    QVBoxLayout* _layout = new QVBoxLayout;
    _layout->setMargin(0);
    _layout->setSpacing(0);
    _layout->addWidget(new QWidget(), 1);
    _layout->addWidget(_text, 0, Qt::AlignBottom);
    setLayout(_layout);

    setStyleSheet("background: "+style()->standardPalette().midlight().color().name(QColor::HexArgb)+";");
}

void SubTab::setText(const QString& text)
{
    _text->setText(text);
}
