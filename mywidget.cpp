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

    m_requestTimeoutLineEdit = new QLineEdit(this);
    m_requestTimeoutLabel = new QLabel(this);

    m_responseLineEdit = new QLineEdit(this);
    m_responseLabel = new QLabel(this);

    m_button = new QPushButton("Start", this);

    m_timer = new QTimer(this);
    m_timer->setInterval(1'000);

    m_time.setHMS(0, 0, 0);

    m_labelTime = new QLabel(this);
    m_labelTime->setText(m_time.toString("mm:ss"));

    m_process = new QProcess;
    m_processTimeout = new QProcess;
    m_requestLabel->setText("Request#1:");
    m_requestTimeoutLabel->setText("Request#2:");
    m_responseLabel->setText("Response:");

    m_labelTime->setAlignment(Qt::AlignCenter);
    m_gridLayout->addWidget(m_requestLabel, 1, 1);
    m_gridLayout->addWidget(m_requestLineEdit, 1, 2);
    m_gridLayout->addWidget(m_button, 1, 3);
    m_gridLayout->addWidget(m_requestTimeoutLabel, 2, 1);
    m_gridLayout->addWidget(m_requestTimeoutLineEdit, 2, 2);
    m_gridLayout->addWidget(m_labelTime, 2, 3);
    m_gridLayout->addWidget(m_responseLabel, 3, 1);
    m_gridLayout->addWidget(m_responseLineEdit, 3, 2);
    m_gridLayout->setAlignment(Qt::AlignCenter);

    connect(m_requestLineEdit, &QLineEdit::editingFinished, this, [&](){
        m_request = QString(m_requestLineEdit->text());
    });
    connect(m_requestTimeoutLineEdit, &QLineEdit::editingFinished, this, [&](){
        m_requestTimeout = QString(m_requestTimeoutLineEdit->text());
    });

    connect(m_process, &QProcess::readyReadStandardOutput, this, [=](){
        QByteArray ba = m_process->readAllStandardOutput();
        ba = ba.simplified();
        ba = ba.trimmed();
        auto isResponse{QString(ba).contains(QString(m_responseLineEdit->text()))};
        if (isResponse)
        {
            m_time.setHMS(0, 0, 0);
        }
    });
    connect(m_process, &QProcess::readyReadStandardError, this, [&](){
        QByteArray ba = m_process->readAllStandardError();
        ba = ba.simplified();
        ba = ba.trimmed();
        qInfo() << ba;
    });

    connect(m_timer, &QTimer::timeout, this, [&](){
        m_time = m_time.addSecs(1);
        if (m_time.second() > 10)
        {
            m_time.setHMS(0, 0, 0);
            if (m_processTimeout->state() != QProcess::Running)
            {
                QStringList requestList = m_requestTimeoutLineEdit->text().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
                if (requestList.size())
                {
                    QStringList argList = QStringList(requestList.begin() + 1, requestList.end());
                    m_processTimeout->start(requestList.first(), argList);
                }
            }
        }
        m_labelTime->setText(m_time.toString("mm:ss"));
        if (m_process->state() != QProcess::Running)
        {
            QStringList requestList = m_requestLineEdit->text().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            if (requestList.size())
            {
                QStringList argList = QStringList(requestList.begin() + 1, requestList.end());
                m_process->start(requestList.first(), argList);
            }
        }
    });

    connect(m_button, &QPushButton::clicked, this, [&](){
        if (m_timer->isActive()) {
            m_timer->stop();
            m_requestLineEdit->setDisabled(false);
            m_requestTimeoutLineEdit->setDisabled(false);
            m_responseLineEdit->setDisabled(false);
            m_button->setText("Start");
            m_time.setHMS(0, 0, 0);
            m_labelTime->setText(m_time.toString("mm:ss"));
            return;
        }
        m_timer->start();
        m_requestLineEdit->setDisabled(true);
        m_requestTimeoutLineEdit->setDisabled(true);
        m_responseLineEdit->setDisabled(true);
        m_button->setText("Stop");
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

QString MyWidget::requestTimeout() const
{
    return m_requestTimeoutLineEdit->text();
}

void MyWidget::setRequestTimeout(QString requestTimeout)
{
    m_requestTimeoutLineEdit->setText(requestTimeout);
}

QString MyWidget::response() const
{
    return m_responseLineEdit->text();
}

void MyWidget::setResponse(QString response)
{
    m_responseLineEdit->setText(response);
}
