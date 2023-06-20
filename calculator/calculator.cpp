#include "calculator.h"
#include "./ui_calculator.h"
#include <QtMath>

double calcVal = 0.0;

bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool powTrigger = false;
bool emptyTrigger = true;

Calculator::Calculator(QWidget *parent) : QMainWindow(parent), ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], &QPushButton::released, this, &NumPressed);
    }

    connect(ui->Dot, &QPushButton::released, this, &DotButtonPressed);
    connect(ui->Add, &QPushButton::released, this, &MathButtonPressed);
    connect(ui->Subtract, &QPushButton::released, this, &MathButtonPressed);
    connect(ui->Multiply, &QPushButton::released, this, &MathButtonPressed);
    connect(ui->Divide, &QPushButton::released, this, &MathButtonPressed);
    connect(ui->Pow, &QPushButton::released, this, &MathButtonPressed);
    connect(ui->Equals, &QPushButton::released, this, &EqualButtonPressed);
    // !!! чем отличается запись?
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if ((displayVal.toDouble() == 0) && emptyTrigger){
        ui->Display->setText(butVal);
        emptyTrigger = false;
    } else {
        displayVal = displayVal + butVal;
        ui->Display->setText(displayVal);
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();


    QString butVal = button->text();

    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    } else if (QString::compare(butVal, "x^", Qt::CaseInsensitive) == 0) {
        powTrigger = true;
    }

    // Clear display
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger || powTrigger){
        if (addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        } else if (divTrigger) {
            solution = calcVal / dblDisplayVal;
        } else
            solution = qPow(calcVal, dblDisplayVal);
    }



    // Put solution in display
    ui->Display->setText(QString::number(solution));
}

void Calculator::ClearButtonPressed()
{
    divTrigger = \
    multTrigger = \
    addTrigger =  \
    subTrigger = false;
    emptyTrigger = true;
    calcVal = 0;
    ui->Display->setText("0");
}

void Calculator::DotButtonPressed()
{
    QString butVal = ui->Dot->text();
    QString displayVal = ui->Display->text();
    ui->Display->setText(displayVal + butVal);
}
