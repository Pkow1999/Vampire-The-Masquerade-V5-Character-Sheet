#ifndef DISCORDCONFIG_H
#define DISCORDCONFIG_H

#include <QHash>
#include <QString>

class DiscordConfig
{
private:
    QString discordWebhookURL;
    QString username;
    QString filepath;
    QHash<QString, QString> emoteIdMap;
    bool useSuccessCounter;
    bool useInline;
    bool useGraphicRepresentation;
    void createSettingsFile();
    QString getUserName();

public:
    DiscordConfig();

    bool getUseSuccessCounter() const;
    QString getDiscordWebhookURL() const;
    QString getUsername() const;
    QHash<QString, QString> getEmoteIdMap() const;
    bool getUseInline() const;
    bool getUseGraphicRepresentation() const;

    int loadValuesFromSettingFile();
};
#endif // DISCORDCONFIG_H
