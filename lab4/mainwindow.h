#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionOpenCSV_triggered();

    void on_actionSaveBinary_triggered();

    //----------------------------------

    void on_actionSaveCSV_triggered();

    void on_actionOpenBinary_triggered();

private:
    Ui::MainWindow *ui;
    // Метод для обработки диалогового окна.
    static void myMessage(const QString &msg, const QString &title);

    // Заведем два отдельных метода для чтения/записи и перечисление для
    // выбора записи. Позволит сократить дублирование кода, так более рационально.

    // Заведем перечисление, чтобы выбирать формат при чтении/записи файла.
    // Можно обойтись и без этого, enum дает более наглядные типы
    enum FileTypes
    {
        BINARY = 0, // Так будем передать в метод не просто 0 и 1, а именованные переменные
        CSV = 1
    };

    // Метод записи в файл
    int writeToFile(const FileTypes &type);

    // Метод чтения из файла
    int readFromFile(const FileTypes &type);
};
#endif // MAINWINDOW_H
