#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QAbstractListModel>
#include <QStringListModel>
#include <QException>

#include "doctor.hpp"
#include "patient.hpp"
#include "file_worker.hpp"

#include <memory>
#include <set>

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

    // Аналогично для пациентов, необходима сортировка по первому параметру - пациентам.
    std::set<std::pair<Patient*, Doctor*>> _patientRelation;

    FileWorker t;

    // Метод для добавления связей.
    void addLink();

    // Методы для сохранения, чтения данных.
private:
    int saveContent(const std::string &path);

    int loadContent(const std::string &path);
};
#endif // MAINWINDOW_H
