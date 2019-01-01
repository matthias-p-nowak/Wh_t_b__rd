#include <workbench.hh>

using namespace std;

void WorkbenchPlugin::startup(QLinkedList<QObject *> &plugins){
  qDebug()<<"workbench starting up";
  setObjectName("workbench");
}

class _Dummy{
  public:
  _Dummy(){
    fromHere("hello from workbench");
  }
} _dummy;

