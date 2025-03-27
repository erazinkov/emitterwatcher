#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QProcess>
#include <QCheckBox>

#include <QTimer>
#include <QTime>
#include <QObject>
#include <QTextBrowser>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr);

    QString request() const;
    void setRequest(QString ip);

    QString requestTimeout() const;
    void setRequestTimeout(QString ip);

    QString response() const;
    void setResponse(QString ip);

private:
    QGridLayout *m_gridLayout;

    QString m_request;
    QLineEdit *m_requestLineEdit;
    QLabel *m_requestLabel;

    QString m_requestTimeout;
    QLineEdit *m_requestTimeoutLineEdit;
    QLabel *m_requestTimeoutLabel;


    QString m_response;
    QLineEdit *m_responseLineEdit;
    QLabel *m_responseLabel;


    QProcess *m_process;
    QProcess *m_processTimeout;

    QTimer *m_timer;
    QCheckBox *m_checkBox;

    QLabel *m_labelTime;
    QTime m_time;
    QTextBrowser *m_textBrowser;


};

#endif // MYWIDGET_H
