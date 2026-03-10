// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"
#include "mazehelper.h"
#include "maze.h"

char * solveMaze(Maze * m) {
    //An obvious upper bound on the size of the solution path is the number
    //of squares in the maze + 1 (to account for the '\0'). You could make
    //this a tighter bound by accounting for how many walls there are, but
    //this approach is good enough!
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		free(retval);
		return NULL;
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	if (curpos.xpos == m->end.xpos && curpos.ypos == m->end.ypos)
	{
		path[n] = '\0';
		// Might need to free something
		return;
	}

	m->maze; // 2D Array for the maze 
	m->width; // Columns in maze
	m->height; // Rows in maze
	m->start; // Location of 's'
	m->end; // Location of 'e'
	
	depthFirstSolve(m, curpos, path, step + 1);
	
	return false;
}

