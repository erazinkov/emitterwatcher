#include "ipwidget.h"

#include <QRegularExpressionValidator>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QDebug>

IPWidget::IPWidget(QWidget *parent) : QWidget(parent)
{
    m_gridLayout = new QGridLayout;
    this->setLayout(m_gridLayout);
    m_lineEdit = new QLineEdit(this);
    m_label = new QLabel(this);
    m_button = new QPushButton("Start", this);

    m_timer = new QTimer(this);
    m_timer->setInterval(1'000);

    m_timerStop = new QTimer(this);
    m_timerStop->setInterval(1'000);

    m_elapsedTimer = new QElapsedTimer;

    m_time.setHMS(0, 0, 0);

    m_labelTime = new QLabel(this);
    m_labelTime->setText(m_time.toString("mm:ss"));

    m_process = new QProcess;
    m_label->setText("IP-address:");
    m_lineEdit->setAlignment(Qt::AlignCenter);
    m_lineEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_gridLayout->addWidget(m_label, 1, 1);
    m_gridLayout->addWidget(m_lineEdit, 1, 2);
    m_gridLayout->addWidget(m_button, 1, 3);
    m_gridLayout->addWidget(m_labelTime, 1, 4);
    m_gridLayout->setAlignment(Qt::AlignCenter);

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression ipRegex ("^" + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange + "$");
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipRegex, this);
    m_lineEdit->setValidator(ipValidator);

    connect(m_lineEdit, &QLineEdit::editingFinished, this, [&](){
//        m_process->start("ping", QStringList() << "-c" << "1" << QString(m_lineEdit->text()));
    });
    connect(m_process, &QProcess::started, this, [&](){
        QString str{"Connecting..."};
        emit(statusChanged(str));
    });
    connect(m_process, &QProcess::readyReadStandardOutput, this, [&](){
        QByteArray ba = m_process->readAllStandardOutput();
        ba = ba.simplified();
        ba = ba.trimmed();
        auto isUnreachable{ba.contains("Destination Host Unreachable")};
        auto isPacketLoss{!ba.contains("0% packet loss")};
        QString str{isUnreachable || isPacketLoss ? "Error" : "Ok"};
        emit(statusChanged(str));
        qInfo() << ba;
    });
    connect(m_process, &QProcess::readyReadStandardError, this, [&](){
        QByteArray ba = m_process->readAllStandardError();
        ba = ba.simplified();
        ba = ba.trimmed();
        QString str{"Error"};
        emit(statusChanged(str));
        qInfo() << ba;
    });


    connect(m_timer, &QTimer::timeout, this, [&](){
        if (m_process->state() != QProcess::Running) {
            m_process->start("ping", QStringList() << "-c" << "1" << QString(m_lineEdit->text()));
        }
    });

    connect(m_timerStop, &QTimer::timeout, this, [&](){
        m_time = m_time.addSecs(1);
        if (m_time.second() > 15) {
            m_time.setHMS(0, 0, 0);
        }
        m_labelTime->setText(m_time.toString("mm:ss"));
    });

    connect(m_button, &QPushButton::clicked, this, [&](){
        if (m_timer->isActive()) {
            m_timer->stop();
            m_lineEdit->setDisabled(false);
            m_button->setText("Start");
            return;
        }
        m_timer->start();
        m_lineEdit->setDisabled(true);
        m_button->setText("Stop");
    });

    connect(m_button, &QPushButton::clicked, this, [&](){
        if (m_timerStop->isActive()) {
            m_timerStop->stop();
            m_time.setHMS(0, 0, 0);
            m_labelTime->setText(m_time.toString("mm:ss"));
            return;
        }
        m_timerStop->start();
    });

}

QString IPWidget::ip() const
{
    return m_lineEdit->text();
}

void IPWidget::setIp(QString ip)
{
    m_lineEdit->setText(ip);
}
