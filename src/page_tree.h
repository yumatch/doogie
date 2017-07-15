#ifndef DOOGIE_PAGE_TREE_H_
#define DOOGIE_PAGE_TREE_H_

#include <QtWidgets>
#include "browser_stack.h"
#include "browser_widget.h"
#include "page_tree_item.h"

namespace doogie {

class PageTree : public QTreeWidget {
  Q_OBJECT

 public:
  explicit PageTree(BrowserStack* browser_stack, QWidget* parent = nullptr);
  void NewPage(const QString& url, bool top_level);
  void CloseCurrentPage();
  void CloseAllPages();
  QMovie* LoadingIconMovie();

 protected:
  virtual Qt::DropActions supportedDropActions() const override;
  virtual void dropEvent(QDropEvent* event) override;
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event) override;
  virtual void mouseReleaseEvent(QMouseEvent* event) override;
  virtual void rowsInserted(const QModelIndex& parent,
                            int start,
                            int end) override;

 private:
  void AddBrowser(QPointer<BrowserWidget> browser,
                  PageTreeItem* parent,
                  bool make_current);
  void CloseItem(PageTreeItem* item);
  void DestroyItem(PageTreeItem* item, bool include_children);

  BrowserStack* browser_stack_ = nullptr;
  QMovie* loading_icon_movie_ = nullptr;
  bool close_dragging_ = false;
  PageTreeItem* close_dragging_on_ = nullptr;
  QRubberBand* rubber_band_ = nullptr;
  QPoint rubber_band_origin_;
  QItemSelection rubber_band_orig_selected_;

 signals:
  void ItemClose(PageTreeItem* item);
  void ItemClosePress(PageTreeItem* item);
  void ItemCloseRelease(PageTreeItem* item);
};

}  // namespace doogie

#endif  // DOOGIE_PAGE_TREE_H_
