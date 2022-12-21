//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;


char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};


// 환자 정볼르 저장하는 구조체  
typedef struct ifs_ele {
	int index;                       //number
	int age;                         //age
	int time;                        //time
	place_t place[N_HISTORY];        //place[N_HISTORY]
} ifs_ele_t;



void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	// 구조체 포인터 선언하기
	ifs_ele_t* ptr;
	 
	// 구조체 포인터의 크기를 동적할당하기 
	ptr = (int*)malloc(sizeof(int) * 8);
	
	// 동적할당 실패시 
	if (ptr == NULL)
	{
		printf("malloc error");
		exit(1);
	}
	
	// 구조체에 환자 정보 저장하기 
	ptr->index = index;
	ptr->age   = age;
	ptr->time  = detected_time;
	ptr->place[4] = history_place[4];
	ptr->place[3] = history_place[3];
	ptr->place[2] = history_place[2];
	ptr->place[1] = history_place[1];
	ptr->place[0] = history_place[0];
		
	return ptr;
}


int ifctele_getAge(void* obj, int num_b, int num_s)
{
	int res = 0;
	 
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	
	// 환자의 나이가 num_b ~ num_s 사이인지 검사한 결과를 변수 res에 저장 
	if ((ptr->age >= num_s) && (ptr->age <= num_b)) 
		res = 0;
	else
		res = 1;
	
	return res;        
}

int ifctele_getHistPlaceIndex(void* obj, int index);
unsigned int ifctele_getinfestedTime(void* obj);


//char* ifctele_getPlaceName(int placeIndex);


void ifctele_printElement(void* obj)
{
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	
	// 포인터를 이용해서 구조체의 특정 정보들을 출력한다. 
	printf("환자 번호 : %d\n", ptr->index); 
	printf("나이 : %d\n", ptr->age);
	printf("감염 확인일자 : %d\n", ptr->time);
	printf("확인 4일전 장소 : %s\n", countryName[ptr->place[4]]);
	printf("확인 3일전 장소 : %s\n", countryName[ptr->place[3]]);
	printf("확인 2일전 장소 : %s\n", countryName[ptr->place[2]]);
	printf("확인 하루전 장소 : %s\n", countryName[ptr->place[1]]);
	printf("확인 당시 장소 : %s\n", countryName[ptr->place[0]]);
}
 

int ifctele_getPlaceName(void* placeName, char *str)
{
	int res = 0;
	
	ifs_ele_t* ptr = (ifs_ele_t*)placeName;
	
	// 문자열 비교 결과를 변수 res에 저장
	res = strcmp(countryName[ptr->place[0]], str);
	
	return res;        
}



int check_day_and_place(void* obj, int n)
{
	int i;
	int next_sick = -1;
	
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	
	
	for (i = 0; i < ifctdb_len(); i++)
		{
			void* obj2 = ifctdb_getData(i);
			ifs_ele_t* ptr2 = (ifs_ele_t*)obj2;
			
			// 추적환자의 감염 확인 n일전의 날짜와 다른 환자의 감염확인 당일 혹은 그 전날의 날짜가 겹치는 경우 
			if (((ptr->time - n) == (ptr2->time)) || ((ptr->time - n) == (ptr2->time-1)))
			{
				// 겹치는 날짜에, 장소까지 같은 경우 
				if ((ptr->place[n] == ptr2->place[0]) || (ptr->place[n] == ptr2->place[1]))
				{
					printf("\n\n-> %d번 환자 (시점 %d, %s)", ptr2->index, ptr->time - n, countryName[ptr->place[n]]);
					next_sick = ptr2->index;
				}
			}	
		} 
		
	return next_sick;
 } 


int find_the_first(void* obj)
{	
	int check1 = -1, check2 = -1, check3 = -1;
	int end = -1;
	
	ifs_ele_t* ptr = (ifs_ele_t*)obj;
	
	
	// 1. 확인 4일전 장소 비교
	check1 = check_day_and_place(ptr, 4);
				
	if (check1 != -1)
	{
		return end = check1;
	}
	// 2. 확인 3일전 장소 비교
	else 
	{
		check2 = check_day_and_place(ptr, 3);
	}
	
	if (check2 != -1)
	{
		return end = check2;
	}
	// 3. 확인 2일전 장소 비교
	else 
	{
		check3 = check_day_and_place(ptr, 2);
	}
		
	if (check3 != -1)
	{
		return end = check3;
	}
	// 4. 최초전파자 확인 
	else
	{
		printf(" : 최초전파자입니다.\n\n");
	}
	
	
	return end;
}
