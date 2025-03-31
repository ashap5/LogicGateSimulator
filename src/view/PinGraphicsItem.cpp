#include "PinGraphicsItem.h"
#include "NodeGraphicsItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>

namespace view {
    PinGraphicsItem::PinGraphicsItem(model::Pin* pin, NodeGraphicsItem* parentNode)
        : pin(pin), parentNode(parentNode), selected(false), rect(-5, -5, 10, 10) {
        
        setFlag(QGraphicsItem::ItemIsSelectable);
        setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
        setAcceptHoverEvents(true);
    }

    QRectF PinGraphicsItem::boundingRect() const {
        return rect;
    }

    void PinGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
        painter->setRenderHint(QPainter::Antialiasing);
        
        // Set brush and pen colors based on pin state
        QColor pinColor = getPinColor();
        
        if (selected) {
            // Highlight selected pins
            painter->setBrush(QBrush(pinColor.lighter(150)));
            painter->setPen(QPen(Qt::red, 2));
        } else {
            painter->setBrush(QBrush(pinColor));
            painter->setPen(QPen(Qt::black, 1));
        }

        // Draw pin as a circle
        painter->drawEllipse(rect);
        
        // Draw a direction indicator (small line)
        QPen directionPen(Qt::black, 1);
        painter->setPen(directionPen);
        
        if (pin->getType() == model::PinType::INPUT) {
            // Draw a line from outside to the pin center for inputs
            painter->drawLine(QPointF(-8, 0), QPointF(-2, 0));
        } else {
            // Draw a line from the pin center to outside for outputs
            painter->drawLine(QPointF(2, 0), QPointF(8, 0));
        }
        
        // Optionally draw pin name
        painter->setPen(Qt::black);
        if (pin->getType() == model::PinType::INPUT) {
            painter->drawText(QPointF(-20, -7), QString::fromStdString(pin->getName()));
        } else {
            painter->drawText(QPointF(10, -7), QString::fromStdString(pin->getName()));
        }
    }

    model::Pin* PinGraphicsItem::getPin() const {
        return pin;
    }

    bool PinGraphicsItem::isSelected() const {
        return selected;
    }

    void PinGraphicsItem::setSelected(bool selected) {
        this->selected = selected;
        update();
    }

    void PinGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        if (event->button() == Qt::LeftButton && 
            (QApplication::keyboardModifiers() & Qt::ControlModifier)) {
            // Toggle selection with Ctrl+left click
            setSelected(!selected);
            emit pinClicked(this);
            event->accept();
        } else {
            // Pass to parent for normal events
            QGraphicsItem::mousePressEvent(event);
        }
    }

    QColor PinGraphicsItem::getPinColor() const {
        // Color based on logic state
        model::LogicState state = pin->getState();
        
        if (pin->getType() == model::PinType::INPUT) {
            if (state == model::LogicState::HIGH) {
                return QColor(255, 128, 0);  // Orange for HIGH
            } else if (state == model::LogicState::LOW) {
                return QColor(100, 100, 100); // Dark gray for LOW
            } else {
                return QColor(200, 200, 200); // Light gray for UNDEFINED
            }
        } else { // OUTPUT pins
            if (state == model::LogicState::HIGH) {
                return QColor(255, 50, 50);   // Red for HIGH
            } else if (state == model::LogicState::LOW) {
                return QColor(50, 50, 255);   // Blue for LOW
            } else {
                return QColor(200, 200, 200); // Light gray for UNDEFINED
            }
        }
    }
}