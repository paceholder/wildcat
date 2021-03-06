#include "UnitWidget.hpp"

#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>
#include <QtCore/QPoint>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Core/IMainWindow>

#include <ComponentManager/Creator>
#include <Models/ConnectionListModel>

#include <Gui/Units/UnitTableEntryDelegate.hpp>
#include <Gui/Units/UnitModel.hpp>
#include <Gui/Units/UnitTableEntry.hpp>

using Geo::TypeSystem::Gui::UnitTableEntryDelegate;
using Geo::TypeSystem::Gui::UnitWidget;
using Geo::TypeSystem::Gui::Units::UnitModel;
using Geo::TypeSystem::Gui::Units::UnitTableEntry;

struct UnitWidget::Private
{
  QPushButton* loadXmlButton;

  QPushButton* saveXmlButton;

  // curve types tree
  QTableView* unitsTable;

  UnitModel* unitsModel;
};

UnitWidget::
UnitWidget()
  : _p(new Private)
{
  setupUi();

  connectSignals();

  emit notifyMainWindow(tr("Configure available Units"));
}


UnitWidget::
~UnitWidget()
{
  if (_p->unitsModel)
    delete _p->unitsModel;

  delete _p;
}


void
UnitWidget::
setupUi()
{
  setWindowTitle("Unit Types");

  _p->loadXmlButton = new QPushButton(tr("Load Xml"));

  _p->loadXmlButton->setToolTip(tr("Loads Xml file"));

  _p->saveXmlButton = new QPushButton(tr("Save Xml"));

  _p->saveXmlButton->setToolTip(tr("Save Geo Xml file"));

  // --------------------

  _p->unitsModel = new UnitModel();

  _p->unitsTable = new QTableView();

  _p->unitsTable->setModel(_p->unitsModel);

  _p->unitsTable->setItemDelegate(new UnitTableEntryDelegate);

  _p->unitsTable->setContextMenuPolicy(Qt::CustomContextMenu);

  _p->unitsTable->setAlternatingRowColors(true);
  _p->unitsTable->verticalHeader()->setSectionResizeMode(
    QHeaderView::ResizeToContents);

  _p->unitsTable->verticalHeader()->hide();

  _p->unitsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  // _p->unitsTable->setSelectionMode(QAbstractItemView::SingleSelection);
  _p->unitsTable->setSelectionMode(QAbstractItemView::NoSelection);

  auto horizHeader = _p->unitsTable->horizontalHeader();

  horizHeader->setSectionResizeMode(QHeaderView::Stretch);
  //

  horizHeader->setSectionResizeMode(UnitTableEntry::Name,
                                    QHeaderView::ResizeToContents);
  horizHeader->setSectionResizeMode(UnitTableEntry::Symbol,
                                    QHeaderView::ResizeToContents);
  horizHeader->setSectionResizeMode(UnitTableEntry::Scale,
                                    QHeaderView::ResizeToContents);
  horizHeader->setSectionResizeMode(UnitTableEntry::Offset,
                                    QHeaderView::ResizeToContents);
  // horizHeader->setSectionResizeMode(UnitTableEntry::Dimensions,
  // QHeaderView::ResizeToContents);

  //
  horizHeader->setStretchLastSection(false);

  horizHeader->setSectionResizeMode(UnitTableEntry::CloseAction,
                                    QHeaderView::Fixed);

  horizHeader->resizeSection(UnitTableEntry::CloseAction, 20);

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->setContentsMargins(0, 0, 0, 0);

  auto ll = new QHBoxLayout();

  ll->addWidget(_p->loadXmlButton);
  ll->addWidget(_p->saveXmlButton);
  ll->addStretch();
  layout->addLayout(ll);

  layout->addWidget(_p->unitsTable);
}


void
UnitWidget::
connectSignals()
{
  connect(_p->loadXmlButton, SIGNAL(released()),
          this, SLOT(onLoadXmlClicked()));

  connect(_p->saveXmlButton, SIGNAL(released()),
          this, SLOT(onSaveXmlClicked()));

  // for deleting rows
  connect(_p->unitsTable, SIGNAL(clicked(const QModelIndex&)),
          _p->unitsModel,   SLOT(onClicked(const QModelIndex&)));

  // -------- main window notification
  using Geo::Core::IMainWindow;
  auto mainWindow = ComponentManager::create<IMainWindow*>("Core.MainWindow");

  connect(this, SIGNAL(notifyMainWindow(QString)),
          mainWindow, SLOT(setStatus(QString)));
}


// TODO: remove data processing from GUI
void
UnitWidget::
onTableViewMenuRequested(const QPoint& pos)
{
  Q_UNUSED(pos);

  // QModelIndex index = _p->unitsTable->indexAt(pos);

  // if (!index.isValid())
  // return;

  // using Geo::Import::TreeWrapper::TreeEntry;
  // using Geo::Import::TreeWrapper::WellInfoBase;
  // using MenuFactory = TreeWrapperMenuFactory;

  // TreeEntry* treeEntry =
  // static_cast<TreeEntry*>(index.internalPointer());

  // WellInfoBase* wellInfo =
  // dynamic_cast<WellInfoBase*>(treeEntry);

  // if (wellInfo) {
  // QSharedPointer<QMenu>
  // menu(MenuFactory::getWellInformationBaseMenu(
  // wellInfo,
  // index.column()));

  // if (menu.isNull())
  // return;

  // menu->exec(_p->unitsTable->mapToGlobal(pos));
  // }
}


void
UnitWidget::
onLoadXmlClicked()
{
  QString fileName =
    QFileDialog::getOpenFileName(this,
                                 tr("Select a Geo Units Xml file"),
                                 QString(),
                                 tr("Curve Type files (*.xml)"));

  if (fileName.isEmpty())
    return;

  if (_p->unitsModel)
    _p->unitsModel->loadXml(fileName);
}


void
UnitWidget::
onSaveXmlClicked()
{
  QString fileName =
    QFileDialog::getSaveFileName(this,
                                 tr("Save Geo Curve Type Xml file"),
                                 QString(),
                                 tr("Database files (*.xml )"));

  if (fileName.isEmpty())
    return;

  if (auto unitModel = static_cast<UnitModel*>(_p->unitsTable->model()))
    unitModel->saveXml(fileName);
}


void
UnitWidget::
setConnection(std::shared_ptr<IConnection> connection)
{
  _p->unitsModel->setConnection(connection);
}
