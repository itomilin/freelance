#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextCodec>

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
    ui->plainTextEdit->clear();
    // Вызываем диалог выбора файла, путь записываем в filename.
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    if (filename.isEmpty())
        return;

    // Открываем файл в режиме только для чтения.
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Читаем построчно файл и записываем его в строку для дальнейшего разбора.
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    utfcodec->setCodecForLocale(utfcodec);
    while (!file.atEnd())
    {
        QString line = file.readLine();
        _data.append(line);
    }

    // Создаем объект класса для парсинга текста. Используем умный указатель.
    std::shared_ptr<TagParser> tagParser = std::make_shared<TagParser>(_data);
    ui->plainTextEdit->insertPlainText(tagParser->parseFile());
}
