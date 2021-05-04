#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "tagparser.hpp"

#include <memory>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    // Поле для хранения контента прочтенного файла.
    QString _data { "" };

    // Открывающий и закрывающий теги для сравнения.
    const QString _tagTitleOpen { "<title>" };
    const QString _tagTitleClose { "</title>" };

    const QString _tagH1Open { "<h1>" };
    const QString _tagH1Close { "</h1>" };

    const QString _tagH2Open { "<h2>" };
    const QString _tagH2Close { "</h2>" };

};

#endif // MAINWINDOW_H
