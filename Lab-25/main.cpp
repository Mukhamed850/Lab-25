#include "ScannerPortTCP.h"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    ScannerPortTCP w;
    w.show();
    return app.exec();
}
