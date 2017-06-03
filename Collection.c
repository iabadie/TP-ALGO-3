#include "Collection.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//ENTREGA 1

Collection* collection_init(Collection* this, char* data, unsigned dataLength, unsigned typeSize) {
	this->size = dataLength;
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
		this->list = 0;
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
	collection_init(dst, memPointer, count*this->typeSize, this->typeSize);
	free(memPointer);
	return dst;
}

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

Collection* collection_collect(Collection* this, Collection* dst, void (*function)(void*)) {
	void* memPointer = (char*)malloc(this->size);
	memcpy(memPointer, this->list, this->size);
	collection_init(dst, memPointer, this->size, this->typeSize);
	collection_iterate(dst, function);
	free(memPointer);
	return dst;
}

void collection_filter(Collection* this, void (*filterFunction)(void*)){
	if(this->size != 0 && this->list){
		free(this->list);
		this = collection_select(this, this, filterFunction);
	}

}









