#include "parameterwidget.h"

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(this->parentWidget()->size());
    this->initWidgets();
    this->translate();
}

void ParameterWidget::initWidgets()
{
    this->initSysWidget();
    this->initNetWidget();

    tab_widget = new QTabWidget(this);
    tab_widget->addTab(sys_widget, QString("System Parameter"));
    tab_widget->addTab(net_widget, QString("Network Parameter"));
}

void ParameterWidget::initSysWidget()
{
    sys_widget = new QWidget();
#if 0
    QVBoxLayout *v_layout = new QVBoxLayout();

    QLabel *label = new QLabel(sys_widget);
    label->setText(tr("SIM ID"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("System ID"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("System Type"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("System Password"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Data Storage Interval"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Data Upload Manner"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Real Data Upload Enable"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Minutes Data Upload Enable"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Hours Data Upload Enable"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Days Data Upload Enable"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Switch Status Upload Enable"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    label = new QLabel(sys_widget);
    label->setText(tr("Alarm Data Upload Enable"));
    sys_label_list->append(label);
    v_layout->addWidget(label);

    sys_widget->setLayout(v_layout);
#endif
}

void ParameterWidget::initNetWidget()
{
    net_widget = new QWidget();
}

void ParameterWidget::translate()
{
}
