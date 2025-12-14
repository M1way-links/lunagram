// src/features/StealthMode.h
#pragma once

#include <QObject>
#include <QSettings>

class StealthMode : public QObject {
    Q_OBJECT

public:
    struct StealthSettings {
        bool hideOnlineStatus = false;
        bool hideReadReceipts = false;
        bool hideTypingIndicator = false;
        bool hideLastSeen = false;
        bool hideVoiceRecording = false;
        bool hideGroupMembers = false;
        
        // Продвинутые настройки
        bool fakeOnlineStatus = false;
        QDateTime fakeLastSeenTime;
        bool sendReadReceiptsAfter = false;
        int readAfterSeconds = 10;
        
        // Исключения
        QStringList alwaysShowOnlineFor;
        QStringList alwaysSendReadReceiptsTo;
    };

    explicit StealthMode(QObject *parent = nullptr);
    
    // Включение/выключение
    void enable(bool enabled);
    bool isEnabled() const;
    
    // Настройки
    void setSettings(const StealthSettings &settings);
    StealthSettings getSettings() const;
    
    // Индивидуальные настройки для чатов
    void setChatException(qint64 chatId, const StealthSettings &settings);
    void removeChatException(qint64 chatId);
    
    // Временные действия
    void appearOnlineFor(int minutes);
    void disableTemporarily(int minutes);
    
    // Автоматические ответы в стелс-режиме
    void setAutoReply(const QString &message);
    QString getAutoReply() const;
    
    // Анти-отслеживание
    void preventScreenshot(bool enabled);
    void hideMessagePreview(bool enabled);

private:
    StealthSettings settings_;
    QMap<qint64, StealthSettings> chatExceptions_;
    QSettings appSettings_;
    
    bool isActive_;
    QString autoReplyMessage_;
    
    void saveToConfig();
    void loadFromConfig();
    
    QTimer *temporaryDisableTimer_;
};