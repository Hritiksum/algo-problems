/*two person meeting schedule and their working hours are given in string formate. To find the time periods more than or equal to 30 min,
in between they both can have meeting together.*/

//    first person schedule= {{"09:00","10:30"},{"12:00","13:00"},{"16:00","17:00"}}
//    first person office working hour= {"09:00","20:00"}
//    second person schedule= {{"10:00","11:30"},{"12:30","14:30"},{"14:30","15:00"},{"16:00","17:00"}}
//    second person office working hour= {"10:00","18:30"}
//    minimum meeting time required=30
//output 11:30-12:00,15:00-16:00,17:00-18:30

#include<bits/stdc++.h>
using namespace std;

class Pair{
public:
    int hh;
    int mm;
};

class shd{
public:
    Pair Start;
    Pair End;
    shd(string s,string e){
        string j=" ";
        j+=s[0];
        j+=s[1];
        Start.hh=stoi(j);
        j=" ";
        j+=s[3];
        j+=s[4];
        Start.mm=stoi(j);

        string k=" ";
        k+=e[0];
        k+=e[1];
        End.hh=stoi(k);
        k=" ";
        k+=e[3];
        k+=e[4];
        End.mm=stoi(k);
    }
    shd(){}
};

queue <shd> vtoq(vector <shd> v,int size){
    queue<shd> q;
    for(int i=0;i<=size;i++){
        q.push(v[i]);
    }
    return q;
}

bool into(shd s1,shd s2){
    int ss1=(s1.Start.hh*100)+s1.Start.mm;
    int se1=(s1.End.hh*100)+s1.End.mm;
    int ss2=(s2.Start.hh*100)+s2.Start.mm;
    int se2=(s2.End.hh*100)+s1.End.mm;
    if(ss2>=ss1 && ss1<=se2){
        return true;
    }
    else if(ss2>=ss1 && ss1<=se2){
        return true;
    }
    else{
        return false;
    }
}

shd mg(shd s1,shd s2,vector<shd> &m,int l){
    shd ma;//={"00000","00000"};
    ma.Start.hh=min(s1.Start.hh,s2.Start.hh);
    ma.Start.mm=min(s1.Start.mm,s2.Start.mm);
    ma.End.hh=max(s1.End.hh,s2.End.hh);
    ma.End.mm=max(s1.End.mm,s2.End.mm);
    if(l){
        m[l]=ma;
    }
    else{
        m.push_back(ma);
    }
}

shd mrg(queue <shd> &s1,queue <shd> &s2,vector <shd> &m){
//    vector <shd> m;
    while(!s1.empty() && !s2.empty()){
        shd is1=s1.front();
        shd is2=s2.front();
        if(into(is1,is2)){
            mg(is1,is2,m,0);//m.push_back(mg(is1,is2,m));
            s1.pop();
            s2.pop();
        }
        else {
            if(is1.Start.hh<is2.Start.hh){
                m.push_back(is1);
                s1.pop();
            }
            else{
                m.push_back(is2);
                s2.pop();
            }
        }
    }
    while(!s1.empty()){

        int l=m.size();
        shd a=m[l-1];
        if(into(a,s1.front())){
            mg(a,s1.front(),m,l-1);
            s1.pop();
        }
        else{
            m.push_back(s1.front());
            s1.pop();
        }

    }
    while(!s2.empty()){
        int l=m.size();
        shd a=m[l-1];
        if(into(a,s2.front())){
            mg(a,s2.front(),m,l-1);
            s2.pop();
        }else{
            m.push_back(s2.front());
            s2.pop();
        }


    }
}

void printv(vector <shd> v,int s){
    for(int i=0;i<=s;i++){
        cout<<v[i].Start.hh<<":"<<v[i].Start.mm<<" "<<v[i].End.hh<<":"<<v[i].End.mm<<endl;
    }
}

void print(queue <shd> q){
    while(!q.empty()){
        shd a=q.front();
        cout<<a.Start.hh<<":"<<a.Start.mm<<" "<<a.End.hh<<":"<<a.End.mm<<endl;
        q.pop();
    }
}

void mtime(vector<shd> v, shd p1,shd p2){
    shd f;
    if(((p1.Start.hh*100)+p1.Start.mm)>((p2.Start.hh*100)+p2.Start.mm)){
        f.Start=p1.Start;
    }
    else{
        f.Start=p2.Start;
    }
    if(((p1.End.hh*100)+p1.End.mm)<((p2.End.hh*100)+p2.End.mm)){
        f.End=p1.End;
    }
    else{
        f.End=p2.End;
    }
    //cout<<f.Start.hh<<":"<<f.Start.mm<<"-"<<f.End.hh<<":"<<f.End.mm;
    int s=v.size();
    //cout<<s


    if(v[0].Start.hh>f.Start.hh){
        cout<<f.Start.hh<<":"<<f.Start.mm<<"-"<<v[0].Start.hh<<":"<<v[0].Start.mm<<endl;
    }else if(v[0].Start.hh==f.Start.hh && abs((v[0].Start.mm)-f.Start.mm)>=30){
        cout<<f.Start.hh<<":"<<f.Start.mm<<"-"<<v[0].Start.hh<<":"<<v[0].Start.mm<<endl;
    }

    for(int i=0;i<=s-1;i++){
        if(v[i+1].Start.hh>v[i].End.hh){
        cout<<v[i].End.hh<<":"<<v[i].End.mm<<"-"<<v[i+1].Start.hh<<":"<<v[i+1].Start.mm<<endl;
        }
        else if(v[i+1].Start.hh==v[i].End.hh && abs((v[i+1].Start.mm)-v[i].End.mm)>=30){
            cout<<v[i].End.hh<<":"<<v[i].End.mm<<"-"<<v[i+1].Start.hh<<":"<<v[i+1].Start.mm<<endl;
        }
    }

    if(v[s-1].End.hh<f.End.hh){
        cout<<v[s-1].End.hh<<":"<<v[s-1].End.mm<<"-"<<f.End.hh<<":"<<f.End.mm<<endl;
    }
    else if(v[s-1].End.hh<f.End.hh && abs(v[s-1].End.mm-f.End.mm)>=30){
        cout<<v[s-1].End.hh<<":"<<v[s-1].End.mm<<"-"<<f.End.hh<<":"<<f.End.mm<<endl;
    }
}


int main(){
//    first person schedule= {{"09:00","10:30"},{"12:00","13:00"},{"16:00","17:00"}}
//    first person time period= {"09:00","20:00"}
//    second person schedule= {{"10:00","11:30"},{"12:30","14:30"},{"14:30","15:00"},{"16:00","17:00"}}
//    second person time period= {"10:00","18:30"}
//    minimum meeting time required=30
    vector <shd> s1={{"09:00","10:30"},{"12:00","13:00"},{"16:00","17:00"}};
    vector <shd> s2={{"10:00","11:30"},{"12:30","14:30"},{"14:30","15:00"},{"16:00","17:00"}};
    shd s1d={"09:00","20:00"};
    shd s2d={"10:00","18:30"};
    int min=30;
    int s1s=s1.size();
    int s2s=s2.size();

    queue <shd> q1=vtoq(s1,s1s-1);
    //print(q1);
    queue <shd> q2=vtoq(s2,s2s-1);
    //print(q2);
    vector <shd> m;
    mrg(q1,q2,m);

    int s=m.size();

    cout<<"merge timetable of both person"<<endl;
    printv(m,s-1);


    cout<<"meetting time"<<endl;
    mtime(m,s1d,s2d);
    return 0;
}
