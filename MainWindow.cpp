#include "MainWindow.h"

#include <QApplication>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint);
    setMinimumSize(640, 480);

    _titleLabel = new QLabel("EnhancedWindow");
    _titleLabel->setAlignment(Qt::AlignCenter);

    QPushButton* _minimizeBtn = new QPushButton(style()->standardIcon(QStyle::SP_TitleBarMinButton), "");
    _minimizeBtn->setFlat(true);
    _minimizeBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_minimizeBtn, &QPushButton::clicked, this, &QMainWindow::showMinimized);

    QPushButton* _maximizeBtn = new QPushButton(style()->standardIcon(QStyle::SP_TitleBarMaxButton), "");
    _maximizeBtn->setFlat(true);
    _maximizeBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_maximizeBtn, &QPushButton::clicked, [=] () {
        raise();

        mouseDoubleClickEvent(nullptr);
    });

    QPushButton* _closeBtn = new QPushButton(style()->standardIcon(QStyle::SP_TitleBarCloseButton), "");
    _closeBtn->setFlat(true);
    _closeBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_closeBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    _titleWidget = new QWidget;
    _titleWidget->setStyleSheet("background: #4b6cb7;");
    QHBoxLayout* _titleLayout = new QHBoxLayout;
    _titleLayout->setSpacing(0);
    _titleLayout->setMargin(0);
    _titleLayout->addWidget(_titleLabel, 1);
    _titleLayout->addWidget(_minimizeBtn);
    _titleLayout->addWidget(_maximizeBtn);
    _titleLayout->addWidget(_closeBtn);
    _titleWidget->setLayout(_titleLayout);

    QTabBar* _tabWidget = new QTabBar;
    _tabWidget->setDrawBase(false);
    _tabWidget->setStyleSheet("QTabBar { background: #4b6cb7; border: none; }"
                              "QTabBar::tab { border: none; padding: 4px; }"
                              "QTabBar::tab:selected { background: "+style()->standardPalette().midlight().color().name(QColor::HexArgb)+"; }");
    _tabWidget->setExpanding(false);
    _tabWidget->addTab("Test1");
    _tabWidget->addTab("Test2");
    _tabWidget->addTab("Test3");

    QStackedWidget* _stackedWidget = new QStackedWidget;
    _stackedWidget->setMinimumHeight(50);

    QWidget* _barWidget = new QWidget;
    QHBoxLayout* _barLayout = new QHBoxLayout;
    _barLayout->setSpacing(0);
    _barLayout->setMargin(0);
    _barLayout->addWidget(_tabWidget, 1);
    _barWidget->setLayout(_barLayout);

    QWidget* _mainWidget = new QWidget;
    _mainWidget->setStyleSheet("background: white; border: 1px solid lightgray; ");

    QWidget* _centralWidget = new QWidget;
    _centralLayout = new QVBoxLayout;
    _centralLayout->setSpacing(0);
    _centralLayout->setMargin(0);
    _centralLayout->addWidget(_titleWidget, 0, Qt::AlignTop);
    _centralLayout->addWidget(_barWidget, 0, Qt::AlignTop);
    _centralLayout->addWidget(_stackedWidget, 0, Qt::AlignTop);
    _centralLayout->addWidget(_mainWidget, 1);
    _centralWidget->setLayout(_centralLayout);

    setContentsMargins(MARGIN,MARGIN,MARGIN,MARGIN);

    setCentralWidget(_centralWidget);

    setStatusBar(new QStatusBar());
}

MainWindow::~MainWindow()
{

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(windowState() != Qt::WindowMaximized)
    {
        setContentsMargins(MARGIN,MARGIN,MARGIN,MARGIN);
        setWindowState(Qt::WindowMaximized);
    }
    else
    {
        setContentsMargins(MARGIN,MARGIN,MARGIN,MARGIN);
        setWindowState(Qt::WindowNoState);
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(_titleLabel->geometry().contains(_titleWidget->mapFromGlobal(event->globalPos())))
        {
            _grabPos = event->pos();
            event->accept();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        if(!_grabPos.isNull())
        {
            if(windowState() == Qt::WindowMaximized)
            {
                setContentsMargins(MARGIN,MARGIN,MARGIN,MARGIN);
                setWindowState(Qt::WindowNoState);
            }

            event->accept();
            setCursor(Qt::ClosedHandCursor);
            move(event->globalPos()-_grabPos);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    setCursor(Qt::ArrowCursor);
    _grabPos = QPoint();
    event->accept();
}
