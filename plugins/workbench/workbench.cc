#include <workbench.hh>

using namespace std;


void WorkbenchPlugin::startup(QLinkedList<QObject *> &plugins){
  qDebug()<<"workbench starting up";
  setObjectName("workbench");
  MainWindow *mw=MainWindow::getInstance();
  mw->show();
}

class _Dummy{
  public:
  _Dummy(){
    fromHere("hello from workbench");
  }
} _dummy;

