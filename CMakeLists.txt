cmake_minimum_required(VERSION 3.16)

project(EncodedImageHashQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick ShaderTools)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appEncodedImageHashQT
    main.cpp
)

qt_add_qml_module(appEncodedImageHashQT
    URI EncodedImageHashQT
    QML_FILES
        Main.qml
    RESOURCES movingText.vert
    RESOURCES movingText.frag
    SOURCES cimage.h cimage.cpp
)

qt_add_shaders(appEncodedImageHashQT "appEncodedImageHashQT_shaders"
    PREFIX
        "/"
    FILES
        "movingText.frag"
        "movingText.vert"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appEncodedImageHashQT PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEncodedImageHashQT
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appEncodedImageHashQT
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appEncodedImageHashQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
