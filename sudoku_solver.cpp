#include <bits/stdc++.h>
using namespace std;

// function to check if 'num' is allowed at position (r, c)
bool allowed(int sudoku[9][9], int r, int c, int num){

    for (int i = 0; i < 9; i++){
        if(sudoku[r][i] == num) return false;
    }
    
    for (int i = 0; i < 9; i++){
        if(sudoku[i][c] == num) return false;
    }

    int r_start = r/3, c_start = c/3;
    r_start *= 3;
    c_start *= 3;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(sudoku[r_start + i][c_start + j] == num) return false;
        }  
    }
    return true;
}

// function to find blanks in the sudoku
bool findBlank(int sudoku[9][9], int &r, int &c){
    for (r = 0; r < 9; r++)
        for (c = 0; c < 9; c++)
            if (sudoku[r][c] == 0) return true;
    return false;
}

// recursive function to fill all numbers from 1 to 9 in the blanks. 
// returns true when the number entered turns out to be the correct.
bool solveSudoku(int sudoku[9][9]){
    int r, c;
    if (!findBlank(sudoku, r, c)) return true;
    for (int num = 1; num <= 9; num++){
        if (allowed(sudoku, r, c, num)){

            sudoku[r][c] = num;
            if (solveSudoku(sudoku)) return true;
            // reset the value to blank to able to pass the 'allowed' condition in the next interation
            sudoku[r][c] = 0;
        }
    }
    return false;
}

// print sudoku
void printSudoku(int sudoku[9][9]){
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++)
            cout << sudoku[r][c] << " ";
        cout << endl;
    }
}

int main(){

    int sudoku[9][9];

    cout<<"To input the sudoku, write the entries as a 9 X 9 matrix with 0 as blanks."<<endl;
    cout<<"Enter the unsolved sudoku: "<<endl;

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cin>>sudoku[i][j];
        }        
    }

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(sudoku[i][j] != 0){
                int temp = sudoku[i][j];
                sudoku[i][j] = 0;
                if(!allowed(sudoku, i, j, temp)){
                    cout<<"Invalid Entry";
                    return 0;
                }
                sudoku[i][j] = temp;
            }
        }        
    }
    
    if (solveSudoku(sudoku) == true) printSudoku(sudoku);
    else cout << "No solution exists";

    return 0;
}
