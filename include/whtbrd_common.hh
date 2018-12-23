#ifndef INCLUDED_201812222
#define INCLUDED_201812222

#include <QtPlugin>

#define fromHere(msg) printf("%s:%d: %s\n",__FILE__,__LINE__,msg)

class IWhtbrdPlugin {
  public:
  virtual ~IWhtbrdPlugin(){}
  virtual QString name()=0;
  virtual void startup()=0;
};

#define IWhtbrdPluginName "org.whtbrd.plugin/1.0"

Q_DECLARE_INTERFACE(IWhtbrdPlugin, IWhtbrdPluginName)

#endif
