#ifndef INCLUDED_201812224
#define INCLUDED_201812224

#include <whtbrd_common.hh>

#include <QDebug>
#include <QtPlugin>

class CommonPlugin: public QObject , IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "common.json")
  
public:
  ~CommonPlugin();
  QString name() override;
  void startup() override;
};

#endif
