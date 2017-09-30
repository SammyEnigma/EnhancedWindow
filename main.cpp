#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Tab* tab1 = w.insertTab("Test1");
    tab1->insertSubTab(new SubTab("SubTab 1a", new QPushButton("TESTITEMS")));
    tab1->insertSubTab("SubTab 1b");
    tab1->insertSubTab("SubTab 1c");
    w.insertTab("Test2")->insertSubTab("SubTab 2");
    w.insertTab("Test3")->insertSubTab("SubTab 3");
    w.show();
    //w.setMainWidget(new QPushButton("Main Widget"));

    return a.exec();
}
