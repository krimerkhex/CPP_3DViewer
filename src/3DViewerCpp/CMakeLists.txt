cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
if (${QT_VERSION_MAJOR} EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
elseif(${QT_VERSION_MAJOR} EQUAL 5)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS OpenGLWidgets)
endif()

set(PROJECT_SOURCES
  main.cc
  model.cc
  model.h
  controler.cc
  controler.h
  veiw.cc
  veiw.h
  veiw.ui
  gl.h
  gl.cc
  matrix_lite.h
  model_pars_obj_afin.h
  model_pars_obj_afin.cc
  model_save_img.h
  model_save_img.cc
  save_settings_model.h
  save_settings_model.cc
)

add_definitions("-Werror -Wall -Wextra")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(3DViewer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(3DViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

install(TARGETS 3DViewer
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets -lstdc++ )


set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if (${QT_VERSION_MAJOR} EQUAL 6)
    target_link_libraries(3DViewer PRIVATE Qt6::OpenGLWidgets)
elseif(${QT_VERSION_MAJOR} EQUAL 5)
    target_link_libraries(3DViewer PRIVATE OpenGL -lGL -lGLU)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()
