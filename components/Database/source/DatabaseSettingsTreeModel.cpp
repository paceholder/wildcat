#include "DatabaseSettingsTreeModel.hpp"

#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include "ConnectionsManager.hpp"
#include "DatabaseSettingsTreeConnection.hpp"
#include "DatabaseSettingsTreeEntry.hpp"

#include <algorithm>

using Geo::Database::DatabaseSettingsTreeModel;

DatabaseSettingsTreeModel::
DatabaseSettingsTreeModel() {
  using DependencyManager::ApplicationContext;

  _connectionsManager =
    ApplicationContext::create<ConnectionsManager>("Database.ConnectionsManager");

  for (auto connection : _connectionsManager->connections())
    _entries.push_back(new DatabaseSettingsTreeConnection(connection));

  // last empty entry ( a placeholder for adding new connections )
  _entries.push_back(new DatabaseSettingsTreeConnection());
}

DatabaseSettingsTreeModel::
~DatabaseSettingsTreeModel() {
  for (auto entry : _entries)
    delete entry;
}

QVariant
DatabaseSettingsTreeModel::
data(const QModelIndex& index, int role) const  {
  if (!index.isValid())
    return QVariant();

  DatabaseSettingsTreeEntry* entry =
    static_cast<DatabaseSettingsTreeEntry*>(index.internalPointer());

  return entry->data(role, index.column());
}

QModelIndex
DatabaseSettingsTreeModel::
index(int row, int column, const QModelIndex& parent) const {
  if (!parent.isValid())
    return QAbstractItemModel::createIndex(row, column, _entries[row]);

  DatabaseSettingsTreeEntry* entry =
    static_cast<DatabaseSettingsTreeEntry*>(parent.internalPointer());

  if (entry->entries().size() == 0)
    return QModelIndex();

  return QAbstractItemModel::createIndex(row, column, entry->entries()[row]);
}

QModelIndex
DatabaseSettingsTreeModel::
parent(const QModelIndex& index) const  {
  DatabaseSettingsTreeEntry* entry =
    static_cast<DatabaseSettingsTreeEntry*>(index.internalPointer());

  Q_ASSERT(entry);

  DatabaseSettingsTreeEntry* parentEntry = entry->parent();

  if (parentEntry == nullptr)
    return QModelIndex();

  DatabaseSettingsTreeEntry* parentParentEntry = parentEntry->parent();

  int position = 0;

  if (parentParentEntry == nullptr)
    position = getEntryPosition(parentEntry);
  else
    position =  parentParentEntry->positionOfChildEntry(parentEntry);

  return QAbstractItemModel::createIndex(position, 0, parentEntry);
}

int
DatabaseSettingsTreeModel::
columnCount(const QModelIndex& parent) const  {
  return 2;
}

int
DatabaseSettingsTreeModel::
rowCount(const QModelIndex& parent) const {
  if (!parent.isValid())
    return _connectionsManager->size() + 1;

  DatabaseSettingsTreeEntry* entry =
    static_cast<DatabaseSettingsTreeEntry*>(parent.internalPointer());

  return entry->entries().size();
}

// bool
// DatabaseSettingsTreeModel::
// insertRows(int row, int count, const QModelIndex& parent) {
////beginInsertRows();

////endInsertRows();
// }

QVariant
DatabaseSettingsTreeModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const {
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section) {
  case DatabaseSettingsTreeEntry::Database:
    result = tr("Item");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}

Qt::ItemFlags
DatabaseSettingsTreeModel::
flags(const QModelIndex& index) const {
  if (!index.isValid())
    return 0;

  Qt::ItemFlags flags = QAbstractItemModel::flags(index);

  if (!index.parent().isValid() &&
      index.row() == _entries.size() - 1)
    flags |= Qt::ItemIsEditable;

  return flags;
}

void
DatabaseSettingsTreeModel::
addConnection(DatabaseType databaseType) {
  int size = _connectionsManager->size();
  beginInsertRows(QModelIndex(), size, size);

  _connectionsManager->createConnection();
  // switch(c->currentIndex()) {
  // case DatabaseType::MySql:
  // break;
  // case DatabaseType::SQLite:
  // break;
  // }
  _entries.insert(size, new DatabaseSettingsTreeConnection(_connectionsManager->operator[](size)));

  endInsertRows();
}

void
DatabaseSettingsTreeModel::
onClicked(const QModelIndex& index) {
  if (!index.parent().isValid() &&
      index.column() == 1 &&
      index.row() != _entries.size() - 1) {
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    auto connectionWrapper = _entries.takeAt(index.row());
    delete connectionWrapper;

    _connectionsManager->removeConnection(index.row());
    endRemoveRows();
  }
}

int
DatabaseSettingsTreeModel::
getEntryPosition(DatabaseSettingsTreeEntry* entry) const {
  auto it = std::find(_entries.begin(),
                      _entries.end(), entry);

  return it - _entries.begin();
}