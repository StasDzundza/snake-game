#define CATCH_CONFIG_RUNNER

#include "mainwindow.h"
#include <QApplication>
#include "Tests/catch2/catch.hpp"
#include "tests.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Catch::Session().run();
    MainWindow w;
    w.show();
    
    return a.exec();
}
