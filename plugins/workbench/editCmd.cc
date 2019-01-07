#include <workbench.hh>

using namespace std;

EditCommand::EditCommand(): Whtbrd_Cmd("Edit"){
  fromHere("constructing edit command");
}

EditCommand::~EditCommand(){
  fromHere("destroying edit command");
}

void EditCommand::exec(){
  fromHere("should be editing something");
  // TODO do the real implementation
}
