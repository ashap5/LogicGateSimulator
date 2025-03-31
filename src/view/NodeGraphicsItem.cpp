#include "NodeGraphicsItem.h"
#include "PinGraphicsItem.h"
#include "../model/gates/SourceNode.h"
#include "../model/gates/SinkNode.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

namespace view {
    NodeGraphicsItem::NodeGraphicsItem(model::LogicGate* gate)
        : gate(gate), rect(-50, -30, 100, 60) {
        
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        
        createPinItems();
    }
    
    NodeGraphicsItem::~NodeGraphicsItem() {
        // The scene will delete pin items when removed
    }
    
    QRectF NodeGraphicsItem::boundingRect() const {
        // Add some margin to the rectangle
        return rect.adjusted(-5, -5, 5, 5);
    }
    
    void NodeGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
        // Draw gate body
        painter->setRenderHint(QPainter::Antialiasing);

        // Fill with gate-specific color
        QColor fillColor = getGateColor();
        if (isSelected()) {
            fillColor = fillColor.lighter(120);
        }

        painter->setBrush(fillColor);
        painter->setPen(QPen(Qt::black, 2));

        painter->drawRect(rect);

        // Determine display text based on gate type
        QString displayText;

        // Special case for sink nodes
        if (gate->getType() == "SINK") {
            auto* sinkNode = dynamic_cast<model::SinkNode*>(gate);
            if (sinkNode) {
                model::LogicState state = sinkNode->getState();
                if (state == model::LogicState::HIGH) {
                    displayText = "Sink 1";
                } else if (state == model::LogicState::LOW) {
                    displayText = "Sink 0";
                } else {
                    displayText = "Sink:";
                }
            }
        }
        // General case for other gates
        else {
            displayText = QString::fromStdString(gate->getType());
        }

        painter->setPen(Qt::black);
        painter->drawText(rect, Qt::AlignCenter, displayText);

        // Update pin positions
        updatePinPositions();
    }
    
    void NodeGraphicsItem::createPinItems() {
        // Create input pin items
        for (model::Pin* pin : gate->getInputPins()) {
            PinGraphicsItem* pinItem = new PinGraphicsItem(pin, this);
            inputPinItems.push_back(pinItem);
            pinItem->setParentItem(this);
        }
        
        // Create output pin items
        for (model::Pin* pin : gate->getOutputPins()) {
            PinGraphicsItem* pinItem = new PinGraphicsItem(pin, this);
            outputPinItems.push_back(pinItem);
            pinItem->setParentItem(this);
        }
        
        updatePinPositions();
    }
    
    void NodeGraphicsItem::updatePinPositions() {
        const float leftEdge = rect.left();
        const float rightEdge = rect.right();
        const float topEdge = rect.top();
        const float height = rect.height();
        
        // Position input pins on the left side
        const int inputCount = static_cast<int>(inputPinItems.size());
        const float inputSpacing = height / (inputCount + 1);
        for (int i = 0; i < inputCount; ++i) {
            inputPinItems[i]->setPos(leftEdge, topEdge + ((i + 1) * inputSpacing));
        }
        
        // Position output pins on the right side
        const int outputCount = static_cast<int>(outputPinItems.size());
        const float outputSpacing = height / (outputCount + 1);
        for (int i = 0; i < outputCount; ++i) {
            outputPinItems[i]->setPos(rightEdge, topEdge + ((i + 1) * outputSpacing));
        }
    }
    
    QColor NodeGraphicsItem::getGateColor() const {
        std::string type = gate->getType();
        
        if (type == "AND") return QColor(173, 216, 230);  // Light blue
        if (type == "OR") return QColor(144, 238, 144);   // Light green
        if (type == "NOT") return QColor(255, 182, 193);  // Light pink
        if (type == "SOURCE") {
            model::SourceNode* source = dynamic_cast<model::SourceNode*>(gate);
            if (source && source->getState() == model::LogicState::HIGH) {
                return QColor(255, 165, 0);  // Orange for logic 1
            }
            return QColor(100, 100, 100);    // Gray for logic 0
        }
        if (type == "SINK") return QColor(255, 255, 150); // Light yellow
        
        return QColor(200, 200, 200); // Default gray
    }
    
    PinGraphicsItem* NodeGraphicsItem::findPinItem(model::Pin* pin) {
        // Check input pins
        for (auto* pinItem : inputPinItems) {
            if (pinItem->getPin() == pin) {
                return pinItem;
            }
        }
        
        // Check output pins
        for (auto* pinItem : outputPinItems) {
            if (pinItem->getPin() == pin) {
                return pinItem;
            }
        }
        
        return nullptr;
    }
    
    model::LogicGate* NodeGraphicsItem::getGate() const {
        return gate;
    }
    
    void NodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsItem::mousePressEvent(event);
    }
    
    void NodeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsItem::mouseMoveEvent(event);
        
        // Update positions of connected wires
        update();
        scene()->update();
    }
    
    void NodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsItem::mouseReleaseEvent(event);
    }
    std::vector<PinGraphicsItem*> NodeGraphicsItem::getAllPinItems() const {
        std::vector<PinGraphicsItem*> allPins;
        allPins.insert(allPins.end(), inputPinItems.begin(), inputPinItems.end());
        allPins.insert(allPins.end(), outputPinItems.begin(), outputPinItems.end());
        return allPins;
    }

    void NodeGraphicsItem::updateDisplayText(const QString& text) {
        // Update any text display (can be implemented based on your needs)
        update();
    }

    void NodeGraphicsItem::updatePinVisuals() {
        // Update pin visuals when needed
        for (auto* pin : inputPinItems) {
            pin->update();
        }
        for (auto* pin : outputPinItems) {
            pin->update();
        }
    }
    QVariant NodeGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
        if (change == ItemPositionChange || change == ItemPositionHasChanged) {
            // Emit signal when position changes
            emit positionChanged(this);

            // Update all connections attached to this node
            updatePinPositions();
        }

        return QGraphicsItem::itemChange(change, value);
    }
}