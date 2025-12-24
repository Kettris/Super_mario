#include "qt_game_window.hpp"
#include <QCloseEvent>
#include <QGraphicsRectItem>
#include <QBrush>

QtGameWindow::QtGameWindow(QWidget* parent) 
    : QMainWindow(parent), scene(nullptr), view(nullptr), gameTimer(nullptr) {
    setWindowTitle("Super Mario - Qt Version");
    setFixedSize(1600, 900);
    setupUI();
}

QtGameWindow::~QtGameWindow() {
    if (gameTimer) {
        gameTimer->stop();
        delete gameTimer;
    }
}

void QtGameWindow::setupUI() {
    auto centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color: #87CEEB;");
    
    auto mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    auto topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(10, 10, 10, 10);
    
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setFont(QFont("Arial", 14, QFont::Bold));
    scoreLabel->setStyleSheet("color: white; background-color: #333; padding: 8px; border-radius: 5px;");
    scoreLabel->setFixedHeight(35);
    
    levelLabel = new QLabel("Level: 1", this);
    levelLabel->setFont(QFont("Arial", 14, QFont::Bold));
    levelLabel->setStyleSheet("color: white; background-color: #555; padding: 8px; border-radius: 5px;");
    levelLabel->setFixedHeight(35);
    
    restartButton = new QPushButton("Restart", this);
    restartButton->setFont(QFont("Arial", 12));
    restartButton->setFixedSize(80, 35);
    restartButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #FF9800;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #F57C00;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #EF6C00;"
        "}"
    );
    
    exitButton = new QPushButton("Exit", this);
    exitButton->setFont(QFont("Arial", 12));
    exitButton->setFixedSize(80, 35);
    exitButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #F44336;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #D32F2F;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #C62828;"
        "}"
    );
    
    topLayout->addWidget(scoreLabel);
    topLayout->addWidget(levelLabel);
    topLayout->addStretch();
    topLayout->addWidget(restartButton);
    topLayout->addWidget(exitButton);
    
    mainLayout->addLayout(topLayout);
    
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1600, 800);
    
    view = new QGraphicsView(scene);
    view->setFixedSize(1600, 800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QBrush(QColor(173, 216, 230)));
    
    mainLayout->addWidget(view);
    setCentralWidget(centralWidget);
    
    gameTimer = new QTimer(this);
    connect(restartButton, &QPushButton::clicked, this, &QtGameWindow::restartGame);
    connect(exitButton, &QPushButton::clicked, this, &QtGameWindow::exitGame);
}

void QtGameWindow::drawWater(int waterLevel) {
    if (waterItem) {
        scene->removeItem(waterItem);
        delete waterItem;
    }
    
    int waterY = waterLevel;
    int waterHeight = 800 - waterLevel;
    
    waterItem = new QGraphicsRectItem(0, waterY, 1600, waterHeight);
    waterItem->setBrush(QBrush(QColor(0, 0, 139)));
    waterItem->setPen(Qt::NoPen);
    scene->addItem(waterItem);
}

void QtGameWindow::keyPressEvent(QKeyEvent* event) {
    emit keyPressed(event);
    QMainWindow::keyPressEvent(event);
}

void QtGameWindow::keyReleaseEvent(QKeyEvent* event) {
    emit keyReleased(event);
    QMainWindow::keyReleaseEvent(event);
}

void QtGameWindow::closeEvent(QCloseEvent* event) {
    if (gameTimer) {
        gameTimer->stop();
    }
    QMainWindow::closeEvent(event);
}

void QtGameWindow::updateScore(int score) {
    scoreLabel->setText(QString("Score: %1").arg(score));
}

void QtGameWindow::updateLevel(int level) {
    levelLabel->setText(QString("Level: %1").arg(level));
}

void QtGameWindow::restartGame() {
    emit restartGame();
}

void QtGameWindow::exitGame() {
    close();
}