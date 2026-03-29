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
    if (p == NULL || p->head == NULL)
    {
        free(p);
        return;
    }
    PathNode * next= p->head->next;
    free(p->head);
    p->head = next;
    freePaths(p);
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
		free(p);	
}

bool addNode(PathLL* paths, char* path) {
    // Add a path to the list of paths
    // TODO
		if (paths == NULL)
		{
			return false;
		}
		PathNode* node = buildNode(path);
		if (node == NULL)
		{
			return false;	
		}
		node->next = paths->head;
		paths->head = node;
    return true;
}

bool removeNode(PathLL* paths, char* path) {
    // Remove a node from the list with the specified path
    // TODO
		if (paths == NULL)
		{
			return false;	
		}

		PathNode* curr = paths->head;
		PathNode* next = paths->head->next;
		PathNode* prev = NULL;
		while (curr != NULL && strcmp(curr->path, path) != 0)
		{
			prev = curr;
			curr = curr->next;
			next = curr->next;
		}

		if (curr == NULL)
		{
			return false;
		}

		if (curr == paths->head)
		{
			paths->head = next;			
			free(curr);
		}
		else if (curr->next = NULL)
		{
			prev->next = NULL;	
			free(curr);
		}
		else
		{
			prev->next = next;		
			free(curr);
		}
		return true;
}

bool containsNode(PathLL* paths, char* path) {
    // Return true if path exists in the list
    // TODO
		
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
