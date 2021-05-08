#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

#include "universities.hpp"

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
    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_actionOpenCSV_triggered();

    void on_comboBoxSort_currentIndexChanged(int index);

    void on_pushButtonUpdate_clicked();

    void on_spinBoxUpdateIndex_valueChanged(int arg1);

    void on_actionSaveBinary_triggered();

    void on_actionSaveCSV_triggered();

    void on_actionOpenBinary_triggered();

    void on_pushButtonClearAll_clicked();

private:
    Ui::MainWindow *ui;
    // Метод для обработки диалогового окна.
    static void myMessage(const QString &msg, const QString &title);
    // Метод отображения данных.
    void showData();
    // Указатель, который хранит структуру прочитанного нода из списка.
    University *_pObject { nullptr };
    // Метод очистки контролов
    void clearControls();

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

    // Список университетов.
    Universities _universities;
};
#endif // MAINWINDOW_H
