#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QPointF>
#include <unordered_map>

#include "../model/Circuit.h"
#include "../model/gates/AndGate.h"
#include "../model/gates/OrGate.h"
#include "../model/gates/NotGate.h"
#include "../model/gates/SourceNode.h"
#include "../model/gates/SinkNode.h"
#include "../view/NodeGraphicsItem.h"

namespace controller {
    class ConnectionManager;

    class SimulationController : public QObject {
        Q_OBJECT
    public:
        explicit SimulationController(QGraphicsScene* scene, QObject* parent = nullptr);
        ~SimulationController();

        QGraphicsScene* getScene() const { return scene; }

        // Circuit manipulation
        void addAndGate(const QPointF& pos);
        void addOrGate(const QPointF& pos);
        void addNotGate(const QPointF& pos);
        void addSourceNode(model::LogicState state, const QPointF& pos);
        void addSinkNode(const QPointF& pos);
        void removeGate(view::NodeGraphicsItem* nodeItem);

        // Simulation control
        void runSimulation();
        void clearCircuit();

        // Selection handling
        ConnectionManager* getConnectionManager() const;

        void simulateCircuit();

        signals:
            void simulationFinished();
        void simulationReset();

        private slots:
            void nodePositionChanged(view::NodeGraphicsItem* node);

    private:
        QGraphicsScene* scene;
        model::Circuit* circuit;
        ConnectionManager* connectionManager;
        std::unordered_map<model::LogicGate*, view::NodeGraphicsItem*> gateToNodeMap;

        // Helper methods
        void addGate(model::LogicGate* gate, const QPointF& pos);
        view::NodeGraphicsItem* createNodeGraphicsItem(model::LogicGate* gate);
        void updateOutputDisplays();
    };
}

#endif // SIMULATIONCONTROLLER_H