#include "SimulationCanvas.h"
#include "NodeGraphicsItem.h"
#include "PinGraphicsItem.h"
#include "ConnectionGraphicsItem.h"
#include "../controller/ConnectionManager.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

namespace view {
    SimulationCanvas::SimulationCanvas(controller::SimulationController* controller, QWidget* parent)
        : QGraphicsView(parent), controller(controller), selectedPin(nullptr), ctrlKeyPressed(false) {
        
        // Use the controller's scene instead of creating a new one
        scene = controller->getScene();
        scene->setBackgroundBrush(Qt::white);
        setScene(scene);

        setRenderHint(QPainter::Antialiasing);
        setDragMode(QGraphicsView::RubberBandDrag);
        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

        // Configure scrolling
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        // Set scene size
        setSceneRect(-5000, -5000, 10000, 10000);
    }

    SimulationCanvas::~SimulationCanvas() {
        // Don't delete the scene as it's owned by the controller
        clearScene();
    }
    
    void SimulationCanvas::addNodeItem(model::LogicGate* gate, const QPointF& pos) {
        NodeGraphicsItem* nodeItem = new NodeGraphicsItem(gate);
        nodeItem->setPos(pos);
        scene->addItem(nodeItem);
        nodeItems.push_back(nodeItem);
        
        // Connect signals from the node item
        connect(nodeItem, &NodeGraphicsItem::pinSelected, 
                controller->getConnectionManager(), &controller::ConnectionManager::onPinSelected);
    }
    
    void SimulationCanvas::removeNodeItem(NodeGraphicsItem* nodeItem) {
        auto it = std::find(nodeItems.begin(), nodeItems.end(), nodeItem);
        if (it != nodeItems.end()) {
            nodeItems.erase(it);
            scene->removeItem(nodeItem);
            delete nodeItem;
        }
    }
    
    void SimulationCanvas::addConnectionItem(model::Connection* connection) {
        NodeGraphicsItem* sourceNode = findNodeItemForGate(connection->getSource()->getParent());
        NodeGraphicsItem* targetNode = findNodeItemForGate(connection->getDestination()->getParent());
        
        if (sourceNode && targetNode) {
            PinGraphicsItem* sourcePin = sourceNode->findPinItem(connection->getSource());
            PinGraphicsItem* targetPin = targetNode->findPinItem(connection->getDestination());
            
            if (sourcePin && targetPin) {
                ConnectionGraphicsItem* connectionItem = 
                    new ConnectionGraphicsItem(connection, sourcePin, targetPin);
                scene->addItem(connectionItem);
                connectionItems.push_back(connectionItem);
            }
        }
    }
    
    void SimulationCanvas::updateConnectionItems() {
        for (auto* connectionItem : connectionItems) {
            connectionItem->updatePath();
        }
    }
    
    void SimulationCanvas::clearScene() {
        for (auto* nodeItem : nodeItems) {
            scene->removeItem(nodeItem);
            delete nodeItem;
        }
        nodeItems.clear();
        
        for (auto* connectionItem : connectionItems) {
            scene->removeItem(connectionItem);
            delete connectionItem;
        }
        connectionItems.clear();
    }
    
    void SimulationCanvas::mousePressEvent(QMouseEvent* event) {
        QGraphicsView::mousePressEvent(event);
    }
    
    void SimulationCanvas::mouseMoveEvent(QMouseEvent* event) {
        QGraphicsView::mouseMoveEvent(event);
        updateConnectionItems();
    }
    
    void SimulationCanvas::mouseReleaseEvent(QMouseEvent* event) {
        QGraphicsView::mouseReleaseEvent(event);
        
        if (event->button() == Qt::RightButton) {
            controller->getConnectionManager()->confirmConnection();
        }
    }
    
    void SimulationCanvas::keyPressEvent(QKeyEvent* event) {
        QGraphicsView::keyPressEvent(event);

        if (event->key() == Qt::Key_Control) {
            ctrlKeyPressed = true;
        }

        // Handle deletion of selected items
        if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
            QList<QGraphicsItem*> selectedItems = scene->selectedItems();

            // Process connections first
            for (auto it = selectedItems.begin(); it != selectedItems.end(); /* no increment */) {
                QGraphicsItem* item = *it;
                ConnectionGraphicsItem* connectionItem = dynamic_cast<ConnectionGraphicsItem*>(item);
                if (connectionItem) {
                    // Remove this item from our list since we're handling it
                    it = selectedItems.erase(it);
                    deleteConnection(connectionItem);
                } else {
                    ++it;
                }
            }

            // Then process nodes (only those that weren't connections)
            for (QGraphicsItem* item : selectedItems) {
                NodeGraphicsItem* nodeItem = dynamic_cast<NodeGraphicsItem*>(item);
                if (nodeItem) {
                    controller->removeGate(nodeItem);
                }
            }
        }
    }
    
    void SimulationCanvas::keyReleaseEvent(QKeyEvent* event) {
        QGraphicsView::keyReleaseEvent(event);
        
        if (event->key() == Qt::Key_Control) {
            ctrlKeyPressed = false;
        }
    }
    
    NodeGraphicsItem* SimulationCanvas::findNodeItemForGate(model::LogicGate* gate) {
        for (auto* nodeItem : nodeItems) {
            if (nodeItem->getGate() == gate) {
                return nodeItem;
            }
        }
        return nullptr;
    }
    
    PinGraphicsItem* SimulationCanvas::findPinItemAt(const QPointF& pos) {
        QGraphicsItem* item = scene->itemAt(pos, QTransform());
        if (item) {
            return dynamic_cast<PinGraphicsItem*>(item);
        }
        return nullptr;
    }
    void SimulationCanvas::deleteConnection(ConnectionGraphicsItem* connectionItem) {
        if (!connectionItem) return;

        // Get model-level connection
        model::Connection* connection = connectionItem->getConnection();
        if (!connection) return;

        // Store pin pointers before any changes
        model::Pin* sourcePin = connectionItem->getSourcePin()->getPin();
        model::Pin* destPin = connectionItem->getTargetPin()->getPin();

        // First remove from our internal list
        auto it = std::find(connectionItems.begin(), connectionItems.end(), connectionItem);
        if (it != connectionItems.end()) {
            connectionItems.erase(it);
        }

        // Remove from scene first to prevent visual artifacts
        scene->removeItem(connectionItem);

        try {
            // Perform the disconnection between pins
            if (sourcePin && destPin) {
                sourcePin->disconnect(destPin);
            }
        } catch (const std::exception& e) {
            qDebug() << "Error during pin disconnection:" << e.what();
        }

        // Finally delete the graphics item
        delete connectionItem;
    }
}