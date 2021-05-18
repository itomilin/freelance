#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_actionSIMPLE_triggered()
{
    _data.clear();
    // Вызываем диалог выбора файла, путь записываем в filename.
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    if (filename.isEmpty())
        return;

    // Открываем файл в режиме только для чтения.
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Читаем построчно файл и записываем его в строку для дальнейшего разбора.
    while (!file.atEnd())
    {
        QString line = file.readLine();

        if (line.size() == 1 && line.endsWith('\n'))
        {
            _data.append('\n');
        }
        else
        {
            // if end
            if (line.endsWith('\n'))
                line.replace('\n', SYMBOL).append('\n');
            else
                line.append(SYMBOL);
            _data.append(line);
        }
    }
    ui->plainTextEdit->setPlainText(_data);
    file.close();
}

// Ниже заведем два метода, для уменьшения дублирования кода
// Передаем аргумент для выбора записи в бинарный или csv формат
int MainWindow::writeToFile(const FileType& type)
{
    QString filename = "";
    // В зависимости от типа, вызываем конструктор с разными фильтрами по маске.
    if (type == FileType::BINARY)
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

    ui->plainTextEdit->clear();

    // Выбираем метод для записи в зависимости от типа
    return type == BINARY ?
                _fileWorker->writeToFileBinary(filename.toStdString(), _data.toStdString()) :
                _fileWorker->writeToFile(filename.toStdString(), _data.toStdString());
}

int MainWindow::readFromFile(const FileType& type)
{
    QString filename = "";
    // В зависимости от типа, вызываем конструктор с разными фильтрами по маске.
    if (type == FileType::BINARY)
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

    _data.clear();
    // Выбираем метод для чтения в зависимости от типа
    return type == BINARY ?
                _fileWorker->readFromFileBinary(filename, _data) :
                _fileWorker->readFromFile(filename.toStdString(), _data);
}

void MainWindow::on_openCSV_triggered()
{
    if (readFromFile(FileType::CSV) == 0)
    {
        ui->plainTextEdit->setPlainText(_data);
        // Вызываем сообщение, что все ок.
        myMessage("File successfully read", "OK");
    }
    else
    {
        myMessage("File could not read!", "ERROR");
    }
}

void MainWindow::on_saveCSV_triggered()
{
    if (writeToFile(FileType::CSV) == 0)
    {
        // Вызываем сообщение, что все ок.
        myMessage("File successfully recorded", "OK");
    }
    else
    {
        myMessage("File could not record!", "ERROR");
    }
}

// -----------------------------------------------------

// save binary
void MainWindow::on_saveBINARY_triggered()
{
    if (writeToFile(FileType::BINARY) == 0)
    {
        // Вызываем сообщение, что все ок.
        myMessage("File successfully recorded", "OK");
    }
    else
    {
        myMessage("File could not record!", "ERROR");
    }
}

//  read binary
void MainWindow::on_openBINARY_triggered()
{
    if (readFromFile(FileType::BINARY) == 0)
    {
        ui->plainTextEdit->setPlainText(_data);
        // Вызываем сообщение, что все ок.
        myMessage("File successfully read", "OK");
    }
    else
    {
        myMessage("File could not read!", "ERROR");
    }
}

