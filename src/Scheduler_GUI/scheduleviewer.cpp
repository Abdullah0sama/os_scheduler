#include "scheduleviewer.h"

ScheduleViewer::ScheduleViewer(const ScheduleList& scheduleList, QWidget *parent, QStackedWidget* stackedWidget)
    : QWidget{parent}
{
    this -> stackedWidget = stackedWidget;



    backButton = new QPushButton("Back");
    container = new QVBoxLayout(this);
    QTableWidget* grantChart = new QTableWidget();
    setupGrantChart(grantChart, scheduleList);
    container ->addWidget(grantChart);
    container -> addWidget(backButton);
    connect(backButton, SIGNAL (clicked()), this, SLOT (onBackClicked()));
}

void ScheduleViewer::setupGrantChart(QTableWidget* grantChart, const ScheduleList& schedule) {
//    const auto timeLine = schedule.getTimeline();
//    grantChart -> setRowCount(2);
//    grantChart -> setColumnCount(timeLine.size());
//    for(int i = 0; i < timeLine.size(); ++i) {
//        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(timeLine[i].getName()));
//        item ->tableWidget()
//        grantChart -> setItem(0, i, item);
//    }
}
void ScheduleViewer::onBackClicked() {
    stackedWidget -> removeWidget(this);
    delete this;
}
