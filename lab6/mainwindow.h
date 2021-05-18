#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QAbstractListModel>
#include <QStringListModel>
#include <QFileDialog>

#include "department.hpp"
#include "medicines.hpp"

#include <memory>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

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

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_pushButtonDeleteDepartment_clicked();

    void on_pushButtonAddDepartment_clicked();

    void on_pushButtonDeleteMedication_clicked();

    void on_pushButtonAddMedication_clicked();

    void on_actioncreate_triggered();

private:
    Ui::MainWindow *ui;

    // вектор, куда будем складывать сущности докторов.
    QVector<Department*> _qDepartments;
//    std::vector<std::unique_ptr<Doctor>> _doctors;

    // вектор, куда будем складывать сущности пациентов.
    QVector<Medicines*> _qMedicines;
//    std::vector<std::unique_ptr<Patient>> _patients;

    // Множество для хранения пар. Используем именно этот контейнер, т.к
    // для задуманного алгоритма построения связей, необходима сортировка по первому
    // параметру - докторам.
    // Для формирования пары отношения, используется контейнер pair
    std::set<std::pair<Department*, Medicines*>> _departmentRelation;
    std::set<std::pair<int, int>> _departmentIndexesRelation;

    // Аналогично для пациентов, необходима сортировка по первому параметру - пациентам.
    std::set<std::pair<Medicines*, Department*>> _medicinesRelation;

    // Метод для добавления связей.
    void addLink();

    void createDepartmentRelation();

    void createMedicinesRelation();

// Методы, поля для работы с файлом.
private:
    int saveContent(const QString &path);

    int loadContent(const QString &path);
    // Название секции, в которй будем размещать список докторов.
    const std::string DEPARTMENT_SECTION = "[department]";
    // Название секции, в которй будем размещать список пациентов.
    const std::string MEDICINES_SECTION = "[medicines]";
    // Название секции, в которй будем размещать список связей.
    const std::string RELATIONS_SECTION = "[relations]";
};
#endif // MAINWINDOW_H
