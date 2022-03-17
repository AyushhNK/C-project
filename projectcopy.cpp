#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
  int main(){
    FILE *fp, *ft;
    char another, choice;
    struct emp{
        char name[40]; 
        int age; 
        float bs; 
    };
  
    struct emp e; 
    printf("********************************\n");
    printf("** EMPLOYEE MANAGEMENT SYSTEM8**\n");
    printf("********************************\n");
    char empname[40]; 
    long int recsize; 
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL){
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL){
            printf("Connot open file");
            exit(1);
        }
    }
  
   
    recsize = sizeof(e);
  

    while(1){
    	
    	printf(".............................\n");
    	printf(":    THINGS YOU CAN DO      :\n");
    	printf(":    *****************      :\n");
    	printf(":                           :\n");
        printf(":Press==>1. Add Record      :\n"); 
        printf(":Press==>2. List Records    :\n"); 
        printf(":Press==>3. Modify Records  :\n"); 
        printf(":Press==>4. Delete Records  :\n"); 
        printf(":Press==>5. Exit            :\n"); 
        printf(".............................\n");
        printf("What do you want to do: "); 
        fflush(stdin); 
        scanf("\n%c", &choice);
        switch(choice){
            case '1':  
                fseek(fp,0,SEEK_END); 
                                        
                another = 'y';
                while(another == 'y'){ 
                    flush();
                    printf("\nEnter name: ");
                    fgets(e.name, 40, stdin);
                    printf("\nEnter age: ");
                    scanf("%d", &e.age);
                    printf("\nEnter basic salary: ");
                    scanf("%f", &e.bs);
  
                    fwrite(&e,recsize,1,fp); 
  
                    printf("\nAdd another record(y/n) ");
                    fflush(stdin);
                    scanf("\n%c", &another);
                }
                break;
            case '2':
                rewind(fp); 
                printf("             RECORD\n");
                printf("             ------\n");
                while(fread(&e,recsize,1,fp)==1){ 
                
                    printf("        Name:%s",e.name); 
                    printf("        Age:%d\n",e.age);
                    printf("        Salary:%.2f\n\n",e.bs);
                }
            	printf("\nPress any key to return to the menu: ");
                fflush(stdin);
                scanf("\n%c", &another);
                break;
  
            case '3':  
                another = 'y';
                while(another == 'y'){
                    printf("Enter the employee name to modify: ");
                    scanf("%s", empname);
                    rewind(fp);
                    while(fread(&e,recsize,1,fp)==1){ 
                        if(strcmp(e.name,empname) == 0){ 
                            printf("\nEnter new name,age and bs: ");
                            scanf("%s%d%f",e.name,&e.age,&e.bs);
                            fseek(fp,-recsize,SEEK_CUR); 
                            fwrite(&e,recsize,1,fp); 
                            break;
                        }
                    }
                    printf("\nModify another record(y/n)");
                    fflush(stdin);
                    scanf("\n%c", &another);
                }
                break;
            case '4':
                another = 'y';
                while(another == 'y'){
                    flush();
                    printf("\nEnter name of employee to delete: ");
                    fgets(empname,40, stdin);
                    ft = fopen("Temp.dat","wb");  
                    rewind(fp); 
                    while(fread(&e,recsize,1,fp) == 1){ 
                        if(strcmp(e.name,empname) != 0){ 
                            fwrite(&e,recsize,1,ft); 
                        }
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("EMP.DAT"); 
                    rename("Temp.dat","EMP.DAT"); 
                    fp = fopen("EMP.DAT", "rb+");
                    printf("Delete another record(y/n)");
                    fflush(stdin);
                    scanf("\n%c", &another);
                }
                break;
            case '5':
                fclose(fp);  
                exit(0); 
        }
    }
    return 0;
}
