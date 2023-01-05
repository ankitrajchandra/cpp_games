#include<bits/stdc++.h>

using namespace std;

void printTicTac(char* c){
    cout<<c[0]<<"|"<<c[1]<<"|"<<c[2]<<endl;
    cout<<"-----"<<endl;
    cout<<c[3]<<"|"<<c[4]<<"|"<<c[5]<<endl;
    cout<<"-----"<<endl;
    cout<<c[6]<<"|"<<c[7]<<"|"<<c[8]<<endl;
}

int thirdOne(int x, int y){
    if(x == y) return -1;
    int a = min(x, y);
    int b = max(x, y);
    if(a == 0){
        if(b == 1) return 2; if(b == 2) return 1;
        if(b == 3) return 6; if(b == 6) return 3;
        if(b == 4) return 8; if(b == 8) return 4;
    }
    if(a == 1){
        if(b == 2) return 0;
        if(b == 4) return 7; if(b == 7) return 4;
    }
    if(a == 2){
        if(b == 4) return 6; if(b == 6) return 4;
        if(b == 5) return 8; if(b == 8) return 5;
    }
    if(a == 3){
        if(b == 4) return 5; if(b == 5) return 4;
        if(b == 6) return 0;
    }
    if(a == 4){
        if(b == 5) return 3;
        if(b == 6) return 2;
        if(b == 7) return 1;
        if(b == 8) return 0;
    }
    if(a == 5 && b == 8) return 2;
    if(a == 6){
        if(b == 7) return 8; if(b == 8) return 7;
    }
    return -1;
}

int interface(char *c){
    printTicTac(c);
    cout<<"Your Turn: "<<endl;
    int input;
    cin>>input;
    while(c[input - 1] == 'X' || c[input-1] == 'O'){
        cout<<"invalid input. Try Again: ";
        cin>>input;
    }
    c[input-1] = 'X';
    return input - 1;
}

bool play(char* c){
    int userMove[4] = {-1, -1, -1, -1}, computerMove[4] = {-1, -1, -1, -1};

    // Move 1
    userMove[0] = interface(c);
    if(userMove[0] == 4) {
        c[0] = 'O';
        computerMove[0] = 0;
    }
    else {
        c[4] = 'O';
        computerMove[0] = 4;
    }

    // Move 2
    userMove[1] = interface(c);
    int val = thirdOne(userMove[0], userMove[1]);
    if(val != -1 && c[val] != 'O') {
        c[val] = 'O';
        computerMove[1] = val;
    }
    else {
        for (int i = 0; i < 9; i++){
            val = thirdOne(computerMove[0], i);
            if(c[i] != 'X' && c[i] != 'O' && c[val] != 'O' && c[val] != 'X'){
                if((thirdOne(userMove[0], i) == -1 || thirdOne(userMove[1], i) == -1) && val != -1){
                    c[val] = 'O';
                    computerMove[1] = val;
                    break;
                }
            }
        }
    }

    // Move 3
    userMove[2] = interface(c);

    val = thirdOne(computerMove[0], computerMove[1]);
    if(val != -1 && c[val] != 'X'){
        c[val] = '@'; c[computerMove[0]] = '@'; c[computerMove[1]] = '@';
        return false; 
    }

    val = thirdOne(userMove[2], userMove[0]);
    if(val != -1 && c[val] != 'O'){
        c[val] = 'O';
        computerMove[2] = val;
    }
    else {
        val = thirdOne(userMove[2], userMove[1]);
        if(val != -1 && c[val] != 0){
            c[val] = 'O';
            computerMove[2] = val;
        }
        else {
            for (int i = 0; i < 9; i++){
                val = thirdOne(computerMove[0], i);
                if(c[i] != 'X' && c[i] != 'O' && c[val] != 'O' && c[val] != 'X'){
                    int count = 0;
                    if(thirdOne(userMove[0], i) != -1) count++;
                    if(thirdOne(userMove[1], i) != -1) count++;
                    if(thirdOne(userMove[2], i) != -1) count++;
                    if( count < 2 && val != -1) {
                        c[val] = 'O';
                        computerMove[2] = val;
                        break;
                    }
                }
            }
        }
    }

    // Move 4
    userMove[3] = interface(c);

    val = thirdOne(computerMove[2], computerMove[0]);
    if(val != -1 && c[val] != 'X'){
        c[val] = '@'; c[computerMove[0]] = '@'; c[computerMove[2]] = '@';
        return false; 
    }

    val = thirdOne(computerMove[2], computerMove[1]);
    if(val != -1 && c[val] != 'X'){
        c[val] = '@'; c[computerMove[1]] = '@'; c[computerMove[2]] = '@';
        return false; 
    }

    val = thirdOne(userMove[3], userMove[0]);
    if(val != -1 && c[val] != 'O'){
        c[val] = 'O';
        return true;
    }
    
    val = thirdOne(userMove[3], userMove[1]);
    if(val != -1 && c[val] != 'O'){
        c[val] = 'O';
        return true;
    }

    val = thirdOne(userMove[3], userMove[2]);
    if(val != -1 && c[val] != 'O'){
        c[val] = 'O';
        return true;
    }

    return true;
}

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char move[9];
    move[0] = '1';
    for (int i = 1; i < 9; i++)
    {
        move[i] = move[i-1] + 1;
    }
    char temp[9];
    
    char state;
    while(1){
        for (int i = 0; i < 9; i++){
            temp[i] = move[i];
        }
        cout<<"Enter 'S' to start new game or any other key to exit: "<<endl;
        cin>>state;
        if(state == 'S'){
            if(play(temp)) {
                printTicTac(temp);
                cout<<"Match Draw"<<endl;
            }
            else{
                printTicTac(temp);
                cout<<"You Lost"<<endl;
            }
        }
        else break;
    }
    return 0;
}