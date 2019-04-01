#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class mList{

  private:

    struct node{
        int value;
        node* next;
    };

    node* top;

    node* createNode(int val) {
      node* temp = new node;
      temp->value = val;
      temp->next = NULL;
    }


  public:

    mList(){
      top = NULL;
    }

    ~mList(){
      delete[] top;
    }

    void addNode(int val){

      if(top == NULL){
        top = createNode(val);
        return;
      }

      node* prev = new node;
      prev->next = NULL;
      node* nex = new node;
      nex->next = NULL;
      node* add = createNode(val);

      prev = top;

      while(prev){

        if(val < top->value){
            add->next = top;
            top = add;
            return;
        }

        else if(val > prev->value && prev->next == NULL){
            prev->next = add;
            return;
        }

        else if(val < prev->next->value){
          nex = prev->next;
          prev->next = add;
          add->next = nex;
          return;
        }
        prev = prev->next;
      }


    }

    void print(){

      node* temp = createNode(top->value);
      temp = top;
      while(temp){
        cout << temp->value << ", ";
        temp = temp->next;
      }

    }

    void median(int size){

        node* temp = new node;
        temp = top;
        int loopIt = 0;
        while(loopIt < ((size-1)/2)){
            temp = temp->next;
            loopIt++;
        }
        cout << temp->value;

    }

    int* returnArray(int arr[]){

        node* temp = new node;
        temp = top;
        int index = 0;
        while(temp){
            arr[index] = temp->value;
            index++;
            temp = temp->next;
        }
    }

};



int main(){

  mList l;

  int curr;

  int size;
  cin >> size;

  while(cin >> curr){
    l.addNode(curr);
  }

  int intArr[size];
  int *ptr = l.returnArray(intArr);

  l.~mList();
  //cout << "median is " <<  intArr[(size-1)/2] << endl;
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //algo begins


  srand(getpid());

  int fd = open("/dev/urandom", O_RDWR);
  unsigned int value;

  float algo1HitAverage = 0.0;
  float algo2HitAverage = 0.0;

  for(int i = 0; i < 500; i++){
    // algo1
    bool algoHit = false;
    float algoMiss = 0.0;

    while(!algoHit){
     int in = rand() % size;
     if (in == (size-1)/2){
       algoHit = true;
     }
     else{
       algoMiss += 1.0;
     }
    }
    algo1HitAverage += algoMiss/500.0;

    algoHit = false;
    algoMiss = 0.0;

    while(!algoHit){
      read(fd, &value, sizeof(value));
      int in = value % size;
      if (in == (size-1)/2){
        algoHit = true;
      }
      else{
        algoMiss += 1.0;
      }
    }
    algo2HitAverage += algoMiss/500.0;

  }

  float algo3HitAverage = 0.0;
  float algo4HitAverage = 0.0;



  for(int i = 0; i < 500; i++){

    int done[size] = {0};
    bool algoHit = false;
    float algoMiss = 0.0;

    while(!algoHit){
      // read(fd, &value, sizeof(value));
      // int in = value % size;
      int in = rand() % size;

      if(done[in] != 1){
        if (in == (size-1)/2){
          algoHit = true;
        }
        else{
          done[in] = 1;
        }
        algoMiss += 1.0;
      }

    }
    algo3HitAverage += algoMiss/500;

    algoHit = false;
    algoMiss = 0.0;

    int done1[size] = {0};

    while(!algoHit){
      read(fd, &value, sizeof(value));
      int in = value % size;

      if(done1[in] != 1){
        if (in == (size-1)/2){
          algoHit = true;
        }
        else{
          done1[in] = 1;
        }
        algoMiss += 1.0;
      }
    }

    algo4HitAverage += algoMiss/500;

  }

  cout << algo1HitAverage << " ";
  cout << algo2HitAverage << " ";
  cout << algo3HitAverage << " ";
  cout << algo4HitAverage << endl;


  return 0;

}
