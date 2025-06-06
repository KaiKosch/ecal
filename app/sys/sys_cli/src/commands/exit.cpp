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

#include "exit.h"
#include "helpers.h"

#include <ecal_utils/string.h>

namespace eCAL
{
  namespace sys
  {
    namespace command
    {

      std::string Exit::Usage() const
      {
        return "";
      }

      std::string Exit::Help() const
      {
        return "Quit eCAL Sys.";
      }

      std::string Exit::Example() const
      {
        return "";
      }

      eCAL::sys::Error Exit::Execute(const std::shared_ptr<EcalSys>& /*ecalsys_instance*/, const std::vector<std::string>& argv) const
      {
        if (!argv.empty())
          return Error(Error::ErrorCode::TOO_MANY_PARAMETERS, EcalUtils::String::Join(" ", std::vector<std::string>(std::next(argv.begin()), argv.end())));

        exit(EXIT_SUCCESS);
      }

      eCAL::sys::Error Exit::Execute(const std::string& /*hostname*/, const std::shared_ptr<eCAL::protobuf::CServiceClientUntyped<eCAL::pb::sys::Service>>& /*remote_ecalsys_service*/, const std::vector<std::string>& argv) const
      {
        if (!argv.empty())
          return Error(Error::ErrorCode::TOO_MANY_PARAMETERS, EcalUtils::String::Join(" ", std::vector<std::string>(std::next(argv.begin()), argv.end())));

        exit(EXIT_SUCCESS);
      }
    }
  }
}