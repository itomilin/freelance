#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddDoctor_clicked()
{
    // Получаем значения с контролов.
    std::string specialization = ui->lineEditSpecialization->text().toStdString();
    std::string initials = ui->lineEditInitials->text().toStdString();
    size_t roomNumber = ui->spinBoxRoomNumber->value();

    // Если поля пустые, завершаем выполнение.
    if (specialization.empty() ||
        initials.empty())
    {
        return;
    }

    // Создаем новый объект
    Doctor doctor(specialization, initials, roomNumber);

    // Кладем созданный объект в вектор.
//    doctors.emplaceBack(std::make_unique<Doctor>(doctor));
    doctors.emplace_back(std::make_unique<Doctor>(doctor));
    // Заполняем контрол.
//    ui->listWidgetDoctors->addItem(QString::fromStdString(doctor.getInfo()));
    ui->listWidgetDoctors->addItems(std::);

//    qDebug() << QString::fromStdString(doctor->getInfo());
}

void MainWindow::on_pushButtonAddPatient_clicked()
{

}
