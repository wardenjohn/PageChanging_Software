#include "page_change.h"
#include "ui_page_change.h"

int order_list[all_instryction];//={70,0,10,20,0,30,0,40,20,30,0,30,20,10,20,0,10,70,0,10};
int wait_time=0;
page_change::page_change(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::page_change)
{
    ui->setupUi(this);
    connect(ui->FAQ,SIGNAL(clicked()),this,SLOT(show_FAQ()));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(start_porgram()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(xue_zha()));
    //ui->lineEdit->setText("0~31");
}

void page_change::xue_zha()
{
    QString str="恩恩，毕竟书上很喜欢那种取极端的情况。其实这里的情况已经算是蛮极端的了，随机取数。\n就是在这种极端的情况下面，使得很多算法都退化了，所以导致后面缺页率很接近的现象。\n"
                "当然，虽然缺页率在非常离散的情况下比较接近，但是我们还是可以发现页面置换的策略是不一样的，把速度调慢点，你应该会发现"
                "选择置换的页面是不一样的。所以缺页率近似的罪非祸首应该就是过于离散的指令序列了吧？是吗？^_^";
    QMessageBox mes(QMessageBox::NoIcon,"学渣分析",str);
    mes.exec();
}

void page_change::show_FAQ()
{
    QString str;
    str = "1.程序左上的“开始”按钮开始运行程序\n\n2.在你开始程序之前，请输入运行时间，以毫秒(ms)为单位\n\n3.在开始程序以后，将会显示出相关信息\n\n4.该程序目前还会出现错位现象，请谅解\n\n5.“**”表示该物理块为空或者没有新加入的页面";
    QMessageBox mes(QMessageBox::NoIcon,"FAQ",str);
    mes.exec();
}

//************************************************************************

void pro4::change_states(Ui::page_change *k)//showing the pagestate
{
    QString page_state;

    page_state =QString::number(M[0].M_number);
    k->page0->setText(page_state);
    page_state =QString::number(M[1].M_number);
    k->page1->setText(page_state);
    page_state =QString::number(M[2].M_number);
    k->page2->setText(page_state);
    page_state =QString::number(M[3].M_number);
    k->page3->setText(page_state);
}

void pro4::change_states_LRU(Ui::page_change *k)
{
    QString page_state;

    page_state =QString::number(M[0].M_number);
    k->LRU_page_0->setText(page_state);
    page_state =QString::number(M[1].M_number);
    k->LRU_page_1->setText(page_state);
    page_state =QString::number(M[2].M_number);
    k->LRU_page_2->setText(page_state);
    page_state =QString::number(M[3].M_number);
    k->LRU_page_3->setText(page_state);
}

void pro4::change_show_list_OPT(QString *show_page_0,QString *show_page_1,QString *show_page_2,QString *show_page_3)
{

}

void pro4::change_states_LFU(Ui::page_change *k)
{
    QString page_state;

    page_state =QString::number(M[0].M_number);
    k->LFU_page0->setText(page_state);
    page_state =QString::number(M[1].M_number);
    k->LFU_page0_2->setText(page_state);
    page_state =QString::number(M[2].M_number);
    k->LFU_page0_3->setText(page_state);
    page_state =QString::number(M[3].M_number);
    k->LFU_page0_4->setText(page_state);
}

void pro4::change_states_OPT(Ui::page_change *k)
{
    QString page_state;

    page_state =QString::number(M[0].M_number);
    k->OPT_page_0->setText(page_state);
    page_state =QString::number(M[1].M_number);
    k->OPT_page_1->setText(page_state);
    page_state =QString::number(M[2].M_number);
    k->OPT_page_2->setText(page_state);
    page_state =QString::number(M[3].M_number);
    k->OPT_page_3->setText(page_state);
}

void pro4::change_states_NRU(Ui::page_change *k)
{
    QString page_state;

    page_state =QString::number(M[0].M_number);
    k->NRU_page0_0->setText(page_state);
    page_state =QString::number(M[1].M_number);
    k->NRU_page0_1->setText(page_state);
    page_state =QString::number(M[2].M_number);
    k->NRU_page0_2->setText(page_state);
    page_state =QString::number(M[3].M_number);
    k->NRU_page0_3->setText(page_state);
}

void pro4::initial_all_instructrion()
{
    for(int i=0;i<page_list;i++)
    {
        for(int j=0;j<instruction_number;j++)
        {
            pagelist[i].instructions[j].used=0;//所有的指令初始化为未用
        }
    }
}

void pro4::inputdata(Ui::page_change *k)//initial funtion
{
    int amount_of_instructions=0;

    for(int i=0;i<page_list;i++)
    {
        //std::cin>>pagelist[i].pag;    //for each node , there is a page number that need to use
        pagelist[i].pag=i;
        pagelist[i].targe=0;         //for this targe , it is used to target the missing pages
        for(int j=0;j<instruction_number;j++)
        {
            pagelist[i].instructions[j].order=amount_of_instructions;
            amount_of_instructions++;
        }//for each page , we need to give the order of the instruction
    }

//initial funtions

    for(int i=0;i<M_count;i++){
        M[i].M_number=-1;
        M[i].time=0;
        M[i].using_time=0;
    }                     //initial all the physic pages are blank

    initial_all_instructrion();
    change_states(k);
}
////////////////////////////////////////////////
int pro4::search_get(int find)//查找是否缺页
{
    int flag=0;
    for(int i=0;i<M_count;i++)
    {
        if(M[i].M_number==find){
            flag=1;
            break;
        }

    }
    return flag;//如果找到了，返回1
}

int pro4::search_blank_mem()
{
    int pos=-1;
    for(int i=0;i<M_count;i++)
    {
        if(M[i].M_number==-1)
        {
            pos=i;
            break;
        }
    }
    return pos;
}

int pro4::search_oldest()
{
    int max=0;
    int pos;
    for(int i=0;i<M_count;i++)
    {
        if(max<M[i].time){
            max = M[i].time;
            pos = i;
        }
    }
    return pos;
}

/*
void pro4::print(int count_missing,Ui::page_change *k)
{
    float ans;
    ans = (count_missing*1.0)/page_list;


    QString stat_head = "Pages :";
    for(int i=0;i<page_list;i++)
    {
        //std::cout<<pagelist[i].pag<<"   ";
        stat_head+=QString::number(pagelist[i].pag)+"   |";
    }


    stat_head+="\n";
    stat_head+="Mistar :";

    for(int i=0;i<page_list;i++)
    {
        if(pagelist[i].targe==1)
            stat_head+="*   |";
        else
            stat_head+="      |";
    }

    stat_head+="\n";
    stat_head+="the rate of missing pages is"+QString("%2").arg(ans);
    k->textBrowser->setText(stat_head);
}*/

void pro4::get_order_list(int order_list[])
{
    srand((unsigned)time(NULL));
    int check_list[320];
    for(int i=0;i<320;i++)
    {
        check_list[0]=0;
    }
    order_list[0] = rand()%320;
    for(int i=1;i<320;i++)
    {
        order_list[i] = get_rand_pos(order_list[i-1]);
    }
    for(int i=0;i<320;i++)
    {
        std::cout<<order_list[i]<<"..."<<i<<std::endl;
    }
}

void pro4::change_show_list(QString *show_page_0,QString *show_page_1,QString *show_page_2,QString *show_page_3)
{
    if(M[0].M_number>=10)
    {
        *show_page_0+=QString::number(M[0].M_number)+"  ";
    }
    else {
        if(M[0].M_number!=-1)
            *show_page_0+="0"+QString::number(M[0].M_number)+"  ";
        else
            //*show_page_0+=QString::number(M[0].M_number)+"  ";
            *show_page_0+="**  ";
    }

    if(M[1].M_number>=10)
    {
        *show_page_1+=QString::number(M[1].M_number)+"  ";
    }
    else{
        if(M[1].M_number!=-1)
            *show_page_1+="0"+QString::number(M[1].M_number)+"  ";
        else
            //*show_page_1+=QString::number(M[1].M_number)+"  ";
            *show_page_1+="**  ";
    }

    if(M[2].M_number>=10)
    {
        *show_page_2+=QString::number(M[2].M_number)+"  ";
    }
    else{
        if(M[2].M_number!=-1)
            *show_page_2+="0"+QString::number(M[2].M_number)+"  ";
        else
            //*show_page_2+=QString::number(M[2].M_number)+"  ";
            *show_page_2+="**  ";
    }

    if(M[3].M_number>=10)
    {
        *show_page_3+=QString::number(M[3].M_number)+"  ";
    }
    else{
        if(M[3].M_number!=-1)
            *show_page_3+="0"+QString::number(M[3].M_number)+"  ";
        else
            //*show_page_3+=QString::number(M[3].M_number)+"  ";
            *show_page_3+="**  ";
    }
}


//改变控件的信息条，控件是唯一对待的,把对应的信息条自加，保存及添加信息
void pro4::change_show_list_LRU(QString *show_page_0,QString *show_page_1,QString *show_page_2,QString *show_page_3)
{
    if(M[0].M_number>=10)
    {
        *show_page_0+=QString::number(M[0].M_number)+"  ";
    }
    else {
        if(M[0].M_number!=-1)
            *show_page_0+="0"+QString::number(M[0].M_number)+"  ";
        else
            *show_page_0+=QString::number(M[0].M_number)+"  ";
    }

    if(M[1].M_number>=10)
    {
        *show_page_1+=QString::number(M[1].M_number)+"  ";
    }
    else{
        if(M[1].M_number!=-1)
            *show_page_1+="0"+QString::number(M[1].M_number)+"  ";
        else
            *show_page_1+=QString::number(M[1].M_number)+"  ";
    }

    if(M[2].M_number>=10)
    {
        *show_page_2+=QString::number(M[2].M_number)+"  ";
    }
    else{
        if(M[2].M_number!=-1)
            *show_page_2+="0"+QString::number(M[2].M_number)+"  ";
        else
            *show_page_2+=QString::number(M[2].M_number)+"  ";
    }

    if(M[3].M_number>=10)
    {
        *show_page_3+=QString::number(M[3].M_number)+"  ";
    }
    else{
        if(M[3].M_number!=-1)
            *show_page_3+="0"+QString::number(M[3].M_number)+"  ";
        else
            *show_page_3+=QString::number(M[3].M_number)+"  ";
    }
}



void pro4::FIFO(Ui::page_change *k)
{
    QTime t;
    QString showing="";
    QString show_page_0="";
    QString show_page_1="";
    QString show_page_2="";
    QString show_page_3="";
    QString new_page="";
    int count_missing = 0;
    int count = 0;
    int search_order = 0;
    //int order_list[all_instryction];

    srand((unsigned)time(NULL));
    k->Model->setText("FIFO");

    //get_order_list(order_list);
    //QPalette pal_0 = k->FIFO_show_page_0->

    show_page_0+="**  ";
    show_page_1+="**  ";
    show_page_2+="**  ";
    show_page_3+="**  ";
    new_page+="**  ";

    for(int i=0;i<M_count;i++){
        M[i].M_number=-1;
        M[i].time=0;
        M[i].using_time=0;
    }


    for(int i=0;i<all_instryction;i++)
    {
        int page = order_list[i]/10;
        int order = order_list[i] - page*10;

        int is_find = search_get(page);

        if(is_find)
        {
            for(int j=0;j<M_count;j++)
            {
                M[j].time++;//所有的物理块的时间+1
            }
           // break;
            new_page+="**  ";

            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
        }//in Memory

        else{

            count_missing++;   //this page not in memory ,missing page

            //pagelist[i].targe=1;//missing page
            int is_blank = search_blank_mem();

            if(is_blank!=-1)//如果不等于-1说明返回的是空白物理块的地址
            {
                M[is_blank].M_number = page;
                M[is_blank].time=0;

                for(int j=0;j<M_count;j++)
                if(j!=is_blank)
                M[j].time++;

                change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);

            }//have blank physic memory

            else{

                int pos = search_oldest();

                M[pos].M_number = page;
                M[pos].time =0;

                for(int j=0;j<M_count;j++)
                if(j!=pos)
                M[j].time++;

                showing+="interviewing Page:"+QString::number(page)+";missing page\n";
            //////print//////////////////////////////////////////////////////////////////
                change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
            }
            //have no blank memory,use FIFO
            if(page>=10){
                new_page+=QString::number(page)+"  ";
            }
            else{
                new_page+="0"+QString::number(page)+"  ";
            }
        }
        count++;

        change_states(k);
        //k->textBrowser->setText(showing);
        //k->textBrowser->moveCursor(QTextCursor::End);

        k->FIFO_NEW_page->setText(new_page);
        k->FIFO_show_page_0->setText(show_page_0);
        k->FIFO_show_page_1->setText(show_page_1);
        k->FIFO_show_page_2->setText(show_page_2);
        k->FIFO_show_page_3->setText(show_page_3);
        k->FIFO_show_page_0->setAlignment(Qt::AlignRight);
        k->FIFO_show_page_1->setAlignment(Qt::AlignRight);
        k->FIFO_show_page_2->setAlignment(Qt::AlignRight);
        k->FIFO_show_page_3->setAlignment(Qt::AlignRight);
        k->FIFO_NEW_page->setAlignment(Qt::AlignRight);

        t.start();
        while(t.elapsed()<wait_time)
            QApplication::processEvents();

    //main algorithm
    }

    //print(count_missing,k);
    k->missingrate_FIFO->setText(QString::number(count_missing*1.0/all_instryction));
}


void page_change::start_porgram()
{
        QTime t;
        pro4 start;
        //start.inputdata(ui);
        int choice;
        QString show_list="";

        choice = ui->lineEdit_2->text().toInt();
        wait_time =choice;
        if(wait_time<=0)
        {
            ui->lineEdit_2->setText("无效输入！");
            goto again;
        }

        wait_time = choice;

        start.get_order_list(order_list);



        for(int i=0;i<all_instryction;i++){
            show_list+=QString::number(order_list[i]/10)+" ";
        }

        ui->textEdit->setText(show_list);
        ui->textEdit->setWordWrapMode(QTextOption::NoWrap);


        start.FIFO(ui);
        start.LRU(ui);
        start.OPT(ui);
        start.LFU(ui);
        start.NRU(ui);

        again:
        if(wait_time<=0)
            ui->lineEdit_2->setText("无效输入");

}

int pro4::complete()
{
    int s=0;
    for(int i=0;i<page_list;i++)
    {
        for(int j=0;j<instruction_number;j++)
        {
            if(pagelist[i].instructions[j].used==0)
            {
                s=1;
                break;
            }
        }
        if(s==1)
            break;
    }
    return s;//如果完成的话，返回0，未完成返回1
}

//********************************************After testing
int pro4::get_rand_pos(int pos)
{
    if(this->rand_flag==0)//寻址低地址段
    {
        this->rand_flag=1;
        return (rand())%pos;
    }

    else//寻址高地址段
    {
        this->rand_flag=0;
        return rand()%(320-pos)+pos;
    }
}



void pro4::LRU(Ui::page_change *k)
{
    QTime t;
    QString showing="";
    QString show_page_0="";
    QString show_page_1="";
    QString show_page_2="";
    QString show_page_3="";
    QString new_page="";
    int count_missing = 0;
    int count = 0;
    //int order_list[320];
    int page=0,order=0;

    show_page_0+="**  ";
    show_page_1+="**  ";
    show_page_2+="**  ";
    show_page_3+="**  ";
    new_page+="**  ";

    srand((unsigned)time(NULL));
    k->Model_2->setText("LRU");

    for(int i=0;i<M_count;i++)
    {
        M[i].M_number=-1;
    }
    for(int i=0;i<M_count;i++){
        M[i].is_get=0;
    }

    //get_order_list(order_list);

    for(int i=0;i<all_instryction;i++)
    {
        //std::cout<<"hello?"<<std::endl;
        page = order_list[i]/10;
        order = order_list[i]-page*10;//把随机数产生的那个指令地址翻译成页与页内偏移

        int is_find = search_get(page);//是否缺页

        if(is_find){

            for(int i=0;i<M_count;i++)
            {
                if(M[i].M_number==page)
                {
                    M[i].time=0;
                }
                else
                {
                    M[i].time++;
                }
            }
            change_states_LRU(k);
            showing+="interviewing Page:"+QString::number(page)+";not missing\n";
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
            new_page+="**  ";
        }

        else{
            count_missing++;

            //pagelist[i].targe=1;
            int is_blank = search_blank_mem();

            if(is_blank != -1){
                M[is_blank].M_number = page;
                M[is_blank].time = 0;

            }//have blank mem

            else{//have no blank memeory
                int max=0;
                int locate=0;//用于记录time最大的哪一个页，用来找出醉酒没有使用的
                for(int i=0;i<M_count;i++)
                {
                    if(M[i].time>max)
                    {
                        locate=i;
                        max = M[i].time;
                    }

                }

                for(int i=0;i<M_count;i++)
                {
                    M[i].time++;
                }
                M[locate].M_number = page;
                M[locate].time=0;//更新

            }//have no blank mem,kernel algorithm,finding the oldest one didt used

            change_states_LRU(k);
            showing+="interviewing Page"+QString::number(page)+";missing\n";
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
            if(page>=10){
                new_page+=QString::number(page)+"  ";
            }
            else{
                new_page+="0"+QString::number(page)+"  ";
            }
        }

        k->LRU_NEW_Page->setText(new_page);
        k->LRU_show_page_0->setText(show_page_0);
        k->LRU_show_page_1->setText(show_page_1);
        k->LRU_show_page_2->setText(show_page_2);
        k->LRU_show_page_3->setText(show_page_3);
        k->LRU_NEW_Page->setAlignment(Qt::AlignRight);
        k->LRU_show_page_0->setAlignment(Qt::AlignRight);
        k->LRU_show_page_2->setAlignment(Qt::AlignRight);
        k->LRU_show_page_3->setAlignment(Qt::AlignRight);
        k->LRU_show_page_1->setAlignment(Qt::AlignRight);


        t.start();
        while(t.elapsed()<wait_time)
            QCoreApplication::processEvents();

    }
    //print(count_missing,k);
    float missrate = count_missing*1.0/(page_list*instruction_number);
    k->missingrate_LRU->setText(QString::number(missrate));
}

int pro4::search_latest()
{
    int max=0;
    int pos=0;
    for(int m=0;m<M_count;m++){
        if(M[m].time>max&&M[m].time!=0){
            max=M[m].time;
            pos = m;
        }//find the one that have the biggest time to now
        else if(M[m].is_get==0){
            pos=m;
            break;
        }//is_get == 0 shows that it will not appear again
        else{

        }
    }

    return pos;
}

void pro4::OPT(Ui::page_change *k)
{
    QTime t;
    QString showing="**  ";
    QString show_page_0="**  ";
    QString show_page_1="**  ";
    QString show_page_2="**  ";
    QString show_page_3="**  ";
    QString new_page="**  ";
    int count_missing = 0;
    int count = 0;
    //int order_list[all_instryction];

    srand((unsigned)time(NULL));
    k->Model_3->setText("OPT");

    //get_order_list(order_list);

    for(int i=0;i<M_count;i++){
        M[i].is_get = 0;
        M[i].M_number=-1;
    }

    for(int i=0;i<all_instryction;i++)
    {
        int page = order_list[i]/10;
        int order = order_list[i] - page*10;

        int is_find = search_get(page);
        //to find if it is already in memory

        if(is_find){
            showing+="interviewing Page:"+QString::number(page)+";not missing\n";
            change_states_OPT(k);
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
            new_page+="**  ";
        }

        else{

            count_missing++;

            //pagelist[i].targe=1;
            int is_blank = search_blank_mem();

            if(is_blank != -1){
                M[is_blank].M_number = page;
                M[is_blank].time = 0;
            }//have blank mem

            else{

                for(int m=0;m<M_count;m++)
                {
                    M[m].is_get=0;
                }

                for(int count=i+1;count<all_instryction;count++){//从现在的i往后数
                    for(int m=0;m<M_count;m++){//对比物理块中的页面号，order_list[count]/10是找到现在count对应的哪一个指令所在的页面
                        if(M[m].M_number == order_list[count]/10&&M[m].is_get!=1){
                            M[m].time = count -i;//如果后面找到了需要访问的页面，就把他的距离时间算出来
                            M[m].is_get = 1;//标记为已找到
                        }
                    }

                    int flag=1;

                    for(int m=0;m<M_count;m++){
                        if(M[m].is_get==0){
                            flag=0;
                            break;
                        }
                    }//提高效率，免除不必要的循环
                    if(flag==1)//如果所有物理块都在未来找到了的话，就直接退出循环了，否则就要一直找下去
                        break;
                }//find the latest one

                int pos = search_latest();
                M[pos].M_number = page;

                for(int m=0;m<M_count;m++){
                    M[m].time = 0;
                    M[m].is_get = 0;
                }
            }//have no blank mem,kernel algorithm


            showing+="interviewing Page:"+QString::number(page)+";missing\n";
            change_states_OPT(k);
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
            if(page>=10){
                new_page+=QString::number(page)+"  ";
            }
            else{
                new_page+="0"+QString::number(page)+"  ";
            }
        }

        k->OPT_NEW_Page->setText(new_page);
        k->OPT_show_page_0->setText(show_page_0);
        k->OPT_show_page_1->setText(show_page_1);
        k->OPT_show_page_2->setText(show_page_2);
        k->OPT_show_page_3->setText(show_page_3);
        k->OPT_NEW_Page->setAlignment(Qt::AlignRight);
        k->LRU_show_page_0->setAlignment(Qt::AlignRight);
        k->LRU_show_page_1->setAlignment(Qt::AlignRight);
        k->LRU_show_page_2->setAlignment(Qt::AlignRight);
        k->LRU_show_page_3->setAlignment(Qt::AlignRight);

        t.start();
        while(t.elapsed()<wait_time)
            QApplication::processEvents();
    }
    //print(count_missing,k);

    k->missingrate_OPT->setText(QString::number(count_missing*1.0/all_instryction));
}

//********************************************
//LFU

void pro4::LFU(Ui::page_change *k)
{
    //have pages,haveMem
    QTime t;
    QString showing="";
    QString show_page_0="**  ";
    QString show_page_1="**  ";
    QString show_page_2="**  ";
    QString show_page_3="**  ";
    QString new_page="**  ";
    int i=0;
    int count_missing=0;//用来计算缺页次数，计算缺页率的
    int inpos=0;   //inspos是用来存放随机数产生的指令地址
    int page = 0,miss=0;
    this->rand_flag=0;
    //int order_list[all_instryction];

    k->Model_4->setText("LFU");

    srand((unsigned)time(NULL));

    for(int i=0;i<M_count;i++){
        M[i].M_number=-1;
        M[i].time=0;
        M[i].using_time=0;
    }
    //int t=0;

    //get_order_list(order_list);

    for(int i=0;i<all_instryction;i++)
    {
        page = order_list[i]/10;
        inpos = order_list[i] - 10*page;

        miss = search_get(page);//if miss==1 ,means find if in memory

        if(miss)//find it
        {
            for(int i=0;i<M_count;i++)
            {
                M[i].time++;
            }

            for(int i=0;i<M_count;i++)
            {
                if(M[i].M_number==page)
                {
                    M[i].using_time++;
                    break;
                }
            }

            new_page+="**  ";
            change_states_LFU(k);
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
        }
        else//miss pages
        {
            int flag=0;
            count_missing++;
            for(int i=0;i<M_count;i++)
            {
                if(M[i].M_number==-1)
                {

                    M[i].M_number=page;
                    M[i].using_time=0;
                    M[i].using_time++;
                    flag=1;
                    break;
                }//缺页，有空闲物理块

            }

            if(flag!=1)//没有空闲物理块
            {
                int pos_wu=0;
                int min=999;
                for(int i=0;i<M_count;i++)//找出最不常使用的哪一个物理块
                {
                    if(M[i].using_time<min)
                    {
                        min=M[i].using_time;
                        pos_wu=i;
                    }
                }

                M[pos_wu].M_number = page;
                M[pos_wu].using_time=0;
                M[pos_wu].using_time++;
                M[pos_wu].time=0;//把该物理块换成我需要的页面

            }//缺页，但是没有空闲物理块,这个时候需要LFU算法


            if(page>=10)
            {
                new_page+=QString::number(page)+"  ";
            }
            else{
                new_page+="0"+QString::number(page)+"  ";
            }
            change_states_LFU(k);
            showing+="Interviewing Pages"+QString::number(page)+":missing\n";
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
        }



        k->LFU_NEW_page->setText(new_page);
        k->LFU_show_page_0->setText(show_page_0);
        k->LFU_show_page_1->setText(show_page_1);
        k->LFU_show_page_2->setText(show_page_2);
        k->LFU_show_page_3->setText(show_page_3);
        k->LFU_NEW_page->setAlignment(Qt::AlignRight);
        k->LFU_show_page_0->setAlignment(Qt::AlignRight);
        k->LFU_show_page_1->setAlignment(Qt::AlignRight);
        k->LFU_show_page_2->setAlignment(Qt::AlignRight);
        k->LFU_show_page_3->setAlignment(Qt::AlignRight);

        t.start();
        while(t.elapsed()<wait_time)
            QCoreApplication::processEvents();


    }

    float mr = count_missing*1.0/320;
    QString misrate = QString::number(mr);
    k->missingrate_LFU->setText(misrate);
}


//**********************************************
//NRU
//???
void pro4::NRU(Ui::page_change *k)
{
    QTime t;
    QString showing="";
    k->Model_5->setText("NRU");
    QString show_page_0="**  ";
    QString show_page_1="**  ";
    QString show_page_2="**  ";
    QString show_page_3="**  ";
    QString new_page="**  ";
    //int order_list[all_instryction];
    int pointer = 0;//指针位置
    int flag_blank=0;//用来判断是不是已经是有空闲物理块的
    int miss=0;//用来判断是否缺页的
    int miss_count=0;//用来计数缺页次数

    //get_order_list(order_list);

    for(int i=0;i<M_count;i++)
    {
        M[i].M_number=-1;
        M[i].changed =0;
    }//初始化

    for(int i=0;i<all_instryction;i++)
    {
        miss=0;
        int page = (order_list[i]+1)/10;
        int inpos = (order_list[i]+1) - page*10;

        for(int j=0;j<M_count;j++)
        {
            if(M[j].M_number==page)//没有缺页
            {
                miss =1;
                M[j].A=1;
                break;
                //new_page+="**"+"  ";
            }
        }


        if(miss==1)
        {
            change_states_NRU(k);
            new_page+="**  ";
            showing+="interviewing Page:"+QString::number(page)+";not missing\n";
            change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);
        }//没有缺页


        else{

            miss_count++;

            if(M[pointer].M_number==-1){
                M[pointer].M_number=page;
                M[pointer].A=0;
                M[pointer].changed=0;

                showing+="Load Page"+QString::number(page)+"in blank Memory\n";

                showing+="running instruction :"+QString::number(page*10+inpos)+"\n";

                pointer = (pointer+1)%M_count;
            }//说明指针所指物理块现在是空白的

            else{
                if(M[pointer].A==1)
                {
                    M[pointer].A=0;
                }

                for(int tem=0;tem<M_count-1;tem++)
                {
                    if(M[pointer].A==0)
                    {
                        M[pointer].M_number = page;
                        M[pointer].A = 1;

                        pointer = (pointer+1)%M_count;
                    }//change out
                    else {
                        pointer = (pointer+1)%M_count;
                    }
                }
            }

            showing+="interviewing Page:"+QString::number(page)+";missing page \n";
            showing+="running instrtction:"+QString::number(page*10+inpos)+"\n";
            if(page>=10)
            {
                new_page+=QString::number(page)+"  ";
            }
            else{
                new_page+="0"+QString::number(page)+"  ";
            }
        }//缺页了




        change_states_NRU(k);
        change_show_list(&show_page_0,&show_page_1,&show_page_2,&show_page_3);

        k->NRU_show_page_0->setText(show_page_0);
        k->NRU_show_page_1->setText(show_page_1);
        k->NRU_show_page_2->setText(show_page_2);
        k->NRU_show_page_3->setText(show_page_3);
        k->NRU_NEW_page->setText(new_page);
        k->NRU_show_page_0->setAlignment(Qt::AlignRight);
        k->NRU_show_page_1->setAlignment(Qt::AlignRight);
        k->NRU_show_page_2->setAlignment(Qt::AlignRight);
        k->NRU_show_page_3->setAlignment(Qt::AlignRight);
        k->NRU_NEW_page->setAlignment(Qt::AlignRight);

        t.start();
        while (t.elapsed()<wait_time) {
            QApplication::processEvents();
        }

    }

    k->missingrate_NRU->setText(QString::number(miss_count*1.0/all_instryction));
}

//***********************************************

page_change::~page_change()
{
    delete ui;
}

//70120304230321201701
