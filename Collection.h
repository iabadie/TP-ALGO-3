#ifndef __COLLECTION_H__
#define __COLLECTION_H__

typedef struct _Collection {
	void* list;
	unsigned size;
	unsigned typeSize;
	//...
} Collection;

// ENTREGA 1

Collection* collection_init(Collection* this, char* data, unsigned size, unsigned typeSize);

Collection* collection_iterate(Collection* this,  void (*showElement)(void*));

Collection* collection_add(Collection* this, char* element);

Collection* collection_remove(Collection* this, char* element);

void collection_free(Collection* this);



//ENTREGA 2

void* collection_find(Collection* this, void* value);

Collection* collection_select(Collection* this, Collection* dst, int (*filter)(void*));

Collection* collection_collect(Collection* this, Collection* dst, void (*function)(void*));

// Primitiva adicional

unsigned conditionalMemCpy(void* pointer1, void* pointer2, unsigned elementCount, unsigned size, int (*filter)(void*));


// ENTREGA 3

void collection_filter(Collection* this, int (*function)(void*));

Collection* collection_reduce_right(Collection* this, void(*function)(void*,void*));

Collection* collection_reduce_left(Collection* this, void (*function) (void*,void*));


// Primitivas adicionales

void collection_init_clean(Collection* dst, unsigned size, unsigned typeSize);

void collection_clone(Collection* this, Collection* dst);

#endif
