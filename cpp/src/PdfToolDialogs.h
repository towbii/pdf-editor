#pragma once
#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QString>
#include <QList>

class MergeDialog : public QDialog {
public:
    explicit MergeDialog(QWidget *parent = nullptr);
    QStringList selectedPaths() const;
private:
    QListWidget *m_list = nullptr;
};

class SplitDialog : public QDialog {
public:
    explicit SplitDialog(int totalPages, QWidget *parent = nullptr);
    QString    outputPath()    const;
    QList<int> selectedPages() const; // 1-based
private:
    int        m_total      = 0;
    QLineEdit *m_rangeEdit  = nullptr;
    QLineEdit *m_outputEdit = nullptr;
};

class CompressDialog : public QDialog {
public:
    explicit CompressDialog(QWidget *parent = nullptr);
    QString outputPath()   const;
    int     imageQuality() const;
private:
    QLineEdit *m_outputEdit = nullptr;
    QSlider   *m_qualSlider = nullptr;
    QLabel    *m_qualLabel  = nullptr;
};

class WatermarkDialog : public QDialog {
public:
    explicit WatermarkDialog(QWidget *parent = nullptr);
    QString text()     const;
    int     fontSize() const;
    float   opacity()  const;
    int     angleDeg() const;
private:
    QLineEdit *m_textEdit = nullptr;
    QSpinBox  *m_sizeBox  = nullptr;
    QSlider   *m_opSlider = nullptr;
    QLabel    *m_opLabel  = nullptr;
    QSpinBox  *m_angleBox = nullptr;
};

