cmake_minimum_required(VERSION 3.19)
project(Client LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core )
find_package(Qt6 REQUIRED COMPONENTS Network )
qt_standard_project_setup()

qt_add_executable(Client
    main.cpp
)

target_link_libraries(Client
    PRIVATE
        Qt::Core
        Qt6::Network
)

include(GNUInstallDirs)

install(TARGETS Client
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
