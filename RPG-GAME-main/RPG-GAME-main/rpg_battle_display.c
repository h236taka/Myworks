#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <wchar.h>
#include "rpg.h"

//encount_pattern = 2
int player_normal_attack_target2(Enemy ****enemy, Enemy *enemy_copy1){
  int command;

  if ( (***enemy) -> badstatus != DEAD && enemy_copy1 -> badstatus != DEAD ){
    printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
    printf("1.%s 2.%s\n", (***enemy) -> name, enemy_copy1 -> name);
    printf("\n");
    command =  _getch();
  }
  if ( (***enemy) -> badstatus != DEAD && enemy_copy1 -> badstatus == DEAD ){
    do {
      printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
      printf("1.%s\n", (***enemy) -> name);
      printf("\n");
      command =  _getch();
      if ( command == 'c' ){
        break;
      }
    } while ( command != '1' );
  }
  if ( (***enemy) -> badstatus == DEAD && enemy_copy1 -> badstatus != DEAD ){
    do {
      printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
      printf("2.%s\n", enemy_copy1 -> name);
      printf("\n");
      command =  _getch();
      if ( command == 'c' ){
        break;
      }
    } while ( command != '2' );
  }

  return command;
}

int player_normal_attack_target3(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2){
  int command;

  if ( (***enemy) -> badstatus != DEAD && enemy_copy1 -> badstatus != DEAD && enemy_copy2 -> badstatus != DEAD ){
    printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
    printf("1.%s 2.%s 3.%s\n", (***enemy) -> name, enemy_copy1 -> name, enemy_copy2 -> name);
    printf("\n");
    command =  _getch();
  }
  if ( (***enemy) -> badstatus != DEAD ){
    if ( enemy_copy1 -> badstatus != DEAD && enemy_copy2 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s\n", (***enemy) -> name, enemy_copy1 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' );
    }
    if ( enemy_copy1 -> badstatus == DEAD && enemy_copy2 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 3.%s\n", (***enemy) -> name, enemy_copy2 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '3' );
    }
    if ( enemy_copy1 -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s\n", (***enemy) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' );
    }
  }
  if ( enemy_copy1 -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && enemy_copy2 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 3.%s\n", enemy_copy1 -> name, enemy_copy2 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' && command != '3' );
    }
    if ( (***enemy) -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s\n", enemy_copy1 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' );
    }
  }
  if ( enemy_copy2 -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && enemy_copy1 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("3.%s\n", enemy_copy2 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '3' );
    }
  }

  return command;
}

int player_normal_attack_target4(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, Enemy *enemy_copy3){
  int command;

  if ( (***enemy) -> badstatus != DEAD && enemy_copy1 -> badstatus != DEAD && enemy_copy2 -> badstatus != DEAD && enemy_copy3 -> badstatus != DEAD ){
    printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
    printf("1.%s 2.%s 3.%s 4.%s\n", (***enemy) -> name, enemy_copy1 -> name, enemy_copy2 -> name, enemy_copy3 -> name);
    printf("\n");
    command =  _getch();
  }

  if ( (***enemy) -> badstatus != DEAD ){
    if ( enemy_copy1 -> badstatus != DEAD && enemy_copy2 -> badstatus == DEAD && enemy_copy3 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s 4.%s\n", (***enemy) -> name, enemy_copy1 -> name, enemy_copy3 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' && command != '4' );
    }
    if ( enemy_copy1 -> badstatus != DEAD && enemy_copy2 -> badstatus != DEAD && enemy_copy3 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s 3.%s\n", (***enemy) -> name, enemy_copy1 -> name, enemy_copy2 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' && command != '3' );
    }
    if ( enemy_copy1 -> badstatus != DEAD && enemy_copy2 -> badstatus == DEAD && enemy_copy3 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s\n", (***enemy) -> name, enemy_copy1 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' );
    }
    if ( enemy_copy1 -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD && enemy_copy3 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s\n", (***enemy) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' );
    }
    if ( enemy_copy1 -> badstatus == DEAD && enemy_copy2 -> badstatus != DEAD && enemy_copy3 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 3.%s 4.%s\n", (***enemy) -> name, enemy_copy2 -> name, enemy_copy3 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '3' && command != '4' );
    }
    if ( enemy_copy1 -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD && enemy_copy3 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 4.%s\n", (***enemy) -> name, enemy_copy3 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '4' );
    }
  }

  if ( enemy_copy1 -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && enemy_copy2 -> badstatus != DEAD && enemy_copy3 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 3.%s 4.%s\n", enemy_copy1 -> name, enemy_copy2 -> name, enemy_copy3 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' && command != '3' && command != '4' );
    }
    if ( (***enemy) -> badstatus == DEAD && enemy_copy2 -> badstatus != DEAD && enemy_copy3 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 3.%s\n", enemy_copy1 -> name, enemy_copy2 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' && command != '3' );
    }
    if ( (***enemy) -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD && enemy_copy3 -> badstatus != DEAD ){
      do{
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 4.%s\n", enemy_copy1 -> name, enemy_copy3 -> name);
        printf("\n");
        command = _getch();
        if ( command == 'c' ){
          break;
        }
      }while( command != '2' && command != '4' );
    }
    if ( (***enemy) -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD && enemy_copy3 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s\n", enemy_copy1 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' );
    }
  }
  if ( enemy_copy2 -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && enemy_copy1 -> badstatus == DEAD && enemy_copy3 -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("3.%s 4.%s\n", enemy_copy2 -> name, enemy_copy3 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '3' && command != '4' );
    }
  }
  if ( enemy_copy3 -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && enemy_copy1 -> badstatus == DEAD && enemy_copy2 -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("4.%s\n", enemy_copy3 -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '4' );
    }
  }

  return command;
}

//encount_pattern = 5
int player_normal_attack_target5(Enemy ****enemy, Enemy ****enemy1){
  int command;

  if ( (***enemy) -> badstatus != DEAD && (***enemy1) -> badstatus != DEAD ){
    printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
    printf("1.%s 2.%s\n", (***enemy) -> name, (***enemy1) -> name);
    printf("\n");
    command =  _getch();
  }
  if ( (***enemy) -> badstatus != DEAD && (***enemy1) -> badstatus == DEAD ){
    do {
      printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
      printf("1.%s\n", (***enemy) -> name);
      printf("\n");
      command =  _getch();
      if ( command == 'c' ){
        break;
      }
    } while ( command != '1' );
  }
  if ( (***enemy) -> badstatus == DEAD && (***enemy1) -> badstatus != DEAD ){
    do {
      printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
      printf("2.%s\n", (***enemy1) -> name);
      printf("\n");
      command =  _getch();
      if ( command == 'c' ){
        break;
      }
    } while ( command != '2' );
  }

  return command;
}

int player_normal_attack_target6(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2){
  int command;

  if ( (***enemy) -> badstatus != DEAD && (***enemy1) -> badstatus != DEAD && (***enemy2) -> badstatus != DEAD ){
    printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
    printf("1.%s 2.%s 3.%s\n", (***enemy) -> name, (***enemy1) -> name, (***enemy2) -> name);
    printf("\n");
    command =  _getch();
  }
  if ( (***enemy) -> badstatus != DEAD ){
    if ( (***enemy1) -> badstatus != DEAD && (***enemy2) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s\n", (***enemy) -> name, (***enemy1) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' );
    }
    if ( (***enemy1) -> badstatus == DEAD && (***enemy2) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 3.%s\n", (***enemy) -> name, (***enemy2) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '3' );
    }
    if ( (***enemy1) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s\n", (***enemy) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' );
    }
  }
  if ( (***enemy1) -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && (***enemy2) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 3.%s\n", (***enemy1) -> name, (***enemy2) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' && command != '3' );
    }
    if ( (***enemy) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s\n", (***enemy1) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' );
    }
  }
  if ( (***enemy2) -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && (***enemy1) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("3.%s\n", (***enemy2) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '3' );
    }
  }

  return command;
}

int player_normal_attack_target7(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3){
  int command;

  if ( (***enemy) -> badstatus != DEAD && (***enemy1) -> badstatus != DEAD && (***enemy2) -> badstatus != DEAD && (***enemy3) -> badstatus != DEAD ){
    printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
    printf("1.%s 2.%s 3.%s 4.%s\n", (***enemy) -> name, (***enemy1) -> name, (***enemy2) -> name, (***enemy3) -> name);
    printf("\n");
    command =  _getch();
  }

  if ( (***enemy) -> badstatus != DEAD ){
    if ( (***enemy1) -> badstatus != DEAD && (***enemy2) -> badstatus == DEAD && (***enemy3) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s 4.%s\n", (***enemy) -> name, (***enemy1) -> name, (***enemy3) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' && command != '4' );
    }
    if ( (***enemy1) -> badstatus != DEAD && (***enemy2) -> badstatus != DEAD && (***enemy3) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s 3.%s\n", (***enemy) -> name, (***enemy1) -> name, (***enemy2) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' && command != '3' );
    }
    if ( (***enemy1) -> badstatus != DEAD && (***enemy2) -> badstatus == DEAD && (***enemy3) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 2.%s\n", (***enemy) -> name, (***enemy1) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '2' );
    }
    if ( (***enemy1) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD && (***enemy3) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s\n", (***enemy) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' );
    }
    if ( (***enemy1) -> badstatus == DEAD && (***enemy2) -> badstatus != DEAD && (***enemy3) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 3.%s 4.%s\n", (***enemy) -> name, (***enemy2) -> name, (***enemy3) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '3' && command != '4' );
    }
    if ( (***enemy1) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD && (***enemy3) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("1.%s 4.%s\n", (***enemy) -> name, (***enemy3) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '1' && command != '4' );
    }
  }

  if ( (***enemy1) -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && (***enemy2) -> badstatus != DEAD && (***enemy3) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 3.%s 4.%s\n", (***enemy1) -> name, (***enemy2) -> name, (***enemy3) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' && command != '3' && command != '4' );
    }
    if ( (***enemy) -> badstatus == DEAD && (***enemy2) -> badstatus != DEAD && (***enemy3) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 3.%s\n", (***enemy1) -> name, (***enemy2) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' && command != '3' );
    }
    if ( (***enemy) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD && (***enemy3) -> badstatus != DEAD ){
      do{
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s 4.%s\n", (***enemy1) -> name, (***enemy3) -> name);
        printf("\n");
        command = _getch();
        if ( command == 'c' ){
          break;
        }
      }while( command != '2' && command != '4' );
    }
    if ( (***enemy) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD && (***enemy3) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("2.%s\n", (***enemy1) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '2' );
    }
  }
  if ( (***enemy2) -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && (***enemy1) -> badstatus == DEAD && (***enemy3) -> badstatus != DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("3.%s 4.%s\n", (***enemy2) -> name, (***enemy3) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '3' && command != '4' );
    }
  }
  if ( (***enemy3) -> badstatus != DEAD ){
    if ( (***enemy) -> badstatus == DEAD && (***enemy1) -> badstatus == DEAD && (***enemy2) -> badstatus == DEAD ){
      do {
        printf("攻撃する対象を選んでください(戻る場合はcを入力してください)\n");
        printf("4.%s\n", (***enemy3) -> name);
        printf("\n");
        command =  _getch();
        if ( command == 'c' ){
          break;
        }
      } while ( command != '4' );
    }
  }

  return command;
}

void hp_graphycal_display(Player ****st, Player ****st2, Player ****st3){

  printf(" ------------");
  printf("          ------------");
  printf("             ------------\n");

  if ( (***st) -> hp == (***st) -> maxhp ){
    printf(" |//////////|");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.9 ){
    printf(" |/////////||");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.8 ){
    printf(" |////////| |");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.7 ){
    printf(" |///////|  |");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.6 ){
    printf(" |//////|   |");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.5 ){
    printf(" |/////|    |");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.4 ){
    printf(" |////|     |");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.3 ){
    printf(" |///|      |");
  }
  else if ( (***st) -> hp >= (***st) -> maxhp * 0.2 ){
    printf(" |//|       |");
  }
  else if ( (***st) -> hp > 0 ){
    printf(" |/|        |");
  }
  else if ( (***st) -> hp == 0 ){
    printf(" ||         |");
  }

  if ( (***st2) -> hp == (***st2) -> maxhp ){
    printf("          |//////////|");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.9 ){
    printf("          |/////////||");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.8 ){
    printf("          |////////| |");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.7 ){
    printf("          |///////|  |");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.6 ){
    printf("          |//////|   |");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.5 ){
    printf("          |/////|    |");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.4 ){
    printf("          |////|     |");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.3 ){
    printf("          |///|      |");
  }
  else if ( (***st2) -> hp >= (***st2) -> maxhp * 0.2 ){
    printf("          |//|       |");
  }
  else if ( (***st2) -> hp > 0 ){
    printf("          |/|        |");
  }
  else if ( (***st2) -> hp == 0 ){
    printf("          ||         |");
  }

  if ( (***st3) -> hp == (***st3) -> maxhp ){
    printf("             |//////////|\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.9 ){
    printf("             |/////////||\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.8 ){
    printf("             |////////| |\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.7 ){
    printf("             |///////|  |\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.6 ){
    printf("             |//////|   |\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.5 ){
    printf("             |/////|    |\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.4 ){
    printf("             |////|     |\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.3 ){
    printf("             |///|      |\n");
  }
  else if ( (***st3) -> hp >= (***st3) -> maxhp * 0.2 ){
    printf("             |//|       |\n");
  }
  else if ( (***st3) -> hp > 0 ){
    printf("             |/|        |\n");
  }
  else if ( (***st3) -> hp == 0 ){
    printf("             ||         |\n");
  }

  printf(" ------------");
  printf("          ------------");
  printf("             ------------\n");
}

void mp_graphycal_display(Player ****st, Player ****st2, Player ****st3){

  printf(" ------------");
  printf("          ------------");
  printf("             ------------\n");

  if ( (***st) -> mp == (***st) -> maxmp ){
    printf(" |//////////|");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.9 ){
    printf(" |/////////||");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.8 ){
    printf(" |////////| |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.7 ){
    printf(" |///////|  |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.6 ){
    printf(" |//////|   |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.5 ){
    printf(" |/////|    |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.4 ){
    printf(" |////|     |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.3 ){
    printf(" |///|      |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.2 ){
    printf(" |//|       |");
  }
  else if ( (***st) -> mp >= (***st) -> maxmp * 0.1 ){
    printf(" |/|        |");
  }
  else{
    printf(" ||         |");
  }

  if ( (***st2) -> mp == (***st2) -> maxmp ){
    printf("          |//////////|");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.9 ){
    printf("          |/////////||");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.8 ){
    printf("          |////////| |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.7 ){
    printf("          |///////|  |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.6 ){
    printf("          |//////|   |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.5 ){
    printf("          |/////|    |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.4 ){
    printf("          |////|     |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.3 ){
    printf("          |///|      |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.2 ){
    printf("          |//|       |");
  }
  else if ( (***st2) -> mp >= (***st2) -> maxmp * 0.1 ){
    printf("          |/|        |");
  }
  else{
    printf("          ||         |");
  }

  if ( (***st3) -> mp == (***st3) -> maxmp ){
    printf("             |//////////|\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.9 ){
    printf("             |/////////||\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.8 ){
    printf("             |////////| |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.7 ){
    printf("             |///////|  |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.6 ){
    printf("             |//////|   |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.5 ){
    printf("             |/////|    |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.4 ){
    printf("             |////|     |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.3 ){
    printf("             |///|      |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.2 ){
    printf("             |//|       |\n");
  }
  else if ( (***st3) -> mp >= (***st3) -> maxmp * 0.1 ){
    printf("             |/|        |\n");
  }
  else{
    printf("             ||         |\n");
  }

  printf(" ------------");
  printf("          ------------");
  printf("             ------------\n");
}

//Playerの状態を表示
void battle_display_condition(Player ****st, int battle_display_condition_count){

  if ( battle_display_condition_count == 0 ){
    if ( (***st) -> badstatus == GOOD ){
      printf(" STATUS:GOOD");
    }
    else if ( (***st) -> badstatus == DEAD ){
      printf(" STATUS:DEAD");
    }
    else if ( (***st) -> badstatus == POISON ){
      printf(" STATUS:POISON");
    }
    else if ( (***st) -> badstatus == PALYZE ){
      printf(" STATUS:PALYZE");
    }
    else if ( (***st) -> badstatus == CHARM ){
      printf(" STATUS:CHARM");
    }
    else if ( (***st) -> badstatus == CLOSE ){
      printf(" STATUS:CLOSE");
    }
    else if ( (***st) -> badstatus == STONE ){
      printf(" STATUS:STONE");
    }
    else if ( (***st) -> badstatus == PANIC ){
      printf(" STATUS:PANIC");
    }
    else if ( (***st) -> badstatus == SLEEP ){
      printf(" STATUS:SLEEP");
    }
    else if ( (***st) -> badstatus == CURSE ){
      printf(" STATUS:CURSE");
    }
  }
  else if ( battle_display_condition_count == 1 ){
    if ( (***st) -> badstatus == GOOD ){
      printf("           STATUS:GOOD");
    }
    else if ( (***st) -> badstatus == DEAD ){
      printf("           STATUS:DEAD");
    }
    else if ( (***st) -> badstatus == POISON ){
      printf("           STATUS:POISON");
    }
    else if ( (***st) -> badstatus == PALYZE ){
      printf("           STATUS:PALYZE");
    }
    else if ( (***st) -> badstatus == CHARM ){
      printf("           STATUS:CHARM");
    }
    else if ( (***st) -> badstatus == CLOSE ){
      printf("           STATUS:CLOSE");
    }
    else if ( (***st) -> badstatus == STONE ){
      printf("           STATUS:STONE");
    }
    else if ( (***st) -> badstatus == PANIC ){
      printf("           STATUS:PANIC");
    }
    else if ( (***st) -> badstatus == SLEEP ){
      printf("           STATUS:SLEEP");
    }
    else if ( (***st) -> badstatus == CURSE ){
      printf("           STATUS:CURSE");
    }
  }
  else{
    if ( (***st) -> badstatus == GOOD ){
      printf("              STATUS:GOOD");
    }
    else if ( (***st) -> badstatus == DEAD ){
      printf("              STATUS:DEAD");
    }
    else if ( (***st) -> badstatus == POISON ){
      printf("              STATUS:POISON");
    }
    else if ( (***st) -> badstatus == PALYZE ){
      printf("              STATUS:PALYZE");
    }
    else if ( (***st) -> badstatus == CHARM ){
      printf("              STATUS:CHARM");
    }
    else if ( (***st) -> badstatus == CLOSE ){
      printf("              STATUS:CLOSE");
    }
    else if ( (***st) -> badstatus == STONE ){
      printf("              STATUS:STONE");
    }
    else if ( (***st) -> badstatus == PANIC ){
      printf("              STATUS:PANIC");
    }
    else if ( (***st) -> badstatus == SLEEP ){
      printf("              STATUS:SLEEP");
    }
    else if ( (***st) -> badstatus == CURSE ){
      printf("              STATUS:CURSE");
    }
  }
}

void encount_pattern1_layout(Enemy ****enemy, int encount_pattern){
  if ( (***enemy) -> badstatus == GOOD ){
    printf("                         %s(GOOD)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("                         %s(POISON)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("                         %s(PALYZE)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("                         %s(CHARM)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("                         %s(CLOSE)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("                         %s(STONE)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("                         %s(PANIC)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("                         %s(SLEEP)\n", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("                         %s(CURSE)\n", (***enemy) -> name);
  }
  printf("\n");
}

void encount_pattern2_layout(Enemy ****enemy, Enemy *enemy_copy1, int encount_pattern){

  if ( (***enemy) -> badstatus == GOOD ){
    printf("             %s(GOOD)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == DEAD ){
    printf("                     ");
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("             %s(POISON)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("             %s(PALYZE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("             %s(CHARM)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("             %s(CLOSE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("             %s(STONE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("             %s(PANIC)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("             %s(SLEEP)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("             %s(CURSE)", (***enemy) -> name);
  }

  if ( enemy_copy1 -> badstatus == GOOD ){
    printf("             %s(GOOD)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == DEAD ){
    printf("                     \n");
  }
  else if ( enemy_copy1 -> badstatus == POISON ){
    printf("             %s(POISON)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == PALYZE ){
    printf("             %s(PALYZE)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CHARM ){
    printf("             %s(CHARM)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CLOSE ){
    printf("             %s(CLOSE)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == STONE ){
    printf("             %s(STONE)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == PANIC ){
    printf("             %s(PANIC)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == SLEEP ){
    printf("             %s(SLEEP)\n", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CURSE ){
    printf("             %s(CURSE)\n", enemy_copy1 -> name);
  }

  printf("\n");

}

void encount_pattern3_layout(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, int encount_pattern){

  if ( (***enemy) -> badstatus == GOOD ){
    printf("  %s(GOOD)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == DEAD ){
    printf("          ");
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("  %s(POISON)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("  %s(PALYZE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("  %s(CHARM)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("  %s(CLOSE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("  %s(STONE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("  %s(PANIC)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("  %s(SLEEP)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("  %s(CURSE)", (***enemy) -> name);
  }

  if ( enemy_copy1 -> badstatus == GOOD ){
    printf("          %s(GOOD)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( enemy_copy1 -> badstatus == POISON ){
    printf("          %s(POISON)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == PALYZE ){
    printf("          %s(PALYZE)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CHARM ){
    printf("          %s(CHARM)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CLOSE ){
    printf("          %s(CLOSE)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == STONE ){
    printf("          %s(STONE)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == PANIC ){
    printf("          %s(PANIC)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == SLEEP ){
    printf("          %s(SLEEP)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CURSE ){
    printf("          %s(CURSE)", enemy_copy1 -> name);
  }

  if ( enemy_copy2 -> badstatus == GOOD ){
    printf("          %s(GOOD)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == DEAD ){
    printf("                  \n");
  }
  else if ( enemy_copy2 -> badstatus == POISON ){
    printf("          %s(POISON)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == PALYZE ){
    printf("          %s(PALYZE)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == CHARM ){
    printf("          %s(CHARM)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == CLOSE ){
    printf("          %s(CLOSE)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == STONE ){
    printf("          %s(STONE)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == PANIC ){
    printf("          %s(PANIC)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == SLEEP ){
    printf("          %s(SLEEP)\n", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == CURSE ){
    printf("          %s(CURSE)\n", enemy_copy2 -> name);
  }

  printf("\n");

}

void encount_pattern4_layout(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, Enemy *enemy_copy3, int encount_pattern){

  if ( (***enemy) -> badstatus == GOOD ){
    printf("  %s(GOOD)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == DEAD ){
    printf("          ");
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("  %s(POISON)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("  %s(PALYZE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("  %s(CHARM)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("  %s(CLOSE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("  %s(STONE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("  %s(PANIC)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("  %s(SLEEP)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("  %s(CURSE)", (***enemy) -> name);
  }

  if ( enemy_copy1 -> badstatus == GOOD ){
    printf("          %s(GOOD)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( enemy_copy1 -> badstatus == POISON ){
    printf("          %s(POISON)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == PALYZE ){
    printf("          %s(PALYZE)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CHARM ){
    printf("          %s(CHARM)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CLOSE ){
    printf("          %s(CLOSE)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == STONE ){
    printf("          %s(STONE)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == PANIC ){
    printf("          %s(PANIC)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == SLEEP ){
    printf("          %s(SLEEP)", enemy_copy1 -> name);
  }
  else if ( enemy_copy1 -> badstatus == CURSE ){
    printf("          %s(CURSE)", enemy_copy1 -> name);
  }

  if ( enemy_copy2 -> badstatus == GOOD ){
    printf("          %s(GOOD)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( enemy_copy2 -> badstatus == POISON ){
    printf("          %s(POISON)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == PALYZE ){
    printf("          %s(PALYZE)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == CHARM ){
    printf("          %s(CHARM)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == CLOSE ){
    printf("          %s(CLOSE)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == STONE ){
    printf("          %s(STONE)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == PANIC ){
    printf("          %s(PANIC)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == SLEEP ){
    printf("          %s(SLEEP)", enemy_copy2 -> name);
  }
  else if ( enemy_copy2 -> badstatus == CURSE ){
    printf("          %s(CURSE)", enemy_copy2 -> name);
  }

  if ( enemy_copy3 -> badstatus == GOOD ){
    printf("          %s(GOOD)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( enemy_copy3 -> badstatus == POISON ){
    printf("          %s(POISON)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == PALYZE ){
    printf("          %s(PALYZE)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == CHARM ){
    printf("          %s(CHARM)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == CLOSE ){
    printf("          %s(CLOSE)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == STONE ){
    printf("          %s(STONE)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == PANIC ){
    printf("          %s(PANIC)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == SLEEP ){
    printf("          %s(SLEEP)\n", enemy_copy3 -> name);
  }
  else if ( enemy_copy3 -> badstatus == CURSE ){
    printf("          %s(CURSE)\n", enemy_copy3 -> name);
  }

  printf("\n");

}

void encount_pattern5_layout(Enemy ****enemy, Enemy ****enemy1, int encount_pattern){
  if ( (***enemy) -> badstatus == GOOD ){
    printf("             %s(GOOD)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == DEAD ){
    printf("                     ");
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("             %s(POISON)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("             %s(PALYZE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("             %s(CHARM)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("             %s(CLOSE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("             %s(STONE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("             %s(PANIC)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("             %s(SLEEP)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("             %s(CURSE)", (***enemy) -> name);
  }

  if ( (***enemy1) -> badstatus == GOOD ){
    printf("             %s(GOOD)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == DEAD ){
    printf("                     \n");
  }
  else if ( (***enemy1) -> badstatus == POISON ){
    printf("             %s(POISON)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == PALYZE ){
    printf("             %s(PALYZE)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CHARM ){
    printf("             %s(CHARM)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CLOSE ){
    printf("             %s(CLOSE)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == STONE ){
    printf("             %s(STONE)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == PANIC ){
    printf("             %s(PANIC)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == SLEEP ){
    printf("             %s(SLEEP)\n", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CURSE ){
    printf("             %s(CURSE)\n", (***enemy1) -> name);
  }

  printf("\n");
}

void encount_pattern6_layout(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, int encount_pattern){

  if ( (***enemy) -> badstatus == GOOD ){
    printf("  %s(GOOD)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == DEAD ){
    printf("          ");
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("  %s(POISON)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("  %s(PALYZE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("  %s(CHARM)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("  %s(CLOSE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("  %s(STONE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("  %s(PANIC)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("  %s(SLEEP)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("  %s(CURSE)", (***enemy) -> name);
  }

  if ( (***enemy1) -> badstatus == GOOD ){
    printf("          %s(GOOD)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( (***enemy1) -> badstatus == POISON ){
    printf("          %s(POISON)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == PALYZE ){
    printf("          %s(PALYZE)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CHARM ){
    printf("          %s(CHARM)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CLOSE ){
    printf("          %s(CLOSE)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == STONE ){
    printf("          %s(STONE)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == PANIC ){
    printf("          %s(PANIC)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == SLEEP ){
    printf("          %s(SLEEP)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CURSE ){
    printf("          %s(CURSE)", (***enemy1) -> name);
  }

  if ( (***enemy2) -> badstatus == GOOD ){
    printf("          %s(GOOD)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == DEAD ){
    printf("                  \n");
  }
  else if ( (***enemy2) -> badstatus == POISON ){
    printf("          %s(POISON)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == PALYZE ){
    printf("          %s(PALYZE)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == CHARM ){
    printf("          %s(CHARM)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == CLOSE ){
    printf("          %s(CLOSE)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == STONE ){
    printf("          %s(STONE)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == PANIC ){
    printf("          %s(PANIC)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == SLEEP ){
    printf("          %s(SLEEP)\n", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == CURSE ){
    printf("          %s(CURSE)\n", (***enemy2) -> name);
  }

  printf("\n");
}

void encount_pattern7_layout(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3, int encount_pattern){

  if ( (***enemy) -> badstatus == GOOD ){
    printf("  %s(GOOD)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == DEAD ){
    printf("          ");
  }
  else if ( (***enemy) -> badstatus == POISON ){
    printf("  %s(POISON)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PALYZE ){
    printf("  %s(PALYZE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CHARM ){
    printf("  %s(CHARM)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CLOSE ){
    printf("  %s(CLOSE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == STONE ){
    printf("  %s(STONE)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == PANIC ){
    printf("  %s(PANIC)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == SLEEP ){
    printf("  %s(SLEEP)", (***enemy) -> name);
  }
  else if ( (***enemy) -> badstatus == CURSE ){
    printf("  %s(CURSE)", (***enemy) -> name);
  }

  if ( (***enemy1) -> badstatus == GOOD ){
    printf("          %s(GOOD)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( (***enemy1) -> badstatus == POISON ){
    printf("          %s(POISON)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == PALYZE ){
    printf("          %s(PALYZE)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CHARM ){
    printf("          %s(CHARM)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CLOSE ){
    printf("          %s(CLOSE)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == STONE ){
    printf("          %s(STONE)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == PANIC ){
    printf("          %s(PANIC)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == SLEEP ){
    printf("          %s(SLEEP)", (***enemy1) -> name);
  }
  else if ( (***enemy1) -> badstatus == CURSE ){
    printf("          %s(CURSE)", (***enemy1) -> name);
  }

  if ( (***enemy2) -> badstatus == GOOD ){
    printf("          %s(GOOD)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( (***enemy2) -> badstatus == POISON ){
    printf("          %s(POISON)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == PALYZE ){
    printf("          %s(PALYZE)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == CHARM ){
    printf("          %s(CHARM)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == CLOSE ){
    printf("          %s(CLOSE)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == STONE ){
    printf("          %s(STONE)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == PANIC ){
    printf("          %s(PANIC)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == SLEEP ){
    printf("          %s(SLEEP)", (***enemy2) -> name);
  }
  else if ( (***enemy2) -> badstatus == CURSE ){
    printf("          %s(CURSE)", (***enemy2) -> name);
  }

  if ( (***enemy3) -> badstatus == GOOD ){
    printf("          %s(GOOD)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == DEAD ){
    printf("                  ");
  }
  else if ( (***enemy3) -> badstatus == POISON ){
    printf("          %s(POISON)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == PALYZE ){
    printf("          %s(PALYZE)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == CHARM ){
    printf("          %s(CHARM)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == CLOSE ){
    printf("          %s(CLOSE)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == STONE ){
    printf("          %s(STONE)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == PANIC ){
    printf("          %s(PANIC)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == SLEEP ){
    printf("          %s(SLEEP)\n", (***enemy3) -> name);
  }
  else if ( (***enemy3) -> badstatus == CURSE ){
    printf("          %s(CURSE)\n", (***enemy3) -> name);
  }

  printf("\n");

}
