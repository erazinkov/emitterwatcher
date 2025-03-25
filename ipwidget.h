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

class MyWidget : public QWidget
{
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_ENUMS(Status)
public:
    enum Status { UNKNOWN, DISCONNECTED, CONNECTED, CONNECTING };

    void setStatus(Status status)
    {
        m_status = status;
        emit statusChanged(status);
    }
    Status status() const
    {
        return m_status;
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.fillRect(0, 0, 20, 20, QBrush{m_color});
    }
signals:
    void statusChanged(Status status) {
        switch (status) {
        case UNKNOWN:
            setColor(QColorConstants::DarkYellow);
            break;
        case DISCONNECTED:
            setColor(QColorConstants::Red);
            break;
        case CONNECTED:
            setColor(QColorConstants::Green);
            break;
        case CONNECTING:
            setColor(QColorConstants::Yellow);
            break;
        }
    }
private:
    Status m_status;
    QColor m_color{QColorConstants::DarkYellow};

    void setColor(QColor color) {
        m_color = color;
        this->repaint();
    }
};

class IPWidget : public QWidget
{
public:
    IPWidget(QWidget *parent = nullptr);

    QString ip() const;
    void setIp(QString ip);

private:
    QGridLayout *m_gridLayout;
    QLineEdit *m_lineEdit;
    QLabel *m_label;
    QProcess *m_process;
    MyWidget *m_myWidget;

    QTimer *m_timer;
    QPushButton *m_button;

    QLabel *m_labelTime;
    QTime m_time;
};

#endif // IPWIDGET_H
