cmake_minimum_required(VERSION 3.16)
project(Lunagram VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Network Multimedia)
find_package(TdLib REQUIRED)

# Настройка сборки
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Исходные файлы
set(SOURCES
    src/core/LunagramClient.cpp
    src/core/TdHandler.cpp
    src/ui/MainWindow.cpp
    src/ui/ChatWidget.cpp
    src/ui/DialogsList.cpp
    src/features/StealthMode.cpp
    src/features/DownloadManager.cpp
    src/features/ThemeEngine.cpp
    src/features/MessageScheduler.cpp
    src/utils/ConfigManager.cpp
)

set(HEADERS
    src/core/LunagramClient.h
    src/core/TdHandler.h
    src/ui/MainWindow.h
    src/ui/ChatWidget.h
    src/ui/DialogsList.h
    src/features/StealthMode.h
    src/features/DownloadManager.h
    src/features/ThemeEngine.h
    src/features/MessageScheduler.h
    src/utils/ConfigManager.h
)

# Ресурсы
set(RESOURCES
    resources/themes.qrc
    resources/icons.qrc
    resources/styles.qrc
)

# Создание исполняемого файла
add_executable(Lunagram ${SOURCES} ${HEADERS} ${RESOURCES})

# Подключение библиотек
target_link_libraries(Lunagram
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Network
    Qt6::Multimedia
    TdLib::TdLib
)

# Настройки установки
install(TARGETS Lunagram RUNTIME DESTINATION bin)
install(DIRECTORY resources/ DESTINATION share/lunagram)

# Генерация установщика (опционально)
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Lunagram")
set(CPACK_PACKAGE_VENDOR "LunaSoft")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)