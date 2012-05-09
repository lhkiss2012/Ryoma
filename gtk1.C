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

#define PMAX     100 //��������Ŀ 

char *title[6]={" ��Դ��Ϣ "," ������Ϣ "," ϵͳ��Ϣ"}; 

GtkWidget *window;//������ 

GtkWidget *notebook;//notebook�ؼ� 

GtkWidget *vbox; 

GtkWidget *hbox; 

GtkWidget *label; 

GtkWidget *cpu_bar; 
 
GtkWidget *table1[5];//������� 

GtkWidget *frame[5];//������ 

GtkWidget *frame0; 

GtkWidget *button[6];//�����ǩ 

gint length; 

GtkWidget *CreateMenuItem(GtkWidget *,char *);//�����˵���� 

GtkWidget *CreateMenuHelp(GtkWidget *);//�����˵�Help���� 

void notebook_cpu_init(void);//cpuҳ���ʼ�� 


/*�ص��������˳����ڹ�������*/ 

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

/*������*/
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
 
 GtkWidget *vscrollbar,*hscrollbar;//��������� 

 GtkWidget *MenuBar;//����˵��� 

 GtkWidget *MenuItemFile,*MenuItemShutDown,*MenuItemHelp; 
 
 gtk_set_locale (); 

 gtk_init(&argc,&argv);//���κι�������֮ǰ��� 

 memset (pfuser, 0 ,sizeof (pfuser)); 

 

 window=gtk_window_new(GTK_WINDOW_TOPLEVEL);//���������� 

 gtk_window_set_title(GTK_WINDOW(window),"---------linux���������-----------");//���ô��ڱ��� 

 gtk_widget_set_usize(window, 600, 500);//���ô��ڴ�С  

 gtk_window_set_resizable (GTK_WINDOW (window), TRUE);// ���ڴ�С�ɸı䣨TRUE�� 

 gtk_container_set_border_width(GTK_CONTAINER(window),5);//���ô��ڱ߿���� 

 gtk_widget_show(window); 

 

 table=gtk_table_new(12,11,TRUE);//��������12��*10�� 

 gtk_widget_show(table); 

 gtk_container_add(GTK_CONTAINER(window),table);//��tableװ������  

 

 notebook=gtk_notebook_new();//����notebook 

 gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook),GTK_POS_TOP);//����notebook�ĸ�ʽ 

 gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 11, 1, 11);//��notebook��������� 

 gtk_widget_show(notebook); 

 /*����notebook��ÿһҳ*/ 

 for(i=0;i<5;i++){    

  label0[i]=gtk_label_new(title[i]);//notebookҳ�����            

  frame[i]=gtk_frame_new(NULL);//ҳ���� 

  gtk_container_set_border_width (GTK_CONTAINER (frame[i]), 10);//������Ե�ľ��� 

  gtk_frame_set_shadow_type (GTK_FRAME (frame[i]),GTK_SHADOW_ETCHED_OUT);//��ܵ���Ӱģʽ 

  gtk_widget_set_size_request(frame[i],450,450);//��ܴ�С 

  gtk_widget_show(frame[i]); 

  gtk_widget_show (label0[i]); 

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook),frame[i],label0[i]);//����notebook�ĵ�iҳ   

  table1[i]=gtk_table_new(12,11,TRUE);//��������12��*11�� 

  gtk_widget_show(table1[i]); 

  gtk_container_add(GTK_CONTAINER(frame[i]),table1[i]);//������tbale1������ 
 } 
 
 MenuBar=gtk_menu_bar_new();//�����˵��� 

 gtk_table_attach_defaults(GTK_TABLE(table),MenuBar,0,11,0,1);//���˵���������� 

 MenuItemFile=CreateMenuItem(MenuBar,"�ļ�");//���Ӳ˵��� 

  MenuItemHelp=CreateMenuItem(MenuBar,"����");//���Ӳ˵��� 

  gtk_widget_show(MenuBar); 

 

    process_label=gtk_label_new("");//������ʾ�������ı�ǩ 

    gtk_widget_show(process_label); 
    
//    timer=gtk_timeout_add(1000,(GtkFunction)process_num,data);//��һ����ʱ��(timer),ÿ���������һ��(GtkFunction)process_num���� 

    gtk_table_attach_defaults(GTK_TABLE(table),process_label,0,2,11,12);//��״̬������ʾ�������� 

     cpu_rate_label=gtk_label_new(" ");//������ʾcpuռ���ʵı�ǩ 

    gtk_widget_show(cpu_rate_label); 

 gtk_table_attach_defaults(GTK_TABLE(table),cpu_rate_label,2,5,11,12);//��״̬������ʾcpuռ���� 
    
 cpu_bar=gtk_progress_bar_new();//����CPU������ 

 gtk_widget_show(cpu_bar); 
 notebook_cpu_init(); 
 
 gtk_signal_connect(GTK_OBJECT(window),"delete_event",GTK_SIGNAL_FUNC(delete_event),NULL); 

  gtk_main(); 
} 


/*cpuҳ���ʼ��*/ 

void notebook_cpu_init(void){ 

   float v,v0;    
   char text[20];
   char text0[20]; 

   gfloat value1,value2; 

 

   vbox = gtk_vbox_new (FALSE, 0);//����������� 

   gtk_widget_show (vbox); 

   gtk_table_attach_defaults(GTK_TABLE(table1[0]),vbox,0,12,0,12); 

 

   frame0 = gtk_frame_new ("CPU");//����������ʾCPU��Ϣ�ı߿򹹼� 

   gtk_widget_show (frame0); 

   gtk_box_pack_start (GTK_BOX (vbox), frame0, FALSE, FALSE, 0);//�ӵ������� 

   gtk_container_add (GTK_CONTAINER (frame0),cpu_bar);        

} 

/*�����˵���*/ 

GtkWidget *CreateMenuItem(GtkWidget *MenuBar,char *test){ 

     GtkWidget *MenuItem; 

     MenuItem=gtk_menu_item_new_with_label(test);//�������˵��� 

    gtk_menu_shell_append(GTK_MENU_SHELL(MenuBar),MenuItem);//�Ѹ��˵��Ͳ˵�������һ�� 

   gtk_widget_show(MenuItem);//��ʾ���˵� 

     return MenuItem; 

} 
