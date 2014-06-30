#ifndef Geo_Core_MainWindow_hpp
#define Geo_Core_MainWindow_hpp

#include <QMainWindow>

namespace Geo {
namespace Core {
class MainWindow: public QMainWindow
{
public:
  virtual
  void
  toCentralWidget(QWidget* widget) = 0;

private:
};
}
}
#endif
