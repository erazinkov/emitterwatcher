#include "mywidget.h"

#include <QRegularExpressionValidator>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QDebug>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    m_gridLayout = new QGridLayout;
    this->setLayout(m_gridLayout);
    m_requestLineEdit = new QLineEdit(this);
    m_requestLabel = new QLabel(this);

    m_responseLineEdit = new QLineEdit(this);
    m_responseLabel = new QLabel(this);

    m_button = new QPushButton("Start", this);

    m_timer = new QTimer(this);
    m_timer->setInterval(1'000);

    m_time.setHMS(0, 0, 0);

    m_labelTime = new QLabel(this);
    m_labelTime->setText(m_time.toString("mm:ss"));

    m_process = new QProcess;
    m_requestLabel->setText("Request:");
    m_requestLineEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_responseLabel->setText("Response:");
    m_responseLineEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_gridLayout->addWidget(m_requestLabel, 1, 1);
    m_gridLayout->addWidget(m_requestLineEdit, 1, 2);
    m_gridLayout->addWidget(m_button, 1, 3);
    m_gridLayout->addWidget(m_labelTime, 1, 4);
    m_gridLayout->addWidget(m_responseLabel, 2, 1);
    m_gridLayout->addWidget(m_responseLineEdit, 2, 2);
    m_gridLayout->setAlignment(Qt::AlignCenter);



    connect(m_requestLineEdit, &QLineEdit::editingFinished, this, [&](){
        m_request = QString(m_requestLineEdit->text());
//        m_process->start("ping", QStringList() << "-c" << "1" << QString(m_lineEdit->text()));
    });
//    connect(m_process, &QProcess::started, this, [=](){

//    });
//    connect(m_process, &QProcess::readyReadStandardOutput, this, [=](){
//        QByteArray ba = m_process->readAllStandardOutput();
//        ba = ba.simplified();
//        ba = ba.trimmed();
//        auto isUnreachable{ba.contains("Destination Host Unreachable")};

//    });
//    connect(m_process, &QProcess::readyReadStandardError, this, [&](){
//        QByteArray ba = m_process->readAllStandardError();
//        ba = ba.simplified();
//        ba = ba.trimmed();

//    });

    connect(m_timer, &QTimer::timeout, this, [&](){
        m_time = m_time.addSecs(1);
        if (m_time.second() > 10)
        {
            m_time.setHMS(0, 0, 0);
        }
        m_labelTime->setText(m_time.toString("mm:ss"));
        if (m_process->state() != QProcess::Running)
        {
//            QStringList strList = m_request.split(" ",QString::SkipEmptyParts);

//            m_process->start("ping", QStringList() << "-c" << "1" << QString(m_lineEdit->text()));
        }
    });

    connect(m_button, &QPushButton::clicked, this, [&](){
        if (m_timer->isActive()) {
            m_timer->stop();
            m_requestLineEdit->setDisabled(false);
            m_button->setText("Start");
            m_time.setHMS(0, 0, 0);
            m_labelTime->setText(m_time.toString("mm:ss"));
            return;
        }
        m_timer->start();
        m_requestLineEdit->setDisabled(true);
        m_button->setText("Stop");
//        m_process->start("ping", QStringList() << "-c" << "1" << QString(m_lineEdit->text()));
    });

}

QString MyWidget::request() const
{
    return m_requestLineEdit->text();
}

void MyWidget::setRequest(QString request)
{
    m_requestLineEdit->setText(request);
}
