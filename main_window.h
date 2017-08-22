#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include "gomoku_core.h"

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  ~MainWindow();

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
  std::unordered_set<GomokuPlay> plays_to_paint;

  //Member widgets:
  Gtk::Button* btn_restart;
  Gtk::Button* btn_human_vs_human;
  Gtk::Button* btn_human_vs_computer;
  Gtk::Button* btn_computer_vs_computer;
  Gtk::Label* lbl_info;
  Gtk::Box* v_box;
  Gtk::Box* h_box;
  Gtk::Grid* grid;
  Gtk::Button* btn_grid[GomokuCore::GRID_SIZE][GomokuCore::GRID_SIZE];
};

#endif // MAINWINDOW_H