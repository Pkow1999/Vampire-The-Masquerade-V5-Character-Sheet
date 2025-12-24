#include "statsmanager.h"
#include "qabstractbutton.h"

#include <QCheckBox>
#include <QRandomGenerator>

QList<int> *StatsManager::getListOfNormalDices() const
{
    return listOfNormalDices;
}

QList<int> *StatsManager::getListOfHungerDices() const
{
    return listOfHungerDices;
}

QStringList *StatsManager::getPoolNames() const
{
    return poolNames;
}

QString StatsManager::normalDiceString() const
{
    QStringList returnValue = QStringList();
    for (const int &dice : *listOfNormalDices) {
        returnValue.append(QString::number(dice));
    }
    return returnValue.join(" ");
}

QString StatsManager::hungerDiceString() const
{
    QStringList returnValue = QStringList();
    for (const int &dice : *listOfHungerDices) {
        returnValue.append(QString::number(dice));
    }
    return returnValue.join(" ");
}

void StatsManager::generateDices(const int &diceAmount, const int &hungerLevel)
{
    listOfNormalDices->clear();
    listOfHungerDices->clear();

    for(int i = 0 ; i < diceAmount - hungerLevel; ++i) {
        listOfNormalDices->append(QRandomGenerator::system()->bounded(10) + 1);
    }

    for(int i = 0; i < (hungerLevel > diceAmount ? diceAmount : hungerLevel); ++i) {
        listOfHungerDices->append(QRandomGenerator::system()->bounded(10) + 1);
    }
    countSuccesses();
}

void StatsManager::rerollDices(const QList<int> &rerollIndexes)
{
    for(const int& index : rerollIndexes) {
        if(index < listOfNormalDices->size()) {
            listOfNormalDices->replace(index, QRandomGenerator::system()->bounded(10) + 1);
        } else {
            int hungerIndex = index - listOfNormalDices->size();
            listOfHungerDices->replace(hungerIndex, QRandomGenerator::system()->bounded(10) + 1);
        }
    }
    countSuccesses();
}

StatsManager::StatsManager()
    : listOfNormalDices(new QList<int>)
    , listOfHungerDices(new QList<int>)
    , poolNames(new QStringList())
{
    currentRollStatus = NO_CRIT;
    lastSuccesesCount = 0;
}

StatsManager::~StatsManager()
{
    qWarning() << "Stats counter d-tor\n";
    delete listOfNormalDices;
    delete listOfHungerDices;
    delete poolNames;
}

RollStatus StatsManager::getCurrentRollStatus() const
{
    return currentRollStatus;
}

int StatsManager::getLastSuccesesCount() const
{
    return lastSuccesesCount;
}

int StatsManager::countDots(QButtonGroup *grp)
{
    int counter = 0;
    for (const QAbstractButton *button : grp->buttons()) {
        if (button->isChecked()) {
            ++counter;
        } else {
            break;
        }
    }
    return counter;
}

int StatsManager::countSuccesses()
{
    int successCounter = 0;
    int crit = 0;
    int red_crit = 0;
    currentRollStatus = NO_CRIT;

    for (const int &num : *listOfNormalDices) {
        if (num > 5) {
            ++successCounter;
        }
        if (num == 10) {
            ++crit;
        }
    }

    for (const int &num : *listOfHungerDices) {
        if (num == 1) {
            currentRollStatus = BESTIAL_FAILURE;
            continue;
        }
        if (num > 5) {
            ++successCounter;
        }

        if (num == 10) {
            ++crit;
            ++red_crit;
        }
    }

    if (crit / 2 > 0) {
        successCounter += crit - (crit % 2);
        currentRollStatus = NORMAL_CRIT;
    }

    int normal_crits = crit - red_crit;

    if (red_crit > 1 || (normal_crits % 2 == 1 && red_crit > 0)) {
        currentRollStatus = RED_CRIT;
    }
    lastSuccesesCount = successCounter;
    return successCounter;
}

QPair<int, int> StatsManager::countIndicators(QLayout *layout, const int &size_)
{
    int superficial = 0;
    int agravated = 0;
    for (int i = 0; i < size_; i++) {
        QCheckBox *check = qobject_cast<QCheckBox *>(layout->itemAt(i)->widget());
        if (check->checkState() == Qt::CheckState::Checked)
            agravated++;
        if (check->checkState() == Qt::CheckState::PartiallyChecked)
            superficial++;
    }
    return QPair<int, int>(superficial, agravated);
}
