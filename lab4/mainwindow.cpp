#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Заполняем combobox данными в конктрукторе.
    ui->comboBoxSort->addItems({"-----",
                                "by foundation year",
                                "by name",
                                "by count of students",
                                "by count of faculties",
                                "by anniversary date"
                               });
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Метод для отображения информационного окна. В зависимости от передаваемой
 * информации, показывает информационные окна.
 * @param msg - содержимое сообщения
 * @param title - название окна
 */
void MainWindow::myMessage(const QString &msg, const QString &title)
{
    // Вызываем message box после успешной записи.
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle(title);
    msgBox.exec();
}

/**
 * Обработчик нажатия на кнопку, которая добавляет новые записи в список.
 */
void MainWindow::on_pushButtonAdd_clicked()
{
    // Выполняем валидацию, если текстовое поле пустое, то сообщаем об этом.
    if (ui->lineEditUniversityName->text().isEmpty())
    {
        myMessage("Field university_name is empty, set some text!",
                  "Error with add new entry!");
        return;
    }
    else if (ui->spinBoxFacultiesCount->text().isEmpty()) {
        myMessage("Field faculties_count is empty, set some text!",
                  "Error with add new entry!");
        return;
    }
    else if (ui->spinBoxFoundationYear->text().isEmpty()) {
        myMessage("Field foundation_year is empty, set some text!",
                  "Error with add new entry!");
        return;
    }
    else if (ui->spinBoxStudentsCount->text().isEmpty()) {
        myMessage("Field students_count is empty, set some text!",
                  "Error with add new entry!");
        return;
    }

    // Если валидация прошла, то берем содержимое из контролов и передаем в метод
    // добавления новой записи в список.
    _universities.addNewUniversity(ui->lineEditUniversityName->text().toStdString(),
                                   ui->spinBoxFoundationYear->value(),
                                   ui->spinBoxStudentsCount->value(),
                                   ui->spinBoxFacultiesCount->value());
    // Обновляем контрол, который показывает количество элементов в списке.
    ui->spinBoxCountUniversities->setValue(_universities.getSize());
    // Очищаем контролы от введенных данных.
    clearControls();
    // Обновляем информацию.
    showData();
    // Вызываем сообщение, что все ок.
    myMessage("Entry was successfully added", "OK");
}

void MainWindow::clearControls()
{
    ui->lineEditUniversityName->clear();
    ui->spinBoxFacultiesCount->clear();
    ui->spinBoxFoundationYear->clear();
    ui->spinBoxStudentsCount->clear();
}

/**
 * Обработчик нажатия на кнопку удаления записи.
 */
void MainWindow::on_pushButtonDelete_clicked()
{
    int retCode = EXIT_SUCCESS;
    // В зависимости от выбора пользователя, удаляем элемент соответствующим способом.
    if (ui->radioButtonDeleteByIndex->isChecked())
    {
        // Удаляем голову списка, передаваемый номер отвечает за тип удаления.
        // Второй параметр номер элемента, который указан в контроле
        retCode = _universities.deleteUniversity(1, ui->spinBoxDeleteIndex->value());
    }
    else if (ui->radioButtonDeleteByTail->isChecked())
    {
        // Удаляем хвост списка, передаваемый номер отвечает за тип удаления.
        // Вторым параметром передаем просто заглушку, он не используется.
        retCode = _universities.deleteUniversity(3, 0);
    }
    else if (ui->radioButtonDeleteByHead->isChecked())
    {
        // Удаляем по индексу, передаваемый номер отвечает за тип удаления.
        // Вторым параметром передаем просто заглушку, он не используется.
        retCode = _universities.deleteUniversity(2, 0);
    }

    if (retCode == EXIT_SUCCESS)
    {
        // Обновляем контрол, который показывает количество элементов в списке.
        ui->spinBoxCountUniversities->setValue(_universities.getSize());
        // Вызываем метод для заполнения контрола с информацией о вузах.
        showData();
        // Вызываем сообщение.
        myMessage("Node successfully deleted!", "OK");
    }
    else
    {
        // Вызываем сообщение.
        myMessage("Wrong index or list is empty!", "ERROR");
    }
}

// Метод, для заполнения plain text информацией о вузах.
void MainWindow::showData()
{
    // Вызываем метод, который возвращает пустую строку или строку с информацией.
    QString universitiesInfo = QString::fromUtf8(_universities.showUniversities());
    // Тернарный оператор, аналог if - else, только писать меньше.
    // Если пустая строка, пишем в контрол, что список пуст, иначе пишем данные.
    universitiesInfo.isEmpty() ?
                ui->plainTextEdit->setPlainText("List is empty!") :
                ui->plainTextEdit->setPlainText(universitiesInfo);
}

/**
 * Обработчик combobox, когда изменяем тип сортировки то берем индекс
 * выбранного элемента.
 */
void MainWindow::on_comboBoxSort_currentIndexChanged(int index)
{
    // Передаем индекс в метод сортировки.
    _universities.sortVectorByType(index);
    // Обновляем данные в plain text.
    showData();
}

/**
 * Обработчик нажатия на кнопку обновить данные.
 * Из полей читаем все введенные данные, и обновляем их.
 * Поскольку используем указатель, можно изменить данные в загруженном объекте,
 * это позволяет избежать лишних действий.
 */
void MainWindow::on_pushButtonUpdate_clicked()
{
    if (_pObject != nullptr)
    {
        _pObject->setName(ui->lineEditUniversityName->text().toStdString());
        _pObject->setFacultyCount(ui->spinBoxFacultiesCount->value());
        _pObject->setFoundationYear(ui->spinBoxFoundationYear->value());
        _pObject->setStudentCount(ui->spinBoxStudentsCount->value());
        showData();
        // Чистим контролы
        clearControls();
        myMessage("Data successfully updated!", "OK");
    }
}

/**
 * Обработчик поиска значения по индексу.
 * Выбранное значение контрола передаем в метод loadInfo, который выполнит
 * поиск по индексу, если значение по индексу существует, то будет не пустой указатель
 * иначе указатель на null
 */
void MainWindow::on_spinBoxUpdateIndex_valueChanged(int arg1)
{
    _pObject = _universities.loadInfo(arg1);
    // Если возвращается нулевой указатель, то индекс задан не верно.
    if (_pObject == nullptr)
    {
        myMessage("Index not found!", "ERROR");
        ui->spinBoxUpdateIndex->setValue(0);
        return;
    }

    ui->lineEditUniversityName->setText(QString::fromUtf8(_pObject->getName()));
    ui->spinBoxFacultiesCount->setValue(_pObject->getFacultyCount());
    ui->spinBoxFoundationYear->setValue(_pObject->getFoundationYear());
    ui->spinBoxStudentsCount->setValue(_pObject->getStudentCount());
}

/**
 * Обработчик загрузки файла, который сохранен в бинарном формате.
 */
void MainWindow::on_actionOpenBinary_triggered()
{
    // Вызываем метод чтения файла, передаем ему путь до файла.
    // В зависимости от возвращаемого значения выполняем действие
    if (readFromFile(BINARY) == 0)
    {
        clearControls();
        // Обновляем контрол, который показывает количество элементов в списке.
        ui->spinBoxCountUniversities->setValue(_universities.getSize());
        // Показываем загруженные данные в контроле.
        showData();
        // Вызываем сообщение, что все ок.
        myMessage("Binary file successfully read!", "OK");
    }
    else
    {
        myMessage("File could not read!", "ERROR");
    }
}

/**
 * Обработчик сохранения файла на диск в бинарном формате.
 */
void MainWindow::on_actionSaveBinary_triggered()
{
    // Вызываем метод чтения файла, передаем ему путь до файла.
    // В зависимости от возвращаемого значения выполняем действие
    if (writeToFile(BINARY) == 0)
    {
        clearControls();
        // Вызываем сообщение, что все ок.
        myMessage("File successfully recorded", "OK");
    }
    else
    {
        myMessage("File could not record!", "ERROR");
    }
}

/**
 * Обработчик загрузки файла в CSV формате
 */
void MainWindow::on_actionOpenCSV_triggered()
{
    // Вызываем метод чтения файла, передаем ему путь до файла.
    // В зависимости от возвращаемого значения выполняем действие
    if (readFromFile(CSV) == 0)
    {
        clearControls();
        // Обновляем контрол, который показывает количество элементов в списке.
        ui->spinBoxCountUniversities->setValue(_universities.getSize());
        // Показываем загруженные данные в контроле.
        showData();
        // Вызываем сообщение, что все ок.
        myMessage("File successfully read!", "OK");
    }
    else
    {
        myMessage("File could not read!", "ERROR");
    }
}

/**
 * Обработчик сохранения файла на диск в CSV
 */
void MainWindow::on_actionSaveCSV_triggered()
{
    // Вызываем метод чтения файла, передаем ему путь до файла.
    // В зависимости от возвращаемого значения выполняем действие
    if (writeToFile(CSV) == 0)
    {
        clearControls();
        // Вызываем сообщение, что все ок.
        myMessage("File successfully recorded", "OK");
    }
    else
    {
        myMessage("File could not record!", "ERROR");
    }
}


// Ниже заведем два метода, для уменьшения дублирования кода
// Передаем аргумент для выбора записи в бинарный или csv формат
int MainWindow::writeToFile(const FileTypes &type)
{
    QString filename = "";
    // В зависимости от типа, вызываем конструктор с разными фильтрами по маске.
    if (type == BINARY)
    {
        filename = QFileDialog::getSaveFileName(this,
                                                "Save the file",
                                                "./",
                                                "Binary files (*.bin)");
    }
    else
    {
        filename = QFileDialog::getSaveFileName(this,
                                                "Save the file",
                                                "./",
                                                "CSV files (*.csv)");
    }

    // Проверяем задано ли имя.
    if (filename.isEmpty())
        return EXIT_FAILURE;

    // Выбираем метод для записи в зависимости от типа
    return type == BINARY ?
                _universities.writeToFileBinary(filename.toStdString()) :
                _universities.writeToFile(filename.toStdString());
}

int MainWindow::readFromFile(const FileTypes &type)
{
    QString filename = "";
    // В зависимости от типа, вызываем конструктор с разными фильтрами по маске.
    if (type == BINARY)
    {
        filename = QFileDialog::getOpenFileName(this,
                                                "Open the file",
                                                "./",
                                                "Binary files (*.bin)");
    }
    else
    {
        filename = QFileDialog::getOpenFileName(this,
                                                "Open the file",
                                                "./",
                                                "CSV files (*.csv)");
    }

    // Проверяем задано ли имя.
    if (filename.isEmpty())
        return EXIT_FAILURE;

    // Выбираем метод для чтения в зависимости от типа
    return type == BINARY ?
                _universities.readFromFileBinary(filename.toStdString()) :
                _universities.readFromFile(filename.toStdString());

}


void MainWindow::on_pushButtonClearAll_clicked()
{
    _universities.clear();
    clearControls();
    ui->plainTextEdit->clear();
    ui->spinBoxCountUniversities->setValue(_universities.getSize());
    myMessage("List purged!", "OK");
}

