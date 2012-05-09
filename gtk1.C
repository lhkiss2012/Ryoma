#define GTK_ENABLE_BROKEN 

#include<gtk/gtk.h> 

#include<stdio.h> 

#include"dirent.h" 

#include"unistd.h" 

#include"sys/file.h" 

#include"fcntl.h" 

#include"string.h" 

#include"time.h" 

#include"math.h" 

#include<stdlib.h> 

#include<sys/time.h> 

#include<gdk/gdk.h> 

#define PMAX     100 //最大进程数目 

char *title[6]={" 资源信息 "," 进程信息 "," 系统信息"}; 

GtkWidget *window;//主窗口 

GtkWidget *notebook;//notebook控件 

GtkWidget *vbox; 

GtkWidget *hbox; 

GtkWidget *label; 

GtkWidget *cpu_bar; 
 
GtkWidget *table1[5];//定义表格 

GtkWidget *frame[5];//定义框架 

GtkWidget *frame0; 

GtkWidget *button[6];//定义标签 

gint length; 

GtkWidget *CreateMenuItem(GtkWidget *,char *);//创建菜单项函数 

GtkWidget *CreateMenuHelp(GtkWidget *);//创建菜单Help函数 

void notebook_cpu_init(void);//cpu页面初始化 


/*回调函数，退出窗口管理程序*/ 

void delete_event(GtkWidget *window,gpointer data){ 

 gtk_main_quit(); 

} 

int select_name(char name[]){ 

 int i; 

 for(i=0;name[i]!=0;i++) 

  if(isalpha(name[i])||name[i]=='.') 

  return 0; 

 return 1; 

} 

/*主函数*/
int main(int argc,char *argv[]){ 

 gint i; 

 int v,v0; 

 int timer; 

 GtkWidget *label2,*label; 

 GtkWidget *label0[5]; 

 GtkWidget *text; 

 gpointer date,data; 

 gdouble value1,value2; 

 gpointer gdata; 

 GtkWidget *label3; 

 GtkWidget *button1;  
 
 GtkWidget *vscrollbar,*hscrollbar;//定义滚动条 

 GtkWidget *MenuBar;//定义菜单栏 

 GtkWidget *MenuItemFile,*MenuItemShutDown,*MenuItemHelp; 
 
 gtk_set_locale (); 

 gtk_init(&argc,&argv);//在任何构件生成之前完成 

 memset (pfuser, 0 ,sizeof (pfuser)); 

 

 window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//创建主窗口 

 gtk_window_set_title(GTK_WINDOW(window),"---------linux任务管理器-----------");//设置窗口标题 

 gtk_widget_set_usize(window, 600, 500);//设置窗口大小  

 gtk_window_set_resizable (GTK_WINDOW (window), TRUE);// 窗口大小可改变（TRUE） 

 gtk_container_set_border_width(GTK_CONTAINER(window),5);//设置窗口边框宽度 

 gtk_widget_show(window); 

 

 table=gtk_table_new(12,11,TRUE);//创建表格12行*10列 

 gtk_widget_show(table); 

 gtk_container_add(GTK_CONTAINER(window),table);//将table装进窗口  

 

 notebook=gtk_notebook_new();//创建notebook 

 gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);//设置notebook的格式 

 gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 11, 1, 11);//将notebook加入表格中 

 gtk_widget_show(notebook); 

 /*创建notebook的每一页*/ 

 for(i=0;i<5;i++){    

  label0[i]=gtk_label_new(title[i]);//notebook页面标题            

  frame[i]=gtk_frame_new(NULL);//页面框架 

  gtk_container_set_border_width (GTK_CONTAINER (frame[i]), 10);//框架与边缘的距离 

  gtk_frame_set_shadow_type (GTK_FRAME (frame[i]),GTK_SHADOW_ETCHED_OUT);//框架的阴影模式 

  gtk_widget_set_size_request(frame[i],450,450);//框架大小 

  gtk_widget_show(frame[i]); 

  gtk_widget_show (label0[i]); 

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook),frame[i],label0[i]);//创建notebook的第i页   

  table1[i]=gtk_table_new(12,11,TRUE);//创建表格12行*11列 

  gtk_widget_show(table1[i]); 

  gtk_container_add(GTK_CONTAINER(frame[i]),table1[i]);//将表格tbale1放入框架 
 } 
 
 MenuBar=gtk_menu_bar_new();//创建菜单栏 

 gtk_table_attach_defaults(GTK_TABLE(table),MenuBar,0,11,0,1);//将菜单栏加入表格 

 MenuItemFile=CreateMenuItem(MenuBar,"文件");//增加菜单项 

  MenuItemHelp=CreateMenuItem(MenuBar,"帮助");//增加菜单项 

  gtk_widget_show(MenuBar); 

 

    process_label=gtk_label_new("");//创建显示进程数的标签 

    gtk_widget_show(process_label); 
    
//    timer=gtk_timeout_add(1000,(GtkFunction)process_num,data);//加一个定时器(timer),每隔１秒调用一次(GtkFunction)process_num函数 

    gtk_table_attach_defaults(GTK_TABLE(table),process_label,0,2,11,12);//在状态栏中显示进程总数 

     cpu_rate_label=gtk_label_new(" ");//创建显示cpu占用率的标签 

    gtk_widget_show(cpu_rate_label); 

 gtk_table_attach_defaults(GTK_TABLE(table),cpu_rate_label,2,5,11,12);//在状态栏中显示cpu占用率 
    
 cpu_bar=gtk_progress_bar_new();//创建CPU进度条 

 gtk_widget_show(cpu_bar); 
 notebook_cpu_init(); 
 
 gtk_signal_connect(GTK_OBJECT(window),"delete_event",GTK_SIGNAL_FUNC(delete_event),NULL); 

  gtk_main(); 
} 


/*cpu页面初始化*/ 

void notebook_cpu_init(void){ 

   float v,v0;    
   char text[20];
   char text0[20]; 

   gfloat value1,value2; 

 

   vbox = gtk_vbox_new (FALSE, 0);//添加纵向盒子 

   gtk_widget_show (vbox); 

   gtk_table_attach_defaults(GTK_TABLE(table1[0]),vbox,0,12,0,12); 

 

   frame0 = gtk_frame_new ("CPU");//添加用于显示CPU信息的边框构件 

   gtk_widget_show (frame0); 

   gtk_box_pack_start (GTK_BOX (vbox), frame0, FALSE, FALSE, 0);//加到盒子中 

   gtk_container_add (GTK_CONTAINER (frame0),cpu_bar);        

} 

/*创建菜单项*/ 

GtkWidget *CreateMenuItem(GtkWidget *MenuBar,char *test){ 

     GtkWidget *MenuItem; 

     MenuItem=gtk_menu_item_new_with_label(test);//创建根菜单项 

    gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar),MenuItem);//把根菜单和菜单栏连在一起 

   gtk_widget_show(MenuItem);//显示根菜单 

     return MenuItem; 

} 

