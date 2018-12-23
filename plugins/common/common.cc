#include <common.hh>

using namespace std;

QString CommonPlugin::name(){
  return "common";
}

void CommonPlugin::startup(){
  qDebug()<< "common firing up";
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
