#include "main_window.h"
#include <gtkmm.h>
#include <set>
#include <iterator>
#include <iostream>

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "ine5430.gomoku");
  
  MainWindow main_window;
 
  //Shows the window and returns   when it is closed.
  return app->run(main_window);
}