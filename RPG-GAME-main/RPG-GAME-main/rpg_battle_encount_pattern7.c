#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <math.h>
#include <wchar.h>
#include <ctype.h>
#include <mbctype.h>
#include <mbstring.h>
#include "rpg.h"

int battle_error_enemydeadcount7(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3){
  int enemy_deadcount;

  enemy_deadcount = 3;
  if ( (***enemy) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( (***enemy1) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( (***enemy2) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  if ( (***enemy3) -> badstatus == DEAD ){
    //nothing
  }
  else{
    enemy_deadcount--;
  }

  return enemy_deadcount;
}

void enemy_full_recover7(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3){

  (***enemy) -> badstatus = GOOD;
  (***enemy1) -> badstatus = GOOD;
  (***enemy2) -> badstatus = GOOD;
  (***enemy3) -> badstatus = GOOD;

  (***enemy) -> hp = (***enemy) -> maxhp;
  (***enemy) -> mp = (***enemy) -> maxmp;

  (***enemy1) -> hp = (***enemy1) -> maxhp;
  (***enemy1) -> mp = (***enemy1) -> maxmp;

  (***enemy2) -> hp = (***enemy2) -> maxhp;
  (***enemy2) -> mp = (***enemy2) -> maxmp;

  (***enemy3) -> hp = (***enemy3) -> maxhp;
  (***enemy3) -> mp = (***enemy3) -> maxmp;
}

//encount_pattern = 5;
<<<<<<< HEAD
void game_battle_encount_pattern7(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Enemy ***enemy, Enemy ***enemy1, Enemy ***enemy2, Enemy ***enemy3, int encount_pattern){
=======
void game_battle_encount_pattern7(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Enemy ***enemy, Enemy ***enemy1, Enemy ***enemy2, Enemy ***enemy3, int encount_pattern){
>>>>>>> origin/main
  int player_damage, enemy_damage, enemy_move, player_guard, player_guard2, player_guard3, move_finish;
  int enemy_deadcount, skill_count, use_skill_count, skill_reaction, recover_point, battle_display_condition_count, enemy_temp;
  int result_exp, result_gold;
  int command;
  int skill_command;
  int skill_target, skill_user;
  double player_turn, enemy_turn, turn_decrease, enemy_turn_temp;

  if ( (**enemy) -> boss_count == 0 ){
    printf("<<<<<<NORMAL BATTLE>>>>>>\n");
    printf("\a");
    sleep(1);
    if ( encount_pattern == 7 ){  //違う敵2体
      printf("%sと%sと%sと%sが現れた!\n", (**enemy) -> name, (**enemy1) -> name, (**enemy2) -> name, (**enemy3) -> name);
      enemy_temp = 4;
      sleep(1);
    }
    printf("\n");
    sleep(1);
  }
  else if ( (**enemy) -> boss_count == 2 ){
    printf("<<<<<<MID BOSS BATTLE>>>>>>\n");
    printf("\a");
    sleep(1);
    if ( encount_pattern == 7 ){
      printf("%sと%sと%sと%sが現れた!\n", (**enemy) -> name, (**enemy1) -> name, (**enemy2) -> name, (**enemy3) -> name);
      enemy_temp = 4;
      sleep(1);
    }

    printf("\n");
    sleep(1);
  }
  else{
    printf("<<<<<<<BOSS BATTLE>>>>>>>\n");
    sleep(1);
    printf("\a");
    if ( encount_pattern == 7 ){
      printf("%sと%sと%sと%sが現れた!\n", (**enemy) -> name, (**enemy1) -> name, (**enemy2) -> name, (**enemy3) -> name);
      enemy_temp = 4;
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
    printf("enemy_deadcount:%d\n", enemy_deadcount);
    printf("                 <<<<<<<PLAYER TURN>>>>>>>\n");
    printf("\n");
    //戦闘画面のレイアウト
    encount_pattern7_layout(&enemy,&enemy1,&enemy2,&enemy3,encount_pattern);
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
            do{
              command = player_normal_attack_target7(&enemy,&enemy1,&enemy2,&enemy3);

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
                player_damage = player_attack(&st, &enemy1, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
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
                  printf("%s<<%dダメージ\n", (**enemy1) -> name, player_damage);
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

                if ( player_damage >= (**enemy1) -> hp ){
                  printf("%sを倒した!\n", (**enemy1) -> name);
                  enemy_deadcount++;
                  (**enemy) -> badstatus = DEAD;
                  //printf("enemy_deadcount:%d", enemy_deadcount);
                }
                else{
                  if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                    (**enemy1) -> hp -= player_damage;
                  }
                }
                move_finish++;
              }
              else if ( command == '3' ){
                player_damage = player_attack(&st, &enemy2, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
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
                  printf("%s<<%dダメージ\n", (**enemy2) -> name, player_damage);
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

                if ( player_damage >= (**enemy2) -> hp ){
                  printf("%sを倒した!\n", (**enemy2) -> name);
                  enemy_deadcount++;
                  (**enemy2) -> badstatus = DEAD;
                  //printf("enemy_deadcount:%d", enemy_deadcount);
                }
                else{
                  if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                    (**enemy2) -> hp -= player_damage;
                  }
                }
                move_finish++;
              }
              else if ( command == '4' ){
                player_damage = player_attack(&st, &enemy3, &enemy_deadcount);
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
                  printf("%s<<%dダメージ\n", (**enemy3) -> name, player_damage);
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

                if ( player_damage >= (**enemy3) -> hp ){
                  printf("%sを倒した!\n", (**enemy3) -> name);
                  enemy_deadcount++;
                  (**enemy3) -> badstatus = DEAD;
                  //printf("enemy_deadcount:%d", enemy_deadcount);
                }
                else{
                  if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                    (**enemy3) -> hp -= player_damage;
                  }
                }
                move_finish++;
              }
              else if ( command == 'c' ){
                break;
              }
              else{
                printf("1,２,3,4のいずれかを入力してください\n");
              }
            }while ( command != '1' && command != '2' && command != '3' && command != '4' );

          }
          else if ( command == '2' ){ //skillコマンド
            skill_count = battle_player_skill_list(&player_skill);

            if ( skill_count != 0 ){
              do {
                printf("使用したいSKILL番号を入力してください! (使用しない場合はcを入力してください)\n");
                skill_command = _getch();
                if ( skill_command == '1' ){    //回復:LV1
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
                else if ( skill_command == '2' ){   //CURE-POISON
                  use_skill_count = 2;
                  //player_ability(&st, &player_skill, use_skill_count);
                  move_finish++;
                  turn_decrease = -1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);

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
            printf("turn_decrease:%f\n", turn_decrease);
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
                enemy_full_recover7(&enemy,&enemy1,&enemy2,&enemy3);
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
            if ( encount_pattern == 7 ){
              enemy_deadcount = battle_error_enemydeadcount7(&enemy,&enemy1,&enemy2,&enemy3);
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
      encount_pattern7_layout(&enemy,&enemy1,&enemy2,&enemy3,encount_pattern);

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
            do{
              command = player_normal_attack_target7(&enemy,&enemy1,&enemy2,&enemy3);

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
                player_damage = player_attack(&st2, &enemy1, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
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
                  printf("%s<<%dダメージ\n", (**enemy1) -> name, player_damage);
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

                if ( player_damage >= (**enemy1) -> hp ){
                  printf("%sを倒した!\n", (**enemy1) -> name);
                  enemy_deadcount++;
                  (**enemy1) -> badstatus = DEAD;
                  //printf("enemy_deadcount:%d", enemy_deadcount);
                }
                else{
                  if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                    (**enemy1) -> hp -= player_damage;
                  }
                }
                move_finish++;
              }
              else if ( command == '3' ){
                player_damage = player_attack(&st3, &enemy2, &enemy_deadcount);  //本当はenemy_copy2だがenemy_copy2はenemyと同じステータス
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
                  printf("%s<<%dダメージ\n", (**enemy2) -> name, player_damage);
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

                if ( player_damage >= (**enemy2) -> hp ){
                  printf("%sを倒した!\n", (**enemy2) -> name);
                  enemy_deadcount++;
                  (**enemy2) -> badstatus = DEAD;
                  //printf("enemy_deadcount:%d", enemy_deadcount);
                }
                else{
                  if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                    (**enemy2) -> hp -= player_damage;
                  }
                }
                move_finish++;
              }
              else if ( command == '4' ){
                player_damage = player_attack(&st2, &enemy3, &enemy_deadcount);
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
                  printf("%s<<%dダメージ\n", (**enemy3) -> name, player_damage);
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

                if ( player_damage >= (**enemy3) -> hp ){
                  printf("%sを倒した!\n", (**enemy3) -> name);
                  enemy_deadcount++;
                  (**enemy3) -> badstatus = DEAD;
                  //printf("enemy_deadcount:%d", enemy_deadcount);
                }
                else{
                  if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                    (**enemy3) -> hp -= player_damage;
                  }
                }
                move_finish++;
              }
              else if ( command == 'c' ){
                break;
              }
              else{
                printf("1,２,3,4のいずれかを入力してください\n");
              }
            }while ( command != '1' && command != '2' && command != '3' && command != '4' );

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
                  //player_ability(&st2, &player_skill2, use_skill_count);

                  turn_decrease = -1;
                  player_turn = calculate_player_turn(player_turn, turn_decrease);
                  move_finish++;

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
                enemy_full_recover7(&enemy,&enemy1,&enemy2,&enemy3);
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
            if ( encount_pattern == 7 ){
              enemy_deadcount = battle_error_enemydeadcount7(&enemy,&enemy1,&enemy2,&enemy3);
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
      encount_pattern7_layout(&enemy,&enemy1,&enemy2,&enemy3, encount_pattern);

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
            if ( encount_pattern == 7 ){    //敵5体
              do{
                //どちらの敵に攻撃するかチェック
                command = player_normal_attack_target7(&enemy,&enemy1,&enemy2,&enemy3);

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
                  player_damage = player_attack(&st3, &enemy1, &enemy_deadcount);  //本当はenemy_copy1だがenemy_copy1はenemyと同じステータス
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
                    printf("%s<<%dダメージ\n", (**enemy1) -> name, player_damage);
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
                    printf("%sの通常攻撃!\n", (**st3) -> name);
                    sleep(1);
                    turn_decrease = -2;
                    player_turn = calculate_player_turn(player_turn, turn_decrease);
                    printf("攻撃はかすりともしない!\n");
                  }

                  if ( player_damage >= (**enemy1) -> hp ){
                    printf("%sを倒した!\n", (**enemy1) -> name);
                    enemy_deadcount++;
                    (**enemy1) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy1) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '3' ){
                  player_damage = player_attack(&st3, &enemy2, &enemy_deadcount);
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
                    printf("%s<<%dダメージ\n", (**enemy2) -> name, player_damage);
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

                  if ( player_damage >= (**enemy2) -> hp ){
                    printf("%sを倒した!\n", (**enemy2) -> name);
                    enemy_deadcount++;
                    (**enemy2) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy2) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == '4' ){
                  player_damage = player_attack(&st3, &enemy3, &enemy_deadcount);
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
                    printf("%s<<%dダメージ\n", (**enemy3) -> name, player_damage);
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

                  if ( player_damage >= (**enemy3) -> hp ){
                    printf("%sを倒した!\n", (**enemy3) -> name);
                    enemy_deadcount++;
                    (**enemy3) -> badstatus = DEAD;
                    //printf("enemy_deadcount:%d", enemy_deadcount);
                  }
                  else{
                    if ( player_damage != -1 && player_damage != -2 && player_damage != -3 ){
                      (**enemy3) -> hp -= player_damage;
                    }
                  }
                  move_finish++;
                }
                else if ( command == 'c' ){
                  break;
                }
                else{
                  printf("1,２,3,4のいずれかを入力してください\n");
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
                  //player_ability(&st3, &player_skill3, use_skill_count);

                  player_turn--;
                  move_finish++;
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
                enemy_full_recover7(&enemy,&enemy1,&enemy2,&enemy3);
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
            if ( encount_pattern == 7 ){
              enemy_deadcount = battle_error_enemydeadcount7(&enemy,&enemy1,&enemy2,&enemy3);
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
      enemy_turn = 4;
      if ( (**enemy) -> badstatus == DEAD ){
        enemy_turn--;
      }
      if ( (**enemy1) -> badstatus == DEAD ){
        enemy_turn--;
      }
      if ( (**enemy2) -> badstatus == DEAD ){
        enemy_turn--;
      }
      if ( (**enemy3) -> badstatus == DEAD ){
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
      encount_pattern7_layout(&enemy,&enemy1,&enemy2,&enemy3,encount_pattern);
      printf("\n");
      sleep(1);

      printf("       %3s                   %3s                 %3s\n", (**st) -> name, (**st2) -> name, (**st3) -> name);
      printf(" HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d       HP:%d/%d MP:%d/%d\n", (**st) -> hp, (**st) -> maxhp, (**st) -> mp, (**st) -> maxmp, (**st2) -> hp, (**st2) -> maxhp, (**st2) -> mp, (**st2) -> maxmp, (**st3) -> hp, (**st3) -> maxhp, (**st3) -> mp, (**st3) -> maxmp);
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

      if ( (**enemy1) -> badstatus != DEAD ){
        sleep(1);
        display_enemy_turn(&enemy1, enemy_turn);
        //enemyの攻撃
        //printf("%f\n", enemy_turn);
        sleep(1);
<<<<<<< HEAD
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy1, player_guard, player_guard2, player_guard3, enemy_turn);
=======
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy1, player_guard, player_guard2, player_guard3, enemy_turn);
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

      if ( (**enemy2) -> badstatus != DEAD ){
        sleep(1);
        display_enemy_turn(&enemy2, enemy_turn);
        //enemyの攻撃
        //printf("%f\n", enemy_turn);
        sleep(1);
<<<<<<< HEAD
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy2, player_guard, player_guard2, player_guard3, enemy_turn);
=======
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy2, player_guard, player_guard2, player_guard3, enemy_turn);
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

      if ( (**enemy3) -> badstatus != DEAD ){
        sleep(1);
        display_enemy_turn(&enemy3, enemy_turn);
        //enemyの攻撃
        //printf("%f\n", enemy_turn);
        sleep(1);
<<<<<<< HEAD
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &pEquip, &p2Equip, &p3Equip, &enemy3, player_guard, player_guard2, player_guard3, enemy_turn);
=======
        enemy_turn = enemy_attack_pattern(&st, &st2, &st3, &equip, &enemy3, player_guard, player_guard2, player_guard3, enemy_turn);
>>>>>>> origin/main
        sleep(1);
        //printf("%f\n", enemy_turn);
      }

      enemy_turn_temp = enemy_turn;

    }while ( enemy_turn > 0 );

  }while( enemy_deadcount != enemy_temp || ( (**st) -> badstatus != DEAD && (**st2) -> badstatus != DEAD && (**st3) -> badstatus != DEAD ) );

  //encount_pattern = 5;
  enemy_full_recover7(&enemy,&enemy1,&enemy2,&enemy3);

  result_exp = 0;
  result_gold = 0;

  result_exp = (**enemy) -> exp + (**enemy1) -> exp + (**enemy2) -> exp + (**enemy3) -> exp;
  result_gold = (**enemy) -> gold + (**enemy1) -> gold + (**enemy2) -> gold + (**enemy3) -> gold;

  printf("\a");
  sleep(1);
  printf("%s達は戦闘に勝利した!\n", (**st) -> name);
  printf("------RESULT------\n");
  printf("  EXP:%d GOLD:%d\n", result_exp, result_gold);
  printf("\n");

  //アイテムドロップ
  item_drop(&st,&st2,&st3,&enemy,&items,encount_pattern);
  item_drop(&st,&st2,&st3,&enemy1,&items,encount_pattern);
  item_drop(&st,&st2,&st3,&enemy2,&items,encount_pattern);
  item_drop(&st,&st2,&st3,&enemy3,&items,encount_pattern);

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
