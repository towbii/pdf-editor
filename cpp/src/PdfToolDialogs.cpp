#include "PdfToolDialogs.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMimeData>
#include <QUrl>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileInfo>

// MergeDialog

MergeDialog::MergeDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Merge PDFs"));
    setMinimumSize(480, 340);
    setAcceptDrops(true);

    auto *lay = new QVBoxLayout(this);
    lay->setSpacing(10);
    lay->setContentsMargins(16, 16, 16, 16);

    auto *hint = new QLabel(
        tr("Select one or more PDF files — or drag &amp; drop them here.\n"
           "Their pages will be appended to the current document."));
    hint->setWordWrap(true);
    hint->setStyleSheet("color:#888; font-size:12px;");
    lay->addWidget(hint);

    m_list = new QListWidget;
    m_list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    lay->addWidget(m_list, 1);

    auto *btnRow = new QHBoxLayout;
    auto *addBtn = new QPushButton(tr("+ Add PDF"));
    auto *remBtn = new QPushButton(tr("Remove"));
    remBtn->setStyleSheet("background:#C0392B;");
    btnRow->addWidget(addBtn);
    btnRow->addWidget(remBtn);
    btnRow->addStretch();
    lay->addLayout(btnRow);

    connect(addBtn, &QPushButton::clicked, this, [=]() {
        QStringList files = QFileDialog::getOpenFileNames(
            this, tr("Select PDF Files"), {},
            tr("PDF Files (*.pdf);;All Files (*)"));
        for (const QString &f : files) addPath(f);
    });
    connect(remBtn, &QPushButton::clicked, this, [=]() {
        qDeleteAll(m_list->selectedItems());
    });

    auto *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    bb->button(QDialogButtonBox::Ok)->setText(tr("Merge"));
    bb->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(bb, &QDialogButtonBox::accepted, this, [=]() {
        if (m_list->count() == 0) {
            QMessageBox::information(this, tr("No Files"),
                tr("Please add at least one PDF file."));
            return;
        }
        accept();
    });
    connect(bb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    lay->addWidget(bb);
}

QStringList MergeDialog::selectedPaths() const {
    QStringList out;
    for (int i = 0; i < m_list->count(); ++i)
        out << m_list->item(i)->text();
    return out;
}

void MergeDialog::addPath(const QString &path) {
    // Avoid duplicates
    for (int i = 0; i < m_list->count(); ++i)
        if (m_list->item(i)->text() == path) return;
    m_list->addItem(new QListWidgetItem(path));
}

void MergeDialog::dragEnterEvent(QDragEnterEvent *ev) {
    if (!ev->mimeData()->hasUrls()) return;
    for (const QUrl &u : ev->mimeData()->urls()) {
        if (u.toLocalFile().toLower().endsWith(".pdf")) {
            ev->acceptProposedAction();
            return;
        }
    }
}

void MergeDialog::dropEvent(QDropEvent *ev) {
    for (const QUrl &u : ev->mimeData()->urls()) {
        QString p = u.toLocalFile();
        if (p.toLower().endsWith(".pdf")) addPath(p);
    }
    ev->acceptProposedAction();
}

// SplitDialog

SplitDialog::SplitDialog(int totalPages, QWidget *parent)
    : QDialog(parent), m_total(totalPages)
{
    setWindowTitle(tr("Extract Pages"));
    setMinimumWidth(440);

    auto *lay = new QVBoxLayout(this);
    lay->setSpacing(10);
    lay->setContentsMargins(16, 16, 16, 16);

    auto *hint = new QLabel(
        tr("Specify a page range (e.g. 1, 3-5, 7) — max page: %1").arg(totalPages));
    hint->setWordWrap(true);
    hint->setStyleSheet("color:#888; font-size:12px;");
    lay->addWidget(hint);

    auto *form = new QFormLayout;
    m_rangeEdit = new QLineEdit;
    m_rangeEdit->setPlaceholderText(tr("e.g.  1-3, 5, 7-9"));
    form->addRow(tr("Pages:"), m_rangeEdit);

    m_outputEdit = new QLineEdit;
    m_outputEdit->setPlaceholderText(tr("Output file …"));
    auto *browseRow = new QHBoxLayout;
    browseRow->addWidget(m_outputEdit, 1);
    auto *browseBtn = new QPushButton("…");
    browseBtn->setFixedWidth(32);
    browseRow->addWidget(browseBtn);
    form->addRow(tr("Save as:"), browseRow);
    lay->addLayout(form);

    connect(browseBtn, &QPushButton::clicked, this, [=]() {
        QString f = QFileDialog::getSaveFileName(
            this, tr("Choose Output File"), {}, tr("PDF Files (*.pdf)"));
        if (!f.isEmpty()) m_outputEdit->setText(f);
    });

    auto *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    bb->button(QDialogButtonBox::Ok)->setText(tr("Extract"));
    bb->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(bb, &QDialogButtonBox::accepted, this, [=]() {
        if (m_rangeEdit->text().trimmed().isEmpty()) {
            QMessageBox::information(this, tr("No Range"), tr("Please enter a page range."));
            return;
        }
        if (m_outputEdit->text().trimmed().isEmpty()) {
            QMessageBox::information(this, tr("No Path"), tr("Please choose an output file."));
            return;
        }
        accept();
    });
    connect(bb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    lay->addWidget(bb);
}

QString SplitDialog::outputPath() const { return m_outputEdit->text().trimmed(); }

QList<int> SplitDialog::selectedPages() const {
    QList<int> pages;
    const QString raw = m_rangeEdit->text();
    for (const QString &part : raw.split(',', Qt::SkipEmptyParts)) {
        QString t = part.trimmed();
        if (t.contains('-')) {
            QStringList lr = t.split('-');
            if (lr.size() == 2) {
                int lo = lr[0].trimmed().toInt();
                int hi = lr[1].trimmed().toInt();
                for (int i = lo; i <= hi && i <= m_total; ++i)
                    if (i >= 1) pages.append(i);
            }
        } else {
            int p = t.toInt();
            if (p >= 1 && p <= m_total) pages.append(p);
        }
    }
    return pages;
}

// CompressDialog

CompressDialog::CompressDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Compress PDF"));
    setMinimumWidth(440);

    auto *lay = new QVBoxLayout(this);
    lay->setSpacing(10);
    lay->setContentsMargins(16, 16, 16, 16);

    auto *hint = new QLabel(
        tr("Saves a compressed copy of the PDF to a new path.\n"
           "Lower image quality = smaller file size."));
    hint->setWordWrap(true);
    hint->setStyleSheet("color:#888; font-size:12px;");
    lay->addWidget(hint);

    auto *form = new QFormLayout;

    m_outputEdit = new QLineEdit;
    m_outputEdit->setPlaceholderText(tr("Output file …"));
    auto *browseRow = new QHBoxLayout;
    browseRow->addWidget(m_outputEdit, 1);
    auto *browseBtn = new QPushButton("…");
    browseBtn->setFixedWidth(32);
    browseRow->addWidget(browseBtn);
    form->addRow(tr("Save as:"), browseRow);

    m_qualLabel  = new QLabel("60");
    m_qualSlider = new QSlider(Qt::Horizontal);
    m_qualSlider->setRange(10, 95);
    m_qualSlider->setValue(60);
    m_qualSlider->setTickPosition(QSlider::TicksBelow);
    m_qualSlider->setTickInterval(10);
    auto *qualRow = new QHBoxLayout;
    qualRow->addWidget(new QLabel(tr("Low")));
    qualRow->addWidget(m_qualSlider, 1);
    qualRow->addWidget(new QLabel(tr("High")));
    qualRow->addWidget(m_qualLabel);
    form->addRow(tr("Image Quality:"), qualRow);
    lay->addLayout(form);

    connect(browseBtn, &QPushButton::clicked, this, [=]() {
        QString f = QFileDialog::getSaveFileName(
            this, tr("Choose Output File"), {}, tr("PDF Files (*.pdf)"));
        if (!f.isEmpty()) m_outputEdit->setText(f);
    });
    connect(m_qualSlider, &QSlider::valueChanged, this, [=](int v) {
        m_qualLabel->setText(QString::number(v));
    });

    auto *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    bb->button(QDialogButtonBox::Ok)->setText(tr("Compress"));
    bb->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(bb, &QDialogButtonBox::accepted, this, [=]() {
        if (m_outputEdit->text().trimmed().isEmpty()) {
            QMessageBox::information(this, tr("No Path"), tr("Please choose an output file."));
            return;
        }
        accept();
    });
    connect(bb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    lay->addWidget(bb);
}

QString CompressDialog::outputPath()    const { return m_outputEdit->text().trimmed(); }
int     CompressDialog::imageQuality()  const { return m_qualSlider->value(); }

// WatermarkDialog

WatermarkDialog::WatermarkDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle(tr("Add Watermark"));
    setMinimumWidth(380);

    auto *lay = new QVBoxLayout(this);
    lay->setSpacing(10);
    lay->setContentsMargins(16, 16, 16, 16);

    auto *form = new QFormLayout;

    m_textEdit = new QLineEdit;
    m_textEdit->setPlaceholderText(tr("e.g.  CONFIDENTIAL"));
    form->addRow(tr("Text:"), m_textEdit);

    m_sizeBox = new QSpinBox;
    m_sizeBox->setRange(12, 120);
    m_sizeBox->setValue(48);
    form->addRow(tr("Font Size:"), m_sizeBox);

    m_opLabel  = new QLabel("15%");
    m_opSlider = new QSlider(Qt::Horizontal);
    m_opSlider->setRange(5, 60);
    m_opSlider->setValue(15);
    auto *opRow = new QHBoxLayout;
    opRow->addWidget(m_opSlider, 1);
    opRow->addWidget(m_opLabel);
    form->addRow(tr("Opacity:"), opRow);

    m_angleBox = new QSpinBox;
    m_angleBox->setRange(-90, 90);
    m_angleBox->setValue(45);
    m_angleBox->setSuffix("°");
    form->addRow(tr("Angle:"), m_angleBox);

    lay->addLayout(form);

    connect(m_opSlider, &QSlider::valueChanged, this, [=](int v) {
        m_opLabel->setText(QString::number(v) + "%");
    });

    auto *bb = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    bb->button(QDialogButtonBox::Ok)->setText(tr("Apply"));
    bb->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(bb, &QDialogButtonBox::accepted, this, [=]() {
        if (m_textEdit->text().trimmed().isEmpty()) {
            QMessageBox::information(this, tr("No Text"), tr("Please enter a watermark text."));
            return;
        }
        accept();
    });
    connect(bb, &QDialogButtonBox::rejected, this, &QDialog::reject);
    lay->addWidget(bb);
}

QString WatermarkDialog::text()     const { return m_textEdit->text().trimmed(); }
int     WatermarkDialog::fontSize() const { return m_sizeBox->value(); }
float   WatermarkDialog::opacity()  const { return m_opSlider->value() / 100.f; }
int     WatermarkDialog::angleDeg() const { return m_angleBox->value(); }
