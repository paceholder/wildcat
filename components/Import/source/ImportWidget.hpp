#ifndef Geo_Import_ImportWidget_hpp
#define Geo_Import_ImportWidget_hpp

#include <QWidget>

namespace Geo {
namespace Import {
class ImportWidget: public QWidget {
  Q_OBJECT

public:
  Q_INVOKABLE
  ImportWidget();

  virtual
  ~ImportWidget();

public slots:
  void
  selectFile();

private:
  class Private;

  Private* im;
};
} // namespace Import
} // namespace Geo

#endif