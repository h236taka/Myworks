#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <math.h>
#include <wchar.h>
#include "rpg.h"

void menu_hp_graphycal_display(Player *****st, Player *****st2, Player *****st3){
  printf(" ------------");
  printf("           ------------");
  printf("              ------------\n");

  if ( (****st) -> hp == (****st) -> maxhp ){
    printf(" |//////////|");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.9 ){
    printf(" |/////////||");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.8 ){
    printf(" |////////| |");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.7 ){
    printf(" |///////|  |");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.6 ){
    printf(" |//////|   |");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.5 ){
    printf(" |/////|    |");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.4 ){
    printf(" |////|     |");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.3 ){
    printf(" |///|      |");
  }
  else if ( (****st) -> hp >= (****st) -> maxhp * 0.2 ){
    printf(" |//|       |");
  }
  else if ( (****st) -> hp > 0 ){
    printf(" |/|        |");
  }
  else if ( (****st) -> hp == 0 ){
    printf(" ||         |");
  }

  if ( (****st2) -> hp == (****st2) -> maxhp ){
    printf("           |//////////|");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.9 ){
    printf("           |/////////||");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.8 ){
    printf("           |////////| |");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.7 ){
    printf("           |///////|  |");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.6 ){
    printf("           |//////|   |");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.5 ){
    printf("           |/////|    |");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.4 ){
    printf("           |////|     |");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.3 ){
    printf("           |///|      |");
  }
  else if ( (****st2) -> hp >= (****st2) -> maxhp * 0.2 ){
    printf("           |//|       |");
  }
  else if ( (****st2) -> hp > 0 ){
    printf("           |/|        |");
  }
  else if ( (****st2) -> hp == 0 ){
    printf("           ||         |");
  }

  if ( (****st3) -> hp == (****st3) -> maxhp ){
    printf("              |//////////|\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.9 ){
    printf("              |/////////||\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.8 ){
    printf("              |////////| |\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.7 ){
    printf("              |///////|  |\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.6 ){
    printf("              |//////|   |\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.5 ){
    printf("              |/////|    |\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.4 ){
    printf("              |////|     |\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.3 ){
    printf("              |///|      |\n");
  }
  else if ( (****st3) -> hp >= (****st3) -> maxhp * 0.2 ){
    printf("              |//|       |\n");
  }
  else if ( (****st3) -> hp > 0 ){
    printf("              |/|        |\n");
  }
  else if ( (****st3) -> hp == 0 ){
    printf("              ||         |\n");
  }

  printf(" ------------");
  printf("           ------------");
  printf("              ------------\n");

}

void menu_mp_graphycal_display(Player *****st, Player *****st2, Player *****st3){

  printf(" ------------");
  printf("           ------------");
  printf("              ------------\n");

  if ( (****st) -> mp == (****st) -> maxmp ){
    printf(" |//////////|");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.9 ){
    printf(" |/////////||");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.8 ){
    printf(" |////////| |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.7 ){
    printf(" |///////|  |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.6 ){
    printf(" |//////|   |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.5 ){
    printf(" |/////|    |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.4 ){
    printf(" |////|     |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.3 ){
    printf(" |///|      |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.2 ){
    printf(" |//|       |");
  }
  else if ( (****st) -> mp >= (****st) -> maxmp * 0.1 ){
    printf(" |/|        |");
  }
  else{
      //死亡時はHPゲージ表示なし
  }

  if ( (****st2) -> mp == (****st2) -> maxmp ){
    printf("           |//////////|");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.9 ){
    printf("           |/////////||");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.8 ){
    printf("           |////////| |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.7 ){
    printf("           |///////|  |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.6 ){
    printf("           |//////|   |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.5 ){
    printf("           |/////|    |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.4 ){
    printf("           |////|     |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.3 ){
    printf("           |///|      |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.2 ){
    printf("           |//|       |");
  }
  else if ( (****st2) -> mp >= (****st2) -> maxmp * 0.1 ){
    printf("           |/|        |");
  }
  else{
      //死亡時はHPゲージ表示なし
  }

  if ( (****st3) -> mp == (****st3) -> maxmp ){
    printf("              |//////////|\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.9 ){
    printf("              |/////////||\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.8 ){
    printf("              |////////| |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.7 ){
    printf("              |///////|  |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.6 ){
    printf("              |//////|   |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.5 ){
    printf("              |/////|    |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.4 ){
    printf("              |////|     |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.3 ){
    printf("              |///|      |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.2 ){
    printf("              |//|       |\n");
  }
  else if ( (****st3) -> mp >= (****st3) -> maxmp * 0.1 ){
    printf("              |/|        |\n");
  }
  else{
      //死亡時はHPゲージ表示なし
  }

  printf(" ------------");
  printf("           ------------");
  printf("              ------------\n");
}

//Playerの状態を表示
void menu_display_condition(Player *****st, int battle_display_condition_count){

  if ( battle_display_condition_count == 0 ){
    if ( (****st) -> badstatus == GOOD ){
      printf(" STATUS:GOOD");
    }
    else if ( (****st) -> badstatus == DEAD ){
      printf(" STATUS:DEAD");
    }
    else if ( (****st) -> badstatus == POISON ){
      printf(" STATUS:POISON");
    }
    else if ( (****st) -> badstatus == PALYZE ){
      printf(" STATUS:PALYZE");
    }
    else if ( (****st) -> badstatus == CHARM ){
      printf(" STATUS:CHARM");
    }
    else if ( (****st) -> badstatus == CLOSE ){
      printf(" STATUS:CLOSE");
    }
    else if ( (****st) -> badstatus == STONE ){
      printf(" STATUS:STONE");
    }
    else if ( (****st) -> badstatus == PANIC ){
      printf(" STATUS:PANIC");
    }
    else if ( (****st) -> badstatus == SLEEP ){
      printf(" STATUS:SLEEP");
    }
    else if ( (****st) -> badstatus == CURSE ){
      printf(" STATUS:CURSE");
    }
  }
  else if ( battle_display_condition_count == 1 ){
    if ( (****st) -> badstatus == GOOD ){
      printf("           STATUS:GOOD");
    }
    else if ( (****st) -> badstatus == DEAD ){
      printf("           STATUS:DEAD");
    }
    else if ( (****st) -> badstatus == POISON ){
      printf("           STATUS:POISON");
    }
    else if ( (****st) -> badstatus == PALYZE ){
      printf("           STATUS:PALYZE");
    }
    else if ( (****st) -> badstatus == CHARM ){
      printf("           STATUS:CHARM");
    }
    else if ( (****st) -> badstatus == CLOSE ){
      printf("           STATUS:CLOSE");
    }
    else if ( (****st) -> badstatus == STONE ){
      printf("           STATUS:STONE");
    }
    else if ( (****st) -> badstatus == PANIC ){
      printf("           STATUS:PANIC");
    }
    else if ( (****st) -> badstatus == SLEEP ){
      printf("           STATUS:SLEEP");
    }
    else if ( (****st) -> badstatus == CURSE ){
      printf("           STATUS:CURSE");
    }
  }
  else{
    if ( (****st) -> badstatus == GOOD ){
      printf("               STATUS:GOOD");
    }
    else if ( (****st) -> badstatus == DEAD ){
      printf("               STATUS:DEAD");
    }
    else if ( (****st) -> badstatus == POISON ){
      printf("               STATUS:POISON");
    }
    else if ( (****st) -> badstatus == PALYZE ){
      printf("               STATUS:PALYZE");
    }
    else if ( (****st) -> badstatus == CHARM ){
      printf("               STATUS:CHARM");
    }
    else if ( (****st) -> badstatus == CLOSE ){
      printf("               STATUS:CLOSE");
    }
    else if ( (****st) -> badstatus == STONE ){
      printf("               STATUS:STONE");
    }
    else if ( (****st) -> badstatus == PANIC ){
      printf("               STATUS:PANIC");
    }
    else if ( (****st) -> badstatus == SLEEP ){
      printf("               STATUS:SLEEP");
    }
    else if ( (****st) -> badstatus == CURSE ){
      printf("               STATUS:CURSE");
    }
  }
}

void menu_player_effective(Player *******st){

  if ( (******st) -> physical_attack == 200 ){
    printf("物理弱点 ");
  }
  else if ( (******st) -> physical_attack == 50 || (******st) -> physical_attack == 25 ){
    printf("物理耐性 ");
  }
  else if ( (******st) -> physical_attack == -1 ){
    printf("物理無効 ");
  }
  else if ( (******st) -> physical_attack == -2 ){
    printf("物理吸収 ");
  }
  else if ( (******st) -> physical_attack == -3 ){
    printf("物理反射 ");
  }

  if ( (******st) -> gun_attack == 200 ){
    printf("銃撃弱点 ");
  }
  else if ( (******st) -> gun_attack == 50 || (******st) -> gun_attack == 25 ){
    printf("銃撃耐性 ");
  }
  else if ( (******st) -> gun_attack == -1 ){
    printf("銃撃無効 ");
  }
  else if ( (******st) -> gun_attack == -2 ){
    printf("銃撃吸収 ");
  }
  else if ( (******st) -> gun_attack == -3 ){
    printf("銃撃反射 ");
  }

  if ( (******st) -> fire == 200 ){
    printf("火炎弱点 ");
  }
  else if ( (******st) -> fire == 50 || (******st) -> fire == 25 ){
    printf("火炎耐性 ");
  }
  else if ( (******st) -> fire == -1 ){
    printf("火炎無効 ");
  }
  else if ( (******st) -> fire == -2 ){
    printf("火炎吸収 ");
  }
  else if ( (******st) -> fire == -3 ){
    printf("火炎反射 ");
  }

  if ( (******st) -> ice == 200 ){
    printf("氷結弱点 ");
  }
  else if ( (******st) -> ice == 50 || (******st) -> ice == 25 ){
    printf("氷結耐性 ");
  }
  else if ( (******st) -> ice == -1 ){
    printf("氷結無効 ");
  }
  else if ( (******st) -> ice == -2 ){
    printf("氷結吸収 ");
  }
  else if ( (******st) -> ice == -3 ){
    printf("氷結反射 ");
  }

  if ( (******st) -> elec == 200 ){
    printf("電撃弱点 ");
  }
  else if ( (******st) -> elec == 50 || (******st) -> elec == 25 ){
    printf("電撃耐性 ");
  }
  else if ( (******st) -> elec == -1 ){
    printf("電撃無効 ");
  }
  else if ( (******st) -> elec == -2 ){
    printf("電撃吸収 ");
  }
  else if ( (******st) -> elec == -3 ){
    printf("電撃反射 ");
  }

  if ( (******st) -> wave == 200 ){
    printf("衝撃弱点 ");
  }
  else if ( (******st) -> wave == 50 || (******st) -> wave == 25 ){
    printf("衝撃耐性 ");
  }
  else if ( (******st) -> wave == -1 ){
    printf("衝撃無効 ");
  }
  else if ( (******st) -> wave == -2 ){
    printf("衝撃吸収 ");
  }
  else if ( (******st) -> wave == -3 ){
    printf("衝撃反射 ");
  }

  if ( (******st) -> almighty == 50 || (******st) -> almighty == 25 ){
    printf("万能耐性 ");
  }

  if ( (******st) -> death == 200 ){
    printf("呪殺弱点 ");
  }
  else if ( (******st) -> death == 50 || (******st) -> death == 25 ){
    printf("呪殺耐性 ");
  }
  else if ( (******st) -> death == -1 ){
    printf("呪殺無効 ");
  }
  else if ( (******st) -> death == -2 ){
    printf("呪殺吸収 ");
  }
  else if ( (******st) -> death == -3 ){
    printf("呪殺反射 ");
  }

  if ( (******st) -> expel == 200 ){
    printf("破魔弱点 ");
  }
  else if ( (******st) -> expel == 50 || (******st) -> expel == 25 ){
    printf("破魔耐性 ");
  }
  else if ( (******st) -> expel == -1 ){
    printf("破魔無効 ");
  }
  else if ( (******st) -> expel == -2 ){
    printf("破魔吸収 ");
  }
  else if ( (******st) -> expel == -3 ){
    printf("破魔反射 ");
  }

  if ( (******st) -> poison == 200 ){
    printf("毒弱点 ");
  }
  else if ( (******st) -> poison == 50 || (******st) -> poison == 25 ){
    printf("毒耐性 ");
  }
  else if ( (******st) -> poison == -1 ){
    printf("毒無効 ");
  }
  else if ( (******st) -> poison == -2 ){
    printf("毒吸収 ");
  }
  else if ( (******st) -> poison == -3 ){
    printf("毒反射 ");
  }

  if ( (******st) -> palyze == 200 ){
    printf("麻痺弱点 ");
  }
  else if ( (******st) -> palyze == 50 || (******st) -> palyze == 25 ){
    printf("麻痺耐性 ");
  }
  else if ( (******st) -> palyze == -1 ){
    printf("麻痺無効 ");
  }
  else if ( (******st) -> palyze == -2 ){
    printf("麻痺吸収 ");
  }
  else if ( (******st) -> palyze == -3 ){
    printf("麻痺反射 ");
  }

  if ( (******st) -> charm == 200 ){
    printf("魅了弱点 ");
  }
  else if ( (******st) -> charm == 50 || (******st) -> charm == 25 ){
    printf("魅了耐性 ");
  }
  else if ( (******st) -> charm == -1 ){
    printf("魅了無効 ");
  }
  else if ( (******st) -> charm == -2 ){
    printf("魅了吸収 ");
  }
  else if ( (******st) -> charm == -3 ){
    printf("魅了反射 ");
  }

  if ( (******st) -> close == 200 ){
    printf("魔封弱点 ");
  }
  else if ( (******st) -> close == 50 || (******st) -> close == 25 ){
    printf("魔封耐性 ");
  }
  else if ( (******st) -> close == -1 ){
    printf("魔封無効 ");
  }
  else if ( (******st) -> close == -2 ){
    printf("魔封吸収 ");
  }
  else if ( (******st) -> close == -3 ){
    printf("魔封反射 ");
  }

  if ( (******st) -> stone == 200 ){
    printf("石化弱点 ");
  }
  else if ( (******st) -> stone == 50 || (******st) -> stone == 25 ){
    printf("石化耐性 ");
  }
  else if ( (******st) -> stone == -1 ){
    printf("石化無効 ");
  }
  else if ( (******st) -> stone == -2 ){
    printf("石化吸収 ");
  }
  else if ( (******st) -> stone == -3 ){
    printf("石化反射 ");
  }

  if ( (******st) -> panic == 200 ){
    printf("混乱弱点 ");
  }
  else if ( (******st) -> panic == 50 || (******st) -> panic == 25 ){
    printf("混乱耐性 ");
  }
  else if ( (******st) -> panic == -1 ){
    printf("混乱無効 ");
  }
  else if ( (******st) -> panic == -2 ){
    printf("混乱吸収 ");
  }
  else if ( (******st) -> panic == -3 ){
    printf("混乱反射 ");
  }

  if ( (******st) -> sleep == 200 ){
    printf("睡眠弱点 ");
  }
  else if ( (******st) -> sleep == 50 || (******st) -> sleep == 25 ){
    printf("睡眠耐性 ");
  }
  else if ( (******st) -> sleep == -1 ){
    printf("睡眠無効 ");
  }
  else if ( (******st) -> sleep == -2 ){
    printf("睡眠吸収 ");
  }
  else if ( (******st) -> sleep == -3 ){
    printf("睡眠反射 ");
  }

  if ( (******st) -> curse == 200 ){
    printf("呪い弱点 ");
  }
  else if ( (******st) -> curse == 50 || (******st) -> curse == 25 ){
    printf("呪い耐性 ");
  }
  else if ( (******st) -> curse == -1 ){
    printf("呪い無効 ");
  }
  else if ( (******st) -> curse == -2 ){
    printf("呪い吸収 ");
  }
  else if ( (******st) -> curse == -3 ){
    printf("呪い反射 ");
  }

  printf("\n");
}

void menu_player_status(Player ******st){
  int command;

  do{
    printf("<<<STATUS>>>\n");
    printf("%s:LV:%d EXP:%d NEXT EXP:%d\n", (*****st) -> name, (*****st) -> lv, (*****st) -> sumexp, (*****st) -> nextexp);
    printf("HP:%d/%d MP:%d/%d\n", (*****st) -> hp, (*****st) -> maxhp, (*****st) -> mp, (*****st) -> maxmp);
    printf("力:%d\n", (*****st) -> atk);
    printf("魔:%d\n", (*****st) -> magic);
    printf("体:%d\n", (*****st) -> str);
    printf("速:%d\n", (*****st) -> agi);
    printf("運:%d\n", (*****st) -> luk);

    printf("\n");
    menu_player_effective(&st);

    printf("\n");
    printf("戻る場合はcを入力してください。\n");
    command = _getch();
    if ( command == '' ){
      printf("強制終了\n");
      exit(EXIT_FAILURE);
    }
  } while ( command != 'c' );
}

int menu_item_useselect(Player *******st, Player *******st2, Player *******st3, Items *******items){
  int item_target;
  int command;

  do{
    printf("使用する対象を選択してください(使用しない場合はcを入力)\n");
    if ( (******st) -> badstatus == DEAD ){
      //nothing
    }
    else{
      printf("1:%s ", (******st) -> name);
    }

    if ( (******st2) -> badstatus == DEAD ){
      //nothing
    }
    else{
      printf("2:%s ", (******st2) -> name);
    }

    if ( (******st3) -> badstatus == DEAD ){
      //nothing
    }
    else{
      printf("3:%s ", (******st3) -> name);
    }
    printf("\n");

    command =  _getch();
    if ( command == '1' ){
      if ( (******st) -> badstatus == DEAD ){
        command = 'e'; //error
      }
      else{
        item_target = 1;
      }
    }
    else if ( command == '2' ){
      if ( (******st2) -> badstatus == DEAD ){
        command = 'e'; //error
      }
      else{
        item_target = 2;
      }
    }
    else if ( command == '3' ){
      if ( (******st3) -> badstatus == DEAD ){
        command = 'e'; //error
      }
      else{
        item_target = 3;
      }
    }
    else if ( command == 'c' ){
      item_target = 0;
    }

  }while ( command != '1' && command != '2' && command != '3' && command != 'c' );

  return item_target;

}

void menu_use_items_effect(Player *******st, Player *******st2, Player *******st3, int item_number, int item_target){
  int recover_point, beforehp;

  //傷薬
  if ( item_number == 1 ){
    recover_point = 50;

    if ( item_target == 1 ){
      beforehp = (******st) -> hp;
      (******st) -> hp += recover_point;
      if ( (******st) -> hp >= (******st) -> maxhp ){
        (******st) -> hp = (******st) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st) -> name, beforehp, (******st) -> maxhp, (******st) -> hp, (******st) -> maxhp);
      printf("\n");
    }
    else if ( item_target == 2 ){
      beforehp = (******st2) -> hp;
      (******st2) -> hp += recover_point;
      if ( (******st2) -> hp >= (******st2) -> maxhp ){
        (******st2) -> hp = (******st2) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st2) -> name, beforehp, (******st2) -> maxhp, (******st2) -> hp, (******st2) -> maxhp);
      printf("\n");
    }
    else if ( item_target == 3 ){
      beforehp = (******st3) -> hp;
      (******st3) -> hp += recover_point;
      if ( (******st3) -> hp >= (******st3) -> maxhp ){
        (******st3) -> hp = (******st3) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st3) -> name, beforehp, (******st3) -> maxhp, (******st3) -> hp, (******st3) -> maxhp);
      printf("\n");
    }
  }
  else if ( item_number == 2 ){

    if ( item_target == 1 ){
      recover_point = (******st) -> maxhp * 0.25;
      beforehp = (******st) -> hp;
      (******st) -> hp += recover_point;
      if ( (******st) -> hp >= (******st) -> maxhp ){
        (******st) -> hp = (******st) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st) -> name, beforehp, (******st) -> maxhp, (******st) -> hp, (******st) -> maxhp);
      printf("\n");
    }
    else if ( item_target == 2 ){
      recover_point = (******st2) -> maxhp * 0.25;
      beforehp = (******st2) -> hp;
      (******st2) -> hp += recover_point;
      if ( (******st2) -> hp >= (******st2) -> maxhp ){
        (******st2) -> hp = (******st2) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st2) -> name, beforehp, (******st2) -> maxhp, (******st2) -> hp, (******st2) -> maxhp);
      printf("\n");
    }
    else if ( item_target == 3 ){
      recover_point = (******st3) -> maxhp * 0.25;
      beforehp = (******st3) -> hp;
      (******st3) -> hp += recover_point;
      if ( (******st3) -> hp >= (******st3) -> maxhp ){
        (******st3) -> hp = (******st3) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st3) -> name, beforehp, (******st3) -> maxhp, (******st3) -> hp, (******st3) -> maxhp);
    }
  }
  else if ( item_number == 3 ){  //宝玉
    if ( item_target == 1 ){
      beforehp = (******st) -> hp;
      recover_point = (******st) -> maxhp;
      (******st) -> hp = recover_point;
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st) -> name, beforehp, (******st) -> maxhp, (******st) -> hp, (******st) -> maxhp);
    }
    else if ( item_target == 2 ){
      beforehp = (******st2) -> hp;
      recover_point = (******st2) -> maxhp;
      (******st2) -> hp = recover_point;
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st2) -> name, beforehp, (******st2) -> maxhp, (******st2) -> hp, (******st2) -> maxhp);
    }
    else if ( item_target == 3 ){
      beforehp = (******st3) -> hp;
      recover_point = (******st3) -> maxhp;
      (******st3) -> hp = recover_point;
      printf("%s HP:%d/%d >> HP:%d/%d\n", (******st3) -> name, beforehp, (******st3) -> maxhp, (******st3) -> hp, (******st3) -> maxhp);
    }
  }
  else if ( item_number == 4 ){
    if ( item_target == 1 ){
      if ( (******st) -> badstatus == POISON ){
        (******st) -> badstatus = GOOD;
        printf("%s(POISON) >> %s(GOOD)\n", (******st) -> name, (******st) -> name);
      }
      else{
        printf("無効果!\n");
      }
      printf("\n");
    }
    else if ( item_target == 2 ){
      if ( (******st2) -> badstatus == POISON ){
        (******st2) -> badstatus = GOOD;
        printf("%s(POISON) >> %s(GOOD)\n", (******st2) -> name, (******st2) -> name);
      }
      else{
        printf("無効果!\n");
      }
      printf("\n");
    }
    else if ( item_target == 3 ){
      if ( (******st3) -> badstatus == POISON ){
        (******st3) -> badstatus = GOOD;
        printf("%s(POISON) >> %s(GOOD)\n", (******st3) -> name, (******st3) -> name);
      }
      else{
        printf("無効果!\n");
      }
      printf("\n");
    }
  }
}

void menu_item_use(Player ******st, Player ******st2, Player ******st3, Items ******items, int command){
  int item_number, item_target;

  if ( command == '1' ){
    item_number = 1;
    item_target = menu_item_useselect(&st,&st2,&st3,&items);
    //printf("item_number:%d\n", item_number);
    //printf("item_target:%d\n", item_target);

    if ( item_target == 0 ){
      //nothing
      return;
    }
    else if ( item_target == 1 ){
      (*****items) -> medicine--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    else if ( item_target == 2 ){
      (*****items) -> medicine--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    //item_target = 3
    else if ( item_target == 3 ){
      (*****items) -> medicine--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
  }
  else if ( command == '2' ){
    item_number = 2;
    item_target = menu_item_useselect(&st,&st2,&st3,&items);
    //printf("item_number:%d\n", item_number);
    //printf("item_target:%d\n", item_target);

    if ( item_target == 0 ){
      //nothing
      return;
    }
    else if ( item_target == 1 ){
      (*****items) -> lifestone--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    else if ( item_target == 2 ){
      (*****items) -> lifestone--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    //item_target = 3
    else if ( item_target == 3 ){
      (*****items) -> lifestone--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
  }
  else if ( command == '3' ){
    item_number = 3;
    item_target = menu_item_useselect(&st,&st2,&st3,&items);
    //printf("item_number:%d\n", item_number);
    //printf("item_target:%d\n", item_target);

    if ( item_target == 0 ){
      //nothing
      return;
    }
    else if ( item_target == 1 ){
      (*****items) -> bead--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    else if ( item_target == 2 ){
      (*****items) -> bead--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    //item_target = 3
    else if ( item_target == 3 ){
      (*****items) -> bead--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
  }
  else if ( command == '4' ){
    item_number = 4;
    item_target = menu_item_useselect(&st,&st2,&st3,&items);
    //printf("item_number:%d\n", item_number);
    //printf("item_target:%d\n", item_target);

    if ( item_target == 0 ){
      //nothing
      return;
    }
    else if ( item_target == 1 ){
      (*****items) -> antipoison--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    else if ( item_target == 2 ){
      (*****items) -> antipoison--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
    //item_target = 3
    else if ( item_target == 3 ){
      (*****items) -> antipoison--;
      menu_use_items_effect(&st,&st2,&st3,item_number,item_target);
      printf("\n");
      return;
    }
  }
}

<<<<<<< HEAD
void equip_change(Player ******st, Equip ******pEquip, Equip ******p2Equip, Equip ******p3Equip){
=======
void equip_change(Player ******st, Equip ******equip){
>>>>>>> origin/main

  printf("\n");
  printf("<<<EQUIP>>>\n");
  printf("%s:", (*****st) -> name);

}

void item_menu(Player *****st, Player *****st2, Player *****st3, Items *****items){
  int command;
  int items_count;

  //to check programs
  //(****items) -> medicine = 1;
  //(****items) -> lifestone = 1;
  //(****items) -> antipoison = 1;

  printf("<<<ITEM>>>\n");
  do{
    items_count = 0;
    if ( (****items) -> medicine > 0 ){
      printf("1.傷薬%d個(味方１人のHPを50回復)\n", (****items) -> medicine);
      items_count = 1;
    }
    if ( (****items) -> lifestone > 0 ){
      printf("2.魔石%d個(味方１人のHPを最大体力の25%%回復)\n", (****items) -> lifestone);
      items_count = 1;
    }
    if ( (****items) -> bead > 0 ){
      printf("3.宝玉%d個(味方1人の体力を全回復)\n", (****items) -> bead);
      items_count = 1;
    }
    if ( (****items) -> antipoison > 0 ){
      printf("4.アンタイポイズン%d個(味方1人のPOISONを回復)\n", (****items) -> antipoison);
      items_count = 1;
    }

    if ( items_count == 0 ){
      printf("ITEMを所持していません\n");
      return;
    }

    printf("\n");
    printf("使用しない場合はcを入力してください!\n");

    command =  _getch();
    if ( command == '1' && (****items) -> medicine > 0 ){
      menu_item_use(&st,&st2,&st3,&items, command);
    }
    else if ( command == '2' && (****items) -> lifestone > 0 ){
      menu_item_use(&st,&st2,&st3,&items, command);
    }
    else if ( command == '3' && (****items) -> bead > 0 ){
      menu_item_use(&st,&st2,&st3,&items, command);
    }
    else if ( command == '4' && (****items) -> antipoison > 0 ){
      menu_item_use(&st,&st2,&st3,&items,command);
    }
    else if ( command == '' ){
      printf("強制終了\n");
      exit(EXIT_FAILURE);
    }
  }while ( command != 'c' );

}

void skill_menu(void){

  printf("skill\n");
}

<<<<<<< HEAD
void equip_menu(Player *****st, Player *****st2, Player *****st3, Equip *****pEquip, Equip *****p2Equip, Equip *****p3Equip){
=======
void equip_menu(Player *****st, Player *****st2, Player *****st3, Equip *****equip){
>>>>>>> origin/main
  int input;

  do {
    printf("\n");
    printf("<<<EQUIP>>>\n");
    printf("誰の装備を変更しますか?(戻る場合はcを入力してください)");
    printf("1:%s\n", (****st) -> name);
    printf("2:%s\n", (****st2) -> name);
    printf("3:%s\n", (****st3) -> name);

    input = _getch();

    if ( input == '1' ){
<<<<<<< HEAD
      equip_change(&st,&pEquip,&p2Equip,&p3Equip);
    }
    else if ( input == '2' ){
      equip_change(&st2,&pEquip,&p2Equip,&p3Equip);
    }
    else if ( input == '3' ){
      equip_change(&st3,&pEquip,&p2Equip,&p3Equip);
=======
      equip_change(&st,&equip);
    }
    else if ( input == '2' ){
      equip_change(&st2,&equip);
    }
    else if ( input == '3' ){
      equip_change(&st3,&equip);
>>>>>>> origin/main
    }
    else if ( input == '' ){
      printf("強制終了\n");
      exit(EXIT_FAILURE);
    }

  } while ( input != 'c' );
<<<<<<< HEAD
=======
  printf("equip\n");
>>>>>>> origin/main
}

void set_menu(void){

  printf("set\n");
}

void status_menu(Player *****st, Player *****st2, Player *****st3){
  int command;

  printf("\n");
  printf("<<<STATUS>>>\n");

  do{
    printf("誰のSTATUSを表示しますか?(戻る場合はcを入力してください。)\n");
    printf("1:%s\n", (****st) -> name);
    printf("2:%s\n", (****st2) -> name);
    printf("3:%s\n", (****st3) -> name);

    command =  _getch();

    if ( command == '1' ){
      menu_player_status(&st);
    }
    else if ( command == '2' ){
      menu_player_status(&st2);
    }
    else if ( command == '3' ){
      menu_player_status(&st3);
    }
    else if ( command == '' ){
      printf("強制終了\n");
      exit(EXIT_FAILURE);
    }

  } while( command != 'c' );

}

void map_menu(Map ***map, Area *****area, int area_data_line, int area_data_len, int automap_area[area_data_line][area_data_len]){
  int i, j, input;

  printf("P:現在地 *:歩いた場所\n");
  printf("<<<<<<<MAP>>>>>>\n");
  for ( j = 0; j < area_data_line; j++ ){
    printf("   ");
    for ( i = 0; i < area_data_len; i++ ){
      if ( automap_area[j][i] == -1 || automap_area[j][i] == 0 ){
        printf(" ");
      }
      else if ( j == (**map) -> y && i == (**map) -> x ){
        printf("P");
        //automap_area[j][i] = 'P';
      }
      else if ( automap_area[j][i] == 1 ){
        printf("*");
      }
    }
    printf("\n");
  }

  printf("\n");

  do{
    printf("mapを閉じるにはcを入力してください。\n");
    input = _getch();
  }while( input != 'c' );

  printf("\n");

}

<<<<<<< HEAD
void display_menu(Player ****st, Player ****st2, Player ****st3, P_skill ****player_skill, P_skill ****player_skill2, P_skill ****player_skill3, Items ****items, Equip ****pEquip, Equip ****p2Equip, Equip ****p3Equip, Map **map, Area ****area, int area_data_line, int area_data_len, int automap_area[area_data_line][area_data_len]){
=======
void display_menu(Player ****st, Player ****st2, Player ****st3, P_skill ****player_skill, P_skill ****player_skill2, P_skill ****player_skill3, Items ****items, Equip ****equip, Map **map, Area ****area, int area_data_line, int area_data_len, int automap_area[area_data_line][area_data_len]){
>>>>>>> origin/main
  int menu_end, input, battle_display_condition_count;

  do{
    printf("\n");
    printf("------MENU--------\n");
    printf("|  1:ITEM        |\n");
    printf("|  2:SKILL       |\n");
    printf("|  3:EQUIP       |\n");
    printf("|  4:SET         |\n");
    printf("|  5:STATUS      |\n");
    printf("|  6:MAP         |\n");
    printf("------------------\n");
    printf("\n");
    printf("GOLD:%d\n", (***st) -> gold);
    printf("\n");
    printf("      %3s                   %3s                   %3s\n", (***st) -> name, (***st2) -> name, (***st3) -> name);
    printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d          HP:%d/%d MP:%d/%d\n", (***st) -> hp, (***st) -> maxhp, (***st) -> mp, (***st) -> maxmp, (***st2) -> hp, (***st2) -> maxhp, (***st2) -> mp, (***st2) -> maxmp, (***st3) -> hp, (***st3) -> maxhp, (***st3) -> mp, (***st3) -> maxmp);

    //HPをグラフィックに表現
    menu_hp_graphycal_display(&st,&st2,&st3);
    //MPをグラフィックに表現
    menu_mp_graphycal_display(&st,&st2,&st3);

    //partyの状態異常ステータスを表示
    battle_display_condition_count = 0;
    menu_display_condition(&st, battle_display_condition_count);

    battle_display_condition_count++;
    menu_display_condition(&st2, battle_display_condition_count);

    battle_display_condition_count++;
    menu_display_condition(&st3, battle_display_condition_count);

    battle_display_condition_count = 0;
    printf("\n");

    printf(" LV:%d", (***st) -> lv);
    printf("                  LV:%d", (***st2) -> lv);
    printf("                     LV:%d", (***st3) -> lv);
    printf("\n");

    printf("メニュー終了時はcを押してください!\n");

    input =  _getch();
    printf("入力：%c\n", input);
    if ( input == '1' ){
      item_menu(&st,&st2,&st3,&items);
    }
    else if ( input == '2' ){
      skill_menu();
    }
    else if ( input == '3' ){
<<<<<<< HEAD
      equip_menu(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip);
=======
      equip_menu(&st,&st2,&st3,&equip);
>>>>>>> origin/main
    }
    else if ( input == '4' ){
      set_menu();
    }
    else if ( input == '5' ){
      status_menu(&st,&st2,&st3);
    }
    else if ( input == '6' ){
      map_menu(&map,&area,area_data_line,area_data_len,automap_area);
    }
    else if ( input == ''){   //ctrl + C
      printf("error!\n");
      exit(EXIT_FAILURE);
    }

  }while( input != 'c' );

  //printf("上下左右キーを押してダンジョン画面に戻ります\n");

}
