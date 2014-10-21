#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    DropShadowWidget(parent)
{
    mouse_pressed = false;

    //this->setWindowFlags(Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint | Qt::SubWindow | this->windowFlags());
    this->setWindowFlags(Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint | this->windowFlags());
    this->setWindowIcon(QIcon(":/icon/AppIcon"));
    this->setWindowTitle(tr("Title"));
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedSize(410, 280);

    this->initWidgets();
    this->translate();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(title, 0);
    main_layout->addLayout(stack_layout, 0);
    main_layout->addStretch();

    this->setLayout(main_layout);

    //prompt_widget->showTip(QString("Error Username Or Password"), );
}

LoginDialog::~LoginDialog()
{
    emit quit();
}

void LoginDialog::initWidgets()
{
    title = new LoginTitle(this);
    stack_layout = new QStackedLayout();
    login_widget = new LoginWidget(this);
    setting_widget = new LoginSettingWidget(this);
    loading_widget = new LoadingWidget(this);

    stack_layout->setStackingMode(QStackedLayout::StackOne);
    stack_layout->addWidget(login_widget);
    stack_layout->addWidget(setting_widget);
    stack_layout->addWidget(loading_widget);
    stack_layout->setCurrentWidget(login_widget);

    connect(title, SIGNAL(showSettingWidget()), this, SLOT(showSettingWidget()));
    connect(title, SIGNAL(showMin()), this, SLOT(showMin()));
    connect(title, SIGNAL(closeWidget()), this, SLOT(close()));

    connect(login_widget, SIGNAL(login(QString &, QString &)), this, SLOT(login(QString &, QString &)));
    connect(login_widget, SIGNAL(showMsg(Util::DispMsgId)), this, SLOT(showMsg(Util::DispMsgId)));
    connect(loading_widget, SIGNAL(cancel()), this, SLOT(abortLogin()));
    connect(loading_widget, SIGNAL(showMsg(Util::DispMsgId)), this, SLOT(showMsg(Util::DispMsgId)));

    connect(setting_widget, SIGNAL(showLogin()), this, SLOT(showLoginWidget()));
    connect(setting_widget, SIGNAL(showMsg(Util::DispMsgId)), this, SLOT(showMsg(Util::DispMsgId)));

    prompt_widget = new PromptWidget(this);
    prompt_widget->move(SHADOW_WIDTH, this->height() - prompt_widget->height() - SHADOW_WIDTH);
    prompt_widget->closeWidget();
}

void LoginDialog::translate()
{
}

void LoginDialog::showSettingWidget()
{
    title->setIconHidden(true);
    title->setTitle(tr("Login Setting"), false, true);
    title->setSettingHidden(true);
    stack_layout->setCurrentWidget(setting_widget);
}

void LoginDialog::showLoginWidget()
{
    title->setIconHidden(true);
    title->setTitle(QString(""), true);
    title->setSettingHidden(false);
    stack_layout->setCurrentWidget(login_widget);
}

void LoginDialog::showLoadingWidget()
{
    title->setIconHidden(true);
    title->setTitle(QString(""), true);
    title->setSettingHidden(true);
    stack_layout->setCurrentWidget(loading_widget);
    loading_widget->start();
}

void LoginDialog::showMin()
{
    this->showMinimized();
}

void LoginDialog::login(QString &user, QString &passwd)
{
    QStringList info;
    QString addr, port;

    for (int i = 0; i < 2; i++) {
        AppSettings settings;
        settings.beginGroup(QString(APP_PARAM_GROUP_TARGET));
        addr = settings.value(QString(APP_PARAM_ADDR), QString(DEFAULT_TARGET_ADDR)).toString();
        port = settings.value(QString(APP_PARAM_PORT), QString(DEFAULT_TARGET_PORT)).toString();
        settings.endGroup();
    }

    showLoadingWidget();

    info << user << passwd << addr << port;
    emit login(info);
}

void LoginDialog::abortLogin()
{
    loading_widget->stop();
    showLoginWidget();
}

void LoginDialog::onLoginResult(int result)
{
    if (stack_layout->currentWidget() != loading_widget) {
        return;
    }

    if (result == Util::LoginSuccessRst) {
        emit DropShadowWidget::accept();
        this->close();
    } else if (result == Util::LoginFailedRst){
        showLoginWidget();
        showMsg(Util::LoginFailedMsg);
    } else if (result == Util::ConnectFailedRst) {
        showLoginWidget();
        showMsg(Util::ConnectFailedMsg);
    } else if (result == Util::ConnectTimeOutRst) {
        showLoginWidget();
        showMsg(Util::ConnectTimeOutMsg);
    }
}

void LoginDialog::showMsg(Util::DispMsgId id)
{
    switch(id) {
    case Util::NoneMsg:
        prompt_widget->closeWidget();
        break;
    case Util::EmptyTargetAddrOrPortMsg:
        this->showWarning(tr("Target IP Address And Port Can't Be Empty"));
        break;
    case Util::EmptyUserOrPasswordMsg:
        this->showWarning(tr("User Name Or Password Is Empty"));
        break;
    case Util::LoginFailedMsg:
        this->showError(tr("Login Failed! User Name Or Password Error!"));
        break;
    case Util::ConnectFailedMsg:
        this->showError(tr("Login Failed! Can't Build Connection!"));
        break;
    case Util::ConnectTimeOutMsg:
        this->showError(tr("Connect Timeout! Try Again!"));
        break;
    default:
        break;
    }
}

void LoginDialog::showWarning(QString warning)
{
    prompt_widget->showTip(warning, QPixmap(":/icon/warning"));
}

void LoginDialog::showError(QString error)
{
    prompt_widget->showTip(error, QPixmap(":/icon/error"));
}

void LoginDialog::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QRect rect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH);
    painter.drawPixmap(rect, QPixmap(":/skin/24_big"));

    painter.setBrush(QBrush(QColor(200, 200, 200, 50), Qt::SolidPattern));
    painter.drawRect(rect);

    QRect linear_rect(SHADOW_WIDTH, title->rect().bottom(), this->width() - 2 * SHADOW_WIDTH, 1);
    QLinearGradient linear_bar(linear_rect.topLeft(), linear_rect.topRight());
    linear_bar.setColorAt(0, QColor(17, 95, 141, 255));
    linear_bar.setColorAt(1, QColor(17, 95, 141, 255));
    painter.setBrush(linear_bar);
    painter.drawRect(linear_rect);

    painter.setPen(Qt::NoPen);
    int pos_y = title->pos().y() + title->height();

    QLinearGradient linear(QPoint(SHADOW_WIDTH, pos_y), QPoint(SHADOW_WIDTH, this->height() - SHADOW_WIDTH));
    linear.setColorAt(0, QColor(255, 255, 255, 210));
    linear.setColorAt(0.5, QColor(255, 255, 255, 235));
    linear.setColorAt(1, QColor(255, 255, 255, 255));
    painter.setBrush(linear);
    painter.setBrush(QBrush(Qt::white));

    painter.drawRect(QRect(SHADOW_WIDTH, pos_y, this->width() - 2 * SHADOW_WIDTH, this->height() - pos_y - SHADOW_WIDTH));

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(QColor(17, 95, 141)));
    painter.drawRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH));
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        mouse_pressed = true;
        pressed_point = event->pos();
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *)
{
    mouse_pressed = false;
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (mouse_pressed) {
        this->move(event->globalPos() - pressed_point);
    }
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    DropShadowWidget::closeEvent(event);
}
