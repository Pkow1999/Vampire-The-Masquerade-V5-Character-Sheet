# Vampire-The-Masquerade-V5-Character-Sheet
Vampire The Masquerade V5 Character Sheet

An interactive character sheet for Vampire The Masquerade Fith Edition, now available in English and (partial) Polish!

Windows version is available [HERE](https://github.com/Pkow1999/Vampire-The-Masquerade-V5-Character-Sheet/releases).

Android version is available [HERE](https://github.com/Pkow1999/vtm_sheet_androidPort).

![obraz](https://github.com/Pkow1999/Vampire-The-Masquerade-V5-Character-Sheet/assets/72875240/8e474c47-6385-4a52-b451-52d07b0914a5)
![obraz](https://github.com/Pkow1999/Vampire-The-Masquerade-V5-Character-Sheet/assets/72875240/14a84108-31d3-4c5d-999c-031132d21521)


## With easy to access clan specific informations!

![obraz](https://github.com/Pkow1999/Vampire-The-Masquerade-V5-Character-Sheet/assets/72875240/1493da9c-4944-4bc0-8bd5-eabd7dc704c3)


## Now you can use discipline cards made by wonderful [Thea Vik](https://www.storytellersvault.com/browse.php?author=Thea%20Vik). Just drop them in the appropriate folders.
![obraz](https://github.com/Pkow1999/Vampire-The-Masquerade-V5-Character-Sheet/assets/72875240/52e4b085-b603-49a9-a836-4434e80900b3)

You can find them in images/disciplines/CATEGORY_OF_DISCIPLINE (e.g. images/disciplines/Animalism)

## Now with Discord Integration via Webhooks!
![483191939_1388335099002878_2471845999946803952_n](https://github.com/user-attachments/assets/24eb4236-c870-4fad-bdf1-36b96c5fa53a)
![484281285_954073670223400_7896717918342017775_n](https://github.com/user-attachments/assets/c1ab376a-3a85-4271-a682-51b1f08819b3)
![484239797_966209985704507_7850873241759562008_n](https://github.com/user-attachments/assets/c817505f-d898-4152-afde-bc80ab451157)

Configurable through settings.json!
```
{
    "DiscordWebhookURL": "", 
    "EmotesIds": {
        "BestialFailure": "",
        "NormalCritical": "",
        "NormalFailure": "",
        "NormalSuccess": "",
        "RedCritical": "",
        "RedFailure": "",
        "RedSuccess": ""
    },
    "GraphicalRepresentation": false,
    "UseInline": false, 
    "UseSuccessCounter": false,
    "Username": ""
}
```
```
DiscordWebhookURL - Discord Webhook URL.
EmotesIds - emotes, custom emotes ids or custom text to represent dice results, ignored if the GraphicalRepresentation is set to false.
GraphicalRepresentation - use custom text/graphics to represent dice results (default: false).
UseInline - send normal and hunger dices results in 1 line or 2 lines (default: false - 1 line).
UseSuccessCounter - send number of success with the dice results (default: false).
Username - your username to be displayed (default: Your PC username)
```
settings.json will automatically generate when you first try to use discord integration in the main folder.
#
Compiled by using Qt 6.02
Clan descriptions taken from [White Wolf Wiki](https://whitewolf.fandom.com/wiki/Main_Page) and [Paradox VTM Wiki](https://vtm.paradoxwikis.com/VTM_Wiki).

Portions of the materials are the copyrights and trademarks of Paradox Interactive AB, and are used with permission. All rights reserved. For more information please visit [worldofdarkness.com](https://www.worldofdarkness.com/)


[<img src="https://github.com/Pkow1999/Vampire-The-Masquerade-V5-Character-Sheet/assets/72875240/94813a9e-620e-410a-913f-d4b91322c3cf" width="200" />](https://www.paradoxinteractive.com/games/world-of-darkness/community/dark-pack-agreement)
