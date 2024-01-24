#include "ScannerPortTCP.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QApplication>
// Константы
#define TIME_OUT 50 // Время остановки, необходимое для сканирования
#define END 1024    // Граница диапозона, в котором происхожит сканирование
// Описание портов
const QVector<QString> DESCRIPTION_PORT = {"stt", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "ms-rome", "unknown",
                         "unknown", "ms-v-worlds", "unknown", "unknown", "mdbs_daemon", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "ircs", "imap", "unknown", "unknown", "unknown", "unknown", "telnet", "msfw-control", "unknown",
                         "unknown", "conference", "unknown", "unknown", "xbox", "unknown", "rtsp", "unknown", "remotefs", "unknown",
                         "nntps", "cifs", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "afpovertcp", "unknown", "unknown", "ms-licensing", "unknown", "unknown", "unknown", "kpasswd",
                         "unknown", "unknown", "http", "unknown", "unknown", "unknown", "ms-sna-server", "unknown", "unknown",
                         "ms-cluster-net", "unknown", "tempo", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "ftp", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "ms-dotnetster", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "ingreslock",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "http-rpc-epmap", "unknown", "unknown",
                         "netbios-ssn", "unknown", "unknown", "unknown", "unknown", "unknown", "ftps-data", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "netnews", "mzap", "nicname", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "rtsps",
                         "unknown", "man", "unknown", "unknown", "unknown", "unknown", "unknown", "kerberos", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "close-combat", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "crs", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "kshell", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "sms-rcinfo", "unknown", "knetd", "unknown", "ms-sna-base", "login", "unknown",
                         "unknown", "rasadv", "unknown", "unknown", "unknown", "remote-winsock", "sqlsrv", "netbios-ns", "unknown",
                         "ms-shuttle", "unknown", "unknown", "courier", "directplay8", "sunrpc", "unknown", "unknown", "unknown",
                         "hostname", "doom", "ms-olap2", "unknown", "unknown", "unknown", "unknown", "unknown", "ms-theater", "wlbs",
                         "unknown", "unknown", "reserved", "unknown", "unknown", "unknown", "telnets", "unknown", "unknown", "bgp",
                         "unknown", "pcmail-srv", "unknown", "unknown", "unknown", "imip-channels", "unknown", "unknown", "unknown",
                         "systat", "echo", "kpop", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "ldaps", "unknown", "unknown", "unknown",
                         "unknown", "imaps", "directplay", "unknown", "unknown", "ms-olap1", "ms-rule-engine", "msdts1", "ws-discovery",
                         "unknown", "unknown", "unknown", "uucp-path", "unknown", "wsd", "unknown", "rrac", "unknown", "hosts2-ns",
                         "unknown", "unknown", "ssh", "unknown", "unknown", "time", "unknown", "qwave", "ms-sql-s", "unknown",
                         "unknown", "gopher", "unknown", "hmmp-ind", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "iso-tsap", "rtelnet", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "ms-sql-m", "msft-gc", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "dhcpv6-server", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "ms-la", "unknown", "http",
                         "unknown", "efs", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "whoami", "unknown", "unknown", "p2pgroup",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "sms-remctrl",
                         "unknown", "msft-gc-ssl", "unknown", "unknown", "unknown", "unknown", "ms-wbt-server", "unknown", "unknown",
                         "smtp", "unknown", "unknown", "unknown", "icslap", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "exec", "unknown", "ms-olap4", "unknown", "unknown", "msexch-routing", "unknown",
                         "https", "wsd", "unknown", "unknown", "unknown", "hmmp-op", "unknown", "dvcprov-port", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "pptp", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "llmnr", "unknown", "unknown", "unknown", "microsoft-ds", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "dhcpv6-client", "dccm", "unknown", "ftp-data",
                         "unknown", "unknown", "unknown", "ipsec-msft", "unknown", "unknown", "finger", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "teredo", "pop2", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "nntp", "sqlserv", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "domain", "msnp", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "nfa", "msmq", "unknown", "unknown", "unknown", "net-device", "unknown", "unknown", "unknown",
                         "qotd", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "print-srv", "ftps", "unknown", "unknown", "unknown", "irc", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "sql-net", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "directplaysrvr", "unknown", "unknown", "pptconference", "unknown", "activesync", "ulp",
                         "unknown", "unknown", "unknown", "unknown", "ms-streaming", "kerberos-adm", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "sms-chat", "daytime", "unknown", "unknown", "nfsd-status", "unknown", "chargen", "unknown",
                         "unknown", "unknown", "sms-xfer", "unknown", "unknown", "wins", "unknown", "unknown", "unknown", "irc-serv",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "cmd", "uucp", "unknown", "auth",
                         "opsmgr", "unknown", "unknown", "printer", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown",
                         "unknown", "pop3", "ms-olap3", "unknown", "ssdp", "klogin", "discard", "mftp", "unknown", "pop3s", "https",
                         "unknown", "nameserver", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "pnrp-port", "msolap-ptp2",
                         "unknown", "epmap", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "sdp-portmapper", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "ms-do",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "ldap", "unknown", "unknown", "unknown",
                         "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "unknown", "msiccp", "unknown", "unknown"
                         };

// Конструктор класса
ScannerPortTCP::ScannerPortTCP(QWidget *p) : QWidget(p) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this); // Создание основного макета окна программы
    QHBoxLayout* h_layout   = new QHBoxLayout;

    // Создание необходимых виджетов
    socket                = new QTcpSocket(this);
    button_start_scanning = new QPushButton;
    button_start_scanning->setText("&Нажмите для начала сканирования");
    connect(button_start_scanning, SIGNAL(clicked()), this, SLOT(on_button_start_scanning()));
    line_input            = new QLineEdit;
    line_input->setPlaceholderText("Введите порт...");
    field_output          = new QTextEdit;
    field_output->setReadOnly(true);

    // Настройка макета
    h_layout->addWidget(line_input);
    h_layout->addWidget(button_start_scanning);

    mainLayout->addLayout(h_layout);
    mainLayout->addWidget(field_output);
    setMinimumSize(500, 300); // Установка минимального размера окна программы
}

// Метод, вызываемый для начала сканирования узла
void ScannerPortTCP::on_button_start_scanning() {
    field_output->clear(); // Очистка предыдущего вывода
    line_input->setPlaceholderText("Введите порт..."); // Установка начального текста-подсказки

    // Обработка ситуации, когда пользователь не ввел порт
    if(line_input->text().isEmpty()) {
        line_input->setPlaceholderText("Пусто!");
        qDebug() << "Пользователь не ввел порт!";
    }
    else {
        qDebug() << "Начало сканирования..."; // Вывод сообщения о начале сканирования
        field_output->append("НАЧАЛО СКАНИРОВАНИЯ...");
        QString host = line_input->text();
        qDebug() << host;

        // Перебор портов в заданном диапазоне
        for(quint16 port = 0; port < END; port++) {
            socket->connectToHost(host, port);
            if(socket->waitForConnected(TIME_OUT)) { // Если удается установить подключение к хосту при помощи порта
                qInfo() << "Открыт порт: " << port;  // Вывод порта в консоль
                QString openPort = QString::number(port);
                field_output->append(openPort + "/tcp: " + DESCRIPTION_PORT[port]); // Вывод порта в поле для вывода
                socket->disconnectFromHost(); // Отсоединение от хоста
            }
            qApp->processEvents();
        }
        qDebug() << "Сканирование завершение"; // Вывод сообщения о завершении сканирования
        field_output->append("СКАНИРОВАНИЕ ЗАВЕРШЕНО!");
    }
}

