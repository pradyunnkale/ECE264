// ***
// *** You MUST modify this file
// ***

#include "solver.h"
#include "list.h"
#include "mazehelper.h"
#include "path.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

PathLL* solveMaze(Maze* m) {

    PathLL* successPaths = buildPaths();
    char* retval = malloc(((m->height * m->width) + 1) * sizeof(char));

    MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
    depthFirstSolve(m, mp, retval, 0, successPaths);

    free(retval);

    return successPaths;
}

void depthFirstSolve(Maze* m, MazePos curpos, char* path, int step,
                     PathLL* successPaths) {
	// TODO (Your best bet is to modify a working implementation from HW9)
	if (!squareOK(curpos, m))
	{
		return;
	}

	if (atEnd(curpos, m))
	{
		path[step] = '\0';
		addNode(successPaths, path);
		return;
	}

	m->maze[curpos.ypos][curpos.xpos].visited = true;

	MazePos next;
	next = curpos;
	next.ypos -= 1;
	path[step] = NORTH;
	depthFirstSolve(m, next, path, step + 1, successPaths);

	next = curpos;
	next.ypos += 1;
	path[step] = SOUTH;
	depthFirstSolve(m, next, path, step + 1, successPaths);

	next = curpos;
	next.xpos += 1;
	path[step] = EAST;
	depthFirstSolve(m, next, path, step + 1, successPaths);

	next = curpos;
	next.xpos -= 1;
	path[step] = WEST;
	depthFirstSolve(m, next, path, step + 1, successPaths);

	return;
}
