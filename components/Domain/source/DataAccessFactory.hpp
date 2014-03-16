#ifndef Geo_Domain_DataAccessFactory_hpp
#define Geo_Domain_DataAccessFactory_hpp

#include <Domain/LogAccess>
#include <Domain/WellAccess>

#include <QSharedPointer>

namespace Geo {
namespace Domain {
/**
 * Class produces various objects for accesing ORM elements
 */
class DataAccessFactory {
public:
  typedef QSharedPointer<DataAccessFactory> Shared;

public:
  virtual
  ~DataAccessFactory() {}

  DataAccessFactory&
  operator=(DataAccessFactory const&) = delete;

  virtual LogAccess::Shared
  logAccess() const = 0;

  virtual WellAccess::Shared
  wellAccess() const = 0;
};
}
}

#endif
