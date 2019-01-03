#ifndef INC_8UsLgj6iHQk
#define INC_8UsLgj6iHQk

#include <whtbrd_common.hh>
#include <whtbrd_show.hh>
#include <QDebug>
#include <QtPlugin>
#include <unordered_set>
#include <utility>

/**
 * a simple plugin - good as a starting point
 */
class CommonPlugin: public IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  // Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "common.json")
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName )
public:
  void startup() override;
};

#endif
