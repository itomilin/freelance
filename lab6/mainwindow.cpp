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
//    _qDoctors.emplaceBack(doctor);
    _qDoctors.push_back(doctor);

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
//    _qPatients.emplaceBack(patient);
    _qPatients.push_back(patient);

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

    // Если не пуст, то перебираем строки которые были выбраны.
    for(auto const &item : selectedPatientsIndexes)
    {
        int patientIndex = item.row();
        int doctorIndex = selectedDoctorIndex.first().row();
        _doctorIndexesRelation.insert(std::make_pair(doctorIndex, patientIndex));
    }

    /** На основе сохраненных индексов, берем значения по индексам и создаем пары отношений.
     *  Необходимо для сохранения связей в файл.
     */
    for (auto const &item : _doctorIndexesRelation)
    {
        _doctorRelation.insert(std::make_pair(_qDoctors.at(item.first),
                                              _qPatients.at(item.second)));
    }
    //


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
    addLink();
    // Очищаем выбранные элементы списка.
    ui->listViewDoctors->clearSelection();
    ui->listViewPatients->clearSelection();
}

int MainWindow::saveContent(const QString &path)
{
    // Проверка на пустоту списков.
    if (_qDoctors.size() == 0 || _qPatients.size() == 0)
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
    file << DOCTOR_SECTION << std::endl;
    for (const auto &doctor : _qDoctors)
    {
        file << doctor->getInfo() << std::endl;
    }

    file << PATIENT_SECTION << std::endl;
    for (const auto &patient : _qPatients)
    {
        file << patient->getInfo() << std::endl;
    }

    file << RELATIONS_SECTION << std::endl;
    for (const auto &item : _doctorIndexesRelation)
    {
        file << item.first << ':' << item.second << std::endl;
    }
    file.close();

    qDebug() << "********File successfull wrote!********";

    return EXIT_SUCCESS;
}

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

    std::string initials;
    std::string roomNumber;
    std::string specialization;
    std::string age;
    std::string gender;

    // Читаем файл до конца.
    // Разбор самым простым образом, находим секцию и читаем до следующей найденной
    // Разбор учитывает порядок, сохраненный файл изменять нельзя.
    getline(file, line);
    // Если встретили секцию с докторами, то создаем объекты и помещаем в список
    // Пока не дошли до следующей секции.
    if (DOCTOR_SECTION == line)
    {
        while (true)
        {
            getline(file, line);

            if (line == PATIENT_SECTION)
                break;

            std::istringstream iss(line);
            // Раскладываем прочитанную строку на поля.
            getline(iss, specialization, ';');
            getline(iss, initials, ';');
            getline(iss, roomNumber, ';');
            // Создаем новый объект
            Doctor *doctor = new Doctor(specialization, initials, std::stoul(roomNumber));

            // Кладем созданный объект в вектор.
            _qDoctors.push_back(doctor);
        }
    }
    if (PATIENT_SECTION == line)
    {
        while (true)
        {
            getline(file, line);
            if (line == RELATIONS_SECTION)
                break;

            std::istringstream iss(line);
            // Раскладываем прочитанную строку на поля.
            getline(iss, initials, ';');
            getline(iss, age, ';');
            getline(iss, gender, ';');
            // Создаем новый объект
            Patient *patient = new Patient(gender, initials, std::stoul(age));

            // Кладем созданный объект в вектор.
            _qPatients.push_back(patient);
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
            _doctorIndexesRelation.insert(std::make_pair(std::stoi(d), std::stoi(p)));
        }
    }

    return EXIT_SUCCESS;
}

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

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Save the file",
                                                    "./",
                                                    "Config files (*.cfg)");

    if (filename.isEmpty())
        return;

    // Clear old data
    _qDoctors.clear();
    _qPatients.clear();
    _doctorIndexesRelation.clear();
    _doctorRelation.clear();
    _patientRelation.clear();

    ui->treeWidgetDoctors->clear();
    ui->treeWidgetPatients->clear();

    loadContent(filename);

    // Загружаем связи и списки в контролы.
    QStringList *lines = new QStringList();
    QStringListModel *model = new QStringListModel(*lines, nullptr);
    // Заполняем контрол.
    for(auto const &doctor : _qDoctors)
    {
        lines->append(QString::fromStdString(doctor->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewDoctors->setModel(model);

    lines->clear();
    model = new QStringListModel(*lines, nullptr);
    // Заполняем контрол.
    for(auto const &patient : _qPatients)
    {
        lines->append(QString::fromStdString(patient->getInfo()));
    }
    model->setStringList(*lines);
    ui->listViewPatients->setModel(model);

    // Создаем базовый topLevelItem для построения дерева отношений.
    QTreeWidgetItem *doctor = new QTreeWidgetItem(ui->treeWidgetDoctors);
    // Присвоим на предыдущий элемент начало контейнера set через итератор.
    Doctor *prevD = _doctorRelation.begin()->first;
    if (!_doctorIndexesRelation.empty())
    {
        /** На основе сохраненных индексов, берем значения по индексам и создаем пары отношений.
         *  Необходимо для сохранения связей в файл.
         */
        for (auto const &item : _doctorIndexesRelation)
        {
            _doctorRelation.insert(std::make_pair(_qDoctors.at(item.first),
                                                  _qPatients.at(item.second)));
        }
        //
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
}

void MainWindow::on_pushButtonDeleteDoctor_clicked()
{
    // Проверяем на наличие модели если указатеь на nullptr, значит список пуст.
    auto modelDoctors = ui->listViewDoctors->selectionModel();
    if (modelDoctors == nullptr)
    {
        qDebug() << "[ ERROR ] tree view is empty!";
        return;
    }

    auto selectedDoctorIndex = modelDoctors->selectedIndexes();
    int doctorIndex = selectedDoctorIndex.first().row();

    // Удаляем сначала из списка докторов.
    _qDoctors.removeAt(doctorIndex);
    for (auto const &item : _doctorIndexesRelation)
    {
        if (item.first == doctorIndex)
        {
            _doctorIndexesRelation.erase(item);
        }
    }



    modelDoctors->model()->removeRow(doctorIndex);
//    _qDoctors.removeAt(doctorIndex);


    qDebug() << "1";
    // Затем из множества связей.
//    _doctorIndexesRelation.find(std::make_pair<doctorIndex, 0>);
//    _doctorIndexesRelation.insert(std::make_pair(doctorIndex, patientIndex));
}
