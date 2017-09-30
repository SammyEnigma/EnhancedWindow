#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QLabel>
#include <QMouseEvent>
#include <QTabBar>
#include <QStackedWidget>

#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Q_DISABLE_COPY(MainWindow)

    QWidget* _titleWidget;
    QLabel* _titleLabel;
    QVBoxLayout* _centralLayout;

    QPoint _grabPos;

    static const size_t MARGIN = 1;

protected:
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
