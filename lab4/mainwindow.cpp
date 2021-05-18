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
 * Обработчик загрузки файла, который сохранен в бинарном формате.
 */
void MainWindow::on_actionOpenBinary_triggered()
{
    // Вызываем метод чтения файла, передаем ему путь до файла.
    // В зависимости от возвращаемого значения выполняем действие
    if (readFromFile(BINARY) == 0)
    {
//        clearControls();

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
//        clearControls();
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
//        clearControls();
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
//    return type == BINARY ?
//                _universities.writeToFileBinary(filename.toStdString()) :
//                _universities.writeToFile(filename.toStdString());
    return 0;
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
//    return type == BINARY ?
//                _universities.readFromFileBinary(filename.toStdString()) :
//                _universities.readFromFile(filename.toStdString());
    return 0;

}

