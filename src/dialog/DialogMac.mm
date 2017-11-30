#include "dialog/Dialog.hpp"
#import <Cocoa/Cocoa.h>

namespace Chimera {
  void ErrorDialog(const std::string &title, const std::string &message) {
    NSAlert *alert = [[NSAlert alloc] init];
    NSAlertStyle style;

#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_12
    style = NSAlertStyleCritical;
#else
    style = NSCriticalAlertStyle;
#endif

    [alert setMessageText:[NSString stringWithCString:title.c_str() encoding:[NSString defaultCStringEncoding]]];
    [alert setInformativeText:[NSString stringWithCString:message.c_str() encoding:[NSString defaultCStringEncoding]]];

    [alert setAlertStyle:style];
    [alert addButtonWithTitle:@"Bail"];

    // Force the alert to appear on top of any other windows
    [[alert window] setLevel:NSModalPanelWindowLevel];

    [alert runModal];
    [alert release];
  }
}
