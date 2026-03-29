// ***
// *** You MUST modify this file
// ***

#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** INTERFACE FUNCTIONS **/

PathLL* buildPaths() {
    PathLL* retval = malloc(sizeof(PathLL));
    retval->head = NULL;
    return retval;
}

// Read the comments in list.h to understand what you need to implement
// for each function.
// Remember to check for memory leak.

void freePaths(PathLL* p) {
	// Remove all nodes from a linked list, deallocate the PathLL structure.
	// TODO
	PathNode * curr = p->head;
	while (curr != NULL)
	{
		PathNode * next = curr->next;		
		free(curr);
		curr = next;
	}
	free(p);
	return;
}

PathNode* buildNode(char* path) {
	// Allocate a new PathNode with path as its data, return the address.

	// WARNING: don't forget to use strcpy to copy path into the new node.
	// Don't just set them equal, otherwise if the input path changes the node
	// will have the wrong path.

	// TODO
	PathNode* node = malloc(sizeof(PathNode));
	if (node == NULL)
	{
		return NULL;		
	}
	strcpy(node->path, path);
	node->next = NULL;
	return node;
}

void freeNode(PathNode* p) {
	// Deallocate a pathNode
	// TODO
	
	// Not sure if the inside of PathNode is memory allocated
	free(p);	
}

bool addNode(PathLL* paths, char* path) {
	// Add a path to the list of paths
	// TODO
	// Check if the address is valid
	if (paths == NULL)
	{
		return false;	
	}
	// Append path
	PathNode * curr = paths->head;
	while(curr->next != NULL)
	{
		curr = curr->next;	
	}
	curr->next = buildNode(path);
	return true;
}

bool removeNode(PathLL* paths, char* path) {
	// Remove a node from the list with the specified path
	// TODO
	if (paths == NULL)
	{
		return false;	
	}

	PathNode * curr = paths->head;
	PathNode * prev = NULL;
	PathNode * next = curr->next;
	while (curr->next != NULL && strcmp(curr->path, path) != 0)
	{
		prev = curr;
		curr = next;				
		next = curr->next;
	}

	if (!strcmp(curr->path, path))
	{
		if (prev == NULL)
		{
			paths->head = next;		
		}
		else
		{
			prev->next = next;	
		}
		free(curr);
		return true;
	}
	return false;
}

bool containsNode(PathLL* paths, char* path) {
	// Return true if path exists in the list
	// TODO
	if (paths == NULL)
	{
		return false;	
	}

	PathNode * curr = paths->head;
	while (curr != NULL)
	{
		if (!strcmp(path, curr->path))
		{
			return true;	
		}
		curr = curr->next;
	}
	return false;
}

void printPaths(PathLL* paths, FILE* fptr) {
    PathNode* curr = paths->head;
    int i = 0;
    while (curr != NULL) {
        fprintf(fptr, "Path %2d: %s\n", i, curr->path);
        i++;
        curr = curr->next;
    }
}
