#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *widget = new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QGridLayout *layout = new QGridLayout;
    widget->setLayout(layout);
    setCentralWidget(widget);

    m_ipWidget = new IPWidget(this);
    layout->addWidget(m_ipWidget);

    readSettings();

    connect(m_ipWidget, &IPWidget::statusChanged, this, &MainWindow::statusBarChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void MainWindow::statusBarChanged(const QString &str)
{
    ui->statusbar->showMessage(str);
}

void MainWindow::writeSettings()
{
    QSettings settings("Diamant LTD", "Emitter Watcher");
    settings.beginGroup("MainWindow");
    auto ip = m_ipWidget->ip();
    settings.setValue("ip", m_ipWidget->ip());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("Diamant LTD", "Emitter Watcher");
    settings.beginGroup("MainWindow");
    auto ip = settings.value("ip").toString();
    m_ipWidget->setIp(settings.value("ip").toString());
    settings.endGroup();
}
