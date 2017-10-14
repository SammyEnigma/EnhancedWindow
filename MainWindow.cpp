#include "MainWindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _titleBarWidget(nullptr),
      _extraBarWidget(nullptr),
      _windowColor("#2a579a")
{
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint);
    setMinimumSize(640, 480);

    _titleLabel = new QLabel("EnhancedWindow");
    _titleLabel->setAlignment(Qt::AlignCenter);

    QBitmap mask;
    QPixmap pxp;

    pxp = style()->standardIcon(QStyle::SP_TitleBarMinButton).pixmap(32, 32);
    mask = pxp.createMaskFromColor(Qt::transparent);
    pxp.fill(Qt::white);
    pxp.setMask(mask);
    QIcon minimizeIcon = pxp;

    pxp = style()->standardIcon(QStyle::SP_TitleBarMaxButton).pixmap(32, 32);
    mask = pxp.createMaskFromColor(Qt::transparent);
    pxp.fill(Qt::white);
    pxp.setMask(mask);
    QIcon maximizeIcon = pxp;

    pxp = style()->standardIcon(QStyle::SP_TitleBarCloseButton).pixmap(32, 32);
    mask = pxp.createMaskFromColor(Qt::transparent);
    pxp.fill(Qt::white);
    pxp.setMask(mask);
    QIcon closeIcon = pxp;

    QPushButton* _minimizeBtn = new QPushButton(minimizeIcon, "");
    _minimizeBtn->setFlat(true);
    _minimizeBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_minimizeBtn, &QPushButton::clicked, this, &QMainWindow::showMinimized);

    QPushButton* _maximizeBtn = new QPushButton(maximizeIcon, "");
    _maximizeBtn->setFlat(true);
    _maximizeBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_maximizeBtn, &QPushButton::clicked, this, [=] () {
        raise();

        mouseDoubleClickEvent(nullptr);
    });

    QPushButton* _closeBtn = new QPushButton(closeIcon, "");
    _closeBtn->setFlat(true);
    _closeBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(_closeBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    _titleWidget = new QWidget;
    _titleWidget->setStyleSheet("color: white; font-weight: bold; background: "+_windowColor.name(QColor::HexArgb)+";");
    _titleLayout = new QHBoxLayout;
    _titleLayout->setSpacing(0);
    _titleLayout->setMargin(0);
    _titleLayout->addWidget(_titleLabel, 1);
    _titleLayout->addWidget(_minimizeBtn);
    _titleLayout->addWidget(_maximizeBtn);
    _titleLayout->addWidget(_closeBtn);
    _titleWidget->setLayout(_titleLayout);

    _tabWidget = new QTabBar;
    _tabWidget->setDrawBase(false);
    _tabWidget->setStyleSheet("QTabBar { background: "+_windowColor.name(QColor::HexArgb)+"; border: none; }"
                              "QTabBar::tab { color: white; font-weight: bold; border: none; padding: 4px; }"
                              "QTabBar::tab:selected { color: "+_windowColor.name(QColor::HexArgb)+"; background: "+style()->standardPalette().midlight().color().name(QColor::HexArgb)+"; }");
    _tabWidget->setExpanding(false);

    _stackedWidget = new QStackedWidget;
    _stackedWidget->setMinimumHeight(50);
    _stackedWidget->setContentsMargins(0,2,0,2);
    _stackedWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    connect(_tabWidget, &QTabBar::currentChanged, _stackedWidget, &QStackedWidget::setCurrentIndex);

    QWidget* _barWidget = new QWidget;
    _barWidget->setStyleSheet("border: none; color: white; background: "+_windowColor.darker(120).name(QColor::HexArgb)+";");
    _barLayout = new QHBoxLayout;
    _barLayout->setSpacing(0);
    _barLayout->setMargin(0);
    _barLayout->addWidget(_tabWidget, 1);
    _barWidget->setLayout(_barLayout);

    _mainWidget = new QWidget;
    _mainWidget->setStyleSheet(".QWidget { background: white; border: 1px solid lightgray; }");

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

    QMainWindow::setCentralWidget(_centralWidget);
}

MainWindow::~MainWindow()
{

}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange)
    {
        if(windowState() == Qt::WindowMaximized)
            setContentsMargins(0,0,0,0);
        else
            setContentsMargins(MARGIN,MARGIN,MARGIN,MARGIN);

        return true;
    }

    return QMainWindow::event(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(windowState() != Qt::WindowMaximized)
        setWindowState(Qt::WindowMaximized);
    else
        setWindowState(Qt::WindowNoState);
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

Tab* MainWindow::insertTab(const QString& text, int pos)
{
    _tabWidget->addTab(text);
    Tab* tab = new Tab;
    _stackedWidget->insertWidget(pos < 0 ? _stackedWidget->count() : pos, tab);
    return tab;
}

void MainWindow::insertTab(const QString& text, Tab* tab, int pos)
{
    _tabWidget->addTab(text);
    _stackedWidget->insertWidget(pos < 0 ? _stackedWidget->count() : pos, tab);
}

void MainWindow::removeTab(int pos)
{
    if(pos < 0)
        return;

    _tabWidget->removeTab(pos);
    _stackedWidget->removeWidget(_stackedWidget->widget(pos));
}

void MainWindow::removeTab(Tab* tab)
{
    _tabWidget->removeTab(_stackedWidget->indexOf(tab));
    _stackedWidget->removeWidget(tab);
}

Tab* MainWindow::tabAt(int pos)
{
    return qobject_cast<Tab*>(_stackedWidget->widget(pos));
}

QWidget* MainWindow::mainWidget() const
{
    return _mainWidget;
}

void MainWindow::setMainWidget(QWidget* w)
{
    if(_mainWidget)
    {
        _centralLayout->removeWidget(_mainWidget);
        _mainWidget->deleteLater();
    }

    w->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    _centralLayout->addWidget(w);
    _mainWidget = w;
}

void MainWindow::setExtraBarWidget(QWidget* extraBarWidget)
{
    if(_extraBarWidget)
    {
        _barLayout->removeWidget(_extraBarWidget);
        _extraBarWidget->deleteLater();
    }

    if(extraBarWidget)
    {
        _barLayout->addWidget(extraBarWidget);
        _extraBarWidget = extraBarWidget;
    }
    else
    {
        _extraBarWidget = nullptr;
    }
}

void MainWindow::setTitleBarWidget(QWidget* titleBarWidget)
{
    if(_titleBarWidget)
    {
        _titleLayout->removeWidget(_titleBarWidget);
        _titleBarWidget->deleteLater();
    }

    if(titleBarWidget)
    {
        _titleLayout->insertWidget(0, titleBarWidget);
        _titleBarWidget = titleBarWidget;
    }
    else
    {
        _titleBarWidget = nullptr;
    }
}

void MainWindow::setWindowTitle(const QString& title)
{
    _titleLabel->setText(title);
}
