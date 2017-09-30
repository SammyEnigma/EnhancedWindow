#include "SubTab.h"

SubTab::SubTab(const QString& text, QWidget* parent) : QWidget(parent)
{
    _text = new QLabel;
    _text->setText(text);
    _text->setAlignment(Qt::AlignCenter);

    QVBoxLayout* _layout = new QVBoxLayout;
    _layout->setSpacing(0);
    _layout->addStretch(1);
    _layout->addWidget(_text, 0, Qt::AlignBottom);
    setLayout(_layout);
}

void SubTab::setText(const QString& text)
{
    _text->setText(text);
}
