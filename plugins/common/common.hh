#ifndef INC_8UsLgj6iHQk
#define INC_8UsLgj6iHQk

#include <whtbrd_common.hh>

#include <QDebug>
#include <QtPlugin>

class CommonPlugin: public IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  // Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "common.json")
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName )
  
public:
  ~CommonPlugin();
  void startup(QLinkedList<QObject *> &plugins) override;
};

#endif
