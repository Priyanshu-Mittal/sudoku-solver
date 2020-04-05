/*

SUDOKU SOLVER
You are given an N*N sudoku grid (N is a multiple of 3). Solve the sudoku and print the solution.

Input Format:
First line contains a single integer N. Next N lines contains N integers each, where jth integer int ith line denotes the value at ith row and jth column in sudoku grid. This value is 0, if the cell is empty.

Constraints:
 Solution exists for input matrix.

Output Format:
Print N lines containing N integers each, where jth integer int ith line denotes the value at ith row and jth column in sudoku grid, such that all cells are filled.

Sample Input
9 
5 3 0 0 7 0 0 0 0 
6 0 0 1 9 5 0 0 0 
0 9 8 0 0 0 0 6 0 
8 0 0 0 6 0 0 0 3 
4 0 0 8 0 3 0 0 1 
7 0 0 0 2 0 0 0 6 
0 6 0 0 0 0 2 8 0 
0 0 0 4 1 9 0 0 5 
0 0 0 0 8 0 0 7 9

Sample Output
5 3 4 6 7 8 9 1 2 
6 7 2 1 9 5 3 4 8 
1 9 8 3 4 2 5 6 7 
8 5 9 7 6 1 4 2 3 
4 2 6 8 5 3 7 9 1 
7 1 3 9 2 4 8 5 6 
9 6 1 5 3 7 2 8 4 
2 8 7 4 1 9 6 3 5 
3 4 5 2 8 6 1 7 9

*/

#include<bits/stdc++.h>
using namespace std;

bool solveSudoku(int board[100][100], int i, int j, int n);
bool canPlace(int board[100][100], int i, int j , int n, int num);

int main()
{
	int n;
	cout<<"Enter no. of rows or columns:";
	cin >> n;													// number of rows/cols
	cout<<"Enter current matrix:(Replace empty places with 0):\n";
	int board[100][100];

	for(int i = 0 ;i < n ; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
			cin >> board[i][j];									// input sudoku
		}
	}

	solveSudoku(board, 0, 0, n);									// function call

	return 0;
}

bool solveSudoku(int board[100][100], int i, int j, int n)
{
	if(i == n)													// solved all rows - then print matrix
	{	cout<<"\nSudoku Solved..\n";
		cout<<"Solution:\n";
		for(int x = 0 ; x < n ; x++)
		{
			for(int y = 0 ; y < n ; y++)
			{
				cout << board[x][y] << " ";
			}
			cout << endl;
		}
		return true;											// true for solution
	}

	if(j == n)													// if at end of row - then shift to another row(i+1) and start from 0th(j) col
	{
		return solveSudoku(board, i+1, 0, n);
	}

	if(board[i][j] != 0)											// if number already in sudoku - then dont overwrite
	{
		return solveSudoku(board, i, j+1, n);
	}

	for(int number = 1; number <= n ; number++)					// for all numbers 
	{
		if(canPlace(board, i, j, n, number))						// if you can place that number on sudoku
		{
			board[i][j] = number;									// place number
			if(solveSudoku(board, i, j+1, n) == true)				// if could solve - retus true
			{
				return true;
			}
		}
	}

	board[i][j] = 0;												// if no number could solve - then backtrack
	return false;												// retus false
}

bool canPlace(int board[100][100], int i, int j , int n, int number)
{
	for(int x = 0 ; x < n ; x++)								// check if that number exists in row or col
	{
		if(board[x][j] == number || board[i][x] == number)
		{
			return false;										// if exist retus false
		}
	}

	int s = sqrt(n);											// side of grid
	int sx = (i / s) * s;										// start of x
	int sy = (j / s) * s;										// start of y

	for(int x = sx ; x < sx + s ; x++)							// loop to check in that grid for number
	{
		for(int y = sy ; y < sy + s ; y++)
		{
			if(board[x][y] == number)								// if number exits - retus false
			{
				return false;
			}
		}
	}

	return true;												// does not exist anywhere - retus true
}