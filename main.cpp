#include "MainWindow.h"
#include <QApplication>

#include <QLineEdit>
#include <QToolButton>
#include <QAction>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Tab* tab1 = w.insertTab("Test1");
    tab1->insertSubTab(new SubTab("SubTab 1a", new QPushButton("TESTITEMS")));
    tab1->insertSubTab(new SubTab("SubTab 1b", new QLabel("TESTITEMS")));
    tab1->insertSubTab("SubTab 1c");
    tab1->insertSubTab("SubTab 1d");
    tab1->insertSubTab("SubTab 1e");
    tab1->insertSubTab("SubTab 1f");
    tab1->insertSubTab("SubTab 1g");
    tab1->insertSubTab("SubTab 1h");
    tab1->insertSubTab("SubTab 1i");
    tab1->insertSubTab("SubTab 1j");
    w.insertTab("Test2")->insertSubTab("SubTab 2");
    w.insertTab("Test3")->insertSubTab("SubTab 3");
    w.show();
    //w.setMainWidget(new QPushButton("Main Widget"));
    w.setExtraBarWidget(new QLineEdit("Text"));
    QToolButton* toolBtn = new QToolButton;
    toolBtn->setAutoRaise(true);
    toolBtn->setDefaultAction(new QAction(QIcon::fromTheme("folder"), "Action 1"));
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    toolBtn->addAction(new QAction("Action 2"));
    toolBtn->addAction(new QAction("Action 3"));
    w.setTitleBarWidget(toolBtn);

    return a.exec();
}
