#ifndef SIMULATIONCANVAS_H
#define SIMULATIONCANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "../controller/SimulationController.h"

namespace view {
    class NodeGraphicsItem;
    class PinGraphicsItem;
    class ConnectionGraphicsItem;
    
    class SimulationCanvas : public QGraphicsView {
        Q_OBJECT
        
    public:
        SimulationCanvas(controller::SimulationController* controller, QWidget* parent = nullptr);
        ~SimulationCanvas();
        
        void addNodeItem(model::LogicGate* gate, const QPointF& pos);
        void removeNodeItem(NodeGraphicsItem* nodeItem);
        void addConnectionItem(model::Connection* connection);
        void updateConnectionItems();
        void clearScene();
        
    protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        
    private:
        QGraphicsScene* scene;
        controller::SimulationController* controller;
        
        // Track items on scene
        std::vector<NodeGraphicsItem*> nodeItems;
        std::vector<ConnectionGraphicsItem*> connectionItems;
        
        // Selection state
        PinGraphicsItem* selectedPin;
        bool ctrlKeyPressed;
        
        // Internal methods
        NodeGraphicsItem* findNodeItemForGate(model::LogicGate* gate);
        PinGraphicsItem* findPinItemAt(const QPointF& pos);
        void tryConnectPins(PinGraphicsItem* source, PinGraphicsItem* target);
        void deleteConnection(ConnectionGraphicsItem* connectionItem);
    };
}

#endif //SIMULATIONCANVAS_H