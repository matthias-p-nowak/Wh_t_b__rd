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

list<Whtbrd_Cmd *> Whtbrd_Cmd::cmds;

Whtbrd_Cmd::Whtbrd_Cmd(string _name):
  name(_name) {
  cmds.push_back(this);
}

Whtbrd_Cmd::~Whtbrd_Cmd() {

}

list<Whtbrd_Cmd *> Whtbrd_Cmd::getList() {
  return cmds;
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

forward_list<Base *> recentObjects(Base *newObject) {
  if(newObject) {
    _allRecentObjects.push_front(newObject);
    recentObjectFound(NULL);
    _allRecentObjects.remove_if(recentObjectFound);
  }
  return _allRecentObjects;
}
