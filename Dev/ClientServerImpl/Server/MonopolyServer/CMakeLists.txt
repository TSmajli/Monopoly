cmake_minimum_required(VERSION 3.19)
project(MonopolyServer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Network)


qt_standard_project_setup()

qt_add_executable(MonopolyServer
    main.cpp
    gameserver.h gameserver.cpp
    player.h player.cpp
    field.h
    propertyfield.h propertyfield.cpp
    streetfield.h streetfield.cpp
    railroadfield.h railroadfield.cpp
    utilityfield.h utilityfield.cpp
    taxfield.h taxfield.cpp
    startfield.h startfield.cpp
    board.h board.cpp
    game.h game.cpp
    jailfield.h jailfield.cpp


)

target_link_libraries(MonopolyServer
    PRIVATE
        Qt::Core
        Qt::Network
)

include(GNUInstallDirs)

install(TARGETS MonopolyServer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
