#include "DatabaseSettingsWidgetModel.hpp"

#include <DependencyManager/ApplicationContext>

#include <Uni/Logging/Logging>

#include <Connections/ConnectionManager.hpp>
#include <Models/DatabaseSettingsWidgetModel/ConnectionEntry.hpp>
#include <Models/DatabaseSettingsWidgetModel/Entry.hpp>

#include <algorithm>

using Geo::Database::Models::DatabaseSettingsWidgetModel::ConnectionEntry;
using Geo::Database::Models::DatabaseSettingsWidgetModel::Entry;
using Geo::Database::Models::DatabaseSettingsWidgetModel::DatabaseSettingsWidgetModel;

DatabaseSettingsWidgetModel::
DatabaseSettingsWidgetModel()
{
  using Connections::ConnectionManager;
  using DependencyManager::ApplicationContext;

  _connectionsManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  for (auto connection : _connectionsManager->connections())
    _entries.push_back(new ConnectionEntry(connection));

  // last empty entry ( a placeholder for adding new connections )
  _entries.push_back(new ConnectionEntry());
}

DatabaseSettingsWidgetModel::
~DatabaseSettingsWidgetModel()
{
  for (auto entry : _entries)
    delete entry;
}

QVariant
DatabaseSettingsWidgetModel::
data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  Entry* entry =
    static_cast<Entry*>(index.internalPointer());

  return entry->data(role, index.column());
}

QModelIndex
DatabaseSettingsWidgetModel::
index(int row, int column, const QModelIndex& parent) const
{
  QModelIndex index;

  if (!parent.isValid())
    index =  QAbstractItemModel::createIndex(row, column, _entries[row]);

  return index;
}

QModelIndex
DatabaseSettingsWidgetModel::
parent(const QModelIndex& index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

int
DatabaseSettingsWidgetModel::
columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);

  return 2;
}

int
DatabaseSettingsWidgetModel::
rowCount(const QModelIndex& parent) const
{
  if (!parent.isValid())
    return _connectionsManager->size();

  return 0;
}

QVariant
DatabaseSettingsWidgetModel::
headerData(int             section,
           Qt::Orientation orientation,
           int             role)  const
{
  QVariant result;

  if (role != Qt::DisplayRole)
    return result;

  if (orientation == Qt::Vertical)
    return result;

  switch (section) {
  case Entry::Type:
    result = tr("Type");
    break;

  case Entry::Database:
    result = tr("Database");
    break;

  default:
    result = QVariant();
    break;
  }

  return result;
}

Qt::ItemFlags
DatabaseSettingsWidgetModel::
flags(const QModelIndex& index) const
{
  return QAbstractItemModel::flags(index);
}