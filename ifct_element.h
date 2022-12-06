//
//  ifct_element.h
//  infection path
//
//  Created by Juyeop Kim on 2022/10/20.
//

#ifndef ifct_element_h
#define ifct_element_h

#define N_PLACE                     40
#define N_HISTORY                   5
#define MAX_PLACENAME               100

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]);
int ifctele_getPlaceName(void* placeName, char *str);
int ifctele_getHistPlaceIndex(void* obj, int index);
unsigned int ifctele_getinfestedTime(void* obj);
int ifctele_getAge(void* obj, int num_b, int num_s);
void ifctele_printElement(void* obj);
#endif /* ifct_element_h */
