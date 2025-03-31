#include "ToolbarWidget.h"
#include <QIcon>
#include <QApplication>
#include <QStyle>

namespace view {
    ToolbarWidget::ToolbarWidget(controller::SimulationController* controller, QWidget* parent)
        : QWidget(parent) {
        
        setMinimumWidth(150);
        
        // Create button group to manage selection state
        buttonGroup = new QButtonGroup(this);
        buttonGroup->setExclusive(true);
        
        // Create main layout
        mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(8);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        
        // Add title
        QLabel* titleLabel = new QLabel("Logic Gate Tools", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont titleFont = titleLabel->font();
        titleFont.setBold(true);
        titleFont.setPointSize(titleFont.pointSize() + 2);
        titleLabel->setFont(titleFont);
        mainLayout->addWidget(titleLabel);
        
        mainLayout->addSpacing(10);
        
        // Create gate buttons
        QLabel* gatesLabel = new QLabel("Logic Gates", this);
        gatesLabel->setAlignment(Qt::AlignLeft);
        mainLayout->addWidget(gatesLabel);
        
        andGateButton = createToolButton("AND");
        buttonGroup->addButton(andGateButton);
        mainLayout->addWidget(andGateButton);
        
        orGateButton = createToolButton("OR");
        buttonGroup->addButton(orGateButton);
        mainLayout->addWidget(orGateButton);
        
        notGateButton = createToolButton("NOT");
        buttonGroup->addButton(notGateButton);
        mainLayout->addWidget(notGateButton);
        
        mainLayout->addSpacing(10);
        
        // Create source/sink node buttons
        QLabel* nodesLabel = new QLabel("Input/Output", this);
        nodesLabel->setAlignment(Qt::AlignLeft);
        mainLayout->addWidget(nodesLabel);
        
        source1Button = createToolButton("Logic 1");
        source1Button->setStyleSheet("QPushButton { color: #d63031; }");
        buttonGroup->addButton(source1Button);
        mainLayout->addWidget(source1Button);
        
        source0Button = createToolButton("Logic 0");
        source0Button->setStyleSheet("QPushButton { color: #0984e3; }");
        buttonGroup->addButton(source0Button);
        mainLayout->addWidget(source0Button);
        
        sinkButton = createToolButton("Output");
        buttonGroup->addButton(sinkButton);
        mainLayout->addWidget(sinkButton);
        
        mainLayout->addSpacing(10);
        
        // Create action buttons
        QLabel* actionsLabel = new QLabel("Actions", this);
        actionsLabel->setAlignment(Qt::AlignLeft);
        mainLayout->addWidget(actionsLabel);
        
        simulateButton = createToolButton("Simulate");
        simulateButton->setStyleSheet("QPushButton { background-color: #00b894; color: white; font-weight: bold; }");
        mainLayout->addWidget(simulateButton);
        
        clearButton = createToolButton("Clear Circuit");
        clearButton->setStyleSheet("QPushButton { background-color: #e17055; color: white; }");
        mainLayout->addWidget(clearButton);
        
        // Add spacer at bottom
        mainLayout->addStretch();
        
        // Connect signals
        connect(andGateButton, &QPushButton::clicked, this, &ToolbarWidget::handleButtonClick);
        connect(orGateButton, &QPushButton::clicked, this, &ToolbarWidget::handleButtonClick);
        connect(notGateButton, &QPushButton::clicked, this, &ToolbarWidget::handleButtonClick);
        connect(source1Button, &QPushButton::clicked, this, &ToolbarWidget::handleButtonClick);
        connect(source0Button, &QPushButton::clicked, this, &ToolbarWidget::handleButtonClick);
        connect(sinkButton, &QPushButton::clicked, this, &ToolbarWidget::handleButtonClick);
        connect(simulateButton, &QPushButton::clicked, this, &ToolbarWidget::simulate);
        connect(clearButton, &QPushButton::clicked, this, &ToolbarWidget::clearCircuit);
        
        setLayout(mainLayout);
    }
    
    ToolbarWidget::~ToolbarWidget() {
        // Qt's parent-child relationship handles cleanup
    }
    
    QPushButton* ToolbarWidget::createToolButton(const QString& text, const QString& iconPath) {
        QPushButton* button = new QPushButton(text, this);
        button->setMinimumHeight(30);
        
        if (!iconPath.isEmpty()) {
            button->setIcon(QIcon(iconPath));
        }
        
        button->setCheckable(true);
        return button;
    }
    
    void ToolbarWidget::handleButtonClick() {
        QObject* sender = QObject::sender();
        
        if (sender == andGateButton) {
            emit addAndGate();
        } else if (sender == orGateButton) {
            emit addOrGate();
        } else if (sender == notGateButton) {
            emit addNotGate();
        } else if (sender == source1Button) {
            emit addSourceNode(model::LogicState::HIGH);
        } else if (sender == source0Button) {
            emit addSourceNode(model::LogicState::LOW);
        } else if (sender == sinkButton) {
            emit addSinkNode();
        }
    }
}