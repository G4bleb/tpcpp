#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QTextEdit>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QKeySequence>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();
private:
  QPushButton * bouton1;
  QPushButton * bouton2;
  QTextEdit * textedit;
  QAction * action_addtext;
  QMenu *fileMenu;
public slots:
  void slot_bouton1();
  void slot_bouton2();
  void slot_addtext();
};

#endif // MAINWINDOW_H
