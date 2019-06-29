#include <iostream>
#include <thread> 
#include <vector>
#include <mutex>

using namespace std;
int seme=0,semo=1;
int semFill=0,semEmpty=10;
int semp=1,semc=0;
mutex mtx,prodConsMtx;
class tc{
  int k;
  int count;
  int buffer[10];
  int idx;
  public :
  tc(int l):k(l),count(l),idx(-1){
      
      for(int i=0;i<10;i++)
      {
          buffer[i]=100;
      }
  }
  
  void tfunc(int n){
       for(int i=0;i<n;i++)
       {
           k++;
       }
  }
  
  void odd()
  {
      while(count< 100)
      {
      mtx.lock();
      if(semo== 1)
      {
      count++;
      cout<<" ODD-"<<count;
      }
      seme=1;
      semo=0;
      mtx.unlock();
      }
  }
  void even()
  {
      while(count< 100 )
      {
      mtx.lock();
      if(seme==1)
      {
      count++;
      cout<<" Even-"<<count;
      }
      seme=0;
      semo=1;
      mtx.unlock();
      }
  }
  void producer()
  {
      while(semFill<10)
      {
          prodConsMtx.lock();
          if(semp==1)
          {
          cout<<"\n p-"<<semFill;
          buffer[semFill]= semFill+1;
          cout<<"-v="<<buffer[semFill];
          semFill++;
          semc=1;
          semp=0;
          }
          prodConsMtx.unlock();
      }
  }
  void consumer()
  {
      int ik=0;
      while(semEmpty >0)
      {
          prodConsMtx.lock();
          if(semc==1)
          {
              int idx=semFill-1;
              cout<<" c-"<<ik<<"-"<<buffer[ik];
              semc=0;
              semp=1;
              ik++;
              semEmpty--;
          }
          prodConsMtx.unlock();
      }
  }
 
 int getk(){ return k;}   
};

int checkRace()
{
 tc ob(0);
std::vector<thread> tlist;
for(int i=0;i<5;i++)
{
    tlist.push_back(thread(&tc::tfunc,&ob,1000));
}	
for(int i=0;i<5;i++)
{
    tlist[i].join();
}
cout<<" - "<<ob.getk();
return ob.getk();
    
}
int main() {
for(int i=0;i<10;i++)
{
  if(checkRace()!=5000)
  {
      cout<<"\n RACE CONDITION OCCURS";
  }
}
cout<<"\n came out successfully !!";


tc ob(0);
thread od(&tc::odd,&ob);
thread evn(&tc::even,&ob);
od.join();
evn.join();

cout<<"\n Producer Consumer Thread :\n";
tc ob1(0);
thread prod(&tc::producer,&ob1);
thread cons(&tc::consumer,&ob1);
prod.join();
cons.join();
	return 0;
}
