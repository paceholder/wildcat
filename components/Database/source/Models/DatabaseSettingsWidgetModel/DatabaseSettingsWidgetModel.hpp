#ifndef Geo_Database_DatabaseSettingsWidgetModel_hpp
#define Geo_Database_DatabaseSettingsWidgetModel_hpp

#include <QtCore/QAbstractItemModel>
#include <QtCore/QVariant>
#include <QtCore/QVector>

namespace Geo {
namespace Database {
//

namespace Connections {
class ConnectionManager;
}

namespace Models {
namespace DatabaseSettingsWidgetModel {
//
class Entry;
//
class DatabaseSettingsWidgetModel: public QAbstractItemModel
{
  Q_OBJECT

public:
  DatabaseSettingsWidgetModel();

  virtual
  ~DatabaseSettingsWidgetModel();

public:
  virtual
  QVariant
  data(const QModelIndex& index, int role) const override;

  virtual
  QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  virtual
  QModelIndex
  parent(const QModelIndex& index) const override;

  virtual
  int
  columnCount(const QModelIndex& parent) const override;

  virtual
  int
  rowCount(const QModelIndex& parent) const override;

  QVariant
  headerData(int             section,
             Qt::Orientation orientation,
             int             role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

private:
  Connections::ConnectionManager* _connectionsManager;

  QVector<Entry*> _entries;

  int
  getEntryPosition(Entry* entry) const;
};
}

//
}
}
}

#endif //  Geo_Database_DatabaseSettingsWidgetModel_hpp