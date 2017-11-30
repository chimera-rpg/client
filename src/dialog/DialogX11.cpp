#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "dialog/Dialog.hpp"

namespace Chimera {
  Display *dis;
  int screen;
  Window win;
  GC gc;
  int win_width = 400;
  int win_height = 300;
  int ok_x = win_width - 64;
  int ok_y = win_height - 12;

  void redrawX(const std::string &title, const std::string &message) {
    XDrawRectangle(dis, win, gc, 1, 1, win_width-2, win_height-2);
    XDrawString(dis, win, gc, 20, 20, title.c_str(), title.length());
    XDrawString(dis, win, gc, 20, 50, message.c_str(), message.length());
    XDrawString(dis, win, gc, ok_x, ok_y, "BAIL", 4);
    XFlush(dis);
  }

  void ErrorDialog(const std::string &title, const std::string &message) {
    int black, white;

    dis     = XOpenDisplay(NULL);
    screen  = DefaultScreen(dis);
    black   = BlackPixel(dis, screen);
    white   = WhitePixel(dis, screen);
    win     = XCreateSimpleWindow(dis, RootWindow(dis, 0), 0, 0, win_width, win_height, 0, white, black);
    XSetStandardProperties(dis,win,title.c_str(),title.c_str(),None,NULL,0,NULL);
    XMapWindow(dis, win);
  
    gc      = XCreateGC(dis, win, 0, 0);

    XSetBackground(dis, gc, black);
    XSetForeground(dis, gc, white);

    XSelectInput(dis, win, ExposureMask|ButtonPressMask);

    redrawX(title, message);

    XEvent event;
    KeySym key;
    while(true) {
      XNextEvent(dis, &event);
      if (event.type == Expose && event.xexpose.count == 0) {
        redrawX(title, message);
      } else if (event.type == ButtonPress) {
        if (event.xbutton.x < win_width && event.xbutton.x >= ok_x-8 && event.xbutton.y < win_height && event.xbutton.y >= ok_y-8) {
          break;
        }
      }
    }
    XFreeGC(dis, gc);
    XDestroyWindow(dis,win);
    XCloseDisplay(dis);
  }
}
