#include <QtCore/QObject> // include this before mudbox headers.
#include <Mudbox/mudbox.h>  

#include "SBrush.h"  

using namespace mudbox;

void Initializer();

static const char *sPluginName = "SBrush1";
static const char *sPluginDescription = "sculpt brush example";
static const char *sPluginAuthorName = "";
static const char *sPluginURL = "";
// Register this plugin. The "Initializer" method will be called when the plugin is loaded.
MB_PLUGIN( sPluginName, sPluginDescription, sPluginAuthorName, sPluginURL, Initializer );

// This function will be called then the plugin is loaded.
void Initializer(void)
{
	
	MB_ADD_CONFIG2( SBrush, 0, NTR("SBrush1"), QObject::tr("SBrush1"), NTR("Custom Sculpt Tools"), QObject::tr("Custom Sculpt Tools"), QObject::tr("sbrushToolTip"));

}

