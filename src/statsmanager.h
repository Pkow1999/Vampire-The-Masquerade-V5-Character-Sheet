#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <QAbstractButton>
#include <QButtonGroup>
#include <QLayout>
#include "rollstatus.hpp"

class StatsManager
{
private:
    RollStatus currentRollStatus;
    int lastSuccesesCount;
    QList<int> *listOfNormalDices;
    QList<int> *listOfHungerDices;
    QStringList *poolNames;

public:
    StatsManager();
    ~StatsManager();
    int countDots(QButtonGroup *grp);
    int countSuccesses();
    QPair<int, int> countIndicators(QLayout *layout, const int &size_);
    RollStatus getCurrentRollStatus() const;
    int getLastSuccesesCount() const;
    QList<int> *getListOfNormalDices() const;
    QList<int> *getListOfHungerDices() const;
    QStringList *getPoolNames() const;
    QString normalDiceString() const;
    QString hungerDiceString() const;
    void generateDices(const int& diceAmount, const int& hungerLevel);
    void rerollDices(const QList<int>& rerollIndexes);
};

#endif // STATSMANAGER_H
