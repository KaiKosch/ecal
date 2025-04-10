/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
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

using System;
using System.Text;
using Eclipse.eCAL.Core;

public class MinimalServiceServer
{
  static byte[] OnMethodCallback(ServiceMethodInformation methodInfo, byte[] request)
  {
    Console.WriteLine("Method called: " + methodInfo.MethodName);
    Console.WriteLine("Request: " + Encoding.UTF8.GetString(request));

    // Echo the request data back as the response.
    return request;
  }

  static void Main()
  {
    // Initialize eCAL API.
    Core.Initialize("minimal server csharp");

    // Print version info.
    Console.WriteLine(string.Format("eCAL {0} ({1})\n", Core.GetVersion(), Core.GetDate()));

    // Create a service server named "service1".
    ServiceServer serviceServer = new ServiceServer("service1");

    // Register the method callback.
    ServiceMethodInformation methodInfo = new ServiceMethodInformation();
    methodInfo.MethodName = "echo";
    serviceServer.SetMethodCallback(methodInfo, OnMethodCallback);

    // Idle main thread until eCAL is no longer OK.
    while (Core.Ok())
    {
      System.Threading.Thread.Sleep(100);
    }

    // Dispose service server.
    serviceServer.Dispose();

    // Finalize eCAL API.
    Core.Terminate();
  }
}
