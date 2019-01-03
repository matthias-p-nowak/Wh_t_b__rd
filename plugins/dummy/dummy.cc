#include <dummy.hh>

/**
 * more later
 */
void DummyPlugin::startup(){
  qDebug()<< "dummy firing up";
  setObjectName("dummy");
  new Dummy_Cmd();
}


Dummy_Cmd::Dummy_Cmd(): Whtbrd_Cmd("Dummy"){
  fromHere("a dummy command instance");
}

Dummy_Cmd::~Dummy_Cmd(){
  
}
void Dummy_Cmd::exec(){
  fromHere("executing dummy");
}
