#include "clanwindow.h"
#include "ui_clanwindow.h"

#include <QFile>
#include <QGraphicsPathItem>


ClanWindow::ClanWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClanWindow)
{
    ui->setupUi(this);
    pic.load("images/Banu Haqim.png");
    ui->label->setText("Banu Haqim");
    ui->bane->setText(tr("Sinner's Blood. + \n -- Tasting the blood of a Kindred provokes a Hunger frenzy (p.220)."));
    ui->compulsion->setText(tr("Until end of scene or tasting the blood of somebody acting against your Convicitions, you suffer a 3 dice penalty"));
    ui->discplineList->setText(tr("Disciplines:\nBlood Sorcery\nCelerity\nObfuscate"));
    ui->picture->setPixmap(pic);
    ui->picture->setScaledContents(true);
    ClanWindow::setWindowTitle(tr("Clan Book"));
}

ClanWindow::~ClanWindow()
{
    qWarning() << "Destruktor klanów";
    delete ui;
}

void ClanWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->discplineList->setText(tr("Disciplines:\n"));
    if(index == 0){
        ui->bane->setText(tr("Sinner's Blood. + \n -- Tasting the blood of a Kindred provokes a Hunger frenzy (p.220)."));
        ui->compulsion->setText(tr("Until end of scene or tasting the blood of somebody acting against your Convicitions, you suffer a 3 dice penalty"));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Blood Sorcery\nCelerity\nObfuscate"));
    }
    else if(index == 1){
        ui->bane->setText(tr("Rage.\n -- Dice penalty of to resist fury frenzy (min. dice pool 1)."));
        ui->compulsion->setText(tr("Until rebeled against expecation or changing someone's minds, you have a 2-dice penalty on all rolls."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Potence\nCelerity\nPresence"));

    }
    else if(index == 2){
        ui->bane->setText(tr("Duskborn do not suffer from any clan bane."));
        ui->compulsion->setText(tr("Duskborn do not suffer from any clan compulsion. Instead, select a number of Thinblood Merits and Flaws."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Thin-Blood Alchemy"));
    }
    else if(index == 3){
        ui->bane->setText(tr("Feral Features.\n -- Frenzy cause a number of feral features to manifest that reduce Attributes by 1 each."));
        ui->compulsion->setText(tr("Until the scene ends, you gain 3 dice penalty to Manipulation and Intelligence rolls."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Animalism\nFortitude\nProtean"));
    }
    else if(index == 4){
        ui->bane->setText(tr("Painful Bite.\n -- Mortals recoil in terror from a Hecata's bite. To resist, they have to pass a test on Stamina + Resolve (Diff. 2 + Bane Severity). Kindred resist falling to Terror Frenzy (Diff. 3).")) ;
        ui->compulsion->setText(tr("Until predicting or solving a death (i.e. as close as possible) lacking empathy and compassion, you suffer a 3-dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Auspex\nOblivion\nFortitude"));
    }
    else if(index == 5){
        ui->bane->setText(tr("Touched by the Abyss.\n -- Reflections & recordings are distorted. Use of Technology & avoiding electronic detection requires a test."));
        ui->compulsion->setText(tr("Until succeeding on a failed action, you suffer a two-dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Dominate\nOblivion\nPotence"));
    }
    else if(index == 6){
        ui->bane->setText(tr("Derangement.\n -- When under effect of a bestial failure or a compulsion, delusions or visions cause a dice penalty to all rolls of the same category (i.e., Physical, Social, or Mental)."));
        ui->compulsion->setText(tr("Until end of the scene, you suffer a 2 dice penalty to Dexterity, Manipulation, Composure, Wits and all rolls to resist terror frenzy."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Auspex\nDominate\nObfuscate"));
    }
    else if(index == 7){
        ui->bane->setText(tr("Light Sensivity.\n -- Direct light causes dice penalties.\n -- Sunlight causes more aggrevated damage."));
        ui->compulsion->setText(tr("Until causing at least one Stain (i.e. for you or others), you suffer a 2 dice penalty to all rolls not related to this goal."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Presence\nProtean\nObfuscate"));
    }
    else if(index == 8){
        ui->bane->setText(tr("Hideous.\n -- Gain the Repulsive (2) Flaw at character creation.\n -- Dice penalty to disguise deformities."));
        ui->compulsion->setText(tr("Until you learn a useful secret, you suffer a 2 dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Animalism\nPotence\nObfuscate"));
    }
    else if(index == 9){
        ui->bane->setText(tr("""Clanless.\n -- Learning disciplines requires more experience. (new Lvl x 6)\n -- At character creation: Suspect (1) Flaw & No Status Merit!\n -- Dice penalty on Social tests."));
        ui->compulsion->setText(tr("Caitiffs do not suffer from any clan compulsion."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("All and none"));
    }
    else if(index == 10){
        ui->bane->setText(tr("Doomed.\n -- When resting within a mile and a week of a previous resting place, you have to roll bane severity. Critial results (i.e. rolling 10s) cause aggrevated damage.\n -- You can't take the \"No Haven\" flaw at character creation"));
        ui->compulsion->setText(tr("You are compeled to perform the next task in the most daring and dangerous way. If not, you suffer a 2 dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Animalism\nPresence\nObfuscate"));
    }
    else if(index == 11){
        ui->bane->setText(tr("Desire of Beauty.\n -- Dice penalty to Discipline rolls, when in a less than beautiful enviroment."));
        ui->compulsion->setText(tr("Until the end of scene or losing sight of the center of your attention, you suffer a 2 dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Auspex\nCelerity\nPresence"));
    }
    else if(index == 12){
        ui->bane->setText(tr("Loss of the Blood Bond.\n -- Kindred can not be bound by blood anymore.\n -- Mortals need to drink your blood a number of additional times to be blood bonded."));
        ui->compulsion->setText(tr("Until end of scene or critical win, you suffer a 2 dice penalty. Repeated action continous to reduce the penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Blood Sorcery\nDominate\nAuspex"));
    }
    else if(index == 13){
        ui->bane->setText(tr("Grounded.\n -- You suffer aggravated Willpower damage equal to Bane Severity when resting in a place, in which you are not surrounded by your possession."));
        ui->compulsion->setText(tr("Until possessing what you desire, you suffer a 2-dice penalty for any action not to ownership"));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Animalism\nDominate\nProtean"));
    }
    else if(index == 14){
        ui->bane->setText(tr("Rare Taste.\n -- Ventrue have a strict feeding preference. Might require a roll on Resolve + Awareness (min.Diff. 4) or expenditure of Willpower."));
        ui->compulsion->setText(tr("Until a non-supernatural order has been obeyed, you suffer a 2 dice penalty on all roll except Leadership."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Dominate\nFortitude\nPresence"));
    }

    pic.load("images/" + ui->comboBox->itemText(index) + ".png");
    ui->label->setText(ui->comboBox->itemText(index));
    ui->picture->setPixmap(pic);
}
