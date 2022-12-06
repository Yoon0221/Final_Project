//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2

int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
    // ���� - ���� ����
	int check_num = -1; 
    char check_place[100] = {0};
    int i, res, none = 0; 
    int check_big = 0, check_small = 0;
    
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //1-2. loading each patient informations
    while ( 3 == fscanf(fp, "%d %d %d", &pIndex, &age, &time))
    {
    	fscanf(fp, "%d %d %d %d %d", &placeHist[4], &placeHist[3], &placeHist[2], & placeHist[1], &placeHist[0]) ;
			
		ifct_element = ifctele_genElement(pIndex, age, time, placeHist);
			 
		ifctdb_addTail(ifct_element);
		
	}
    
    //1-3. FILE pointer close
    fclose(fp);
    
    
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu : ");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
                {
                	while(1)
                	{
                		printf("\n\n����ϰ� ���� ȯ���� ��ȣ�� �Է����ֽʽÿ� : ");
                		scanf(" %d", &check_num);
                		getchar();
                		
                		if ((check_num >= 0) && (check_num < ifctdb_len()))
                			break;
					}
                
                	printf("\n\n");
                	ifctele_printElement(ifctdb_getData(check_num));
                	printf("\n\n");
				}
                break;
                
            case MENU_PLACE:
                {
                	// ���� �� ����
					none = 0;
					 
                	printf("\n\nƯ�� ��ҿ��� ������ Ȯ�ε� ȯ�ڵ��� ������ ����ϴ� ����Դϴ�.\n");
                	printf("�˻��ϰ� ���� ��Ҹ� �������� ���� ���� �Է����ֽʽÿ� : ");
					scanf(" %s", check_place);
					
					// �� ȯ�ڵ��� �ߺ� ��ҿ� �Է¹��� ��� �� 
					for (i = 0; i < ifctdb_len(); i++)
					{
						res = ifctele_getPlaceName(ifctdb_getData(i), check_place);
						
						// ȯ���� �ߺ���ҿ� �Է¹��� ��Ұ� ������ 
						if (res == 0)
						{
							printf("\n\n");
                			ifctele_printElement(ifctdb_getData(i));       // �� ���� ȯ�� ���� ��� 
                			printf("\n\n");
                			none = 1;
						}
					} 
					
					if (none != 1)
						printf("�ش� ��ҿ��� ������ ȯ�ڰ� �����ϴ�.\n\n");
					 
				}
                break;
                
            case MENU_AGE:
                {
                	// ���� �� ����
					none = 0;
					
                	printf("\n\nƯ�� ������ ���̿� �ش��ϴ� ȯ�� ���� ������ ����ϴ� ����Դϴ�.\n");
                	printf("�˻��ϰ� ���� �ִ�, �ּ� ���̸� �Է����ֽʽÿ�.\n");
                	
                	while(1)
                	{
                		printf("�ִ� : ");
						scanf(" %d", &check_big); 
						printf("�ּڰ� : ");
						scanf(" %d", &check_small); 
                		
						if ((check_big > 0) && (check_small > 0) && (check_big >= check_small))
                			break;
                		else
                			printf("�ٽ� �Է����ֽʽÿ�.\n\n");
					}
					
					for (i = 0; i < ifctdb_len(); i++)
					{
						res = ifctele_getAge(ifctdb_getData(i), check_big, check_small);
						
						// ȯ���� ���̰� �Է¹��� �ִ�, �ּ��� �����̸� 
						if (res == 0)
						{
							printf("\n\n");
                			ifctele_printElement(ifctdb_getData(i));       // �� ���� ȯ�� ���� ��� 
                			printf("\n\n");
                			none = 1; 
						}
					}
					
					if (none != 1)
						printf("������ ȯ���� �ش� ���̴�� �����ϴ�.\n\n");
						
				}
                break;
                
            case MENU_TRACK:
                    
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
