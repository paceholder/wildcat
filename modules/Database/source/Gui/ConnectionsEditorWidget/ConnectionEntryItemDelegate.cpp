#include "ConnectionEntryItemDelegate.hpp"

#include <QComboBox>
#include <QLabel>
#include <QModelIndex>
#include <QWidget>

#include <Models/ConnectionsEditorWidgetModel/ConnectionEntry.hpp>
#include <Models/ConnectionsEditorWidgetModel/ConnectionsEditorWidgetModel.hpp>

#include <Connections/Connection.hpp>

using Geo::Database::Gui::ConnectionsEditorWidget::ConnectionEntryItemDelegate;

QWidget*
ConnectionEntryItemDelegate::
createEditor(QWidget*                    parent,
             const QStyleOptionViewItem& option,
             const QModelIndex&          index) const
{
  Q_UNUSED(option);

  using Geo::Database::Models::ConnectionEntry;

  if (index.parent().isValid())
    return nullptr;

  ConnectionEntry* connection =
    static_cast<ConnectionEntry*>(index.internalPointer());

  if (connection)
  {
    QComboBox* cb = new QComboBox(parent);

    connect(cb,
            SIGNAL(activated(int)),
            this,
            SLOT(comboBoxActivated(int)));

    return cb;
  }

  return nullptr;
}


void
ConnectionEntryItemDelegate::
updateEditorGeometry(QWidget*                    editor,
                     const QStyleOptionViewItem& option,
                     const QModelIndex&          index) const
{
  Q_UNUSED(index);

  editor->setGeometry(option.rect);
}


void
ConnectionEntryItemDelegate::
setEditorData(QWidget* editor, const QModelIndex& index) const
{
  Q_UNUSED(index);

  QComboBox* c = static_cast<QComboBox*>(editor);

  c->addItem(Connections::Connection::connectionTypeName(Connections::
                                                         DatabaseType::SQLite));
  c->addItem(Connections::Connection::connectionTypeName(Connections::
                                                         DatabaseType::MongoDB));

  c->showPopup();
}


void
ConnectionEntryItemDelegate::
setModelData(QWidget*            editor,
             QAbstractItemModel* model,
             const QModelIndex&  index) const
{
  using Geo::Database::Models::ConnectionsEditorWidgetModel;

  if (!index.parent().isValid())
  {
    QComboBox* c = static_cast<QComboBox*>(editor);
    ConnectionsEditorWidgetModel* m =
      static_cast<ConnectionsEditorWidgetModel*>(model);

    m->addConnection((Connections::DatabaseType)c->currentIndex());
  }
}


void
ConnectionEntryItemDelegate::
comboBoxActivated(int index)
{
  Q_UNUSED(index);

  QComboBox* cd = static_cast<QComboBox*>(QObject::sender());

  emit commitData(cd);

  emit closeEditor(cd);
}
