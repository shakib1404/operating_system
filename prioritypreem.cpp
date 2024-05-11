#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("input_for_scheduling.txt","r",stdin);
    int number_of_process;
    cin>>number_of_process;
    string process[number_of_process];
    int burst_time[number_of_process];
    int new_burst_time[number_of_process];
    int priority[number_of_process];
    int arrival_time[number_of_process];
    int i,j,k;
    for(i=0;i<number_of_process;i++){
        cin>>process[i]>>burst_time[i]>>priority[i]>>arrival_time[i];
        new_burst_time[i]=burst_time[i];
    }
    int start_time[number_of_process];
    int finish_time[number_of_process];
    int check_done[number_of_process];
    int already_added_in_queue[number_of_process];
    for(i=0;i<number_of_process;i++){
        check_done[i]=0;
        already_added_in_queue[i]=0;
    }
    string queue_line[500];
    int queue_time[500];
    int gantt_chart_start[500],gantt_chart_finish[500];
    int time=0,index=0;
    for(i=1;i;i++){
        int higher_priority=INT_MIN;
        int working_process=i;
        for(j=0;j<number_of_process;j++){
            if(priority[j]>higher_priority && check_done[j]==0 && arrival_time[j]<=time){
                higher_priority=priority[j];
                working_process=j;
            }
        }
        queue_line[index]=process[working_process];
        gantt_chart_start[index]=time;
        if(already_added_in_queue[working_process]==0){
            start_time[working_process]=time;
            already_added_in_queue[working_process]=1;
        }
        int minimum_time=INT_MAX;
        for(j=0;j<number_of_process;j++){
            if(arrival_time[j]<minimum_time && arrival_time[j]>time){
                minimum_time=arrival_time[j];
            }
        }
        if(time+burst_time[working_process]>minimum_time){
            queue_time[index]=minimum_time;
            burst_time[working_process]-=(minimum_time-time);
            time=minimum_time;
        }
        else{
            queue_time[index]=time+burst_time[working_process];
            time+=burst_time[working_process];
            burst_time[working_process]=0;
            finish_time[working_process]=time;
        }
        gantt_chart_finish[index]=time;
        index++;
        if(burst_time[working_process]==0){
            check_done[working_process]=1;
            int another_minimum_time=INT_MAX;
            for(j=0;j<number_of_process;j++){
                if(arrival_time[j]<another_minimum_time && check_done[j]==0){
                    another_minimum_time=arrival_time[j];
                }
            }
            if(another_minimum_time>time){
                time=another_minimum_time;
            }
        }
        int flag=0;
        for(j=0;j<number_of_process;j++){
            if(check_done[j]==0){
                flag=1;
            }
        }
        if(flag==0){
            break;
        }
    }
    cout<<"                                             Gantt chart"<<endl;
   cout<<"|---"<<queue_line[0]<<"---|";
    for(i=1;i<index;i++){
        if(gantt_chart_start[i]>gantt_chart_finish[i-1]){
            cout<<"---idle---|";
        }
        cout<<"----"<<queue_line[i]<<"----|";
    }
    cout<<endl;
    cout<<"0        "<<gantt_chart_finish[0];
    for(i=1;i<index;i++){
        if(gantt_chart_start[i]>gantt_chart_finish[i-1]){
            cout<<"         "<<gantt_chart_start[i];
        }
            cout<<"         "<<gantt_chart_finish[i];
    }
    double average_turnaround_time=0.0;
    double average_waiting_time=0.0;
    cout<<endl;
    cout<<"Turn around time for each process: "<<endl;
    for(i=0;i<number_of_process;i++){
        cout<<process[i]<<"="<<finish_time[i]-arrival_time[i]<<endl;
        average_turnaround_time+=finish_time[i]-arrival_time[i];
    }
    cout<<"Waiting time for each process: "<<endl;
    for(i=0;i<number_of_process;i++){
        cout<<process[i]<<"="<<finish_time[i]-arrival_time[i]-new_burst_time[i]<<endl;
        average_waiting_time+=finish_time[i]-arrival_time[i]-new_burst_time[i];
    }
    cout<<"Average turnaround time: "<<average_turnaround_time/number_of_process<<endl;
    cout<<"Average waiting time: "<<average_waiting_time/number_of_process<<endl;
}
