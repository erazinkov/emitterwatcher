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

    m_myWidget = new MyWidget(this);
    layout->addWidget(m_myWidget);

    readSettings();
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

void MainWindow::writeSettings()
{
    QSettings settings("Diamant LTD", "Emitter Watcher");
    settings.beginGroup("MainWindow");
    auto request = m_myWidget->request();
    settings.setValue("request", request);
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("Diamant LTD", "Emitter Watcher");
    settings.beginGroup("MainWindow");
    auto request = settings.value("request").toString();
    m_myWidget->setRequest(request);
    settings.endGroup();
}
