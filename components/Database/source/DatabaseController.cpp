#include "DatabaseController.hpp"

#include <QtWidgets/QLabel>

#include <Core/MainWindow>
#include <Uni/Logging/Logging>

#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>
#include <Models/SettingsWidgetModel/SettingsWidgetModel.hpp>

#include <Gui/ConnectionsEditorWidget/ConnectionsEditorWidget.hpp>
#include <Gui/DatabaseSettingsWidget/DatabaseSettingsWidget.hpp>

#include <DependencyManager/ApplicationContext>

namespace Geo {
namespace  Database {
DatabaseController* DatabaseController::_instance = nullptr;

DatabaseController*
DatabaseController::
instance()
{
  if (!_instance)
    _instance = new DatabaseController();

  return _instance;
}

DatabaseController::
DatabaseController()
{
  //
}

DatabaseController::
~DatabaseController()
{
  //
}

void
DatabaseController::
showConnectionsWidget()
{
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;
  using Geo::Database::Gui::ConnectionsEditorWidget;
  using Model =
          Geo::Database::Models::ConnectionsEditorWidgetModel::
          ConnectionsEditorWidgetModel;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  auto databaseConnectionsTreeModel = new Model();

  auto databaseConnectionsWidget = new ConnectionsEditorWidget(
    databaseConnectionsTreeModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}

void
DatabaseController::
showSettingsWidget()
{
  using DependencyManager::ApplicationContext;
  using Geo::Core::MainWindow;

  using Geo::Database::Gui::DatabaseSettingsWidget;
  using Geo::Database::Models::SettingsWidgetModel::SettingsWidgetModel;

  MainWindow* mainWindow =
    ApplicationContext::create<MainWindow>("Core.MainWindow");

  auto databaseSettingsWidgetModel = new SettingsWidgetModel();

  auto databaseConnectionsWidget = new DatabaseSettingsWidget(
    databaseSettingsWidgetModel);

  mainWindow->toCentralWidget(databaseConnectionsWidget);
}

//
}
}
