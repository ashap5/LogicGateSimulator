#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include "../model/LogicState.h"
#include "../controller/SimulationController.h"

namespace view {
    class ToolbarWidget : public QWidget {
        Q_OBJECT

    public:
        explicit ToolbarWidget(controller::SimulationController* controller = nullptr, QWidget* parent = nullptr);
        virtual ~ToolbarWidget();

        signals:
        void addAndGate();
        void addOrGate();
        void addNotGate();
        void addSourceNode(model::LogicState state);
        void addSinkNode();
        void simulate();
        void clearCircuit();
        void addXorGate();
        void addNandGate();
        void addNorGate();

        private slots:
            void handleButtonClick();

    private:
        QPushButton* createToolButton(const QString& text, const QString& iconPath = QString());

        QVBoxLayout* mainLayout;
        QButtonGroup* buttonGroup;

        QPushButton* andGateButton;
        QPushButton* orGateButton;
        QPushButton* notGateButton;
        QPushButton* source1Button;
        QPushButton* source0Button;
        QPushButton* sinkButton;
        QPushButton* simulateButton;
        QPushButton* clearButton;
        QPushButton* xorGateButton;
        QPushButton* nandGateButton;
        QPushButton* norGateButton;
    };
}

#endif // TOOLBARWIDGET_H