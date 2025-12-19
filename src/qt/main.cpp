#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QFont>

class StartDialog : public QDialog {
    Q_OBJECT
public:
    explicit StartDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Super Mario Launcher");
        setFixedSize(400, 200);
        
        auto layout = new QVBoxLayout(this);
        
        auto label = new QLabel("Нажмите кнопку для начала игры", this);
        label->setAlignment(Qt::AlignCenter);
        label->setFont(QFont("Arial", 14));
        layout->addWidget(label);
        
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
        
        connect(startButton, &QPushButton::clicked, this, &StartDialog::accept);
        
        setStyleSheet(
            "QDialog {"
            "    background-color: #f5f5f5;"
            "}"
        );
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    StartDialog startDialog;
    if (startDialog.exec() != QDialog::Accepted) {
        return 0;
    }
    
    system("build_ninja\\super_mario.exe");
    
    return 0;
}

#include "main.moc"