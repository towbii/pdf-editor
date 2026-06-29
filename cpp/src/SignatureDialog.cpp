#include "SignatureDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QTabWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDateTime>
#include <QDir>

// ── Drawing canvas (QWidget-based for reliable mouse events) ─────────────────
class DrawCanvas : public QWidget {
public:
    explicit DrawCanvas(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(400, 180);
        setCursor(Qt::CrossCursor);
        clearDrawing();
    }

    void clearDrawing() {
        m_pix = QPixmap(size());
        m_pix.fill(Qt::transparent);
        m_hasContent = false;
        update();
    }

    bool hasContent() const { return m_hasContent; }
    QPixmap canvas() const { return m_pix; }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter p(this);
        p.fillRect(rect(), Qt::white);
        p.drawPixmap(0, 0, m_pix);
        p.setPen(QPen(QColor("#555555"), 1));
        p.setBrush(Qt::NoBrush);
        p.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void mousePressEvent(QMouseEvent *ev) override {
        if (ev->button() != Qt::LeftButton) return;
        m_drawing = true;
        m_lastPt = ev->position().toPoint();
    }

    void mouseMoveEvent(QMouseEvent *ev) override {
        if (!m_drawing || !(ev->buttons() & Qt::LeftButton)) return;
        QPoint cur = ev->position().toPoint();
        QPainter p(&m_pix);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::black, 2.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        p.drawLine(m_lastPt, cur);
        m_lastPt = cur;
        m_hasContent = true;
        update();
    }

    void mouseReleaseEvent(QMouseEvent *ev) override {
        if (ev->button() == Qt::LeftButton) m_drawing = false;
    }

private:
    QPixmap m_pix;
    QPoint  m_lastPt;
    bool    m_drawing    = false;
    bool    m_hasContent = false;
};

// ── SignatureDialog ──────────────────────────────────────────────────────────

SignatureDialog::SignatureDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Signature"));
    setModal(true);
    setMinimumWidth(440);

    auto *lay = new QVBoxLayout(this);
    lay->setSpacing(10);
    lay->setContentsMargins(16, 16, 16, 16);

    auto *tabs = new QTabWidget;

    // ── Tab 1: Draw ──────────────────────────────────────────
    auto *drawPage = new QWidget;
    auto *drawLay  = new QVBoxLayout(drawPage);
    drawLay->setContentsMargins(8, 8, 8, 8);

    auto *hint = new QLabel(tr("Hold the mouse button and draw your signature:"));
    hint->setWordWrap(true);
    hint->setStyleSheet("color: #888888; font-size: 11px;");
    drawLay->addWidget(hint);
    drawLay->addSpacing(6);

    auto *canvas = new DrawCanvas;
    drawLay->addWidget(canvas, 0, Qt::AlignCenter);

    auto *clearBtn = new QPushButton(tr("Clear"));
    connect(clearBtn, &QPushButton::clicked, canvas, &DrawCanvas::clearDrawing);
    drawLay->addWidget(clearBtn, 0, Qt::AlignRight);
    tabs->addTab(drawPage, tr("Draw"));

    // ── Tab 2: Upload PNG ────────────────────────────────────
    auto *uploadPage = new QWidget;
    auto *uploadLay  = new QVBoxLayout(uploadPage);
    uploadLay->setContentsMargins(8, 8, 8, 8);
    m_preview = new QLabel(tr("No image selected"));
    m_preview->setAlignment(Qt::AlignCenter);
    m_preview->setFixedHeight(160);
    m_preview->setStyleSheet("border: 1px dashed #636366; border-radius: 6px;");
    auto *chooseBtn = new QPushButton(tr("Select PNG / JPG …"));
    connect(chooseBtn, &QPushButton::clicked, this, &SignatureDialog::choosePng);
    uploadLay->addWidget(m_preview);
    uploadLay->addWidget(chooseBtn, 0, Qt::AlignRight);
    tabs->addTab(uploadPage, tr("File"));

    lay->addWidget(tabs);

    auto *bb = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    bb->button(QDialogButtonBox::Ok)->setText(tr("Insert"));
    bb->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));

    connect(bb, &QDialogButtonBox::accepted, this, [=]() {
        if (tabs->currentIndex() == 0) {
            if (!canvas->hasContent()) {
                QMessageBox::information(this, tr("Empty Signature"),
                    tr("Please draw a signature first."));
                return;
            }
            QString tmpDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
            QDir().mkpath(tmpDir);
            QString fname = tmpDir + "/sig_" +
                QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".png";

            QPixmap px = canvas->canvas();
            QImage img = px.toImage().convertToFormat(QImage::Format_ARGB32);
            int left = img.width(), right = 0, top = img.height(), bottom = 0;
            for (int y = 0; y < img.height(); ++y)
                for (int x = 0; x < img.width(); ++x)
                    if (qAlpha(img.pixel(x, y)) > 10) {
                        left   = qMin(left,   x); right  = qMax(right,  x);
                        top    = qMin(top,    y); bottom = qMax(bottom, y);
                    }
            if (right > left && bottom > top) {
                int margin = 4;
                QImage cropped = img.copy(
                    qMax(0, left - margin), qMax(0, top - margin),
                    right - left + 2*margin, bottom - top + 2*margin);
                cropped.save(fname, "PNG");
                m_path = fname;
                accept();
            }
        } else {
            if (m_path.isEmpty()) {
                QMessageBox::information(this, tr("No File"),
                    tr("Please select an image file first."));
                return;
            }
            accept();
        }
    });
    connect(bb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    lay->addWidget(bb);
}

void SignatureDialog::choosePng() {
    QString f = QFileDialog::getOpenFileName(
        this, tr("Select Signature"), {},
        tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (f.isEmpty()) return;
    m_path = f;
    QPixmap px(f);
    if (!px.isNull())
        m_preview->setPixmap(px.scaledToWidth(360, Qt::SmoothTransformation));
}
