#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "WinSock2.h"
#include "Ws2tcpip.h"
typedef int socklen_t;
// typedef char* receiveBufer_t;
#else
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
// typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif

#include <memory>
#include <string>

class SocketAddress {
 public:
  SocketAddress(uint32_t inAddress, uint16_t inPort) {
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = htonl(inAddress);
    GetAsSockAddrIn()->sin_port = htons(inPort);
  }

  SocketAddress(const sockaddr& inSockAddr) {
    memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
  }

  SocketAddress() {
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = INADDR_ANY;
    GetAsSockAddrIn()->sin_port = 0;
  }

  bool operator==(const SocketAddress& inOther) const {
    return (mSockAddr.sa_family == AF_INET &&
            GetAsSockAddrIn()->sin_port ==
                inOther.GetAsSockAddrIn()->sin_port) &&
           (GetIP4Ref() == inOther.GetIP4Ref());
  }

  size_t GetHash() const {
    return (GetIP4Ref()) |
           ((static_cast<uint32_t>(GetAsSockAddrIn()->sin_port)) << 13) |
           mSockAddr.sa_family;
  }

  uint32_t GetSize() const { return sizeof(sockaddr); }

  std::string ToString() const;

 private:
  friend class UDPSocket;
  friend class TCPSocket;

  sockaddr mSockAddr;
#if _WIN32
  uint32_t& GetIP4Ref() {
    return *reinterpret_cast<uint32_t*>(
        &GetAsSockAddrIn()->sin_addr.S_un.S_addr);
  }
  const uint32_t& GetIP4Ref() const {
    return *reinterpret_cast<const uint32_t*>(
        &GetAsSockAddrIn()->sin_addr.S_un.S_addr);
  }
#else
  uint32_t& GetIP4Ref() { return GetAsSockAddrIn()->sin_addr.s_addr; }
  const uint32_t& GetIP4Ref() const {
    return GetAsSockAddrIn()->sin_addr.s_addr;
  }
#endif

  sockaddr_in* GetAsSockAddrIn() {
    return reinterpret_cast<sockaddr_in*>(&mSockAddr);
  }
  const sockaddr_in* GetAsSockAddrIn() const {
    return reinterpret_cast<const sockaddr_in*>(&mSockAddr);
  }
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

namespace std {
template <>
struct hash<SocketAddress> {
  size_t operator()(const SocketAddress& inAddress) const {
    return inAddress.GetHash();
  }
};
}  // namespace std