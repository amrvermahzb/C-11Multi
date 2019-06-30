#include <iostream>
#include <thread> 
#include <vector>
#include <mutex>

using namespace std;
int seme=0,semo=1;
int semFill=0,semEmpty=10;
int semp=1,semc=0;
mutex mtx,prodConsMtx;
