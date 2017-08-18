#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  ~MainWindow();

protected:
  //Signal handlers:
  void on_button_clicked(Gtk::Button* clicked_button);

  //Member widgets:
  Gtk::Button* btn_restart;
  Gtk::Button* btn_human_vs_human;
  Gtk::Grid* grid;
  Gtk::Button* btn_grid[15][15];
};

#endif // MAINWINDOW_H