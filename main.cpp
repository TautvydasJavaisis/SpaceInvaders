#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77

const int x = 76;
const int y = 28;

class Notifications{
  public:
    void PrintIntro(){
      cout << " Intro for the best game" << endl; 
      cout << " Space Invaders OG 100% " << endl;
      cout << "a i kaire " << endl;
      cout << "d i desine " << endl;
      cout << "w  sauti" << endl;
      cout << " = blokada kuri turi dvi gyvybes, kai turi viena pavirs i _ " << endl;
      cout << " Yra dvieju rusiu priesai vieni su dvejom gyvybem kiti su viena " << endl;
      system("pause");
    }
    void PrintEnd(int score){
      cout << " Pralaimejot xd" << endl;
      cout << " Score : " << score << endl;
      system("pause");
    }
};
class Character {
  protected:
    char character, projectile; 
  public:
    Character(char character, char projectile): character(character), projectile(projectile){}
    Character(){}
    char GetCharacter(){
      return character;
    }
    char GetProjectile(){
      return projectile;
    } 
};
class Player : public Character {
  public:
    Player(char character, char projectile) : Character(character, projectile) {}
};
class SmallerEnemy : public Character {
  public:
    SmallerEnemy(char character, char projectile) : Character(character, projectile) {}
};
class BiggerEnemy : public Character {
  public:
    BiggerEnemy(char character, char projectile) : Character(character, projectile) {}
};
class Points{
  private: 
    int score, lifes;
  public:
    Points(double score, double lifes): score(score), lifes(lifes) {}
    int GetScore(){
      return score;
    }
    int GetLifes(){
      return lifes;
    }
    void RemoveLife(){
      lifes--;
    }
    void AddScore(){
      score++;
    }
};
class Board{
  private:
    char board[y][x] = {' '};
    Points *points;
    Player *player;
    SmallerEnemy *sEnemy;
    BiggerEnemy *bEnemy;
    int xPlayer;
    bool enemyDirection; // true i desine, false i kaire
  public:
    Board(){}
    void ConstructWalls(){
      for(int i = 0; i < y; i++){
        board[i][0] = '|';
        board[i][x-1] = '|';
      }
      for(int i = 0; i < x; i++){
        board[0][i] = '-';
        board[y-1][i] = '-';
      }
    }
    void CreatePlayer(){
      this->points = new Points(0,3);
      this->player = new Player('W', 'I');
      xPlayer = x/2;
      board[y-3][xPlayer] = player->GetCharacter();
    }
    void CreateEnemies(){
      this->sEnemy = new SmallerEnemy('o', '*');
      this->bEnemy = new BiggerEnemy('X', '*');
      int blankSpace= 1;
      int enemyType= 1;
      for(int i = 2; i < y-10; i+=2){
        for(int j = 2; j < 40; j+=3){
          if(blankSpace == 1){
            if(enemyType == 1){
              board[i][j] = sEnemy->GetCharacter();
              enemyType = 0;
            }
            else{
              board[i][j] = bEnemy->GetCharacter();
              enemyType++;
            }
            blankSpace = 0;
          }
          else
            blankSpace++;
        }
      }
    }
    void CreateObstacles(){
      int blankSpace;
      for(int i = y-7; i < y-4; i++){
        blankSpace= 5;
        for(int j = 2; j < x-3; j++){
          if(blankSpace == 5){
              board[i][j] = '=';
              blankSpace = 0;
          }
          else{
              blankSpace++;
          }
        }
      }
    }
    void Input(){
      if (_kbhit()){
        char in = _getch();
        switch (in){
          case 'w':{
            board[y-4][xPlayer] = player->GetProjectile();
            break;
          }
          case 'a':{
            board[y-3][xPlayer] = ' ';
            if(xPlayer-2>0)
              xPlayer--;
            board[y-3][xPlayer] = player->GetCharacter();
            break;
          }
          case 'd':{
            board[y-3][xPlayer] = ' ';
            if(xPlayer+2<x-1)
              xPlayer++;
            board[y-3][xPlayer] = player->GetCharacter();
            break;
          }
        }
      }
    }
    void MoveEnemies(){
      if(enemyDirection){
        for(int i = 2; i < y-10; i+=2){
          if(board[i][x-2] == sEnemy->GetCharacter() || board[i][x-2] == bEnemy->GetCharacter()) // suranda krypti
            enemyDirection = false;
        }
      }
      else{
        for(int i = 2; i < y-10; i+=2){
          if(board[i][1] == sEnemy->GetCharacter() || board[i][1] == bEnemy->GetCharacter())
            enemyDirection = true;
        }
      }

      if(enemyDirection){
        for(int i = 2; i < y-10; i+=2){
          for(int j = x-1; j > 0; j--){
              if(board[i][j] == sEnemy->GetCharacter()){
                board[i][j+1] = sEnemy->GetCharacter();
                board[i][j] = ' ';
              }
              if(board[i][j] == bEnemy->GetCharacter()){
                board[i][j+1] = bEnemy->GetCharacter();
                board[i][j] = ' ';
              }
            }           
          }
        } 
      else{
        for(int i = 2; i < y-10; i+=2){
          for(int j = 1; j < x-1; j++){
            if(board[i][j] == sEnemy->GetCharacter()){
              board[i][j-1] = sEnemy->GetCharacter();
              board[i][j] = ' ';
            }
            if(board[i][j] == bEnemy->GetCharacter()){
              board[i][j-1] = bEnemy->GetCharacter();
              board[i][j] = ' ';
            }
          }           
        }
      } 
    }
    void EnemiesShot(){
      int posibleProjectiles1 = 0;
      int posibleProjectiles2 = 0;
      int lastEnemyY;
      for(int j = 1; j < x-1; j++){
        for(int i = 2; i < y-10; i+=2){
          if(board[i][j] == sEnemy->GetCharacter()){
            posibleProjectiles1++;
            lastEnemyY = i;
          }
          if(board[i][j] == bEnemy->GetCharacter()){
            posibleProjectiles2++;
            lastEnemyY = i;
          }
        }
        bool a = rand() % 6;
        bool b = rand() % 2;
        if(!(a)){
          if(posibleProjectiles1 > 0 && posibleProjectiles2 > 0){
            if(b)
              board[lastEnemyY+1][j] = sEnemy->GetProjectile();
            else
              board[lastEnemyY+1][j] = bEnemy->GetProjectile();
          }
          else if(posibleProjectiles1 > 0){
            board[lastEnemyY+1][j] = sEnemy->GetProjectile();
          }
          else if(posibleProjectiles2 > 0){
            board[lastEnemyY+1][j] = bEnemy->GetProjectile();
          }
        }
        posibleProjectiles1 = 0;
        posibleProjectiles2 = 0;          
      }
    }
    void ShotVelocity(){
      for(int j = 1; j < x-1; j++){
        for(int i = y-1; i > 1; i--){
          if(board[i][j] == sEnemy->GetProjectile()){ // silpnesnis suvis
            board[i][j] = ' ';
            if(board[i+1][j] == player->GetCharacter()) // jei pataiko zaideja
              points->RemoveLife();
            else if(board[i+1][j] == '_') // jei pataiko sienas
              board[i+1][j] = ' ';
            else if(board[i+1][j] == '=')
              board[i+1][j] = '_';
            else if(!(board[i+1][j] == player->GetProjectile() || board[i+1][j] == sEnemy->GetCharacter() || board[i+1][j] ==bEnemy->GetCharacter()|| board[i+1][j] == '-'))
              board[i+1][j] = sEnemy->GetProjectile();
          }
          if(board[i][j] == bEnemy->GetProjectile()){ // stipresnis suvis
            board[i][j] = ' ';
            if(board[i+1][j] == player->GetCharacter()){
              points->RemoveLife();
              points->RemoveLife();
            }
            else if(board[i+1][j] == '_')
              board[i+1][j] = ' ';
            else if(board[i+1][j] == '=')
              board[i+1][j] = '_';
            else if(!(board[i+1][j] == player->GetProjectile() || board[i+1][j] == sEnemy->GetCharacter() || board[i+1][j] ==bEnemy->GetCharacter()|| board[i+1][j] == '-'))
              board[i+1][j] = bEnemy->GetProjectile();
          }
        }
      }
    };
    void PlayerShotVelocity(){
      for(int j = 1; j < x-1; j++){
        for(int i = 1; i < y-1; i++){
          if(board[i][j] == player->GetProjectile()){ // zaidejo suvis
            board[i][j] = ' ';
            if(board[i-1][j] == sEnemy->GetCharacter()){ // jei pataiko i priesa
              board[i-1][j] = ' ';
              points->AddScore();
            }
            else if(board[i-1][j] == bEnemy->GetCharacter()){
              board[i-1][j] = sEnemy->GetCharacter();
              points->AddScore();
            }
            else if( board[i-1][j] == sEnemy->GetProjectile() || board[i-1][j] == bEnemy->GetProjectile()){
              board[i-1][j] = ' ';
            }
            else if(!(board[i-1][j] == '-' || board[i-1][j] == '='|| board[i-1][j] == '_'))
              board[i-1][j] = player->GetProjectile();
          }
        }
      }
    };
    void PrintBoard(){
      for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
          if(j != x-1)
            cout << board[i][j];
          else
            cout << board[i][j] << endl;
        }
      }
      cout << "Lifes left : " << points->GetLifes() << endl;
      cout << "Score : " << points->GetScore();
    }
    int GetHealth(){
      return points->GetLifes();
    }
    int GetScore(){
      return points->GetScore();
    }
};
class Game{
  private:
    Board *a;
  public:
    void CreateGame(){
      this->a = new Board();
      a->ConstructWalls();
      a->CreatePlayer();
      a->CreateEnemies();
      a->CreateObstacles();
    }
    void RunGame(){
      Notifications notification;
      notification.PrintIntro();
      while(a->GetHealth()>0){
        a->PrintBoard();
        if (_kbhit())
          a->Input();
        a->ShotVelocity();
        a->PlayerShotVelocity();
        a->EnemiesShot();
        a->MoveEnemies();
        Sleep(130);
        system("cls");
      }
      notification.PrintEnd(a->GetScore());
    }
};
int main()
{
  Game newgame;
  newgame.CreateGame();
  newgame.RunGame();

 return 0;
}
