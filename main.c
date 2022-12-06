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
    
    // 지윤 - 변수 선언
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
                		printf("\n\n출력하고 싶은 환자의 번호를 입력해주십시오 : ");
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
                	// 변수 값 설정
					none = 0;
					 
                	printf("\n\n특정 장소에서 감염이 확인된 환자들의 정보를 출력하는 기능입니다.\n");
                	printf("검색하고 싶은 장소를 영문으로 띄어쓰기 없이 입력해주십시오 : ");
					scanf(" %s", check_place);
					
					// 각 환자들의 발병 장소와 입력받은 장소 비교 
					for (i = 0; i < ifctdb_len(); i++)
					{
						res = ifctele_getPlaceName(ifctdb_getData(i), check_place);
						
						// 환자의 발병장소와 입력받은 장소가 같으면 
						if (res == 0)
						{
							printf("\n\n");
                			ifctele_printElement(ifctdb_getData(i));       // 그 때의 환자 정보 출력 
                			printf("\n\n");
                			none = 1;
						}
					} 
					
					if (none != 1)
						printf("해당 장소에서 감염된 환자가 없습니다.\n\n");
					 
				}
                break;
                
            case MENU_AGE:
                {
                	// 변수 값 설정
					none = 0;
					
                	printf("\n\n특정 범위의 나이에 해당하는 환자 관련 정보를 출력하는 기능입니다.\n");
                	printf("검색하고 싶은 최대, 최소 나이를 입력해주십시오.\n");
                	
                	while(1)
                	{
                		printf("최댓값 : ");
						scanf(" %d", &check_big); 
						printf("최솟값 : ");
						scanf(" %d", &check_small); 
                		
						if ((check_big > 0) && (check_small > 0) && (check_big >= check_small))
                			break;
                		else
                			printf("다시 입력해주십시오.\n\n");
					}
					
					for (i = 0; i < ifctdb_len(); i++)
					{
						res = ifctele_getAge(ifctdb_getData(i), check_big, check_small);
						
						// 환자의 나이가 입력받은 최대, 최소의 사이이면 
						if (res == 0)
						{
							printf("\n\n");
                			ifctele_printElement(ifctdb_getData(i));       // 그 때의 환자 정보 출력 
                			printf("\n\n");
                			none = 1; 
						}
					}
					
					if (none != 1)
						printf("감염된 환자중 해당 나이대는 없습니다.\n\n");
						
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
