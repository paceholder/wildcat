#ifndef Geo_Import_LASFile_hpp
#define Geo_Import_LASFile_hpp

#include <QtCore/QDateTime>
#include <QtCore/QMap>
#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QVector>

namespace Geo {
namespace Import {
/**
 * Class contains all the informaation from a LAS file split into special
 * structures
 */
class LASFile {
public:
  LASFile(): valid(false) {}

  struct WellInformationEntry {
    QString mnem;
    QString units;
    QString name;
    QString value;
  };

  struct WellInformation {
    QString wellName;
    double  start;
    double  stop;
    double  step;
    double  nullValue;
    QString units;

    QVector<WellInformationEntry> entries;
  };

  struct CurveInformationEntry {
    QString mnem;
    QString units;
    QString code;
    QString description;
  };

  struct ParameterInformationEntry {
    QString mnem;
    QString unit;
    QString comment;
  };

public:
  LASFile(QString fileName);

  QString
  getText() const;

  WellInformation                    wellInformation;
  QVector<CurveInformationEntry>     curveInformation;
  QVector<ParameterInformationEntry> parameterInformation;

  QList<QPair<QString, QVector<double> > > data;

  bool valid;
};
}
}
#endif // Geo_Import_LASFile_hpp
