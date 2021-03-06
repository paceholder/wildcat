#pragma once

#include "TreeEntry.hpp"

namespace Geo
{
namespace Import
{
namespace TreeWrapper
{

/// Composite pattern. Used to represent LAS file strurcture as a tree
class LasFileEntry : public TreeEntry
{
public:
  LasFileEntry(std::shared_ptr<LasFile> lasFile);

  virtual QVariant
  data(int role, int column) const override;

private:
  void
  createEntries(std::shared_ptr<LasFile> lasFile);
};
}
}
}
