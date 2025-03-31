#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "view/MainWindow.h"
#include <QFile>
#include <QGraphicsScene>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set application information
    app.setApplicationName("Logic Gate Simulator");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("LogicSim");

    // Create a scene for the controller
    QGraphicsScene* scene = new QGraphicsScene();
    controller::SimulationController* controller = new controller::SimulationController(scene);

    // Optional: Show splash screen
    QSplashScreen splash(QPixmap(":/resources/splash.png"));
    splash.show();

    // Create and show main window after a brief delay
    view::MainWindow mainWindow(controller);
    QTimer::singleShot(1500, &splash, &QSplashScreen::close);
    QTimer::singleShot(1500, &mainWindow, &view::MainWindow::show);
    
    // Load stylesheet if needed
    QFile styleFile(":/resources/styles.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        app.setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
    
    mainWindow.setWindowTitle("Logic Gate Simulator");
    mainWindow.setMinimumSize(1024, 768);

    return app.exec();
}