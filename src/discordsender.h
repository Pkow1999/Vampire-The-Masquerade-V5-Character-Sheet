#ifndef DISCORDSENDER_H
#define DISCORDSENDER_H

#include <QNetworkAccessManager>
#include <QString>
#include "statsmanager.h"
#include "discordconfig.h"

class DiscordSender : public QNetworkAccessManager
{
private:
    DiscordConfig *discordConfig;
    StatsManager *statsCounter;

public:
    DiscordSender(QObject *parrent = nullptr,
                  DiscordConfig *config = nullptr,
                  StatsManager *statsCounter = nullptr);
    QNetworkReply *sendData(const QString &poolFormatted,
                            const QString &normalDicesFormatted,
                            const QString &hungerDicesFormatted);
    void formatDataForDiscord();
    DiscordConfig *getDiscordConfig() const;
    void setDiscordConfig(DiscordConfig *newDiscordConfig);
};

#endif // DISCORDSENDER_H
