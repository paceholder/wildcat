#include "ImportWidget.hpp"

#include <Uni/Logging/Logging>

#include <QAbstractItemModel>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QList>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#include <Database/Connections/Connection>
#include <Database/Connections/ConnectionManager>
#include <DependencyManager/ApplicationContext>

#include "ImportController.hpp"
#include "ImportTreeItemDelegate.hpp"
#include "ImportTreeModel.hpp"

#include "Las/LasImporter.hpp"
#include "Las/TreeWrapper/LasFileEntry.hpp"

using Geo::Import::Gui::ImportWidget;

struct ImportWidget::Private
{
  QComboBox* connectionsComboBox;

  QTreeView* treeView;

  QDialogButtonBox* dialogButton;
};

ImportWidget::
ImportWidget():
  p(new Private)
{
  setWindowTitle("Import Data");
  setMinimumSize(QSize(800, 400));

  setupUi();

  setupDataBinding();
}


ImportWidget::
~ImportWidget()
{
  delete p;
}


void
ImportWidget::
setupUi()
{
  using Geo::Import::Gui::ImportTreeItemDelegate;

  p->connectionsComboBox = new QComboBox();

  p->treeView = new QTreeView();

  p->treeView->setAlternatingRowColors(true);
  p->treeView->header()->show();
  p->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

  p->treeView->setItemDelegate(new  ImportTreeItemDelegate());

  p->dialogButton = new QDialogButtonBox(QDialogButtonBox::Ok);

  auto okButton =  p->dialogButton->button(QDialogButtonBox::Ok);
  okButton->setText(tr("Import"));

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(p->connectionsComboBox);
  layout->addWidget(p->treeView);
  layout->addWidget(p->dialogButton);

  connect(p->dialogButton, SIGNAL(accepted()),
          this, SLOT(onImportClicked()));
}


void
ImportWidget::
setModel(ImportTreeModel* importModel)
{
  p->treeView->setModel(importModel);

  p->treeView->expandAll();

  using DependencyManager::ApplicationContext;
  using Geo::Database::Connections::ConnectionManager;

  auto connectionManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  if (connectionManager->size())
    importModel->setConnection(connectionManager->at(0));
}


void
ImportWidget::
setupDataBinding()
{
  using DependencyManager::ApplicationContext;
  using Geo::Database::Connections::Connection;
  using Geo::Database::Connections::ConnectionManager;

  auto connectionManager =
    ApplicationContext::create<ConnectionManager>("Database.ConnectionManager");

  for (int i = 0; i < connectionManager->size(); ++i) {
    Connection::Shared c = connectionManager->at(i);
    p->connectionsComboBox->addItem(c->textDescription());
  }
}


void
ImportWidget::
onImportClicked()
{
  // take selected database  and push data into there

  auto importTreeModel =
    static_cast<ImportTreeModel*>(p->treeView->model());
  auto lasFileEntries = importTreeModel->getLasFileEntries();

  QVector<LasFile::Shared> lasFiles;

  for (auto lasFileEntry : lasFileEntries)
    lasFiles.append(lasFileEntry->lasFile());

  int databaseIndex = p->connectionsComboBox->currentIndex();

  LasImporter(databaseIndex).import(lasFiles);

  // close import window
  static_cast<QWidget*>(parent())->close();
}