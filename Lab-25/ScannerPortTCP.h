#ifndef SCANNER_PORT_TCP_H
#define SCANNER_PORT_TCP_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QLabel>

class ScannerPortTCP : public QWidget {
    Q_OBJECT
private:
    QLineEdit*   line_input;
    QTextEdit *  field_output;
    QPushButton* button_start_scanning;
    QTcpSocket*  socket;
private slots:
    void on_button_start_scanning();
public:
    ScannerPortTCP(QWidget *p = nullptr);
};
#endif
