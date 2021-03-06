#include "ConnectionListModel.hpp"

#include <Database/Connections/IConnection>
#include <Database/Connections/IConnectionManager>

#include <ComponentManager/Creator>

#include "ConnectionEntry.hpp"

using Geo::Models::ConnectionEntry;
using Geo::Models::ConnectionListModel;

ConnectionListModel::
ConnectionListModel()
{
  using CM = Database::IConnectionManager;

  // defined as Singleton in Database.json
  _connectionsManager =
    ComponentManager::create<CM*>("Database.ConnectionManager");

  for (auto connection : _connectionsManager->connections())
    _entries.push_back(std::make_unique<ConnectionEntry>(connection));
}


ConnectionListModel::
~ConnectionListModel()
{}


QVariant
ConnectionListModel::
data(const QModelIndex& index, int role) const
{
  Q_UNUSED(role);

  ConnectionEntry* entry =
    static_cast<ConnectionEntry*>(index.internalPointer());

  return entry->data();
}


QModelIndex
ConnectionListModel::
index(int row, int column, const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  Q_ASSERT_X(row < _entries.size(), "ConnectionListModel", "Incorrect number of connections");
  return QAbstractItemModel::createIndex(row, column, _entries[row].get());
}


QModelIndex
ConnectionListModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}


int
ConnectionListModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return 1;
}


int
ConnectionListModel::
rowCount(QModelIndex const & parent) const
{
  Q_UNUSED(parent);

  return _connectionsManager->size();
}


QVariant
ConnectionListModel::
headerData(int section,
           Qt::Orientation orientation,
           int role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section)
  {
    case ConnectionEntry::Type:
      result = tr("Type");
      break;

    case ConnectionEntry::Database:
      result = tr("Database");
      break;

    default:
      result = QVariant();
      break;
  }

  return result;
}


Qt::ItemFlags
ConnectionListModel::
flags(const QModelIndex& index) const
{
  return QAbstractItemModel::flags(index);
}
