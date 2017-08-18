#include <gtkmm.h>

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

class MainWindow : public Gtk::Window{
protected:
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Button *btn_ok;
    Gtk::Button *btn_cancel;
    Gtk::Label  *lbl_hw;

public:
    MainWindow();//constructor

protected:
    //signal handlers
    void on_ok_button_clicked();
    void on_cancel_button_clicked();
};

#endif //MAIN_WINDOW_H