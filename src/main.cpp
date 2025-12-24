#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <thread>
#include <chrono>

#include "qt_game/qt_game_window.hpp"
#include "game.hpp"
#include "first_level.hpp"
#include "second_level.hpp"
#include "third_level.hpp"
#include "qt_ui_factory.hpp"

class QtGameController : public QObject {
    Q_OBJECT
    
private:
    biv::Game game;
    biv::QtUIFactory* ui_factory = nullptr;
    biv::GameLevel* game_level = nullptr;
    biv::Mario* mario = nullptr;
    
    bool keyLeftPressed = false;
    bool keyRightPressed = false;
    bool keySpacePressed = false;
    bool was_on_third_level = false;
    
    QTimer* gameTimer;
    QtGameWindow* gameWindow = nullptr;
    
    const int SCALE_FACTOR = 10;
    bool isInWater = false;
    int waterDeathTimer = 0;
    
public:
    QtGameController() {
        gameTimer = new QTimer(this);
        connect(gameTimer, &QTimer::timeout, this, &QtGameController::updateGame);
        gameTimer->setInterval(16);
    }
    
    ~QtGameController() {
        delete ui_factory;
        delete game_level;
    }
    
    void startGame(QtGameWindow* window) {
        gameWindow = window;
        
        delete ui_factory;
        delete game_level;
        
        ui_factory = new biv::QtUIFactory(&game, window->getScene());
        game_level = new biv::FirstLevel(ui_factory);
        mario = ui_factory->get_mario();
        was_on_third_level = false;
        isInWater = false;
        waterDeathTimer = 0;
        
        window->drawWater(600);
        
        gameTimer->start();
    }
    
    void handleKeyPress(QKeyEvent* event) {
        switch (event->key()) {
            case Qt::Key_A:
            case Qt::Key_Left:
                keyLeftPressed = true;
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                keyRightPressed = true;
                break;
            case Qt::Key_Space:
            case Qt::Key_W:
            case Qt::Key_Up:
                keySpacePressed = true;
                break;
        }
    }
    
    void handleKeyRelease(QKeyEvent* event) {
        switch (event->key()) {
            case Qt::Key_A:
            case Qt::Key_Left:
                keyLeftPressed = false;
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                keyRightPressed = false;
                break;
            case Qt::Key_Space:
            case Qt::Key_W:
            case Qt::Key_Up:
                keySpacePressed = false;
                break;
        }
    }
    
    int getScaleFactor() const { return SCALE_FACTOR; }
    
private slots:
    void updateGame() {
        handleInput();
        
        ui_factory->update_enemies(0.016f);
        
        game.move_objs_horizontally();
        game.check_horizontally_static_collisions();
        
        game.move_objs_vertically();
        game.check_mario_collision();
        game.check_vertically_static_collisions();
        
        if (!mario->is_active()) {
            handleDeath();
        }
        
        if (mario->get_y() * SCALE_FACTOR > 600) {
            if (!isInWater) {
                isInWater = true;
                waterDeathTimer = 0;
            }
            
            waterDeathTimer++;
            if (waterDeathTimer >= 1) {
                handleDeath();
            }
        } else {
            isInWater = false;
            waterDeathTimer = 0;
        }
        
        if (game.is_level_end()) {
            gameTimer->stop();
            
            biv::ThirdLevel* current_third = dynamic_cast<biv::ThirdLevel*>(game_level);
            if (current_third) {
                was_on_third_level = true;
            } else {
                was_on_third_level = false;
            }
            
            auto next_level = game_level->get_next();
            delete game_level;
            game_level = next_level;
            
            mario = ui_factory->get_mario();
            
            biv::ThirdLevel* next_third = dynamic_cast<biv::ThirdLevel*>(game_level);
            if (was_on_third_level && !next_third) {
                game.get_scores().reset();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            game.start_level();
            
            gameTimer->start();
        }
        
        if (gameWindow) {
            gameWindow->updateScore(game.get_scores().get_score());
            
            int level_num = 1;
            if (dynamic_cast<biv::ThirdLevel*>(game_level)) {
                level_num = 3;
            } else if (dynamic_cast<biv::SecondLevel*>(game_level)) {
                level_num = 2;
            }
            gameWindow->updateLevel(level_num);
        }
        
        ui_factory->refresh();
    }
    
private:
    void handleInput() {
        if (keyLeftPressed) {
            mario->move_map_right();
            if (!game.check_static_collisions(mario)) {
                game.move_map_right();
            }
            mario->move_map_left();
        }
        
        if (keyRightPressed) {
            mario->move_map_left();
            if (!game.check_static_collisions(mario)) {
                game.move_map_left();
            }
            mario->move_map_right();
        }
        
        if (keySpacePressed) {
            mario->jump();
            keySpacePressed = false;
        }
    }
    
    void handleDeath() {
        game.get_scores().reset();
        game_level->restart();
        mario = ui_factory->get_mario();
        isInWater = false;
        waterDeathTimer = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
};

class GameLauncher : public QDialog {
    Q_OBJECT
    
public:
    explicit GameLauncher(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Super Mario");
        setFixedSize(400, 200);
        setupUI();
    }
    
private slots:
    void startGame() {
        auto gameWindow = new QtGameWindow();
        gameController.startGame(gameWindow);
        
        connect(gameWindow, &QtGameWindow::keyPressed, 
                &gameController, &QtGameController::handleKeyPress);
        connect(gameWindow, &QtGameWindow::keyReleased, 
                &gameController, &QtGameController::handleKeyRelease);
        
        gameWindow->show();
        close();
    }
    
private:
    void setupUI() {
        auto layout = new QVBoxLayout(this);
        
        auto titleLabel = new QLabel("SUPER MARIO", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setFont(QFont("Arial", 20, QFont::Bold));
        titleLabel->setStyleSheet("color: #E52521;");
        layout->addWidget(titleLabel);
        
        auto startButton = new QPushButton("СТАРТ", this);
        startButton->setFont(QFont("Arial", 16, QFont::Bold));
        startButton->setMinimumHeight(50);
        startButton->setStyleSheet(
            "QPushButton {"
            "    background-color: #4CAF50;"
            "    color: white;"
            "    border: none;"
            "    border-radius: 10px;"
            "    padding: 15px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #45a049;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #3d8b40;"
            "}"
        );
        layout->addWidget(startButton);
        
        connect(startButton, &QPushButton::clicked, this, &GameLauncher::startGame);
        
        setStyleSheet(
            "QDialog {"
            "    background-color: #f0f0f0;"
            "}"
        );
    }
    
    QtGameController gameController;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    GameLauncher launcher;
    launcher.show();
    
    return app.exec();
}

#include "main.moc"