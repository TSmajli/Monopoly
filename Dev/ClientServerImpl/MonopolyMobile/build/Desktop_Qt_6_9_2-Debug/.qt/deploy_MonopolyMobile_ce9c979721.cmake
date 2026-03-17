include("/home/user/Dokumente/GitHub/Monopoly/Dev/ClientServerImpl/MonopolyMobile/build/Desktop_Qt_6_9_2-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MonopolyMobile-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/user/Dokumente/GitHub/Monopoly/Dev/ClientServerImpl/MonopolyMobile/build/Desktop_Qt_6_9_2-Debug/MonopolyMobile"
    GENERATE_QT_CONF
)
