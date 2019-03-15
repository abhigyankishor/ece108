#include <iostream>

using namespace std;

int main(){
// take size of adjacency matrix
	int size;
	cin >> size;
// setup variables curr for current int passed, lCount for current position in line, row for current row number        
	int curr;
	int adMat[size][size] = {0};
	int lCount = 1;
	int row;

//setting all values of adjaceny matrix to be 1
	for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                                adMat[i][j] = 0;
                };
                
        };

//while loops till there is still a file element, lCount is 1 initially and set to 1 once 0 is encountered. Row selects its value only when lCount is 1, else we populate the the rest of the row.
	while(cin >> curr){
			
		if(curr == 0){
			lCount = 1;
		}

		else if(lCount == 1){
			row = curr-1;
			lCount ++;
		}

		else{
			lCount++;
			adMat[row][curr-1] = 1;
		}
		
		
	};
		
//reflexive case
	for(int i = 0; i < size; i++){
		adMat[i][i] = 1;	
	};

//transitive case
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			for(int k = 0; k < size; k++){
				if(adMat[i][j] && adMat[j][k] && i != j){
					adMat[i][k] = 1;
				};
			};
		};
	};

//done once again to ensure any inferred cases are considered	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			for(int k = 0; k < size; k++){
				if(adMat[i][j] && adMat[j][k] && i != j){
					adMat[i][k] = 1;
				};
			};
		};
	};


//setup another adjacency matrix set to 0 to prevent noise
	int ad[size][size] = {0};
	
	for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                                ad[i][j] = 0;
                };
                
        };

//create a register for the used variables from adMat so they are not transferred as a smaller adjacency class. Intially all indices have a value of 0. As they are used up they are set to 1 and so they are not looked at again saving time.
	int adRel[size] = {0};
	
	for(int i = 0; i < size; i++){
		adRel[i] = 0;
	};

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(adMat[i][j] && adMat[j][i] and adRel[j] != 1){
				adRel[j] = 1;
				ad[i][j] = 1;
			};
		};		
	};

//output loop. isFirst is created to check whether element is first in the output. Easir to remove a trailing by creating an if to see this condition satisfied or not. Only place , when its not isFirst
	bool isFirst = true;
	for(int i = 0; i < size; i++){
                if(adRel[i] == 1){
                        cout << "{";
			isFirst = true;
                        for(int j = 0; j < size; j++){
                                if(ad[i][j] == 1){
                                        adRel[j] = 0;
                                       if(isFirst == true){
				       		cout << j+1;
						isFirst = false;
				       }
				       else{
				       		cout << ", " << j+1;
				       }
                                }
                        };
			cout << "}" << endl;
                };
        };


	return 0;

}

