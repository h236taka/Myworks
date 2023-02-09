#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include "rpg.h"

int player_ability(Player ****st, Player ****st2, Player ****st3, P_skill ****player_skill, int use_skill_count, int skill_target, int skill_user){
  int recover_point, base, beforehp;

  if ( use_skill_count == 1 ){

    //skill使用者
    if ( skill_user == 1 ){
      printf("%s>>ケディア\n", (***st) -> name);
      sleep(1);

      if ( (***st) -> mp < 3 ){
        printf("MP不足!\n");
      }
      else{
        (***st) -> mp -= 3;

        base = 25;
        recover_point = (rand() % ( base + (***st) -> magic * 3 + (***st) -> luk - base + 1) ) + base; //(rand()%(max - min + 1)) + min;

        if ( skill_target == 1 ){
          beforehp = (***st) -> hp;

          (***st) -> hp += recover_point;
          if ( (***st) -> hp >= (***st) -> maxhp ){
            (***st) -> hp = (***st) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st) -> name, beforehp, (***st) -> maxhp, (***st) -> hp, (***st) -> maxhp);
          printf("\n");
        }
        else if ( skill_target == 2 ){
          beforehp = (***st2) -> hp;

          (***st2) -> hp += recover_point;
          if ( (***st2) -> hp >= (***st2) -> maxhp ){
            (***st2) -> hp = (***st2) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st2) -> name, beforehp, (***st2) -> maxhp, (***st2) -> hp, (***st2) -> maxhp);
          printf("\n");
        }
        else if ( skill_target == 3 ){
          beforehp = (***st3) -> hp;

          (***st3) -> hp += recover_point;
          if ( (***st3) -> hp >= (***st3) -> maxhp ){
            (***st3) -> hp = (***st3) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st3) -> name, beforehp, (***st3) -> maxhp, (***st3) -> hp, (***st3) -> maxhp);
          printf("\n");
        }

      }
    }
    else if ( skill_user == 2 ){
      printf("%s>>ケディア\n", (***st2) -> name);
      sleep(1);

      if ( (***st2) -> mp < 3 ){
        printf("MP不足!\n");
      }
      else{
        (***st2) -> mp -= 3;

        base = 25;
        recover_point = (rand() % ( base + (***st2) -> magic * 3 + (***st2) -> luk - base + 1) ) + base; //(rand()%(max - min + 1)) + min;

        if ( skill_target == 1 ){
          beforehp = (***st) -> hp;

          (***st) -> hp += recover_point;
          if ( (***st) -> hp >= (***st) -> maxhp ){
            (***st) -> hp = (***st) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st) -> name, beforehp, (***st) -> maxhp, (***st) -> hp, (***st) -> maxhp);
          printf("\n");
        }
        else if ( skill_target == 2 ){
          beforehp = (***st2) -> hp;

          (***st2) -> hp += recover_point;
          if ( (***st2) -> hp >= (***st2) -> maxhp ){
            (***st2) -> hp = (***st2) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st2) -> name, beforehp, (***st2) -> maxhp, (***st2) -> hp, (***st2) -> maxhp);
          printf("\n");
        }
        else if ( skill_target == 3 ){
          beforehp = (***st3) -> hp;

          (***st3) -> hp += recover_point;
          if ( (***st3) -> hp >= (***st3) -> maxhp ){
            (***st3) -> hp = (***st3) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st3) -> name, beforehp, (***st3) -> maxhp, (***st3) -> hp, (***st3) -> maxhp);
          printf("\n");
        }

      }
    }
    else if ( skill_user == 3 ){
      printf("%s>>ケディア\n", (***st3) -> name);
      sleep(1);

      if ( (***st3) -> mp < 3 ){
        printf("MP不足!\n");
      }
      else{
        (***st3) -> mp -= 3;

        base = 25;
        recover_point = (rand() % ( base + (***st3) -> magic * 3 + (***st3) -> luk - base + 1) ) + base; //(rand()%(max - min + 1)) + min;

        if ( skill_target == 1 ){
          beforehp = (***st) -> hp;

          (***st) -> hp += recover_point;
          if ( (***st) -> hp >= (***st) -> maxhp ){
            (***st) -> hp = (***st) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st) -> name, beforehp, (***st) -> maxhp, (***st) -> hp, (***st) -> maxhp);
          printf("\n");
        }
        else if ( skill_target == 2 ){
          beforehp = (***st2) -> hp;

          (***st2) -> hp += recover_point;
          if ( (***st2) -> hp >= (***st2) -> maxhp ){
            (***st2) -> hp = (***st2) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st2) -> name, beforehp, (***st2) -> maxhp, (***st2) -> hp, (***st2) -> maxhp);
          printf("\n");
        }
        else if ( skill_target == 3 ){
          beforehp = (***st3) -> hp;

          (***st3) -> hp += recover_point;
          if ( (***st3) -> hp >= (***st3) -> maxhp ){
            (***st3) -> hp = (***st3) -> maxhp;
          }

          printf("%s: HP:%d/%d >> HP:%d/%d\n", (***st3) -> name, beforehp, (***st3) -> maxhp, (***st3) -> hp, (***st3) -> maxhp);
          printf("\n");
        }

      }
    }

  }
  else if ( use_skill_count == 2 ){  //キュアポ
    //skill使用者
    if ( skill_user == 1 ){
      printf("%s>>キュアポ\n", (***st) -> name);
      sleep(1);

      if ( (***st) -> mp < 4 ){
        printf("MP不足!\n");
      }
      else{
        (***st) -> mp -= 4;

        if ( skill_target == 1 ){
          if ( (***st) -> badstatus == POISON ){
            (***st) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }
        else if ( skill_target == 2 ){
          if ( (***st2) -> badstatus == POISON ){
            (***st2) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st2) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }
        else if ( skill_target == 3 ){
          if ( (***st3) -> badstatus == POISON ){
            (***st3) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st3) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }

      }
    }
    else if ( skill_user == 2 ){
      printf("%s>>キュアポ\n", (***st2) -> name);
      sleep(1);

      if ( (***st2) -> mp < 4 ){
        printf("MP不足!\n");
      }
      else{
        (***st2) -> mp -= 4;

        if ( skill_target == 1 ){
          if ( (***st) -> badstatus == POISON ){
            (***st) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }
        else if ( skill_target == 2 ){
          if ( (***st2) -> badstatus == POISON ){
            (***st2) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st2) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }
        else if ( skill_target == 3 ){
          if ( (***st3) -> badstatus == POISON ){
            (***st3) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st3) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }

      }
    }
    else if ( skill_user == 3 ){
      printf("%s>>キュアポ\n", (***st3) -> name);
      sleep(1);

      if ( (***st3) -> mp < 4 ){
        printf("MP不足!\n");
      }
      else{
        (***st3) -> mp -= 4;

        if ( skill_target == 1 ){
          if ( (***st) -> badstatus == POISON ){
            (***st) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }
        else if ( skill_target == 2 ){
          if ( (***st2) -> badstatus == POISON ){
            (***st2) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st2) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }
        else if ( skill_target == 3 ){
          if ( (***st3) -> badstatus == POISON ){
            (***st3) -> badstatus = GOOD;
            printf("%s: STATUS(POISON) >> STATUS(GOOD)\n", (***st3) -> name);
            printf("\n");
          }
          else{
            printf("無効果\n");
            printf("\n");
          }
        }

      }
    }
  }

}

int skill_target_select(Player ****st, Player ****st2, Player ****st3, int use_skill_count){
  int skill_target;
  int command;

  if ( use_skill_count == 1 ){
    do{
      printf("使用する対象を選択してください(使用しない場合はcを入力)\n");
      if ( (***st) -> badstatus == DEAD ){
        //nothing
      }
      else{
        printf("1:%s ", (***st) -> name);
      }

      if ( (***st2) -> badstatus == DEAD ){
        //nothing
      }
      else{
        printf("2:%s ", (***st2) -> name);
      }

      if ( (***st3) -> badstatus == DEAD ){
        //nothing
      }
      else{
        printf("3:%s ", (***st3) -> name);
      }
      printf("\n");

      command =  _getch();
      if ( command == '1' ){
        if ( (***st) -> badstatus == DEAD ){
          command = 'e';  //error
        }
        else{
          skill_target = 1;
        }
      }
      else if ( command == '2' ){
        if ( (***st2) -> badstatus == DEAD ){
          command = 'e';
        }
        else{
          skill_target = 2;
        }
      }
      else if ( command == '3' ){
        if ( (***st3) -> badstatus == DEAD ){
          command = 'e';
        }
        else{
          skill_target = 3;
        }
      }
      else if ( command == 'c' ){
        skill_target = 0;
      }
    }while ( command != '1' && command != '2' && command != '3' && command != 'c' );

  }

  return skill_target;
}

int battle_player_skill_list(P_skill ****player_skill){
  int skill_count;

  skill_count = 0;
  printf("<<<<<<SKILL>>>>>>\n");
  if ( (***player_skill) -> recover1 == 1 ){
    printf("1:ケディア 消費MP:3 (味方1人のHP小回復)\n");
    skill_count++;
  }
  if ( (***player_skill) -> cure_poison == 1 ){
    printf("2:キュアポ 消費MP:4 (味方1人のPOISON状態を回復)\n");
    skill_count++;
  }
  if ( (***player_skill) -> recover2 == 1 ){
    printf("3:回復:LV2 (HP中回復)\n");
    skill_count++;
  }
  if ( (***player_skill) -> recover3 == 1 ){
    printf("4:回復:LV3 (HP大回復)\n");
    skill_count++;
  }
  if ( skill_count == 0 ){
    printf("使用可能なSKILLはありません!\n");
  }
  printf("-----------------------------\n");

  return skill_count;
}

<<<<<<< HEAD
double enemy_attack_skill(Player ******st, Equip ******pEquip, Equip ******p2Equip, Equip ******p3Equip, Enemy ******enemy, int player_guard, int player_guard2, int player_guard3, int attack_skill_number){
=======
double enemy_attack_skill(Player ******st, Equip ******equip, Enemy ******enemy, int player_guard, int player_guard2, int player_guard3, int attack_skill_number){
>>>>>>> origin/main
  double attack_skill_count;
  int damage_base, damage, eva, critical, eva_count, critical_count, i, max_damage, temp;
  double eva_base, critical_base;
  int magic_power;

  //クエイク(全体攻撃)
  if ( attack_skill_number == 1 ){

    eva_count = 0;
    critical_count = 0;

    if ( (*****st) -> physical_attack == -1 ){  //物理攻撃無効
      sleep(1);
      printf("%s<<BLOCK!\n", (*****st) -> name);

      attack_skill_count = -2;
    }
    else if ( (*****st) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (*****enemy) -> lv + (*****enemy) -> atk ) * 32 ) / 15 ) / 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base;
      temp = damage;
      damage = -2;
      (*****st) -> hp += temp;
      if ( (*****st) -> hp > (*****st) -> maxhp ){
        (*****st) -> hp = (*****st) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (*****st) -> name, temp);
      attack_skill_count = -2;
    }
    else if ( (*****st) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (*****enemy) -> lv + (*****enemy) -> atk ) * 32 ) / 15 ) / 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (*****enemy) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (*****enemy) -> name, temp);
      if ( (*****enemy) -> hp <= 0 ){
        (*****enemy) -> hp = 0;
        (*****enemy) -> badstatus = DEAD;
        printf("%sは倒れた\n", (*****enemy) -> name);
      }
      attack_skill_count = -2;
    }
    else{
      damage_base = ( ( ( (*****enemy) -> lv + (*****enemy) -> atk ) * 32 ) / 15 ) / 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      eva_base = 3 + ( (*****st) -> agi * 0.2 ) + ( (*****st) -> luk * 0.1 ) - ( (*****enemy) -> agi * 0.1) - ( (*****enemy) -> luk * 0.1);   //回避率計算

      eva_base = round(eva_base);

      if ( eva_base < 3 ){
        eva_base = 3;     //回避率最小値3%
      }

      critical_base = 5 + ( (*****enemy) -> luk * 0.2) - ( (*****st) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 5 ){
        critical_base = 5;       //critical最小値5%
      }

      critical_base = round(critical_base);

      critical = (rand() % ( 100 - 1 + 1 ) + 1);   //critical率の乱数

      for ( i = 1; i <= critical_base; i++ ){
        if ( critical_base == i ){
          if ( critical >= 1 && critical <= i ){   //回避率critical_base%
            max_damage = damage_base * 1.3;   //ダメージの最大乱数はdamage_baseの1.3倍
            sleep(1);
            printf("CRITICAL!!\n");
            damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base; //(rand()%(max - min + 1)) + min;
            damage *= 2;     //criticalでダメージ2倍
            critical_count++;
            attack_skill_count = 0.1;
          }
        }
      }

      max_damage = damage_base * 1.3;
      if ( critical_count == 0 ){
        damage = (rand() % ( max_damage - damage_base + 1) ) + damage_base; //(rand()%(max - min + 1)) + min;
        //printf("damage:%d\n", damage);
        //味方の耐性判断
        if ( (*****st) -> physical_attack == 100 ){
          damage = damage;
          attack_skill_count = -1;
        }
        else if ( (*****st) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          attack_skill_count = -1;
        }
        else if ( (*****st) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          attack_skill_count = 0.1;
        }
        else if ( (*****st) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          attack_skill_count = -1;
        }
        else if ( (*****st) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          attack_skill_count = -1;
        }
        else if ( (*****st) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          attack_skill_count = -1;
        }

        if ( player_guard == 1 ){
          damage /= 1.6;
          attack_skill_count = -1;
        }
      }

      if ( damage >= (*****st) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (*****st) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (*****st) -> name);
        (*****st) -> hp = 0;
        (*****st) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (*****st) -> name, damage);
        (*****st) -> hp -= damage;
        if ( (*****st) -> hp <= 0 ){
          (*****st) -> hp = 0;
          (*****st) -> badstatus = DEAD;
        }
      }

    }
  }
  else if ( attack_skill_number == 2 ){  //エンファ
    eva_count = 0;
    magic_power = 10;

    if ( (*****st) -> fire == -1 ){  //火炎攻撃無効
      sleep(1);
      printf("%s<<BLOCK!\n", (*****st) -> name);

      attack_skill_count = -2;
    }
    else if ( (*****st) -> fire == -2 ){  //火炎攻撃吸収
      damage_base = ( magic_power * (*****enemy) -> magic ) / ( (*****st) -> magic * 3 );
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base;
      temp = damage;
      damage = -2;
      (*****st) -> hp += temp;
      if ( (*****st) -> hp > (*****st) -> maxhp ){
        (*****st) -> hp = (*****st) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (*****st) -> name, temp);
      attack_skill_count = -2;
    }
    else if ( (*****st) -> fire == -3 ){  //火炎攻撃反射
      damage_base = ( magic_power * (*****enemy) -> magic ) / ( (*****st) -> magic * 3 );
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (*****enemy) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (*****enemy) -> name, temp);
      if ( (*****enemy) -> hp <= 0 ){
        (*****enemy) -> hp = 0;
        (*****enemy) -> badstatus = DEAD;
        printf("%sは倒れた\n", (*****enemy) -> name);
      }
      attack_skill_count = -2;
    }
    else{
      damage_base = ( magic_power * (*****enemy) -> magic ) / ( (*****st) -> magic * 3 );
      //printf("damage_base:%d\n", damage_base);
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      //回避率5%
      eva_base = 5 + ( (*****st) -> agi * 0.2 ) + ( (*****st) -> luk * 0.1 ) - ( (*****enemy) -> agi * 0.1) - ( (*****enemy) -> luk * 0.1);   //回避率計算

      eva_base = round(eva_base);

      if ( eva_base < 5 ){
        eva_base = 5;     //回避率最小値5%
      }

      max_damage = damage_base * 1.3;
      damage = (rand() % ( max_damage - damage_base + 1) ) + damage_base; //(rand()%(max - min + 1)) + min;
      //printf("damage:%d\n", damage);
      //printf("damage:%d\n", damage);
      //味方の耐性判断
      if ( (*****st) -> fire == 100 ){
        damage = damage;
        attack_skill_count = -1;
      }
      else if ( (*****st) -> fire == 150 ){     //火炎攻撃1.5倍
        damage *= 1.5;
        attack_skill_count = -1;
      }
      else if ( (*****st) -> fire == 200 ){
        sleep(1);
        printf("WEAKNESS!!\n");
        damage *= 1.7;
        attack_skill_count = 0.1;
      }
      else if ( (*****st) -> fire == 80 ){  //火炎攻撃ダメージ80%
        damage *= 0.8;
        attack_skill_count = -1;
      }
      else if ( (*****st) -> fire == 50 ){  //火炎攻撃半減
        sleep(1);
        printf("RESIST!\n");
        damage *= 0.5;
        attack_skill_count = -1;
      }
      else if ( (*****st) -> fire == 25 ){  //火炎攻撃ダメージ25%
        sleep(1);
        printf("RESIST!\n");
        damage *= 0.25;
        attack_skill_count = -1;
      }

      if ( player_guard == 1 ){
        damage /= 1.6;
        attack_skill_count = -1;
      }

      if ( damage >= (*****st) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (*****st) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (*****st) -> name);
        (*****st) -> hp = 0;
        (*****st) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (*****st) -> name, damage);
        (*****st) -> hp -= damage;
        if ( (*****st) -> hp <= 0 ){
          (*****st) -> hp = 0;
          (*****st) -> badstatus = DEAD;
        }
      }

    }
  }


  return attack_skill_count;
}

int enemy_skill_target(Player ******st, Player ******st2, Player ******st3){
  int target_base;

  target_base = (rand() % ( 3 - 1 + 1 ) + 1); //スキルを使用するターゲットを決定

  if ( target_base == 1 ){
    if ( (*****st) -> badstatus == DEAD ){
      if ( (*****st2) -> badstatus == DEAD ){
        target_base = 3;
        return target_base;
      }
      if ( (*****st3) -> badstatus == DEAD ){
        target_base = 2;
        return target_base;
      }
    }
  }
  else if ( target_base == 2 ){
    if ( (*****st2) -> badstatus == DEAD ){
      if ( (*****st) -> badstatus == DEAD ){
        target_base = 3;
        return target_base;
      }
      if ( (*****st3) -> badstatus == DEAD ){
        target_base = 1;
        return target_base;
      }
    }
  }
  else if ( target_base == 3 ){
    if ( (*****st3) -> badstatus == DEAD ){
      if ( (*****st) -> badstatus == DEAD ){
        target_base = 2;
        return target_base;
      }
      if ( (*****st2) -> badstatus == DEAD ){
        target_base = 1;
        return target_base;
      }
    }
  }

  return target_base;
}

//enemyのskillに関わる関数 skill_reaction = 1ならダメージに関係するskill skill_reactionが0ならダメージに関係しないskill
<<<<<<< HEAD
double use_enemy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****pEquip, Equip *****p2Equip, Equip *****p3Equip, Enemy *****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
=======
double use_enemy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****equip, Enemy *****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
>>>>>>> origin/main
  int enemy_move, badstatus_per, badstatus_count, recover_point;
  int target_base;
  double turn_decrease;
  int attack_skill_number;
  double attack_skill_count, attack_skill_count2, attack_skill_count3;  //playerがattackskillでダメージを受けたかどうか

  badstatus_count = 0; //badstatusになったか判定 1はbadstatusになったということ

  //ゴブリン
  if ( (****enemy) -> enemy_id == 3 || (****enemy) -> enemy_id == 7 ){
    printf("%s>>クエイク\n", (****enemy) -> name);
    sleep(1);
    printf("%sは地面を大きく揺らした!\n", (****enemy) -> name);
    sleep(1);

    attack_skill_number = 1;
<<<<<<< HEAD
    attack_skill_count = enemy_attack_skill(&st, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    attack_skill_count2 = enemy_attack_skill(&st2, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    attack_skill_count3 = enemy_attack_skill(&st3, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
=======
    attack_skill_count = enemy_attack_skill(&st, &equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    attack_skill_count2 = enemy_attack_skill(&st2, &equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    attack_skill_count3 = enemy_attack_skill(&st3, &equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
>>>>>>> origin/main

    if ( attack_skill_count == -2 || attack_skill_count2 == -2 || attack_skill_count3 == -2 ){
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
    }
    else if ( attack_skill_count == 0.1 || attack_skill_count2 == 0.1 || attack_skill_count3 == 0.1 ){
      turn_decrease = 0.1;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
    }
    else{
      turn_decrease = -1;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
    }
  }
  //グール
  else if ( (****enemy) -> enemy_id == 5 ){
    target_base = enemy_skill_target(&st,&st2,&st3);

    badstatus_per = (rand() % ( 100 - 1 + 1) ) + 1; //状態異常乱数生成(1~100)
    //printf("badstatus_per:%d\n", badstatus_per);
    printf("%s>>ポイゾガ\n", (****enemy) -> name);
    if ( badstatus_per >= 1 && badstatus_per <= 35 ){
      if ( target_base == 1 ){
        if ( (****st) -> badstatus == POISON ){
          printf("%sは既にPOISONになっている\n", (****st) -> name);
        }
        else{
          (****st) -> badstatus = POISON;
          printf("%sはPOISONになった\n", (****st) -> name);
        }
      }
      else if ( target_base == 2 ){
        if ( (****st2) -> badstatus == POISON ){
          printf("%sは既にPOISONになっている\n", (****st2) -> name);
        }
        else{
          (****st2) -> badstatus = POISON;
          printf("%sはPOISONになった\n", (****st2) -> name);
        }
      }
      else if ( target_base == 3 ){
        if ( (****st3) -> badstatus == POISON ){
          printf("%sは既にPOISONになっている\n", (****st3) -> name);
        }
        else{
          (****st3) -> badstatus = POISON;
          printf("%sはPOISONになった\n", (****st3) -> name);
        }
      }
    }
    else{
      if ( target_base == 1 ){
        printf("%s<<MISS!!\n", (****st) -> name);
      }
      else if ( target_base == 2 ){
        printf("%s<<MISS!!\n", (****st2) -> name);
      }
      else if ( target_base == 3 ){
        printf("%s<<MISS!!\n", (****st3) -> name);
      }
    }

    turn_decrease = -1;
    enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
  }
  //ゾンビ
  else if ( (****enemy) -> enemy_id == 6 ){
    target_base = enemy_skill_target(&st,&st2,&st3);

    badstatus_per = (rand() % ( 100 - 1 + 1) ) + 1; //状態異常乱数生成(1~100)
    //printf("badstatus_per:%d\n", badstatus_per);
    printf("%s>>パララズ\n", (****enemy) -> name);
    if ( badstatus_per >= 1 && badstatus_per <= 35 ){
      if ( target_base == 1 ){
        if ( (****st) -> badstatus == PALYZE ){
          printf("%sは既にPALYZEになっている\n", (****st) -> name);
        }
        else{
          (****st) -> badstatus = PALYZE;
          printf("%sはPALYZEになった\n", (****st) -> name);
        }
      }
      else if ( target_base == 2 ){
        if ( (****st2) -> badstatus == PALYZE ){
          printf("%sは既にPALYZEになっている\n", (****st2) -> name);
        }
        else{
          (****st2) -> badstatus = PALYZE;
          printf("%sはPALYZEになった\n", (****st2) -> name);
        }
      }
      else if ( target_base == 3 ){
        if ( (****st3) -> badstatus == PALYZE ){
          printf("%sは既にPALYZEになっている\n", (****st3) -> name);
        }
        else{
          (****st3) -> badstatus = PALYZE;
          printf("%sはPALYZEになった\n", (****st3) -> name);
        }
      }
    }
    else{
      if ( target_base == 1 ){
        printf("%s<<MISS!!\n", (****st) -> name);
      }
      else if ( target_base == 2 ){
        printf("%s<<MISS!!\n", (****st2) -> name);
      }
      else if ( target_base == 3 ){
        printf("%s<<MISS!!\n", (****st3) -> name);
      }
    }

    turn_decrease = -1;
    enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
  }
  else if ( (****enemy) -> enemy_id == 8 ){  //オンモラキ
    target_base = enemy_skill_target(&st,&st2,&st3);
    printf("%s>>エンファ\n", (****enemy) -> name);
    sleep(1);
    printf("%sは小さな火球を飛ばした!\n", (****enemy) -> name);
    sleep(1);

    attack_skill_number = 2;

    if ( target_base == 1 ){
<<<<<<< HEAD
      attack_skill_count = enemy_attack_skill(&st, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    }
    else if ( target_base == 2 ){
      attack_skill_count2 = enemy_attack_skill(&st2, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    }
    else if ( target_base == 3 ){
      attack_skill_count3 = enemy_attack_skill(&st3, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
=======
      attack_skill_count = enemy_attack_skill(&st, &equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    }
    else if ( target_base == 2 ){
      attack_skill_count2 = enemy_attack_skill(&st2, &equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
    }
    else if ( target_base == 3 ){
      attack_skill_count3 = enemy_attack_skill(&st3, &equip, &enemy, player_guard, player_guard2, player_guard3, attack_skill_number);
>>>>>>> origin/main
    }

    if ( attack_skill_count == -2 || attack_skill_count2 == -2 || attack_skill_count3 == -2 ){
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
    }

    if ( attack_skill_count == 0.1 || attack_skill_count2 == 0.1 || attack_skill_count3 == 0.1 ){
      turn_decrease = 0.1;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
    }

    if ( attack_skill_count == -1 || attack_skill_count2 == -1 || attack_skill_count3 == -1 ){
      turn_decrease = -1;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
    }

  }
  else if ( (****enemy) -> enemy_id == 101 ){    //回復:LV1
    recover_point = (rand() % ( 20 + (****enemy) -> magic * 3 - 20 + 1) ) + 20; //回復量20 ~ 20 + (***enemy) -> magic * 3
    printf("%s>>ケディア\n", (****enemy) -> name);
    (****enemy) -> hp +=  recover_point;
    if ( (****enemy) -> hp >= (****enemy) -> maxhp ){
      (****enemy) -> hp = (****enemy) -> maxhp;
    }
    printf("%sのHPが%d回復した!\n", (****enemy) -> name, recover_point);
    turn_decrease = -1;
    enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
  }

  return enemy_turn;
}

<<<<<<< HEAD
double use_enemy_copy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****pEquip, Equip *****p2Equip, Equip *****p3Equip, Enemy **enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
=======
double use_enemy_copy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****equip, Enemy **enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
>>>>>>> origin/main
  int enemy_move, badstatus_per, badstatus_count, recover_point;
  int target_base;
  double turn_decrease;
  int magic_damage;

  badstatus_count = 0; //badstatusになったか判定

  //グールの毒スキル
  if ( (*enemy_copy1) -> enemy_id == 5 ){
    target_base = enemy_skill_target(&st,&st2,&st3);

    badstatus_per = ( rand() % ( 100 - 1 + 1) ) + 1; //状態異常乱数生成(1~100)
    //printf("badstatus_per:%d\n", badstatus_per);
    printf("%s>>ポイゾガ\n", (*enemy_copy1) -> name);
    if ( badstatus_per >= 1 && badstatus_per <= 20 ){
      if ( target_base == 1 ){
        if ( (****st) -> badstatus == POISON ){
          printf("%sは既にPOISONになっている\n", (****st) -> name);
        }
        else{
          (****st) -> badstatus = POISON;
          printf("%sはPOISONになった\n", (****st) -> name);
        }
      }
      else if ( target_base == 2 ){
        if ( (****st2) -> badstatus == POISON ){
          printf("%sは既にPOISONになっている\n", (****st2) -> name);
        }
        else{
          (****st2) -> badstatus = POISON;
          printf("%sはPOISONになった\n", (****st2) -> name);
        }
      }
      else if ( target_base == 3 ){
        if ( (****st3) -> badstatus == POISON ){
          printf("%sは既にPOISONになっている\n", (****st3) -> name);
        }
        else{
          (****st3) -> badstatus = POISON;
          printf("%sはPOISONになった\n", (****st3) -> name);
        }
      }
    }
    else{
      if ( target_base == 1 ){
        printf("%s<<MISS!!\n", (****st) -> name);
      }
      else if ( target_base == 2 ){
        printf("%s<<MISS!!\n", (****st2) -> name);
      }
      else if ( target_base == 3 ){
        printf("%s<<MISS!!\n", (****st3) -> name);
      }
    }

    turn_decrease = -1;
    enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
  }
  else if ( (*enemy_copy1) -> enemy_id == 6 ){
    target_base = enemy_skill_target(&st,&st2,&st3);

    badstatus_per = (rand() % ( 100 - 1 + 1) ) + 1; //状態異常乱数生成(1~100)
    //printf("badstatus_per:%d\n", badstatus_per);
    printf("%s>>パララズ\n", (*enemy_copy1) -> name);
    if ( badstatus_per >= 1 && badstatus_per <= 35 ){
      if ( target_base == 1 ){
        if ( (****st) -> badstatus == PALYZE ){
          printf("%sは既にPALYZEになっている\n", (****st) -> name);
        }
        else{
          (****st) -> badstatus = PALYZE;
          printf("%sはPALYZEになった\n", (****st) -> name);
        }
      }
      else if ( target_base == 2 ){
        if ( (****st2) -> badstatus == PALYZE ){
          printf("%sは既にPALYZEになっている\n", (****st2) -> name);
        }
        else{
          (****st2) -> badstatus = PALYZE;
          printf("%sはPALYZEになった\n", (****st2) -> name);
        }
      }
      else if ( target_base == 3 ){
        if ( (****st3) -> badstatus == PALYZE ){
          printf("%sは既にPALYZEになっている\n", (****st3) -> name);
        }
        else{
          (****st3) -> badstatus = PALYZE;
          printf("%sはPALYZEになった\n", (****st3) -> name);
        }
      }
    }
    else{
      if ( target_base == 1 ){
        printf("%s<<MISS!!\n", (****st) -> name);
      }
      else if ( target_base == 2 ){
        printf("%s<<MISS!!\n", (****st2) -> name);
      }
      else if ( target_base == 3 ){
        printf("%s<<MISS!!\n", (****st3) -> name);
      }
    }

    turn_decrease = -1;
    enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
  }
  else if ( (*enemy_copy1) -> enemy_id == 7 ){
    target_base = enemy_skill_target(&st,&st2,&st3);
  }
  else if ( (*enemy_copy1) -> enemy_id == 101 ){    //回復:LV1
    recover_point = (rand() % (20 + (*enemy_copy1) -> magic * 3 - 20 + 1) ) + 20; //回復量20 ~ 20 + (***enemy) -> magic * 3
    printf("%s:SKILL>>ケディア\n", (*enemy_copy1) -> name);
    (*enemy_copy1) -> hp +=  recover_point;
    if ( (*enemy_copy1) -> hp >= (*enemy_copy1) -> maxhp ){
      (*enemy_copy1) -> hp = (*enemy_copy1) -> maxhp;
    }
    printf("%sのHPが%d回復した!\n", (*enemy_copy1) -> name, recover_point);
    turn_decrease = -1;
    enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
  }

  return enemy_turn;
}

<<<<<<< HEAD
double enemy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****pEquip, Equip ****p2Equip, Equip ****p3Equip, Enemy ****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
=======
double enemy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****equip, Enemy ****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
>>>>>>> origin/main
  int enemy_move;

  if ( (***enemy) -> enemy_id == 3 || (***enemy) -> enemy_id == 7 ){  //bossゴブリン
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1;
    if ( enemy_move >= 1 && enemy_move <= 50 ){
<<<<<<< HEAD
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);
=======
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_attack(&st,&st2,&st3,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);
    }
  }
  //グール
  else if ( (***enemy) -> enemy_id == 5 ){
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 40 ){  //毒攻撃を使用する行動
<<<<<<< HEAD
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_attack(&st, &st2, &st3, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else if ( (***enemy) -> enemy_id == 6 ){  //ゾンビ
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 35 ){  //麻痺攻撃を使用する行動
<<<<<<< HEAD
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_attack(&st, &st2, &st3, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else if ( (***enemy) -> enemy_id == 8 ){
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 40 ){  //火炎攻撃を使用する行動
<<<<<<< HEAD
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
      enemy_turn = use_enemy_skill(&st,&st2,&st3,&equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_attack(&st, &st2, &st3, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else if ( (***enemy) -> enemy_id == 101 ){    //skill(回復:LV1)を持つ敵の攻撃パターン
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 45 ){  //回復:LV1を使用する行動
      if ( (***enemy) -> hp <= (***enemy) -> maxhp * 0.6 ){
<<<<<<< HEAD
        enemy_turn = use_enemy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
        enemy_turn = use_enemy_skill(&st,&st2,&st3,&equip,&enemy,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
      }
    }
    else{
      enemy_turn = enemy_attack(&st, &st2, &st3, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else{
    enemy_turn = enemy_attack(&st, &st2, &st3, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
  }

  if ( enemy_turn < 0 ){
    enemy_turn = 0;
  }

  return enemy_turn;
}

<<<<<<< HEAD
double enemy_copy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****pEquip, Equip ****p2Equip, Equip ****p3Equip, Enemy *enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
=======
double enemy_copy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****equip, Enemy *enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
>>>>>>> origin/main
  int enemy_move;

  if ( enemy_copy1 -> enemy_id == 5 ){    //skill(POISON)を持つ敵の攻撃パターン
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 35 ){  //毒攻撃を使用する行動
<<<<<<< HEAD
      enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
      enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_copy_attack(&st, &st2, &st3, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else if ( enemy_copy1 -> enemy_id == 6 ){
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 30 ){  //毒攻撃を使用する行動
<<<<<<< HEAD
      enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
      enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_copy_attack(&st, &st2, &st3, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else if ( enemy_copy1 -> enemy_id == 7 ){
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 45 ){  //毒攻撃を使用する行動
<<<<<<< HEAD
      enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
      enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
    }
    else{
      enemy_turn = enemy_copy_attack(&st, &st2, &st3, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else if ( enemy_copy1 -> enemy_id == 101 ){    //skill(回復:LV1)を持つ敵の攻撃パターン
    enemy_move = (rand() % ( 100 - 1 + 1) ) + 1; //敵の攻撃パターン生成(1~100)
    //printf("%d\n", enemy_move);
    if ( enemy_move >= 1 && enemy_move <= 45 ){  //回復:LV1を使用する行動
      if ( enemy_copy1 -> hp <= enemy_copy1 -> maxhp * 0.6 ){
<<<<<<< HEAD
        enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
=======
        enemy_turn = use_enemy_copy_skill(&st,&st2,&st3,&equip,&enemy_copy1,player_guard,player_guard2,player_guard3,enemy_turn);  //skillがダメージを与えるskillならば１ そうでなければ0
>>>>>>> origin/main
      }
    }
    else{
      enemy_turn = enemy_copy_attack(&st, &st2, &st3, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
    }
  }
  else{
    enemy_turn = enemy_copy_attack(&st, &st2, &st3, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
  }

  if ( enemy_turn < 0 ){
    enemy_turn = 0;
  }

  return enemy_turn;
}
