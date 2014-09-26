#include "titlewidget.h"

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent)
{
    this->initWidgets();

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_icon, 0, Qt::AlignTop);
    title_layout->addSpacing(3);
    title_layout->addWidget(title_version, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(menu_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(0, 0, 0, 0);

    QStringList string_list;
    string_list << ":/tool_button/main"
                << ":/tool_button/setting"
                << ":/tool_button/real_data"
                << ":/tool_button/history"
                << ":/tool_button/export";

    QHBoxLayout *tool_button_layout = new QHBoxLayout();

    signal_mapper = new QSignalMapper(this);
    for (int i = 0; i < string_list.size(); i++) {
        ToolButton *tool_button = new ToolButton(string_list.at(i), this);
        tool_button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        //signal_mapper->setMapping(tool_button, QString::number(i, 10));
        signal_mapper->setMapping(tool_button, i);
        tool_button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }
    //connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));
    connect(signal_mapper, SIGNAL(mapped(int)), this, SLOT(selectPage(int)));

    logo_label = new LogoLabel(this);
    //logo_label->setPixmap(QPixmap(":/icon/logo"));
    //logo_label->setScaledContents(true);
    //logo_label->setFixedSize(200, 58);
    logo_label->setFixedSize(220, 76);
    tool_button_layout->addWidget(logo_label, 1, Qt::AlignVCenter);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(tool_button_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);
    setFixedHeight(110);

    selectPage(0);
    this->translate();
}

TitleWidget::~TitleWidget()
{
}

void TitleWidget::initWidgets()
{
    mousePressed = false;

    /*
    QFont &font = const_cast<QFont &>(this->font());
    font.setBold(true);
    */

    title_icon = new QLabel(this);
    title_version = new QLabel(this);
    menu_button = new PushButton(this);
    min_button = new PushButton(this);
    close_button = new PushButton(this);

    connect(menu_button, SIGNAL(clicked()), this, SIGNAL(showMenu()));
    connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeMainWindow()));

    title_icon->setPixmap(QPixmap(":/icon/AppIcon"));
    title_icon->setScaledContents(true);
    title_icon->setFixedSize(25, 25);
    title_version->setStyleSheet(QString("font:bold;color:white"));
    menu_button->setPicName(QString(":/title_button/menu"));
    min_button->setPicName(QString(":/title_button/min"));
    close_button->setPicName(QString(":/title_button/close"));
}

void TitleWidget::showEvent(QShowEvent *)
{
    //qDebug("title show");
    //setMouseTracking(true);
}

void TitleWidget::translate()
{
#ifdef PROGRAM_BETA_VERSION
    title_version->setText(tr("DAA Tool Box") + QString(PROGRAM_VERSION_NUM).left(3) + QString(" ") + tr("Beta Version"));
#else
    title_version->setText(tr("DAA Tool Box") + QString(PROGRAM_VERSION_NUM).left(3) + QString(" ") + tr("Release Version"));
#endif
    menu_button->setToolTip(tr("Menu"));
    min_button->setToolTip(tr("Minimize"));
    close_button->setToolTip(tr("Close"));
    tool_button_list.at(0)->setText(tr("Main Page"));
    tool_button_list.at(1)->setText(tr("Parameter Setting"));
    tool_button_list.at(2)->setText(tr("Real Data"));
    tool_button_list.at(3)->setText(tr("History Data"));
    tool_button_list.at(4)->setText(tr("Data Export"));
}

void TitleWidget::selectPage(int index)
{

    for (int i = 0; i < tool_button_list.count(); i++) {
        ToolButton *tool_button = tool_button_list.at(i);
        if (index == i) {
            tool_button->setMousePressed(true);
        } else {
            tool_button->setMousePressed(false);
        }
    }

    emit turnPage(index);
}

void TitleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = event->globalPos() - this->parentWidget()->pos();
    }
}

void TitleWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void TitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed) {
        this->parentWidget()->move(event->globalPos() - mousePoint);
        //this->parentWidget()->move(currentPoint);
    }
}
