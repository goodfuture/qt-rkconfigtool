#include "firmwareupgradedialog.h"

FirmwareUpgradeDialog::FirmwareUpgradeDialog(QWidget *parent) :
    DropShadowWidget(parent)
{
    this->setDropEnabled(true);
    this->setFixedSize(460, 320);
    this->initWidgets();
    this->translate();
    this->hide();
}

void FirmwareUpgradeDialog::initWidgets()
{
    title_icon_label = new QLabel;
    title_string_label = new QLabel;
    logo_label = new QLabel;
    specify_label = new QLabel;
    close_button = new PushButton;
    firmware_type_label = new QLabel;
    file_path_label = new QLabel;
    progress_label = new QLabel;
    prompt_label = new QLabel;
    file_path_line = new QLineEdit;
    file_select_button = new QToolButton;
    upgrade_button = new QPushButton;
    cancel_button = new QPushButton;
    progress_bar = new QProgressBar;
    combox = new QComboBox;
    stacked_layout = new QStackedLayout;
    progress_widget = new QWidget(this);
    select_widget = new QWidget(this);

    title_icon_label->setPixmap(QPixmap(QString(":/firmware_upgrade_dialog/upgrade")));
    title_icon_label->setScaledContents(true);
    title_icon_label->setFixedSize(22, 22);

    QPalette palette;
    palette.setColor(QPalette::Foreground, QColor(255, 255, 255));
    title_string_label->setPalette(palette);

    close_button->setPicName(QString(":/title_button/close"));
    this->connect(close_button, SIGNAL(clicked()), SLOT(close()));

    title_layout = new QHBoxLayout;
    title_layout->setSpacing(5);
    title_layout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    title_layout->addWidget(title_string_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setContentsMargins(5, 0, 0, 0);

    logo_label->setScaledContents(true);
    logo_label->setPixmap(QPixmap(":/icon/logo"));
    logo_label->setFixedSize(230, 230 * 88.0f / 300);

    specify_label->setAlignment(Qt::AlignTop);
    specify_label->setFixedWidth(this->width() - 80);
    specify_label->setWordWrap(true);

    file_path_line->setEnabled(false);

    progress_bar->setRange(0, 100);
    progress_bar->setValue(0);
    progress_bar->setTextVisible(true);

    QFont font = specify_label->font();
    font.setPointSize(10);
    specify_label->setFont(font);

    this->connect(cancel_button, SIGNAL(clicked()), SLOT(close()));
    this->connect(file_select_button, SIGNAL(clicked()), SLOT(onFileSelectButtonClicked()));
    this->connect(upgrade_button, SIGNAL(clicked()), SLOT(onUpgradeButtonClicked()));

    stacked_layout->addWidget(select_widget);
    stacked_layout->addWidget(progress_widget);

    QGridLayout *select_layout = new QGridLayout(select_widget);
    select_layout->addWidget(firmware_type_label, 2, 0, 1, 1, Qt::AlignLeft);
    select_layout->addWidget(combox, 2, 1, 1, 1, Qt::AlignLeft);
    select_layout->addWidget(file_path_label, 3, 0);
    select_layout->addWidget(file_path_line, 3, 1);
    select_layout->addWidget(file_select_button, 3, 2);

    QGridLayout *progress_layout = new QGridLayout(progress_widget);
    progress_layout->addWidget(prompt_label, 0, 0, 1, 2, Qt::AlignCenter);
    progress_layout->addWidget(progress_label, 1, 0);
    progress_layout->addWidget(progress_bar, 1, 1);

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addStretch();
    button_layout->addWidget(upgrade_button);
    button_layout->addWidget(cancel_button);

    center_layout = new QVBoxLayout;
    center_layout->setContentsMargins(20, 0, 20, 20);
    center_layout->addWidget(logo_label, 0, Qt::AlignCenter);
    center_layout->addSpacing(15);
    center_layout->addWidget(specify_label, 0, Qt::AlignCenter);
    center_layout->addLayout(stacked_layout);
    center_layout->addLayout(button_layout);

    main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_layout);
    main_layout->addLayout(center_layout, 1);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);
}

void FirmwareUpgradeDialog::translate()
{
    title_string_label->setText(tr("Firmware Upgrade"));
    file_path_label->setText(tr("File Path") + ":");
    firmware_type_label->setText(tr("Firmware Type") + ":");
    file_select_button->setText(tr("Select File"));
    upgrade_button->setText(tr("Upgrade"));
    cancel_button->setText(tr("Cancel"));
    progress_label->setText(tr("Progress") + ":");
    combox->addItem(tr("HMI Firmware"));
    combox->addItem(tr("Function Firmware"));
    combox->addItem(tr("DTU Tool Firmware"));
    specify_label->setText(tr("Warning:Upgrading firmware may take a few minutes,"
                              "please don't turn off the DAP's power or quit this application!"));
    prompt_label->setText(tr("Progressing, Please wait..."));
}

void FirmwareUpgradeDialog::onUpgradeButtonClicked()
{
    if (file_path_line->text().isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Please Select A File"), tr("Ok"));
        return;
    }
    stacked_layout->setCurrentWidget(progress_widget);
    close_button->setEnabled(false);
    upgrade_button->setEnabled(false);
    cancel_button->setEnabled(false);
    prompt_label->setText(tr("Progressing, Please wait..."));
    if (combox->currentIndex() == 0) {
        emit beginUpgrade(Util::HmiFirmware, file_path_line->text());
    } else if (combox->currentIndex() == 1) {
        emit beginUpgrade(Util::CoreFirmware, file_path_line->text());
    } else if (combox->currentIndex() == 2) {
        emit beginUpgrade(Util::DtuToolFirmware, file_path_line->text());
    }
}

void FirmwareUpgradeDialog::onFileSelectButtonClicked()
{
    if (combox->currentIndex() == 0) {
        file_path_line->setText(QFileDialog::getOpenFileName(this, tr("Open File"), tr("HMI Firmware") + ".bin", QString("(*.bin)")));
    } else if (combox->currentIndex() == 1) {
        file_path_line->setText(QFileDialog::getOpenFileName(this, tr("Open File"), tr("Function Firmware") + ".bin", QString("(*.bin)")));
    } else if (combox->currentIndex() == 2) {
        file_path_line->setText(QFileDialog::getOpenFileName(this, tr("Open File"), tr("Dtu Tool Firmware") + ".bin", QString("(*.bin)")));
    }
}

void FirmwareUpgradeDialog::onUpgradeProgress(int progress)
{
    if (progress >= 0) {
        progress_bar->setValue(progress);
    } else {
        progress_bar->setValue(0);
        QMessageBox::critical(this, tr("Error"), tr("Failed To Upgrade, Please Try Again!"), tr("Ok"));
    }

    if (progress >= 100) {
        prompt_label->setText(tr("Finished To Upgrade!"));
        if (QMessageBox::information(this, tr("Information"), tr("Upgrade Successful! New Firmware Will Take Effect After Reboot!") + QString("\n") + tr("Will You Reboot Now?"), tr("Yes"), tr("No")) == 0) {
            emit userRequest(Util::REQUEST_REBOOT_DEVICE);
        }
    }

    if (progress >= 100 || progress < 0) {
        stacked_layout->setCurrentWidget(select_widget);
        close_button->setEnabled(true);
        upgrade_button->setEnabled(true);
        cancel_button->setEnabled(true);
    }
}

void FirmwareUpgradeDialog::closeEvent(QCloseEvent *)
{
    combox->setCurrentIndex(0);
    file_path_line->clear();
    stacked_layout->setCurrentWidget(select_widget);
}

void FirmwareUpgradeDialog::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    QPainter painter(this);
    int height = 27;
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QPixmap(":/skin/24_big"));
    painter.drawRect(QRect(SHADOW_WIDTH, height, this->width() - 2 * SHADOW_WIDTH, this->height() - SHADOW_WIDTH - height));
}
