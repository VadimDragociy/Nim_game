#include <iostream>
#include <vector>
using namespace std;

void input(int n, vector<vector<int>>& Game_board){//ввод значений в игровое поле 
    int switch_string =1;

    for (int i = 0; i < n;++i){
        if ( switch_string<=n){
            for(int j =0;j<switch_string;j++){
                Game_board[i][j]=1;
        
            }
            switch_string++;
        }

    }
}

void output(const vector <vector<int>>& Game_board){//вывод игрового поля
    for(int i =0;i<Game_board.size();i++){
        for(int j =0;j<Game_board[i].size();j++){
            cout<< Game_board[i][j]<<"  ";  
        }
        cout<< endl;   
    }
}

void summarize_vector(vector <int>& Sum,const vector <vector<int>>& Game_board){//сумма чтобы пользоваться тактикой
    int stringsum=0;
    for (int i =0;i< Game_board.size(); i++){
        for (int j =0;j<Game_board[i].size();j++){
            stringsum+= Game_board[i][j];    
        }
        Sum[i]=stringsum;   
        stringsum=0;
    }
}

bool check_win(const vector <int>& Sum){
    int stringsum=0;
    for(int i =0;i<Sum.size();++i){
        stringsum+=Sum[i];
    }
    if(stringsum>0){
        return false;
    }
    
    return true;

}

void robots_move(vector <int>& Sum,vector <vector<int>>& Game_board){
    int iterable_for_xor=1;
    int save_j_iterable=0;
    int save_i_iterable=0;
    
    for( int i =0;i< Game_board.size();i++){
        for( int j =1;j< Sum[i]+1;j++){
            iterable_for_xor=Sum[i]-j;
            for( int k =0;k< Game_board.size();k++){
                if(k!=i){
                    iterable_for_xor= iterable_for_xor^Sum[k];  
                }
            }
            save_j_iterable=j;
            save_i_iterable=i;
            
            if (iterable_for_xor==0){
                
                Sum[i]-=j;
                
                int delete_from_the_end=Game_board[i].size()-1;
                while(j>0){
                    if(Game_board[i][delete_from_the_end]!=0){
                        Game_board[i][delete_from_the_end]=0;
                        j--;
                    }
                    delete_from_the_end--;
                }
                
                break;
            }               
        }
        if (iterable_for_xor==0) break;
    }      
    if (iterable_for_xor != 0){// не нашел оптимальный ход, делаем последнее возможное
        
        Sum[save_i_iterable]-=save_j_iterable;
        
        for(int h =save_j_iterable-1;h>=0;h--){
            Game_board[save_i_iterable][h]=0;
        }               
    }
}

void players_move(vector <int>& Sum,vector <vector<int>>& Game_board){
    int stroka,kolvo=0;

    cout<<"Введите строку и количество фишек, которые вы хотите убрать (Номера строк начинаются с 1)"<<endl;
    cin>> stroka>>kolvo;

    Sum[stroka-1]-=kolvo;

    int h=Game_board[stroka-1].size()-1;
    while(kolvo>0){
        if(Game_board[stroka-1][h]!=0){
        Game_board[stroka-1][h]=0;
        kolvo--;              
        }
    h--;
    }
}

int main(){
    int n=0;//размеры игры
    int hardness=0; // выбор сложности
    bool win=false; // ура победа

    cout<<" Выберите размер "<< endl;
    cout<<" Введите высоту и ширину (одно число) "<< endl;
    cin >> n;

    
    vector <vector <int>> Game_board(n, vector <int> (n));
    vector <int> Sum(n,0);
    
    cout<<" Выберите сложность "<< endl;
    cout<<" (Сложность зависит от того, кто ходит первым: Вы или робот) "<< endl;
    cout<<" Введите цифру 1, чтобы ходить первым или введите цифру 2, чтобы ходить вторым "<< endl;

    cin>>hardness;

    input(n,Game_board); // Создали массив
    output(Game_board); // вывели его
    summarize_vector(Sum,Game_board); // изначальная сумма, которая потом меняется
    
    if (hardness==1){
        while (win==0)
        {
            players_move(Sum,Game_board);
            cout<<endl;
            win=check_win(Sum);
            if (win==1){
                cout<< "Джон Коннор, вы победили машин, восставших из пепла ядерного огня"<<endl;
                break;
            }
            cout<<endl;
            robots_move(Sum,Game_board);
            output(Game_board);
            win=check_win(Sum);
            if (win==1){
                cout<< "Вы проиграли машине, как грустно"<<endl;
                break;
            }
        }
    }
    else if (hardness==2){//робот первый
        while (win==0){  
            cout<<endl;
            robots_move(Sum,Game_board);
            output(Game_board);
            win=check_win(Sum);
            if (win==1){
                cout<< "Вы проиграли машине, как грустно"<<endl;
                break;
            }
            players_move(Sum,Game_board);
            win=check_win(Sum);
            if (win==1){
                cout<< "Джон Коннор, вы победили машин, восставших из пепла ядерного огня"<<endl;
                break;
            }
        }
    }
}
