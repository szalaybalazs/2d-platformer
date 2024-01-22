#import <Cocoa/Cocoa.h>

void SetWindowRatio(void *window) {
    NSWindow *win = (__bridge NSWindow*) window;
    win.aspectRatio = NSMakeSize( 1280, 720 );
}