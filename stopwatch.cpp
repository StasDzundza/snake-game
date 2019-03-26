#include "stopwatch.h"


stopwatch::stopwatch(QWidget *parent) :
    QDialog(parent)
{
    running = false;
}

stopwatch::~stopwatch()
{
    timer.stop();
}

QString stopwatch::GetTime()
{
    int ms = time_on_stopwatch.msecsSinceStartOfDay() + QTime::currentTime().msecsSinceStartOfDay() - last_start.msecsSinceStartOfDay();

    return QTime::fromMSecsSinceStartOfDay(ms).toString("mm:ss:zzz");
}

void stopwatch::Start()
{
   if(!timer.isActive())
    {
        last_start = QTime::currentTime();
        timer.start(20);
    }
}

void stopwatch::Stop()
{
    if(timer.isActive())
    {
        timer.stop();
        time_on_stopwatch = QTime::fromMSecsSinceStartOfDay(time_on_stopwatch.msecsSinceStartOfDay()+QTime::currentTime().msecsSinceStartOfDay()- last_start.msecsSinceStartOfDay());
    }
}

void stopwatch::Reset()
{
    timer.stop();
    time_on_stopwatch = QTime::fromMSecsSinceStartOfDay(0);
}
