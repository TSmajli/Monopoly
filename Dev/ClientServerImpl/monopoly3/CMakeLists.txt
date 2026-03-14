cmake_minimum_required(VERSION 3.19)
project(monopoly3 LANGUAGES CXX)

if(NOT DEFINED Qt6_DIR AND EXISTS "C:/Qt/6.10.2/mingw_64/lib/cmake/Qt6")
    set(Qt6_DIR "C:/Qt/6.10.2/mingw_64/lib/cmake/Qt6")
endif()

if(EXISTS "C:/Qt/6.10.2/mingw_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(monopoly3
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    networkclient.cpp
    networkclient.h
    mainwindow.ui
    images.qrc
)

qt_add_resources(app_resources
    images.qrc
)

target_sources(monopoly3 PRIVATE
    ${app_resources}
)

target_link_libraries(monopoly3
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS monopoly3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET monopoly3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})