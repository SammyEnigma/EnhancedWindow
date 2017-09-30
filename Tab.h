#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>

#include "SubTab.h"

class Tab : public QWidget
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(Tab)

    QHBoxLayout* _layout;

protected:
    void paintEvent(QPaintEvent* event);

public:
    Tab(QWidget* parent = nullptr);

    SubTab* insertSubTab(const QString& text, int pos = -1);
    void insertSubTab(SubTab* subtab, int pos = -1);
    void removeSubTab(int pos);
    void removeSubTab(SubTab* subtab);
    SubTab*subTabAt(int pos);

signals:

public slots:

};

#endif // TAB_H
