cmake_minimum_required(VERSION 3.5)

project(SP23 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)  # Add Sql here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)  # Add Sql here



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SP23
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        registration_window.h registration_window.cpp registration_window.ui
        settings.h settings.cpp settings.ui
        backlog.h backlog.cpp backlog.ui
        taskboard.h taskboard.cpp taskboard.ui
        calendar.h calendar.cpp calendar.ui
        sprints.h sprints.cpp sprints.ui
        confluence.h confluence.cpp confluence.ui
        parentboard.ui parentboard.cpp parentboard.h
        assets/resources.qrc
        projectcreation.h projectcreation.cpp projectcreation.ui
        backlog.cpp backlog.h backlog.ui
    )
else()
    if(ANDROID)
        add_library(SP23 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SP23
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SP23 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)  # Add Sql here


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SP23)
endif()
set_target_properties(SP23 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SP23
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SP23)
endif()
