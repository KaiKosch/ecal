/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2024 Continental Corporation
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

/**
 * @file   eh5_writer.h
 * @brief  Hdf5 based Writer implementation
**/

#pragma once

#include <functional>
#include <set>
#include <string>
#include <memory>

#include <ecal/measurement/base/writer.h>

namespace eCAL
{
  namespace experimental
  {
    namespace measurement
    {
      namespace hdf5
      {
        struct WriterImpl;

        /**
         * @brief Hdf5 based Writer implementation
        **/
        class Writer : public measurement::base::Writer
        {
        public:
          /**
           * @brief Constructor
          **/
          Writer();

          /**
           * @brief Constructor
          **/
          Writer(const std::string& path);

          /**
           * @brief Destructor
          **/
          virtual ~Writer();

          /**
           * @brief Copy operator
          **/
          Writer(const Writer& other) = delete;
          Writer& operator=(const Writer& other) = delete;

          /**
          * @brief Move operator
          **/
          Writer(Writer&&) noexcept;
          Writer& operator=(Writer&&) noexcept;



          /**
           * @brief Open file
           *
           * @param path     Input file path / measurement directory path.
           *
           *                 Default measurement directory structure:
           *                  - root directory e.g.: M:\measurement_directory\measurement01
           *                  - documents directory:                                |_doc
           *                  - hosts directories:                                  |_Host1 (e.g.: CARPC01)
           *                                                                        |_Host2 (e.g.: CARPC02)
           *
           *                 File path as output
           *                  - full path to  measurement directory (recommended with host name) (e.g.: M:\measurement_directory\measurement01\CARPC01),
           *                  - to set the name of the actual hdf5 file use SetFileBaseName method.
           *
           * @return         true if output (AccessType::CREATE) measurement directory structure can be accessed/created, false otherwise.
          **/
          bool Open(const std::string& path) override;

          /**
           * @brief Close file
           *
           * @return         true if succeeds, false if it fails
          **/
          bool Close() override;

          /**
           * @brief Checks if file/measurement is ok
           *
           * @return  true if location is accessible, false otherwise
          **/
          bool IsOk() const override;

          /**
           * @brief Gets maximum allowed size for an individual file
           *
           * @return       maximum size in MB
          **/
          size_t GetMaxSizePerFile() const override;

          /**
           * @brief Sets maximum allowed size for an individual file
           *
           * @param size   maximum size in MB
          **/
          void SetMaxSizePerFile(size_t size) override;

          /**
          * @brief Whether each Channel shall be writte in its own file
          *
          * When enabled, data is clustered by channel and each channel is written
          * to its own file. The filenames will consist of the basename and the
          * channel name.
          *
          * @return true, if one file per channel is enabled
          */
          bool IsOneFilePerChannelEnabled() const override;

          /**
          * @brief Enable / disable the creation of one individual file per channel
          *
          * When enabled, data is clustered by channel and each channel is written
          * to its own file. The filenames will consist of the basename and the
          * channel name.
          *
          * @param enabled   Whether one file shall be created per channel
          */
          void SetOneFilePerChannelEnabled(bool enabled) override;

          /**
           * @brief Set data type information of the given channel
           *
           * @param channel_name  channel name
           * @param info          datatype info of the channel
           *
           * @return              channel type
          **/
          void SetChannelDataTypeInformation(const eCAL::experimental::measurement::base::Channel& channel, const base::DataTypeInformation& info) override;

          /**
           * @brief Set measurement file base name (desired name for the actual hdf5 files that will be created)
           *
           * @param base_name        Name of the hdf5 files that will be created.
          **/
          void SetFileBaseName(const std::string& base_name) override;

          /**
           * @brief Add entry to file
           *
           * @param data           data to be added
           * @param size           size of the data
           * @param snd_timestamp  send time stamp
           * @param rcv_timestamp  receive time stamp
           * @param channel_name   channel name
           * @param id             message id
           * @param clock          message clock
           *
           * @return              true if succeeds, false if it fails
          **/
          bool AddEntryToFile(const base::WriteEntry& entry) override;

        private:
          std::unique_ptr<WriterImpl> impl;
        };
      }  // namespace hdf5
    }  // namespace measurement
  }  // namespace experimental 
}  // namespace eCAL
