// src/core/LunagramClient.h
#pragma once

#include <QObject>
#include <memory>
#include "TdHandler.h"
#include "../features/StealthMode.h"
#include "../features/DownloadManager.h"
#include "../features/ThemeEngine.h"

class LunagramClient : public QObject {
    Q_OBJECT

public:
    explicit LunagramClient(QObject *parent = nullptr);
    ~LunagramClient();

    // Инициализация
    bool initialize();
    
    // Основные функции
    void sendMessage(qint64 chatId, const QString &text);
    void deleteMessage(qint64 chatId, qint64 messageId);
    void editMessage(qint64 chatId, qint64 messageId, const QString &newText);
    
    // Расширенные функции
    void enableStealthMode(bool enabled);
    void scheduleMessage(qint64 chatId, const QString &text, 
                        const QDateTime &time);
    void translateMessage(qint64 chatId, qint64 messageId, 
                         const QString &targetLang);
    
    // Настройки
    void setTheme(const QString &themeName);
    void setFontSize(int size);
    void setInterfaceScale(double scale);

private:
    std::unique_ptr<TdHandler> tdHandler_;
    std::unique_ptr<StealthMode> stealthMode_;
    std::unique_ptr<DownloadManager> downloadManager_;
    std::unique_ptr<ThemeEngine> themeEngine_;
    
    QString apiId_;
    QString apiHash_;
    
    void loadConfig();
    void saveConfig();
};