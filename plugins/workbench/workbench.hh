#ifndef INC_VGYnNgUTW4e
#define INC_VGYnNgUTW4e

#include <whtbrd_common.hh>
#include <mainwindow.hh>
#include <preview.hh>
#include <fullscreen.hh>
#include <comselwid.hh>
#include <editCmd.hh>

#include <QDebug>
#include <QListWidgetItem>


class WorkbenchPlugin: public IWhtbrdPlugin{
  Q_OBJECT
  Q_INTERFACES(IWhtbrdPlugin)
  // Q_PLUGIN_METADATA(IID IWhtbrdPluginName FILE "workbench.json")
  Q_PLUGIN_METADATA(IID IWhtbrdPluginName )
  
public:
  void startup() override;
};

#endif
