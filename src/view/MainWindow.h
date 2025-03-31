#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../controller/SimulationController.h"

class QAction;
class QToolBar;
class QVBoxLayout;

namespace view {
    class SimulationCanvas;
    class ToolbarWidget;

    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(controller::SimulationController* controller);
        ~MainWindow();

        private slots:
            void onSimulateClicked();
        void onClearCircuitClicked();

    private:
        void setupUi();
        void createActions();
        void createMenus();
        void createToolbars();

        controller::SimulationController* controller;
        SimulationCanvas* canvas;
        ToolbarWidget* toolbar;

        // Actions
        QAction* simulateAction;
        QAction* clearAction;
        QAction* exitAction;
    };
}

#endif //MAINWINDOW_H