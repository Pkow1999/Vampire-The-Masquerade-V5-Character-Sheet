#include "statscounter.h"
#include "qabstractbutton.h"

#include <QCheckBox>

QList<int> *StatsCounter::getListOfNormalDices() const
{
    return listOfNormalDices;
}

QList<int> *StatsCounter::getListOfHungerDices() const
{
    return listOfHungerDices;
}

QStringList *StatsCounter::getPoolNames() const
{
    return poolNames;
}

QString StatsCounter::normalDiceString() const
{
    QStringList returnValue = QStringList();
    for(const int& dice : *listOfNormalDices) {
        returnValue.append(QString::number(dice));
    }
    return returnValue.join(" ");
}

QString StatsCounter::hungerDiceString() const
{
    QStringList returnValue = QStringList();
    for(const int& dice : *listOfHungerDices) {
        returnValue.append(QString::number(dice));
    }
    return returnValue.join(" ");
}

StatsCounter::StatsCounter() : listOfNormalDices(new QList<int>), listOfHungerDices(new QList<int>), poolNames(new QStringList()) {
    currentRollStatus = NO_CRIT;
    lastSuccesesCount = 0;
}

StatsCounter::~StatsCounter()
{
    qWarning() << "Stats counter d-tor\n";
    delete listOfNormalDices;
    delete listOfHungerDices;
    delete poolNames;
}

RollStatus StatsCounter::getCurrentRollStatus() const
{
    return currentRollStatus;
}

int StatsCounter::getLastSuccesesCount() const
{
    return lastSuccesesCount;
}

int StatsCounter::countDots(QButtonGroup *grp)
{
    int counter = 0;
    for(const QAbstractButton *button : grp->buttons()) {
        if(button->isChecked()) {
            ++counter;
        }
        else {
            break;
        }
    }
    return counter;
}

int StatsCounter::countSuccesses()
{
    int successCounter = 0;
    int crit = 0;
    int red_crit = 0;
    currentRollStatus = NO_CRIT;

    for(const int& num : *listOfNormalDices){
        if(num > 5) {
            ++successCounter;
        }
        if(num == 10) {
            ++crit;
        }
    }

    for(const int& num : *listOfHungerDices){
        if(num == 1){
            currentRollStatus = BESTIAL_FAILURE;
            continue;
        }
        if(num > 5) {
            ++successCounter;
        }

        if(num == 10) {
            ++crit;
            ++red_crit;
        }
    }

    if(crit / 2 > 0) {
        successCounter += crit - (crit % 2);
        currentRollStatus = NORMAL_CRIT;
    }

    int normal_crits = crit - red_crit;

    if(red_crit > 1 || (normal_crits % 2 == 1 && red_crit > 0)) {
        currentRollStatus = RED_CRIT;
    }
    lastSuccesesCount = successCounter;
    return successCounter;
}

QPair<int, int> StatsCounter::countIndicators(QLayout *layout, const int &size_)
{
    int superficial = 0;
    int agravated = 0;
    for(int i = 0; i < size_; i++)
    {
        QCheckBox *check = qobject_cast<QCheckBox *>(layout->itemAt(i)->widget());
        if(check->checkState() == Qt::CheckState::Checked)
            agravated++;
        if(check->checkState() == Qt::CheckState::PartiallyChecked)
            superficial++;
    }
    return QPair<int,int>(superficial, agravated);
}

