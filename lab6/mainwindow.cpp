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
void MainWindow::on_pushButtonAddDepartment_clicked()
{
    // Получаем значения с контролов.
    std::string departmentName = ui->lineEditDepartmentName->text().toStdString();
    size_t staffCount = ui->spinBoxStaffCount->value();

    // Если поля пустые, тогда не выполняем код ниже.
    if (departmentName.empty())
        return;

    for (const auto& item : _qDepartments)
    {
        if (item->getName() == departmentName)
        {
            qDebug() << QString::fromStdString(departmentName) << " already exist";
            return;
        }
    }

    // Создаем новый объект
    Department *department = new Department(departmentName, staffCount);

    // Кладем созданный объект в вектор.
    _qDepartments.push_back(department );

    QStringList *lines = new QStringList();
    QStringListModel *model = new QStringListModel(*lines, nullptr);
    // Заполняем контрол.
    for(auto const &department : _qDepartments)
    {
        lines->append(QString::fromStdString(department->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewDepartment->setModel(model);
}

// Обработчик кнопки добавления препаратов.
void MainWindow::on_pushButtonAddMedication_clicked()
{
    // Получаем значения с контролов.
    std::string medicinesName = ui->lineEditMedicationName->text().toStdString();
    double price = ui->doubleSpinBoxPrice->value();
    size_t age = ui->spinBoxStaffCount->value();

    // Если поля пустые, завершаем выполнение.
    if (medicinesName.empty())
        return;

    for (const auto& item : _qMedicines)
    {
        if (item->getName() == medicinesName)
        {
            qDebug() << QString::fromStdString(medicinesName) << " already exist";
            return;
        }
    }

    // Создаем новый объект
    Medicines *medicines = new Medicines(medicinesName, price, age);

    // Кладем созданный объект в вектор.
    _qMedicines.push_back(medicines);

    QStringList *lines = new QStringList();
    QStringListModel *model = new QStringListModel(*lines, nullptr);

    // Заполняем контрол.
    for(auto const &item : _qMedicines)
    {
        lines->append(QString::fromStdString(item->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewMedication->setModel(model);
}

void MainWindow::addLink()
{
    // Проверяем на наличие модели если указатеь на nullptr, значит список пуст.
    auto model = ui->listViewMedication->selectionModel();
    auto modelDepartment = ui->listViewDepartment->selectionModel();
    if (model == nullptr || modelDepartment == nullptr)
    {
        qDebug() << "[ ERROR ] tree view is empty!";
        return;
    }

    auto selectedPatientsIndexes = model->selectedIndexes();
    auto selectedDepartmentIndex = modelDepartment->selectedIndexes();
    // Проверяем выбраны ли элементы из списков.
    if (selectedPatientsIndexes.empty() || selectedDepartmentIndex.empty())
    {
        return;
    }
    // Обязательно очистить дерево связей.
    ui->treeWidgetDepartment->clear();
    ui->treeWidgetMedication->clear();

    // Если не пуст, то перебираем строки которые были выбраны.
    for(auto const &item : selectedPatientsIndexes)
    {
        int patientIndex = item.row();
        int doctorIndex = selectedDepartmentIndex.first().row();
        _departmentIndexesRelation.insert(std::make_pair(doctorIndex, patientIndex));
    }

    /** На основе сохраненных индексов, берем значения по индексам и создаем пары отношений.
     *  Необходимо для сохранения связей в файл.
     */
    for (auto const &item : _departmentIndexesRelation)
    {
        _departmentRelation.insert(std::make_pair(_qDepartments.at(item.first),
                                              _qMedicines.at(item.second)));
    }

    createDepartmentRelation();
    createMedicinesRelation();
}

void MainWindow::createDepartmentRelation()
{

    // Создаем дерево отношений для отделов.

    // Создаем базовый topLevelItem для построения дерева отношений.
    QTreeWidgetItem *department = new QTreeWidgetItem(ui->treeWidgetDepartment);
    // Присвоим на предыдущий элемент начало контейнера set через итератор.
    Department *prevD = _departmentRelation.begin()->first;

    // Перебираем все связи  доктор -> пациенты
    for(auto const &relation : _departmentRelation)
    {
        // Записываем следующее в списке имя доктора и пациента.
        // Извлекаем значения из контейнера pair first - доктор, second - пациент
        auto d = relation.first;
        auto p = relation.second;

        // Для будущего формирования дерева, заполняем список.
        // Формируем множество для отношения пациент -> доктора
        _medicinesRelation.insert(std::make_pair(p, d));

        // Когда сменяется доктор, то создаем новый topLevelItem
        // Для этого проверяем на равенство предыдущий и текущий элемент списка
        if (d != prevD)
        {
            department = new QTreeWidgetItem(ui->treeWidgetDepartment);
        }
        // добавляем в topLevelItem информацию о докторе
        department->setText(0, d->getInfo().c_str());
        ui->treeWidgetDepartment->addTopLevelItem(department);

        // Создаем объект child для препаратов и добавляем его в topLevelItem
        // таким образом формируется дерево отношений
        QTreeWidgetItem *patient = new QTreeWidgetItem();
        // В первую колонку вставляем пустую строку.
        patient->setText(0, "");
        // Во вторую информацию о препаратах.
        patient->setText(1, p->getInfo().c_str());
        // Привязываем препараты к отделению.
        department->addChild(patient);

        prevD = d;
    }

}

void MainWindow::createMedicinesRelation()
{
    // -------------------------------------------------------------------------
    // Создаем обратное дерево отношений для пациентов.

    // Создаем базовый topLevelItem
    QTreeWidgetItem *medicines = new QTreeWidgetItem(ui->treeWidgetMedication);

    // Присвоим на предыдущий элемент начало контейнера set через итератор.
    Medicines *prevM = _departmentRelation.begin()->second;

    // Перебираем все связи  доктор -> пациенты
    for(auto const &relation : _medicinesRelation)
    {
        // Записываем следующее в списке имя доктора и пациента.
        auto p = relation.first;
        auto d = relation.second;

        // Когда сменяется доктор, то создаем новый topLevelItem
        // Для этого проверяем на равенство предыдущий и текущий элемент списка
        if (p != prevM)
        {
            medicines = new QTreeWidgetItem(ui->treeWidgetMedication);
        }
        // добавляем в topLevelItem информацию о пациенте.
        medicines->setText(0, p->getInfo().c_str());
        ui->treeWidgetDepartment->addTopLevelItem(medicines);

        // Создаем объект child для доктора и добавляем его в topLevelItem
        // таким образом формируется дерево отношений
        QTreeWidgetItem *doctor = new QTreeWidgetItem();
        // В первую колонку вставляем пустую строку.
        doctor->setText(0, "");
        // Во вторую информацию о докторе.
        doctor->setText(1, d->getInfo().c_str());
        // Привязываем докторов к пациентам.
        medicines->addChild(doctor);

        prevM = p;
    }
}

// Метод сохранения контента в файл.
int MainWindow::saveContent(const QString &path)
{
    // Проверка на пустоту списков.
    if (_qDepartments.size() == 0 || _qMedicines.size() == 0)
    {
        qDebug() << "Lists are empty!";
        return EXIT_FAILURE;
    }

    std::ofstream file;
    file.open(path.toStdString(), std::ofstream::out);

    if (!file.is_open())
    {
        // Если файл не смогли прочесть, тогда печатаем сообщение и возвращаем 1.
        qDebug() << "********Could not open the file!********";
        return EXIT_FAILURE;
    }

    // Формируем сохранения в некоторое подобие конфигурационного файла.
    file << DEPARTMENT_SECTION << std::endl;
    for (const auto &doctor : _qDepartments)
    {
        file << doctor->getInfo() << std::endl;
    }

    file << MEDICINES_SECTION << std::endl;
    for (const auto &patient : _qMedicines)
    {
        file << patient->getInfo() << std::endl;
    }

    file << RELATIONS_SECTION << std::endl;
    for (const auto &item : _departmentIndexesRelation)
    {
        file << item.first << ':' << item.second << std::endl;
    }
    file.close();

    qDebug() << "********File successfull wrote!********";

    return EXIT_SUCCESS;
}

// Метод загрузки из файла.
int MainWindow::loadContent(const QString &path)
{
    std::ifstream file;
    file.open(path.toStdString(), std::ifstream::in | std::ifstream::binary);

    if (!file.is_open())
    {
        // Если файл не смогли прочесть, тогда печатаем сообщение и возвращаем 1.
        qDebug() << "********Could not open the file!********";
        return EXIT_FAILURE;
    }

    std::string line;

    std::string departmentName;
    std::string staffCount;
    std::string medicinesName;
    std::string expireDate;
    std::string price;

    // Читаем файл до конца.
    // Разбор самым простым образом, находим секцию и читаем до следующей найденной
    // Разбор учитывает порядок, сохраненный файл изменять нельзя.
    getline(file, line);
    // Если встретили секцию с отделами, то создаем объекты и помещаем в список
    // Пока не дошли до следующей секции.
    if (DEPARTMENT_SECTION == line)
    {
        while (true)
        {
            getline(file, line);

            if (line == MEDICINES_SECTION)
                break;

            std::istringstream iss(line);
            // Раскладываем прочитанную строку на поля.
            getline(iss, departmentName, ';');
            getline(iss, staffCount, ';');
            // Создаем новый объект
            Department *department = new Department(departmentName, std::stoul(staffCount));

            // Кладем созданный объект в вектор.
            _qDepartments.push_back(department);
        }
    }
    if (MEDICINES_SECTION == line)
    {
        while (true)
        {
            getline(file, line);
            if (line == RELATIONS_SECTION)
                break;

            std::istringstream iss(line);
            // Раскладываем прочитанную строку на поля.
            getline(iss, medicinesName, ';');
            getline(iss, price, ';');
            getline(iss, expireDate, ';');
            // Создаем новый объект
            Medicines *medicines = new Medicines(medicinesName,
                                               std::stod(price),
                                               std::stoul(expireDate));

            // Кладем созданный объект в вектор.
            _qMedicines.push_back(medicines);
        }
    }
    if (line == RELATIONS_SECTION)
    {
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            std::istringstream iss(line);
            std::string d;
            std::string p;

            getline(iss, d, ':');
            getline(iss, p, ':');
            _departmentIndexesRelation.insert(std::make_pair(std::stoi(d), std::stoi(p)));
        }
    }

    return EXIT_SUCCESS;
}

// Обработчик кнопки сохранения.
void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Save the file",
                                                    "./",
                                                    "Config files (*.cfg)");

    if (filename.isEmpty())
        return;

    saveContent(filename);

}

// Обработчик кнопки загрузки файла
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Save the file",
                                                    "./",
                                                    "Config files (*.cfg)");

    if (filename.isEmpty())
        return;

    // Clear old data
    _qDepartments.clear();
    _qMedicines.clear();
    _departmentIndexesRelation.clear();
    _departmentRelation.clear();
    _medicinesRelation.clear();

    ui->treeWidgetDepartment->clear();
    ui->treeWidgetMedication->clear();

    loadContent(filename);

    // Загружаем связи и списки в контролы.
    QStringList *lines = new QStringList();
    QStringListModel *model = new QStringListModel(*lines, nullptr);
    // Заполняем контрол.
    for(auto const &item : _qDepartments)
    {
        lines->append(QString::fromStdString(item->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewDepartment->setModel(model);

    lines->clear();
    model = new QStringListModel(*lines, nullptr);
    // Заполняем контрол.
    for(auto const &patient : _qMedicines)
    {
        lines->append(QString::fromStdString(patient->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewMedication->setModel(model);

    if (!_departmentIndexesRelation.empty())
    {
        /** На основе сохраненных индексов, берем значения по индексам и создаем пары отношений.
         *  Необходимо для сохранения/чтения связей.
         */
        for (auto const &item : _departmentIndexesRelation)
        {
            _departmentRelation.insert(std::make_pair(_qDepartments.at(item.first),
                                                  _qMedicines.at(item.second)));
        }
        createDepartmentRelation();
    }
    createMedicinesRelation();
}

// Обработчик удаления препаратов.
void MainWindow::on_pushButtonDeleteMedication_clicked()
{
    // Проверяем на наличие модели если указатеь на nullptr, значит список пуст.
    auto modelPatients = ui->listViewMedication->selectionModel();
    if (modelPatients == nullptr)
    {
        qDebug() << "[ ERROR ] tree view is empty!";
        return;
    }

    // Удаление только по первому выделеному индексу
    auto selectedPatientIndex = modelPatients->selectedIndexes();
    int patientIndex = selectedPatientIndex.first().row();

    // Удаляем сначала из списка препараты.
    _qMedicines.erase(_qMedicines.begin() + patientIndex);

    // Очищаем модель
    modelPatients->model()->removeRow(patientIndex);
    // Очищаем связи
    _departmentRelation.clear();
    _medicinesRelation.clear();
    // Очищаем контролы
    ui->treeWidgetDepartment->clear();
    ui->treeWidgetMedication->clear();
    // Clear old data
    _departmentIndexesRelation.clear();
}

// Обработчик удаления отделов.
void MainWindow::on_pushButtonDeleteDepartment_clicked()
{
    // Проверяем на наличие модели если указатеь на nullptr, значит список пуст.
    auto modelDoctors = ui->listViewDepartment->selectionModel();
    if (modelDoctors == nullptr)
    {
        qDebug() << "[ ERROR ] tree view is empty!";
        return;
    }

    auto selectedDoctorIndex = modelDoctors->selectedIndexes();
    int doctorIndex = selectedDoctorIndex.first().row();

    // Удаляем сначала из списка отделы.
    _qDepartments.erase(_qDepartments.begin() + doctorIndex);

    modelDoctors->model()->removeRow(doctorIndex);
    _departmentRelation.clear();
    _medicinesRelation.clear();
    ui->treeWidgetDepartment->clear();
    ui->treeWidgetMedication->clear();
    // Clear old data
    _departmentIndexesRelation.clear();
}


void MainWindow::on_actioncreate_triggered()
{
    addLink();
    // Очищаем выбранные элементы списка.
    ui->listViewDepartment->clearSelection();
    ui->listViewMedication->clearSelection();
}
