/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2025 Continental Corporation
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

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/client.h>
#include <ecal/msg/protobuf/server.h>

#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <cmath>

#include "math_service_impl.h"
#include "ping_service_impl.h"

#include "math.pb.h"
#include "ping.pb.h"

enum {
  CMN_REGISTRATION_REFRESH_MS = 1000
};

//
// Typed Math Service Tests
//
TEST(core_cpp_clientserver_proto, TypedBlocking_Math)
{
  eCAL::Initialize("TypedBlocking_Math");

  auto math_service = std::make_shared<MathServiceImpl>();
  eCAL::protobuf::CServiceServer<MathService> math_server(math_service);
  eCAL::protobuf::CServiceClient<MathService> math_client;

  std::this_thread::sleep_for(std::chrono::milliseconds(CMN_REGISTRATION_REFRESH_MS));

  SFloatTuple request;
  request.set_inp1(20.0);
  request.set_inp2(22.0);

  auto result = math_client.CallWithResponse<SFloatTuple, SFloat>("Add", request);
  EXPECT_TRUE(result.first);
  ASSERT_FALSE(result.second.empty());

  double out = result.second[0].response.out();
  EXPECT_DOUBLE_EQ(out, 42.0);

  eCAL::Finalize();
}

TEST(core_cpp_clientserver_proto, TypedCallback_Math)
{
  eCAL::Initialize("TypedCallback_Math");

  auto math_service = std::make_shared<MathServiceImpl>();
  eCAL::protobuf::CServiceServer<MathService> math_server(math_service);
  eCAL::protobuf::CServiceClient<MathService> math_client;

  std::this_thread::sleep_for(std::chrono::milliseconds(CMN_REGISTRATION_REFRESH_MS));

  SFloatTuple request;
  request.set_inp1(50.0);
  request.set_inp2(2.0);

  std::promise<double> prom;
  auto fut = prom.get_future();

  auto callback = [&prom](const eCAL::protobuf::SMsgServiceResponse<SFloat>& resp)
  {
    prom.set_value(resp.response.out());
  };

  bool initiated = math_client.CallWithCallback<SFloatTuple, SFloat>("Divide", request, callback);
  EXPECT_TRUE(initiated);

  double result = fut.get();
  EXPECT_DOUBLE_EQ(result, 25.0);

  eCAL::Finalize();
}

TEST(core_cpp_clientserver_proto, TypedCallbackAsync_Math)
{
  eCAL::Initialize("TypedCallbackAsync_Math");

  auto math_service = std::make_shared<MathServiceImpl>();
  eCAL::protobuf::CServiceServer<MathService> math_server(math_service);
  eCAL::protobuf::CServiceClient<MathService> math_client;

  std::this_thread::sleep_for(std::chrono::milliseconds(CMN_REGISTRATION_REFRESH_MS));

  SFloatTuple request;
  request.set_inp1(50.0);
  request.set_inp2(2.0);

  std::promise<double> prom;
  auto fut = prom.get_future();

  auto callback = [&prom](const eCAL::protobuf::SMsgServiceResponse<SFloat>& resp)
    {
      prom.set_value(resp.response.out());
    };

  auto start = std::chrono::steady_clock::now();

  bool initiated = math_client.CallWithCallbackAsync<SFloatTuple, SFloat>("Divide", request, callback);
  EXPECT_TRUE(initiated);

  auto async_call_end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(async_call_end - start);
  EXPECT_LT(duration.count(), 10);

  double result = fut.get();
  EXPECT_DOUBLE_EQ(result, 25.0);

  eCAL::Finalize();
}

//
// Typed Ping Service Tests
//
TEST(core_cpp_clientserver_proto, TypedBlocking_Ping)
{
  eCAL::Initialize("TypedBlocking_Ping");

  auto ping_service = std::make_shared<PingServiceImpl>();
  eCAL::protobuf::CServiceServer<PingService> ping_server(ping_service);
  eCAL::protobuf::CServiceClient<PingService> ping_client;

  std::this_thread::sleep_for(std::chrono::milliseconds(CMN_REGISTRATION_REFRESH_MS));

  PingRequest request;
  request.set_message("PING");

  auto result = ping_client.CallWithResponse<PingRequest, PingResponse>("Ping", request);
  EXPECT_TRUE(result.first);
  ASSERT_FALSE(result.second.empty());

  std::string answer = result.second[0].response.answer();
  EXPECT_EQ(answer, "PONG");

  eCAL::Finalize();
}

TEST(core_cpp_clientserver_proto, TypedCallback_Ping)
{
  eCAL::Initialize("TypedCallback_Ping");

  auto ping_service = std::make_shared<PingServiceImpl>();
  eCAL::protobuf::CServiceServer<PingService> ping_server(ping_service);
  eCAL::protobuf::CServiceClient<PingService> ping_client;

  std::this_thread::sleep_for(std::chrono::milliseconds(CMN_REGISTRATION_REFRESH_MS));

  PingRequest request;
  request.set_message("PING");

  std::promise<std::string> prom;
  auto fut = prom.get_future();

  auto callback = [&prom](const eCAL::protobuf::SMsgServiceResponse<PingResponse>& resp)
  {
    prom.set_value(resp.response.answer());
  };

  bool initiated = ping_client.CallWithCallback<PingRequest, PingResponse>("Ping", request, callback);
  EXPECT_TRUE(initiated);

  std::string answer = fut.get();
  EXPECT_EQ(answer, "PONG");

  eCAL::Finalize();
}
