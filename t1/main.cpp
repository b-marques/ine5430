#include "main_window.h"
#include <gtkmm.h>
#include <set>
#include <iterator>
#include <iostream>

#include <unordered_set>
#include "gomoku_player.h"

int main(int argc, char *argv[]) {

	// GomokuPlayer player = GomokuPlayer();

	// std::cout <<  "set contains:" << std::endl;
	// player.play(0, 0);

	// auto aux = player.plays().find(GomokuPlay(0,0));
	// if(aux != player.plays().end()){
	//   std::cout << player.plays().size() << std::endl;
	// } else {
	//   std::cout << "not find" << std::endl;
	// }

	// for (auto it = player.plays().begin(); it != player.plays().end(); ++it)
	//   std::cout << " " << it -> x();

	auto app = Gtk::Application::create(argc, argv, "ine5430.gomoku");

	MainWindow main_window;

	//Shows the window and returns   when it is closed.
	return app->run(main_window);
}
