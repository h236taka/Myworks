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

int player_attack(Player ****st, Enemy ****enemy, int *enemy_deadcount){
  int damage_base, damage, i, eva, critical, eva_count, critical_count, max_damage, temp;
  double eva_base, critical_base;

  eva_count = 0;
  critical_count = 0;
  damage_base =( ( ( (***st) -> lv + (***st) -> atk ) * 32 ) / 15 ) - (***enemy) -> str;
  if ( damage_base < 0 ){
    damage_base = 0;
    return -10;
  }
  eva_base = 3 + ( (***enemy) -> agi * 0.1 ) + ( (***enemy) -> luk * 0.1 ) - ( (***st) -> agi * 0.2) - ( (***st) -> luk * 0.1);   //回避率計算

  //麻痺状態では攻撃の命中率が下がる
  if ( (***st) -> badstatus == PALYZE ){
    eva_base += 50;
    if ( eva_base > 100 ){
      eva_base = 100;
    }
  }

  //printf("before eva_base = %f\n", eva_base);
  eva_base = round(eva_base);
  //printf("after eva_base = %f\n", eva_base);

  if ( eva_base < 3 ){
    eva_base = 3;     //回避率最小値3%
  }

  eva = (rand() % ( 100 - 1 + 1 ) + 1);  //回避率の乱数
  //printf("eva number = %d\n", eva);

  for ( i = 3; i <= eva_base; i++ ){
    if ( eva_base == i ){
      if ( eva >= 1 && eva <= i ){   //回避率eva_base%
        damage = 0;
        eva_count++;
      }
    }
  }

  if ( eva_count == 0 ){
    critical_base = 1 + ( (***st) -> luk * 0.2 ) + ( (***st) -> agi * 0.2 )- ( (***enemy) -> luk * 0.1 );  //critical率の計算
    if ( critical_base < 1 ){
      critical_base = 1;       //critical最小値1%
    }
    //printf("before critical_base = %f\n", critical_base);
    critical_base = round(critical_base);
    //printf("after critical_base = %f\n", critical_base);

    critical = (rand() % ( 100 - 1 + 1 ) + 1);   //critical率の乱数
    //printf("critical number = %d\n", critical);

    //critical_base = 100;
    for ( i = 1; i <= critical_base; i++ ){
      if ( critical_base == i ){
        if ( critical >= 1 && critical <= i ){   //回避率critical_base%
          max_damage = damage_base * 1.5;   //ダメージの最大乱数はdamage_baseの1.5倍
          damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base; //(rand()%(max - min + 1)) + min;
          damage *= 2;     //criticalでダメージ2倍
          damage += 100000;
          critical_count++;
        }
      }
    }

    max_damage = damage_base * 1.3;

    if ( critical_count == 0 ){
      damage = (rand() % ( max_damage - damage_base + 1) ) + damage_base; //(rand()%(max - min + 1)) + min;
      //敵の耐性判断
      if ( (***enemy) -> physical_attack == 150 ){     //物理攻撃1.5倍
        damage *= 1.5;
      }
      else if ( (***enemy) -> physical_attack == 200 ){
        printf("%sの通常攻撃!\n", (***st) -> name);
        sleep(1);
        printf("WEAKNESS!!\n");
        damage *= 2;
      }
      else if ( (***enemy) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
        damage *= 0.8;
      }
      else if ( (***enemy) -> physical_attack == 50 ){  //物理攻撃半減
        printf("%sの通常攻撃!\n", (***st) -> name);
        sleep(1);
        printf("RESIST!\n");
        damage *= 0.5;
      }
      else if ( (***enemy) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
        printf("%sの通常攻撃!\n", (***st) -> name);
        sleep(1);
        printf("RESIST!\n");
        damage *= 0.25;
      }
      else if ( (***enemy) -> physical_attack == -1 ){   //物理攻撃無効
        damage = -1;
      }
      else if ( (***enemy) -> physical_attack == -2 ){   //物理攻撃吸収
        temp = damage;
        damage = -2;
        (***enemy) -> hp += temp;
        if ( (***enemy) -> hp > (***enemy) -> maxhp ){
          (***enemy) -> hp = (***enemy) -> maxhp;
        }
        printf("%sの通常攻撃!\n", (***st) -> name);
        sleep(1);
        printf("Absorb!\n");
        printf("%s:%dダメージ吸収\n", (***enemy) -> name, temp);
      }
      else if ( (***enemy) -> physical_attack == -3 ){   //物理攻撃反射
        temp = damage;
        damage = -3;
        (***st) -> hp -= temp;
        printf("%sの通常攻撃!\n", (***st) -> name);
        sleep(1);
        printf("Reflect!\n");
        printf("%sは%dダメージを受けた\n", (***st) -> name, temp);
        if ( (***st) -> hp <= 0 ){
          (***st) -> hp = 0;
          (***st) -> badstatus = DEAD;
          sleep(1);
          printf("%sは死んでしまった\n", (***st) -> name);
        }
      }

    }
  }

  return damage;
}

double calculate_enemy_turn(double enemy_turn, double turn_decrease){

  if ( turn_decrease == -1 ){  //ターンを1消費
    if ( enemy_turn == 4 || enemy_turn == 3 || enemy_turn == 2 || enemy_turn == 1 ){
      enemy_turn += turn_decrease;
    }
    else if ( enemy_turn == 4.4 ){
      enemy_turn = 3.3;
    }
    else if ( enemy_turn == 4.3 ){
      enemy_turn = 3.2;
    }
    else if ( enemy_turn == 4.2 ){
      enemy_turn = 3.1;
    }
    else if ( enemy_turn == 4.1 ){
      enemy_turn = 3.0;
    }
    else if ( enemy_turn == 3.3 ){
      enemy_turn = 2.2;
    }
    else if ( enemy_turn == 3.2 ){
      enemy_turn = 2.1;
    }
    else if ( enemy_turn == 3.1 ){
      enemy_turn = 2.0;
    }
    else if ( enemy_turn == 2.2 ){
      enemy_turn = 1.1;
    }
    else if ( enemy_turn == 2.1 ){
      enemy_turn = 1.0;
    }
    else if ( enemy_turn == 1.1 ){
      enemy_turn = 0.0;
    }
  }
  else if ( turn_decrease == -2 ){
    if ( enemy_turn == 4 || enemy_turn == 3 || enemy_turn == 2 || enemy_turn == 1 ){
      enemy_turn += turn_decrease;
    }
    else if ( enemy_turn == 4.4 ){
      enemy_turn = 2.2;
    }
    else if ( enemy_turn == 4.3 ){
      enemy_turn = 2.1;
    }
    else if ( enemy_turn == 4.2 ){
      enemy_turn = 2.0;
    }
    else if ( enemy_turn == 4.1 ){
      enemy_turn = 2.0;
    }
    else if ( enemy_turn == 3.3 ){
      enemy_turn = 1.1;
    }
    else if ( enemy_turn == 3.2 ){
      enemy_turn = 1.0;
    }
    else if ( enemy_turn == 3.1 ){
      enemy_turn == 1.0;
    }
    else if ( enemy_turn == 2.2 || enemy_turn == 2.1 || enemy_turn == 1.1 ){
      enemy_turn = 0.0;
    }
  }
  //turn増加
  else if ( turn_decrease == 0.1 ){
    if ( enemy_turn == 4 || enemy_turn == 3 || enemy_turn == 2 || enemy_turn == 1 ){
      //printf("here\n");
      enemy_turn += turn_decrease;
      //printf("enemy_turn:%f\n", enemy_turn);
    }
    else if ( enemy_turn == 4.4 ){
      enemy_turn = 3.3;
    }
    else if ( enemy_turn == 4.3 || enemy_turn == 4.2 || enemy_turn == 4.1 ){
      enemy_turn += turn_decrease;
    }
    else if ( enemy_turn == 3.3 ){
      enemy_turn = 3.2;
    }
    else if ( enemy_turn == 3.2 || enemy_turn == 3.1 ){
      enemy_turn += turn_decrease;
    }
    else if ( enemy_turn == 2.2 ){
      enemy_turn = 1.1;
    }
    else if ( enemy_turn == 2.1 ){
      enemy_turn += turn_decrease;
    }
    else if ( enemy_turn == 1.1 ){
      enemy_turn = 0.0;
    }

  }

  return enemy_turn;
}

double enemy_attack(Player *****st, Player *****st2, Player *****st3, Enemy *****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
  int damage_base, damage, eva, critical, eva_count, critical_count, i, max_damage;
  int temp, target_base, target;
  double eva_base, critical_base, turn_decrease;

  eva_count = 0;
  critical_count = 0;
  //damage_base = ( (****enemy) -> atk + (****enemy) -> lv ) * 5 - ( (****st) -> str + (****st) -> lv ) * 2;
  printf("%sの攻撃!\n", (****enemy) -> name);
  sleep(1);
  //eva_base = 3 + ( (****st) -> agi * 0.2 ) + ( (****st) -> luk * 0.1 ) - ( (****enemy) -> agi * 0.1) - ( (****enemy) -> luk * 0.1);   //回避率計算

  //攻撃する味方を選択
  target_base = (rand() % ( 3 - 1 + 1 ) + 1); //各メンバーへの攻撃確率は33%
  if ( target_base == 1 && (****st) -> badstatus == DEAD ){  //targetが死亡していたときtarget変更
    if ( (****st2) -> badstatus == DEAD ){
      target_base = 3;
    }
    else{
      target_base = 2;
    }
  }
  if ( target_base == 2 && (****st2) -> badstatus == DEAD ){
    if ( (****st3) -> badstatus == DEAD ){
      target_base = 1;
    }
    else{
      target_base = 3;
    }
  }
  if ( target_base == 3 && (****st3) -> badstatus == DEAD ){
    if ( (****st) -> badstatus == DEAD ){
      target_base = 2;
    }
    else{
      target_base = 1;
    }
  }
  if ( target_base == 1 ){  //主人公
    if ( (****st) -> physical_attack == -1 ){  //物理攻撃無効
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base;
      temp = damage;
      damage = -2;
      (****st) -> hp += temp;
      if ( (****st) -> hp > (****st) -> maxhp ){
        (****st) -> hp = (****st) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (****st) -> name, temp);
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (****enemy) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (****enemy) -> name, temp);
      if ( (****enemy) -> hp <= 0 ){
        (****enemy) -> hp = 0;
        (****enemy) -> badstatus = DEAD;
        printf("%sは倒れた\n", (****enemy) -> name);
      }
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else{
      target = 1;   //主人公
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      eva_base = 3 + ( (****st) -> agi * 0.2 ) + ( (****st) -> luk * 0.1 ) - ( (****enemy) -> agi * 0.1) - ( (****enemy) -> luk * 0.1);   //回避率計算
    }
  }
  else if ( target_base == 2 ){   //2人目のメンバー
    if ( (****st2) -> physical_attack == -1 ){  //物理攻撃無効
      damage = -1;
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st2) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st2) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -2;
      (****st2) -> hp += temp;
      if ( (****st2) -> hp > (****st2) -> maxhp ){
        (****st2) -> hp = (****st2) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (****st2) -> name, temp);
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st2) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st2) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (****enemy) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (****enemy) -> name, temp);
      if ( (****enemy) -> hp <= 0 ){
        (****enemy) -> hp = 0;
        (****enemy) -> badstatus = DEAD;
        printf("%sは倒れた\n", (****enemy) -> name);
      }
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else{
      target = 2;
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st2) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      eva_base = 3 + ( (****st2) -> agi * 0.2 ) + ( (****st2) -> luk * 0.1 ) - ( (****enemy) -> agi * 0.1) - ( (****enemy) -> luk * 0.1);   //回避率計算
    }
  }
  else if ( target_base == 3 ){   //３人目のメンバー
    if ( (****st3) -> physical_attack == -1 ){  //物理攻撃無効
      damage = -1;
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st3) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st3) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -2;
      (****st) -> hp += temp;
      if ( (****st3) -> hp > (****st3) -> maxhp ){
        (****st3) -> hp = (****st3) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (****st3) -> name, temp);
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st3) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st3) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (****enemy) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (****enemy) -> name, temp);
      if ( (****enemy) -> hp <= 0 ){
        (****enemy) -> hp = 0;
        (****enemy) -> badstatus = DEAD;
        printf("%sは倒れた\n", (****enemy) -> name);
      }
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else{
      target = 3;
      damage_base = ( ( ( (****enemy) -> lv + (****enemy) -> atk ) * 32 ) / 15 ) - (****st3) -> str * 2;
      if ( damage_base < 0 ){
        damage_base = 1;
      }
      eva_base = 3 + ( (****st3) -> agi * 0.2 ) + ( (****st3) -> luk * 0.1 ) - ( (****enemy) -> agi * 0.1) - ( (****enemy) -> luk * 0.1);   //回避率計算
    }
  }

  //printf("target:%d\n", target);

  //printf("before eva_base = %f\n", eva_base);
  eva_base = round(eva_base);
  //printf("after eva_base = %f\n", eva_base);

  if ( eva_base < 3 ){
    eva_base = 3;     //回避率最小値3%
  }

  eva = (rand() % ( 100 - 1 + 1 ) + 1);  //回避率の乱数
  //printf("eva number = %d\n", eva);
  for ( i = 3; i <= eva_base; i++ ){
    if ( eva_base == i ){
      if ( eva >= 1 && eva <= i ){   //回避率eva_base%
        damage = 0;
        printf("MISS!\n");
        turn_decrease = -2;
        enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        eva_count++;
      }
    }
  }

  if ( eva_count == 0 ){
    if ( target == 1 ){
      critical_base = 1 + ( (****enemy) -> luk * 0.2) - ( (****st) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 1 ){
        critical_base = 1;       //critical最小値1%
      }
    }
    else if ( target == 2 ){
      critical_base = 1 + ( (****enemy) -> luk * 0.2) - ( (****st2) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 1 ){
        critical_base = 1;       //critical最小値1%
      }
    }
    else if ( target == 3 ){
      critical_base = 1 + ( (****enemy) -> luk * 0.2) - ( (****st3) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 1 ){
        critical_base = 1;       //critical最小値1%
      }
    }
    //printf("before critical_base = %f\n", critical_base);
    critical_base = round(critical_base);
    //printf("after critical_base = %f\n", critical_base);

    critical = (rand() % ( 100 - 1 + 1 ) + 1);   //critical率の乱数
    //printf("critical number = %d\n", critical);

    for ( i = 1; i <= critical_base; i++ ){
      if ( critical_base == i ){
        if ( critical >= 1 && critical <= i ){   //回避率critical_base%
          max_damage = damage_base * 1.3;   //ダメージの最大乱数はdamage_baseの1.3倍
          sleep(1);
          printf("CRITICAL!!\n");
          damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base; //(rand()%(max - min + 1)) + min;
          damage *= 2;     //criticalでダメージ2倍
          critical_count++;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
    }

    max_damage = damage_base * 1.3;
    if ( critical_count == 0 ){
      damage = (rand() % ( max_damage - damage_base + 1) ) + damage_base; //(rand()%(max - min + 1)) + min;
      //味方の耐性判断
      if ( target == 1 ){
        if ( (****st) -> physical_attack == 100 ){
          damage = damage;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

        if ( player_guard == 1 ){
          damage /= 1.6;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
      else if ( target == 2 ){
        if ( (****st2) -> physical_attack == 100 ){
          damage = damage;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

        if ( player_guard2 == 1 ){
          damage /= 1.6;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
      else if ( target == 3 ){
        if ( (****st3) -> physical_attack == 100 ){
          damage = damage;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

        if ( player_guard3 == 1 ){
          damage /= 1.6;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
    }

    if ( target == 1 ){
      if ( damage >= (****st) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (****st) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (****st) -> name);
        (****st) -> hp = 0;
        (****st) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (****st) -> name, damage);
        (****st) -> hp -= damage;
        if ( (****st) -> hp <= 0 ){
          (****st) -> hp = 0;
          (****st) -> badstatus = DEAD;
        }
      }
    }
    else if ( target == 2 ){
      if ( damage >= (****st2) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (****st2) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (****st2) -> name);
        (****st2) -> hp = 0;
        (****st2) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (****st2) -> name, damage);
        (****st2) -> hp -= damage;
        if ( (****st2) -> hp <= 0 ){
          (****st2) -> hp = 0;
          (****st2) -> badstatus = DEAD;
        }
      }
    }
    else{
      if ( damage >= (****st2) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (****st3) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (****st3) -> name);
        (****st3) -> hp = 0;
        (****st3) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (****st3) -> name, damage);
        (****st3) -> hp -= damage;
        if ( (****st3) -> hp <= 0 ){
          (****st3) -> hp = 0;
          (****st3) -> badstatus = DEAD;
        }
      }
    }
  }

  player_guard = 0;
  player_guard2 = 0;
  player_guard3 = 0;

  //printf("enemy_attack's enemy_turn:%f\n", enemy_turn);

  return enemy_turn;
}

double enemy_copy_attack(Player *****st, Player *****st2, Player *****st3, Enemy **enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn){
  int damage_base, damage, eva, critical, eva_count, critical_count, i, max_damage;
  int temp, target_base, target;
  double eva_base, critical_base, turn_decrease;

  eva_count = 0;
  critical_count = 0;
  //damage_base = ( (****enemy) -> atk + (****enemy) -> lv ) * 5 - ( (****st) -> str + (****st) -> lv ) * 2;
  printf("%sの攻撃!\n", (*enemy_copy1) -> name);
  sleep(1);
  //eva_base = 3 + ( (****st) -> agi * 0.2 ) + ( (****st) -> luk * 0.1 ) - ( (****enemy) -> agi * 0.1) - ( (****enemy) -> luk * 0.1);   //回避率計算

  //攻撃する味方を選択
  target_base = (rand() % ( 3 - 1 + 1 ) + 1); //各メンバーへの攻撃確率は33%
  if ( target_base == 1 ){  //主人公
    if ( (****st) -> physical_attack == -1 ){  //物理攻撃無効
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st) -> str * 2;
      max_damage = damage_base * 1.3;
      damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base;
      temp = damage;
      damage = -2;
      (****st) -> hp += temp;
      if ( (****st) -> hp > (****st) -> maxhp ){
        (****st) -> hp = (****st) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (****st) -> name, temp);
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st) -> str * 2;
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (*enemy_copy1) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (*enemy_copy1) -> name, temp);
      if ( (*enemy_copy1) -> hp <= 0 ){
        (*enemy_copy1) -> hp = 0;
        (*enemy_copy1) -> badstatus = DEAD;
        printf("%sは倒れた\n", (*enemy_copy1) -> name);
      }
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else{
      target = 1;   //主人公
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st) -> str * 2;
      eva_base = 3 + ( (****st) -> agi * 0.2 ) + ( (****st) -> luk * 0.1 ) - ( (*enemy_copy1) -> agi * 0.1) - ( (*enemy_copy1) -> luk * 0.1);   //回避率計算
    }
  }
  else if ( target_base == 2 ){   //2人目のメンバー
    if ( (****st2) -> physical_attack == -1 ){  //物理攻撃無効
      damage = -1;
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st2) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st2) -> str * 2;
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -2;
      (****st2) -> hp += temp;
      if ( (****st2) -> hp > (****st2) -> maxhp ){
        (****st2) -> hp = (****st2) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (****st2) -> name, temp);
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st2) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st2) -> str * 2;
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (*enemy_copy1) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (*enemy_copy1) -> name, temp);
      if ( (*enemy_copy1) -> hp <= 0 ){
        (*enemy_copy1) -> hp = 0;
        (*enemy_copy1) -> badstatus = DEAD;
        printf("%sは倒れた\n", (*enemy_copy1) -> name);
      }
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else{
      target = 2;
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st2) -> str * 2;
      eva_base = 3 + ( (****st2) -> agi * 0.2 ) + ( (****st2) -> luk * 0.1 ) - ( (*enemy_copy1) -> agi * 0.1) - ( (*enemy_copy1) -> luk * 0.1);   //回避率計算
    }
  }
  else if ( target_base == 3 ){   //３人目のメンバー
    if ( (****st3) -> physical_attack == -1 ){  //物理攻撃無効
      damage = -1;
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st3) -> physical_attack == -2 ){  //物理攻撃吸収
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st3) -> str * 2;
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -2;
      (****st) -> hp += temp;
      if ( (****st3) -> hp > (****st3) -> maxhp ){
        (****st3) -> hp = (****st3) -> maxhp;
      }
      printf("Absorb!\n");
      sleep(1);
      printf("%s<<%dダメージ吸収\n", (****st3) -> name, temp);
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else if ( (****st3) -> physical_attack == -3 ){  //物理攻撃反射
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st3) -> str * 2;
      max_damage = damage_base * 1.3;
      temp = damage;
      damage = -3;
      (*enemy_copy1) -> hp -= temp;
      printf("Reflect!\n");
      sleep(1);
      printf("%s<<%dダメージ\n", (*enemy_copy1) -> name, temp);
      if ( (*enemy_copy1) -> hp <= 0 ){
        (*enemy_copy1) -> hp = 0;
        (*enemy_copy1) -> badstatus = DEAD;
        printf("%sは倒れた\n", (*enemy_copy1) -> name);
      }
      turn_decrease = -2;
      enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
      return enemy_turn;
    }
    else{
      target = 3;
      damage_base = ( ( ( (*enemy_copy1) -> lv + (*enemy_copy1) -> atk ) * 32 ) / 15 ) - (****st3) -> str * 2;
      eva_base = 3 + ( (****st3) -> agi * 0.2 ) + ( (****st3) -> luk * 0.1 ) - ( (*enemy_copy1) -> agi * 0.1) - ( (*enemy_copy1) -> luk * 0.1);   //回避率計算
    }
  }

  //printf("target:%d\n", target);

  //printf("before eva_base = %f\n", eva_base);
  eva_base = round(eva_base);
  //printf("after eva_base = %f\n", eva_base);

  if ( eva_base < 3 ){
    eva_base = 3;     //回避率最小値3%
  }

  eva = (rand() % ( 100 - 1 + 1 ) + 1);  //回避率の乱数
  //printf("eva number = %d\n", eva);

  for ( i = 3; i <= eva_base; i++ ){
    if ( eva_base == i ){
      if ( eva >= 1 && eva <= i ){   //回避率eva_base%
        damage = 0;
        printf("MISS!\n");
        eva_count++;
        turn_decrease = -2;
        enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        return enemy_turn;
      }
    }
  }

  if ( eva_count == 0 ){
    if ( target == 1 ){
      critical_base = 1 + ( (*enemy_copy1) -> luk * 0.2) - ( (****st) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 1 ){
        critical_base = 1;       //critical最小値1%
      }
    }
    else if ( target == 2 ){
      critical_base = 1 + ( (*enemy_copy1) -> luk * 0.2) - ( (****st2) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 1 ){
        critical_base = 1;       //critical最小値1%
      }
    }
    else if ( target == 3 ){
      critical_base = 1 + ( (*enemy_copy1) -> luk * 0.2) - ( (****st3) -> luk * 0.1);  //critical率の計算
      if ( critical_base < 1 ){
        critical_base = 1;       //critical最小値1%
      }
    }
    //printf("before critical_base = %f\n", critical_base);
    critical_base = round(critical_base);
    //printf("after critical_base = %f\n", critical_base);

    critical = (rand() % ( 100 - 1 + 1 ) + 1);   //critical率の乱数
    //printf("critical number = %d\n", critical);

    for ( i = 1; i <= critical_base; i++ ){
      if ( critical_base == i ){
        if ( critical >= 1 && critical <= i ){   //回避率critical_base%
          max_damage = damage_base * 1.3;   //ダメージの最大乱数はdamage_baseの1.3倍
          sleep(1);
          printf("CRITICAL!!\n");
          damage = (rand() % ( max_damage - damage_base + 1 )) + damage_base; //(rand()%(max - min + 1)) + min;
          damage *= 2;     //criticalでダメージ2倍
          critical_count++;

          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
    }

    max_damage = damage_base * 1.3;
    if ( critical_count == 0 ){
      damage = (rand() % ( max_damage - damage_base + 1) ) + damage_base; //(rand()%(max - min + 1)) + min;
      //味方の耐性判断
      if ( target == 1 ){
        if ( (****st) -> physical_attack == 100 ){
          damage = damage;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

        if ( player_guard == 1 ){
          damage /= 1.6;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
      else if ( target == 2 ){
        if ( (****st2) -> physical_attack == 100 ){
          damage = damage;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st2) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

        if ( player_guard2 == 1 ){
          damage /= 1.6;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

      }
      else if ( target == 3 ){
        if ( (****st3) -> physical_attack == 100 ){
          damage = damage;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 150 ){     //物理攻撃1.5倍
          damage *= 1.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 200 ){
          sleep(1);
          printf("WEAKNESS!!\n");
          damage *= 2;
          turn_decrease = 0.1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 80 ){  //物理攻撃ダメージ80%
          damage *= 0.8;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 50 ){  //物理攻撃半減
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.5;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
        else if ( (****st3) -> physical_attack == 25 ){  //物理攻撃ダメージ25%
          sleep(1);
          printf("RESIST!\n");
          damage *= 0.25;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }

        if ( player_guard3 == 1 ){
          damage /= 1.6;
          turn_decrease = -1;
          enemy_turn = calculate_enemy_turn(enemy_turn, turn_decrease);
        }
      }
    }

    if ( target == 1 ){
      if ( damage >= (****st) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (****st) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (****st) -> name);
        (****st) -> hp = 0;
        (****st) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (****st) -> name, damage);
        (****st) -> hp -= damage;
        if ( (****st) -> hp <= 0 ){
          (****st) -> hp = 0;
          (****st) -> badstatus = DEAD;
        }
      }
    }
    else if ( target == 2 ){
      if ( damage >= (****st2) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (****st2) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (****st2) -> name);
        (****st2) -> hp = 0;
        (****st2) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (****st2) -> name, damage);
        (****st2) -> hp -= damage;
        if ( (****st2) -> hp <= 0 ){
          (****st2) -> hp = 0;
          (****st2) -> badstatus = DEAD;
        }
      }
    }
    else{
      if ( damage >= (****st2) -> hp ){
        sleep(1);
        printf("%s<<%dダメージ\n", (****st3) -> name, damage);
        sleep(1);
        printf("%sは死んでしまった!\n", (****st3) -> name);
        (****st3) -> hp = 0;
        (****st3) -> badstatus = DEAD;
      }
      else{
        printf("%s<<%dダメージ\n", (****st3) -> name, damage);
        (****st3) -> hp -= damage;
        if ( (****st3) -> hp <= 0 ){
          (****st3) -> hp = 0;
          (****st3) -> badstatus = DEAD;
        }
      }
    }
  }

  player_guard = 0;
  player_guard2 = 0;
  player_guard3 = 0;

  return enemy_turn;
}

void display_gameover(void){

  sleep(1);
  printf("・・・・・・\n");
  sleep(2);
  printf("あなた達には失望しましたよ\n");
  sleep(2);
  printf("やはり人間には荷が重すぎましたか・・・\n");
  printf("\n");
  sleep(1);
  printf("\a");
  printf("---------------\n");
  printf("---GAME OVER---\n");
  printf("---------------\n");

  exit(EXIT_SUCCESS);
}

void poison_effect(Player ****st){
  int poison_damage;

  poison_damage = (***st) -> maxhp * 0.15;
  (***st) -> hp -= poison_damage;
  if ( (***st) -> hp <= 0 ){
    printf("%sは毒により%dダメージを受けた!\n", (***st) -> name, poison_damage);
    printf("%sは死んでしまった!\n");
    (***st) -> badstatus = DEAD;
  }
  else{
    printf("%sは毒により%dダメージを受けた!\n", (***st) -> name, poison_damage);
  }
}


void enemy_data_copy(Enemy ****enemy, Enemy *enemy_copy){

  strcpy(enemy_copy -> name, (***enemy) -> name);
  enemy_copy -> hp = (***enemy) -> hp;
  enemy_copy -> maxhp = (***enemy) -> maxhp;
  enemy_copy -> mp = (***enemy) -> maxmp;
  enemy_copy -> maxmp = (***enemy) -> maxmp;
  enemy_copy -> atk = (***enemy) -> atk;
  enemy_copy -> magic = (***enemy) -> magic;
  enemy_copy -> str = (***enemy) -> str;
  enemy_copy -> agi = (***enemy) -> agi;
  enemy_copy -> luk = (***enemy) -> luk;
  enemy_copy -> lv = (***enemy) -> lv;
  enemy_copy -> exp = (***enemy) -> exp;
  enemy_copy -> gold = (***enemy) -> gold;
  enemy_copy -> badstatus = (***enemy) -> badstatus;
  enemy_copy -> physical_attack = (***enemy) -> physical_attack;
  enemy_copy -> gun_attack = (***enemy) -> gun_attack;
  enemy_copy -> fire = (***enemy) -> fire;
  enemy_copy -> ice = (***enemy) -> ice;
  enemy_copy -> elec = (***enemy) -> elec;
  enemy_copy -> wave = (***enemy) -> wave;
  enemy_copy -> almighty = (***enemy) -> almighty;
  enemy_copy -> death = (***enemy) -> death;
  enemy_copy -> expel = (***enemy) -> expel;
  enemy_copy -> poison = (***enemy) -> poison;
  enemy_copy -> palyze = (***enemy) -> palyze;
  enemy_copy -> charm = (***enemy) -> charm;
  enemy_copy -> close = (***enemy) -> close;
  enemy_copy -> stone = (***enemy) -> stone;
  enemy_copy -> panic = (***enemy) -> panic;
  enemy_copy -> sleep = (***enemy) -> sleep;
  enemy_copy -> curse = (***enemy) -> curse;
  enemy_copy -> boss_count = (***enemy) -> boss_count;
  enemy_copy -> enemy_id = (***enemy) -> enemy_id;
}

//encount_pattern = 1; 敵１体
//encount_pattern = 2; 同じ敵2体
//encount_pattern = 3; 同じ敵３体
//encount_pattern = 4; 同じ敵４体
//encount_pattern = 5; 違う敵２体
//encount_pattern = 6; 違う敵３体
//encount_pattern = 7; 違う敵４体
//encount_pattern = 8; 敵４体(敵２体を１グループとして２グループ)

//未実装
//encount_pattern = 9; 敵４体(同じ敵３体と違う敵１体)
//encount_pattern = 10; 敵３体(同じ敵２体と違う敵１体)

int battle_escape(Player ****st){
  int escape, escape_count, i;
  double escape_base;

  escape_count = 0;
  if ( escape_count == 0 ){  //逃走試行回数
    escape_base = 35 + ( (***st) -> agi * 0.2 + (***st) -> luk * 0.2);   //逃走確率の最小値35% + 逃走を選択したキャラの速と運の値
    escape_base = round(escape_base);
    //printf("escape_base = %f\n", escape_base);
    escape = (rand() % ( 100 - 1 + 1 ) + 1);
    //printf("escape number = %d\n", escape);
    for ( i = 35; i <= escape_base; i++ ){
      if ( escape_base == i ){
        if ( escape >= 1 && escape <= i ){
          printf("逃走成功!!\n");
          printf("%s達は戦闘から逃走した!\n", (***st) -> name);
          return 1;
        }
        else{
          printf("逃走失敗\n");
          return -1;
        }
      }
    }
  }

}

//player_turnについては株式会社ATLUSのRPGで多く用いられているプレスターンバトルシステムを参考
double calculate_player_turn(double player_turn, double turn_decrease){

  if ( turn_decrease == -1 ){  //ターンを1消費
    if ( player_turn == 3 || player_turn == 2 || player_turn == 1 || player_turn == 0 ){
      player_turn += turn_decrease;
    }
    else if ( player_turn == 3.3 ){
      player_turn = 2.2;
    }
    else if ( player_turn == 3.2 ){
      player_turn = 2.1;
    }
    else if ( player_turn == 3.1 ){
      player_turn = 2.0;
    }
    else if ( player_turn == 2.2 ){
      player_turn = 1.1;
    }
    else if ( player_turn == 1.1 ){
      player_turn = 0;
    }
    else if ( player_turn == 2.1 ){
      player_turn = 1;
    }
  }
  else if ( turn_decrease == -2 ){
    if ( player_turn == 3 || player_turn == 2 || player_turn == 1 ){
      player_turn += turn_decrease;
      //printf("%f\n", player_turn);
      if ( player_turn < 0 ){
        player_turn = 0;
      }
    }
    else if ( player_turn == 1.1 || player_turn == 2.1 || player_turn == 2.2 ){
      player_turn = 0;
    }
    else if ( player_turn == 3.3 ){
      player_turn = 1.1;
    }
    else if ( player_turn == 3.2 ){
      player_turn = 1;
    }
    else if ( player_turn == 3.1 ){
      player_turn = 1;
    }
  }
  //プレスターン増加
  else if ( turn_decrease == 0.1 ){
    //printf("here\n");
    if ( player_turn == 3 || player_turn == 2 || player_turn == 1 ){
      player_turn += turn_decrease;
    }
    else if ( player_turn == 1.1 ){
      player_turn = 0;
    }
    else if ( player_turn == 2.1 ){
      player_turn = 2.2;
    }
    else if ( player_turn == 2.2 ){
      player_turn = 1.1;
    }
    else if ( player_turn == 3.1 ){
      player_turn = 3.2;
    }
    else if ( player_turn == 3.2 ){
      player_turn = 3.3;
    }
    else if ( player_turn == 3.3 ){
      player_turn = 2.2;
    }
  }
  //turn消費無し
  else if ( turn_decrease == 0.0 ){
    player_turn = player_turn;
  }

  return player_turn;
}

void display_player_turn(Player ****st, double player_turn){
  //弱点を付くと〇が◎になる
  //◎を0.1、２つ目の◎を0.2、３つ目の◎を0.3とカウント
  if ( player_turn == 3.0 ){
    printf("%sのTURN! (PLAYER TURN: 〇〇〇)\n", (***st) -> name);
  }
  else if ( player_turn == 2.0 ){
    printf("%sのTURN! (PLAYER TURN: 〇〇)\n", (***st) -> name);
  }
  else if ( player_turn == 1.0 ){
    printf("%sのTURN! (PLAYER TURN: 〇)\n", (***st) -> name);
  }
  else if ( player_turn == 1.1 ){
    printf("%sのTURN! (PLAYER TURN: ◎)\n", (***st) -> name);
  }
  else if ( player_turn == 2.1 ){
    printf("%sのTURN! (PLAYER TURN: ◎〇)\n", (***st) -> name);
  }
  else if ( player_turn == 2.2 ){
    printf("%sのTURN! (PLAYER TURN: ◎◎)\n", (***st) -> name);
  }
  else if ( player_turn == 3.1 ){
    printf("%sのTURN! (PLAYER TURN: ◎〇〇)\n", (***st) -> name);
  }
  else if ( player_turn == 3.2 ){
    printf("%sのTURN! (PLAYER TURN: ◎◎〇)\n", (***st) -> name);
  }
  else if ( player_turn == 3.3 ){
    printf("%sのTURN! (PLAYER TURN: ◎◎◎)\n", (***st) -> name);
  }
}

void display_enemy_turn(Enemy ****enemy, double enemy_turn){

  if ( enemy_turn == 4 ){
    printf("%sのTURN! (ENEMY TURN: 〇〇〇〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 3 ){
    printf("%sのTURN! (ENEMY TURN: 〇〇〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 2 ){
    printf("%sのTURN! (ENEMY TURN: 〇〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 1 ){
    printf("%sのTURN! (ENEMY TURN: 〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 4.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎〇〇〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 4.2 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎〇〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 4.3 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎◎〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 4.4 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎◎◎)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 3.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎〇〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 3.2 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 3.3 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎◎)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 2.2 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 2.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎〇)\n", (***enemy) -> name);
  }
  else if ( enemy_turn == 1.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎)\n", (***enemy) -> name);
  }
}

void display_enemy_copy_turn(Enemy *enemy_copy1, double enemy_turn){

  if ( enemy_turn == 4 ){
    printf("%sのTURN! (ENEMY TURN: 〇〇〇〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 3 ){
    printf("%sのTURN! (ENEMY TURN: 〇〇〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 2 ){
    printf("%sのTURN! (ENEMY TURN: 〇〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 1 ){
    printf("%sのTURN! (ENEMY TURN: 〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 4.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎〇〇〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 4.2 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎〇〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 4.3 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎◎〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 4.4 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎◎◎)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 3.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎〇〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 3.2 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 3.3 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎◎)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 2.2 ){
    printf("%sのTURN! (ENEMY TURN: ◎◎)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 2.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎〇)\n", enemy_copy1 -> name);
  }
  else if ( enemy_turn == 1.1 ){
    printf("%sのTURN! (ENEMY TURN: ◎)\n", enemy_copy1 -> name);
  }
}

int battle_error_enemydeadcount1(Enemy ****enemy){
  int enemy_deadcount;

  if ( (***enemy) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount = 0;
  }

  return enemy_deadcount;
}

int battle_error_enemydeadcount2(Enemy ****enemy, Enemy *enemy_copy1){
  int enemy_deadcount;

  enemy_deadcount = 2;
  if ( (***enemy) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( enemy_copy1 -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  return enemy_deadcount;
}

int battle_error_enemydeadcount3(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2){
  int enemy_deadcount;

  enemy_deadcount = 3;
  if ( (***enemy) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( enemy_copy1 -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( enemy_copy2 -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  return enemy_deadcount;
}

int battle_error_enemydeadcount4(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, Enemy *enemy_copy3){
  int enemy_deadcount;

  enemy_deadcount = 4;
  if ( (***enemy) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( enemy_copy1 -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( enemy_copy2 -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( enemy_copy3 -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  return enemy_deadcount;
}

void player_badstatus_recover(Player ****st){

  if ( (***st) -> badstatus == GOOD || (***st) -> badstatus == POISON || (***st) -> badstatus == DEAD || (***st) -> badstatus == CLOSE || (***st) -> badstatus == CURSE ){
    //ステータスはそのまま
  }
  else{
    (***st) -> badstatus = GOOD;
  }

}

//敵１種類の戦闘関数
<<<<<<< HEAD
void game_battle(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Enemy ***enemy, int encount_pattern){  //構造体のポインタを引数にまたポインタ指定（ダブルポインタ)
=======
void game_battle(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Enemy ***enemy, int encount_pattern){  //構造体のポインタを引数にまたポインタ指定（ダブルポインタ)
>>>>>>> origin/main
  int player_damage, enemy_damage, enemy_move, player_guard, player_guard2, player_guard3, move_finish;
  int enemy_deadcount, skill_count, use_skill_count, skill_reaction, recover_point, battle_display_condition_count, enemy_temp;
  int result_exp, result_gold;
  int command;
  int skill_command;
  int skill_target, skill_user;
  double player_turn, enemy_turn, turn_decrease, enemy_turn_temp;

  Enemy enemy_copy1;
  Enemy enemy_copy2;
  Enemy enemy_copy3;

  if ( (**enemy) -> boss_count == 0 ){
    printf("------NORMAL BATTLE------\n");
    printf("\a");
    sleep(1);
    if ( encount_pattern == 1 ){
      printf("%sが現れた!\n", (**enemy) -> name);
      enemy_temp = 1;
      sleep(1);
    }
    else if ( encount_pattern == 2 ){   //同じ敵2体
      printf("%sが２体が現れた!\n", (**enemy) -> name);
      enemy_temp = 2;
      enemy_data_copy(&enemy,&enemy_copy1);
    }
    else if ( encount_pattern == 3 ){   //同じ敵３体
      printf("%sが３体が現れた!\n", (**enemy) -> name);
      enemy_temp = 3;
      enemy_data_copy(&enemy,&enemy_copy1);
      enemy_data_copy(&enemy,&enemy_copy2);
    }
    else if ( encount_pattern == 4 ){   //同じ敵４体
      printf("%sが４体が現れた!\n", (**enemy) -> name);
      enemy_temp = 4;
      enemy_data_copy(&enemy,&enemy_copy1);
      enemy_data_copy(&enemy,&enemy_copy2);
      enemy_data_copy(&enemy,&enemy_copy3);
    }
    printf("\n");
    sleep(1);
  }
  else if ( (**enemy) -> boss_count == 2 ){
    printf("------MID BOSS BATTLE------\n");
    printf("\a");
    sleep(1);
    if ( encount_pattern == 1 ){
      printf("%sが現れた!\n", (**enemy) -> name);
      enemy_temp = 1;
      sleep(1);
    }
    else if ( encount_pattern == 2 ){   //同じ敵2体
      printf("%sが２体が現れた!\n", (**enemy) -> name);
      enemy_temp = 2;
      enemy_data_copy(&enemy,&enemy_copy1);
    }
    else if ( encount_pattern == 3 ){   //同じ敵３体
      printf("%sが３体が現れた!\n", (**enemy) -> name);
      enemy_temp = 3;
      enemy_data_copy(&enemy,&enemy_copy1);
      enemy_data_copy(&enemy,&enemy_copy2);
    }
    else if ( encount_pattern == 4 ){   //同じ敵４体
      printf("%sが４体が現れた!\n", (**enemy) -> name);
      enemy_temp = 4;
      enemy_data_copy(&enemy,&enemy_copy1);
      enemy_data_copy(&enemy,&enemy_copy2);
      enemy_data_copy(&enemy,&enemy_copy3);
    }
    printf("\n");
    sleep(1);
  }
  else{
    printf("<<<<<<<BOSS BATTLE>>>>>>>\n");
    sleep(1);
    printf("\a");
    if ( encount_pattern == 1 ){
      printf("%sが現れた!\n", (**enemy) -> name);
      enemy_temp = 1;
      sleep(1);
    }
    printf("\n");
    sleep(1);
  }

  player_turn = 3;
  //味方パーティが生きている人数を初期プレイヤーターンとして設定
  if ( (**st) -> badstatus == DEAD ){
    player_turn--;
  }
  if ( (**st2) -> badstatus == DEAD ){
    player_turn--;
  }
  if ( (**st3) -> badstatus == DEAD ){
    player_turn--;
  }

  enemy_deadcount = 0; //enemyが死んだか判定
  skill_count = 0; //skillがあるか判定
  use_skill_count = 0; //skillの使用に関する判定
  do {
    skill_reaction = 1;
    //printf("enemy_deadcount:%d\n", enemy_deadcount);
    printf("                 <<<<<<<PLAYER TURN>>>>>>>\n");
    printf("\n");
    //戦闘画面のレイアウト
    if ( encount_pattern == 1 ){
      encount_pattern1_layout(&enemy,encount_pattern);
    }
    else if ( encount_pattern == 2 ){
      encount_pattern2_layout(&enemy,&enemy_copy1,encount_pattern);
    }
    else if ( encount_pattern == 3 ){
      encount_pattern3_layout(&enemy, &enemy_copy1, &enemy_copy2, encount_pattern);
    }
    else if ( encount_pattern == 4 ){
      encount_pattern4_layout(&enemy, &enemy_copy1, &enemy_copy2, &enemy_copy3, encount_pattern);
    }
    printf("\n");

    printf("       %2s                  %2s                 %2s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);

    printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d        HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);

    //HPをグラフィックに表現
    hp_graphycal_display(&st,&st2,&st3);
    //MPをグラフィックに表現
    mp_graphycal_display(&st,&st2,&st3);

    //partyの状態異常ステータスを表示
    battle_display_condition_count = 0;
    battle_display_condition(&st, battle_display_condition_count);

    battle_display_condition_count++;
    battle_display_condition(&st2, battle_display_condition_count);

    battle_display_condition_count++;
    battle_display_condition(&st3, battle_display_condition_count);
    battle_display_condition_count = 0;
    printf("\n");
    printf("\n");
    //player_turnの処理
    //主人公のターン
    player_turn = 3;
    do{
      do{
        move_finish = 0;  //各playerがplayer_turnが減少する行動を行ったら1になる
        player_guard = 0; //主人公のガードを使用に関する判定
        if ( (**st) -> badstatus == DEAD ){
          printf("%sは死んでいて行動できない!\n", (**st) -> name);
          move_finish++;
          turn_decrease = -1;
          player_turn = calculate_player_turn(player_turn, turn_decrease);
        }
        else{
          display_player_turn(&st, player_turn);
          printf("1.ATTACK 2.SKILL 3.GUARD 4.ITEMS 5.ESCAPE 6.NEXT TURN\n");
          printf("\n");
          printf("1~6を入力してください\n");
          command =  _getch();
          if ( command == '1' ){   //攻撃コマンド
            if ( encount_pattern == 1 ){   //敵１体
              player_damage = player_attack(&st, &enemy, &enemy_deadcount);
              if ( player_damage > 0 ){
                printf("%s>>通常攻撃!\n", (**st) -> name);
                sleep(1);
                if ( player_damage > 99000 ){
                  player_damage -= 100000;
                  printf("CRITICAL!\n");
                  turn_decrease = 0.1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                }
                else{
                  turn_decrease = -1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                }
                printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                if ( (**enemy) -> physical_attack == 200 ){ //弱点をついた時

                }
                sleep(1);
              }
              else if ( player_damage == 0 ){
                printf("%s>>通常攻撃!\n", (**st) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("Miss!\n", (**st) -> name); //回避時
              }
              else if ( player_damage == -1 ){
                printf("%s>>通常攻撃!\n", (**st) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("BLOCK!\n");
              }
              else if ( player_damage == -2 ){
                //処理なし
              }
              else if ( player_damage == -3 ){
                //処理なし
              }
              else if ( player_damage == -10 ){
                printf("%s>>通常攻撃!\n", (**st) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("攻撃はかすりともしない!\n");
              }

              if ( player_damage >= (**enemy) -> hp ){
                printf("%sを倒した!\n", (**enemy) -> name);
                enemy_deadcount++;
                (**enemy) -> badstatus = DEAD;
                //printf("enemy_deadcount:%d", enemy_deadcount);
              }
              else{
                if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                  (**enemy) -> hp -= player_damage;
                }
              }
              move_finish++;
            }
            else if ( encount_pattern == 2 ){    //敵2体
              do{
                //どちらの敵に攻撃するかチェック
                command = player_normal_attack_target2(&enemy,&enemy_copy1);

                if ( command == '1' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%sの通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1か２を入力してください\n");
                }
              }while ( command != '1' && command != '2' );

            }
            else if ( encount_pattern == 3 ){   //敵３体
              do{

                command = player_normal_attack_target3(&enemy,&enemy_copy1,&enemy_copy2);

                if ( command == '1' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy2.hp ){
                    printf("%sを倒した!\n", enemy_copy2.name);
                    enemy_deadcount++;
                    enemy_copy2.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy2.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1,２,3のいずれかを入力してください\n");
                }
              }while ( command != '1' && command != '2' && command != '3' );
            }
            else if ( encount_pattern == 4 ){   //敵４体
              do{

                command = player_normal_attack_target4(&enemy,&enemy_copy1,&enemy_copy2,&enemy_copy3);

                if ( command == '1' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Block\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Block\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy2.hp ){
                    printf("%sを倒した!\n", enemy_copy2.name);
                    enemy_deadcount++;
                    enemy_copy2.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy2.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '4' ){
                  player_damage = player_attack(&st, &enemy, &enemy_deadcount);  //本当はenemy_copy3だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy3.hp ){
                    printf("%sを倒した!\n", enemy_copy3.name);
                    enemy_deadcount++;
                    enemy_copy3.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy3.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '9' ){
                  break;
                }
                else{
                  printf("1,2,3,4のいずれかを入力してください\n");
                }
              }while ( command != '1' && command != '2' && command != '3' && command != '4' );
            }
          }
          else if ( command == '2' ){ //skillコマンド
            skill_count = battle_player_skill_list(&player_skill);

            if ( skill_count != 0 ){
              do {
                printf("使用したいSKILL番号を入力してください! (使用しない場合はcを入力してください)\n");
                skill_command = _getch();
                if ( skill_command == '1' ){    //ケディア
                  use_skill_count = 1;
                  skill_target = skill_target_select(&st, &st2, &st3, use_skill_count);

                  //いずれかのターゲットが存在する
                  if ( skill_target != 0 ){
                    skill_user = 1; //Player
                    player_ability(&st,&st2,&st3,&player_skill,use_skill_count,skill_target,skill_user);

                    move_finish++;
                    turn_decrease = -1;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                  }
                  else{
                    //turn消費無し
                  }

                  printf("\n");
                }
                else if ( skill_command == '2' ){   //キュアポ
                  use_skill_count = 2;
                  skill_target = skill_target_select(&st, &st2, &st3, use_skill_count);

                  //いずれかのターゲットが存在する
                  if ( skill_target != 0 ){
                    skill_user = 1; //Player
                    player_ability(&st,&st2,&st3,&player_skill,use_skill_count,skill_target,skill_user);

                    move_finish++;
                    turn_decrease = -1;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                  }
                  else{
                    //turn消費無し
                  }

                  printf("\n");
                }
                else if ( skill_command == 'c' ){
                  printf("\n");
                  use_skill_count = 99;
                }


              }while ( use_skill_count == 0 );    //skillを使うと数値は0ではない
            }

          }
          else if ( command == '3' ){  //防御コマンド

            //enemy_attackのテンプレート
            player_guard++;
            move_finish++;
            turn_decrease = -1;
            player_turn = calculate_player_turn(player_turn, turn_decrease);

          }
          else if ( command == '4' ){  //item使用
            turn_decrease = battle_item_use(&items,&st,&st2,&st3);
            //printf("turn_decrease:%f\n", turn_decrease);
            if ( turn_decrease == 0 ){
              player_turn = calculate_player_turn(player_turn, turn_decrease);
              move_finish = 0;
            }
            else{
              player_turn = calculate_player_turn(player_turn, turn_decrease);
              move_finish = 1;
            }

          }
          else if ( command == '5' ){  //逃走する
            if ( (**enemy) -> boss_count == 0 ){
              printf("逃走中・・・\n");
              sleep(2);
              if ( battle_escape(&st) == 1 ){
                return;
              }
              else{
                player_turn = 0;
                move_finish = 1;
              }
            }
            else{
              printf("逃走失敗!\n");
              sleep(1);
              player_turn = 0;
              move_finish = 1;
            }
          }
          else if ( command == '6' ){
            turn_decrease = 0.1;
            player_turn = calculate_player_turn(player_turn, turn_decrease);
            move_finish = 1;
            player_guard = 0;
          }
          //イレギュラーな入力が行われるとenemy_deadcountの値が最大までインクリメントされてしまうのでこの処理を追加
          else{
            if ( encount_pattern == 1 ){
              enemy_deadcount = battle_error_enemydeadcount1(&enemy);
            }
            else if ( encount_pattern == 2 ){
              enemy_deadcount = battle_error_enemydeadcount2(&enemy,&enemy_copy1);
            }
            else if ( encount_pattern == 3 ){
              enemy_deadcount = battle_error_enemydeadcount3(&enemy,&enemy_copy1,&enemy_copy2);
            }
            else if ( encount_pattern == 4 ){
              enemy_deadcount = battle_error_enemydeadcount4(&enemy,&enemy_copy1,&enemy_copy2,&enemy_copy3);
            }

            printf("コマンドを正しく入力してください\n");
            system("pause");
            printf("\n");
          }

          if ( (**st) -> badstatus == POISON ){ //毒状態時
            poison_effect(&st);
          }
        }
        //printf("enemy_deadcount:%d\n", enemy_deadcount);
      }while ( move_finish != 1 );

      if ( enemy_deadcount == enemy_temp ){
        break;
      }

      if ( player_turn == 0 ){
        break;
      }

      printf("                 <<<<<<<PLAYER TURN>>>>>>>\n");
      printf("\n");

      //戦闘画面のレイアウト
      if ( encount_pattern == 1 ){
        encount_pattern1_layout(&enemy,encount_pattern);
      }
      else if ( encount_pattern == 2 ){
        encount_pattern2_layout(&enemy,&enemy_copy1,encount_pattern);
      }
      else if ( encount_pattern == 3 ){
        encount_pattern3_layout(&enemy,&enemy_copy1,&enemy_copy2,encount_pattern);
      }

      printf("       %2s                  %2s                 %2s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);

      printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d        HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);

      //HPをグラフィックに表現
      hp_graphycal_display(&st,&st2,&st3);
      //MPをグラフィックに表現
      mp_graphycal_display(&st,&st2,&st3);

      //partyの状態異常ステータスを表示
      battle_display_condition_count = 0;
      battle_display_condition(&st, battle_display_condition_count);

      battle_display_condition_count++;
      battle_display_condition(&st2, battle_display_condition_count);

      battle_display_condition_count++;
      battle_display_condition(&st3, battle_display_condition_count);
      battle_display_condition_count = 0;
      printf("\n");
      printf("\n");

      do{
        //２人目のターン
        move_finish = 0;
        player_guard2 = 0;

        if ( (**st2) -> badstatus == DEAD ){
          printf("%sは死んでいて行動できない!\n", (**st2) -> name);
          turn_decrease = -1;
          player_turn = calculate_player_turn(player_turn, turn_decrease);
          move_finish++;
        }
        else{
          //printf("%f\n", player_turn);
          display_player_turn(&st2, player_turn);
          printf("1.ATTACK 2.SKILL 3.GUARD 4.ITEMS 5.ESCAPE 6.NEXT TURN\n");
          printf("\n");
          printf("1~6を入力してください\n");
          command =  _getch();
          if ( command == '1' ){   //攻撃コマンド
            if ( encount_pattern == 1 ){   //敵１体
              player_damage = player_attack(&st2, &enemy, &enemy_deadcount);
              if ( player_damage > 0 ){
                printf("%s>>通常攻撃!\n", (**st2) -> name);
                sleep(1);
                if ( player_damage > 99000 ){
                  player_damage -= 100000;
                  printf("CRITICAL!\n");
                  turn_decrease = 0.1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                  sleep(1);
                }
                else{
                  turn_decrease = -1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                }
                printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
              }
              else if ( player_damage == 0 ){
                printf("%s>>通常攻撃!\n", (**st2) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("Miss!\n", (**st2) -> name); //回避時
              }
              else if ( player_damage == -1 ){
                printf("%s>>通常攻撃!\n", (**st2) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("BLOCK!\n");
              }
              else if ( player_damage == -2 ){
                //処理なし
              }
              else if ( player_damage == -3 ){
                //処理なし
              }
              else if ( player_damage == -10 ){
                printf("%s>>通常攻撃!\n", (**st2) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("攻撃はかすりともしない!\n");
              }

              if ( player_damage >= (**enemy) -> hp ){
                printf("%sを倒した!\n", (**enemy) -> name);
                enemy_deadcount++;
                (**enemy) -> badstatus = DEAD;
                //printf("enemy_deadcount:%d\n", enemy_deadcount);
              }
              else{
                if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                  (**enemy) -> hp -= player_damage;
                }
              }
              move_finish++;
            }
            else if ( encount_pattern == 2 ){    //敵2体
              do{

                //どちらの敵に攻撃するかチェック
                command = player_normal_attack_target2(&enemy,&enemy_copy1);

                if ( command == '1' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1か２を入力してください\n");
                }
              }while ( command != '1' && command != '2' );

            }
            else if ( encount_pattern == 3 ){   //敵３体
              do{

                command = player_normal_attack_target3(&enemy,&enemy_copy1,&enemy_copy2);

                if ( command == '1' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }

                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){   //player_damageが巨大値ならばCRITICAL判定
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy2.hp ){
                    printf("%sを倒した!\n", enemy_copy2.name);
                    enemy_deadcount++;
                    enemy_copy2.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy2.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1,2,3のいずれかを入力してください\n");
                }
              }while ( command != '1' && command != '2' && command != '3' );
            }
            else if ( encount_pattern == 4 ){   //敵４体
              do{

                command = player_normal_attack_target4(&enemy,&enemy_copy1,&enemy_copy2,&enemy_copy3);

                if ( command == '1' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command =='2' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy2.hp ){
                    printf("%sを倒した!\n", enemy_copy2.name);
                    enemy_deadcount++;
                    enemy_copy2.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy2.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '4' ){
                  player_damage = player_attack(&st2, &enemy, &enemy_deadcount);  //本当はenemy_copy3だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st2) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st2) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy3.hp ){
                    printf("%sを倒した!\n", enemy_copy3.name);
                    enemy_deadcount++;
                    enemy_copy3.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy3.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1,2,3,4のいずれかを入力してください\n");
                }
              }while ( command != '1' && command != '2' && command != '3' && command != '4' );
            }

          }
          else if ( command == '2' ){ //skillコマンド
            skill_count = battle_player_skill_list(&player_skill2);

            if ( skill_count != 0 ){
              do {
                printf("使用したいSKILL番号を入力してください! (使用しない場合はcを入力してください)\n");
                skill_command = _getch();
                if ( skill_command == '1' ){    //回復:LV1
                  use_skill_count = 1;
                  skill_target = skill_target_select(&st, &st2, &st3, use_skill_count);

                  //いずれかのターゲットが存在する
                  if ( skill_target != 0 ){
                    skill_user = 2; //Player2
                    player_ability(&st,&st2,&st3,&player_skill,use_skill_count,skill_target,skill_user);

                    turn_decrease = -1;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    move_finish++;
                  }
                  else{
                    //turn消費無し
                  }

                  printf("\n");

                }
                else if ( skill_command == '2' ){   //CURE-POISON
                  use_skill_count = 2;
                  skill_target = skill_target_select(&st, &st2, &st3, use_skill_count);

                  //いずれかのターゲットが存在する
                  if ( skill_target != 0 ){
                    skill_user = 2; //Player
                    player_ability(&st,&st2,&st3,&player_skill,use_skill_count,skill_target,skill_user);

                    move_finish++;
                    turn_decrease = -1;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                  }
                  else{
                    //turn消費無し
                  }

                  printf("\n");

                }
                else if ( skill_command == 'c' ){
                  printf("\n");
                  use_skill_count = 99;
                }

              }while ( use_skill_count == 0 );    //skillを使うと数値は0ではない
            }

          }
          else if ( command == '3' ){  //防御コマンド

            //enemy_attackのテンプレート
            player_guard2++;
            turn_decrease = -1;
            player_turn = calculate_player_turn(player_turn, turn_decrease);
            move_finish++;
          }
          else if ( command == '4' ){  //item使用
            turn_decrease = battle_item_use(&items,&st,&st2,&st3);
            if ( turn_decrease == 0 ){
              player_turn = calculate_player_turn(player_turn, turn_decrease);
              move_finish = 0;
            }
            else{
              player_turn = calculate_player_turn(player_turn, turn_decrease);
              move_finish = 1;
            }

          }
          else if ( command == '5' ){  //逃走する
            if ( (**enemy) -> boss_count == 0 ){
              printf("逃走中・・・\n");
              sleep(2);
              if ( battle_escape(&st2) == 1 ){
                return;
              }
              else{
                player_turn = 0;
                move_finish = 1;
              }
            }
            else{
              printf("逃走失敗!\n");
              sleep(1);
              move_finish = 1;
              player_turn = 0;
            }
          }
          else if ( command == '6' ){
            turn_decrease = 0.1;
            player_turn = calculate_player_turn(player_turn, turn_decrease);
            move_finish = 1;
            player_guard2 = 0;
          }
          //イレギュラーな入力が行われるとenemy_deadcountの値が最大までインクリメントされてしまうのでこの処理を追加
          else{
            if ( encount_pattern == 1 ){
              enemy_deadcount = battle_error_enemydeadcount1(&enemy);
            }
            else if ( encount_pattern == 2 ){
              enemy_deadcount = battle_error_enemydeadcount2(&enemy,&enemy_copy1);
            }
            printf("コマンドを正しく入力してください\n");
            system("pause");
            printf("\n");
          }

          if ( (**st2) -> badstatus == POISON ){ //毒状態時
            poison_effect(&st2);
          }
        }
      }while ( move_finish != 1 );

      if ( enemy_deadcount == enemy_temp ){
        break;
      }

      if ( player_turn == 0 ){
        break;
      }

      printf("                 <<<<<<<PLAYER TURN>>>>>>>\n");
      printf("\n");

      //戦闘画面のレイアウト
      if ( encount_pattern == 1 ){
        encount_pattern1_layout(&enemy,encount_pattern);
      }
      else if ( encount_pattern == 2 ){
        encount_pattern2_layout(&enemy,&enemy_copy1,encount_pattern);
      }
      else if ( encount_pattern == 3 ){
        encount_pattern3_layout(&enemy,&enemy_copy1,&enemy_copy2,encount_pattern);
      }

      printf("       %2s                  %2s                 %2s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);

      printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d        HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);

      //HPをグラフィックに表現
      hp_graphycal_display(&st,&st2,&st3);
      //MPをグラフィックに表現
      mp_graphycal_display(&st,&st2,&st3);

      //partyの状態異常ステータスを表示
      battle_display_condition_count = 0;
      battle_display_condition(&st, battle_display_condition_count);

      battle_display_condition_count++;
      battle_display_condition(&st2, battle_display_condition_count);

      battle_display_condition_count++;
      battle_display_condition(&st3, battle_display_condition_count);
      battle_display_condition_count = 0;
      printf("\n");
      printf("\n");

      do{
        move_finish = 0;
        player_guard3 = 0;

        if ( (**st3) -> badstatus == DEAD ){
          printf("%sは死んでいて行動できない!\n", (**st3) -> name);
          turn_decrease = -1;
          player_turn = calculate_player_turn(player_turn, turn_decrease);
          move_finish++;
        }
        else{
          //printf("%f\n", player_turn);
          display_player_turn(&st3, player_turn);
          printf("1.ATTACK 2.SKILL 3.GUARD 4.ITEMS 5.ESCAPE 6.NEXT TURN\n");
          printf("\n");
          printf("1~6を入力してください\n");
          command =  _getch();
          if ( command == '1' ){   //攻撃コマンド
            if ( encount_pattern == 1 ){   //敵１体
              player_damage = player_attack(&st3, &enemy, &enemy_deadcount);
              if ( player_damage > 0 ){
                printf("%s>>通常攻撃!\n", (**st3) -> name);
                sleep(1);
                if ( player_damage > 99000 ){
                  player_damage -= 100000;
                  printf("CRITICAL!\n");
                  turn_decrease = 0.1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                  sleep(1);
                }
                else{
                  turn_decrease = -1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                }
                printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
              }
              else if ( player_damage == 0 ){
                printf("%s>>通常攻撃!\n", (**st3) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("Miss!\n", (**st3) -> name); //回避時
              }
              else if ( player_damage == -1 ){
                printf("%s>>通常攻撃!\n", (**st3) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("BLOCK!\n");
              }
              else if ( player_damage == -2 ){
                //処理なし
              }
              else if ( player_damage == -3 ){
                //処理なし
              }
              else if ( player_damage == -10 ){
                printf("%s>>通常攻撃!\n", (**st3) -> name);
                sleep(1);
                turn_decrease = -2;
                player_turn = calculate_player_turn(player_turn, turn_decrease);
                printf("攻撃はかすりともしない!\n");
              }

              if ( player_damage >= (**enemy) -> hp ){
                printf("%sを倒した!\n", (**enemy) -> name);
                enemy_deadcount++;
                (**enemy) -> badstatus = DEAD;
                //printf("enemy_deadcount:%d", enemy_deadcount);
              }
              else{
                if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                  (**enemy) -> hp -= player_damage;
                }
              }
              move_finish++;
            }
            else if ( encount_pattern == 2 ){    //敵2体
              do{

                //どちらの敵に攻撃するかチェック
                command = player_normal_attack_target2(&enemy,&enemy_copy1);

                if ( command == '1' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Block\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1か２を入力してください\n");
                }
              }while ( command != '1' && command != '2' );

            }
            else if ( encount_pattern == 3 ){   //敵３体
              do{

                command = player_normal_attack_target3(&enemy,&enemy_copy1,&enemy_copy2);

                if ( command == '1' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy2.hp ){
                    printf("%sを倒した!\n", enemy_copy2.name);
                    enemy_deadcount++;
                    enemy_copy2.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy2.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1,２,3のいずれかを入力してください\n");
                }
              }while ( command != '1' && command != '2' && command != '3' );
            }
            else if ( encount_pattern == 4 ){   //敵４体
              do{

                command = player_normal_attack_target4(&enemy,&enemy_copy1,&enemy_copy2,&enemy_copy3);

                if ( command == '1' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy) -> hp ){
                    printf("%sを倒した!\n", (**enemy) -> name);
                    enemy_deadcount++;
                    (**enemy) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '2' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy1.hp ){
                    printf("%sを倒した!\n", enemy_copy1.name);
                    enemy_deadcount++;
                    enemy_copy1.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy1.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy2.hp ){
                    printf("%sを倒した!\n", enemy_copy2.name);
                    enemy_deadcount++;
                    enemy_copy2.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy2.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '4' ){
                  player_damage = player_attack(&st3, &enemy, &enemy_deadcount);  //本当はenemy_copy3だがenemy_copy2はenemyと同じステータス
                  if ( player_damage > 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    if ( player_damage > 99000 ){
                      player_damage -= 100000;
                      printf("CRITICAL!\n");
                      turn_decrease = 0.1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                      sleep(1);
                    }
                    else{
                      turn_decrease = -1;
                      player_turn = calculate_player_turn(player_turn, turn_decrease);
                    }
                    printf("%s<<%dダメージ\n", (**enemy) -> name, player_damage);
                  }
                  else if ( player_damage == 0 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("Miss!\n", (**st3) -> name); //回避時
                  }
                  else if ( player_damage == -1 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("BLOCK!\n");
                  }
                  else if ( player_damage == -2 ){
                    //処理なし
                  }
                  else if ( player_damage == -3 ){
                    //処理なし
                  }
                  else if ( player_damage == -10 ){
                    printf("%s>>通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= enemy_copy3.hp ){
                    printf("%sを倒した!\n", enemy_copy3.name);
                    enemy_deadcount++;
                    enemy_copy3.badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      enemy_copy3.hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1,2,3,4のいずれかを入力してください\n");
                }
              }while ( command != '1' && command != '2' && command != '3' && command != '4' );
            }
          }
          else if ( command == '2' ){ //skillコマンド
            skill_count = battle_player_skill_list(&player_skill3);

            if ( skill_count != 0 ){
              do {
                printf("使用したいSKILL番号を入力してください! (使用しない場合はcを入力してください)\n");
                skill_command = _getch();
                if ( skill_command == '1' ){    //回復:LV1
                  use_skill_count = 1;
                  skill_target = skill_target_select(&st, &st2, &st3, use_skill_count);

                  //いずれかのターゲットが存在する
                  if ( skill_target != 0 ){
                    skill_user = 3; //Player3
                    player_ability(&st,&st2,&st3,&player_skill,use_skill_count,skill_target,skill_user);

                    turn_decrease = -1;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    move_finish++;
                  }
                  else{
                    //turn消費無し
                  }

                  printf("\n");

                }
                else if ( skill_command == '2' ){   //CURE-POISON
                  use_skill_count = 2;
                  skill_target = skill_target_select(&st, &st2, &st3, use_skill_count);

                  //いずれかのターゲットが存在する
                  if ( skill_target != 0 ){
                    skill_user = 3; //Player
                    player_ability(&st,&st2,&st3,&player_skill,use_skill_count,skill_target,skill_user);

                    move_finish++;
                    turn_decrease = -1;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                  }
                  else{
                    //turn消費無し
                  }

                  printf("\n");
                }
                else if ( skill_command == 'c' ){
                  printf("\n");
                  use_skill_count = 99;
                }

              }while ( use_skill_count == 0 );    //skillを使うと数値は0ではない
            }

          }
          else if ( command == '3' ){  //防御コマンド

            //enemy_attackのテンプレート
            player_guard3++;
            player_turn--;
            move_finish++;
          }
          else if ( command == '4' ){  //item使用
            turn_decrease = battle_item_use(&items,&st,&st2,&st3);
            if ( turn_decrease == 0 ){
              player_turn = calculate_player_turn(player_turn, turn_decrease);
              move_finish = 0;
            }
            else{
              player_turn = calculate_player_turn(player_turn, turn_decrease);
              move_finish = 1;
            }

          }
          else if ( command == '5' ){  //逃走する
            if ( (**enemy) -> boss_count == 0 ){
              printf("逃走中・・・\n");
              sleep(2);
              if ( battle_escape(&st3) == 1 ){
                return;
              }
              else{
                player_turn = 0;
                move_finish = 1;
              }
            }
            else{
              printf("逃走失敗!\n");
              sleep(1);
              move_finish = 1;
              player_turn = 0;
            }
          }
          else if ( command == '6' ){
            turn_decrease = 0.1;
            player_turn = calculate_player_turn(player_turn, turn_decrease);
            move_finish = 1;
            player_guard3 = 0;
          }
          //イレギュラーな入力が行われるとenemy_deadcountの値が最大までインクリメントされてしまうのでこの処理を追加
          else{
            if ( encount_pattern == 1 ){
              enemy_deadcount = battle_error_enemydeadcount1(&enemy);
            }
            else if ( encount_pattern == 2 ){
              enemy_deadcount = battle_error_enemydeadcount2(&enemy,&enemy_copy1);
            }
            else if ( encount_pattern == 3 ){
              enemy_deadcount = battle_error_enemydeadcount3(&enemy,&enemy_copy1,&enemy_copy2);
            }
            else if ( encount_pattern == 4 ){
              enemy_deadcount = battle_error_enemydeadcount4(&enemy,&enemy_copy1,&enemy_copy2,&enemy_copy3);
            }

            printf("コマンドを正しく入力してください\n");
            system("pause");
            printf("\n");
          }

          if ( (**st3) -> badstatus == POISON ){ //毒状態時
            poison_effect(&st3);
          }
        }

      }while ( move_finish != 1 );

      if ( enemy_deadcount == enemy_temp ){
        break;
      }

    }while ( player_turn != 0 );

    //enemy_turn;
    if ( enemy_deadcount == enemy_temp ){
      break;
    }

    //関係のない値の代入
    enemy_turn_temp = -2;

    //敵の攻撃
    do {
      if ( encount_pattern == 1 ){
        enemy_turn = 1;
        if ( enemy_turn != enemy_turn_temp && enemy_turn_temp != -2 ){
          enemy_turn = enemy_turn_temp;
        }

        printf("                 <<<<<<<ENEMY TURN>>>>>>>\n");
        printf("\n");
        encount_pattern1_layout(&enemy,encount_pattern);
        printf("\n");
        sleep(1);

        printf("       %3s                   %3s                    %3s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);
        printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d          HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);
        battle_display_condition_count = 0;
        hp_graphycal_display(&st,&st2,&st3);
        mp_graphycal_display(&st,&st2,&st3);
        battle_display_condition(&st, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st2, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st3, battle_display_condition_count);
        printf("\n");

        display_enemy_turn(&enemy, enemy_turn);
        //enemyの攻撃
        //printf("%f\n", enemy_turn);
        sleep(1);
<<<<<<< HEAD
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
=======
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
        sleep(1);
        //printf("%f\n", enemy_turn);

        if ( enemy_turn <= 0 ){
          break;
        }
      }
      else if ( encount_pattern == 2 ){
        enemy_turn = 2;
        if ( (**enemy) -> badstatus == DEAD ){
          enemy_turn--;
        }
        if ( enemy_copy1.badstatus == DEAD ){
          enemy_turn--;
        }
        //printf("enemy_turn:%f\n", enemy_turn);
        //printf("enemy_turn_temp:%f\n", enemy_turn_temp);

        if ( enemy_turn != enemy_turn_temp && enemy_turn_temp != -2 ){
          enemy_turn = enemy_turn_temp;
        }
        //printf("enemy_turn:%f\n", enemy_turn);
        //printf("enemy_turn_temp:%f\n", enemy_turn_temp);

        printf("                 <<<<<<<ENEMY TURN>>>>>>>\n");
        printf("\n");
        encount_pattern2_layout(&enemy,&enemy_copy1,encount_pattern);
        printf("\n");
        sleep(1);

        printf("       %3s                   %3s                    %3s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);
        printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d          HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);
        battle_display_condition_count = 0;
        hp_graphycal_display(&st,&st2,&st3);
        mp_graphycal_display(&st,&st2,&st3);
        battle_display_condition(&st, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st2, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st3, battle_display_condition_count);
        printf("\n");
        //printf("enemy's badstatus:%d\n", (**enemy) -> badstatus);
        //printf("enemy_copy1's badstatus:%d\n", enemy_copy1.badstatus);
        if ( (**enemy) -> badstatus != DEAD ){
          display_enemy_turn(&enemy, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
          printf("\n");
        }

        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

        if ( enemy_copy1.badstatus != DEAD ){
          sleep(1);
          display_enemy_copy_turn(&enemy_copy1, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &equip, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
        }

        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

      }
      else if ( encount_pattern == 3 ){
        enemy_turn = 3;
        if ( (**enemy) -> badstatus == DEAD ){
          enemy_turn--;
        }
        if ( enemy_copy1.badstatus == DEAD ){
          enemy_turn--;
        }
        if ( enemy_copy2.badstatus == DEAD ){
          enemy_turn--;
        }

        if ( enemy_turn != enemy_turn_temp && enemy_turn_temp != -2 ){
          enemy_turn = enemy_turn_temp;
        }
        //printf("enemy_turn:%f\n", enemy_turn);
        printf("                 <<<<<<<ENEMY TURN>>>>>>>\n");
        printf("\n");
        encount_pattern3_layout(&enemy,&enemy_copy1,&enemy_copy2,encount_pattern);
        printf("\n");
        sleep(1);

        printf("       %3s                   %3s                    %3s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);
        printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d          HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);
        battle_display_condition_count = 0;
        hp_graphycal_display(&st,&st2,&st3);
        mp_graphycal_display(&st,&st2,&st3);
        battle_display_condition(&st, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st2, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st3, battle_display_condition_count);
        printf("\n");
        //printf("enemy's badstatus:%d\n", (**enemy) -> badstatus);
        //printf("enemy_copy1's badstatus:%d\n", enemy_copy1.badstatus);
        if ( (**enemy) -> badstatus != DEAD ){
          display_enemy_turn(&enemy, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
          printf("\n");
        }

        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

        if ( enemy_copy1.badstatus != DEAD ){
          sleep(1);
          display_enemy_copy_turn(&enemy_copy1, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &equip, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //rintf("%f\n", enemy_turn);
        }
        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

        if ( enemy_copy2.badstatus != DEAD ){
          sleep(1);
          display_enemy_copy_turn(&enemy_copy2, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy_copy2, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &equip, &enemy_copy2, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
        }

      }
      else if ( encount_pattern == 4 ){
        enemy_turn = 4;
        if ( (**enemy) -> badstatus == DEAD ){
          enemy_turn--;
        }
        if ( enemy_copy1.badstatus == DEAD ){
          enemy_turn--;
        }
        if ( enemy_copy2.badstatus == DEAD ){
          enemy_turn--;
        }
        if ( enemy_copy3.badstatus == DEAD ){
          enemy_turn--;
        }

        if ( enemy_turn != enemy_turn_temp && enemy_turn_temp != -2 ){
          enemy_turn = enemy_turn_temp;
        }
        //printf("enemy_turn:%f\n", enemy_turn);
        printf("                 <<<<<<<ENEMY TURN>>>>>>>\n");
        printf("\n");
        encount_pattern4_layout(&enemy,&enemy_copy1,&enemy_copy2,&enemy_copy3,encount_pattern);
        printf("\n");
        sleep(1);

        printf("       %3s                   %3s                    %3s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);
        printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d          HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);
        battle_display_condition_count = 0;
        hp_graphycal_display(&st,&st2,&st3);
        mp_graphycal_display(&st,&st2,&st3);
        battle_display_condition(&st, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st2, battle_display_condition_count);
        battle_display_condition_count++;
        battle_display_condition(&st3, battle_display_condition_count);
        printf("\n");
        //printf("enemy's badstatus:%d\n", (**enemy) -> badstatus);
        //printf("enemy_copy1's badstatus:%d\n", enemy_copy1.badstatus);
        if ( (**enemy) -> badstatus != DEAD ){
          display_enemy_turn(&enemy, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
          printf("\n");
        }

        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

        if ( enemy_copy1.badstatus !=DEAD ){
          sleep(1);
          display_enemy_copy_turn(&enemy_copy1, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &equip, &enemy_copy1, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
        }
        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

        if ( enemy_copy2.badstatus != DEAD ){
          sleep(1);
          display_enemy_copy_turn(&enemy_copy2, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy_copy2, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &equip, &enemy_copy2, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
        }

        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

        if ( enemy_copy3.badstatus != DEAD ){
          sleep(1);
          display_enemy_copy_turn(&enemy_copy3, enemy_turn);
          //enemyの攻撃
          //printf("%f\n", enemy_turn);
          sleep(1);
<<<<<<< HEAD
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy_copy3, player_guard, player_guard2, player_guard3, enemy_turn);
=======
          enemy_turn = enemy_copy_attack_pattern(&st, &st2, &st3, &equip, &enemy_copy3, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
          sleep(1);
          //printf("%f\n", enemy_turn);
        }

        if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
          display_gameover();
        }
        if ( enemy_turn <= 0 ){
          break;
        }

      }
      if ( (**st) -> badstatus == DEAD && (**st2) -> badstatus == DEAD && (**st3) -> badstatus == DEAD ){
        display_gameover();
      }

      enemy_turn_temp = enemy_turn;

    } while ( enemy_turn > 0 );

  }while( enemy_deadcount != enemy_temp || ( (**st) -> badstatus != DEAD && (**st2) -> badstatus != DEAD && (**st3) -> badstatus != DEAD ) );

  (**enemy) -> badstatus = GOOD;  //敵の状態をGOODに戻す
  enemy_copy1.badstatus = GOOD;
  (**enemy) -> hp = (**enemy) -> maxhp;
  (**enemy) -> mp = (**enemy) -> maxmp;

  result_exp = 0;
  result_gold = 0;
  if ( encount_pattern == 1 ){
    result_exp = (**enemy) -> exp;
    result_gold = (**enemy) -> gold;
  }
  else if ( encount_pattern == 2 ){
    result_exp = (**enemy) -> exp + enemy_copy1.exp;
    result_gold = (**enemy) -> gold + enemy_copy1.gold;
  }
  else if ( encount_pattern == 3 ){
    result_exp = (**enemy) -> exp + enemy_copy1.exp + enemy_copy2.exp;
    result_gold = (**enemy) -> gold + enemy_copy1.gold + enemy_copy2.gold;
  }
  else if ( encount_pattern == 4 ){
    result_exp = (**enemy) -> exp + enemy_copy1.exp + enemy_copy2.exp + enemy_copy3.exp;
    result_gold = (**enemy) -> gold + enemy_copy1.gold + enemy_copy2.gold + enemy_copy3.gold;
  }

  printf("\a");
  sleep(1);
  printf("%s達は戦闘に勝利した!\n", (**st) -> name);
  printf("------RESULT------\n");
  printf("  EXP:%d GOLD:%d\n", result_exp, result_gold);
  printf("\n");

  //アイテムドロップ
  if ( encount_pattern == 1 || encount_pattern == 2 || encount_pattern == 3 || encount_pattern == 4 ){
    item_drop(&st,&st2,&st3,&enemy,&items,encount_pattern);
  }

  if ( (**st) -> badstatus == DEAD ){
    //経験値獲得無し
  }
  else{
    (**st) -> exp += result_exp;
    (**st) -> sumexp += result_exp;
    level_up(&st, &player_skill);
  }
  if ( (**st2) -> badstatus == DEAD ){
    //獲得経験値なし
  }
  else{
    (**st2) -> exp += result_exp;
    (**st2) -> sumexp += result_exp;
    level_up(&st2, &player_skill2);
  }
  if ( (**st3) -> badstatus == DEAD ){
    //獲得経験値なし
  }
  else{
    (**st3) -> exp += result_exp;
    (**st3) -> sumexp += result_exp;
    level_up(&st3, &player_skill3);
  }

  (**st) -> gold += result_gold;

  player_badstatus_recover(&st);
  player_badstatus_recover(&st2);
  player_badstatus_recover(&st3);
}
