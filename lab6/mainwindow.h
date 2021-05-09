#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "doctor.hpp"

#include <memory>

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
    void on_pushButtonAddDoctor_clicked();

    void on_pushButtonAddPatient_clicked();

private:
    Ui::MainWindow *ui;

    // Заведем вектор, куда будем складывать сущности докторов.
    std::vector<std::unique_ptr<Doctor>> doctors;
};
#endif // MAINWINDOW_H
