#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.insertTab("Test1")->insertSubTab("SubTab 1");
    w.insertTab("Test2")->insertSubTab("SubTab 2");
    w.insertTab("Test3")->insertSubTab("SubTab 3");
    w.show();
    //w.setMainWidget(new QPushButton("Main Widget"));

    return a.exec();
}
