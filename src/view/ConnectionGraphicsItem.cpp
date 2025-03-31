#include "ConnectionGraphicsItem.h"
#include "PinGraphicsItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <cmath>

namespace view {
    ConnectionGraphicsItem::ConnectionGraphicsItem(model::Connection* connection, 
                                                PinGraphicsItem* sourcePin, 
                                                PinGraphicsItem* targetPin)
        : connection(connection), sourcePin(sourcePin), targetPin(targetPin) {
        
        setFlag(QGraphicsItem::ItemIsSelectable);
        setZValue(-1); // Ensure connections appear behind nodes
        updatePath();
    }
    
    QRectF ConnectionGraphicsItem::boundingRect() const {
        return path.boundingRect().adjusted(-5, -5, 5, 5);
    }
    
    void ConnectionGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
        painter->setRenderHint(QPainter::Antialiasing);
        
        // Set pen based on connection state
        QPen pen;
        pen.setWidth(2);
        
        // Get the logic state from the source pin
        model::LogicState state = connection->getSource()->getState();
        if (state == model::LogicState::HIGH) {
            pen.setColor(QColor(255, 50, 50)); // Red for HIGH
        } else if (state == model::LogicState::LOW) {
            pen.setColor(QColor(50, 50, 255)); // Blue for LOW
        } else {
            pen.setColor(QColor(150, 150, 150)); // Gray for UNDEFINED
        }
        
        // Highlight if selected
        if (isSelected()) {
            pen.setWidth(3);
            pen.setStyle(Qt::DashLine);
        }
        
        painter->setPen(pen);
        painter->drawPath(path);
    }
    
    model::Connection* ConnectionGraphicsItem::getConnection() const {
        return connection;
    }
    
    PinGraphicsItem* ConnectionGraphicsItem::getSourcePin() const {
        return sourcePin;
    }
    
    PinGraphicsItem* ConnectionGraphicsItem::getTargetPin() const {
        return targetPin;
    }
    
    void ConnectionGraphicsItem::updatePath() {
        // Get scene positions of pins
        QPointF sourcePos = sourcePin->scenePos();
        QPointF targetPos = targetPin->scenePos();
        
        // Create a path between the pins
        path = createConnectionPath(sourcePos, targetPos);
        
        // Update the item's path
        setPath(path);
    }
    
    void ConnectionGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsPathItem::mousePressEvent(event);
        if (event->button() == Qt::LeftButton) {
            setSelected(true);
        }
    }
    
    QPainterPath ConnectionGraphicsItem::createConnectionPath(const QPointF& start, const QPointF& end) const {
        QPainterPath path;
        path.moveTo(mapFromScene(start));
        
        // Create a bezier curve path
        qreal dx = end.x() - start.x();
        qreal dy = end.y() - start.y();
        
        // Calculate control points for a nice curve
        qreal distance = std::sqrt(dx * dx + dy * dy);
        qreal controlDistance = std::min(distance / 2, 80.0); // Cap control distance
        
        QPointF control1 = mapFromScene(start + QPointF(controlDistance, 0));
        QPointF control2 = mapFromScene(end - QPointF(controlDistance, 0));
        
        path.cubicTo(control1, control2, mapFromScene(end));
        
        return path;
    }
}