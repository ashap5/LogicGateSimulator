#include "ConnectionManager.h"
#include "../view/ConnectionGraphicsItem.h"
#include <QMessageBox>

namespace controller {
    ConnectionManager::ConnectionManager(QGraphicsScene* scene, QObject* parent)
        : QObject(parent), scene(scene) {
    }

    ConnectionManager::~ConnectionManager() {
        // Qt will handle parent-child cleanup
    }

    void ConnectionManager::handlePinClicked(view::PinGraphicsItem* pin) {
        if (!pin) return;

        // Check if pin is already selected
        auto it = std::find(selectedPins.begin(), selectedPins.end(), pin);
        if (it != selectedPins.end()) {
            // Deselect the pin
            pin->setSelected(false);
            selectedPins.erase(it);
            return;
        }

        // Add the pin to selection
        selectedPins.push_back(pin);
        pin->setSelected(true);

        // If we have two pins selected, check if we can connect them
        if (selectedPins.size() == 2) {
            if (canConnect()) {
                // Valid connection, wait for right-click to confirm
            } else {
                // Invalid connection, show error and reset
                QMessageBox::warning(nullptr, "Invalid Connection",
                    "Cannot connect these pins. Please select one input and one output pin.");
                cancelSelection();
            }
        } else if (selectedPins.size() > 2) {
            // Too many pins selected, reset
            cancelSelection();
        }
    }

    void ConnectionManager::confirmConnection() {
        if (!canConnect()) return;

        // Determine which pin is source (output) and which is destination (input)
        view::PinGraphicsItem* sourcePin = nullptr;
        view::PinGraphicsItem* destPin = nullptr;

        if (selectedPins[0]->getPin()->getType() == model::PinType::OUTPUT) {
            sourcePin = selectedPins[0];
            destPin = selectedPins[1];
        } else {
            sourcePin = selectedPins[1];
            destPin = selectedPins[0];
        }

        // Create the connection in the model
        model::Pin* source = sourcePin->getPin();
        model::Pin* dest = destPin->getPin();

        if (source->connect(dest)) {
            // Find the newly created connection
            for (auto* conn : source->getConnections()) {
                if (conn->getSource() == source && conn->getDestination() == dest) {
                    // Create and add the visual representation
                    view::ConnectionGraphicsItem* connectionItem =
                        createConnectionGraphicsItem(conn, sourcePin, destPin);

                    scene->addItem(connectionItem);
                    emit connectionCreated(connectionItem);
                    break;
                }
            }
        }

        // Reset selection
        cancelSelection();
    }

    void ConnectionManager::cancelSelection() {
        for (auto* pin : selectedPins) {
            pin->setSelected(false);
        }
        selectedPins.clear();
    }

    bool ConnectionManager::hasSelection() const {
        return !selectedPins.empty();
    }

    bool ConnectionManager::canConnect() const {
        if (selectedPins.size() != 2) return false;

        model::Pin* pin1 = selectedPins[0]->getPin();
        model::Pin* pin2 = selectedPins[1]->getPin();

        // Pins must be of different types (one input, one output)
        if (pin1->getType() == pin2->getType()) return false;

        // Check model-level connection compatibility
        return pin1->canConnect(pin2);
    }

    view::ConnectionGraphicsItem* ConnectionManager::createConnectionGraphicsItem(
        model::Connection* connection,
        view::PinGraphicsItem* sourcePin,
        view::PinGraphicsItem* targetPin) {

        return new view::ConnectionGraphicsItem(connection, sourcePin, targetPin);
    }
    void ConnectionManager::onPinSelected(view::PinGraphicsItem* pin) {
        if (!pin) return;

        // If no pin is selected, select this one as the starting pin
        if (!startPin) {
            startPin = pin;
            startPin->setSelected(true);
        } else {
            // If we already have a starting pin, try to make a connection
            model::Pin* source = startPin->getPin();
            model::Pin* target = pin->getPin();

            // Try to connect pins directly using Pin's connect method
            if (source && target) {
                // Decide which is the output and which is the input
                if (source->getType() == model::PinType::OUTPUT &&
                    target->getType() == model::PinType::INPUT) {
                    source->connect(target);
                    } else if (target->getType() == model::PinType::OUTPUT &&
                              source->getType() == model::PinType::INPUT) {
                        target->connect(source);
                              }
            }

            // Clear selection state
            startPin->setSelected(false);
            startPin = nullptr;
        }
    }
    void controller::ConnectionManager::updatePinVisuals() {
        // Update visual appearance of pins
        for (auto* pin : selectedPins) {
            if (pin) {
                pin->update();
            }
        }
    }
    void controller::ConnectionManager::positionChanged(view::NodeGraphicsItem* node) {
        // Update connections when a node changes position
        if (node && scene) {
            // Find all connection items in the scene that might need updating
            for (auto* item : scene->items()) {
                auto* connectionItem = dynamic_cast<view::ConnectionGraphicsItem*>(item);
                if (connectionItem) {
                    // Update the path of the connection
                    connectionItem->updatePath();
                }
            }
            scene->update();
        }
    }
}