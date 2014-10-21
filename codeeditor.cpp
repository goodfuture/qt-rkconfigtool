#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) :
    QComboBox(parent)
{
    nameList << tr("Oxygen Content") << tr("Gas Velocity") << tr("Gas Temperature")
             << tr("Gas Dynamic Pressure") << tr("Gas Humidity")
             << tr("Cryogenic Temperature") << tr("Flue Sectional Area")
             << tr("Gas Pressure") << tr("Exhaust Gas Velocity") << tr("Smoke Dust Content")
             << tr("Sulfur Dioxide Content") << tr("Nitrogen Oxide Content")
             << tr("Carbonic Oxide Content") << tr("Carbon Disulfide") << tr("Sewage Rate")
             << tr("PH Value") << tr("Chemical Oxygen Demand") << tr("Ammonia Nitrogen Content")
             << tr("Total Phosphorus Content") << tr("Total Displacement");

    codeList << "S01" << "S02" << "S03" << "S04" << "S05"
             << "S06" << "S07" << "S08" << "B02" << "01"
             << "02" << "03" << "04" << "12" << "B01" << "001"
             << "011" << "060" << "101" << "Pfk";

    lineEdit = new QLineEdit(this);
    this->setLineEdit(lineEdit);
    this->setMaxVisibleItems(5);
    this->clear();
    this->addItems(nameList);
}

void CodeEditor::onClicked()
{
    this->showPopup();
    qDebug() << "Clicked";
}

void CodeEditor::setText(QString text)
{
    lineEdit->setText(text);
}

QString CodeEditor::text()
{
    if (nameList.contains(lineEdit->text())) {
        return codeList.at(nameList.indexOf(lineEdit->text()));
    }

    return lineEdit->text();
}

void CodeEditor::paintEvent(QPaintEvent *event)
{
    QComboBox::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    QRect rect(this->rect().topRight() - QPoint(20, 0), this->rect().bottomRight());
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(rect, QPixmap(":/code_editor/list_down"));

    QLinearGradient linear(rect.topLeft(), rect.bottomLeft());
    linear.setColorAt(0, QColor(255, 255, 255, 200));
    linear.setColorAt(0.5, QColor(0, 0, 0, 200));
    linear.setColorAt(1, QColor(255, 255, 255, 200));

    painter.setBrush(QBrush(linear));
    painter.drawRect(QRect(rect.x(), rect.y() + 3, 1, rect.height() - 6));
}
