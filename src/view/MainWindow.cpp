#include "MainWindow.h"
#include "SimulationCanvas.h"
#include "ToolbarWidget.h"

#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QDockWidget>
#include <QMessageBox>
#include <QDebug>

namespace view {
    MainWindow::MainWindow(controller::SimulationController* controller)
        : QMainWindow(nullptr), controller(controller) {
        setupUi();
        createActions();
        createMenus();
        createToolbars();
    }

    MainWindow::~MainWindow() {
        // Qt handles cleanup of child widgets
    }

    void MainWindow::setupUi() {
        // Create central canvas widget
        canvas = new SimulationCanvas(controller, this);
        setCentralWidget(canvas);

        // Create dock widget for toolbar
        QDockWidget* dockWidget = new QDockWidget("Gates", this);
        dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        toolbar = new ToolbarWidget(controller, this);
        dockWidget->setWidget(toolbar);
        addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        // Connect toolbar signals to controller actions
        connect(toolbar, &ToolbarWidget::addAndGate, this, [this]() {
            qDebug() << "AND Gate button pressed";
            QPointF center = canvas->mapToScene(canvas->viewport()->rect().center());
            controller->addAndGate(center);
        });

        connect(toolbar, &ToolbarWidget::addOrGate, this, [this]() {
            qDebug() << "OR Gate button pressed";
            QPointF center = canvas->mapToScene(canvas->viewport()->rect().center());
            controller->addOrGate(center);
        });

        connect(toolbar, &ToolbarWidget::addNotGate, this, [this]() {
            qDebug() << "NOT Gate button pressed";
            QPointF center = canvas->mapToScene(canvas->viewport()->rect().center());
            controller->addNotGate(center);
        });

        connect(toolbar, &ToolbarWidget::addSourceNode, this, [this](model::LogicState state) {
            qDebug() << "Source Node button pressed - state:" << (state == model::LogicState::HIGH ? "HIGH" : "LOW");
            QPointF center = canvas->mapToScene(canvas->viewport()->rect().center());
            controller->addSourceNode(state, center);
        });

        connect(toolbar, &ToolbarWidget::addSinkNode, this, [this]() {
            qDebug() << "Sink Node button pressed";
            QPointF center = canvas->mapToScene(canvas->viewport()->rect().center());
            controller->addSinkNode(center);
        });

        connect(toolbar, &ToolbarWidget::simulate, this, [this]() {
            qDebug() << "Simulate button pressed";
            controller->simulateCircuit();
        });

        connect(toolbar, &ToolbarWidget::clearCircuit, this, [this]() {
            qDebug() << "Clear Circuit button pressed";
            controller->clearCircuit();
        });
    }

    void MainWindow::createActions() {
        simulateAction = new QAction("&Simulate", this);
        simulateAction->setShortcut(QKeySequence("F5"));
        connect(simulateAction, &QAction::triggered, this, &MainWindow::onSimulateClicked);

        clearAction = new QAction("&Clear Circuit", this);
        clearAction->setShortcut(QKeySequence("Ctrl+N"));
        connect(clearAction, &QAction::triggered, this, &MainWindow::onClearCircuitClicked);

        exitAction = new QAction("E&xit", this);
        exitAction->setShortcut(QKeySequence("Alt+F4"));
        connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    }

    void MainWindow::createMenus() {
        QMenu* fileMenu = menuBar()->addMenu("&File");
        fileMenu->addAction(clearAction);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAction);

        QMenu* simulationMenu = menuBar()->addMenu("&Simulation");
        simulationMenu->addAction(simulateAction);
    }

    void MainWindow::createToolbars() {
        QToolBar* simToolBar = addToolBar("Simulation");
        simToolBar->addAction(simulateAction);
        simToolBar->addAction(clearAction);
    }

    void MainWindow::onSimulateClicked() {
        controller->simulateCircuit();
    }

    void MainWindow::onClearCircuitClicked() {
        controller->clearCircuit();
    }
}