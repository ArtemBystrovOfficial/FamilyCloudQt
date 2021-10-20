#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QFileInfo>
#include <QFileDialog>
#include <QStringList>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>


using namespace std;

set <string> check_adress;
vector < pair < string, string>  > adress;
int adress_size_time = 0;
string s_data;
string s_time_t;
string s_time;
bool key1;
bool key2;
bool key3;
bool key4=false;
bool key5=false;
int k=0;
int it;
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


void MainWindow::on_pushButton_clicked()
{


     QStringList adress_list = QFileDialog::getOpenFileNames(0, "Directory Dialog", "","*.jpg *.png *.bmp");
     for(int i=0; i!=adress_list.size();i++)
     {
     s_data=adress_list[i].toStdString();

     check_adress.insert(adress_list[i].toStdString());
     if(check_adress.size()!=adress_size_time){

         for(int j=0;j < s_data.size(); j++)
         {
             if(s_data[j]== '/' )  it=j;
         }
           QFileInfo fileinfo(adress_list[i]);
           QDateTime last_mod = fileinfo.lastModified();
           k=0;
           key1=false; key2=false; key3=false;
           s_time="";
           s_time_t=last_mod.toString().toStdString();
         for(int j=0;j < s_time_t.size(); j++)
           {
               if(s_time_t[j]==' ')k++;
                if(k==1&&key1==false){s_time+=s_time_t.substr(j+1,3);s_time+=" "; key1=true; }
                if(k==2&&key2==false){
                    if(s_time_t[j+2]==' ')s_time+="0"+s_time_t.substr(j+1,1);
                   else s_time+=s_time_t.substr(j+1,2);s_time+=" ";
                    key2=true;
                }
                if(k==4&&key3==false){s_time+=s_time_t.substr(j+1,4); key3=true;}
           }

        ui->label_6->setText(QString::fromStdString(s_time_t));
         ui->listWidget->addItem(QString::fromStdString(s_data.substr(it+1,s_data.size()-it-1))+" | "+QString::fromStdString(s_time));

         adress.push_back(make_pair(adress_list[i].toStdString(), s_time )    );
     }
     adress_size_time=check_adress.size();
     }
     if(check_adress.size()!=0){
     ui->label_4->setText("Accept");
     ui->label_4->setStyleSheet("color: green");
     key5=true;
   }
}


int d=1;



void MainWindow::on_pushButton_2_clicked()
{
    adress.clear();
    check_adress.clear();
    adress_size_time = 0;
    ui->listWidget->clear();
    ui->label_4->setText("Select");
    ui->label_4->setStyleSheet("color: red");
    ui->label_5->setText("Select");
    ui->label_5->setStyleSheet("color: red");
}

QString fold="";

void MainWindow::on_pushButton_3_clicked()
{
    QString folder = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
      fold=folder;
      ui->label_6->setText(fold);
      if(fold!=""){
          key4=true;
      ui->label_5->setText("Accept");
      ui->label_5->setStyleSheet("color: green");
      }
}

string year,month,day,dot;

void MainWindow::on_pushButton_4_clicked()
{
    if(key4==true&&key5==true){
    ui->label_2->setText("0%");
    QDir dir;
    if(!(dir.exists(fold+"/TEMP")))
    dir.mkdir(fold+"/TEMP");
    for(int i=0;i!=adress.size();i++)
    {
        year=adress[i].second.substr(7,4);
        month=adress[i].second.substr(0,3);
        day=adress[i].second.substr(4,2);

        if(!(dir.exists(fold+"/TEMP/"+QString::fromStdString(year))))
        dir.mkdir(fold+"/TEMP/"+QString::fromStdString(year));

        if(!(dir.exists(fold+"/TEMP/"+QString::fromStdString(year)+"/"+QString::fromStdString(month))))
        dir.mkdir(fold+"/TEMP/"+QString::fromStdString(year)+"/"+QString::fromStdString(month));

        if(!(dir.exists(fold+"/TEMP/"+QString::fromStdString(year)+"/"+QString::fromStdString(month)+"/"+QString::fromStdString(day))))
        dir.mkdir(fold+"/TEMP/"+QString::fromStdString(year)+"/"+QString::fromStdString(month)+"/"+QString::fromStdString(day));

        if (!QFile(QString::fromStdString(adress[i].first)).exists()) {
              QMessageBox::critical(this,"Error", "Файлы потеряны, провертье целостность файлов или утечки");

          }else{
            for(int j=0;j<adress[i].first.size();j++)
            {
                if(adress[i].first[j]=='.')
                {
                    dot=adress[i].first.substr(j,adress[i].first.size()-j);
                    break;
                }
            }
            QFile::copy(QString::fromStdString(adress[i].first),fold+"/TEMP/"+
                        QString::fromStdString(year)+"/"+QString::fromStdString(month)+"/"+
                        QString::fromStdString(day)+"/"+QString::fromStdString(year+"_"+month+"_"+day+"-"+to_string(d))
                        +QString::fromStdString(dot));

        }
        d++;
        int h = int(double((i+1)/adress.size())*100);
        ui->label_2->setText(QString::fromStdString(to_string(h)+"%"));



    }

    adress.clear();
    check_adress.clear();
    adress_size_time = 0;
    ui->listWidget->clear();
    ui->label_4->setText("Select");
    ui->label_4->setStyleSheet("color: red");
    ui->label_5->setText("Select");
    ui->label_5->setStyleSheet("color: red");
    QMessageBox::about(this,"Complete", "Программа выполнена успешно");
    key4=false;
    key5=false;
    }
    else{
        QMessageBox::critical(this,"Error", "Выберите все данные");
    }
}


void MainWindow::on_progressBar_valueChanged(int value)
{

}
void MainWindow::on_pushButton_5_clicked()
{
    QApplication::quit();
}

