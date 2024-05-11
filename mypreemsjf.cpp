#include<bits/stdc++.h>

using namespace std;

#define M 20

int n;
string process[M];
int arrival[M];
int completion[M];
int turnaround[M],waiting[M];
int burst[M];
float tsum=0,wsum=0;


int main()
{

    cout <<"numeber of process:";
    cin>>n;
    cout<<"Enter the process:";
    for(int i=0;i<n;i++)
    {
        cin>>process[i];
    }
     cout<<"Enter the burst time:";
    for(int i=0;i<n;i++)
    {
        cin>>burst[i];
    }

    cout<<"Enter the arrival time:";

    for(int i=0;i<n;i++)
    {
        cin>>arrival[i];
    }
    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {
            if (burst[j] > burst[j + 1]) {
                swap(burst[j], burst[j + 1]);
                swap(process[j],process[j+1]);
            }
        }
    }
    completion[0]=0;
    for(int i=1;i<=n;i++)
    {
        completion[i]=completion[i-1]+burst[i-1];
    }

    for(int i=0;i<n;i++)
    {
        turnaround[i]=completion[i+1]-arrival[i];
        cout<<process[i]<<"...turnaround..time.."<<turnaround[i]<<endl;
        tsum+=turnaround[i];
    }

    for(int i=0;i<n;i++)
    {
        waiting[i]=turnaround[i]-burst[i];
        cout<<process[i]<<"...waiting...."<<waiting[i]<<endl;
        wsum+=waiting[i];
    }
    cout <<"Gant chart:"<<endl;
    for(int i=1;i<=n;i++)
    {
      cout<<  completion[i-1] <<"......."<< process[i-1] <<".....";
    }
    cout<<completion[n]<<endl;

    cout<<"average turn around:"<<(tsum/n)<<endl;
    cout<<"average waiting around:"<<(wsum/n)<<endl;



}





