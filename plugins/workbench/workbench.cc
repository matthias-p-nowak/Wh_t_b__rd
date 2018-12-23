#include <workbench.hh>

using namespace std;

QString WorkbenchPlugin::name(){
  return "workbench";
}

void WorkbenchPlugin::startup(){
  qDebug()<<"workbench starting up";
}

class _Dummy{
  public:
  _Dummy(){
    fromHere("hello from workbench");
  }
} _dummy;

