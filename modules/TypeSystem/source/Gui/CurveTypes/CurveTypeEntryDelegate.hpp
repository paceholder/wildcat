#pragma once

#include <QtWidgets/QStyledItemDelegate>

namespace Geo
{
namespace TypeSystem
{
namespace Gui
{
//

class CurveTypeEntryDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  QWidget*
  createEditor(QWidget*                    parent,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index) const override;

  void
  updateEditorGeometry(QWidget*                    editor,
                       const QStyleOptionViewItem& option,
                       const QModelIndex&          index) const override;

  void
  setEditorData(QWidget* editor, const QModelIndex& index) const override;

  void
  setModelData(QWidget*            editor,
               QAbstractItemModel* model,
               const QModelIndex&  index) const override;
};

//
} // namespace Gui
} // namespace TypeSystem
} // namespace Geo
