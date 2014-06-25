#ifndef Geo_Database_ConnectionPropertiesWidget_hpp
#define Geo_Database_ConnectionPropertiesWidget_hpp

#include <Connections/Connection.hpp>
#include <QWidget>

namespace Geo {
namespace Database {
namespace Gui {
class ConnectionPropertiesWidget: public QWidget
{
public:
  virtual
  ~ConnectionPropertiesWidget()
  {
  }

  virtual void
  setConnection(Connections::Connection::Shared connection) = 0;
};
}
}
}

#endif // eo_Database_ConnectionPropertiesWidget_hpp
