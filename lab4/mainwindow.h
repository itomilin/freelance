#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QVector>

#include "file_worker.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_saveCSV_triggered();

    void on_actionSIMPLE_triggered();

    void on_openCSV_triggered();

    void on_saveBINARY_triggered();

    void on_openBINARY_triggered();

private:
    Ui::MainWindow *ui;

    const QChar SYMBOL { '!' };

    // Метод для обработки диалогового окна.
    static void myMessage(const QString &msg, const QString &title);

    // Заведем перечисление, чтобы выбирать формат при чтении/записи файла.
    // Можно обойтись и без этого, enum дает более наглядные типы
    enum FileType
    {
        BINARY = 0, // Так будем передать в метод не просто 0 и 1, а именованные переменные
        CSV = 1
    };

    // Метод записи в файл
    int writeToFile(const FileType& type);

    // Метод чтения из файла
    int readFromFile(const FileType& type);

    FileWorker *_fileWorker;

    QString _data = "";

};

#endif // MAINWINDOW_H
