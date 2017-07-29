#include "TraitsWidget.hpp"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

#include <Gui/Traits/WellTraitItemDelegate.hpp>
#include <Gui/Traits/TraitsWidgetModel.hpp>
#include <Gui/Traits/WellTraitEntry.hpp>

using Geo::Database::IConnection;
using Geo::Database::Gui::Traits::TraitsWidget;
using Geo::Database::Gui::Traits::TraitsWidgetModel;

using Geo::Database::Gui::Traits::WellTraitItemDelegate;

namespace Geo
{
namespace Database
{
namespace Gui
{

struct TraitsWidget::Private
{
  Private()
    : traitsTable(nullptr)
    , traitsWidgetModel(nullptr)
  {}

  QTableView* traitsTable;

  TraitsWidgetModel* traitsWidgetModel;
};

TraitsWidget::
TraitsWidget()
  : _p(new Private)
{
  createUi();
  connectSignals();
}


TraitsWidget::
~TraitsWidget()
{
  // TODO: check delete models everywhere
  if (_p->traitsWidgetModel)
    delete _p->traitsWidgetModel;

  delete _p;
}


void
TraitsWidget::
setConnection(std::shared_ptr<IConnection> connection)
{
  _p->traitsWidgetModel->setConnection(connection);
}


void
TraitsWidget::
createUi()
{
  setWindowTitle(tr("Well Traits Settings"));

  _p->traitsWidgetModel = new TraitsWidgetModel();

  // --------------

  _p->traitsTable = new QTableView();

  _p->traitsTable->setModel(_p->traitsWidgetModel);

  // temporarily use standard edit tool
  _p->traitsTable->setItemDelegate(new WellTraitItemDelegate());

  _p->traitsTable->setAlternatingRowColors(true);

  auto headerView = _p->traitsTable->horizontalHeader();

  using Gui::Traits::WellTraitEntry;
  headerView->setStretchLastSection(false);
  headerView->setSectionResizeMode(WellTraitEntry::Trait,
                                   QHeaderView::ResizeToContents);

  headerView->setSectionResizeMode(WellTraitEntry::Synonyms,
                                   QHeaderView::ResizeToContents);

  headerView->setSectionResizeMode(WellTraitEntry::Type,
                                   QHeaderView::Stretch);

  headerView->setSectionResizeMode(WellTraitEntry::CloseAction,
                                   QHeaderView::Fixed);
  headerView->resizeSection(WellTraitEntry::CloseAction, 20);

  auto verticalHeader = _p->traitsTable->verticalHeader();
  verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
  verticalHeader->hide();

  _p->traitsTable->setEditTriggers(QAbstractItemView::AllEditTriggers);

  QVBoxLayout* l = new QVBoxLayout();

  l->setContentsMargins(0, 0, 0, 0);

  l->addWidget(_p->traitsTable);

  setLayout(l);
}


void
TraitsWidget::
connectSignals()
{
  // for deleting rows
  connect(_p->traitsTable, SIGNAL(clicked(const QModelIndex&)),
          _p->traitsWidgetModel,   SLOT(onClicked(const QModelIndex&)));
}


//
}
}
}
