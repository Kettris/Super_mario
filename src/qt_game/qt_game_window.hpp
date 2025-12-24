#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFont>

class QtGameWindow : public QMainWindow {
    Q_OBJECT
    
signals:
    void keyPressed(QKeyEvent* event);
    void keyReleased(QKeyEvent* event);
    
public:
    explicit QtGameWindow(QWidget* parent = nullptr);
    ~QtGameWindow();
    
    QGraphicsScene* getScene() const { return scene; }
    void drawWater(int waterLevel);
    
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    
public slots:
    void updateScore(int score);
    void updateLevel(int level);
    
private slots:
    void restartGame();
    void exitGame();
    
private:
    void setupUI();
    
    QGraphicsScene* scene;
    QGraphicsView* view;
    QLabel* scoreLabel;
    QLabel* levelLabel;
    QTimer* gameTimer;
    
    QPushButton* restartButton;
    QPushButton* exitButton;
    
    QGraphicsRectItem* waterItem = nullptr;
};