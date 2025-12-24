#include <QApplication>
#include "qt_game/qt_game_launcher.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    QtGameLauncher launcher;
    launcher.exec();
    
    return 0;
}