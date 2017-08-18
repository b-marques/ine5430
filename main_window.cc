#include "main_window.h"
#include <iostream>
#include <string>

MainWindow::MainWindow()
{
  grid = Gtk::manage(new Gtk::Grid());

  std::string cell;
  for (int i = 0; i < 15; ++i) {
    if(i){
      cell = std::to_string(i) + "," + "0";
      btn_grid[i][0] = Gtk::manage(new Gtk::Button(cell));
      btn_grid[i][0] -> signal_clicked().connect(sigc::bind<Gtk::Button*>(sigc::mem_fun(*this, &MainWindow::on_button_clicked), btn_grid[i][0]));

      grid -> attach_next_to(*btn_grid[i][0], *btn_grid[i-1][0], Gtk::POS_BOTTOM, 1, 1);
      btn_grid[i][0] -> show();
    } else {
      cell = std::to_string(i) + "," + "0";
      btn_grid[i][0] = Gtk::manage(new Gtk::Button(cell));
      btn_grid[i][0] -> signal_clicked().connect(sigc::bind<Gtk::Button*>(
              sigc::mem_fun(*this, &MainWindow::on_button_clicked), btn_grid[i][0]));
      grid -> attach_next_to(*btn_grid[i][0], Gtk::POS_RIGHT, 1, 1);
      btn_grid[i][0] -> show();
    }
    for (int j = 0; j < 15; ++j) {
      if(j) {
        cell = std::to_string(i) + "," + std::to_string(j);
        btn_grid[i][j] = Gtk::manage(new Gtk::Button(cell));
        btn_grid[i][j] -> signal_clicked().connect(sigc::bind<Gtk::Button*>(sigc::mem_fun(*this, &MainWindow::on_button_clicked), btn_grid[i][j]));
        grid -> attach_next_to(*btn_grid[i][j],*btn_grid[i][j-1], Gtk::POS_RIGHT, 1, 1);
        btn_grid[i][j] -> show();
      }
    }
  }


  set_border_width(10);
  grid->show();

  add(*grid);

}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked(Gtk::Button* clicked_button)
{

  clicked_button -> set_label("O");
}