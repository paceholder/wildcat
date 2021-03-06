#pragma once

#include <Domain/WellTrait>

#include "Connections/IConnection.hpp"
#include "TraitEntry.hpp"

namespace Geo
{
namespace Database
{
namespace Gui
{

class WellTraitEntry : public TraitEntry
{
public:
  enum Column { Trait,
                Synonyms,
                Type,
                CloseAction,
                Size };

  enum State { Active,
               Deleted };

public:
  WellTraitEntry(Geo::Domain::WellTrait::Shared trait);

  // WellTraitEntry();

  QVariant
  data(int role, int column) override;

  Geo::Domain::WellTrait::Shared
  trait() const;

  State
  getState() const { return _state; }

  bool
  getPersisted() const { return _persisted; }

  void
  setPersisted(bool const persisted) { _persisted = persisted; }

public slots:
  void
  switchState();

private:
  Geo::Domain::WellTrait::Shared _trait;

  State _state;

  // if object in DB already?
  bool _persisted;

private:
  QVariant
  getDisplayOrEditRole(int column) const;

  QVariant
  getDecorationRole(int column) const;

  QVariant
  getForegroundRole(int column) const;
};

//
}
}
}
