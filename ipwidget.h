#ifndef IPWIDGET_H
#define IPWIDGET_H

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

#include <QElapsedTimer>

class IPWidget : public QWidget
{
    Q_OBJECT
public:
    IPWidget(QWidget *parent = nullptr);

    QString ip() const;
    void setIp(QString ip);

signals:
    void statusChanged(const QString &);

private:
    QGridLayout *m_gridLayout;
    QLineEdit *m_ipLineEdit;
    QLineEdit *m_commandLineEdit;
    QLabel *m_label;
    QProcess *m_process;

    QTimer *m_timer;
    QTimer *m_timerStop;
    QElapsedTimer *m_elapsedTimer;
    QPushButton *m_button;

    QLabel *m_labelTime;
    QTime m_time;
};

#endif // IPWIDGET_H
