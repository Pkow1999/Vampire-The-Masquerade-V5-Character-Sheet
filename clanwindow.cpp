#include "clanwindow.h"
#include "ui_clanwindow.h"

#include <QFile>
#include <QGraphicsPathItem>


ClanWindow::ClanWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClanWindow)
{
    ui->setupUi(this);
    ui->picture->setScaledContents(true);
    ui->comboBox->setCurrentIndex(1);
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
        ui->nicknames->setText(tr("The Clan of the Hunt, Assamites, Assassins, Mediators, Lawmen, Saracens, Children of Haqim (endonym), Judges"));
        ui->desc->setText(tr("Silent masters of assassination, killing for hire and collecting blood for rituals to bring them closer to their progenitor."));
        ui->bane->setText(tr("Sinner's Blood. + \n -- Tasting the blood of a Kindred provokes a Hunger frenzy (p.220)."));
        ui->compulsion->setText(tr("Until end of scene or tasting the blood of somebody acting against your Convicitions, you suffer a 3 dice penalty"));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Blood Sorcery\n") + tr("Celerity\n") + tr("Obfuscate\n"));
    }
    else if(index == 1){
        ui->nicknames->setText(tr("The Learned Clan, Warrior Scholars, Punks, Rebels, Rabble, Zealots, Agitators"));
        ui->desc->setText(tr("Once philosopher-kings of an ancient civilization, but are now rebels and rogues with a fearsome inclination toward frenzy."));
        ui->bane->setText(tr("Rage.\n -- Dice penalty of to resist fury frenzy (min. dice pool 1)."));
        ui->compulsion->setText(tr("Until rebeled against expecation or changing someone's minds, you have a 2-dice penalty on all rolls."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Potence\n") + tr("Celerity\n") + tr("Presence\n"));

    }
    else if(index == 2){
        ui->nicknames->setText(tr("Duskborn, Mercurians, The Young Ones, Run-Off, Weaklings, Chameleons"));
        ui->desc->setText(tr("Terms primarily used to refer to Caitiff and vampires of the 14th, or higher, generations. For centuries, the thin-blooded have been persecuted by elders, Gehenna cults, and other Noddists that fear their existence because Gehenna prophecies seem to indicate thin-blooded vampires are a sign of the End Times. "));
        ui->bane->setText(tr("Duskborn do not suffer from any clan bane."));
        ui->compulsion->setText(tr("Duskborn do not suffer from any clan compulsion. Instead, select a number of Thinblood Merits and Flaws."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Thin-Blood Alchemy"));
    }
    else if(index == 3){
        ui->nicknames->setText(tr("The Clan of the Beast,Animals, Bêtes, Outlanders, Outlaws, Wolf's-Heads"));
        ui->desc->setText(tr("Bestial and untamed, often coming to resemble the animals over which they demonstrate mastery."));
        ui->bane->setText(tr("Feral Features.\n -- Frenzy cause a number of feral features to manifest that reduce Attributes by 1 each."));
        ui->compulsion->setText(tr("Until the scene ends, you gain 3 dice penalty to Manipulation and Intelligence rolls."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Animalism\n") + tr("Fortitude\n") + tr("Protean\n"));
    }
    else if(index == 4){
        ui->nicknames->setText(tr("The Clan of Death, Necromancers, Graverobbers, The Family, Stiffs, Corpses, Devil-Kindred, Lazarenes"));
        ui->desc->setText(tr("An insular, extended family of vampires who practice the art of commanding the dead while commanding global finances."));
        ui->bane->setText(tr("Painful Bite.\n -- Mortals recoil in terror from a Hecata's bite. To resist, they have to pass a test on Stamina + Resolve (Diff. 2 + Bane Severity). Kindred resist falling to Terror Frenzy (Diff. 3).")) ;
        ui->compulsion->setText(tr("Until predicting or solving a death (i.e. as close as possible) lacking empathy and compassion, you suffer a 3-dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() +tr("Oblivion\n")+ tr("Auspex\n") + tr("Fortitude\n"));
    }
    else if(index == 5){
        ui->nicknames->setText(tr("The Night Clan, Abyss Mystics, Keepers, Magisters, Shadows, Traitors, Turncoats"));
        ui->desc->setText(tr("Proud nobles who command the very essence of darkness and shadow — to the point of worshipping it, some say."));
        ui->bane->setText(tr("Touched by the Abyss.\n -- Reflections & recordings are distorted. Use of Technology & avoiding electronic detection requires a test."));
        ui->compulsion->setText(tr("Until succeeding on a failed action, you suffer a two-dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Oblivion\n") + tr("Dominate\n") + tr("Potence\n"));
    }
    else if(index == 6){
        ui->nicknames->setText(tr("Kooks, Seers, Lunatics, Madmen, Cassandras, Children of Malkav, Clan of the Moon, Malks, Jesters"));
        ui->desc->setText(tr("A clan fractured by madness, each member irrevocably suffering under the yoke of insanity."));
        ui->bane->setText(tr("Derangement.\n -- When under effect of a bestial failure or a compulsion, delusions or visions cause a dice penalty to all rolls of the same category (i.e., Physical, Social, or Mental)."));
        ui->compulsion->setText(tr("Until end of the scene, you suffer a 2 dice penalty to Dexterity, Manipulation, Composure, Wits and all rolls to resist terror frenzy."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Auspex\n") + tr("Dominate\n") + tr("Obfuscate\n"));
    }
    else if(index == 7){
        ui->nicknames->setText(tr("Followers of Set, Judasians, Liberators, Corrupters, Tempters, Serpents, Setites, The Clan of Faith, the Clan of Lies, Typhonists, Sand-Snakes, Vipers"));
        ui->desc->setText(tr("Religious movement that evangelizes the example of a chthonic god, while seeking out the world’s secret places and protecting ancient artifacts."));
        ui->bane->setText(tr("Light Sensivity.\n -- Direct light causes dice penalties.\n -- Sunlight causes more aggrevated damage."));
        ui->compulsion->setText(tr("Until causing at least one Stain (i.e. for you or others), you suffer a 2 dice penalty to all rolls not related to this goal."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Obfuscate\n") + tr("Presence\n") + tr("Protean\n"));
    }
    else if(index == 8){
        ui->nicknames->setText(tr("The Clan of the Hidden, Sewer Rats, Lepers (archaic), Priors, Crawlers (Renaissance), Nossies"));
        ui->desc->setText(tr("Hideously disfigured by the Embrace, so they keep to the sewers shadows and traffic in the secrets they collect."));
        ui->bane->setText(tr("Hideous.\n -- Gain the Repulsive (2) Flaw at character creation.\n -- Dice penalty to disguise deformities."));
        ui->compulsion->setText(tr("Until you learn a useful secret, you suffer a 2 dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Obfuscate\n") + tr("Animalism\n") + tr("Potence\n"));
    }
    else if(index == 9){
        ui->nicknames->setText(tr("The Clanless, The Wretched, Freestylers,  Orphans, Trash, Unbound (endonym)"));
        ui->desc->setText(tr("Also known as the clanless, are rare Cainites that do not officially belong to any clan. These vampires have no inherent clan weakness, but no inherent disciplines as well. None of the typical clan markers apply to them. "));
        ui->bane->setText(tr("""Clanless.\n -- Learning disciplines requires more experience. (new Lvl x 6)\n -- At character creation: Suspect (1) Flaw & No Status Merit!\n -- Dice penalty on Social tests."));
        ui->compulsion->setText(tr("Caitiffs do not suffer from any clan compulsion."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("All and none"));
    }
    else if(index == 10){
        ui->nicknames->setText(tr("Rogues, Ravens, Daredevils, The Haunted, Gypsies, Criminals, Deceivers, Charlatans, Shapers, Seekers, Unwelcome, Hundred-Mask Clowns (by the Kuei-jin)"));
        ui->desc->setText(tr("Nomads and tricksters who can force the mind to see what isn’t there, though they are slaves to the vices they indulge in."));
        ui->bane->setText(tr("Doomed.\n -- When resting within a mile and a week of a previous resting place, you have to roll bane severity. Critial results (i.e. rolling 10s) cause aggrevated damage.\n -- You can't take the \"No Haven\" flaw at character creation"));
        ui->compulsion->setText(tr("You are compeled to perform the next task in the most daring and dangerous way. If not, you suffer a 2 dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Obfuscate\n") + tr("Presence\n")  + tr("Animalism\n"));
    }
    else if(index == 11){
        ui->nicknames->setText(tr("Unicorns, Soulsuckers, Cyclops, Soul-Thieves, Daijals, Saulot's progeny, the Hidden Ones, Peacemakers"));
        ui->desc->setText(tr("In the Final Nights, the once mighty Salubri Clan is considered barely a bloodline after the diablerie of their progenitor, Saulot. Their general few numbers grant credibility to the rumors that they are only composed of seven vampires at any time, and that these modern Salubri are fully committed to the search for Golconda – enacting a bloody ritual when they achieve that state or despair of ever doing so. "));
        ui->bane->setText(tr("Hunted.\n -- Your blood may cause Hunger Frenzy (Taste: Diff. 2* + Bane Severity & Smell: Diff. 4 at Hunger 4+)\n -- You have a Third Eye that can not be supernaturally concealed and bleeds when using Disciplines."));
        ui->compulsion->setText(tr("Until resolved or end of scene, you suffer a 2 dice penalty for any action not to reduce the suffering of others."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Auspex\n") + tr("Dominate\n") + tr("Fortitude\n"));
    }
    else if(index == 12){
        ui->nicknames->setText(tr("The Clan of the Rose, Artisans (archaic), Aesthetes, Vanitas, Epicureans (Renaissance), Degenerates, Torries"));
        ui->desc->setText(tr("Cainites that enjoy every sensual pleasure the world has to offer, idolizing physical beauty and the adoration of their thralls."));
        ui->bane->setText(tr("Desire of Beauty.\n -- Dice penalty to Discipline rolls, when in a less than beautiful enviroment."));
        ui->compulsion->setText(tr("Until the end of scene or losing sight of the center of your attention, you suffer a 2 dice penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Celerity\n") + tr("Presence\n") + tr("Auspex\n"));
    }
    else if(index == 13){
        ui->nicknames->setText(tr("The Broken Clan, Warlocks, Wizards, Magi, Usurpers, Grayfaces, Tremores ('Trembling Ones'), the Pyramid"));
        ui->desc->setText(tr("Vampiric sorcerers that wield the supernatural power of their past as a hermetic house, though they became vampires through treachery and artifice."));
        ui->bane->setText(tr("Loss of the Blood Bond.\n -- Kindred can not be bound by blood anymore.\n -- Mortals need to drink your blood a number of additional times to be blood bonded."));
        ui->compulsion->setText(tr("Until end of scene or critical win, you suffer a 2 dice penalty. Repeated action continous to reduce the penalty."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Blood Sorcery\n") + tr("Dominate\n") + tr("Auspex\n"));
    }
    else if(index == 14){
        ui->nicknames->setText(tr("Fiends, Dragons, Voivodes, The Old Clan, Stokers"));
        ui->desc->setText(tr("Eldritch Old World lords who have little in common with the mortal world and can manipulate flesh and bone at a whim."));
        ui->bane->setText(tr("Grounded.\n -- You suffer aggravated Willpower damage equal to Bane Severity when resting in a place, in which you are not surrounded by your possession."));
        ui->compulsion->setText(tr("Until possessing what you desire, you suffer a 2-dice penalty for any action not to ownership"));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Dominate\n")+ tr("Animalism\n") + tr("Protean\n"));
    }
    else if(index == 15){
        ui->nicknames->setText(tr("The Clan of Kings, Blue Bloods, Patricians, Warlords, Ambitiones, Power Mongers"));
        ui->desc->setText(tr("Observe the noblesse oblige of vampire society, though their entitlement and greed encourages them to seek ever more at the expense of others."));
        ui->bane->setText(tr("Rare Taste.\n -- Ventrue have a strict feeding preference. Might require a roll on Resolve + Awareness (min.Diff. 4) or expenditure of Willpower."));
        ui->compulsion->setText(tr("Until a non-supernatural order has been obeyed, you suffer a 2 dice penalty on all roll except Leadership."));
        ui->discplineList->setText(ui->discplineList->toPlainText() + tr("Dominate\n") + tr("Presence\n") + tr("Fortitude\n"));
    }
    pic.load("images/" + ui->comboBox->itemText(index) + ".png");
    ui->label->setText(ui->comboBox->itemText(index));
    ui->picture->setPixmap(pic);
}
