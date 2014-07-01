#ifndef Geo_Import_Gui_ImportTreeWidget_hpp
#define Geo_Import_Gui_ImportTreeWidget_hpp

#include <QtWidgets/QStyledItemDelegate>

namespace Geo {
namespace Import {
namespace Gui {

class ImportTreeItemDelegate: public QStyledItemDelegate
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
}
}
}


#endif //  Geo_Import_Gui_ImportTreeWidget_hpp
