#ifndef INC_h96GkDIjTr4
#define INC_h96GkDIjTr4

#include <whtbrd_common.hh>
#include <QDebug>

class DummyPlugin: public IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  // Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "dummy.json")
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName )
  
public:
  void startup() override;
};
#endif
