# notepad-qt

A lightweight text editor built with **C++** and **Qt Widgets**, designed for everyday text and code editing.

![C++](https://img.shields.io/badge/C%2B%2B-17-blue) ![Qt](https://img.shields.io/badge/Qt-5%2F6-green)

---

## What is this?

notepad-qt is a desktop notepad application with a clean GUI. It supports opening and saving files in multiple formats, basic text editing operations, dark mode, and live statistics — all built using the Qt Widgets framework.

---

## Features

- **File management** — New, Open, Save, Save As with support for `.txt`, `.cpp`, `.h`, `.py`, `.js`, `.cs`, `.sh`, `.bash`, `.html`
- **Editing** — Undo, Redo, Copy, Cut, Paste
- **Font selection** — change the editor font at runtime
- **Dark mode** — toggle between light and dark editor theme
- **Live counter** — word and character count shown in the status bar
- **Line highlighting** — current line is highlighted for easier navigation
- **Unsaved changes indicator** — `*` appears in the title bar when there are unsaved changes

---

## Requirements

- Qt 5.15+ or Qt 6
- C++17 or later
- qmake

---

## Build & Run

**Using Qt Creator:**
1. Open `notepad.pro` in Qt Creator
2. Click **Run** (Ctrl+R)

**Using the command line:**
```bash
qmake notepad.pro
make
./notepad
```

---

## Usage

| Action | How |
|---|---|
| New file | File → New or `Ctrl+N` |
| Open file | File → Open or `Ctrl+O` |
| Save | File → Save or `Ctrl+S` |
| Save As | File → Save As |
| Find & Replace | Edit → Find & Replace |
| Change font | Format → Font |
| Toggle dark mode | View → Dark Mode |
| Undo / Redo | Edit → Undo/Redo or `Ctrl+Z` / `Ctrl+Y` |

When you close or open a new file with unsaved changes, the app will ask whether you want to save first.

---

## Project Structure

```
notepad-qt/
├── main.cpp              # entry point
├── mainwindow.cpp        # main window logic
├── mainwindow.h          # main window header
├── mainwindow.ui         # UI layout (Qt Designer)
├── notepad.pro           # qmake project file
├── resources.qrc         # resource file (icons)
└── images/               # toolbar and menu icons
```
