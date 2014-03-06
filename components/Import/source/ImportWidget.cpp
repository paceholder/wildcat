#include "ImportWidget.hpp"

#include <Uni/Logging/Logging>

#include <QList>

#include <QDialogButtonBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#include "LasFile.hpp"
#include "LasFileParser.hpp"

#include "ImportController.hpp"
#include "ImportTreeModel.hpp"

namespace Geo {
namespace Import {
class ImportWidget::Private {
public:
  QPushButton*    openFileButton;
  QPlainTextEdit* textEdit;

  QTreeView* treeView;

  ImportTreeModel* importTreeModel;
};

ImportWidget::
ImportWidget():
  im(new Private) {
  setWindowTitle("Import Data");

  im->openFileButton = new QPushButton("Import Files");

  connect(im->openFileButton, SIGNAL(clicked()), this, SLOT(selectFile()));

  //

  // im->textEdit = new QPlainTextEdit();

  im->treeView = new QTreeView();

  im->importTreeModel = new ImportTreeModel();

  im->treeView->setModel(im->importTreeModel);
  im->treeView->setAlternatingRowColors(true);
  im->treeView->header()->show();

  QVBoxLayout* layout = new QVBoxLayout(this);

  layout->addWidget(im->openFileButton);
  // layout->addWidget(im->textEdit);
  layout->addWidget(im->treeView);

  this->setMinimumSize(QSize(500, 400));
}

ImportWidget::
~ImportWidget() {}

void
ImportWidget::
selectFile() {
  QVector<ImportTreeLasFileModel*> lasFileModels =
    ImportController::instance()->selectFilesAndImport(this);

  im->importTreeModel->setImportTreeLasFileModels(lasFileModels);

  INFO << "las files have been chosen";
}
}         // namespace Import
}         // namespace Geo