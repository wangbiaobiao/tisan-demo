/*******************************************************
 * File name: pando_object.c
 * Author: razr
 * Versions: 1.0
 * Description: 
 * History:
 *   1.Date: Sep 11, 2015
 *     Author: razr
 *     Modification:    
 *********************************************************/

#include "pando_object.h"

#define MAX_OBJECTS 16

static pando_object s_pando_object_list[MAX_OBJECTS] = {};
static int s_pando_object_list_idx = 0;
uint8_t FLASH_SEC_NUM = 0;

void ICACHE_FLASH_ATTR
register_pando_object(pando_object object)
{
	if(s_pando_object_list_idx > MAX_OBJECTS - 1)
	{
		return;
	}
	FLASH_SEC_NUM = object.no;
	s_pando_object_list[s_pando_object_list_idx++] = object;
}

pando_object* ICACHE_FLASH_ATTR
find_pando_object(int8 no)
{
	int i;
	for(i = 0; i < s_pando_object_list_idx; i++)
	{
		if( s_pando_object_list[i].no == no)
		{
			return &s_pando_object_list[i];
		}
	}
	return NULL;
}

pando_objects_iterator* ICACHE_FLASH_ATTR
create_pando_objects_iterator()
{
	pando_objects_iterator* it =  (pando_objects_iterator*)os_malloc(sizeof(pando_objects_iterator));
	it->cur = 0;
	return it;
}

void ICACHE_FLASH_ATTR
delete_pando_objects_iterator(pando_objects_iterator* it)
{
	if(it)
	{
		os_free(it);
	}
}

pando_object* ICACHE_FLASH_ATTR
pando_objects_iterator_next(pando_objects_iterator *it)
{
	if(it->cur == s_pando_object_list_idx)
	{
		return NULL;
	}
	return &s_pando_object_list[it->cur++];
}

