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

//アイテム使用者選択
int battle_item_useselect(Items *****items, Player *****st, Player *****st2, Player *****st3){
  //item_targetとはアイテムを使用する対象メンバー(主人公は１、２人目は２、３人目は３)
  int item_target;
  int command;

  do{
    printf("使用する対象を選択してください(使用しない場合はcを入力)\n");
    if ( (****st) -> badstatus == DEAD ){
      //nothing
    }
    else{
      printf("1:%s ", (****st) -> name);
    }

    if ( (****st2) -> badstatus == DEAD ){
      //nothing
    }
    else{
      printf("2:%s ", (****st2) -> name);
    }

    if ( (****st3) -> badstatus == DEAD ){
      //nothing
    }
    else{
      printf("3:%s ", (****st3) -> name);
    }
    printf("\n");

    command =  _getch();
    if ( command == '1' ){
      if ( (****st) -> badstatus == DEAD ){
        command = 'e';  //error
      }
      else{
        item_target = 1;
      }
    }
    else if ( command == '2' ){
      if ( (****st2) -> badstatus == DEAD ){
        command = 'e';
      }
      else{
        item_target = 2;
      }
    }
    else if ( command == '3' ){
      if ( (****st3) -> badstatus == DEAD ){
        command = 'e';
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

//アイテム使用
void use_items_effect(Player *****st, Player *****st2, Player *****st3, int item_number, int item_target){
  int recover_point, beforehp;

  //傷薬
  if ( item_number == 1 ){
    recover_point = 50;

    if ( item_target == 1 ){
      beforehp = (****st) -> hp;
      (****st) -> hp += recover_point;
      if ( (****st) -> hp >= (****st) -> maxhp ){
        (****st) -> hp = (****st) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st) -> name, beforehp, (****st) -> maxhp, (****st) -> hp, (****st) -> maxhp);
    }
    else if ( item_target == 2 ){
      beforehp = (****st2) -> hp;
      (****st2) -> hp += recover_point;
      if ( (****st2) -> hp >= (****st2) -> maxhp ){
        (****st2) -> hp = (****st2) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st2) -> name, beforehp, (****st2) -> maxhp, (****st2) -> hp, (****st2) -> maxhp);
    }
    else if ( item_target == 3 ){
      beforehp = (****st3) -> hp;
      (****st3) -> hp += recover_point;
      if ( (****st3) -> hp >= (****st3) -> maxhp ){
        (****st3) -> hp = (****st3) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st3) -> name, beforehp, (****st3) -> maxhp, (****st3) -> hp, (****st3) -> maxhp);
    }
  }
  //魔石
  else if ( item_number == 2 ){

    if ( item_target == 1 ){
      recover_point = (****st) -> maxhp * 0.25;
      beforehp = (****st) -> hp;
      (****st) -> hp += recover_point;
      if ( (****st) -> hp >= (****st) -> maxhp ){
        (****st) -> hp = (****st) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st) -> name, beforehp, (****st) -> maxhp, (****st) -> hp, (****st) -> maxhp);
    }
    else if ( item_target == 2 ){
      recover_point = (****st2) -> maxhp * 0.25;
      beforehp = (****st2) -> hp;
      (****st2) -> hp += recover_point;
      if ( (****st2) -> hp >= (****st2) -> maxhp ){
        (****st2) -> hp = (****st2) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st2) -> name, beforehp, (****st2) -> maxhp, (****st2) -> hp, (****st2) -> maxhp);
    }
    else if ( item_target == 3 ){
      recover_point = (****st3) -> maxhp * 0.25;
      beforehp = (****st3) -> hp;
      (****st3) -> hp += recover_point;
      if ( (****st3) -> hp >= (****st3) -> maxhp ){
        (****st3) -> hp = (****st3) -> maxhp;
      }
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st3) -> name, beforehp, (****st3) -> maxhp, (****st3) -> hp, (****st3) -> maxhp);
    }
  }
  else if ( item_number == 3 ){   //宝玉
    if ( item_target == 1 ){
      recover_point = (****st) -> maxhp;
      beforehp = (****st) -> hp;
      (****st) -> hp = recover_point;
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st) -> name, beforehp, (****st) -> maxhp, (****st) -> hp, (****st) -> maxhp);
    }
    else if ( item_target == 2 ){
      recover_point = (****st2) -> maxhp;
      beforehp = (****st2) -> hp;
      (****st2) -> hp = recover_point;
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st2) -> name, beforehp, (****st2) -> maxhp, (****st2) -> hp, (****st2) -> maxhp);
    }
    else if ( item_target == 3 ){
      recover_point = (****st3) -> maxhp;
      beforehp = (****st3) -> hp;
      (****st3) -> hp = recover_point;
      printf("%s HP:%d/%d >> HP:%d/%d\n", (****st3) -> name, beforehp, (****st3) -> maxhp, (****st3) -> hp, (****st3) -> maxhp);
    }
  }
  //antipoison
  else if ( item_number == 4 ){
    if ( item_target == 1 ){
      if ( (****st) -> badstatus == POISON ){
        (****st) -> badstatus = GOOD;
        printf("%s(POISON) >> %s(GOOD)\n", (****st) -> name, (****st) -> name);
      }
      else{
        printf("無効果!\n");
      }
      printf("\n");
    }
    else if ( item_target == 2 ){
      if ( (****st2) -> badstatus == POISON ){
        (****st2) -> badstatus = GOOD;
        printf("%s(POISON) >> %s(GOOD)\n", (****st2) -> name, (****st2) -> name);
      }
      else{
        printf("無効果!\n");
      }
      printf("\n");
    }
    else if ( item_target == 3 ){
      if ( (****st3) -> badstatus == POISON ){
        (****st3) -> badstatus = GOOD;
        printf("%s(POISON) >> %s(GOOD)\n", (****st3) -> name, (****st3) -> name);
      }
      else{
        printf("無効果!\n");
      }
      printf("\n");
    }
  }
}

int battle_item_use(Items ****items, Player ****st, Player ****st2, Player ****st3){
  int items_count, item_target, item_number, turn_decrease, loop_count;
  int command;

  items_count = 0;
  //(***items) -> medicine = 10;
  //(***items) -> lifestone = 10;
  (***items) -> bead = 2;

  loop_count = 0;
  do {
    printf("<<<<<<ITEMS>>>>>>\n");
    if ( (***items) -> medicine > 0 ){
      printf("1.傷薬%d個(味方１人のHPを50回復)\n", (***items) -> medicine);
      printf("\n");
      items_count++;
    }
    if ( (***items) -> lifestone > 0 ){
      printf("2.魔石%d個(味方１人のHPを最大体力の25%%回復)\n", (***items) -> lifestone);
      printf("\n");
      items_count++;
    }
    if ( (***items) -> bead > 0 ){
      printf("3.宝玉%d個(味方1人のHPを全回復)\n", (***items) -> bead);
      printf("\n");
      items_count++;
    }
    if ( (***items) -> antipoison > 0 ){
      printf("4.アンタイポイズン%d個(味方1人のPOISONを回復)\n", (***items) -> antipoison);
      printf("\n");
      items_count++;
    }

    if ( items_count == 0 ){
      printf("使用可能なITEMはありません\n");
      printf("\n");
      turn_decrease = 0.0;
      //printf("turn_decrease:%d\n", turn_decrease);
      return turn_decrease;
    }

    printf("使用したいアイテムを選択してください(使用しない場合はcを入力)\n");
    command =  _getch();

    if ( command == '1' && (***items) -> medicine > 0 ){
      //傷薬はアイテムナンバー1
      item_number = 1;
      item_target = battle_item_useselect(&items,&st,&st2,&st3);
      //printf("item_number:%d\n", item_number);
      //printf("item_target:%d\n", item_target);

      if ( item_target == 0 ){
        //nothing
        turn_decrease = 0.0;
      }
      else if ( item_target == 1 ){
        (***items) -> medicine--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      else if ( item_target == 2 ){
        (***items) -> medicine--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      //item_target = 3
      else if ( item_target == 3 ){
        (***items) -> medicine--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
    }
    else if ( command == '2' && (***items) -> lifestone > 0 ){
      //魔石はアイテムナンバー2
      item_number = 2;
      item_target = battle_item_useselect(&items,&st,&st2,&st3);
      //printf("item_number:%d\n", item_number);
      //printf("item_target:%d\n", item_target);

      if ( item_target == 0 ){
        //nothing
        turn_decrease = 0.0;
      }
      else if ( item_target == 1 ){
        (***items) -> lifestone--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      else if ( item_target == 2 ){
        (***items) -> lifestone--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      //item_target = 3
      else if ( item_target == 3 ){
        (***items) -> lifestone--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
    }
    else if ( command == '3' && (***items) -> bead > 0 ){
      item_number = 3;
      item_target = battle_item_useselect(&items,&st,&st2,&st3);
      //printf("item_number:%d\n", item_number);
      //printf("item_target:%d\n", item_target);

      if ( item_target == 0 ){
        //nothing
        turn_decrease = 0.0;
      }
      else if ( item_target == 1 ){
        (***items) -> bead--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      else if ( item_target == 2 ){
        (***items) -> bead--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      //item_target = 3
      else if ( item_target == 3 ){
        (***items) -> bead--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
    }
    else if ( command == '4' && (***items) -> antipoison > 0 ){
      item_number = 4;
      item_target = battle_item_useselect(&items,&st,&st2,&st3);
      //printf("item_number:%d\n", item_number);
      //printf("item_target:%d\n", item_target);

      if ( item_target == 0 ){
        //nothing
        turn_decrease = 0.0;
      }
      else if ( item_target == 1 ){
        (***items) -> antipoison--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      else if ( item_target == 2 ){
        (***items) -> antipoison--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
      //item_target = 3
      else if ( item_target == 3 ){
        (***items) -> antipoison--;
        use_items_effect(&st,&st2,&st3,item_number,item_target);
        turn_decrease = -1;
        loop_count++;
      }
    }
    else if ( command == 'c' ){
      turn_decrease = 0.0;
      loop_count++;
    }

  }while( loop_count == 0 );


  return turn_decrease;
}

int item_drop_caluculate(int i, int drop_base, int drop_per){
  int drop_count;

  drop_count = 0;

  for ( i = 1; i <= drop_base; i++ ){
    if ( drop_base == i ){
      if ( drop_per >= 1 && drop_per <= i ){   //回避率eva_base%
        drop_count++;
      }
    }
  }

  return drop_count;
}

void item_drop(Player ****st, Player ****st2, Player ****st3, Enemy ****enemy, Items ****items, int encount_pattern){
  int i, drop_per, drop_count, loop;
  double drop_base;

  loop = 0;
  drop_count = 0;
  //スライム
  if ( (***enemy) -> enemy_id == 1 ){
    if ( encount_pattern == 1 || encount_pattern == 2 || encount_pattern == 3 || encount_pattern == 4 ){
      while ( loop != encount_pattern ){
        drop_base = 10;  //drop最低率は10%

        drop_base = drop_base + ( (***st) -> luk * 0.1 + (***st2) -> luk * 0.1 + (***st3) -> luk * 0.1 );
        if ( drop_base > 100 ){
          drop_base = 100;
        }

        //printf("before drop_base:%f\n", drop_base);
        drop_base = round(drop_base);
        //printf("after drop_base:%f\n", drop_base);

        drop_per = (rand() % ( 100 - 1 + 1 ) + 1);  //アイテムドロップ率の乱数
        i = 1;
        drop_count += item_drop_caluculate(i,drop_base,drop_per);

        loop++;
      }
    }
    else{
      drop_base = 10;  //drop最低率は10%

      drop_base = drop_base + ( (***st) -> luk * 0.1 + (***st2) -> luk * 0.1 + (***st3) -> luk * 0.1 );
      if ( drop_base > 100 ){
        drop_base = 100;
      }

      //printf("before drop_base:%f\n", drop_base);
      drop_base = round(drop_base);
      //printf("after drop_base:%f\n", drop_base);

      drop_per = (rand() % ( 100 - 1 + 1 ) + 1);  //アイテムドロップ率の乱数
      i = 1;
      drop_count += item_drop_caluculate(i,drop_base,drop_per);
    }

    //printf("drop_count:%d\n", drop_count);

    if ( drop_count != 0 ){
      printf("DROP ITEM:傷薬×%d\n", drop_count);
      sleep(1);
      (***items) -> medicine += drop_count;
    }

  }
  //コボルト
  else if ( (***enemy) -> enemy_id = 2 ){
    if ( encount_pattern == 1 || encount_pattern == 2 || encount_pattern == 3 || encount_pattern == 4 ){
      while ( loop != encount_pattern ){
        drop_base = 15;  //drop最低率は15%

        drop_base = drop_base + ( (***st) -> luk * 0.1 + (***st2) -> luk * 0.1 + (***st3) -> luk * 0.1 );
        if ( drop_base > 100 ){
          drop_base = 100;
        }

        //printf("before drop_base:%f\n", drop_base);
        drop_base = round(drop_base);
        //printf("after drop_base:%f\n", drop_base);

        drop_per = (rand() % ( 100 - 1 + 1 ) + 1);  //アイテムドロップ率の乱数
        i = 1;
        drop_count += item_drop_caluculate(i,drop_base,drop_per);

        loop++;
      }
    }
    else{
      drop_base = 15;  //drop最低率は15%

      drop_base = drop_base + ( (***st) -> luk * 0.1 + (***st2) -> luk * 0.1 + (***st3) -> luk * 0.1 );
      if ( drop_base > 100 ){
        drop_base = 100;
      }

      //printf("before drop_base:%f\n", drop_base);
      drop_base = round(drop_base);
      //printf("after drop_base:%f\n", drop_base);

      drop_per = (rand() % ( 100 - 1 + 1 ) + 1);  //アイテムドロップ率の乱数
      i = 1;
      drop_count += item_drop_caluculate(i,drop_base,drop_per);
    }


    //printf("drop_count:%d\n", drop_count);

    if ( drop_count != 0 ){
      printf("DROP ITEM:魔石×%d\n", drop_count);
      sleep(1);
      (***items) -> lifestone += drop_count;
    }

  }

}
