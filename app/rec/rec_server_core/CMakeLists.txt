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

find_package(Threads REQUIRED)
find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)
find_package(fineftp REQUIRED)
find_package(tinyxml2 REQUIRED)

set(PROJECT_NAME rec_server_core)

set(source_files
    include/rec_server_core/ecalstate_helpers.h
    include/rec_server_core/proto_helpers.h
    include/rec_server_core/rec_server.h
    include/rec_server_core/rec_server_config.h
    include/rec_server_core/rec_server_types.h
	include/rec_server_core/status.h

    src/ecalstate_helpers.cpp
    src/monitoring_thread.cpp
    src/monitoring_thread.h
    src/proto_helpers.cpp
    src/rec_server.cpp
    src/rec_server_impl.cpp
    src/rec_server_impl.h
    src/recorder_command.h
    src/recorder_settings.h

    src/config/config.cpp
    src/config/config.h
    src/config/config_v1.cpp
    src/config/config_v1.h
    src/config/config_v2to4.cpp
    src/config/config_v2to4.h

    src/recorder/abstract_recorder.h
    src/recorder/local_recorder.cpp
    src/recorder/local_recorder.h
    src/recorder/remote_recorder.cpp
    src/recorder/remote_recorder.h
) 

add_library (${PROJECT_NAME} ${source_files})
add_library (eCAL::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_include_directories(${PROJECT_NAME} PUBLIC  include)

create_targets_protobuf()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    tinyxml2::tinyxml2
    protobuf::libprotobuf
    eCAL::protobuf_core
    eCAL::app_pb
    ThreadingUtils
    Threads::Threads
    eCAL::ecal-utils
    EcalParser
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    eCAL::rec_client_core
    fineftp::server
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

source_group(TREE "${CMAKE_CURRENT_LIST_DIR}"
    FILES
        ${source_files}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER app/rec)
