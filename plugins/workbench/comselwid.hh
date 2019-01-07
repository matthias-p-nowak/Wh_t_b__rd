#ifndef INC_a6iGvMRGOei
#define INC_a6iGvMRGOei

#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QKeyEvent>

class CommandSelectionWidgetList;

class CommandSelectionWidget: public QDialog {
private:
 CommandSelectionWidgetList *cswl;
public:
  CommandSelectionWidget(QWidget *parent=NULL);
  virtual ~CommandSelectionWidget();
  void fill();
  void execCmd(QString cmd);
public slots:
  void itemSelected(QListWidgetItem *item);
};

#endif
