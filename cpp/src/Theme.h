#pragma once
#include <QString>

namespace Theme {

inline QString darkSheet() {
    return QStringLiteral(R"(
/* ── Global ───────────────────────────────────────── */
* { font-family: "Segoe UI", system-ui; font-size: 13px; }
QMainWindow { background: #1C1C1C; color: #E8E8E8; }
QDialog     { background: #242424; color: #E8E8E8; }
QWidget     { background: transparent; color: #E8E8E8; }

/* ── Menu Bar ─────────────────────────────────────── */
QMenuBar {
    background: #2A2A2A;
    color: #D4D4D4;
    border-bottom: 1px solid #1A1A1A;
    padding: 0 6px;
}
QMenuBar::item {
    padding: 6px 12px;
    background: transparent;
    border-radius: 4px;
    margin: 2px 1px;
}
QMenuBar::item:selected { background: #383838; color: #FFFFFF; }
QMenuBar::item:pressed  { background: #CC3232; color: #FFFFFF; }

/* ── Menus ────────────────────────────────────────── */
QMenu {
    background: #2C2C2C;
    color: #E0E0E0;
    border: 1px solid #404040;
    border-radius: 8px;
    padding: 5px;
}
QMenu::item {
    padding: 7px 28px 7px 16px;
    border-radius: 5px;
}
QMenu::item:selected { background: #CC3232; color: #FFFFFF; }
QMenu::item:disabled { color: #555555; }
QMenu::separator {
    height: 1px;
    background: #3A3A3A;
    margin: 4px 10px;
}
QMenu::indicator { width: 16px; margin-left: 4px; }

/* ── Tool Bars ────────────────────────────────────── */
QToolBar {
    background: #2A2A2A;
    border: none;
    border-bottom: 1px solid #191919;
    padding: 4px 8px;
    spacing: 2px;
}
QToolBar::separator {
    width: 1px;
    background: #3A3A3A;
    margin: 5px 6px;
}

/* ── Tool Buttons ─────────────────────────────────── */
QToolButton {
    background: transparent;
    color: #C8C8C8;
    border: none;
    border-radius: 5px;
    padding: 5px 11px;
    font-size: 13px;
    min-height: 26px;
}
QToolButton:hover   { background: #383838; color: #FFFFFF; }
QToolButton:pressed { background: #2A2A2A; color: #FFFFFF; }
QToolButton:checked {
    background: #CC3232;
    color: #FFFFFF;
    font-weight: 600;
}
QToolButton:checked:hover { background: #DD4444; }
QToolButton:disabled      { color: #4A4A4A; }

/* ── Scroll Area ──────────────────────────────────── */
QScrollArea { background: #1A1A1A; border: none; }
QAbstractScrollArea > QWidget { background: #1A1A1A; }

/* ── Scrollbars ───────────────────────────────────── */
QScrollBar:vertical {
    background: transparent;
    width: 8px;
    margin: 2px 0;
}
QScrollBar::handle:vertical {
    background: #424242;
    min-height: 28px;
    border-radius: 4px;
    margin: 0 1px;
}
QScrollBar::handle:vertical:hover   { background: #5A5A5A; }
QScrollBar::handle:vertical:pressed { background: #CC3232; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }

QScrollBar:horizontal {
    background: transparent;
    height: 8px;
    margin: 0 2px;
}
QScrollBar::handle:horizontal {
    background: #424242;
    min-width: 28px;
    border-radius: 4px;
    margin: 1px 0;
}
QScrollBar::handle:horizontal:hover   { background: #5A5A5A; }
QScrollBar::handle:horizontal:pressed { background: #CC3232; }
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }
QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal { background: transparent; }

/* ── Splitter ─────────────────────────────────────── */
QSplitter { background: #1C1C1C; }
QSplitter::handle { background: #282828; }
QSplitter::handle:horizontal { width: 1px; }
QSplitter::handle:vertical   { height: 1px; }

/* ── Status Bar ───────────────────────────────────── */
QStatusBar {
    background: #1A1A1A;
    color: #888888;
    font-size: 12px;
    border-top: 1px solid #2A2A2A;
}
QStatusBar::item { border: none; }
QStatusBar QLabel { color: #888888; padding: 0 10px; font-size: 12px; }

/* ── Slider ───────────────────────────────────────── */
QSlider::groove:horizontal {
    background: #3A3A3A;
    height: 3px;
    border-radius: 2px;
}
QSlider::handle:horizontal {
    background: #FFFFFF;
    width: 13px;
    height: 13px;
    margin: -5px 0;
    border-radius: 7px;
    border: 1.5px solid #666;
}
QSlider::handle:horizontal:hover { background: #FFAAAA; border-color: #CC3232; }
QSlider::handle:horizontal:pressed { background: #CC3232; border-color: #CC3232; }
QSlider::sub-page:horizontal { background: #CC3232; border-radius: 2px; }

/* ── Labels ───────────────────────────────────────── */
QLabel { color: #E0E0E0; background: transparent; }

/* ── Buttons ──────────────────────────────────────── */
QPushButton {
    background: #CC3232;
    color: #FFFFFF;
    border: none;
    border-radius: 6px;
    padding: 7px 20px;
    font-size: 13px;
    min-width: 80px;
}
QPushButton:hover   { background: #DD4444; }
QPushButton:pressed { background: #AA2424; }
QPushButton:default { background: #CC3232; }
QPushButton:default:hover { background: #DD4444; }
QPushButton:disabled { background: #2A2A2A; color: #4A4A4A; }

/* ── Input fields ─────────────────────────────────── */
QLineEdit {
    background: #313131;
    color: #E0E0E0;
    border: 1px solid #3C3C3C;
    border-radius: 5px;
    padding: 5px 9px;
    selection-background-color: #CC3232;
}
QLineEdit:focus { border-color: #CC3232; }

QTextEdit {
    background: #252525;
    color: #E0E0E0;
    border: 1px solid #3C3C3C;
    border-radius: 5px;
    padding: 6px;
    selection-background-color: #CC3232;
}
QTextEdit:focus { border-color: #CC3232; }

/* ── List widgets ─────────────────────────────────── */
QListWidget {
    background: #242424;
    color: #D0D0D0;
    border: 1px solid #333333;
    border-radius: 6px;
    outline: none;
    padding: 3px;
}
QListWidget::item { padding: 7px 10px; border-radius: 5px; }
QListWidget::item:hover    { background: #2E2E2E; }
QListWidget::item:selected { background: #CC3232; color: #FFFFFF; }

QTreeWidget {
    background: #242424;
    color: #D0D0D0;
    border: 1px solid #333333;
    border-radius: 4px;
    outline: none;
}
QTreeWidget::item:hover    { background: #2E2E2E; }
QTreeWidget::item:selected { background: #CC3232; color: #FFFFFF; }
QHeaderView::section {
    background: #2A2A2A;
    color: #999999;
    padding: 6px 8px;
    border: none;
    border-bottom: 1px solid #1A1A1A;
    font-size: 12px;
    font-weight: 600;
}

/* ── Combo Box ────────────────────────────────────── */
QComboBox {
    background: #313131;
    color: #E0E0E0;
    border: 1px solid #3C3C3C;
    border-radius: 5px;
    padding: 5px 9px;
}
QComboBox:hover { border-color: #CC3232; }
QComboBox::drop-down { border: none; width: 22px; }
QComboBox QAbstractItemView {
    background: #2C2C2C;
    color: #E0E0E0;
    border: 1px solid #404040;
    border-radius: 4px;
    selection-background-color: #CC3232;
    outline: none;
}

/* ── Tab Widget ───────────────────────────────────── */
QTabWidget::pane {
    background: #242424;
    border: 1px solid #333333;
    border-radius: 0 6px 6px 6px;
}
QTabBar::tab {
    background: #2A2A2A;
    color: #999999;
    border: 1px solid #333333;
    border-bottom: none;
    padding: 7px 18px;
    border-radius: 5px 5px 0 0;
    margin-right: 2px;
}
QTabBar::tab:selected { background: #242424; color: #FFFFFF; }
QTabBar::tab:hover:!selected { background: #333333; color: #CCCCCC; }

/* ── Zoom label ───────────────────────────────────── */
QLabel#zoomLabel { color: #666666; font-size: 12px; padding: 0 4px; background: transparent; }

/* ── Tool Tips ────────────────────────────────────── */
QToolTip {
    background: #2C2C2C;
    color: #E0E0E0;
    border: 1px solid #444444;
    border-radius: 5px;
    padding: 5px 10px;
    font-size: 12px;
}

/* ── KeySequenceEdit ──────────────────────────────── */
QKeySequenceEdit {
    background: #313131;
    color: #E0E0E0;
    border: 1px solid #3C3C3C;
    border-radius: 5px;
    padding: 4px 8px;
}

/* ── Checkboxes ───────────────────────────────────── */
QCheckBox { color: #E0E0E0; spacing: 8px; }
QCheckBox::indicator {
    width: 16px; height: 16px;
    background: #313131;
    border: 1px solid #505050;
    border-radius: 3px;
}
QCheckBox::indicator:checked { background: #CC3232; border-color: #CC3232; }

/* ── Message Box ──────────────────────────────────── */
QMessageBox { background: #242424; }
QMessageBox QLabel { color: #E0E0E0; }
QDialogButtonBox QPushButton { min-width: 80px; }

/* ── SpinBox ──────────────────────────────────────── */
QSpinBox, QDoubleSpinBox {
    background: #313131;
    color: #E0E0E0;
    border: 1px solid #3C3C3C;
    border-radius: 5px;
    padding: 4px 8px;
}
QSpinBox:focus, QDoubleSpinBox:focus { border-color: #CC3232; }
)");
}

inline QString lightSheet() {
    return QStringLiteral(R"(
* { font-family: "Segoe UI", system-ui; font-size: 13px; color: #1C1C1C; }
QMainWindow  { background: #F2F2F2; }
QDialog      { background: #FFFFFF; }
QWidget      { background: transparent; color: #1C1C1C; }
QAbstractScrollArea > QWidget { background: #EBEBEB; }

/* ── Menu Bar ─────────────────────────────────────── */
QMenuBar {
    background: #FAFAFA;
    color: #1C1C1C;
    border-bottom: 1px solid #E0E0E0;
    padding: 0 6px;
}
QMenuBar::item { padding: 6px 12px; border-radius: 4px; background: transparent; margin: 2px 1px; }
QMenuBar::item:selected { background: #EBEBEB; color: #1C1C1C; }
QMenuBar::item:pressed  { background: #CC3232; color: #FFFFFF; }

/* ── Menus ────────────────────────────────────────── */
QMenu {
    background: #FFFFFF;
    color: #1C1C1C;
    border: 1px solid #D8D8D8;
    border-radius: 8px;
    padding: 5px;
}
QMenu::item { padding: 7px 28px 7px 16px; border-radius: 5px; }
QMenu::item:selected { background: #CC3232; color: #FFFFFF; }
QMenu::item:disabled { color: #AAAAAA; }
QMenu::separator { height: 1px; background: #E8E8E8; margin: 4px 10px; }

/* ── Tool Bars ────────────────────────────────────── */
QToolBar {
    background: #F5F5F5;
    border: none;
    border-bottom: 1px solid #E0E0E0;
    padding: 4px 8px;
    spacing: 2px;
}
QToolBar::separator { width: 1px; background: #DDDDDD; margin: 5px 6px; }

/* ── Tool Buttons ─────────────────────────────────── */
QToolButton {
    background: transparent;
    color: #333333;
    border: none;
    border-radius: 5px;
    padding: 5px 11px;
    min-height: 26px;
}
QToolButton:hover   { background: #E8E8E8; color: #1C1C1C; }
QToolButton:pressed { background: #D8D8D8; color: #1C1C1C; }
QToolButton:checked { background: #CC3232; color: #FFFFFF; font-weight: 600; }
QToolButton:checked:hover { background: #DD4444; }
QToolButton:disabled { color: #BBBBBB; }

/* ── Scroll Area ──────────────────────────────────── */
QScrollArea { background: #EBEBEB; border: none; }

/* ── Scrollbars ───────────────────────────────────── */
QScrollBar:vertical { background: transparent; width: 8px; margin: 2px 0; }
QScrollBar::handle:vertical { background: #C0C0C0; min-height: 28px; border-radius: 4px; margin: 0 1px; }
QScrollBar::handle:vertical:hover { background: #A0A0A0; }
QScrollBar::handle:vertical:pressed { background: #CC3232; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }
QScrollBar:horizontal { background: transparent; height: 8px; margin: 0 2px; }
QScrollBar::handle:horizontal { background: #C0C0C0; min-width: 28px; border-radius: 4px; margin: 1px 0; }
QScrollBar::handle:horizontal:hover { background: #A0A0A0; }
QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }

/* ── Splitter ─────────────────────────────────────── */
QSplitter { background: #E0E0E0; }
QSplitter::handle { background: #E0E0E0; }
QSplitter::handle:horizontal { width: 1px; }
QSplitter::handle:vertical   { height: 1px; }

/* ── Status Bar ───────────────────────────────────── */
QStatusBar { background: #F0F0F0; color: #777777; font-size: 12px; border-top: 1px solid #DDDDDD; }
QStatusBar::item { border: none; }
QStatusBar QLabel { color: #777777; padding: 0 10px; font-size: 12px; }

/* ── Slider ───────────────────────────────────────── */
QSlider::groove:horizontal { background: #D8D8D8; height: 3px; border-radius: 2px; }
QSlider::handle:horizontal {
    background: #FFFFFF; width: 13px; height: 13px; margin: -5px 0;
    border-radius: 7px; border: 1.5px solid #AAAAAA;
}
QSlider::handle:horizontal:hover { background: #CC3232; border-color: #CC3232; }
QSlider::sub-page:horizontal { background: #CC3232; border-radius: 2px; }

/* ── Labels ───────────────────────────────────────── */
QLabel { color: #1C1C1C; background: transparent; }

/* ── Buttons ──────────────────────────────────────── */
QPushButton {
    background: #CC3232; color: #FFFFFF; border: none;
    border-radius: 6px; padding: 7px 20px; min-width: 80px;
}
QPushButton:hover   { background: #DD4444; }
QPushButton:pressed { background: #AA2424; }
QPushButton:default { background: #CC3232; }
QPushButton:disabled { background: #D8D8D8; color: #AAAAAA; }

/* ── Input fields ─────────────────────────────────── */
QLineEdit {
    background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC;
    border-radius: 5px; padding: 5px 9px; selection-background-color: #CC3232;
}
QLineEdit:focus { border-color: #CC3232; }

QTextEdit {
    background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC;
    border-radius: 5px; padding: 6px; selection-background-color: #CC3232;
}
QTextEdit:focus { border-color: #CC3232; }

/* ── SpinBox ──────────────────────────────────────── */
QSpinBox, QDoubleSpinBox {
    background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC;
    border-radius: 5px; padding: 4px 8px;
}
QSpinBox:focus, QDoubleSpinBox:focus { border-color: #CC3232; }

/* ── ComboBox ─────────────────────────────────────── */
QComboBox {
    background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC;
    border-radius: 5px; padding: 5px 9px;
}
QComboBox:hover { border-color: #CC3232; }
QComboBox::drop-down { border: none; width: 22px; }
QComboBox QAbstractItemView {
    background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC;
    border-radius: 4px; selection-background-color: #CC3232;
    selection-color: #FFFFFF; outline: none;
}

/* ── List / Tree widgets ──────────────────────────── */
QListWidget, QTreeWidget {
    background: #FFFFFF; color: #1C1C1C; border: 1px solid #D8D8D8;
    border-radius: 6px; outline: none; padding: 3px;
}
QListWidget::item, QTreeWidget::item { padding: 6px 10px; border-radius: 4px; color: #1C1C1C; }
QListWidget::item:hover, QTreeWidget::item:hover { background: #F0F0F0; }
QListWidget::item:selected, QTreeWidget::item:selected { background: #CC3232; color: #FFFFFF; }
QHeaderView::section {
    background: #F5F5F5; color: #555555; padding: 6px 8px; border: none;
    border-bottom: 1px solid #E0E0E0; font-size: 12px; font-weight: 600;
}

/* ── Tab Widget ───────────────────────────────────── */
QTabWidget::pane { background: #FFFFFF; border: 1px solid #D8D8D8; border-radius: 0 6px 6px 6px; }
QTabBar::tab {
    background: #ECECEC; color: #555555; border: 1px solid #D8D8D8;
    border-bottom: none; padding: 7px 18px; border-radius: 5px 5px 0 0; margin-right: 2px;
}
QTabBar::tab:selected { background: #FFFFFF; color: #1C1C1C; }
QTabBar::tab:hover:!selected { background: #E0E0E0; }

/* ── Zoom label ───────────────────────────────────── */
QLabel#zoomLabel { color: #999999; font-size: 12px; padding: 0 4px; background: transparent; }

/* ── Tool Tips ────────────────────────────────────── */
QToolTip { background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC; border-radius: 5px; padding: 5px 10px; }
QKeySequenceEdit { background: #FFFFFF; color: #1C1C1C; border: 1px solid #CCCCCC; border-radius: 5px; padding: 4px 8px; }

/* ── Checkboxes ───────────────────────────────────── */
QCheckBox { color: #1C1C1C; spacing: 8px; }
QCheckBox::indicator {
    width: 16px; height: 16px; background: #FFFFFF;
    border: 1px solid #BBBBBB; border-radius: 3px;
}
QCheckBox::indicator:checked { background: #CC3232; border-color: #CC3232; }

/* ── Message Box ──────────────────────────────────── */
QMessageBox { background: #FFFFFF; }
QMessageBox QLabel { color: #1C1C1C; }
QDialogButtonBox QPushButton { min-width: 80px; }
)");
}

} // namespace Theme
