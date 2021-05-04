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

void MainWindow::on_actionOpen_triggered()
{
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
        _data.append(line);
    }

    // Создаем объект класса для парсинга текста. Используем умный указатель.
    std::shared_ptr<TagParser> tagParser = std::make_shared<TagParser>(_data);
    // Вызываем метод парсинга файла для тегов заданных по заданию.
    ui->plainTextEdit->setPlainText(tagParser->parseHTML(_tagTitleOpen, _tagTitleClose));
    ui->plainTextEdit->appendPlainText(tagParser->parseHTML(_tagH1Open, _tagH1Close));
    ui->plainTextEdit->appendPlainText(tagParser->parseHTML(_tagH2Open, _tagH2Close));
    // Очищаем загруженный контент.
    _data.clear();
    // Закрываем файл.
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    // Вызываем диалог сохранения файла, путь записываем в filename.
    QString filename = QFileDialog::getSaveFileName(this, "Save the file");
    if (filename.isEmpty())
        return;

    // Открываем файл в режиме для записи.
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    // Переменная для хранения контента, который нужно записать в файл.
    QTextStream out(&file);
    // Пишем содержимое plainText в файл.
    out << ui->plainTextEdit->toPlainText() << "\n";
    // Закрываем файл.
    file.close();
    // Чистим текстовое поле.
    ui->plainTextEdit->clear();

    // Вызываем message box после успешной записи.
    QMessageBox msgBox;
    msgBox.setText("Successfull created! to -> " + filename);
    msgBox.exec();
}
