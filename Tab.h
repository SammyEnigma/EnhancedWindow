#ifndef TAB_H
#define TAB_H

#include <QWidget>

#include "SubTab.h"

class Tab : public QWidget
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(Tab)

    QHBoxLayout* _layout;

protected:

public:
    Tab(QWidget* parent = nullptr);

    SubTab* insertSubTab(const QString& text, int pos = -1);
    void insertSubTab(SubTab* tab, int pos = -1);
    void removeSubTab(int pos);
    void removeSubTab(SubTab* tab);
    SubTab*subTabAt(int pos);

signals:

public slots:

};

#endif // TAB_H
