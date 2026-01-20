cmake_minimum_required(VERSION 3.19)
project(Client LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)


qt_standard_project_setup()

qt_add_executable(Client
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    networkclient.h networkclient.cpp

)

target_link_libraries(Client
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Widgets
        Qt6::Network
)

include(GNUInstallDirs)

install(TARGETS Client
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Client
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
