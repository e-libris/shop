#include <QString>
#include <QDateTime>
#include <QVector>
#include <QAbstractAnimation>
#include <QtAlgorithms>
#include <QtCharts>

#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/item.h"
#include "src/procreceipt.h"
#include "src/receipt.h"
#include "src/reports.h"

using namespace QtCharts;

using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow) {
    cout << "mainwindow" << endl;
    ui->setupUi(this);

    cout << "generate_master(v)" << endl;
    generate_master(v);
    cout << "end generate_master(v)" << endl;
    cout << "v.size() is: " << v.size() << endl;

    vector<int>v2(14,0);
    cout << "end vectorv2 declaration" << endl;

    cout << "connect" << endl;
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(bdate_cbox_changed()));

    // v is a vector of receipts
    // i is a receipt in vector v
    cout << "for i in v" << endl;
    for(auto&& i : v)   {

        ui->comboBox->addItem(QString::fromStdString(i.fdate));

        ui->textBrowser->append(QString::fromStdString(i.fdate).leftJustified(20, ' ') +
                               (QString::fromStdString("cashier: " + i.cashier).rightJustified(20, ' ')));
        string itemline;
        stringstream ss;
        QString item;

        // i is a receipt obj
        // j is an item in receipt i
        for(auto&& j : i.receiptvec)  {
            string tmp = to_string(j.price);
            tmp = tmp.substr(0, tmp.length()-2) + "." + tmp.substr(tmp.length()-2, 2);
            QString symbol = "$";
            ui->textBrowser->append((QString::fromStdString(j.name)).leftJustified(20, ' ')
                                  + symbol.rightJustified(15, ' ')
                                  + (QString::fromStdString(tmp)).rightJustified(5,' '));

            v2[j.category]++;
            //cout << j.category << endl;
        }

        ui->textBrowser->append(QString::fromStdString("\n"));

    }
    cout << "end for i in v" << endl;

    ui->comboBox_3->addItem("Select an item");
    //ifstream f("/home/roger/stuff/prog/Qt/AttemptTwo/data/items_mod.db");
    ifstream f("items.db");
    vector<string>itemdb;
    string line, line2, code, name, desc;
    stringstream ss;

    while(getline(f, line)) {
        itemdb.push_back(line);
        ss.clear();
        ss.str("");
        ss<<line;
        getline(ss,code,',');
        getline(ss,name,',');
        getline(ss,desc,',');
        ss.clear();
        ss.str("");
        ss << setw(14) << left << code << setw(20) << right << name;
        ui->comboBox_3->addItem(QString::fromStdString(ss.str()));
    }
    f.close();

    connect(ui->comboBox_3, SIGNAL(currentIndexChanged(int)),
            this, SLOT(item_selected()));
    //ui->comboBox_3->setCurrentIndex(-1);


    ui->label->setText("");
    QPixmap qpm = QString::fromStdString("resources/0001_generic.jpg");
    ui->label_2->setPixmap(qpm.scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));
    ui->label_2->setAlignment(Qt::AlignCenter);



    draw_pie(v2, v.front().date, v.back().date);



    QBarSet *set = new QBarSet("totals");

    for(auto& i : v)
        *set << stoi(i.total);
    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Totals, week to week");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    cout << "dates" << endl;
    QStringList dates;
    for(auto& i : v)    {
        string tmp(1, i.date[4]); // = i.date[4];
        tmp += i.date[5];
        int tmp2 = stoi(tmp);

        dates << QString::fromStdString(getmonthstring(tmp2) + '\n' + i.date[6]+i.date[7]);
        //cout << getmonthstring(tmp2) + " " + i.date[6]+i.date[7] << endl;
    }
    cout << "end dates" << endl;

    QBarCategoryAxis *axisx = new QBarCategoryAxis();
    axisx->append(dates);
    chart->addAxis(axisx, Qt::AlignBottom);
    series->attachAxis(axisx);
    QValueAxis *axisy = new QValueAxis();
    axisy->setRange(50,325);
    chart->addAxis(axisy, Qt::AlignLeft);
    series->attachAxis(axisy);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->myplot->setChart(chart);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// take a date string in format YYYYMMDD and return a date string in format MM/DD/YY
string to_fdate(string s) {
    s = s[4]+s[5]+'/'+s[6]+s[7]+'/'+s[2]+s[3];
    return s;
}

void MainWindow::draw_pie(vector<int>& v2, string a, string b) {
    cout << "a: " << a << "\tb: " << b << endl;
    QPieSeries *pseries = new QPieSeries();
    ifstream f;
    string line,line2;
    stringstream ss;
    f.open("categories.txt");
    getline(f,line);
    while(getline(f,line))  {
        ss.clear();
        ss.str("");
        ss<<line;
        getline(ss,line,',');
        getline(ss,line2,',');
        pseries->append(QString::fromStdString(line2), v2[stoul(line)]);
    }

    for(int i = 0; i < 13; i++)  {
        QPieSlice *slice = pseries->slices().at(i);
        slice->setLabelVisible();
    }

    QChart *pchart = new QChart();
    pchart->addSeries(pseries);
    pchart->setTitle("Simple piechart example");

    QChartView *cView = new QChartView(pchart);
    cView->setRenderHint(QPainter::Antialiasing);
    ui->myplot_2->setChart(pchart);
}

void MainWindow::bdate_cbox_changed()   {

    ui->comboBox_2->clear();
    string asdf = ui->comboBox->currentText().toStdString();
    auto it = find_if(v.begin(), v.end(),
                      [&asdf](const receipt& r){return r.fdate == asdf;});
    if(it != v.end())   {
        while(it != v.end())    {
            ui->comboBox_2->addItem(QString::fromStdString(it->fdate));
            it++;
        }
    }
}

void MainWindow::item_selected()    {
    string selected_code, compare_code, line;
    selected_code = ui->comboBox_3->currentText().toStdString();
    ifstream f("item_descriptions.txt");
    stringstream ss,ss2;
    ss2<<selected_code;
    ss2>>selected_code;
    while(getline(f,line))  {
        ss.clear();
        ss.str("");
        ss<<line;
        getline(ss, compare_code, ',');
        if(selected_code == compare_code)   {       // found one with a description
            getline(ss, line);
            ui->label->setText(QString::fromStdString(line));
            ui->label->setAlignment(Qt::AlignCenter);
            //cout << line << endl;
            line = "resources/" + selected_code + ".png";
            QPixmap qp = QString::fromStdString(line);
            ui->label_2->setPixmap(qp.scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));
            ui->label_2->setAlignment(Qt::AlignCenter);

            break;
        }
    }
    f.close();

}
