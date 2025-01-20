#pragma once

#include <unordered_map>

#include "ReplicationManagerTransmissionData.h"
#include "RoboCatShared.h"

class ReplicationManagerServer {
 public:
  void ReplicateCreate(int inNetworkId, uint32_t inInitialDirtyState);
  void ReplicateDestroy(int inNetworkId);
  void SetStateDirty(int inNetworkId, uint32_t inDirtyState);
  void HandleCreateAckd(int inNetworkId);
  void RemoveFromReplication(int inNetworkId);

  void Write(OutputMemoryBitStream& inOutputStream,
             ReplicationManagerTransmissionData* ioTransmissinData);

 private:
  uint32_t WriteCreateAction(OutputMemoryBitStream& inOutputStream,
                             int inNetworkId, uint32_t inDirtyState);
  uint32_t WriteUpdateAction(OutputMemoryBitStream& inOutputStream,
                             int inNetworkId, uint32_t inDirtyState);
  uint32_t WriteDestroyAction(OutputMemoryBitStream& inOutputStream,
                              int inNetworkId, uint32_t inDirtyState);

  std::unordered_map<int, ReplicationCommand> mNetworkIdToReplicationCommand;
};
