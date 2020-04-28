#pragma once

#ifndef __BROADCAST_SENDER_H__
#define __BROADCAST_SENDER_H__

#include "IpProtocol.h"

#include <Winsock2.h>
#include <string>
#include <stdint.h>
#include <memory>
#include <Ws2tcpip.h>

class BroadcastSender
{
public:
   BroadcastSender();
   ~BroadcastSender();
   void reset(void);
   bool init(IpProtocol ipProtocol);
   bool setBroadcastSettings(const char* address, const uint16_t port);
   bool sendTo(const std::string& sendBuff, int& bytesSend);
   void close(void);

private:
   void fillAddrInfoCriteria(addrinfo* hints) const;
   bool fillNetworkAddressStructure(const char* address, sockaddr_in* socketAddr);
   void fillPort(uint16_t port, sockaddr_in* socketAddr);
   void fillIpProtocolFamily(sockaddr_in* socketAddr);

private:
   SOCKET socketId;
   sockaddr_in sendAddr;
   IpProtocol ipProtocol;
};

#endif // __BROADCAST_SENDER_H__