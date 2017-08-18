#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

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
  void on_button_clicked(Gtk::Button* clicked_button);

  //Member widgets:
  Gtk::Button* btn_restart;
  Gtk::Button* btn_human_vs_human;
  Gtk::Button* btn_human_vs_computer;
  Gtk::Button* btn_computer_vs_computer;
  Gtk::Box* v_box;
  Gtk::Box* h_box;
  Gtk::Grid* grid;
  Gtk::Button* btn_grid[15][15];
};

#endif // MAINWINDOW_H