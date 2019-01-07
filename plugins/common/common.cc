#include <common.hh>

/**
 * almost nothing to do
 */
using namespace std;

void CommonPlugin::startup() {
  qDebug()<< "common firing up";
  fromHere("Common plugin");
  setObjectName("common");
  recentObjects(new Whtbrd_Show());
}


Whtbrd_Cmd::Whtbrd_Cmd(string _name):
  name(_name) {
  recentObjects(this);
}

Whtbrd_Cmd::~Whtbrd_Cmd() {
  fromHere(name.c_str());
}


void Whtbrd_Cmd::getCmds(list<Whtbrd_Cmd *> &cmds){
  unordered_set<Whtbrd_Cmd *> haveAlready;
  auto ro=recentObjects();
  for(auto b : ro){
    auto c=dynamic_cast2<Whtbrd_Cmd>(b);
    if(c){
      auto ret=haveAlready.insert(c);
      if(ret.second){
        // inserted
        cmds.push_back(c);
      }
    }
  }
}


forward_list<Base *> _allRecentObjects;

bool recentObjectFound(const Base *obj) {
  static unordered_set<const Base *> found;
  if(obj==NULL) {
    found.clear();
    return true;
  }
  auto r=found.insert(obj);
  return ! r.second;
}

time_t lastCleaned=0;

forward_list<Base *> recentObjects(Base *newObject) {
  if(newObject) {
    _allRecentObjects.push_front(newObject);
    auto t=lastCleaned;
    lastCleaned=time(NULL);
    if(t<lastCleaned) {
      recentObjectFound(NULL);
      _allRecentObjects.remove_if(recentObjectFound);
    }
  }
  return _allRecentObjects;
}
