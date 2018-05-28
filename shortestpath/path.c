#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_VALUE 0xFFFFFF
#define MAX_BUFF_SIZE 1024


int **matrix;
int *dist;
int *path;
int *visited;
int *stackArray;
int stackIndex = 0;

int initializeArrays(const int n);
int InsertNodeInfo(const int i, const int j, const int value);
void input();
void testPrintMatrix(const int n);
int choose(const int n);
void ShortedPath(const int n, const int start);
void PrintPath(const int n, const int start);
void Push(const int value);
int Pop();

int initializeArrays(const int n)
{
	int i,j;

	if ( n <= 0 ) return 0;

	// 배열 초기화
	matrix = (int**)malloc(sizeof(int*)*n);
	dist = (int*)malloc(sizeof(int)*n);
	path = (int*)malloc(sizeof(int)*n);
	visited = (int*)malloc(sizeof(int)*n);
	stackArray = (int*)malloc(sizeof(int)*n);


	for( i = 0 ; i < n ; i++ )
	{
		matrix[i] = (int*)malloc(sizeof(int)*n);

		for( j = 0 ; j < n ; j++ )
		{
			if(i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = MAX_VALUE;
		}
	}

	return 1;
}


int InsertNodeInfo(const int i, const int j, const int value)
{
	if (value <= 0) return 0;

	matrix[i][j] = value;

	return 1;
}



void input()
{
	int n;
	int from, to, value;
	char buf[MAX_BUFF_SIZE];
	FILE *in;

	//파싱할 데이터 읽는 부분
	if( (in = fopen("TestMakeMatrix.txt", "r")) == 0)
		return;

	//배열 사이즈
	memset(buf, 0, MAX_BUFF_SIZE);
	fgets(buf, MAX_BUFF_SIZE, in);

	n = atoi(buf);

	//배열 생성 및 초기화
	if( !initializeArrays(n) )
		fprintf(stdout, "Error make matrix\n");

	//배열 변수
	while(1)
	{
		memset(buf, 0, MAX_BUFF_SIZE);
		
		if( fgets(buf, MAX_BUFF_SIZE, in) == NULL ) break;
		
		from = atoi(strtok(buf, " "));
		to = atoi(strtok(NULL, " "));
		value = atoi(strtok(NULL, " "));

		if( !InsertNodeInfo(from-1, to-1, value) )
			fprintf(stdout, "Error Data Error\n");
	}


	ShortedPath(n, 0);
	//testPrintMatrix(10);
}

void testPrintMatrix(const int n)
{
	int i,j;

	for( i = 0 ; i < n ; i ++)
	{
		for ( j = 0 ; j < n ; j ++)
		{
			printf("%2d%s", matrix[i][j], (j == n) ? "\n" : " ");
		}
	}
}

int choose(const int n)
{
	int min = MAX_VALUE;
	int min_index = 0;
	int i;

	for( i = 0 ; i < n; i++ )
	{
		if(!visited[i])
		{
			if(min > dist[i])
			{
				min = dist[i];
				min_index = i;
			}
		}
	}

	return min_index;
}

void ShortedPath(const int n, const int start)
{
	int i, u, j;

	for( i = 0 ; i < n ; i++ )
	{
		visited[i] = 0;
		dist[i] = matrix[start][i];
		path[i] = start;
	}

	visited[start] = 1;
	dist[start] = 0;

	for( i = 0 ; i < n - 1 ; i++ )
	{
		u = choose(n);

		visited[u] = 1;
		
		for( j = 0 ; j < n ; j ++ )
		{
			if(!visited[j])
			{
				if(dist[u] + matrix[u][j] < dist[j])
				{
					dist[j] = dist[u] + matrix[u][j];
					path[j] = u;
				}
			}
		}
	}

	for( i = 0 ; i < n ; i++ )
	{
		printf("[%d]%d\n", (i+1), dist[i]); 
	}

	PrintPath(n, start);
}

void PrintPath(const int n, const int start)
{
	int i, j=0;

	for( i = 0 ; i < n ; i ++ )
	{
		if( i == start )
			continue;

		memset(stackArray, 0, n);
		stackIndex = 0;

		printf("정점 %d : ", i+1);

		if(dist[i] == MAX_VALUE)
		{
			printf("X\n");
			continue;
		}

		Push(MAX_VALUE);

		for(j = i; j != start; j = path[j])
			Push(j);

		printf("%d", start+1);

		for( j = 0; (j = stackArray[stackIndex-1]) != MAX_VALUE ; Pop() )
		{
			//if(j+1 > 0 && j != start)
				printf(" -> %d", j+1);
		}

		printf("\n");
	}


}

void Push(const int value)
{
	stackArray[stackIndex++] = value;
}

int Pop()
{
	return stackArray[stackIndex--];
}
