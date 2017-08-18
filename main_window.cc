#include "main_window.h"

using namespace Gtk;

MainWindow::MainWindow(const Glib::RefPtr<Gtk::Builder>& refGlade, BaseObjectType* cobject) :
    Gtk::Window(cobject), builder(refGlade){

    builder->get_widget("btn_ok", btnOk);
    builder->get_widget("btn_cancel", btnCancel);
    builder->get_widget("lbl_hw",lblNotice);

    btnOk->signal_clicked()
    	.connect(sigc::mem_fun(*this, &MainWindow::on_ok_button_clicked));
    btnCancel->signal_clicked()
    	.connect(sigc::mem_fun(*this, &MainWindow::on_cancel_button_clicked));

}


void MainWindow::on_ok_button_clicked(){
    lbl_hw->set_text("Ok clicked!");
}

void MainWindow::on_cancel_button_clicked(){
    lbl_hw->set_text("Cancel clicked!");
}