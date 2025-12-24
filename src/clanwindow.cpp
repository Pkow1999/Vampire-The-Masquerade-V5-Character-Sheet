#include "clanwindow.h"
#include "ui_clanwindow.h"

#include <QFile>
#include <QGraphicsPathItem>

ClanWindow::ClanWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::ClanWindow)
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

void ClanWindow::setClanWindowText(const QString &nicknames,
                                   const QString &description,
                                   const QString &bane,
                                   const QString &alternative,
                                   const QString &compulsion,
                                   const QStringList &disciplineList)
{
    ui->nicknames->setText(nicknames);
    ui->desc->setText(description);
    if (ui->checkBox->isChecked() && !alternative.isEmpty()) {
        ui->bane->setText(alternative);
    } else {
        ui->bane->setText(bane);
    }
    ui->compulsion->setText(compulsion);
    ui->discplineList->setText(ui->discplineList->toPlainText() + disciplineList.join("\n"));
}

void ClanWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->discplineList->setText(tr("Disciplines:\n"));
    switch (index) {
    case 0: //Banu Haqim
        setClanWindowText(
            tr("The Clan of the Hunt, Assamites, Assassins, Mediators, Lawmen, Saracens, Children "
               "of Haqim (endonym), Judges"),
            tr("Silent masters of assassination, killing for hire and collecting blood for rituals "
               "to bring them closer to their progenitor."),
            tr("Blood Addiction - When the Banu Haqim slakes at least one Hunger level from "
               "another vampire, they must make a Hungry Frenzy test at difficulty 2 plus Bane "
               "Severity. If they fail, they must gorge themselves on vitae, in turn opening the "
               "door to possible Diablerie."),
            tr("Noxious Blood - The Blood of the Banu Haqim is toxic to mortals, but not to other "
               "vampires. Due to this mortals receive Aggravated Damage equal to the Bane Severity "
               "of the vampire for each Rouse Check’s worth of Blood consumed. Their Blood cannot "
               "be used to heal mortal injuries. In amounts below the amount needed to Blood Bond, "
               "it does not harm them, even if directly injected into them."),
            tr("Judgement - Urged to punish a wrongdoer, the vampire must slake one Hunger from "
               "anyone that acts against their own Convictions. Failing to do so results in a "
               "three-dice penalty to all rolls until the Compulsion is satisfied or the scene "
               "ends. Should the victim be a vampire, the Bane applies."),
            {tr("Blood Sorcery"), tr("Celerity"), tr("Obfuscate")});
        break;
    case 1: //Brujah
        setClanWindowText(
            tr("The Learned Clan, Warrior Scholars, Punks, Rebels, Rabble, Zealots, Agitators"),
            tr("Once philosopher-kings of an ancient civilization, but are now rebels and rogues "
               "with a fearsome inclination toward frenzy."),
            tr("Violent Temper - A rage is simmering in the back of the mind with a Brujah with "
               "the slightest provocation able to send them into a frenzied rage. Subtracts dice "
               "equal to the Bane Severity of the Brujah against Fury Frenzy"),
            tr("Violence - When a messy critical occurs as the result of any Skill test, a Brujah "
               "vampire causes damage to the subject of their interaction equal to their Bane "
               "Severity, in addition to any other result of the Hunger dice. The type of damage "
               "is dependent on the situation either physical or mental. The damage is Aggravated "
               "unless the player spends a point of Willpower to turn it into Superficial."),
            tr("Rebellion - The Brujah craves to take a stance against those who represent the "
               "status quo. This does not relent until they have gone against orders, "
               "expectations, or changed someone's mind. During this Compulsion, they suffer a -2 "
               "to dice all pools."),
            {tr("Potence"), tr("Celerity"), tr("Presence")});
        break;
    case 2:
        setClanWindowText(
            tr("Duskborn, Mercurians, The Young Ones, Run-Off, Weaklings, Chameleons"),
            tr("Terms primarily used to refer to Caitiff and vampires of the 14th, or higher, "
               "generations. For centuries, the thin-blooded have been persecuted by elders, "
               "Gehenna cults, and other Noddists that fear their existence because Gehenna "
               "prophecies seem to indicate thin-blooded vampires are a sign of the End Times."),
            tr("Duskborn do not suffer from any clan bane."),
            tr(""),
            tr("Duskborn do not suffer from any clan compulsion. Instead, select a number of "
               "Thinblood Merits and Flaws."),
            {tr("Thin-Blood Alchemy")});
        break;
    case 3: //Gangrel
        setClanWindowText(
            tr("The Clan of the Beast,Animals, Bêtes, Outlanders, Outlaws, Wolf's-Heads"),
            tr("Bestial and untamed, often coming to resemble the animals over which they "
               "demonstrate mastery."),
            tr("Bestial Features - In Frenzy, Gangrel gains animalistic features equal to their "
               "Bane Severity. These features last for one more night afterward, each feature "
               "reducing one Attribute by 1 point. The Gangrel may choose to Ride the Wave in "
               "order to only have one feature manifest and only lose one Attribute point."),
            tr("Survival Instincts - Subtract dice equal to the Bane Severity in any roll to "
               "resist fear Frenzy. The pool cannot be below one die."),
            tr("Feral Impulses - Unleash the animal hidden in their Blood. This urges the Gangrel "
               "to regress into an animalistic state where speech becomes difficult, clothes "
               "become too constrictive and arguments and best settled with claws and teeth. For "
               "one scene the Gangrel suffers a -3 dice penalty to all rolls involving "
               "Manipulation and Intelligence as they are only able to speak one word sentences "
               "during this Compulsion."),
            {tr("Animalism"), tr("Fortitude"), tr("Protean")});
        break;
    case 4: //Hecata
        setClanWindowText(
            tr("The Clan of Death, Necromancers, Graverobbers, The Family, Stiffs, Corpses, "
               "Devil-Kindred, Lazarenes"),
            tr("An insular, extended family of vampires who practice the art of commanding the "
               "dead while commanding global finances."),
            tr("Decay - Hecata suffer additional dots in Flaws equal to their Bane Severity spread "
               "as they see fit across Retainer, Haven, and Resources Flaws. These Flaws can "
               "either be taken at Character Creation or removed by paying twice the amount of "
               "Background dots. Additionally, any purchase of dots in these Advantages costs an "
               "additional amount of experience points equal to their Bane Severity."),
            tr("Painful Kiss - Hecata may only take harmful drinks from mortals which result in "
               "blood loss. Unwilling mortals that are able to escape will make the attempt, even "
               "those who are convinced or willing must succeed in a Stamina + Resolve test "
               "against Difficulty 2 + Bane Severity in order to not recoil. Vampires who are "
               "willingly bit must make a Frenzy test against Difficulty 3 to avoid terror "
               "Frenzy."),
            tr("Morbidity - The vampire must move something from life to death or vice versa, any "
               "action not taken to end or resurrect something suffers a two-dice penalty. The "
               "subject does not have to be a living thing and can instead be an object or more "
               "abstract such as ideas or conversation points. This Compulsion lasts until their "
               "manage to kill or return something to life. "),
            {tr("Oblivion"), tr("Auspex"), tr("Fortitude")});
        break;
    case 5: //Lasombra
        setClanWindowText(
            tr("The Night Clan, Abyss Mystics, Keepers, Magisters, Shadows, Traitors, Turncoats"),
            tr("Proud nobles who command the very essence of darkness and shadow — to the point of "
               "worshipping it, some say."),
            tr("Callousness - Whenever making a Remorse test remove a number of dice equal to the "
               "Bane Severity. The dice pool cannot be reduced below 1. "),
            tr("Distorted Image - In reflections or recordings (live or not) the Lasombra appear "
               "to be distorted, those who know what vampires are know precisely what's going on, "
               "while others might be confused but know something is wrong. This does not however, "
               "hide their identity with any certainty and they are not likely to be caught more "
               "often on surveillance than any other Kindred. In addition to this, modern "
               "communication technology which includes making a phone call requires a Technology "
               "test at Difficulty 2 + Bane Severity as microphones struggle with them as much as "
               "cameras. Avoiding any electronic vampire detection system is also done with a "
               "penalty equal to their Bane Severity"),
            tr("Ruthlessness - The next time the vampire fails an action they receive a two-dice "
               "penalty to all rolls until a future attempt at the same action succeeds. This "
               "penalty applies to future attempts of the same action still."),
            {tr("Oblivion"), tr("Dominate"), tr("Potence")});
        break;
    case 6: //Malkavian
        setClanWindowText(
            tr("Kooks, Seers, Lunatics, Madmen, Cassandras, Children of Malkav, Clan of the Moon, "
               "Malks, Jesters"),
            tr("A clan fractured by madness, each member irrevocably suffering under the yoke of "
               "insanity."),
            tr("Fractured Perspective - When suffering a Bestial Failure or a Compulsion, their "
               "mental derangement comes to the forefront. Suffers a penalty equal to their Bane "
               "Severity to one category of dice pools (Physical, Social or Mental) for the entire "
               "scene. The penalty and nature of the affliction are decided between the player and "
               "Storyteller during character creation."),
            tr("Unnatural Manifestations - Using Discipline powers within close proximity of "
               "mortals scares them and any social interactions other than Intimidation suffer a "
               "dice penalty equal to their Bane Severity. This is not Masquerade-breaking, but "
               "the dislike remains for the duration of one scene. Other vampires subject to this "
               "recognize the Malkavian as a vampire but suffer no penalty."),
            tr("Delusion - Whether it's figments of their imagination or extrasensory perception "
               "of the truths. For one scene, the Malkavian suffers a 2 dice penalty to rolls "
               "involving Dexterity, Manipulation, Composure, and Wits. As well as rolls to resist "
               "terror Frenzy."),
            {tr("Auspex"), tr("Dominate"), tr("Obfuscate")});
        break;
    case 7: //Followers of Set
        setClanWindowText(
            tr("Followers of Set, Judasians, Liberators, Corrupters, Tempters, Serpents, Setites, "
               "The Clan of Faith, the Clan of Lies, Typhonists, Sand-Snakes, Vipers"),
            tr("Religious movement that evangelizes the example of a chthonic god, while seeking "
               "out the world’s secret places and protecting ancient artifacts."),
            tr("Abhors the Light - When a Minister is exposed to direct illumination, be it "
               "naturally caused or artificial, they receive a penalty equal to their Bane "
               "Severity to all dice pools while subject to the light. They also add their Bane "
               "Severity to Aggravated damage taken from sunlight."),
            tr("Cold-Blooded - They can only use Blush of Life if they have recently fed from a "
               "living vessel in the same scene or up to roughly an hour ago, Storytellers "
               "discretion. When they do so, it requires a number of Rouse Checks equal to their "
               "Bane Severity rather than just one."),
            tr("Transgression - The Minister suffers a burning desire to influence those around "
               "them to shatter the chains of their own making. They suffer a two-dice penalty to "
               "all dice pools that do not relate to enticing someone or themselves to break a "
               "Chronicle or personal Conviction. The Compulsion ends once the Minister causes "
               "someone, or themselves, at least one stain."),
            {tr("Obfuscate"), tr("Presence"), tr("Protean")});
        break;
    case 8: //Nosferatu
        setClanWindowText(
            tr("The Clan of the Hidden, Sewer Rats, Lepers (archaic), Priors, Crawlers "
               "(Renaissance), Nossies"),
            tr("Hideously disfigured by the Embrace, so they keep to the sewers shadows and "
               "traffic in the secrets they collect."),
            tr("Repulsiveness - Cursed by their blood, when they are Embraced they are twisted "
               "into revolting monsters. They can never raise their rating in the Looks merits and "
               "instead must take the (••) Repulsive flaw. Any attempt to disguise themselves "
               "incurs a penalty equal to the character's Bane Severity, this also includes the "
               "use of Disciplines such as Mask of a Thousand Faces. However, most Nosferatu do "
               "not breach the Masquerade by being seen, they are instead perceived as gross or "
               "terrifying."),
            tr("Infestation - The Haven of a Nosferatu is always infested with vermin, any attempt "
               "to do something that requires concentration takes a two plus Bane Severity "
               "penalty, as well as the same penalty to social tests at ST discretion. "
               "Additionally, when a Nosferatu spends a scene at an enclosed location, the vermin "
               "appears and causes the same penalty though reduced to equal only the Bane "
               "Severity. Any attempt to control these vermin with Animalism is done at a penalty "
               "equal to Bane Severity"),
            tr("Cryptophilia - Consumed by a hunger for private secrets, the Nosferatu seeks to "
               "obtain knowledge no matter big or small as long as it's not a well-known bit of "
               "information. During this, they also refuse to give up their secrets except in "
               "strict trade for something greater than their own. Any action not actively working "
               "towards gaining them a secret they take a two-dice penalty. This Compulsion does "
               "not end till they learn a secret they deem to be useful, sharing this secret is "
               "entirely optional."),
            {tr("Obfuscate"), tr("Animalism"), tr("Potence")});
        break;
    case 9: //Caitiff
        setClanWindowText(
            tr("The Clanless, The Wretched, Freestylers,  Orphans, Trash, Unbound (endonym)"),
            tr("Also known as the clanless, are rare Cainites that do not officially belong to any "
               "clan. These vampires have no inherent clan weakness, but no inherent disciplines "
               "as well. None of the typical clan markers apply to them."),
            tr("Outcast - Untouched by their ancestors, the Caitiff do not share a common Bane. "
               "The character begins with the Flaw Suspect (•) and they may not purchase positive "
               "status during Character Creation. The Storyteller may impose a 1-2 dice penalty to "
               "social tests against Kindred who know they are Caitiff. To improve a Discipline, "
               "the cost is 6 times the level of experience points."),
            tr(""),
            tr("Caitiffs do not suffer from any clan compulsion."),
            {tr("All and none")});
        break;
    case 10: //Ravnos
        setClanWindowText(
            tr("Rogues, Ravens, Daredevils, The Haunted, Gypsies, Criminals, Deceivers, "
               "Charlatans, Shapers, Seekers, Unwelcome, Hundred-Mask Clowns (by the Kuei-jin)"),
            tr("Nomads and tricksters who can force the mind to see what isn’t there, though they "
               "are slaves to the vices they indulge in."),
            tr("Doomed - Anytime they daysleep within the same place more than once in seven "
               "nights, roll a number of dice equal to their Bane Severity. If they receive any "
               "10's they then take 1 Aggravated damage for each as they are scorched from within. "
               "What constitutes as the same place is defined by the chronicle, but generally will "
               "need a mile distance between the two resting places before the bane is triggered. "
               "Mobile havens do work as long as the haven is moved a mile away. Due to this, the "
               "Ravnos may not take the No Haven Flaw."),
            tr("Unbirth Name - If a Ravnos’ unbirth name is used against them, the name-wielding "
               "opponent receives a bonus equal to the Ravnos’ Bane Severity to resist their "
               "Discipline powers. Additionally, the Ravnos affected receives the same penalty to "
               "resist supernatural powers used by the opponent."),
            tr("Tempting Fate - When faced with their next problem, the Daredevil must attempt the "
               "solution with the most dangerous or daring of actions, anything less incurs a "
               "two-dice penalty. Context appropriate flashy or risky attempts may even net bonus "
               "dice. They are free to convince others to follow them in their actions but may as "
               "well go it alone. This Compulsion persists until the problem is solved or further "
               "attempts become impossible to accomplish."),
            {tr("Obfuscate"), tr("Presence"), tr("Animalism")});
        break;
    case 11: //Salubri
        setClanWindowText(
            tr("Unicorns, Soulsuckers, Cyclops, Soul-Thieves, Daijals, Saulot's progeny, the "
               "Hidden Ones, Peacemakers"),
            tr("In the Final Nights, the once mighty Salubri Clan is considered barely a bloodline "
               "after the diablerie of their progenitor, Saulot. Their general few numbers grant "
               "credibility to the rumors that they are only composed of seven vampires at any "
               "time, and that these modern Salubri are fully committed to the search for Golconda "
               "– enacting a bloody ritual when they achieve that state or despair of ever doing "
               "so. "),
            tr("Hunted - Their vitae has a unique trait where when another clan partakes in their "
               "Blood they find it difficult to pull away. Once a non-Salubri has consumed at "
               "least one Hunger level worth, they must make a Hunger Frenzy test at difficulty 2 "
               "+ the Salubri's Bane Severity (3 + the Salubri's Bane Severity for Banu Haqim). If "
               "they fail, they will continue to consume the Salubri until pried off. "
               "Additionally, each Salubri has a third eye and while it's not always human-like "
               "it's always present and cannot be obscured by supernatural powers. In addition to "
               "this, whenever they activate a Discipline, the eye weeps vitae with its intensity "
               "correlating to the level of the Discipline used. The Blood flowing from the eye "
               "can trigger a Hunger Frenzy test from nearby vampires with Hunger 4 or more"),
            tr("Asceticism - Whenever their Hunger is below three, the Salubri suffer a penalty "
               "equal to their Bane Severity to any Discipline dice pools. The bleeding third eye "
               "still remains."),
            tr("Affective Empathy - Overwhelmed with empathy for a personal problem of someone "
               "else, any action not taken to help the person mitigate the suffering they take a "
               "two-dice penalty. This Compulsion continues until the sufferer's burden is eased, "
               "a more critical problem arises or the scene ends."),
            {tr("Auspex"), tr("Dominate"), tr("Fortitude")});
        break;
    case 12: //Toreador
        setClanWindowText(
            tr("The Clan of the Rose, Artisans (archaic), Aesthetes, Vanitas, Epicureans "
               "(Renaissance), Degenerates, Torries"),
            tr("Cainites that enjoy every sensual pleasure the world has to offer, idolizing "
               "physical beauty and the adoration of their thralls."),
            tr("Aesthetic Fixation - A desire for beauty takes control over the Toreador and when "
               "in lesser surroundings they suffer. When they are within settings they find less "
               "than beautiful, they take a penalty equal to their Bane Severity when using "
               "Disciplines."),
            tr("Agonizing Empathy - Whenever their feeding causes Aggravated damage to a mortal, "
               "the vampire suffers the same damage in return but cannot receive more than their "
               "Bane Severity. This damage is generally Aggravated. The damage itself is reflected "
               "as vivid bruising wherever they bit their victim as internal bleeding takes "
               "place."),
            tr("Obsession - Utterly obsessed with a single thing, the Toreador cannot speak of "
               "anything but that object. Be it a person, a piece of artwork, a blood splatter in "
               "the right lighting, or the sunrise itself, they cannot take their attention from "
               "it. Any other actions receive a two-dice penalty. This Compulsion lasts until they "
               "can no longer perceive the object or the scene ends."),
            {tr("Celerity"), tr("Presence"), tr("Auspex")});
        break;
    case 13: //Tremere
        setClanWindowText(
            tr("The Broken Clan, Warlocks, Wizards, Magi, Usurpers, Grayfaces, Tremores "
               "('Trembling Ones'), the Pyramid"),
            tr("Vampiric sorcerers that wield the supernatural power of their past as a hermetic "
               "house, though they became vampires through treachery and artifice."),
            tr("Deficient Blood - Before the fall of Vienna, they were defined by their rigid "
               "hierarchy of Blood Bonds within the Pyramid. After the fall, their Blood weakened "
               "and rejected all prior connections. Tremere are unable to Blood Bond other "
               "Kindred, though they can still be Bound by other clans. Tremere can still Blood "
               "Bond mortals to do their bidding, but the vitae must drink an additional amount of "
               "times equal to their Bane Severity."),
            tr("Stolen Blood - When performing a Blood Surge they need to make Rouse Checks equal "
               "to their Bane Severity. If these Rouse Checks increase their Hunger to 5 or "
               "higher, they can choose whether to back off their Blood Surge or perform it to "
               "then hit Hunger 5 afterward immediately"),
            tr("Perfectionism - Nothing but the best will satisfy them, anything less than "
               "exceptional still instills a profound sense of failure. When afflicted by this, "
               "the Warlock suffers a two-dice penalty to all dice pools. The penalty is reduced "
               "to one die when actions are being repeated and removed entirely on a second "
               "repeat. This does not end till they managed to score a critical win on a Skill "
               "roll or the scene ends."),
            {tr("Blood Sorcery"), tr("Dominate"), tr("Auspex")});
        break;
    case 14: //Tzimisce
        setClanWindowText(
            tr("Fiends, Dragons, Voivodes, The Old Clan, Stokers"),
            tr("Eldritch Old World lords who have little in common with the mortal world and can "
               "manipulate flesh and bone at a whim."),
            tr("Grounded - Each Tzimisce must select a specific charge, be it physical location, a "
               "group of people, or something even more esoteric. Each night they must sleep "
               "surrounded by their charge, if they do not, they sustain aggravated Willpower "
               "damage equal to their Bane Severity upon waking the following night."),
            tr("Cursed Courtesy - If they wish to enter a place of residence uninvited they must "
               "spend Willpower equal to their Bane Severity, this penalty also applies to their "
               "Discipline pools while they are there. The invitation inside can only be made by "
               "someone who lives there and this does not occur in uninhabited homes or public "
               "places. Tzimisce with this Bane cannot take the uninvited Folkloric Block."),
            tr("Covetousness - When afflicted with this compulsion they become obsessed with "
               "owning something in the scene, be it an object, or property to a living person. "
               "Whatever it is, they must add it to their collection and any action taken not "
               "towards this purpose incurs a two-dice penalty. This penalty continues until "
               "ownership is established or the object of their desire is unobtainable."),
            {tr("Dominate"), tr("Animalism"), tr("Protean")});
        break;
    case 15: //Ventrue
        setClanWindowText(
            tr("The Clan of Kings, Blue Bloods, Patricians, Warlords, Ambitiones, Power Mongers"),
            tr("Observe the noblesse oblige of vampire society, though their entitlement and greed "
               "encourages them to seek ever more at the expense of others."),
            tr("Rarefied Tastes - When the Ventrue drinks the blood of a mortal who does not fall "
               "within their preference, they must spend Willpower equal to their Bane Severity "
               "else they will vomit the blood from their bodies unable to slake their hunger. "
               "Their preferences range within the clan, some looking for descendants of a certain "
               "nationality to soldiers suffering from PTSD. With a Resolve + Awareness test, they "
               "can sense if a mortal they seek to feed from fits within their preference. At "
               "character creation, their preference should be selected."),
            tr("Hierarchy - The Ventrue suffer a penalty equal to their Bane Severity to their "
               "Discipline dice pools when using them against a vampire of a lower generation. "
               "They must also spend Willpower equal to this penalty if they wish to directly "
               "attack other vampires of a lower generation."),
            tr("Arrogance - Fueled by the beast and their natural desire for power, the Ventrue "
               "must force someone to obey a command given. The order cannot be given through "
               "supernatural means such as Dominate. Until they satisfy the requirements, they "
               "receive a two-dice penalty for any actions not directly related to leadership."),
            {tr("Dominate"), tr("Presence"), tr("Fortitude")});
        break;
    }

    pic.load(":/images/" + ui->comboBox->itemText(index) + ".png");
    ui->label->setText(ui->comboBox->itemText(index));
    ui->picture->setPixmap(pic);
}

void ClanWindow::on_checkBox_toggled(bool checked)
{
    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());
}
