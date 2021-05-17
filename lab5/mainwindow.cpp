#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем объект класса
    dirModel = new QFileSystemModel(this);
    // Задаем модификатор readonly
    dirModel->setReadOnly(true);
    // Показываем все файлы включая скрытые, кроме символов выше/ниже (. ..)
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
    // Задаем root путь испольняемого файла в качестве отображаемого по умолчанию.
    dirModel->setRootPath("");
    ui->treeView->setModel(dirModel);
    ui->treeView->setRootIndex(dirModel->index(""));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Обработчик события нажатия по дереву файлов
 * Получаем путь при нажатии на элемент, для дальнейшей работы.
 */
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    selectedPath = dirModel->fileInfo(index).absoluteFilePath();
    parseDir(selectedPath);
}

/**
 * Обработчик нажатия на кнопку поиска директории
 */
void MainWindow::on_pushButton_clicked()
{
    // Если поле пустое, ничего не делаем
    if(ui->lineEdit->text().isEmpty())
        return;

    // Если не пустое, парсим путь в текстовом поле и пытаемся отобразить модель
    auto modelIndex = dirModel->index(ui->lineEdit->text());
    // Если строка или колонка возвращает -1, значит путь неправильный.
    if (modelIndex.column() == -1 || modelIndex.row() == -1)
    {
        msgBox.setText("Invalid system path!");
        msgBox.exec();
        return;
    }

    // Если путь правильный, отображаем модель в контроле.
    ui->treeView->setRootIndex(dirModel->index(ui->lineEdit->text()));
    parseDir(ui->lineEdit->text());
}

// Парсим директорию по указанному пути. Если в качестве пути будет указан файл
// в таком случае будет сообщение.
void MainWindow::parseDir(const QString &path)
{
    // Чистим контол, если не пустой.
    if (ui->listWidget->count() > 0)
        ui->listWidget->clear();

    // Задаем переменную которая определяет все файлы по заданному пути
    QDir dir(path);

    if(QFileInfo(path).isFile())
    {
        msgBox.setText("Is not a directory! Select the directory!");
        msgBox.exec();
        return;
    }

    // Добавим полученный список в контрол.
    ui->listWidget->addItems(attrs->parseFiles(dir));
}
