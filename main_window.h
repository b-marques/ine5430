#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include "gomoku_core.h"

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  ~MainWindow();
  const static int GRID_SIZE = 15;

private:  
  //GUI Building
  void load_grid();
  void load_box_layout();
  void load_buttons();

  //Signal handlers:
  void on_grid_button_clicked(int x, int y, Gtk::Button* clicked_button);
  void on_restart_button_clicked(Gtk::Button* clicked_button);

  // Game control
  GomokuCore* gomoku_core;

  //Member widgets:
  Gtk::Button* btn_restart;
  Gtk::Button* btn_human_vs_human;
  Gtk::Button* btn_human_vs_computer;
  Gtk::Button* btn_computer_vs_computer;
  Gtk::Box* v_box;
  Gtk::Box* h_box;
  Gtk::Grid* grid;
  Gtk::Button* btn_grid[GRID_SIZE][GRID_SIZE];
};

#endif // MAINWINDOW_H