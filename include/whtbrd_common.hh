#ifndef INCLUDED_201812222
#define INCLUDED_201812222

#include <QtPlugin>

#define fromHere(msg) printf("%s:%d: %s\n",__FILE__,__LINE__,msg)

class IWhtbrdPlugin {
  virtual QString name();
  virtual void startup();
  virtual ~IWhtbrdPlugin();
};

#define IWhtbrdPluginName "org.whtbrd.plugin/1.0"

Q_DECLARE_INTERFACE(IWhtbrdPlugin, IWhtbrdPluginName)

#endif
