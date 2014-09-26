#include "dockitemwidget.h"

DockItemWidget::DockItemWidget(QWidget *parent, QPixmap &icon, QString &tip) :
    QWidget(parent)
{
    this->setMouseTracking(true);

    jumpTimer = new QTimer(this);
    jumpTimer->setInterval(15);
    this->connect(jumpTimer, SIGNAL(timeout()), SLOT(onJumpTimerTimeout()));

    jumping = false;
    mouseIn = false;
    mousePressed = false;

    normalIcon = icon;
    mirrorIcon = createMirrorIcon(icon);

    iconMaxScaleFactor = 1.2f;
    jumpOffsetFactor = 1 / 150.0f;

    defaultIconSize.setHeight(50);
    defaultIconSize.setWidth(50);

    tipString = tip;

    resize();
    initJumping();
    initTipStringRect();
    initIconPosAndSize();
}

DockItemWidget::~DockItemWidget()
{
}

void DockItemWidget::initIconPosAndSize()
{
    normalIconRect.setSize(defaultIconSize);
    //normalIconRect.moveBottomLeft(QPoint((this->width() - defaultIconSize.width()) / 2, this->height() / 2));
    normalIconRect.moveBottomLeft(QPoint((this->width() - defaultIconSize.width()) / 2, basePoint.y()));

    mirrorIconRect.setSize(defaultIconSize);
    //mirrorIconRect.moveTopLeft(QPoint((this->width() - defaultIconSize.width()) / 2, this->height() / 2));
    mirrorIconRect.moveTopLeft(QPoint((this->width() - defaultIconSize.width()) / 2, basePoint.y()));
}

void DockItemWidget::initTipStringRect()
{
    /*
        QFont font;
        font.setFamily("Arial");
        font.setPointSize(12);
        painter.setFont(font);
        */
    QPixmap pixmap(100, 100);
    QPainter painter(&pixmap);
    tipStringRect = painter.boundingRect(0, 0, 100, 100, Qt::AlignLeft, tipString);
    tipStringRect.setSize(tipStringRect.size() + QSize(4, 4));
}

void DockItemWidget::initJumping()
{
    jumpTicks = 0;
    jumpCount = 0;
    jumpMaxCount = 3;
    jumpTicksWhenTop = 20;
    jumpOffset = 0;
}

QPixmap DockItemWidget::createMirrorIcon(QPixmap &icon)
{
    QImage image = icon.toImage().mirrored(false, true);
    QPixmap mirrorPixmap = QPixmap::fromImage(image);

    QPixmap pixmap(mirrorPixmap.size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawPixmap(0, 0, mirrorPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    //painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), QColor(0, 0, 0, int(0.3 * 255)));
    painter.end();

    return pixmap;
}

void DockItemWidget::resize()
{
    float normalIconHeightFactor = 5.0f / 6;
    float normalIconHeightFactorReverse = 1.0 / normalIconHeightFactor;

    int width = iconMaxScaleFactor * defaultIconSize.width();
    //int height = 2 * iconMaxScaleFactor * defaultIconSize.height();
    int height =  normalIconHeightFactorReverse * iconMaxScaleFactor * defaultIconSize.height();

    initJumping();
    jumpOffset = 0.5f * 9.8f * jumpTicksWhenTop * jumpTicksWhenTop;
    jumpOffset *= jumpOffsetFactor;
    height += jumpOffset;
    height *= 1.1f; //Correct Factor, Get Rid Of TipString Be Tripped;

    basePoint.setX(width / 2);
    basePoint.setY(height * normalIconHeightFactor);

    this->setFixedSize(width, height);
}

void DockItemWidget::setDefaultIconSize(QSize &iconSize)
{
    this->defaultIconSize = iconSize;
    this->resize();
}

void DockItemWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void DockItemWidget::enterEvent(QEvent *)
{
    mouseIn = true;
    this->repaint();
}

void DockItemWidget::leaveEvent(QEvent *)
{
    mousePressed = false;
    mouseIn = false;

    if (!jumping) {
        initIconPosAndSize();
    }
    this->repaint();
}

void DockItemWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (jumping) {
        return;
    }

    QPoint pos = event->pos();

    int dist = qAbs(pos.x() - basePoint.x());
    //int dist = qSqrt(qPow(pos.x() - basePoint.x(), 2) + qPow(pos.y() - normalIconRect.y() + normalIconRect.height(), 2));
    //qDebug() << dist;

#if 0
    if (dist > this->width() / 2) {
        return;
    }
#else
    if  (!normalIconRect.contains(pos)) {
        if (!jumping) {
            initIconPosAndSize();
        }
        this->repaint();
        return;
    }
#endif

    //int len = this->width() / 2;
    int len = this->width() / 2;

    iconScaleFactor = ((len - dist) * iconMaxScaleFactor + dist) / len;

    normalIconRect.setWidth(defaultIconSize.width() * iconScaleFactor);
    normalIconRect.setHeight(defaultIconSize.height() * iconScaleFactor);

    int leftPos = len - normalIconRect.width() / 2;
    normalIconRect.moveBottomLeft(QPoint(leftPos, basePoint.y()));

    dist = pos.x() - basePoint.x();
    len = this->width() - tipStringRect.width();

    int tipPosX = (this->width() - tipStringRect.width()) / 2;
    int tipPosY = normalIconRect.top() - 3;

    tipPosX = tipPosX - (dist * len / this->width());
    tipStringRect.moveBottomLeft(QPoint(tipPosX, tipPosY));

    mirrorIconRect.setWidth(normalIconRect.width());
    mirrorIconRect.setHeight(normalIconRect.height());
    mirrorIconRect.moveTopLeft(normalIconRect.bottomLeft());

    this->repaint();
}

void DockItemWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    QPoint pos = event->pos();

    if (normalIconRect.contains(pos)) {
        mousePressed = true;
    }
}

void DockItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    QPoint pos = event->pos();
    if (normalIconRect.contains(pos) && mousePressed == true) {
        mousePressed = false;
        if (!jumping) {
            initJumping();
            jumping = true;
            jumpTimer->start();
        }
    }
}

void DockItemWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(normalIconRect, normalIcon);
    painter.drawPixmap(mirrorIconRect, mirrorIcon);

    if (!jumping && mouseIn) {
        painter.setPen(QPen(QColor(255, 255, 255)));
        painter.setBrush(QBrush(QColor(68, 122, 228, 160)));
        painter.drawRoundedRect(tipStringRect, 3, 3);

        painter.setPen(QPen(QColor(255, 255, 255)));
        painter.drawText(tipStringRect, Qt::AlignCenter, tipString);
    }
    //painter.drawText(QRect(0, 0, this->width(), this->height()), QString("TEST"));
}

void DockItemWidget::onJumpTimerTimeout()
{
    if (jumpTicks == 2 * jumpTicksWhenTop) {
        jumpTicks = 0;
        jumpTicksWhenTop -= 5;
        if (++jumpCount == jumpMaxCount) {
            jumping = false;
            jumpTimer->stop();
            if (!mouseIn) {
                initIconPosAndSize();
            }
            emit clicked();
        }
    }

    if ((jumpTicks / jumpTicksWhenTop) == 0) {
        jumpOffset = 9.8f * jumpTicksWhenTop * jumpTicks - 0.5f * 9.8f * jumpTicks * jumpTicks;
    } else {
        jumpOffset = 0.5f * 9.8f * jumpTicksWhenTop * jumpTicksWhenTop;
        jumpOffset -= 0.5f * 9.8f * (jumpTicks - jumpTicksWhenTop) * (jumpTicks - jumpTicksWhenTop);
    }

    jumpOffset *= jumpOffsetFactor;

    normalIconRect.moveBottom(basePoint.y() - jumpOffset);
    mirrorIconRect.moveTop(basePoint.y() + jumpOffset);
    jumpTicks++;

    this->repaint();
}
