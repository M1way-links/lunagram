// src/features/ThemeEngine.h
#pragma once

#include <QObject>
#include <QMap>
#include <QJsonObject>

class ThemeEngine : public QObject {
    Q_OBJECT

public:
    struct Theme {
        QString name;
        QString author;
        QString version;
        QString baseTheme; // "dark" или "light"
        
        // Цвета
        QMap<QString, QString> colors;
        
        // Стили
        QString css;
        
        // Иконки
        QString iconPack;
        
        // Анимации
        bool animationsEnabled;
        int animationSpeed; // 1-10
        
        // Шрифты
        QString fontFamily;
        int fontSize;
        
        // Закругления
        int borderRadius; // px
        int messageRadius; // px
    };

    explicit ThemeEngine(QObject *parent = nullptr);
    
    // Управление темами
    bool loadTheme(const QString &themePath);
    bool saveTheme(const QString &themePath, const Theme &theme);
    void applyTheme(const QString &themeName);
    
    // Создание тем
    void createThemeFromCurrent();
    void editTheme(const QString &themeName, const QJsonObject &changes);
    
    // Настройки
    void setAutoTheme(bool enabled); // Авто-тема по времени
    void setFollowSystemTheme(bool enabled);
    
    // Кастомизация
    void setAccentColor(const QString &color);
    void setBackgroundImage(const QString &imagePath);
    void setOpacity(double opacity);
    
    // Экспорт/импорт
    bool exportTheme(const QString &themeName, const QString &path);
    bool importTheme(const QString &path);
    
    // Готовые темы
    QList<QString> getBuiltinThemes() const;
    QList<QString> getUserThemes() const;

signals:
    void themeChanged(const QString &themeName);
    void accentColorChanged(const QString &color);
    void fontChanged(const QString &fontFamily);

private:
    QMap<QString, Theme> themes_;
    QString currentTheme_;
    
    QSettings settings_;
    
    void loadBuiltinThemes();
    void loadUserThemes();
    
    void applyColors(const QMap<QString, QString> &colors);
    void applyCSS(const QString &css);
    void applyFont(const QString &fontFamily, int size);
};