#include "SimulationController.h"
#include "ConnectionManager.h"
#include "../view/NodeGraphicsItem.h"
#include "../view/PinGraphicsItem.h"
#include "../view/ConnectionGraphicsItem.h"
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsView>

namespace controller {
    SimulationController::SimulationController(QGraphicsScene* scene, QObject* parent)
        : QObject(parent), scene(scene), circuit(new model::Circuit()) {
        connectionManager = new ConnectionManager(scene, this);
    }

    SimulationController::~SimulationController() {
        delete circuit;
    }

    void SimulationController::addAndGate(const QPointF& pos) {
        addGate(new model::AndGate(), pos);
    }

    void SimulationController::addOrGate(const QPointF& pos) {
        addGate(new model::OrGate(), pos);
    }

    void SimulationController::addNotGate(const QPointF& pos) {
        addGate(new model::NotGate(), pos);
    }

    void SimulationController::addSourceNode(model::LogicState state, const QPointF& pos) {
        addGate(new model::SourceNode(state), pos);
    }

    void SimulationController::addSinkNode(const QPointF& pos) {
        addGate(new model::SinkNode(), pos);
    }

    void SimulationController::addGate(model::LogicGate* gate, const QPointF& pos) {
        // Add to the model
        circuit->addGate(gate);

        qDebug() << "Gate placed in simulation:" << QString::fromStdString(gate->getType());

        // Create visual representation
        view::NodeGraphicsItem* nodeItem = createNodeGraphicsItem(gate);

        // Add visual representation to scene
        scene->addItem(nodeItem);
        nodeItem->setPos(pos);

        // Map the gate to its visual representation
        gateToNodeMap[gate] = nodeItem;

        // Connect signals
        connect(nodeItem, &view::NodeGraphicsItem::positionChanged,
                this, &SimulationController::nodePositionChanged);

        // Connect pin signals to the connection manager
        for (auto* pinItem : nodeItem->getAllPinItems()) {
            connect(pinItem, &view::PinGraphicsItem::pinClicked,
                    connectionManager, &ConnectionManager::handlePinClicked);
        }
    }

    view::NodeGraphicsItem* SimulationController::createNodeGraphicsItem(model::LogicGate* gate) {
        return new view::NodeGraphicsItem(gate);
    }

    void SimulationController::removeGate(view::NodeGraphicsItem* nodeItem) {
        if (!nodeItem) return;

        model::LogicGate* gate = nodeItem->getGate();

        // Remove from mapping
        gateToNodeMap.erase(gate);

        // Remove from scene
        scene->removeItem(nodeItem);
        delete nodeItem;

        // Remove from model
        circuit->removeGate(gate);
    }

    void SimulationController::runSimulation() {
        simulateCircuit();
    }

    void SimulationController::clearCircuit() {
        // First, safely clear the scene which removes all QGraphicsItems
        scene->clear();
        gateToNodeMap.clear();

        // Create a new empty circuit
        model::Circuit* oldCircuit = circuit;
        circuit = new model::Circuit();

        // Delete the old circuit after all references are cleared
        delete oldCircuit;

        emit simulationReset();
    }

    ConnectionManager* SimulationController::getConnectionManager() const {
        return connectionManager;
    }

    void SimulationController::simulateCircuit() {
        circuit->simulate();
        updateOutputDisplays();
    }

    void SimulationController::nodePositionChanged(view::NodeGraphicsItem* node) {
        // Update connections when node position changes
        if (connectionManager) {
            connectionManager->positionChanged(node);
        }
    }

    void SimulationController::updateOutputDisplays() {
        // Update the visual state of all nodes
        for (auto& pair : gateToNodeMap) {
            view::NodeGraphicsItem* nodeItem = pair.second;
            if (nodeItem) {
                nodeItem->updatePinVisuals();
            }
        }
    }
}