#ifndef INCLUDED_201812223
#define INCLUDED_201812223

#include <whtbrd_common.hh>

#include <QDebug>


class WorkbenchPlugin: public IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "workbench.json")
  
public:
  void startup(QLinkedList<QObject *> &plugins) override;
};

#endif
