#include "OperatorsManagerWidget.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OperatorsManagerWidget w;
    w.show();
    return QApplication::exec();
}
