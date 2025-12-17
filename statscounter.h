#ifndef STATSCOUNTER_H
#define STATSCOUNTER_H

#include <QButtonGroup>
#include <QLayout>
#include <QAbstractButton>
#include "rollstatus.hpp"

class StatsCounter
{
private:
    RollStatus currentRollStatus;
    int lastSuccesesCount;
    QList<int> *listOfNormalDices;
    QList<int> *listOfHungerDices;
    QStringList *poolNames;
public:
    StatsCounter();
    ~StatsCounter();
    int countDots(QButtonGroup *grp);
    int countSuccesses();
    QPair<int, int> countIndicators(QLayout *layout,const int &size_);
    RollStatus getCurrentRollStatus() const;
    int getLastSuccesesCount() const;
    QList<int> *getListOfNormalDices() const;
    QList<int> *getListOfHungerDices() const;
    QStringList *getPoolNames() const;
    QString normalDiceString() const;
    QString hungerDiceString() const;
};

#endif // STATSCOUNTER_H
