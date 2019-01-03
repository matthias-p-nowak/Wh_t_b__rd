#ifndef INC_VEhJgHBhI79
#define INC_VEhJgHBhI79

#include <string>
#include <list>
#include <whtbrd_base.hh>
#include <whtbrd_show.hh>

class Whtbrd_Cmd: public Base{

public:
  Whtbrd_Cmd(std::string name);
  virtual ~Whtbrd_Cmd();
  static std::list<Whtbrd_Cmd *> getList();
  std::string name;
  virtual void exec()=0;
  
private:
  static std::list<Whtbrd_Cmd *> cmds;
};

#endif
