#include "Collection.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//ENTREGA 1

Collection* collection_init(Collection* this, char* data, unsigned size, unsigned typeSize) {
	this->size = size;
	this->typeSize = typeSize;
	this->list = (char*)malloc(this->size);
	memcpy(this->list, data, this->size);
	return this;
}

Collection* collection_iterate(Collection* this, void (*applyFunction)(void*)) {
	unsigned count = this->size / this->typeSize;
	void* pointer = this->list;
	while(count--){
		(*applyFunction)(pointer);
		pointer += this->typeSize;
	}
	return this;
}

Collection* collection_add(Collection* this, char* element) {
	unsigned newSize = this->size + this->typeSize;
	this->list = (char*) realloc(this->list, newSize);
	char* pointer = this->list + this->size;
	memcpy(pointer, element, this->typeSize);
	this->size = newSize;
	return this;
}

Collection* collection_remove(Collection* this, char* element){
	void* pointer = collection_find(this, element);
	if(pointer) {
		unsigned elementsToMove = this->size - ((pointer + this->typeSize) - this->list);
		memcpy(pointer, pointer + this->typeSize,  elementsToMove);
		this->list = (char*)realloc(this->list, this->size - this->typeSize);
		this->size -= this->typeSize;
	}
	return this;
}

void collection_free(Collection* this){
	if(this->list) {
		free(this->list);
		this->list = NULL;
	}
}

// ENTREGA 2

void* collection_find(Collection* this, void* value) {
	unsigned count = this->size / this->typeSize;
	void* auxPointer = this->list;
	while(count--) {
		if(memcmp(auxPointer, value, this->typeSize) == 0) {
			return auxPointer;
		}
		auxPointer += this->typeSize;
	}
	return 0;
}

Collection* collection_select(Collection* this, Collection* dst, int (*filter)(void*)){
	unsigned elementCount = this->size / this->typeSize;
	char* memPointer = (char*)malloc(this->size);
	unsigned count = conditionalMemCpy(this->list, memPointer, elementCount, this->typeSize, filter);
	collection_free(dst);
	collection_init(dst, memPointer, count*this->typeSize, this->typeSize);
	free(memPointer);
	memPointer = NULL;
	return dst;
}

Collection* collection_collect(Collection* this, Collection* dst, void (*function)(void*)) {
	void* memPointer = (char*)malloc(this->size);
	memcpy(memPointer, this->list, this->size);
	collection_init(dst, memPointer, this->size, this->typeSize);
	collection_iterate(dst, function);
	free(memPointer);
	memPointer = NULL;
	return dst;
}

// ENTREGA 3

void collection_filter(Collection* this, int (*filterFunction)(void*)){
	if(this->size == 0){
		return;
	}
	Collection* dst;
	collection_init_clean(dst, this->size, this->typeSize);
	collection_clone(this, collection_select(this, dst, filterFunction));
}


Collection* collection_reduce_right(Collection* this, void(*function)(void*,void*)){
	if(this->size < this->typeSize){
		return 0;
	}
	if(this->size != this->typeSize){
		unsigned count = (this->size / this->typeSize) - 1;
		void* bundle = (void*)malloc(this->typeSize);
		void* positionPointer = this->list + this->size - this->typeSize;
		memcpy(bundle, positionPointer, this->size);
		positionPointer -= this->typeSize;
		while(count--){
		(*function)(bundle, positionPointer);
		positionPointer -= this->typeSize;
		}
		this->list = (char*)realloc(this->list, this->typeSize);
		this->size = this->typeSize;
		memcpy(this->list, bundle, this->typeSize);
		free(bundle);
		bundle = NULL;
	}
	return this;
}

Collection* collection_reduce_left(Collection* this, void(*function)(void*,void*)){
	if(this->size < this->typeSize){
			return 0;
		}
	if(this->size != this->typeSize){
		unsigned count = (this->size / this->typeSize) - 1;
		void* bundle = (void*)malloc(this->typeSize);
		memcpy(bundle, this->list, this->size);
		void* actualPosition = this->list + this->typeSize;
		while(count--){
			(*function)(bundle, actualPosition);
			actualPosition += this->typeSize;
		}
		this->list = (char*)realloc(this->list, this->typeSize);
		this->size = this->typeSize;
		memcpy(this->list, bundle, this->size);

		// free(bundle);
		// Al hacer el free del malloc pedido y asignado a bundle, el programa se rompe
		// con el siguiente error y no se entiende el motivo. Dejo el codigo comentado.

		//  console Error  *** free(): invalid next size (fast)  ***
	}
	return this;
}

// ENTREGA 4

void collection_intersection(Collection* this, Collection* secondary) {
	unsigned elementsCount = this->size / this->typeSize;
	void* newMem = malloc(this->size);
	void* newMemTravellPointer = newMem;
	unsigned newFinalSize = 0;
	void* primaryPointer = this->list;
	while(elementsCount--) {
		if(collection_find(secondary, primaryPointer) != 0) {
			memcpy(newMemTravellPointer, primaryPointer, this->typeSize);
			newMemTravellPointer += this->typeSize;
			newFinalSize += 1;
		}
		primaryPointer += this->typeSize;
	}
	if(newFinalSize != 0) {
	newMem = realloc(newMem, newFinalSize * this->typeSize);
	free(this->list);
	collection_update(this, newMem, newFinalSize * this->typeSize, this->typeSize);
	return;
	}
	free(newMem);
}


// Primitivas adicionales

// Se encarga de copiar valor por valor, los que cumplan con la condiciòn de la funciòn filter.
unsigned conditionalMemCpy(void* pointer1, void* pointer2, unsigned elementCount, unsigned size, int (*filter)(void*)){
	unsigned count = 0;
	while(elementCount--) {
		if((*filter)(pointer1) == 1){
			memcpy(pointer2, pointer1, size);
			pointer1+= size;
			pointer2+= size;
			count++;
		}else {
			pointer1+= size;
		}
	}
	return count;
}

void collection_clone(Collection* this, Collection* dst){
	free(this->list);
	this->list = dst->list;
	this->size = dst->size;
	this->typeSize = dst->typeSize;
}

void collection_init_clean(Collection* dst, unsigned size, unsigned typeSize){
	dst->size = size;
	dst->typeSize = typeSize;
	dst->list = (void*)malloc(dst->size);
	memset(dst->list, 0, dst->size);
}

void collection_update(Collection* this, char* newPointer, unsigned newSize, unsigned newTypeSize) {
	this->size = newSize;
	this->typeSize = newTypeSize;
	this->list = newPointer;
}




