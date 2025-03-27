#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QObject>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QProcess>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>

#include <QTimer>
#include <QTime>
#include <QObject>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr);

    QString request() const;
    void setRequest(QString ip);

private:
    QGridLayout *m_gridLayout;

    QString m_request;
    QLineEdit *m_requestLineEdit;
    QLabel *m_requestLabel;

    QString m_response;
    QLineEdit *m_responseLineEdit;
    QLabel *m_responseLabel;


    QProcess *m_process;

    QTimer *m_timer;
    QPushButton *m_button;

    QLabel *m_labelTime;
    QTime m_time;


};

#endif // MYWIDGET_H
