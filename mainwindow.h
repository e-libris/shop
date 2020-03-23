#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include "src/receipt.h"

using std::string;
using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    string to_fdate(string);
    vector<receipt> v;
    struct dbitem   {
        string code;
        string name;

    };

private:
    Ui::MainWindow *ui;

private slots:
    // ???
    void draw_pie(vector<int>&, string, string);
    void bdate_cbox_changed();
    void item_selected();
};
#endif // MAINWINDOW_H
