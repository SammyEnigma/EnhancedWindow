#ifndef TAB_H
#define TAB_H

#include <QScrollBar>
#include <QScrollArea>
#include <QPushButton>

#include "SubTab.h"

class Tab : public QWidget
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(Tab)

    QHBoxLayout* _subsLayout;
    QScrollArea* _scrollArea;
    QPushButton* _leftBtn;
    QPushButton* _rightBtn;

protected:
    void resizeEvent(QResizeEvent* event);

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
