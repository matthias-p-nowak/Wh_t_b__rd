#ifndef INCLUDED_201812224
#define INCLUDED_201812224

#include <whtbrd_common.hh>

#include <QDebug>
#include <QtPlugin>

class CommonPlugin: public IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "common.json")
  
public:
  ~CommonPlugin();
  void startup(QLinkedList<QObject *> &plugins) override;
};

#endif
