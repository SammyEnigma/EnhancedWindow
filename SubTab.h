#ifndef SUBTAB_H
#define SUBTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QPalette>

class SubTab : public QWidget
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(SubTab)

    QVBoxLayout* _layout;
    QWidget* _itemsWidget;
    QLabel* _text;

protected:

public:
    SubTab(const QString& text, QWidget* itemsWidget = nullptr, QWidget* parent = nullptr);

    void setText(const QString& text);

    QWidget* setItemsWidget(QWidget* itemsWidget);
    QWidget* itemsWidget() const;

signals:

public slots:

};

#endif // SUBTAB_H
