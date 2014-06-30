#ifndef Geo_Database_DatabaseSettingsWidget_hpp
#define Geo_Database_DatabaseSettingsWidget_hpp

#include <QWidget>

namespace Geo {
namespace Database {
namespace Models {
namespace DatabaseSettingsWidgetModel {
class DatabaseSettingsWidgetModel;
}
}

namespace Gui {
namespace DatabaseSettingsWidget {
class DatabaseSettingsWidget: public QWidget
{
  Q_OBJECT

public:
  DatabaseSettingsWidget(Models::DatabaseSettingsWidgetModel::DatabaseSettingsWidgetModel*
                         tableModel);

  ~DatabaseSettingsWidget();

public slots:
  void
  onConnectionClicked(const QModelIndex& index);

private:
  void
  setupUi(
    Models::DatabaseSettingsWidgetModel::DatabaseSettingsWidgetModel* tableModel);

  void
  connectSignals();

private:
  struct Private;

  Private* p;
};
}
}
}
}

#endif // Geo_Database_DatabaseSettingsWidget_hpp
