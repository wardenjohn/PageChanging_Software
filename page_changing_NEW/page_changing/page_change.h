#ifndef PAGE_CHANGE_H
#define PAGE_CHANGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTime>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdlib.h>

#include <fstream>
#include <time.h>

#define M_count 4
#define page_list 32
#define instruction_number 10
#define tar 2
//#define wait_time 10//程序暂停时间
#define all_instryction 320

typedef struct ins
{
    int order;
    int used;
}ins;

typedef struct PAGE
{
    int pag;   //show each unit containing the page number
    int targe;//to show if this page is page-missing
    ins instructions[instruction_number];//each page will have 10 instructions
}pagest;

typedef struct MEM
{
    int M_number;//used to show this physic memory is now containing which page
    int time;    //is time
    int using_time;
    int is_get; //the flag that show if we have found it
    int A;
    int changed;
}mem;




namespace Ui {
class page_change;
}

class page_change : public QMainWindow
{
    Q_OBJECT

public:
    explicit page_change(QWidget *parent = 0);
    ~page_change();

public slots:
    void show_FAQ();
    void start_porgram();
    void xue_zha();
private:
    Ui::page_change *ui;
};


class pro4
{

private:
pagest pagelist[page_list];//pagelist means to the calling pages ,here ,we use to store the pages
mem M[M_count];
int rand_flag;
public:
int search_oldest();
void inputdata(Ui::page_change *k);
int search_blank_mem();
int search_get(int find);
void FIFO(Ui::page_change *k);
void LRU(Ui::page_change *k);
void OPT(Ui::page_change *k);
void LFU(Ui::page_change *k);
void NRU(Ui::page_change *k);
void print(int count_missing,Ui::page_change *k);
int search_latest();
void change_states(Ui::page_change *k);
void initial_all_instructrion(void);
int complete(void);
int get_rand_pos(int pos);
void get_order_list(int order_list[]);
void change_show_list(QString *show_page_0,QString *show_page_1,QString *show_page_2,QString *show_page_3);
void change_show_list_LRU(QString *show_page_0,QString *show_page_1,QString *show_page_2,QString *show_page_3);
void change_states_LRU(Ui::page_change *k);
void change_show_list_OPT(QString *show_page_0,QString *show_page_1,QString *show_page_2,QString *show_page_3);
void change_states_OPT(Ui::page_change *k);
void change_states_LFU(Ui::page_change *k);
void change_states_NRU(Ui::page_change *k);
};

#endif // PAGE_CHANGE_H
