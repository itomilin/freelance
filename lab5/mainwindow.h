#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QtCore>
#include <QDir>
#include <QMessageBox>

#include "windows_attrs.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QString selectedPath;
    QMessageBox msgBox;

    void parseDir(const QString &path);

    WindowsAttrs *attrs;
};
#endif // MAINWINDOW_H
