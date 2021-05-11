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

// Обработчик кнопки добавления доктора.
void MainWindow::on_pushButtonAddDoctor_clicked()
{
    // Получаем значения с контролов.
    std::string specialization = ui->lineEditSpecialization->text().toStdString();
    std::string initials = ui->lineEditInitialsDoctor->text().toStdString();
    size_t roomNumber = ui->spinBoxRoomNumber->value();

    // Если поля пустые, тогда не выполняем код ниже.
    if (specialization.empty() ||
        initials.empty())
    {
        return;
    }

    // Создаем новый объект
//    Doctor doctor(specialization, initials, roomNumber);
    Doctor *doctor = new Doctor(specialization, initials, roomNumber);

    // Кладем созданный объект в вектор.
//    _doctors.emplace_back(std::make_unique<Doctor>(doctor));
    _qDoctors.emplaceBack(doctor);

    QStringList *lines = new QStringList();
    QStringListModel *model = new QStringListModel(*lines, nullptr);
    // Заполняем контрол.
    for(auto const &doctor : _qDoctors)
    {
        lines->append(QString::fromStdString(doctor->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewDoctors->setModel(model);
}

// Обработчик кнопки добавления пациентов.
void MainWindow::on_pushButtonAddPatient_clicked()
{
    // Получаем значения с контролов.
    std::string gender = ui->lineEditGender->text().toStdString();
    std::string initials = ui->lineEditInitialsPatient->text().toStdString();
    size_t age = ui->spinBoxAge->value();

    // Если поля пустые, завершаем выполнение.
    if (gender.empty() ||
        initials.empty())
    {
        return;
    }

    // Создаем новый объект
    Patient *patient = new Patient(gender, initials, age);

    // Кладем созданный объект в вектор.
    _qPatients.emplaceBack(patient);

    QStringList *lines = new QStringList();
    QStringListModel *model = new QStringListModel(*lines, nullptr);

    // Заполняем контрол.
    for(auto const &patient : _qPatients)
    {
        lines->append(QString::fromStdString(patient->getInfo()));
//        ui->listWidgetPatients->addItem(QString::fromStdString(patient->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewPatients->setModel(model);
}

void MainWindow::addLink()
{
    // Проверяем на наличие модели если указатеь на nullptr, значит список пуст.
    auto model = ui->listViewPatients->selectionModel();
    auto modelDoctors = ui->listViewDoctors->selectionModel();
    if (model == nullptr || modelDoctors == nullptr)
    {
        qDebug() << "[ ERROR ] tree view is empty!";
        return;
    }

    auto selectedPatientsIndexes = model->selectedIndexes();
    auto selectedDoctorIndex = modelDoctors->selectedIndexes();
    // Проверяем выбраны ли элементы из списков.
    if (selectedPatientsIndexes.empty() || selectedDoctorIndex.empty())
    {
        return;
    }
    // Обязательно очистить дерево связей.
    ui->treeWidgetDoctors->clear();
    ui->treeWidgetPatients->clear();

    // Выбранный доктор из первого списка.
    auto doc = _qDoctors.at(selectedDoctorIndex.first().row());

    // Если не пуст, то перебираем строки которые были выбраны.
    for(auto const &item : selectedPatientsIndexes)
    {
        auto patient = _qPatients.at(item.row());
        _doctorRelation.insert(std::make_pair(doc, patient));
        qDebug() << item.row();
    }

    // -------------------------------------------------------------------------
    // Создаем дерево отношений для докторов.

    // Создаем базовый topLevelItem для построения дерева отношений.
    QTreeWidgetItem *doctor = new QTreeWidgetItem(ui->treeWidgetDoctors);

    // Присвоим на предыдущий элемент начало контейнера set через итератор.
    Doctor *prevD = _doctorRelation.begin()->first;

    // Перебираем все связи  доктор -> пациенты
    for(auto const &relation : _doctorRelation)
    {
        // Записываем следующее в списке имя доктора и пациента.
        // Извлекаем значения из контейнера pair first - доктор, second - пациент
        auto d = relation.first;
        auto p = relation.second;

        // Для будущего формирования дерева, заполняем список.
        // Формируем множество для отношения пациент -> доктора
        _patientRelation.insert(std::make_pair(p, d));

        // Когда сменяется доктор, то создаем новый topLevelItem
        // Для этого проверяем на равенство предыдущий и текущий элемент списка
        if (d != prevD)
        {
            doctor = new QTreeWidgetItem(ui->treeWidgetDoctors);
        }
        // добавляем в topLevelItem информацию о докторе
        doctor->setText(0, d->getInfo().c_str());
        ui->treeWidgetDoctors->addTopLevelItem(doctor);

        // Создаем объект child для пациента и добавляем его в topLevelItem
        // таким образом формируется дерево отношений
        QTreeWidgetItem *patient = new QTreeWidgetItem();
        // В первую колонку вставляем пустую строку.
        patient->setText(0, {});
        // Во вторую информацию о пациете.
        patient->setText(1, p->getInfo().c_str());
        // Привязываем пациента к доктору.
        doctor->addChild(patient);

        prevD = d;
    }

    // -------------------------------------------------------------------------
    // Создаем обратное дерево отношений для пациентов.

    // Создаем базовый topLevelItem
    QTreeWidgetItem *patient = new QTreeWidgetItem(ui->treeWidgetPatients);

    // Присвоим на предыдущий элемент начало контейнера set через итератор.
    Patient *prevP = _doctorRelation.begin()->second;

    // Перебираем все связи  доктор -> пациенты
    for(auto const &relation : _patientRelation)
    {
        // Записываем следующее в списке имя доктора и пациента.
        auto p = relation.first;
        auto d = relation.second;

        // Когда сменяется доктор, то создаем новый topLevelItem
        // Для этого проверяем на равенство предыдущий и текущий элемент списка
        if (p != prevP)
        {
            patient = new QTreeWidgetItem(ui->treeWidgetPatients);
        }
        // добавляем в topLevelItem информацию о пациенте.
        patient->setText(0, p->getInfo().c_str());
        ui->treeWidgetDoctors->addTopLevelItem(patient);

        // Создаем объект child для доктора и добавляем его в topLevelItem
        // таким образом формируется дерево отношений
        QTreeWidgetItem *doctor = new QTreeWidgetItem();
        // В первую колонку вставляем пустую строку.
        doctor->setText(0, {});
        // Во вторую информацию о докторе.
        doctor->setText(1, d->getInfo().c_str());
        // Привязываем докторов к пациентам.
        patient->addChild(doctor);

        prevP = p;
    }
}

void MainWindow::on_pushButtonCreateDoctorRelation_clicked()
{
    t.getTest();
    addLink();
    // Очищаем выбранные элементы списка.
    ui->listViewDoctors->clearSelection();
    ui->listViewPatients->clearSelection();
}

int MainWindow::saveContent(const std::string &path)
{
    return EXIT_SUCCESS;
}

int MainWindow::loadContent(const std::string &path)
{
    return EXIT_SUCCESS;
}
