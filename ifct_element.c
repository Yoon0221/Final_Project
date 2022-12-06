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


typedef struct ifs_ele {
	int index;                       //number
	int age;                         //age
	int time;                        //time
	place_t place[N_HISTORY];        //place[N_HISTORY]
} ifs_ele_t;



void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY])
{
	ifs_ele_t* ptr;
	
	ptr = (int*)malloc(sizeof(int) * 8);
	
	// �����Ҵ� ���н� 
	if (ptr == NULL)
	{
		printf("malloc error");
		exit(1);
	}
	
	// ����ü ���� ���� 
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
	
	// ȯ���� ���̰� num_b ~ num_s �������� �˻��� ����� ���� res�� ���� 
	
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
	
	// ��� ����
	printf("ȯ�� ��ȣ : %d\n", ptr->index); 
	printf("���� : %d\n", ptr->age);
	printf("���� Ȯ������ : %d\n", ptr->time);
	printf("Ȯ�� 4���� ��� : %s\n", countryName[ptr->place[4]]);
	printf("Ȯ�� 3���� ��� : %s\n", countryName[ptr->place[3]]);
	printf("Ȯ�� 2���� ��� : %s\n", countryName[ptr->place[2]]);
	printf("Ȯ�� �Ϸ��� ��� : %s\n", countryName[ptr->place[1]]);
	printf("Ȯ�� ��� ��� : %s\n", countryName[ptr->place[0]]);
}


int ifctele_getPlaceName(void* placeName, char *str)
{
	int res = 0;
	
	ifs_ele_t* ptr = (ifs_ele_t*)placeName;
	
	// ���ڿ� �� ����� ���� res�� ����
	res = strcmp(countryName[ptr->place[0]], str);
	
	return res;        
}
