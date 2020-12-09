#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#define max_name 30
#define max_desc 50

static GtkWidget *monthNum;
static GtkWidget *dayNum;
static GtkWidget *desc;
static GtkWidget *typeE;
static GtkWidget *codeDeleted;
static GtkWidget *monthInfo;
static GtkWidget *dayInfo;
static GtkWidget *descInfo;
static GtkWidget *deleteInfo;
static GtkWidget *recoverCode;
static GtkWidget *result;
int input;

typedef enum {work=0, life, home, holiday, other} eventTypes;

struct events {
    eventTypes types;
    int day;
    int month;
    char descriptor[max_desc];
    int code;
    struct events* next;
}*list=NULL;

struct trash {
    eventTypes types_trash;
    int day_trash;
    int month_trash;
    char descriptor_trash[max_desc];
    int code_trash;
    struct trash* next;
}*head=NULL;

void executed(void);
char say[] = "added";


void normalAdd(eventTypes event, int dayNum, int monthNum, char descrip[], int codeNum);
void adding(GtkWidget *actionAdd, gpointer data);
char* itoa(int i, char b[]);
int randomNum(void);
void deleting(GtkWidget *actionDelete, gpointer data);
void recoveringTrash (GtkWidget *recoverTrash, gpointer data);
void saving (GtkWidget *save, gpointer data);
void load(void);
void displayHelperTrash(void);
void displayHelperTrash(void);
void displaying(GtkWidget *actiondisplaying, gpointer data);
void displayingTrash(GtkWidget *actionDisplayingTrash, gpointer data);
void popping(GtkToggleButton *tglButton, gpointer data);


void normalAdd(eventTypes event,
               int dayNum,
               int monthNum,
               char descrip[],
               int codeNum) {
    struct events* temp = list;
    struct events* p;
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    p=(struct contact*) malloc(sizeof(struct events));
    p->types=event;
    p->day=dayNum;
    p->month=monthNum;
    strcpy(p->descriptor,descrip);
    p->code=codeNum;
    
    int now, after;
    if(temp){
        if(((tm.tm_mon+1) > temp->month) || ((tm.tm_mon+1) == temp->month && tm.tm_mday>temp->day)) {
            after = (temp->month)*100 + (temp->day) + 4000;
        }
        else {
            after = (temp->month)*100 + (temp->day);
        }
    }
    
    if(((tm.tm_mon+1) > p->month) || ((tm.tm_mon+1) == p->month && tm.tm_mday>p->day)) {
        now = (p->month)*100 + (p->day) + 4000;
    }
    else {
        now = (p->month)*100 + (p->day);
    }
    
    if (temp == NULL || after >= now) {
           p->next = list;
           list = p;
       }
    else {
        temp = list;
        if(temp->next){
            if(((tm.tm_mon+1) > temp->next->month) || ((tm.tm_mon+1) == temp->next->month && tm.tm_mday>temp->next->day)) {
                after = (temp->next->month)*100 + (temp->next->day) + 4000;
            }
            else {
                after = (temp->next->month)*100 + (temp->next->day);
            }
        }
           
        while (temp->next != NULL && after < now) {
               
            temp = temp->next;
            if(temp->next){
                if(((tm.tm_mon+1) > temp->next->month) || ((tm.tm_mon+1) == temp->next->month && tm.tm_mday>temp->next->day)) {
                    after = (temp->next->month)*100 + (temp->next->day) + 4000;
                }
                else {
                    after = (temp->next->month)*100 + (temp->next->day);
                }
            }
        }
        p->next = temp->next;
        temp->next = p;
    }
    
}

void adding(GtkWidget *actionAdd,
            gpointer data) {
    
    struct events* temp = list;
    struct events* p;
    char buffer[max_desc];
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    char typeInfo[8];
    p=(struct contact*) malloc(sizeof(struct events));
    int theMonth = atoi((char*)gtk_entry_get_text(GTK_ENTRY(monthNum)));
    int theDay = atoi((char*)gtk_entry_get_text(GTK_ENTRY(dayNum)));
    strcpy(p->descriptor,gtk_entry_get_text(GTK_ENTRY(desc)));
    
    if (theDay > 31 || theDay < 1){
        snprintf(buffer, sizeof(buffer), "ERROR: %s", "day not valid");
        gtk_label_set_text(GTK_LABEL(result), buffer);
        return;
    }
    if (theMonth > 12 || theMonth < 1){
        snprintf(buffer, sizeof(buffer), "ERROR: %s", "month not valid");
        gtk_label_set_text(GTK_LABEL(result), buffer);
        return;
    }
    if (((theMonth == 2) || (theMonth == 4) || (theMonth == 5) || (theMonth == 9) || (theMonth == 11)) && (theDay>30 || theDay<1)) {
        snprintf(buffer, sizeof(buffer), "ERROR: %s", "day not valid for the month");
        gtk_label_set_text(GTK_LABEL(result), buffer);
        return;
    }
    
    p->day=theDay;
    p->month=theMonth;
    strcpy(typeInfo,gtk_entry_get_text(GTK_ENTRY(typeE)));
    if(strcasecmp(typeInfo,"work")==0){
        p->types=0;
    }
    else if(strcasecmp(typeInfo,"life")==0){
        p->types=1;
    }
    else if(strcasecmp(typeInfo,"home")==0){
        p->types=2;
    }
    else if(strcasecmp(typeInfo,"holiday")==0){
        p->types=3;
    }
    else{
        p->types=4; // "other"
    }
    p->code=randomNum();
    
    int now, after;
    if(temp){
        if(((tm.tm_mon+1) > temp->month) || ((tm.tm_mon+1) == temp->month && tm.tm_mday>temp->day)) {
            after = (temp->month)*100 + (temp->day) + 4000;
        }
        else {
            after = (temp->month)*100 + (temp->day);
        }
    }
    
    if(((tm.tm_mon+1) > p->month) || ((tm.tm_mon+1) == p->month && tm.tm_mday>p->day)) {
        now = (p->month)*100 + (p->day) + 4000;
    }
    else {
        now = (p->month)*100 + (p->day);
    }
    
    if (temp == NULL || after >= now) {
           p->next = list;
           list = p;
       }
    else {
        temp = list;
        if(temp->next){
            if(((tm.tm_mon+1) > temp->next->month) || ((tm.tm_mon+1) == temp->next->month && tm.tm_mday>temp->next->day)) {
                after = (temp->next->month)*100 + (temp->next->day) + 4000;
            }
            else {
                after = (temp->next->month)*100 + (temp->next->day);
            }
        }
           
        while (temp->next != NULL && after < now) {
               
            temp = temp->next;
            if(temp->next){
                if(((tm.tm_mon+1) > temp->next->month) || ((tm.tm_mon+1) == temp->next->month && tm.tm_mday>temp->next->day)) {
                    after = (temp->next->month)*100 + (temp->next->day) + 4000;
                }
                else {
                    after = (temp->next->month)*100 + (temp->next->day);
                }
            }
        }
        p->next = temp->next;
        temp->next = p;
    }
    
    snprintf(buffer, sizeof(buffer), "added: %s", p->descriptor);
    gtk_label_set_text(GTK_LABEL(result), buffer);
}

char* itoa(int i,
           char b[]) {
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int randomNum() {
    
    struct events* pp = list;
    struct trash* p = head;
    int b=0;
    int x=0;
    while(b==0 || x==0){
        b=1;
        srand(time(0));
        x = rand()%1000+1;
        while(pp){
            if(pp->code==x){
                b=0;
            }
            pp=pp->next;
        }
        while(p){
            if(p->code_trash==x){
                b=0;
            }
            p=p->next;
        }
    }
    return x;
}

void deleting(GtkWidget *actionDelete,
              gpointer data) {
    
    struct trash* pp = (struct trash*) malloc(sizeof(struct trash));
    int codeD = atoi((char*)gtk_entry_get_text(GTK_ENTRY(codeDeleted)));
    struct events* temp = list, *prev;
    
    if (temp != NULL && temp->code == codeD) {
        pp->code_trash=temp->code;
        pp->day_trash=temp->day;
        strcpy(pp->descriptor_trash,temp->descriptor);
        pp->month_trash=temp->month;
        pp->types_trash=temp->types;
          
        pp->next = head;
        head = pp;
          
        list = temp->next;
        free(temp);
        return;
    }
    
    while (temp != NULL && temp->code != codeD)
    {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    pp->code_trash=temp->code;
    pp->day_trash=temp->day;
    strcpy(pp->descriptor_trash,temp->descriptor);
    pp->month_trash=temp->month;
    pp->types_trash=temp->types;
    
    pp->next = head;
    head = pp;
    
    prev->next = temp->next;
    free(temp);
}

void recoveringTrash (GtkWidget *recoverTrash,
                      gpointer data) {
    
    struct trash *temp=head, *prev;
    int codeD = atoi((char*)gtk_entry_get_text(GTK_ENTRY(codeDeleted)));
    if (temp != NULL && temp->code_trash == codeD) {
        
        normalAdd(temp->types_trash, temp->day_trash, temp->month_trash, temp->descriptor_trash, temp->code_trash);
        
        head = temp->next;
        free(temp);
        
        return;
    }
    
    while (temp != NULL && temp->code_trash != codeD)
    {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    normalAdd(temp->types_trash, temp->day_trash, temp->month_trash, temp->descriptor_trash, temp->code_trash);
    
    prev->next = temp->next;
    free(temp);
}

void saving (GtkWidget *save,
             gpointer data) {
    
    char *fileName = "new_cal_list.txt";
    int eventValue;
    FILE *file;
    file=fopen(fileName, "wb");
    
    struct events* p;
    
    for(p=list; p!=NULL; p=p->next) {
        if(p->types == work){
            eventValue = 0;
        }
        else if(p->types == life) {
            eventValue = 1;
        }
        else if(p->types == home) {
            eventValue = 2;
        }
        else if(p->types == holiday) {
            eventValue = 3;
        }
        else {
            eventValue = 4;
        }
        fwrite(&eventValue, sizeof(int), 1, file);
        fwrite(&p->day, sizeof(int), 1, file);
        fwrite(&p->month, sizeof(int), 1, file);
        fwrite(p->descriptor, max_desc, 1, file);
        fwrite(&p->code, sizeof(int), 1, file);
        /*sizeof(eventValue)
        sizeof(p->day)
        sizeof(p->month)
        sizeof(p->descriptor)
        sizeof(p->code)*/
    }
    fclose(file);
    
}

void load() {
    char *fileName = "new_cal_list.txt";
    int eventValue;
    FILE *file;
    file=fopen(fileName, "rb");
    
    struct events* p;
    p = (struct contact*) malloc(sizeof(struct events));
    
    while(fread(&eventValue, sizeof(int), 1, file)==1) {
        
        if(eventValue == 0){
            p->types = work;
        }
        else if(eventValue == 1) {
            p->types = life;
        }
        else if(eventValue == 2) {
            p->types = home;
        }
        else if(eventValue == 3) {
            p->types = holiday;
        }
        else {
            p->types = other;
        }
        fread(&p->day, sizeof(int), 1, file);
        fread(&p->month, sizeof(int), 1, file);
        fread(p->descriptor, max_desc, 1, file);
        fread(&p->code, sizeof(int), 1, file);
        
        normalAdd(p->types, p->day, p->month, p->descriptor, p->code);
    }
    fclose(file);
    
}

char final[500];

void displayHelper() {
    struct events* p = list;
    strcpy(final,"");
    while(p){
        char dayStr[5],monthStr[5],codeStr[10],typeStr[8];
        char newLine[3] = "\n";
        
        if (p->types == work){
            strcpy(typeStr,"work");
        }
        else if (p->types == life){
            strcpy(typeStr,"life");
        }
        else if (p->types == home){
            strcpy(typeStr,"home");
        }
        else if (p->types == holiday){
            strcpy(typeStr,"holiday");
        }
        else{
            strcpy(typeStr,"other");
        }
        
        strcat(final,newLine);
        
        strcat(final,typeStr);
        
        strcat(final,newLine);
        
        itoa(p->month,monthStr);
        strcat(final,monthStr);
        
        strcat(final,"/");
        
        itoa(p->day,dayStr);
        strcat(final,dayStr);
        
        strcat(final,newLine);
        
        strcat(final,p->descriptor);
        
        strcat(final,newLine);
        
        itoa(p->code,codeStr);
        strcat(final,codeStr);
        
        strcat(final,newLine);
        
        p=p->next;
    }
    
}

char finalTrash[500];

void displayHelperTrash() {
    struct trash* p = head;
    strcpy(finalTrash,"");
    while(p){
        char dayStr[5],monthStr[5],codeStr[10],typeStr[8];
        char newLine[3] = "\n";
        
        if (p->types_trash == work){
            strcpy(typeStr,"work");
        }
        else if (p->types_trash == life){
            strcpy(typeStr,"life");
        }
        else if (p->types_trash == home){
            strcpy(typeStr,"home");
        }
        else if (p->types_trash == holiday){
            strcpy(typeStr,"holiday");
        }
        else{
            strcpy(typeStr,"other");
        }
        
        strcat(finalTrash,newLine);
        
        strcat(finalTrash,typeStr);
        
        strcat(finalTrash,newLine);
        
        itoa(p->month_trash,monthStr);
        strcat(finalTrash,monthStr);
        
        strcat(finalTrash,"/");
        
        itoa(p->day_trash,dayStr);
        strcat(finalTrash,dayStr);
        
        strcat(finalTrash,newLine);
        
        strcat(finalTrash,p->descriptor_trash);
        
        strcat(finalTrash,newLine);
        
        itoa(p->code_trash,codeStr);
        strcat(finalTrash,codeStr);
        
        strcat(finalTrash,newLine);
        
        p=p->next;
    }
    
}

void displaying(GtkWidget *actiondisplaying,
                 gpointer data) {
   
    displayHelper();
    
    snprintf(final, sizeof(final), "%s", final);
    gtk_label_set_text(GTK_LABEL(result), final);
    
}


void displayingTrash(GtkWidget *actionDisplayingTrash,
                      gpointer data) {
    displayHelperTrash();
    snprintf(finalTrash, sizeof(finalTrash), "%s", finalTrash);
    gtk_label_set_text(GTK_LABEL(result), finalTrash);
    
}

void popping(GtkToggleButton *tglButton,
              gpointer data) {
    GtkWidget *popover = data;
    g_return_if_fail(GTK_IS_POPOVER(popover));
    g_return_if_fail(GTK_IS_TOGGLE_BUTTON(tglButton));
    gtk_popover_set_modal(GTK_POPOVER(popover), FALSE);
    
    if (gtk_toggle_button_get_active(tglButton)){
        gtk_popover_popup(GTK_POPOVER(popover));
    }
    
    else{
        gtk_popover_popdown(GTK_POPOVER(popover));
    }
}


int main (int argc,
          char *argv[]) {
    GtkApplication *app = gtk_application_new ("com.example.GtkApplication", G_APPLICATION_FLAGS_NONE);
   
    GtkWidget *window, *grid, *actionAdd, *actionDelete, *actionsave, *actionrecoverTrash, *actiondisplay, *popover, *toggleButton, *actionDisplayingTrash;
    
    load();
    
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect(app, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window),grid);
    
    monthInfo = gtk_label_new("month");
    gtk_grid_attach(GTK_GRID(grid), monthInfo, 0,0,1,1);
    monthNum =gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), monthNum,0,1,1,1);
    
    dayInfo = gtk_label_new("day");
    gtk_grid_attach(GTK_GRID(grid), dayInfo, 1,0,1,1);
    dayNum = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), dayNum, 1,1,1,1);
    
    descInfo = gtk_label_new("description");
    gtk_grid_attach(GTK_GRID(grid), descInfo, 2,0,1,1);
    desc = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), desc, 2, 1, 1, 1);
    
    descInfo = gtk_label_new("work, home, life, or other");
    gtk_grid_attach(GTK_GRID(grid), descInfo, 3,0,1,1);
    typeE = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), typeE,3,1,1,1);
    
    actionAdd = gtk_button_new_with_label("add event");
    g_signal_connect(actionAdd,"clicked",G_CALLBACK(adding),NULL);
    gtk_grid_attach(GTK_GRID(grid), actionAdd, 4, 1, 1, 1);
    
    result = gtk_label_new("result:");
    gtk_grid_attach(GTK_GRID(grid), result,0,9,1,1);
    
    deleteInfo = gtk_label_new("code of event to be deleted");
    gtk_grid_attach(GTK_GRID(grid), deleteInfo, 3,2,1,1);
    codeDeleted = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), codeDeleted, 3, 3, 1, 1);
    
    actionDelete = gtk_button_new_with_label("delete event");
    g_signal_connect(actionDelete,"clicked",G_CALLBACK(deleting),NULL);
    gtk_grid_attach(GTK_GRID(grid),actionDelete,4,3,1,1);

    dayInfo = gtk_label_new("code of event to be recovered");
    gtk_grid_attach(GTK_GRID(grid), dayInfo, 3,4,1,1);
    recoverCode = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), recoverCode, 3, 5, 1, 1);
    
    actionrecoverTrash = gtk_button_new_with_label("recover trash");
    g_signal_connect(actionrecoverTrash,"clicked",G_CALLBACK(recoveringTrash),NULL);
    gtk_grid_attach(GTK_GRID(grid),actionrecoverTrash,4,5,1,1);
    
    actiondisplay = gtk_button_new_with_label("display");
    g_signal_connect(actiondisplay,"clicked",G_CALLBACK(displaying),NULL);
    gtk_grid_attach(GTK_GRID(grid),actiondisplay,4,7,1,1);
    
    toggleButton = gtk_toggle_button_new_with_label("add'l functions");
    gtk_grid_attach(GTK_GRID(grid),toggleButton,3,7,1,1);
    
    actionsave = gtk_button_new_with_label("save into 'new_cal_list.txt'");
    g_signal_connect(actionsave,"clicked",G_CALLBACK(saving),NULL);
    gtk_widget_show(actionsave);
    
    actionDisplayingTrash = gtk_button_new_with_label("display trash");
    g_signal_connect(actionDisplayingTrash,"clicked",G_CALLBACK(displayingTrash),NULL);
    gtk_grid_attach(GTK_GRID(grid),actionDisplayingTrash,4,8,1,1);
    
    popover = gtk_popover_new(toggleButton);
    gtk_container_add(GTK_CONTAINER(popover), actionsave);
    
    gtk_container_set_border_width(GTK_CONTAINER(popover), 4);
    
    g_signal_connect(toggleButton,"toggled",G_CALLBACK(popping),popover);
    
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}


