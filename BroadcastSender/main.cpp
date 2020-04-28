#include "BroadcastSender.h"
#include "WinsockManager.h"

#include <iostream>
#include <memory>

#define DLL_WINSOCK_VERSION MAKEWORD(2, 2)

int main()
{
   std::unique_ptr<WinsockManager> winsockManager = std::make_unique<WinsockManager>();
   std::unique_ptr<BroadcastSender> broadcastSender = nullptr;
   std::string ipAddress;
   uint16_t port;
   std::string sendBuff;
   int bytesSend = 0;

   if (false == winsockManager->startup(DLL_WINSOCK_VERSION))
   {
      printf("Winsock initialization error\n");
      return -1;
   }

   std::cout << "Enter broadcast ip address: ";
   std::cin >> ipAddress;

   std::cout << "Enter port: ";
   std::cin >> port;

   broadcastSender = std::make_unique<BroadcastSender>();

   if (true == broadcastSender->init(IpProtocol::IPV4))
   {
      std::cout << "Socket initialized\n";
   }
   else
   {
      std::cout << "Cannot initialiaze a socket\n";
      std::cout << "Error: " << WinsockManager::getErrorMessage() << "\n";
      winsockManager->cleanup();
      return -1;
   }

   if (broadcastSender->setBroadcastSettings(ipAddress.c_str(), port) == false)
   {
      std::cout << "Broadcast settings have not been set\n";
      std::cout << "Error: " << WinsockManager::getErrorMessage() << "\n";
      broadcastSender->close();
      winsockManager->cleanup();
      return -1;
   }

   std::cout << "Enter message: ";
   std::cin >> sendBuff;

   if (broadcastSender->sendTo(sendBuff, bytesSend) <= 0)
   {
      std::cout << "Data have not been sent\n";
      std::cout << "Error: " << WinsockManager::getErrorMessage() << "\n";
   }

   broadcastSender->close();
   std::cout << "Socket closed" << "\n";
   winsockManager->cleanup();
   std::cin.get();
   return 0;
}