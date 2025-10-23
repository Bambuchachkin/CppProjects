#include <iostream>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <string>
// #include <bits/stdc++.h>
#include <cmath>
#include <random>
using std::cout;
using std::cin;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

struct Player{
    int x_position;
    int y_position;
    int angle;
    int width;
    int** body;
    int owner=0;
};

struct Bullet{
    int x_position;
    int y_position;
    int Vector;
    int owner=0;
};

int** Field_Init(int Len){
    int** Field_Matrix = new int* [Len];
    for (int i=0; i<Len; i++){
        Field_Matrix[i] = new int [Len];
    }
    for (int i=0; i<Len; i++){
        for (int j=0; j<Len; j++){
            Field_Matrix[i][j]=0;
            if ((i==0) or (i==Len-1) or (j==0) or (j==Len-1)){
                Field_Matrix[i][j]=1;
            }
        }
    }
    return(Field_Matrix);
}

bool Tank_Print(Player* User, int Field_Len, int** Field_Matrix){
    int** Body_Matrix = User->body;
    for (int i=0; i<Field_Len; i++){
        for (int j=0; j<Field_Len; j++){
            Body_Matrix[i][j]=0;
        }
    }
    if ((User->angle==-1) and (User->x_position>=0)){
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position] = 1;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position][User->x_position] = 1;
        Body_Matrix[User->y_position][User->x_position+((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position] = 0;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 1;
    }
    if ((User->angle==1) and (User->x_position>=0)){
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position] = 0;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position][User->x_position] = 1;
        Body_Matrix[User->y_position][User->x_position+((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 0;
    }
    if ((User->angle==2) and (User->x_position>=0)){
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position] = 1;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position][User->x_position-((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position][User->x_position] = 1;
        Body_Matrix[User->y_position][User->x_position+((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 0;
    }
    if ((User->angle==-2) and (User->x_position>=0)){
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position] = 1;
        Body_Matrix[User->y_position-((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position][User->x_position-((User->width-1)/2)] = 1;
        Body_Matrix[User->y_position][User->x_position] = 1;
        Body_Matrix[User->y_position][User->x_position+((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position-((User->width-1)/2)] = 0;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position] = 1;
        Body_Matrix[User->y_position+((User->width-1)/2)][User->x_position+((User->width-1)/2)] = 1;
    }
    for (int i =0; i<Field_Len; i++){
        Field_Matrix[0][i]=1;
        Field_Matrix[Field_Len-1][i]=1;
        Field_Matrix[i][0]=1;
        Field_Matrix[i][Field_Len-1]=1;
    }
    for (int i=0; i<Field_Len; i++){
        for (int j=0; j<Field_Len; j++){
            Field_Matrix[i][j] += User->body[i][j];
        }
    }
    return(true);
}

int** Body_Init(int Field_Len, Player* User){
    int** Body_Matrix = new int* [Field_Len];
    for (int i=0; i<Field_Len; i++){
        Body_Matrix[i] = new int [Field_Len];
    }
    for (int i=0; i<Field_Len; i++){
        for (int j=0; j<Field_Len; j++){
            Body_Matrix[i][j]=0;
        }
    }
    int x_center = (Field_Len-1)/2;
    int y_center = (Field_Len-1)/2;
    User->x_position = x_center;
    User->y_position = y_center;
    User->angle=1;
    User->width=3;
    return(Body_Matrix);
}

bool Place_Check(int** Field_Matrix, int S_x, int S_y){
    int Sum=0;
    for (int i=S_x-1; i<=S_x+1; i++){
        for (int j=S_y-1; j<=S_y+1; j++){
            Sum++;
            if (Field_Matrix[j][i] == 1){
                Sum++;
            }
        }
    }
    if ((Sum==13) or (Sum==14) or (Sum==0)){
        return(true);
    } else{
        return(false);
    }
}

bool Body_Update(int Vector, Player* User, int** Field_Matrix, int Field_Len){
    if (Vector==0){
    Place_Check(Field_Matrix, User->x_position, User->y_position+Vector);
        for (int i=User->x_position-1; i<=User->x_position+1; i++){
            for (int j=User->y_position-1; j<=User->y_position+1; j++){
                Field_Matrix[j][i] =0;
            }
        }
        User->y_position+=Vector;
        Tank_Print(User, Field_Len, Field_Matrix);
    return(true);
    }
    User->angle = Vector;
    if ((Vector==1) or (Vector==-1)){
        if (Place_Check(Field_Matrix, User->x_position, User->y_position+Vector)){
            for (int i=User->x_position-1; i<=User->x_position+1; i++){
                for (int j=User->y_position-1; j<=User->y_position+1; j++){
                    Field_Matrix[j][i] =0;
                }
            }
            User->y_position+=Vector;
            Tank_Print(User, Field_Len, Field_Matrix);
        }
        return(true);
    }
    if ((Vector==2) or (Vector==-2)){
        if (Vector==2){
            Vector=1;
        } else{
            Vector=-1;
        }
        if (Place_Check(Field_Matrix, User->x_position+Vector, User->y_position)){
            for (int i=User->x_position-1; i<=User->x_position+1; i++){
                for (int j=User->y_position-1; j<=User->y_position+1; j++){
                    Field_Matrix[j][i] =0;
                }
            }
            User->x_position+=Vector;
            Tank_Print(User, Field_Len, Field_Matrix);
        }
        return(true);
    }
    return(true);
}

void Cout(int** Field_Matrix, int Field_Len, int score, std::string record){
    int Sum=0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, 0});
    cout<<"Press 'Backspace' to finish the game."<<endl;
    cout<<"Record: "<<record<<endl;
    cout<<"Score: "<<score<<endl;
    for (int i=0; i<Field_Len; i++){
        for (int j=0; j<Field_Len; j++){
            if (Field_Matrix[i][j]==1){
                cout<<'O'<<' ';
            }
            if (Field_Matrix[i][j]==0){
                cout<<' '<<' ';
            }
            if (Field_Matrix[i][j]==2){
                cout<<'.'<<' ';
            }
            if (Field_Matrix[i][j]>2){
                cout<<Field_Matrix[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

bool Bullet_Update(Bullet** Bullets, int** Field_Matrix, int Field_Len){
    for (int i=0; i<10; i++){
        if (Bullets[i]->Vector!=0){
        if (Field_Matrix[Bullets[i]->y_position][Bullets[i]->x_position]>=2){
            Field_Matrix[Bullets[i]->y_position][Bullets[i]->x_position]--;
            Bullets[i]->Vector=0;
            Bullets[i]->x_position=Bullets[i]->y_position=-1;
        } else{
            Field_Matrix[Bullets[i]->y_position][Bullets[i]->x_position]--;
            if ((Bullets[i]->Vector==1) or (Bullets[i]->Vector==-1)){
                Bullets[i]->y_position+=Bullets[i]->Vector;
            } else {
                int vector=0;
                if (Bullets[i]->Vector==2){
                    vector = 1;
                } else{
                    vector = -1; 
                }
                Bullets[i]->x_position+=vector;
            }
            if((Bullets[i]->x_position<(Field_Len-1)) and (Bullets[i]->y_position<(Field_Len-1)) and (Bullets[i]->x_position>=0) and (Bullets[i]->y_position>=0)){
                // cout<<Bullets[i]->y_position<<" "<<Bullets[i]->x_position<<endl;
                Field_Matrix[Bullets[i]->y_position][Bullets[i]->x_position]++;
            } else{
                Bullets[i]->Vector=0;
                Bullets[i]->x_position=Bullets[i]->y_position=-1;
            }
        }
    }
    }
    return(true);
}

bool Bot_Init(Player** Bots, int Field_Len, int Number){
    for (int i=0; i<Number; i++){
        if (i==0){
            Bots[i]->y_position=3;
            Bots[i]->x_position=3;
        }
        if (i==1){
            Bots[i]->y_position=3;
            Bots[i]->x_position=Field_Len-4;
        }if (i==2){
            Bots[i]->y_position=Field_Len-4;
            Bots[i]->x_position=5;
        }
        if (i==3){
            Bots[i]->y_position=Field_Len-4;
            Bots[i]->x_position=Field_Len-6;
        }
    }
    return(true);
}

bool Shooting(Player* User, int** Field_Matrix, Bullet** Bullets){
    int index=0;
    while (Bullets[index]->Vector!=0){
        index++;
        if (index==10){
            return(false);
        }
    }
    Bullets[index]->owner = User->owner;
    Bullets[index]->Vector = User->angle;
    if ((Bullets[index]->Vector==1) or (Bullets[index]->Vector==-1)){
        Bullets[index]->y_position = User->y_position + 2*Bullets[index]->Vector;
        Bullets[index]->x_position = User->x_position;
    } else {
        int vector=0;
        if (Bullets[index]->Vector==2){
            vector = 1;
        } else{
            vector = -1;
        }
        Bullets[index]->x_position = User->x_position + 2*vector;
        Bullets[index]->y_position = User->y_position;
    }
    Field_Matrix[Bullets[index]->y_position][Bullets[index]->x_position]++;
    return(true);
}

bool Bot_Update(Player** Bots, int** Field_Matrix, int Field_Len, Bullet** Bullets){
    rand();
    int Vector = 0;
    int R=0;
    int k = 2;
    for (int i=0; i<4; i++){
        if ((Bots[i]->x_position)>-1){
            R = rand();
            if (R<31000){
                Vector = 0;
            } else{
                if (R%(5*k) == 0){
                    Shooting(Bots[i], Field_Matrix, Bullets);
                }
                if(R%(2*k)==0){
                    Vector = 1;
                }
                if(R%(3*k)==0){
                    Vector = 2;
                }
                if(R%(4*k)==0){
                    Vector = -1;
                }
                if(R%(6*k)==0){
                    Vector = -2;
                }
            }
            Body_Update(Vector, Bots[i], Field_Matrix, Field_Len);
        }
    }
    return(true);
}

int Get_Symbol(){
    char Symbol = getch();
    for (int i=0; i<10; i++){
        cout<<'\b';
    }
    if (Symbol=='w'){
        return(-1);
    }
    if (Symbol=='s'){
        return(1);
    }
    if (Symbol=='d'){
        return(2);
    }
    if (Symbol=='a'){
        return(-2);
    }
    if (Symbol==' '){
        return(10);
    }
    if (Symbol=='\b'){
        return(-100);
    }
    return(0);
}

int Distance(Player* User1, Player* User2){
    int x1,x2,y1,y2;
    y1 = User1->y_position;
    x1 = User1->x_position;
    y2 = User2->y_position;
    x2 = User2->x_position;
    int X,Y;
    X=x1-x2;
    if (X<0){
        X=-X;
    }
    Y=y1-y2;
    if (Y<0){
        Y=-Y;
    }
    if (Y>=3 or X>=3){
        return(1);
    } else {
        return(0);
    }

}

int Distance_B(Player* User1, Bullet* User2){
    int x1,x2,y1,y2;
    y1 = User1->y_position;
    x1 = User1->x_position;
    y2 = User2->y_position;
    x2 = User2->x_position;
    int X,Y;
    X=x1-x2;
    if (X<0){
        X=-X;
    }
    Y=y1-y2;
    if (Y<0){
        Y=-Y;
    }
    if (Y>=2 or X>=2){
        return(1);
    } else {
        return(0);
    }

}
int Kill(Player* User, Player** Bots, int** Field_Matrix, Bullet** Bullets){
    int N = 4;
    for (int i=0; i<N; i++){
        if (Distance(User, Bots[i])==0){
            return(-1);
        }
    }
    N = 10;
    for (int i=0; i<N; i++){
        if (Distance_B(User, Bullets[i])==0){
            return(-1);
        }
    }
    for (int i=0; i<N; i++){
        if (Bullets[i]->owner==1){
        for (int j=0; j<4; j++){
            if(Bots[j]->x_position>=0){
                if (Distance_B(Bots[j], Bullets[i])==0){
                    return(j);
                }
            }
        }
    }
    }
    return(-100);
}

void Animation(int** Field_Matrix, int Field_Len, int score, std::string record){
    for (int i = 0; i<Field_Len; i++){
        for (int j = 0; j<Field_Len; j++){
            Field_Matrix[i][j] = 1;
        }
        Cout(Field_Matrix, Field_Len, score, record);
    }

}

void Debugging(Player** Bots, Bullet** Bullets, Player* User){
    cout<<"User"<<" [ x= "<<User->y_position<<", y = "<<User->x_position<<" ]"<<endl;
    for (int i=0; i<4; i++){
        cout<<"Bot "<<i<<" [ x= "<<Bots[i]->y_position<<", y = "<<Bots[i]->x_position<<" ]"<<endl;
    }
    for (int i=0; i<10; i++){
        cout<<"Bullet "<<i<<" [ x= "<<Bullets[i]->y_position<<", y = "<<Bullets[i]->x_position<<", vector = "<<Bullets[i]->Vector<<" ]"<<endl;
    }
}
int P_Distance(int x1, int y1, int x2, int y2){
    return(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}
void Real_Debugging(Player** Bots, Bullet** Bullets, Player* User, int** Field_Matrix, int Field_Len){
    int flag=0;
    for (int i=0; i<Field_Len; i++){
        for (int j=0; j<Field_Len; j++){
            flag=0;
            if (P_Distance(j , i, User->x_position, User->y_position)<2){
                flag=1;
                break;
            }
            for (int k=0; k<4; k++){
                if (P_Distance(j , i, Bots[k]->x_position, Bots[k]->y_position)<2){
                    flag=1;
                    break;
                }
            }
            for (int k=0; k<10; k++){
                if (P_Distance(j , i, Bullets[k]->x_position, Bullets[k]->y_position)==0){
                    flag=1;
                    break;
                }
            }
            if (flag==0){
                Field_Matrix[i][j]=0;
            }
        }
    }
    for (int i =0; i<Field_Len; i++){
        Field_Matrix[0][i]=1;
        Field_Matrix[Field_Len-1][i]=1;
        Field_Matrix[i][0]=1;
        Field_Matrix[i][Field_Len-1]=1;
    }
}

int main(){
    std::cout << "\x1B[2J\x1B[H";
    Player User;
    User.owner=1;
    int score = 0;
    int record=0;
    Player* User_Adress=&User;
    int Field_Len = 0;

    std::string RRecord;
    std::string Record;
    std::ifstream in("Record.txt");
    if (in.is_open())
    {
        while (std::getline(in, RRecord))
        {
            Record = RRecord;
        }
    }
    in.close();

    while ((Field_Len < 11) or (Field_Len > 20)){
        cout<<"Enter Field Len (from 11 to 20): ";
        cin>>Field_Len;
    }
    fputs("\e[?25l", stdout); /* hide the cursor */
    cout << "\x1B[2J\x1B[H";
    Field_Len+=2;
    int** Field_Adress = Field_Init(Field_Len);
    int** Body_Adress = Body_Init(Field_Len, &User);
    User.body=Body_Adress;
    Tank_Print(User_Adress, Field_Len, Field_Adress);
    Cout(Field_Adress, Field_Len, score, Record);

    Bullet** Bullets = new Bullet*[10];
    for (int i=0; i<10; i++){
        Bullets[i] = new Bullet;
        Bullets[i]->x_position=-1;
        Bullets[i]->y_position=-1;
        Bullets[i]->Vector=0;
    }

    Player** Bots = new Player*[8];
    for (int i=0; i<4; i++){
        Bots[i] = new Player;
        Bots[i]->body=Body_Init(Field_Len, Bots[i]);
        Bots[i]->x_position=-1;
        Bots[i]->y_position=-1;
    }

    int Number=4;
    Bot_Init(Bots, Field_Len, Number);
    int B_Number=4;

    while(true){
        sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() + microseconds(1000));
        int Symbol = 0;
        if (_kbhit()){
            Symbol = Get_Symbol();
        }
        if ((Symbol<3) and (Symbol!=0)){
            Body_Update(Symbol, &User, Field_Adress, Field_Len);
        }
        if (Symbol==-100){
            break;
        }
        if (Symbol == 10){
            Shooting(&User, Field_Adress, Bullets);
        }
        Bullet_Update(Bullets, Field_Adress, Field_Len);
        Bot_Update(Bots, Field_Adress, Field_Len, Bullets);
        Cout(Field_Adress, Field_Len, score, Record);
        int Kill_Code = Kill(&User, Bots, Field_Adress, Bullets);
        if (Kill_Code == -1){
            break;
        }
        if (Kill_Code >-1){
            score++;
            if (Kill_Code==0){
                score-=0.5;
            }
            // cout<<Bots[Kill_Code]->x_position<<" "<<Bots[Kill_Code]->y_position<<endl;
            Place_Check(Field_Adress, Bots[Kill_Code]->x_position, Bots[Kill_Code]->y_position+0);
            for (int i=Bots[Kill_Code]->x_position-1; i<=Bots[Kill_Code]->x_position+1; i++){
                for (int j=Bots[Kill_Code]->y_position-1; j<=Bots[Kill_Code]->y_position+1; j++){
                    if ((j>=0) and (i>=0)){
                        Field_Adress[j][i] =0;
                    }
                }
            }
            Bots[Kill_Code]->x_position=-2;
            Bots[Kill_Code]->y_position=-2;
            Tank_Print(Bots[Kill_Code], Field_Len, Field_Adress);
        }
        Real_Debugging(Bots, Bullets, &User, Field_Adress, Field_Len);
        // Debugging(Bots, Bullets, &User);
        if (score>record){
            record=score;
        }
        B_Number=0;
        for(int i=0; i<4; i++){
            if (Bots[i]->x_position>-1){
                B_Number++;
            }
        }
        if (B_Number==0){
            Bot_Init(Bots, Field_Len, Number);
            for(int i=0; i<4; i++){
                if (P_Distance(User.x_position, User.y_position, Bots[i]->x_position, Bots[i]->y_position)<=2){
                    Bots[i]->x_position = -2;
                    Bots[i]->y_position = -2;
                }
            }
        }
    }
    Animation(Field_Adress, Field_Len, score, Record);

    for (int i=0; i<Field_Len; i++){
        delete[] Field_Adress[i];
    }
    delete[] Field_Adress;
    for (int i=0; i<Field_Len; i++){
        delete[] Body_Adress[i];
    }
    delete[] Body_Adress;
    for (int i=0; i<10; i++){
        delete[] Bullets[i];
    }
    delete[] Bullets;
    for (int i=0; i<4; i++){
        delete[] Bots[i];
    }
    delete[] Bots;
    cout<<"Your score: "<<score<<endl;
    cout<<"GG"<<endl;
    std::ofstream f("Record.txt", std::ios::out);
    std::fstream("Record.txt", std::fstream::out);
    f<<record<<std::endl;

    return (0);
}