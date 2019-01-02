#include <common.hh>

/**
 * almost nothing to do
 */
using namespace std;

void CommonPlugin::startup(){
  qDebug()<< "common firing up";
  fromHere("Common plugin");
  setObjectName("common");
}
