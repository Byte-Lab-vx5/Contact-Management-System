#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//NOTE - CLEAR SCREEN
#ifdef _WIN32
   void clear(){
       system("cls");
   }
#else
    void clear(){
       system("clear");
    }
#endif

#ifdef _WIN32
    #include<windows.h>
    void wait(int msecs * 1000){
        Sleep(msecs);
    }
#else
    #include<unistd.h>
    void wait(int secs){
        sleep(secs);
    }
#endif


typedef struct{
    char name[30];
    char email[30];
    long unsigned phone;
}contact;

void AddC();
void SearchC();
void UpdateC();
void SortC();
void DisplayC();
void DeleteC();

//NOTE - MAIN FUNCTION
int main(){
    int choice;
    do{
        clear();
        printf("\n==============\n  WELCOME\n==============\n\n");
        printf("1.Add Contact\n");
        printf("2.Search Contact\n");
        printf("3.Update Contact\n");
        printf("4.Sort Contact\n");
        printf("5.Display Contact\n");
        printf("6.Delete Contact\n");
        printf("0.Exit\n");        
        printf("===============\n");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                clear();
                AddC();
                break;
            case 2:
                clear();
                SearchC();
                break;
            case 3:
                clear();
                UpdateC();
                break;
            case 4:
                clear();
                SortC();
                break;
            case 5:
                clear();
                DisplayC();
                break;

            case 6:                
                clear();
                DeleteC();
                break;
        }
    }while(choice!=0);

    printf("\n\n");
    return 0;
}



void AddC(){
    contact *contacts;
    int nOfC;
    int validate;
    int ch;
    char exit[7];
    
    
    while(1){
        clear();
        printf("\n\nADD CONTACT\n\n");
        printf("How many contacts?: ");
        validate = scanf("%d", &nOfC);
        if(validate !=1){
            printf("\nError: enter integer value:");            
            while((ch = getchar())!='\n' && ch !=EOF){

            }
            continue;
        }
        
        if(nOfC <= 0){
            printf("Error: Number of contacts must be > 0");
            while((ch = getchar())!='\n' && ch !=EOF){

            }            
            continue;
        }
        break;       
    }
   
    contacts = (contact*)calloc(nOfC, sizeof(contact));
    if(!contacts){
        perror("calloc in AddC");
        return;
    }

    FILE *fp = fopen("contact.dat", "ab");
        if(!fp){
            perror("fopen in AddC");
            free(contacts);
            return;
        }

        for(int i=0; i<nOfC; i++){
            clear();
            printf("Contact %d\n\n", i+1);

            printf("Name: ");
            scanf(" %29[^\n]", contacts[i].name);

            printf("Email: ");
            scanf(" %29[^\n]", contacts[i].email);

            printf("phone: ");
            scanf(" %lu", &contacts[i].phone);
            
            fwrite(&contacts[i], sizeof(contact), 1, fp);
        }
        
    fclose(fp);
    free(contacts);
}


//NOTE - SEARCH CONTACT FUNCTION 
void SearchC(){
    contact *contact1;
    char name[30];
    int found;
    int back;
    contact1 = malloc(sizeof(contact));
    if(!contact1){        
        perror("malloc");
        free(contact1);
        return;
    }
    clear();
    printf("\n\nSEARCH CONTACT\n\n");
    printf("Enter name: ");
    scanf(" %29[^\n]", name);

    FILE *fp = fopen("contact.dat", "rb");
        if(!fp){            
            perror("fopen");
            free(contact1);
            return;
        }

        while(fread(contact1, sizeof(contact), 1, fp)){
            if(strcmp(contact1->name, name)==0){
                found = 1;
                break;
            }
        }

        if(found){            
            
            do{
                clear();
                printf("Name: %s\n", contact1->name);
                printf("Email: %s\n", contact1->email);
                printf("phone: %lu\n\n", contact1->phone); 

                printf("0.Back: ");
                scanf("%d", &back);
            } while (back!=0);
        }

        
        
    fclose(fp);
    free(contact1);
}


//NOTE - UPDATE CONTACT
void UpdateC(){
    contact contact2;
    char name[30];
    int ch;
    int exist = 0, found = 0;
    while(1){
        clear();        
        printf("\n\nUPDATE CONTACT\n\n");
        printf("Enter name of contact to update: ");
        scanf(" %29[^\n]", name);
        int valid = 1;

        for(int i=0; name[i]!='\0'; i++){
            if(!isalpha(name[i])
             && name[i]!=' '
             && name[i]!='-' 
             && name[i] !='\''){
                valid = 0;
                break;
            }
        }
        
        if((!valid) || strlen(name)<3){
            printf("\nInvalid name. Please enter a valid name (3 or more alphabetic characters)");            
            continue;
        }
        break;
    }


    clear();
    //puts("\n");   
    FILE *fp = fopen("contact.dat", "r+b");
        if(!fp){
            perror("fopen in update contact");
            fflush(stdout);
            wait(3);
            return;
        }else{
            while(fread(&contact2, (long)sizeof(contact), 1, fp)){
                if(strcmp(contact2.name, name)==0){                   
                    found = 1;
                    break;
                }
            }
        }      
        
        while(found !=1){
            clear();
            printf("\nNo contact (%s) found in the database\n\n", name);
            fflush(stdout);
            wait(1);
            printf("Enter name of contact to update: ");
            scanf(" %29[^\n]", name);
        }
        if(found){
            printf("\nContact found\n\n");
            wait(2);
            
            printf("Enter new name: ");
            scanf(" %29[^\n]", contact2.name);


            printf("Enter new email: ");
            scanf(" %29[^\n]", contact2.email);


            printf("Enter new phone number: ");
            scanf(" %lu", &contact2.phone);


            fseek(fp, (long)-sizeof(contact), SEEK_CUR);
            printf("\n\nUpdating contact..\n\n");
            wait(2);

            fwrite(&contact2, (long)sizeof(contact), 1, fp);
            fflush(stdout);
            wait(3);
            printf("\n\nContact Updated\n\n");
            wait(2);            
        }
        // else{
        //     printf("\nNo such contact found in the database\n\n");
        //     fflush(stdout);
        //     wait(2);
        //     return;
        // }
          
                
    fclose(fp);
}




int sort(const void *a, const void *b){
    contact *c1 = (contact *)a;
    contact *c2 = (contact *)b;
    return strcmp(c1->name, c2->name);
}

//NOTE - SORT CONTACT FUNCTION
void SortC(){
    contact *contacts;
     printf("\n\nSORT CONTACT\n\n");
    FILE *fp = fopen("contact.dat", "rb");
        if(!fp){
            perror("fopen in SortC");
            wait(3);
            return;
            free(contacts);
        }

        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        int count = size/sizeof(contact);
        rewind(fp);
        contacts = calloc(count, sizeof(contact));
        fread(contacts, sizeof(contact), count, fp);
        qsort(contacts, count, sizeof(contact), sort);
    fclose(fp);

    FILE *fp1 = fopen("contact.dat", "wb");
        if(!fp1){
            perror("2nd fopen in SortC");
            wait(3);
            return;
        }

        fwrite(contacts, sizeof(contact), count, fp1);
    fclose(fp);
    free(contacts);
}




//NOTE - DISPLAY CONTACT FUNCTION
void DisplayC(){
    contact *c;
    int exit;
    int ch;
    printf("\n\nDISPLAY CONTACT\n\n");
    FILE *fp = fopen("contact.dat", "rb");
        fseek(fp,0,SEEK_END);
        long size = ftell(fp);
        int count = size/sizeof(contact);
        rewind(fp);
        c = calloc(count, sizeof(contact));
        fread(c, sizeof(contact), count, fp);
        int i = 0;
        while(i<count){           
            wait(1);
            printf("Name: %s\nEmail: %s\nPhone: %lu\n\n", c[i].name, c[i].email, c[i].phone);
            wait(1);
            i++;            
        }
    fclose(fp);
    printf("\nAll contacts displayed\n\n");
    while(1){
        printf("\n0.exit: ");
        int validate = scanf("%d", &exit);
        if(validate !=1 || exit <0 || exit >0){
            printf("\n\nInvalid: Input must be an interger (0)");
            while((ch = getchar())!='\n' && ch != EOF){

            }
            continue;
        }
        break;
    }
    free(c);
}






//NOTE - DELETE CONTACT
void DeleteC(){
    contact *contacts;
    char name[30];    
    int ch;
    int found = 0;
    contacts = malloc(sizeof(contact));
    if(!contacts){
        perror("\n\nError allocating memory");
        return;       
    }
    

    while(strcmp(name, "exit")!=0){
        clear();
        printf("\nTypee (exit) to quit current screen\n");
        printf("\n\nDELETE CONTACT\n\n");
        printf("Enter name: ");
        scanf(" %[^\n]", name);

        if(strcmp(name, "exit")==0){
            clear();
            break;
        }

        if((!isalpha(name[0])) && name[0] != '_'){
            printf("Err: name cannot beggin with %c", name[0]);
            continue;
        }else if(isdigit(name[0])){
            printf("Err: name cannot beggin with %d", name[0]);
            continue;
        }


               



        FILE *fp = fopen("contact.dat", "rb");
            if(!fp){
                clear();
                perror("\ncontact.dat");
                fflush(stdout);
                wait(3);
                return;
                free(contacts);
            }              

            
            
            fseek(fp, 0, SEEK_END);
            long size = ftell(fp);
            int count = size / sizeof(contact);
           
           
            if(count <= 0){
                printf("\ncontact.dat: File is empty\n");
                wait(3);
                return;
                free(contacts);
            }

            
           rewind(fp);
            while(fread(contacts, sizeof(contact), 1, fp)){
                if(strcmp(contacts->name, name)==0){
                    found = 1;
                    break;
                }               
            }

            if(!found){                
                printf("\n%s not in database", name);
                //fflush(stdout);
                wait(1);
                continue;
            }   
            
            


            rewind(fp);
            while(fread(contacts, sizeof(contact),1,fp)){
                if(strcmp(contacts->name, name) != 0){
                    FILE *temp = fopen("temp.dat", "ab");
                        if(!temp){
                            perror("\nError allocating memmory");
                            return;
                            free(contacts);
                        }

                        
                        fwrite(contacts, sizeof(contact), 1, temp);
                        
                    fclose(temp);
                }
            }     
            
        fclose(fp); 
        remove("contact.dat");
        rename("temp.dat", "contact.dat");       
        continue;        
    }    

    free(contacts);
}
