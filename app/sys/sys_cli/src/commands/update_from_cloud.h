/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2020 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#pragma once

#include "command.h"

namespace eCAL
{
  namespace sys
  {
    namespace command
    {
      class UpdateFromCloud : public Command
      {
      public:
        std::string Usage()    const override;
        std::string Help()     const override;
        std::string Example()  const override;

        eCAL::sys::Error Execute(const std::shared_ptr<EcalSys>& ecalsys_instance, const std::vector<std::string>& argv) const override;
        eCAL::sys::Error Execute(const std::string& hostname, const std::shared_ptr<eCAL::protobuf::CServiceClientUntyped<eCAL::pb::sys::Service>>& remote_ecalsys_service, const std::vector<std::string>& argv) const override;
      };
    }
  }
}