#include <common.hh>

using namespace std;

void CommonPlugin::startup(QLinkedList<QObject *> &plugins){
  qDebug()<< "common firing up";
  setObjectName("common");
}

CommonPlugin::~CommonPlugin(){
  qDebug()<<"destroying CommonPlugin";
}

class _Dummy{
  public:
  _Dummy(){
    fromHere("hello from common part");
  }
} _dummy;
