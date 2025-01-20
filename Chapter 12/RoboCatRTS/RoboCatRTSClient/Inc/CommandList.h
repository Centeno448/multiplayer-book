#pragma once

#include <deque>

#include "Command.h"
#include "MemoryBitStream.h"

class CommandList {
 public:
  CommandList() {}

  void AddCommand(CommandPtr inCommand);

  void Clear() { mCommands.clear(); }
  int GetCount() const { return static_cast<int>(mCommands.size()); }

  void ProcessCommands(uint64_t inExpectedPlayerId);

  void Write(OutputMemoryBitStream& inOutputStream);
  void Read(InputMemoryBitStream& inInputStream);

 private:
  std::deque<CommandPtr> mCommands;
};
