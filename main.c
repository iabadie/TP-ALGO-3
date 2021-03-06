#include "Collection.h"
#include <stdio.h>

//Functions

void showElement(void* pointer) {
			double* p = pointer;
			printf("%f\n", *p);
		}

void sumElements(void* previous, void* actual){
			*(double*)previous = *(double*)previous + *(double*)actual;
}

int filterFunction(void* pointer){
	if(*(double*)pointer >= 3.0){
			return 1;
	}
	return 0;
}

void duplicate(void* pointer) {
	double* p = pointer;
	*p = *p * 2;
}

void applyFunction(void* pointer) {
	*(double*)pointer = 2 * *(double*)pointer;
}

int main(int argc, char** argv) {
	{
		//Test - collection_init  - initialize the collection with any received data
		printf("Test collection_init :\n");
		//Data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		//print results to show works fine
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	{
		//Test - collection_free - free memory allocated by Collection TDA
		printf("Test collection_free :\n");
		//Data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		collection_free(&collection);
		printf("---------------\n");
	}

	{
		//Test - collection_add  - Add a element data on Collection list
		printf("Test collection_add :\n");
		//Data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		double element = 6.6;
		void* pointerElement = &element;

		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		collection_add(&collection, pointerElement);
		//print results to show works fine
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	{
		//Test - collection_remove  - Remove a element data on Collection list
		printf("Test collection_remove :\n");
		//Data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		double removeElement = 2.2;
		char* removePointerElement = (char*)&removeElement;

		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		collection_remove(&collection, removePointerElement);
		//print results to show works fine
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	{
		//Test - collection_iterate  -  Iterate the Collection list applying a local function at each element
		printf("Test collection_iterate :\n");
		//Data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		//functions


		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		//print results to show works fine
		collection_iterate(&collection, &duplicate);
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	//ENTREGA 2 ------------------------

	{
		//Test - collection_find  -  Iterate the Collection and return the searched value
		printf("Test collection_find :\n");
		//Data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		double elementToFind = 2.2;
		char* elementToFindPointer = (char*)&elementToFind;


		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		double* toShow = (double*)collection_find(&collection, elementToFindPointer);
		//print results to show works fine
		printf("Find: \nDir: %p\nVal: %f\n", toShow, *toShow);
		printf("---------------\n");
	}

	{
		//Test - collection_select  -  Iterate the Collection and return a filtered by a parameter criterian collection in a new Collection
		printf("Test collection_select :\n");

		//data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };


		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));

		Collection collection2;
		collection_select(&collection, &collection2, &filterFunction);
		//print results to show works fine
		collection_iterate(&collection2, &showElement);
		printf("---------------\n");
	}

	{
		//Test - collection_collect  -  Iterate the Collection list applying a local function at each element
		printf("Test collection_collect :\n");
		//data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));

		Collection collection2;
		collection_collect(&collection, &collection2, &applyFunction);
		//print results to show works fine
		collection_iterate(&collection2, &showElement);
		printf("---------------\n");
	}

	// ENTREGA 3

	{
		//Test - collection_filter  -  Iterate the Collection list applying a local function at each element
		printf("Test collection_filter :\n");
		//data
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		//Collection test
		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));

		//collection_iterate(&collection, &showElement);
		collection_filter(&collection, &filterFunction);
		//print results to show works fine
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	{
		// Test - reduce_right

		printf("Test colection_reduce_right: \n");
		double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };

		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		collection_reduce_right(&collection, &sumElements);
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	{
		// Test - reduce_left

		printf("Test colection_reduce_left: \n");
		double data[] = { 1.1, 2.2, 3.3, 4.4 };
		//declared function


		Collection collection;
		collection_init(&collection, (char*)data, sizeof(data), sizeof(double));
		collection_reduce_left(&collection, &sumElements);
		collection_iterate(&collection, &showElement);
		printf("---------------\n");
	}

	{
		// Test - colection_intersection

		printf("Test colection_intersection: \n");
		double data1[] = { 1.1, 2.2, 3.3, 4.4 };
		double data2[] = { 5.3, 1.1, 3.3, 4.5 };
		//declared function

		//declared collection1
		Collection collection1;
		collection_init(&collection1, (char*)data1, sizeof(data1), sizeof(double));
		//declared collection 2
		Collection collection2;
		collection_init(&collection2, (char*)data2, sizeof(data2), sizeof(double));
		collection_intersection(&collection1, &collection2);
		collection_iterate(&collection1, &showElement);
		printf("---------------\n");
	}

	{
		//Test - Join

		printf("Test colection_join: \n");

		double data1[] = { 1.1, 2.2, 3.3, 4.4 };
		double data2[] = { 5.5, 6.6, 7.7, 8.8 };

		Collection collection;
		collection_init(&collection, (char*)data1, sizeof(data1), sizeof(double));

		Collection collection2;
		collection_init(&collection2, (char*)data2, sizeof(data2), sizeof(double));

		collection_join(&collection, &collection2);

		collection_iterate(&collection, &showElement);
	}

	return 0;
}

