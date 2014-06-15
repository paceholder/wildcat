#include "ConnectionManager.hpp"

#include "SQLiteConnection.hpp"

#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

#include <Uni/Logging/Logging>

using Geo::Database::Connection;
using Geo::Database::ConnectionManager;

ConnectionManager::
ConnectionManager()
{
  loadFromXml();
}


QSharedPointer<Connection>
ConnectionManager::
createConnection()
{
  auto sqliteConnection = new SQLiteConnection();

  QSharedPointer<Connection> c(sqliteConnection);

  appendConnection(c);

  return c;
}


void
ConnectionManager::
appendConnection(QSharedPointer<Connection> c)
{
  connect(c.data(), SIGNAL(databaseChanged(QString)),
          this, SLOT(storeToXml()));

  _connections.append(c);
  storeToXml();
}


void
ConnectionManager::
removeConnection(int i)
{
  _connections.remove(i);

  storeToXml();
}


// -------------------------

void
ConnectionManager::
loadFromXml()
{
  QDomDocument doc("Connections");

  QFile file(getDefaultConfigFile());

  if (!file.open(QIODevice::ReadOnly))
    return;

  if (!doc.setContent(&file)) {
    file.close();
    return;
  }

  file.close();

  // ------

  QDomElement docElem = doc.documentElement();

  QDomNode n = docElem.firstChild();

  while (!n.isNull()) {
    // try to convert the node to an element.
    QDomElement e = n.toElement();

    if (!e.isNull()) {
      Connection::Shared connection =
        Connection::restoreConnectionFromXml(e);

      if (!connection.isNull())
        appendConnection(connection);
    }

    n = n.nextSibling();
  }
}


void
ConnectionManager::
storeToXml()
{
  QDomDocument doc("Connections");

  QDomElement root = doc.createElement("Connections");
  doc.appendChild(root);

  for (auto connection : _connections)
    root.appendChild(connection->xmlDescription(doc));

  QString xml = doc.toString();

  QString fileName = getDefaultConfigFile();

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;

  QTextStream out(&file);

  out << xml;
}


QString
ConnectionManager::
getDefaultConfigFile() const
{
  QString configLocation =
    QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

  QString fileName =
    QDir(configLocation).absoluteFilePath("geo.xml");

  return fileName;
}
