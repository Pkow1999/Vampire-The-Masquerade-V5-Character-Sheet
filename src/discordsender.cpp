#include "discordsender.h"

#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

DiscordConfig *DiscordSender::getDiscordConfig() const
{
    return discordConfig;
}

void DiscordSender::setDiscordConfig(DiscordConfig *newDiscordConfig)
{
    discordConfig = newDiscordConfig;
}

DiscordSender::DiscordSender(QObject *parent, DiscordConfig *config, StatsManager *counter)
    : QNetworkAccessManager(parent)
    , discordConfig(config)
    , statsCounter(counter)
{}

QNetworkReply *DiscordSender::sendData(const QString &poolFormatted,
                                       const QString &normalDicesFormatted,
                                       const QString &hungerDicesFormatted)
{
    QUrl url = QUrl(discordConfig->getDiscordWebhookURL());
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray postData;
    QString inlineString = "true";
    if (!discordConfig->getUseInline())
        inlineString = "false";
    QString successStatus;

    switch (statsCounter->getCurrentRollStatus()) {
    case RollStatus::NO_CRIT:
        break;
    case RollStatus::NORMAL_CRIT:
        successStatus = tr("Critical Success!");
        break;
    case RollStatus::RED_CRIT:
        successStatus = tr("Messy Critical!");
        break;
    case RollStatus::BESTIAL_FAILURE:
        successStatus = tr("Possible Bestial Failure");
        break;
    }
    postData.append(
        QString("{\"embeds\": [{"
                "\"title\":"
                + tr("\"%1 rolls:\",").arg(discordConfig->getUsername())
                + "\"description\": \"%1\","
                  "\"fields\": ["
                  "{"
                  "\"name\":"
                + tr("\"Normal Dices\",")
                + "\"value\": \"%2\","
                  "\"inline\": %4"
                  "},"
                  "{"
                  "\"name\":"
                + tr("\"Hunger Dices\",")
                + "\"value\": \"%3\","
                  "\"inline\": %4"
                  "}"
                + (discordConfig->getUseSuccessCounter()
                       ? ",{"
                         "\"name\":"
                             + tr("\"%1 Successes\",")
                                   .arg(QString::number(statsCounter->getLastSuccesesCount()))
                             + "\"value\": \"%5\""
                               "}"
                       : "")
                + "]"
                  "}]"
                  "}")
            .arg(poolFormatted,
                 normalDicesFormatted,
                 hungerDicesFormatted,
                 inlineString,
                 successStatus)
            .toUtf8());
    return this->post(request, postData);
}

void DiscordSender::formatDataForDiscord()
{
    QString poolToSend = statsCounter->getPoolNames()->join("+");
    QString normalDicesToSend;
    QString hungerDicesToSend;
    if (!discordConfig->getUseGraphicRepresentation()) {
        //data = QString(tr("```%1 rolls: %2\nNormal dices: %3\nHunger dices: %4```")).arg(userName, poolName.join("+"), normalDices.join(" "), hungerDices.join(" "));
        normalDicesToSend = statsCounter->normalDiceString();
        hungerDicesToSend = statsCounter->hungerDiceString();
    } else {
        QStringList normalDiceGraphic;
        QStringList hungerDiceGraphic;
        for (const int &value : *statsCounter->getListOfNormalDices()) {
            if (value == 10)
                normalDiceGraphic.append(discordConfig->getEmoteIdMap().value("NormalCritical"));
            else if (value < 10 && value > 5)
                normalDiceGraphic.append(discordConfig->getEmoteIdMap().value("NormalSuccess"));
            else
                normalDiceGraphic.append(discordConfig->getEmoteIdMap().value("NormalFailure"));
        }

        for (const int &value : *statsCounter->getListOfHungerDices()) {
            if (value == 10)
                hungerDiceGraphic.append(discordConfig->getEmoteIdMap().value("RedCritical"));
            else if (value < 10 && value > 5)
                hungerDiceGraphic.append(discordConfig->getEmoteIdMap().value("RedSuccess"));
            else if (value == 1)
                hungerDiceGraphic.append(discordConfig->getEmoteIdMap().value("BestialFailure"));
            else
                hungerDiceGraphic.append(discordConfig->getEmoteIdMap().value("RedFailure"));
        }
        normalDicesToSend = normalDiceGraphic.join("   ");
        hungerDicesToSend = hungerDiceGraphic.join("   ");
        //data = QString(tr("%1 rolls: %2\n%3\n%4").arg(userName, poolName.join("+"), normalDiceGraphic.join(" "), hungerDiceGraphic.join(" ")));
    }
    this->sendData(poolToSend, normalDicesToSend, hungerDicesToSend);
}
