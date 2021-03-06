#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  
  Pair* item = createPair(key,value);
  int index=hash(key,map->capacity);
  if(map->buckets[index]==NULL || map->buckets[index]->key==NULL )
  {
    /*
    if(map->capacity==map->size){
      return;  
    }
    */
    map->buckets[index]=item;
    map->size++;
  }
  else
  {
    while(map->buckets[index]!=NULL)
    {
      if(is_equal(key,map->buckets[index]->key)==1)
      {
        return;
      }
      index++;
      index%=map->capacity;
      //if(index>=map->capacity)
      //{
        //index=0; 
      //}
      
    } 
    if(map->buckets[index]==NULL || map->buckets[index]->key==NULL )
    {
      /*
      if(map->capacity==map->size){
        return;  
      }
      */
      map->buckets[index]=item;
      map->size++;
    }
  }
    
  
 
 
  
}


void enlarge(HashMap * map) {

    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *mapa=malloc(sizeof(HashMap));
    if(mapa== NULL)
    {
        printf("no hay suficiente memoria");
        return NULL;
    }
    mapa->size=0;
    mapa->capacity=capacity;
    mapa->current=-1;
    mapa->buckets=(Pair**)calloc(mapa->capacity,sizeof(Pair*));
    if(mapa->buckets==NULL)
    {
        mapa = NULL;
        return NULL;
    }
    
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {   
  int index=hash(key,map->capacity);
  while(map->buckets[index]!=NULL)
    {
      if(is_equal(map->buckets[index]->key,key)==1)
      {
        map->buckets[index]->key=NULL;
        map->size--;
      }
      index++;
      index%=map->capacity;
    }
}
  
    



Pair * searchMap(HashMap * map,  char * key) {   
  int index=hash(key,map->capacity);
  while(map->buckets[index]!=NULL)
    {
      if(is_equal(map->buckets[index]->key,key)==1)
      {
        map->current=index;
        return map->buckets[index];
      }
      index++;
      index%=map->capacity;
    }

  return NULL;
}

Pair * firstMap(HashMap * map) {
  int inde=0;
  while(map->buckets[inde]==NULL || map->buckets[inde]->key == NULL){
    inde=(inde+1)%map->capacity;
  }
  map->current=inde;
  return map->buckets[inde];
  
}

Pair * nextMap(HashMap * map) {
  
  long indi;
  indi = map->current;
  indi = (indi + 1) % map->capacity;
  while(map->buckets[indi]==NULL || map->buckets[indi]->key==NULL)
  {
    indi=(indi + 1 )% map->capacity;
  }
  if (indi == 0) return NULL;
  map->current=indi;
  return map->buckets[indi];
  
  
}
