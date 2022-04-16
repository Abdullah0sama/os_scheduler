#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("background: #3F72AF; color: #00092C ");
    QStringList schedulersNames = {"First Come First Serve", "Shortest Job First", "Priority", "Round Robin"};

    header = new QLabel("OS Scheduler");
    header -> setAlignment(Qt::AlignCenter);
    header -> setStyleSheet("font-size: 80px; font-weight:bold;margin:70px; color: #303841");

    schedulerSelect = new QComboBox();
    schedulerSelect -> addItems(schedulersNames);

    continueButton = new QPushButton("Continue");


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout -> addWidget(header);
    mainLayout -> addWidget(schedulerSelect);
    mainLayout -> addWidget(continueButton);

    mainLayout -> setAlignment(Qt::AlignCenter);

    QWidget *wid = new QWidget(this);
    wid -> setLayout(mainLayout);
    stackedWidget = new QStackedWidget();
    stackedWidget -> addWidget(wid);

    setCentralWidget(stackedWidget);
    setFixedSize(1000, 600);
    connect(continueButton, SIGNAL (clicked()), this, SLOT (onContinueButtonClicked()));
 }


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onContinueButtonClicked() {
    int type = 0;
    Scheduler *scheduler = nullptr;
    if(schedulerSelect -> currentText() == "Priority") {
        type = Scheduler::PRIORITY;
        scheduler = new Priority();
    } else if (schedulerSelect -> currentText() == "First Come First Serve") {
        type = Scheduler::FCFS;
        scheduler = new FCFS();
    } else if (schedulerSelect -> currentText() == "Shortest Job First") {
        type = Scheduler::SJF;
        scheduler = new SJF();
    } else if(schedulerSelect -> currentText() == "Round Robin") {
        type = Scheduler::RB;
        scheduler = new RR();
    }
    stackedWidget -> addWidget(new ProcessesManager(stackedWidget, scheduler, this, type));
    stackedWidget -> setCurrentIndex(stackedWidget -> count() - 1);

}

