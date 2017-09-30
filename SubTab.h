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

    QLabel* _text;

protected:

public:
    SubTab(const QString& text, QWidget* parent = nullptr);

    void setText(const QString& text);

signals:

public slots:

};

#endif // SUBTAB_H
