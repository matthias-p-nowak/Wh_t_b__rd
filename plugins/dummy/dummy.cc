#include <dummy.hh>

void DummyPlugin::startup(QLinkedList<QObject *> &plugins){
  qDebug()<< "dummy firing up";
  setObjectName("dummy");
}
