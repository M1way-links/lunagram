// src/core/TdHandler.h
#pragma once

#include <QObject>
#include <td/telegram/Client.h>
#include <td/telegram/td_api.h>
#include <map>
#include <queue>

class TdHandler : public QObject {
    Q_OBJECT

public:
    struct Message {
        qint64 id;
        qint64 chatId;
        QString text;
        QDateTime date;
        bool isOutgoing;
        bool isEdited;
    };

    TdHandler(QObject *parent = nullptr);
    
    bool connectToTelegram(const QString &apiId, const QString &apiHash);
    void disconnect();
    
    // Основные методы
    qint64 sendMessage(qint64 chatId, const QString &text);
    bool deleteMessage(qint64 chatId, qint64 messageId);
    bool editMessage(qint64 chatId, qint64 messageId, const QString &newText);
    
    // Дополнительные функции
    void markAsRead(qint64 chatId);
    void setTypingStatus(qint64 chatId, bool typing);
    void downloadFile(qint32 fileId, const QString &path);
    
    // Получение данных
    QList<qint64> getChatList();
    QList<Message> getChatHistory(qint64 chatId, int limit = 50);
    
signals:
    void newMessageReceived(const Message &msg);
    void messageEdited(qint64 chatId, qint64 messageId, const QString &newText);
    void connectionStateChanged(bool connected);
    void authorizationStateChanged(int state);
    void downloadProgress(qint32 fileId, int percentage);

private slots:
    void processUpdates();

private:
    std::unique_ptr<td::Client> client_;
    std::map<qint64, QString> chatTitles_;
    std::queue<td::td_api::object_ptr<td::td_api::Object>> updatesQueue_;
    
    bool isAuthorized_;
    qint64 currentUserId_;
    
    void handleUpdate(td::td_api::object_ptr<td::td_api::Object> update);
    void handleNewMessage(td::td_api::object_ptr<td::td_api::message> message);
    void sendRequest(td::td_api::object_ptr<td::td_api::Function> request);
    
    QTimer *updateTimer_;
};