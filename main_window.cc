#include "main_window.h"
#include <iostream>
#include <string>

MainWindow::MainWindow()
{
  load_grid();
  load_box_layout();

  set_border_width(15);

  add(*v_box);

}

MainWindow::~MainWindow()
{
  delete btn_restart;
  delete btn_human_vs_human;
  delete btn_human_vs_computer;
  delete btn_computer_vs_computer;
  for (int i = 0; i < 15; ++i)
  {
    for (int j = 0; j < 15; ++j)
    {
      delete btn_grid[i][j];
    }
  }
  delete grid;
  delete h_box;
  delete v_box;
  
  
}

void MainWindow::on_button_clicked(Gtk::Button* clicked_button)
{
  clicked_button -> set_label("O");
}

void MainWindow::load_grid()
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

  grid->show();
}

void MainWindow::load_box_layout()
{
  v_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 8));
  v_box -> pack_start(*grid);

  h_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 4));

  load_buttons();

  h_box -> show();

  v_box -> pack_start(*h_box);
  v_box -> show();
}

void MainWindow::load_buttons()
{
  btn_restart = Gtk::manage(new Gtk::Button("Restart"));
  btn_restart -> show();
  btn_human_vs_human = Gtk::manage(new Gtk::Button("vs Human"));
  btn_human_vs_human -> show();
  btn_human_vs_computer = Gtk::manage(new Gtk::Button("vs IA"));
  btn_human_vs_computer -> show();
  btn_computer_vs_computer = Gtk::manage(new Gtk::Button("IA vs IA"));
  btn_computer_vs_computer -> show();
  h_box -> pack_start(*btn_restart);
  h_box -> pack_start(*btn_human_vs_human);
  h_box -> pack_start(*btn_human_vs_computer);
  h_box -> pack_start(*btn_computer_vs_computer);
}
