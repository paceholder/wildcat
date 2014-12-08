#ifndef Geo_Database_Traits_WellTrait_hpp
#define Geo_Database_Traits_WellTrait_hpp

#include <Database/Connections/Connection>
#include <Domain/WellTrait>

#include <Models/Traits/Entry.hpp>

namespace Geo {
namespace Database {
namespace Models {
namespace Traits {
//

class WellTraitEntry: public Entry
{
public:
  enum Column { Trait       = 0,
                Synonyms    = 1,
                Type        = 2,
                CloseAction = 3,
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

public slots:
  void
  switchState();

private:
  Geo::Domain::WellTrait::Shared _trait;

  State _state;

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
}

#endif //  Geo_Database_Traits_WellTrait_hpp
