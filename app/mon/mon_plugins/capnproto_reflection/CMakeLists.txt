# ========================= eCAL LICENSE =================================
#
# Copyright (C) 2016 - 2025 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= eCAL LICENSE =================================

project(mon_plugin_capnproto_reflection VERSION 0.1.0)

# Legacy Qt5 (pre 5.15) support as suggested by teh Qt Documentation:
# https://doc.qt.io/qt-6/cmake-qt5-and-qt6-compatibility.html#supporting-older-qt-5-versions
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

find_package(CapnProto REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF) # Reason for being turned off: AutoUIC will prevent VS from detecting changes in .ui files
set(CMAKE_AUTORCC OFF) # Reason for being turned off: AutoRCC will create an entirely new project in VS which clutters the solution appearance. Additionally, we cannot assign a source group to the generated .cpp files which will clutter the project.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(${PROJECT_NAME}_src
  src/capnproto_tree_builder.cpp
  src/plugin_widget.cpp
  src/plugin.cpp
)

set(${PROJECT_NAME}_header
  src/capnproto_tree_builder.h
  src/plugin_widget.h
  src/plugin.h
)

set(${PROJECT_NAME}_ui
  src/plugin_widget.ui
)

# compile qt resource files and ui files
if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_wrap_ui(autogen_ui ${${PROJECT_NAME}_ui})
else()
  qt5_wrap_ui(autogen_ui ${${PROJECT_NAME}_ui})
endif()

ecal_add_mon_plugin(${PROJECT_NAME} 
  SOURCES ${${PROJECT_NAME}_src} ${${PROJECT_NAME}_header} ${${PROJECT_NAME}_ui} ${autogen_ui}
  METADATA src/metadata.json
)

target_link_libraries (${PROJECT_NAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Widgets
  eCAL::capnproto_core
  CapnProto::capnp
  CustomQt
  eCAL::mon_plugin_lib
  MonitorTreeView
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)

target_include_directories(${PROJECT_NAME} PRIVATE src)
ecal_install_mon_plugin(${PROJECT_NAME})

if (TARGET mon)
add_dependencies(mon ${PROJECT_NAME})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/${ECAL_MON_PLUGIN_DIR}
  FOLDER app/mon/plugins)