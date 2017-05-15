#pragma once

#include <QtCore/QAbstractItemModel>

#include <Database/Connections/Connection>

namespace Geo {
//
namespace Database {
namespace Connections {
class ConnectionManager;
class Connection;
}
}

//
namespace Models {

class ConnectionEntry;

/// TODO: make class abstract, do not link to this library directly

class ConnectionListModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  Q_INVOKABLE
  ConnectionListModel();

  virtual
  ~ConnectionListModel();

public:
  virtual QVariant
  data(const QModelIndex& index, int role) const override;

  virtual QModelIndex
  index(int row, int column, const QModelIndex& parent) const override;

  virtual QModelIndex
  parent(const QModelIndex& index) const override;

  virtual int
  columnCount(const QModelIndex& parent) const override;

  virtual int
  rowCount(const QModelIndex& parent) const override;

  QVariant
  headerData(int section,
             Qt::Orientation orientation,
             int role = Qt::DisplayRole) const override;

  Qt::ItemFlags
  flags(const QModelIndex& index) const override;

signals:

  void connectionChanged(Database::Connections::Connection::Shared);

protected:
  Database::Connections::ConnectionManager* _connectionsManager;

  QVector<ConnectionEntry*> _entries;

  int
  getEntryPosition(ConnectionEntry* entry) const;
};

//
}
}
