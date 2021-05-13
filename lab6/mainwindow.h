#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QAbstractListModel>
#include <QStringListModel>
#include <QFileDialog>

#include "doctor.hpp"
#include "patient.hpp"

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
    void on_pushButtonAddDoctor_clicked();

    void on_pushButtonAddPatient_clicked();

    void on_pushButtonCreateDoctorRelation_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_pushButtonDeleteDoctor_clicked();

    void on_pushButtonDeletePatient_clicked();

private:
    Ui::MainWindow *ui;

    // вектор, куда будем складывать сущности докторов.
    QVector<Doctor*> _qDoctors;
//    std::vector<std::unique_ptr<Doctor>> _doctors;

    // вектор, куда будем складывать сущности пациентов.
    QVector<Patient*> _qPatients;
//    std::vector<std::unique_ptr<Patient>> _patients;

    // Множество для хранения пар. Используем именно этот контейнер, т.к
    // для задуманного алгоритма построения связей, необходима сортировка по первому
    // параметру - докторам.
    // Для формирования пары отношения, используется контейнер pair
    std::set<std::pair<Doctor*, Patient*>> _doctorRelation;
    std::set<std::pair<int, int>> _doctorIndexesRelation;

    // Аналогично для пациентов, необходима сортировка по первому параметру - пациентам.
    std::set<std::pair<Patient*, Doctor*>> _patientRelation;

    // Метод для добавления связей.
    void addLink();

    void createDoctorRelation();

    void createPatientRelation();

// Методы, поля для работы с файлом.
private:
    int saveContent(const QString &path);

    int loadContent(const QString &path);
    // Название секции, в которй будем размещать список докторов.
    const std::string DOCTOR_SECTION = "[doctors]";
    // Название секции, в которй будем размещать список пациентов.
    const std::string PATIENT_SECTION = "[patients]";
    // Название секции, в которй будем размещать список связей.
    const std::string RELATIONS_SECTION = "[relations]";
};
#endif // MAINWINDOW_H
