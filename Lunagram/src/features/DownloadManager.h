// src/features/DownloadManager.h
#pragma once

#include <QObject>
#include <QMap>
#include <QQueue>
#include <QThreadPool>

class DownloadManager : public QObject {
    Q_OBJECT

public:
    enum Priority {
        PriorityLow = 0,
        PriorityNormal = 1,
        PriorityHigh = 2,
        PriorityImmediate = 3
    };

    struct DownloadTask {
        qint32 fileId;
        QString fileName;
        QString savePath;
        qint64 totalSize;
        qint64 downloaded;
        Priority priority;
        QDateTime addedTime;
        bool isPaused;
        int speedLimit; // KB/s, 0 = без ограничений
    };

    explicit DownloadManager(QObject *parent = nullptr);
    
    // Управление загрузками
    int addDownload(qint32 fileId, const QString &fileName, 
                   const QString &savePath, Priority priority = PriorityNormal);
    bool pauseDownload(int taskId);
    bool resumeDownload(int taskId);
    bool cancelDownload(int taskId);
    
    // Настройки
    void setMaxSimultaneousDownloads(int count);
    void setDefaultDownloadPath(const QString &path);
    void setSpeedLimit(int kbPerSecond);
    
    // Приоритеты
    void setTaskPriority(int taskId, Priority priority);
    void reorderQueue(const QList<int> &newOrder);
    
    // Автоматизация
    void setAutoDownload(bool enabled);
    void setAutoDownloadTypes(const QStringList &extensions);
    
    // Статистика
    qint64 getTotalDownloaded() const;
    int getActiveDownloadsCount() const;
    QList<DownloadTask> getQueue() const;

signals:
    void downloadProgress(int taskId, int percentage, qint64 speed);
    void downloadCompleted(int taskId, const QString &path);
    void downloadFailed(int taskId, const QString &error);
    void downloadPaused(int taskId);
    void downloadResumed(int taskId);

private:
    QMap<int, DownloadTask> tasks_;
    QQueue<int> queue_;
    QMap<int, QThread*> activeDownloads_;
    
    int maxSimultaneous_;
    QString defaultPath_;
    bool autoDownload_;
    QStringList autoDownloadTypes_;
    int speedLimit_;
    
    int nextTaskId_;
    
    void processQueue();
    void startDownload(int taskId);
    
    class DownloadWorker : public QObject {
        Q_OBJECT
    public:
        DownloadWorker(int taskId, DownloadTask task);
        
    public slots:
        void download();
        
    signals:
        void progress(int taskId, int percentage, qint64 speed);
        void completed(int taskId, const QString &path);
        void error(int taskId, const QString &error);
    };
};