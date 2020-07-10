#include<iostream>
#include<iomanip>
using namespace std;
#define pinite_num 4//Number of memory blocks, you can choose the size according to the situation.
const int sequ[20]={7,5,1,2,5,3,5,4,2,3,5,3,2,1,2,5,1,7,5,1};//Preset the page number to be called
int pinite[pinite_num];//Memory block array
int Mispg[20];//The sequence of pages that are swapped out
int Mispg_num=0;//Lack of page times
double Mispg_prc;//Page Fault Rate
int pr=0;
//int count=0;
//int replace[20];
//===============================================================

void Optimal()
{
 cout<<"optimal algorithm"<<endl;
 int i=0;//Memory block array index
 int j;//Preloaded page number array index
 int k=0;//Missing page sequence array index
 for(j=0;j<20;++j)
 {
  if(i<pinite_num)//When the block is not full, the page number is placed directly into the block
  {
   pinite[i]=sequ[j];
   ++i;
   ++Mispg_num;
  }
  else
  {
   int a=0;
   while(pinite[a]!=sequ[j]&&a<4)//Find out if the page number is in a block of memory
    ++a;
   if(a<4)//The page number is already in the block of memory
    continue;
   else
   {
    int b[4];//The page number in the memory block is in the next used location
    int h=j;
    while(sequ[h]!=pinite[0]&&h<20)
     ++h;
    b[0]=h;
    h=j;
    while(sequ[h]!=pinite[1]&&h<20)
     ++h;
    b[1]=h;
    h=j;
    while(sequ[h]!=pinite[2]&&h<20)
     ++h;
    b[2]=h;
    h=j;
    while(sequ[h]!=pinite[3]&&h<20)
     ++h;
    b[3]=h;
    int max_x=0;//Finally, locate the memory number where the page number is to be swapped out
    int max=b[0];
    for(int c=0;c<4;++c)
     if(b[c]>max)
     {max=b[c];max_x=c;}
    Mispg[k]=pinite[max_x];
    pinite[max_x]=sequ[j];
    ++Mispg_num;
    ++k;
   }
  }
 }
 Mispg_prc=Mispg_num/20.0;
 Mispg[k]='\0';
}
//--------------------------------------------------------------
void FIFO()
{
 cout<<"FFIO algorithm"<<endl;
 int i=0;//Memory block array index
 int j;//Preloaded page number array index
 int k=0;//Missing page sequence array index
 for(j=0;j<20;++j)
 {
  if(i<pinite_num)//When the block is not full, the page number is placed directly into the block
  {
   pinite[i]=sequ[j];
   ++i;
   ++Mispg_num;
  }
  else//Page missing interrupts and substitutions occur when the block is full
  {
   int a=0;
   while(pinite[a]!=sequ[j]&&a<4)//Find out if the page number is in a block of memory
    ++a;
   if(a<4)//The page number is already in the block of memory
    continue;
   else
   {
    Mispg[k]=pinite[0];
    pinite[0]=pinite[1];
    pinite[1]=pinite[2];
    pinite[2]=pinite[pinite_num-1];
    pinite[pinite_num-1]=sequ[j];
    ++Mispg_num;
    ++k;
   }
  }
}
 Mispg_prc=Mispg_num/20.0;
 Mispg[k]='\0';
}
//--------------------------------------------------------------

void LRU()
{
 cout<<"Least Recently Used algorithm"<<endl;
    for (int i=0;i<20;i++)
    {
        //there are 3 memory pages in memory ,so if i<3,just put it in memory
        if(i<4)
        {
            pinite[i]=sequ[i];
            Mispg_num++;
        }
        else
        {
            //check if this page is in memory already
            bool exist=false;
            for(int j=0;j<4;j++)
            {
                if(sequ[i]==pinite[j])
                {
                    exist=true;
                    break;
                }
            }
            if (exist==false)
            {
                //begin to choose a memory page to replace
                int last=0;
                bool ok[4];
                for (int j=0;j<4;j++) ok[j]=false;

                //check from i step -1 till 0
                for(int j=i;j>=0;j--)
                {
                    for(int k=0;k<4;k++)
                    {
                        if (sequ[j]==pinite[k])
                        {
                            ok[k]=true;
                            last++;
                            break;
                        }
                    }
                    if (last==2)break;
                }
                //check which ok ==false
                for (int j=0;j<4;j++)
                {
                    if (ok[j]==false)
                    {
                        //replace this memory[j]
                        Mispg_num++;
                        Mispg[pr]=pinite[j];
                        pr++;
                        pinite[j]=sequ[i];
                        break;
                    }
                }

            }
        }
        //output
        cout<<sequ[i]<<":  [ ";
        for(int j=0;j<4;j++)
        {
            if (pinite[j]==-1) cout<<"*  ";
            else cout<<pinite[j]<<"  ";
        }
       cout<<sequ[i]<<":  ] ";
    }

 //out put
    cout<<"######################"<<endl;
    cout<<"the lack page Mispg_num = " <<Mispg_num<<endl;
    cout<<"repalce pages are  : ";
    for (int i=0;i<pr;i++)
    {
        cout<<Mispg[i]<<" ";
    }
    cout<<endl;
    //cout<<"the rate of page lack is "<<Mispg_num/12.0*100<<"%"<<endl;
Mispg_prc=Mispg_num/20.0;
}

//---------------------------------------------------------------
void print()
{
 cout<<"Number of page missing interrupts："<<Mispg_num<<"     Page Fault Rate :"<<Mispg_prc<<endl;
 cout<<"Replace the page number sequence： ";
 int k=0;
 while(Mispg[k]!='\0')
 {cout<<Mispg[k]<<" ";++k;}
 cout<<endl;
}
//-------------------------------------------------------------
void reset()//Zero the block of memory, the page number being replaced, and the page missing rate for reuse
{
 for(int i=0;i<pinite_num;++i)
  pinite[i]='\0';
 for(int j=0;j<20;++j)
  Mispg[j]='\0';
 Mispg_num=0;
}

int main()
{
 cout<<setw(18)<<"Page replacement algorithm simulation"<<endl;
 char a='y';
 while(a=='y'||a=='Y')
 {
  cout<<"1. Optimal replacement algorithm 2. Fifo algorithm 3. Least Recently Used algorithm" <<endl;
  cout<<"Select the page replacement algorithm:";
  int chiose;
  cin>>chiose;
  switch(chiose)
  {
  case 1:Optimal();print();reset();break;
  case 2:FIFO();print();reset();break;
  case 3:LRU();print();reset();break;
  default:cout<<"@select error！"<<endl;
  };
  cout<<endl<<"yes（y|Y）no go on: ";
  cin>>a;
  cout<<endl;
 }
}
