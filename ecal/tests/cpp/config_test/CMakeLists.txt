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

project(test_config)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(tclap REQUIRED)

if(ECAL_CORE_CONFIGURATION)
  find_package(yaml-cpp REQUIRED)
  include(${ECAL_PROJECT_ROOT}/thirdparty/yaml-cpp/compatibility-yaml-cpp.cmake)
  yaml_cpp_create_compatibility_targets()
endif()

set(config_test_src
  src/config_test.cpp
  src/path_processing_test.cpp
  src/yaml_processing_test.cpp
  ${ECAL_CORE_PROJECT_ROOT}/core/src/config/default_configuration.cpp
  ${ECAL_CORE_PROJECT_ROOT}/core/src/config/ecal_path_processing.cpp
)

if(ECAL_CORE_CONFIGURATION)
  list(APPEND config_test_src
    ${ECAL_CORE_PROJECT_ROOT}/core/src/config/configuration_reader.cpp
    ${ECAL_CORE_PROJECT_ROOT}/core/src/config/configuration_to_yaml.cpp
  )
endif()

ecal_add_gtest(${PROJECT_NAME} ${config_test_src})

target_include_directories(${PROJECT_NAME} PRIVATE 
  $<TARGET_PROPERTY:eCAL::core,INCLUDE_DIRECTORIES>
  ${CMAKE_CURRENT_LIST_DIR}/src
  ${ECAL_CORE_PROJECT_ROOT}/core/src/config
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE 
    $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${QNXNTO}>>>:dl>
    eCAL::core
    eCAL::ecal-utils
    Threads::Threads
    tclap::tclap
    GTest::gmock_main
)

if(ECAL_CORE_CONFIGURATION)
  target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)
  target_compile_definitions(${PROJECT_NAME} PRIVATE ECAL_CORE_CONFIGURATION)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

target_compile_definitions(${PROJECT_NAME} PRIVATE ECAL_CORE_COMMAND_LINE)

ecal_install_gtest(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER tests/cpp/config)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES 
    ${${PROJECT_NAME}_src}
)
