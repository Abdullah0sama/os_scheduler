#include "scheduleviewer.h"

ScheduleViewer::ScheduleViewer(const ScheduleList& scheduleList, QWidget *parent, QStackedWidget* stackedWidget)
    : QWidget{parent}
{
    this -> stackedWidget = stackedWidget;


    backButton = new QPushButton("Back");
    container = new QVBoxLayout(this);
    QTableWidget* grantChart = new QTableWidget();
    QTableWidget* processMetrics = new QTableWidget();

    setupGrantChart(grantChart, scheduleList.getTimeline());
    setupProcessesMetrics(processMetrics, scheduleList);
    container ->addWidget(grantChart, 0);
    container -> addWidget(processMetrics, 0);
    container -> addWidget(backButton, 0, Qt::AlignRight);
    connect(backButton, SIGNAL (clicked()), this, SLOT (onBackClicked()));
}

void ScheduleViewer::setupGrantChart(QTableWidget* grantChart, const std::vector<TimeFrame>& timeLine) {
    grantChart -> setRowCount(2);
    grantChart -> setColumnCount(timeLine.size());
    grantChart -> setShowGrid(false);
//    grantChart -> setStyleSheet("QTableWidget::item{ border-left: 2px dashed white; } ");
    grantChart -> setMaximumHeight(this -> height() * 0.2);
    grantChart -> setFocusPolicy(Qt::NoFocus);
    grantChart -> setSelectionMode(QAbstractItemView::NoSelection);
    grantChart -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    grantChart -> setFrameStyle(QFrame::NoFrame);

    grantChart -> verticalHeader() -> setVisible(false);
    grantChart -> horizontalHeader() -> setVisible(false);


    int heightMainRow = grantChart -> height() * 0.8;
    grantChart -> setRowHeight(0, heightMainRow);
    grantChart -> setRowHeight(1, grantChart -> height() - heightMainRow);
    grantChart -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto backgroundColor = QBrush(QColor("#DDDDDD"));
    for(int i = 0; i < timeLine.size(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(timeLine[i].getName()));

        item -> setBackground(backgroundColor);
        item -> setTextAlignment(Qt::AlignCenter);
        grantChart -> setItem(0, i, item);

        grantChart -> setColumnWidth(i, std::max(uint(100) ,(timeLine[i].end - timeLine[i].start) * 5));
        QTableWidgetItem* time = new QTableWidgetItem(QString::number(timeLine[i].start));

        grantChart -> setItem(1, i, time);
    }
}
void ScheduleViewer::setupProcessesMetrics(QTableWidget* processTable, const ScheduleList& scheduleList) {
//    processTable -> setMaximumWidth(this -> width() * 0.75);
    processTable -> setRowCount(scheduleList.numberOfProcesses() + 1);
    processTable -> setColumnCount(3);
    processTable -> setHorizontalHeaderLabels({"", "Waiting Time", "TurnAround Time"});
    processTable -> setFocusPolicy(Qt::NoFocus);
    processTable -> setSelectionMode(QAbstractItemView::NoSelection);
    processTable -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    processTable -> setShowGrid(false);
    processTable -> verticalHeader() -> setVisible(false);
//    processTable -> setStyleSheet("QTableWidget::item { border-bottom: 1px solid black; } ");
    processTable -> setFrameStyle(QFrame::NoFrame);
    processTable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);

    const auto & process = scheduleList.getProcesses();
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    for(int i = 0; i < process.size(); ++i) {
        PMetric pmetric = scheduleList.getProcessMetric(process[i]);
        totalWaitingTime += pmetric.waitingTime;
        totalTurnAroundTime += pmetric.turnAroundTime;
        QTableWidgetItem* waitingTime = new QTableWidgetItem(QString::number(pmetric.waitingTime));
        QTableWidgetItem* turnAroundTime = new QTableWidgetItem(QString::number(pmetric.turnAroundTime));
        waitingTime -> setTextAlignment(Qt::AlignCenter);
        turnAroundTime -> setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *name = new QTableWidgetItem(QString::fromStdString(process[i]->getName()));
        name -> setTextAlignment(Qt::AlignCenter);
        processTable -> setItem(i, 0, name);
        processTable->setItem(i, 1, waitingTime);
        processTable->setItem(i, 2, turnAroundTime);
    }

    QTableWidgetItem* avgItem = new QTableWidgetItem();
    avgItem -> setTextAlignment(Qt::AlignCenter);
    avgItem -> setBackground(QBrush(QColor("#303841")));
    avgItem -> setForeground(QBrush(QColor("#EEEEEE"))  );
    QTableWidgetItem *avgWaitItem = avgItem->clone();
    QTableWidgetItem *avgTurnAroundItem = avgItem -> clone();
    avgWaitItem -> setText(QString::number((totalWaitingTime * 1.0) / scheduleList.numberOfProcesses()));
    avgTurnAroundItem -> setText(QString::number((totalTurnAroundTime * 1.0) / scheduleList.numberOfProcesses()));
    QTableWidgetItem *name = avgItem->clone();
    name -> setText("Average");
    processTable -> setItem(scheduleList.numberOfProcesses(), 0, name);
    processTable -> setItem(scheduleList.numberOfProcesses(), 1, avgWaitItem);
    processTable -> setItem(scheduleList.numberOfProcesses(), 2, avgTurnAroundItem);
}
void ScheduleViewer::onBackClicked() {
    stackedWidget -> removeWidget(this);
    delete this;
}
