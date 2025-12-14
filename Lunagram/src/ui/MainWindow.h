// src/ui/MainWindow.h
#pragma once

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "../core/LunagramClient.h"

QT_BEGIN_NAMESPACE
class QTabWidget;
class QListWidget;
class QTextEdit;
class QSplitter;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNewMessage(const TdHandler::Message &msg);
    void onSendMessage();
    void onChatSelected(qint64 chatId);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    
    // Меню функций
    void openStealthSettings();
    void openDownloadManager();
    void openThemeSettings();
    void openMessageScheduler();
    
    // Контекстное меню сообщения
    void onMessageContextMenu(const QPoint &pos);
    void replyToMessage();
    void forwardMessage();
    void copyMessage();
    void deleteMessage();
    void editMessage();
    void saveAttachment();
    void translateMessage();

private:
    void setupUI();
    void setupMenuBar();
    void setupTrayIcon();
    void setupShortcuts();
    
    void loadChatList();
    void loadChatHistory(qint64 chatId);
    
    // Виджеты
    QSplitter *mainSplitter_;
    QListWidget *chatListWidget_;
    QTabWidget *chatTabs_;
    QTextEdit *messageInput_;
    
    // Система
    LunagramClient *client_;
    QSystemTrayIcon *trayIcon_;
    QMenu *trayMenu_;
    
    // Текущее состояние
    qint64 currentChatId_;
    QMap<qint64, QString> chatNames_;
    
    // Настройки
    bool minimizeToTray_;
    bool startMinimized_;
    
    void saveWindowState();
    void loadWindowState();
};