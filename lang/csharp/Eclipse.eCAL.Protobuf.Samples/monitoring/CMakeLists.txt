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

include(CSharpUtilities)
project(Eclipse.eCAL.Protobuf.Monitoring.Samples LANGUAGES CSharp)

find_package(eCAL REQUIRED)

macro(ecal_add_csharp_protobuf_monitoring_sample sample_name)
  ecal_add_sample(${sample_name} ${sample_name}.cs)
  target_link_libraries(${sample_name} PRIVATE
    Eclipse.eCAL.Protobuf
    Eclipse.eCAL.Protobuf.Datatypes
  )
  set_property(TARGET ${sample_name} PROPERTY FOLDER samples/csharp/protobuf/monitoring)
  
  set_target_properties(${sample_name} PROPERTIES
    VS_GLOBAL_ROOTNAMESPACE ${sample_name}
  )

  set_property(TARGET ${sample_name}  PROPERTY
    VS_PACKAGE_REFERENCES "Google.Protobuf_${ECAL_CSHARP_PROTOBUF_VERSION}"
  )
endmacro()

ecal_add_csharp_protobuf_monitoring_sample(logging_rec_csharp)
ecal_add_csharp_protobuf_monitoring_sample(monitoring_rec_csharp)
