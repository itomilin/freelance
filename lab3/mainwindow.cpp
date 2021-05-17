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

    QString data = "";
    // Читаем построчно файл и записываем его в строку для дальнейшего разбора.
    while (!file.atEnd())
    {
        QString line = file.readLine();

        if (line.size() == 1 && line.endsWith('\n'))
        {
            data.append('\n');
        }
        else
        {
            // if end
            if (line.endsWith('\n'))
                line.replace('\n', SYMBOL).append('\n');
            else
                line.append(SYMBOL);
            data.append(line);
        }
    }
    ui->plainTextEdit->setPlainText(data);
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
