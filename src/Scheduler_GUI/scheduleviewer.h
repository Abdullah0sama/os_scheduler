#ifndef SCHEDULEVIEWER_H
#define SCHEDULEVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include "../ScheduleList.h"
#include "../TimeFrame.h"
#include <QString>
#include <QDebug>
#include <QVBoxLayout>
#include <QTableWidget>

class ScheduleViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleViewer(const ScheduleList& scheduleList, QWidget *parent = nullptr, QStackedWidget *stackedWidget = nullptr);
private:
    QStackedWidget *stackedWidget;
    QPushButton *backButton;
    QVBoxLayout *container;

    void setupGrantChart(QTableWidget* grantChart, const ScheduleList& schedule);
private slots:
    void onBackClicked();
signals:


};

#endif // SCHEDULEVIEWER_H
