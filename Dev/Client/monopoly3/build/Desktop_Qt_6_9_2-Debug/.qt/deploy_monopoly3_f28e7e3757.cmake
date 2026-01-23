include("/home/user/Projekte_Qt/monopoly3/build/Desktop_Qt_6_9_2-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/monopoly3-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/user/Projekte_Qt/monopoly3/build/Desktop_Qt_6_9_2-Debug/monopoly3"
    GENERATE_QT_CONF
)
