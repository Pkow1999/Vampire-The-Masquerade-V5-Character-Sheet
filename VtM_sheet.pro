QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = ankh.ico

SOURCES += \
    clanwindow.cpp \
    disciplinewindow.cpp \
    main.cpp \
    noteswindow.cpp \
    mainwindow.cpp

HEADERS += \
    clanwindow.h \
    disciplinewindow.h \
    noteswindow.h \
    mainwindow.h

FORMS += \
    clanwindow.ui \
    disciplinewindow.ui \
    noteswindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    VtM_sheet_pl_PL.ts \
    VtM_sheet_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    VtM_sheet_en_US.ts \
    ankh.ico \
    images/Banu Haqim.png \
    images/Brujah.png \
    images/Cienkokrwiści.png \
    images/Gangrel.png \
    images/Hecata.png \
    images/Lasombra.png \
    images/Malkavian.png \
    images/Ministerium.png \
    images/Nosferatu.png \
    images/Parias.png \
    images/Ravnos.png \
    images/Salubri.png \
    images/Torreador.png \
    images/Tremere.png \
    images/Tzimisce.png \
    images/Ventrue.png \
    images/bestial-fail.png \
    images/checkbox_checked.png \
    images/checkbox_checked_hover.png \
    images/checkbox_checked_pressed.png \
    images/checkbox_humanity_checked.png \
    images/checkbox_humanity_checked_hover.png \
    images/checkbox_humanity_checked_pressed.png \
    images/checkbox_indeterminate.png \
    images/checkbox_indeterminate_hover.png \
    images/checkbox_indeterminate_pressed.png \
    images/checkbox_unchecked.png \
    images/checkbox_unchecked_hover.png \
    images/checkbox_unchecked_pressed.png \
    images/disciplines/Animalism/0 - Animalism card back.png \
    images/disciplines/Animalism/1 - Bond Famulus.png \
    images/disciplines/Animalism/1 - Sense the Beast.png \
    images/disciplines/Animalism/2 - Atavism.png \
    images/disciplines/Animalism/2 - Feral Whispers.png \
    images/disciplines/Animalism/3 - Animal Succulence.png \
    images/disciplines/Animalism/3 - Quell the Beast.png \
    images/disciplines/Animalism/3 - Unliving Hive.png \
    images/disciplines/Animalism/4 - Subsume the Spirit.png \
    images/disciplines/Animalism/5 - Animal Dominion.png \
    images/disciplines/Animalism/5 - Drawing out the Beast.png \
    images/disciplines/Auspex/0 - Auspex card back.png \
    images/disciplines/Auspex/1 - Heightened senses.png \
    images/disciplines/Auspex/1 - Sense the unseen.png \
    images/disciplines/Auspex/2 - Obeah.png \
    images/disciplines/Auspex/2 - Premonition.png \
    images/disciplines/Auspex/3 - Scry the soul.png \
    images/disciplines/Auspex/3 - Share the senses.png \
    images/disciplines/Auspex/4 - Spirit's touch.png \
    images/disciplines/Auspex/5 - Clairvoyance.png \
    images/disciplines/Auspex/5 - Possession.png \
    images/disciplines/Auspex/5 - Telepathy.png \
    images/disciplines/Auspex/5 - Unburdening the bestial soul.png \
    images/disciplines/Blood Sorcery Rituals/Blood Sorcery Ritual Card back.png \
    images/disciplines/Blood Sorcery Rituals/Blood Sorcery Ritual Ward card back.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Blood Walk.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Bloody Message.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Clinging of the Insect.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Coax the Garden.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Craft Bloodstone.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Dampen the Fear.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Enrich the Blood.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Herd Ward.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Letter Ward.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Wake with Evening's Freshness.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 1 - Ward Against Ghouls.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Calling the Aura's Remnants.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Communicate with Kindred Sire.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Enhance Dyscrasia.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Eyes of Babel.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Illuminate the Trail of Prey.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Ishtar's Touch.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - The Shroud of Silence.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Truth of Blood.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Ward Against Spirits.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 2 - Warding Circle Against Ghouls.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Bladed Hands.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Bloodless Feast.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Dagon's Call.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Deflection of Wooden Doom.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Essence of Air.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Eyes of the Past.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Fire in the Blood.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Firewalker.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Gentle Mind.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Haunted House.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Illusion of Peaceful Death.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Illusion of Perfection.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - One with the Blade.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Sanguine Watcher.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - The Unseen Change.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Ward Against Lupines.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 3 - Warding Circle Against Spirits.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Defense of the Sacred Haven.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Eyes of the Nighthawk.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Incorporeal Passage.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Protean Curse.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Rending the Sweet Earth.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Ward Against Cainites.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 4 - Warding Circle Against Lupines.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 5 - Creatio Ignis.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 5 - Eden's Bounty.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 5 - Escape to True Sanctuary.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 5 - Heart of Stone.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 5 - Shaft of Belated Dissolution.png \
    images/disciplines/Blood Sorcery Rituals/Ritual 5 - Warding Circle Against Cainites.png \
    images/disciplines/Blood Sorcery/0 - Blood Sorcery card back.png \
    images/disciplines/Blood Sorcery/1 - A Taste for Blood.png \
    images/disciplines/Blood Sorcery/1 - Corrosive Vitae.png \
    images/disciplines/Blood Sorcery/1 - Shape the Sanguine Sacrament.png \
    images/disciplines/Blood Sorcery/2 - Extinguish Vitae.png \
    images/disciplines/Blood Sorcery/3 - Blood of Potency.png \
    images/disciplines/Blood Sorcery/3 - Scorpion's Touch.png \
    images/disciplines/Blood Sorcery/4 - Theft of Vitae.png \
    images/disciplines/Blood Sorcery/5 - Baal's Caress.png \
    images/disciplines/Blood Sorcery/5 - Cauldron of Blood.png \
    images/disciplines/Celerity/0 - Celerity card back.png \
    images/disciplines/Celerity/1 - Cat's Grace.png \
    images/disciplines/Celerity/1 - Rapid Reflexes.png \
    images/disciplines/Celerity/2 - Fleetness.png \
    images/disciplines/Celerity/3 - Blink.png \
    images/disciplines/Celerity/3 - Traversal.png \
    images/disciplines/Celerity/4 - Draught of Elegance.png \
    images/disciplines/Celerity/4 - Unerring Aim.png \
    images/disciplines/Celerity/5 - Lightning Strike.png \
    images/disciplines/Celerity/5 - Split Second.png \
    images/disciplines/Dominate/0 - Dominate card back.png \
    images/disciplines/Dominate/1 - Cloud Memory.png \
    images/disciplines/Dominate/1 - Compel.png \
    images/disciplines/Dominate/2 - Dementation.png \
    images/disciplines/Dominate/2 - Domitor's Favor.png \
    images/disciplines/Dominate/2 - Mesmerize.png \
    images/disciplines/Dominate/2 - Slavish Devotion.png \
    images/disciplines/Dominate/3 - Submerged Directive.png \
    images/disciplines/Dominate/3 - The Forgetful Mind.png \
    images/disciplines/Dominate/4 - Ancestral Dominion.png \
    images/disciplines/Dominate/4 - Rationalize.png \
    images/disciplines/Dominate/5 - Mass Manipulation.png \
    images/disciplines/Dominate/5 - Terminal Decree.png \
    images/disciplines/Fortitude/0 - Fortitude card back.png \
    images/disciplines/Fortitude/1 - Resilience.png \
    images/disciplines/Fortitude/1 - Unswayable Mind.png \
    images/disciplines/Fortitude/2 - Enduring Beasts.png \
    images/disciplines/Fortitude/2 - Obdurate.png \
    images/disciplines/Fortitude/2 - Toughness.png \
    images/disciplines/Fortitude/2 - Valeren.png \
    images/disciplines/Fortitude/3 - Defy Bane.png \
    images/disciplines/Fortitude/3 - Fortify the Inner Facade.png \
    images/disciplines/Fortitude/3 - Seal the Beast's Maw.png \
    images/disciplines/Fortitude/4 - Draught of Endurance.png \
    images/disciplines/Fortitude/4 - Shatter.png \
    images/disciplines/Fortitude/5 - Flesh of Marble.png \
    images/disciplines/Fortitude/5 - Prowess from Pain.png \
    images/disciplines/Obfuscate/0 - Obfuscate card back.png \
    images/disciplines/Obfuscate/1 - Cloak of Shadows.png \
    images/disciplines/Obfuscate/1 - Silence of Death.png \
    images/disciplines/Obfuscate/2 - Chimerstry.png \
    images/disciplines/Obfuscate/2 - Ghost's Passing.png \
    images/disciplines/Obfuscate/2 - Mental Maze.png \
    images/disciplines/Obfuscate/2 - Unseen Passage.png \
    images/disciplines/Obfuscate/3 - Fata Morgana.png \
    images/disciplines/Obfuscate/3 - Ghost in the Machine.png \
    images/disciplines/Obfuscate/3 - Mask of a Thousand Faces.png \
    images/disciplines/Obfuscate/4 - Conceal.png \
    images/disciplines/Obfuscate/4 - Vanish.png \
    images/disciplines/Obfuscate/5 - Cloak the Gathering.png \
    images/disciplines/Obfuscate/5 - Impostor's Guise.png \
    images/disciplines/Oblivion Ceremonies/0 - Oblivion Ceremonies card info.png \
    images/disciplines/Oblivion Ceremonies/1 - Summon Spirit.png \
    images/disciplines/Oblivion Ceremonies/1 - The Gift of False Life.png \
    images/disciplines/Oblivion Ceremonies/1 - Traveler's Call.png \
    images/disciplines/Oblivion Ceremonies/2 - Awaken the Homuncular Servant.png \
    images/disciplines/Oblivion Ceremonies/2 - Compel Spirit.png \
    images/disciplines/Oblivion Ceremonies/3 - Fortezza Sindonica.png \
    images/disciplines/Oblivion Ceremonies/3 - Host Spirit.png \
    images/disciplines/Oblivion Ceremonies/3 - Knit the Veil.png \
    images/disciplines/Oblivion Ceremonies/3 - Name of the Father.png \
    images/disciplines/Oblivion Ceremonies/3 - Shambling Hordes.png \
    images/disciplines/Oblivion Ceremonies/4 - Bind the Spirit.png \
    images/disciplines/Oblivion Ceremonies/4 - Death Rattle.png \
    images/disciplines/Oblivion Ceremonies/4 - Split the Shroud.png \
    images/disciplines/Oblivion Ceremonies/5 - Ex Nihilo.png \
    images/disciplines/Oblivion Ceremonies/5 - Lazarene Blessing.png \
    images/disciplines/Oblivion Ceremonies/5 - Pit of Contemplation.png \
    images/disciplines/Oblivion/0 - Oblivion card back.png \
    images/disciplines/Oblivion/1 - Ashes to Ashes.png \
    images/disciplines/Oblivion/1 - Oblivion's Sight.png \
    images/disciplines/Oblivion/1 - Shadow Cloak.png \
    images/disciplines/Oblivion/1 - The Binding Fetter.png \
    images/disciplines/Oblivion/2 - Arms of Ahriman.png \
    images/disciplines/Oblivion/2 - Fatal Precognition.png \
    images/disciplines/Oblivion/2 - Shadow Cast.png \
    images/disciplines/Oblivion/2 - Where the Shroud Thins.png \
    images/disciplines/Oblivion/3 - Aura of Decay.png \
    images/disciplines/Oblivion/3 - Passion Feast.png \
    images/disciplines/Oblivion/3 - Shadow Perspective.png \
    images/disciplines/Oblivion/3 - Touch of Oblivion.png \
    images/disciplines/Oblivion/4 - Necrotic Plague.png \
    images/disciplines/Oblivion/4 - Stygian Shroud.png \
    images/disciplines/Oblivion/5 - Shadow Step.png \
    images/disciplines/Oblivion/5 - Skuld Fulfilled.png \
    images/disciplines/Oblivion/5 - Tenebrous Avatar.png \
    images/disciplines/Oblivion/5 - Withering Spirit.png \
    images/disciplines/Potence/0 - Potence card back.png \
    images/disciplines/Potence/1 - Lethal Body.png \
    images/disciplines/Potence/1 - Soaring Leap.png \
    images/disciplines/Potence/2 - Prowess.png \
    images/disciplines/Potence/3 - Brutal Feed.png \
    images/disciplines/Potence/3 - Spark of Rage.png \
    images/disciplines/Potence/3 - Uncanny Grip.png \
    images/disciplines/Potence/4 - Draught of Might.png \
    images/disciplines/Potence/5 - Earthshock.png \
    images/disciplines/Potence/5 - Fist of Caine.png \
    images/disciplines/Presence/0 - Presence card back.png \
    images/disciplines/Presence/1 - Awe.png \
    images/disciplines/Presence/1 - Daunt.png \
    images/disciplines/Presence/1 - Eyes of the Serpent.png \
    images/disciplines/Presence/2 - Lingering Kiss.png \
    images/disciplines/Presence/3 - Dread Gaze.png \
    images/disciplines/Presence/3 - Entrancement.png \
    images/disciplines/Presence/3 - True Love's Face.png \
    images/disciplines/Presence/4 - Irresistible Voice.png \
    images/disciplines/Presence/4 - Magnum Opus.png \
    images/disciplines/Presence/4 - Summon.png \
    images/disciplines/Presence/5 - Majesty.png \
    images/disciplines/Presence/5 - Star Magnetism.png \
    images/disciplines/Protean/0 - Protean card back.png \
    images/disciplines/Protean/1 - Eyes of the Beast.png \
    images/disciplines/Protean/1 - Weight of the Feather.png \
    images/disciplines/Protean/2 - Feral Weapons.png \
    images/disciplines/Protean/2 - Vicissitude.png \
    images/disciplines/Protean/3 - Earth Meld.png \
    images/disciplines/Protean/3 - Fleshcrafting.png \
    images/disciplines/Protean/3 - Shapechange.png \
    images/disciplines/Protean/4 - Horrid Form.png \
    images/disciplines/Protean/4 - Metamorphosis.png \
    images/disciplines/Protean/5 - Mist Form.png \
    images/disciplines/Protean/5 - One with the Land.png \
    images/disciplines/Protean/5 - The Heart of Darkness.png \
    images/disciplines/Protean/5 - The Unfettered Heart.png \
    images/disciplines/Thin-blood Alchemy/0 - Counterfeit Discipline.png \
    images/disciplines/Thin-blood Alchemy/0 - Distillation_Athanor Corporis.png \
    images/disciplines/Thin-blood Alchemy/0 - Distillation_Calcinatio.png \
    images/disciplines/Thin-blood Alchemy/0 - Distillation_Fixatio.png \
    images/disciplines/Thin-blood Alchemy/00 - Thin-blood Alchemy Card Back.png \
    images/disciplines/Thin-blood Alchemy/1 - Far Reach.png \
    images/disciplines/Thin-blood Alchemy/1 - Gaoler's Bane.png \
    images/disciplines/Thin-blood Alchemy/1 - Haze.png \
    images/disciplines/Thin-blood Alchemy/2 - Envelop.png \
    images/disciplines/Thin-blood Alchemy/2 - Red's Flamin' Hot Sauce.png \
    images/disciplines/Thin-blood Alchemy/3 - Chemically-Induced Flashback.png \
    images/disciplines/Thin-blood Alchemy/3 - Concoct Ashe.png \
    images/disciplines/Thin-blood Alchemy/3 - Defractionate.png \
    images/disciplines/Thin-blood Alchemy/3 - Profane Hieros Gamos.png \
    images/disciplines/Thin-blood Alchemy/3 - Stay the Falling Sand.png \
    images/disciplines/Thin-blood Alchemy/4 - Airborne Momentum.png \
    images/disciplines/Thin-blood Alchemy/4 - Discipline Channeling.png \
    images/disciplines/Thin-blood Alchemy/4 - Hollow Leg.png \
    images/disciplines/Thin-blood Alchemy/5 - Awaken the Sleeper.png \
    images/normal-crit.png \
    images/normal-fail.png \
    images/normal-success.png \
    images/red-crit.png \
    images/red-fail.png \
    images/red-success.png
