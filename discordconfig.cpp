#include "discordconfig.h"
#include "errorcodes.hpp"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>


DiscordConfig::DiscordConfig() : discordWebhookURL(QString()), emoteIdMap(QHash<QString, QString>()), useSuccessCounter(true), useInline(false), useGraphicRepresentation(false)
{
    filepath = QDir::currentPath() + "/settings.json";
    username = qgetenv("USER");
    if (username.isEmpty())
        username = qgetenv("USERNAME");
}

QString DiscordConfig::getDiscordWebhookURL() const
{
    return discordWebhookURL;
}

QString DiscordConfig::getUsername() const
{
    return username;
}

QHash<QString, QString> DiscordConfig::getEmoteIdMap() const
{
    return emoteIdMap;
}

bool DiscordConfig::getUseInline() const
{
    return useInline;
}

bool DiscordConfig::getUseGraphicRepresentation() const
{
    return useGraphicRepresentation;
}

void DiscordConfig::createSettingsFile(){
    QFile settingsFile(filepath);
    if (!settingsFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    QJsonObject jsonSettings{
                             {"DiscordWebhookURL", ""},
                             {"Username", username},
                             {"GraphicalRepresentation", false},
                             {"UseInline", false},
                             {"UseSuccessCounter", false},
                             {"EmotesIds", QJsonObject{
                                                  {"NormalSuccess", ""},
                                                  {"NormalFailure", ""},
                                                  {"NormalCritical", ""},
                                                  {"RedSuccess", ""},
                                                  {"RedFailure", ""},
                                                  {"RedCritical", ""},
                                                  {"BestialFailure", ""}
                                              }
                             },
                             };
    settingsFile.write(QJsonDocument(jsonSettings).toJson());
    settingsFile.close();
}

int DiscordConfig::loadValuesFromSettingFile()
{

    QFileInfo settingsFileInfo(filepath);

    if(!settingsFileInfo.exists() || !settingsFileInfo.isFile()) {
        createSettingsFile();
        return FILE_DOES_NOT_EXIST;
    }

    QFile settingsFile(filepath);
    if (!settingsFile.open(QIODevice::ReadOnly)) {
        return CANNOT_OPEN_FILE;
    }

    QByteArray saveData = settingsFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if(json.contains("DiscordWebhookURL") && json["DiscordWebhookURL"].isString())
        discordWebhookURL = json["DiscordWebhookURL"].toString();

    if(discordWebhookURL.isEmpty()){
        return WEBHOOK_IS_EMPTY;
    }

    if(json.contains("GraphicalRepresentation") && json["GraphicalRepresentation"].isBool())
        useGraphicRepresentation = json["GraphicalRepresentation"].toBool();

    if(useGraphicRepresentation){
        if(json.contains("EmotesIds") && json["EmotesIds"].isObject()){
            QJsonObject emotes = json["EmotesIds"].toObject();
            for(const QString& key : emotes.keys()){
                emoteIdMap.insert(key, emotes.value(key).toString());
            }
            if(emoteIdMap.size() != 7 && emoteIdMap.values().contains("")){
                return MISSING_VALUES;//Not all values are set
            }
        }
    }
    if(json.contains("UseInline") && json["UseInline"].isBool())
        useInline = json["UseInline"].toBool();

    if(json.contains("UseSuccessCounter") && json["UseSuccessCounter"].isBool())
        useSuccessCounter = json["UseSuccessCounter"].toBool();

    if(json.contains("Username") && json["Username"].isString())
        username = json["Username"].toString();

    return 0;
}

bool DiscordConfig::getUseSuccessCounter() const
{
    return useSuccessCounter;
}
