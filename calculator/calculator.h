#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
public slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ClearButtonPressed();
    void DotButtonPressed();
};
#endif // CALCULATOR_H
