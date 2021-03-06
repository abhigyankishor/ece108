#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

int charToInt(char c){
 
    int n = int(c) - 48;
 
    return n;
}

int OR(int a, int b){
 
    return (a || b);
    
}

int AND(int a, int b){
    
    return (a && b);

}

int assignPolarity(int a){
    
    if(a>0){
        return 1;
    }
    else{
        return 0;
    }
}

int absolute(int a){
    return ((a >= 0) ? a : -1*a);
}

int *lineReturn(string dimacsLine, int varCount, int *arr){
    
    int i = 0;
    int index = 0;
    int isNeg = 1;
    int currParameter = 0;
    char c;
    while(i < dimacsLine.size()){
       
        c = char(dimacsLine[i]);
       
        if (index > varCount){
       
            return arr;
        }
       
        else if(c == ' '){
       
            arr[index] *= isNeg;
            index++;
            currParameter = 0;
            isNeg = 1;
        } 
       
        else if(c == '-'){
       
            isNeg = -1;
        }
       
        else if(int(c) >= 48 && int(c) <= 57){
       
            currParameter *= 10;
            currParameter += charToInt(c);
            arr[index] = currParameter;
        }
       
        else{
       
            return arr;
        }
       
        i++;
        
    }
    
}
int varCount(string dimacsLine){
    
    return charToInt(dimacsLine[0]);	

}	

bool cnf(string dimacsFile, int input[]){
    
    int parameters[2];
    fstream read;
    read.open(dimacsFile);
    string line = " ";
    getline(read,line);
    
    int *parPtr = lineReturn(line,2,parameters);
    int varCount = parameters[0];
    int clauseCount = parameters[1];
    
    int currAND = 1;

    for (int i = 1; i <= clauseCount; i++){
        
        int arr[varCount] = {0};
        getline(read,line);
        int *arrPtr = lineReturn(line,varCount,arr);
        
        int currOR = 0;
        int curr;
        
        
        for(int j = 0; j < varCount; j++){
            
            if (arr[j] == 0){
                continue;
                
            }
//variable overflow	    
	    if (absolute(arr[j]) > varCount){
		    return false;
	    }    
            curr = assignPolarity(arr[j]*input[absolute(arr[j])-1]);
            currOR = OR(curr, currOR);
           
        }
        currAND = AND(currOR, currAND);
    }
    
    
    read.close();
    
    return ((currAND > 0) ? true : false);
    
}

int main(int argc, const char *argv[]){
    
    fstream read;
    string line;
    read.open(argv[1]);
    getline(read,line);
    int inputSize = varCount(line);
    read.close();
    int input[inputSize];
        
    for(int i = 0; i < inputSize; i++){
        
        input[i] = atoi(argv[i+2]);
        
    }
    
    bool evaluate = cnf(argv[1], input);
    cout << evaluate;
    return 0;
}

