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
    container ->addWidget(grantChart, 50);
    container -> addWidget(processMetrics, 0);
    container -> addWidget(backButton, 0, Qt::AlignRight);
    connect(backButton, SIGNAL (clicked()), this, SLOT (onBackClicked()));
}

void ScheduleViewer::setupGrantChart(QTableWidget* grantChart, const std::vector<TimeFrame>& timeLine) {
    grantChart -> setRowCount(2);
    grantChart -> setColumnCount(timeLine.size() + 1);
    grantChart -> setShowGrid(false);
    grantChart -> setMaximumHeight(this -> height() * 0.2);
    grantChart -> setFocusPolicy(Qt::NoFocus);
    grantChart -> setSelectionMode(QAbstractItemView::NoSelection);
    grantChart -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    grantChart -> setFrameStyle(QFrame::NoFrame);

    grantChart -> verticalHeader() -> setVisible(false);
    grantChart -> horizontalHeader() -> setVisible(false);


    int heightMainRow = grantChart -> height() * 0.6;
    grantChart -> setRowHeight(0, heightMainRow);
    grantChart -> setRowHeight(1,  grantChart -> height() * 0.2);
    grantChart -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grantChart -> setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    auto backgroundColor = QBrush(QColor("#DDDDDD"));
    for(int i = 0; i < timeLine.size(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(timeLine[i].getName()));

        item -> setBackground(backgroundColor);
        item -> setTextAlignment(Qt::AlignCenter);
        grantChart -> setItem(0, i, item);

        grantChart -> setColumnWidth(i, std::min(uint(150) ,(timeLine[i].end - timeLine[i].start) * 5));
        QTableWidgetItem* time = new QTableWidgetItem(QString::number(timeLine[i].start));

        grantChart -> setItem(1, i, time);
    }
    grantChart -> setItem(1, timeLine.size(), new QTableWidgetItem(QString::number(timeLine[timeLine.size() - 1].end)));
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
    processTable -> setFrameStyle(QFrame::NoFrame);
    processTable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);

    const auto & process = scheduleList.getProcesses();
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;



    for(int i = 0; i < process.size(); ++i) {
        PMetric pmetric = scheduleList.getProcessMetric(process[i]);
        totalWaitingTime += pmetric.waitingTime;
        totalTurnAroundTime += pmetric.turnAroundTime;

        QTableWidgetItem* waitingTime = makeCell(QString::number(pmetric.waitingTime));
        QTableWidgetItem* turnAroundTime = makeCell(QString::number(pmetric.turnAroundTime));
        QTableWidgetItem *name = makeCell(QString::fromStdString(process[i]->getName()));

        processTable -> setItem(i, 0, name);
        processTable->setItem(i, 1, waitingTime);
        processTable->setItem(i, 2, turnAroundTime);
    }


    QTableWidgetItem *avgWaitItem = makeCell(QString::number((totalWaitingTime * 1.0) / scheduleList.numberOfProcesses()),
                                             "#303841", "#EEEEEE");
    QTableWidgetItem *avgTurnAroundItem = makeCell(QString::number((totalTurnAroundTime * 1.0) / scheduleList.numberOfProcesses()),
                                                   "#303841", "#EEEEEE");
    QTableWidgetItem *name = makeCell("Average", "#303841", "#EEEEEE");

    processTable -> setItem(scheduleList.numberOfProcesses(), 0, name);
    processTable -> setItem(scheduleList.numberOfProcesses(), 1, avgWaitItem);
    processTable -> setItem(scheduleList.numberOfProcesses(), 2, avgTurnAroundItem);
}
void ScheduleViewer::onBackClicked() {
    stackedWidget -> removeWidget(this);
    delete this;
}

QTableWidgetItem* ScheduleViewer::makeCell(const QString& text, const QString& bckColor, const QString& frgColor) {
    QTableWidgetItem *cell= new QTableWidgetItem(text);
    cell -> setTextAlignment(Qt::AlignCenter);
    cell -> setBackground(QBrush(QColor(bckColor)));
    cell -> setForeground(QBrush(QColor(frgColor)));
    return cell;
}
