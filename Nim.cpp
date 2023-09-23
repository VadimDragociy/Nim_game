#include <iostream>
#include <vector>
using namespace std;

void vvod(int n, vector<vector<int>>& Game){//ввод значений в игровое поле 
    int p =1;

    for (int i = 0; i < n;++i){
        if ( p<=n){
            for(int j =0;j<p;j++){
                Game[i][j]=1;
        
            }
            p++;
        }

    }
}

void vivod(vector <vector<int>>& Game){//вывод игрового поля
    for(int i =0;i<Game.size();i++){
        for(int j =0;j<Game[i].size();j++){
            cout<< Game[i][j]<<"  ";  
        }
        cout<< endl;   
    }
}

void summ(int sum, vector <int>& Sum,vector <vector<int>>& Game){//сумма чтобы пользоваться тактикой
    for (int i =0;i< Game.size(); i++){
        for (int j =0;j<Game[i].size();j++){
            sum+= Game[i][j];    
        }
        Sum[i]=sum;   
        sum=0;
    }
}

bool proverka_win(vector <int>& Sum){
    int sum=0;
    for(int i =0;i<Sum.size();++i){
        sum+=Sum[i];
    }
    if(sum>0) return false;
    
    return true;

}

void hod_robota(int sum, vector <int>& Sum,vector <vector<int>>& Game){
    int ili,p,r=0;
    for( int i =0;i< Game.size();i++){
        for( int j =1;j< Sum[i]+1;j++){
            ili=Sum[i]-j;
            for( int k =0;k< Game.size();k++){
                if(k!=i){
                    ili= ili^Sum[k];  
                }
            }
            p=j;
            r=i;
            
            if (ili==0){
                Sum[i]-=j;
                int h=Game[i].size()-1;
                while(j>0){
                    if(Game[i][h]!=0){
                        Game[i][h]=0;
                        j--;
                    }
                    h--;
                }
                break;
            }               
        }
        if (ili==0) break;
    }      
    if (ili != 0){// не нашел оптимальный ход, делаем последнее возможное
        Sum[r]-=p;
        for(int h =p-1;h>0;h--){
            Game[r][h]=0;
        }               
    }
}

void hod_ugroka(vector <int>& Sum,vector <vector<int>>& Game){
    int stroka,kolvo=0;

    cout<<"Введите строку и количество фишек, которые вы хотите убрать (Номера строк начинаются с 1)"<<endl;
    cin>> stroka>>kolvo;

    Sum[stroka-1]-=kolvo;

    int h=Game[stroka-1].size()-1;
    while(kolvo>0){
        if(Game[stroka-1][h]!=0){
        Game[stroka-1][h]=0;
        kolvo--;              
        }
    h--;
    }
}

int main(){
    int n=0;//размеры игры
    int sum=0; //сумма строки
    int swich=0; // выбор сложности
    bool win=false; // ура победа

    cout<<" Выберите размер "<< endl;
    cout<<" Введите высоту и ширину (одно число) "<< endl;
    cin >> n;

    
    vector <vector <int>> Vec(n, vector <int> (n));
    vector <int> Sum(n,0);

    cout<<" Выберите сложность "<< endl;
    cout<<" (Сложность зависит от того, кто ходит первым: Вы или робот) "<< endl;
    cout<<" Введите цифру 1, чтобы ходить первым или введите цифру 2, чтобы ходить вторым "<< endl;

    cin>>swich;

    vvod(n,Vec); // Создали массив
    vivod(Vec); // вывели его
    summ(sum,Sum,Vec); // изначальная сумма, которая потом меняется

    if (swich==1){
        while (win==0)
        {
            hod_ugroka(Sum,Vec);
            cout<<endl;
            win=proverka_win(Sum);
            if (win==1){
                cout<< "Джон Коннор, вы победили машин, восставших из пепла ядерного огня"<<endl;
                break;
            }
            cout<<endl;
            hod_robota(sum,Sum,Vec);
            vivod(Vec);
            win=proverka_win(Sum);
            if (win==1){
                cout<< "Вы проиграли машине, как грустно"<<endl;
                break;
            }
        }
    }
    else if (swich==2){//робот первый
        while (win==0){  
            cout<<endl;
            hod_robota(sum,Sum,Vec);
            vivod(Vec);
            win=proverka_win(Sum);
            if (win==1){
                cout<< "Вы проиграли машине, как грустно"<<endl;
                break;
            }
            hod_ugroka(Sum,Vec);
            win=proverka_win(Sum);
            if (win==1){
                cout<< "Джон Коннор, вы победили машин, восставших из пепла ядерного огня"<<endl;
                break;
            }
        }
    }
}
