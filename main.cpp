#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

using namespace std;

/*
    Author: Madhav Prasad Dhimal
*/

const int width = 100;
const int height = 30;

void BlankMap(){

    int i;
    int j;
    ofstream File;
    File.open("Map.txt");

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            File << "0";
        }
        File << "\n";
    }
    

    File.close();
}

void Import(char Map[30][100]){

    int i;
    int j;

    string line;

    ifstream File;
    File.open("Map.txt");

    for(i = 0; i < height; i++){
        getline(File, line);
        for(j = 0; j < width; j++){
            Map[i][j] = line[j];
        }
    }
    cout << "\n\n";
    File.close();
}

void Print(char Map[30][100]){

    int i;
    int j;

    cout << "\n\n\n\n\n\n\n\n\n\n\n";

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if(Map[i][j] == '0'){
                cout << "o";
            }
            else{
                cout << "#";
            }
        }
        cout << "\n";
    }

}

bool Stable(char Map[30][100], int x, int y){

    int i;
    int j;

    int count = -1;

    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
            if(x+i >= 0 && x+i < height && y+j >= 0 && y+j < width && Map[x+i][y+j] == '1'){
                count++;
            }
        }
    }

    if(count == 2 || count == 3){
        return true;
    }
    else{
        return false;
    }

}

bool Revive(char Map[30][100], int x, int y){
    
    int i;
    int j;

    int count = 0;

    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
            if(x+i >= 0 && x+i < height && y+j >= 0 && y+j < width && Map[x+i][y+j] == '1'){
                count++;
            }
        }
    }

    if(count == 3){
        return true;
    }
    else{
        return false;
    }

}

void Logic(char Map[30][100], char NextMap[30][100]){

    int i;
    int j;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if(Map[i][j] == '1' && !Stable(Map, i, j)){
                NextMap[i][j] = '0'; // Dies
            }
            else if(Map[i][j] == '0' && Revive(Map, i, j)){
                NextMap[i][j] = '1'; // Revives
            }
            else{
                NextMap[i][j] = Map[i][j];
            }
        }
    }

}

void Swap(char Map[30][100], char NextMap[30][100]){

    int i;
    int j;
    char temp;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            temp = Map[i][j];
            Map[i][j] = NextMap[i][j];
            NextMap[i][j] = Map[i][j];
        }
    }
}

bool done(char Map[30][100], char NextMap[30][100]){

    int i;
    int j;

    int count = 0;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if(Map[i][j] == NextMap[i][j]){
                count++;
            }
        }
    }
    if(count == 3000){
        return true;
    }
    return false;
}

int main(int argc, char *argv[]){

    int i;
    int j;

    char Map[30][100];

    char NextMap[30][100];

    if(strcmp(argv[1], "1") == 0){
        BlankMap();
    }
    else if(strcmp(argv[1], "2") == 0){
        RandomMap();
    }
    
    Import(Map);


    Print(Map);

    while(!done(Map, NextMap)){
        usleep(100000);
        Logic(Map, NextMap);
        Print(NextMap);
        swap(Map, NextMap);
    }


    return 0;
}
