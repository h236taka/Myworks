#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <wchar.h>
#include "rpg.h"

//プレイ時間に関するグローバルな型・変数
time_t start_time, end_time;
int play_time;

int main(void){
  int load, input;   //input:プレイヤーの入力
  Player player;
  Player player2;
  Player player3;
  Items items = {0};
<<<<<<< HEAD
  Equip pEquip;
  Equip p2Equip;
  Equip p3Equip;
=======
  Equip equip = {0};
>>>>>>> origin/main

  Area area = {0};


  //boss_count = １ならばボス扱い
  //boss_count = 2ならば強制戦闘
  //enemy_skillが0以外なら敵はスキルを使用
  //enemy_id = 1,2,3,4 通常攻撃のみ
  //enemy_id = 100 POISON
  //enemy_id = 101 回復:LV1

  //enemy_id = 0 通常攻撃のみ
  // name hp, maxhp, mp, maxmp, atk, magic, str, agi, luk, lv, exp, gold, badstatus, physical_attack, gun_attack, fire, ice, elec, wave, almighty, death, expel, poison, palyze, charm, close, stone, panic, sleep, curse, boss_count, enemy_id
  Enemy slime = {"スライム", 10, 10, 0, 0, 2, 1, 1, 1, 1, 1, 5, 15, 0, 150, 100, 200, 100, 100, 100, 100, 100, 200, 100, 100, 100, 100, 100, 100, 100, 100, 0, 1};
  Enemy kobalt = {"コボルト", 20, 20, 0, 0, 2, 1, 2, 1, 1, 2, 10, 20, 0, 80, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 2};
  Enemy goblin = {"ゴブリン", 65, 65, 0, 0, 3, 1, 2, 2, 1, 3, 25, 30, 0, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 1, 3}; //boss
  Enemy zombiedog = {"ゾンビドッグ", 30, 30, 0, 0, 2, 1, 3, 5, 1, 3, 8, 15, 0, 100, 100, 200, 200, 100, 100, 100, -1, 200, 100, 100, 100, 100, 100, 100, 100, 100, 0, 4};
  Enemy ghoul = {"グール", 30, 30, 10, 10, 1, 1, 1, 1, 1, 2, 10, 20, 0, 100, 100, 150, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 5};
  Enemy zombie = {"ゾンビ", 55, 55, 12, 12, 2, 1, 3, 2, 1, 2, 6, 30, 0, 100, 100, 200, 100, 200, 100, 100, -1, 200, 100, 100, 100, 100, 100, 100, 100, -1, 0, 6};
  Enemy goblin_normal = {"ゴブリン", 70, 70, 0, 0, 3, 1, 3, 2, 1, 3, 15, 30, 0, 100, 150, 100, 100, 100, 200, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 7};  //通常敵
  Enemy onmoraki = {"オンモラキ", 50, 50, 15, 15, 2, 3, 2, 3, 2, 4, 12, 25, 0, 80, 100, -1, 200, 100, 100, 100, -1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 8};
  //Enemy pixie = {"ピクシー", 55, 55, 15, 15, 1, 3, 1, 5, 5, 3, 25, 40, 0, 100, 150, 100, 100, 50, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 101};
  //Enemy angel = {"エンジェル", 108, 108, 30, 30, 2, 5, 3, 5, 2, 4, 50, 100, 0, 100, 100, 100, 100, 150, 100, 100, 200, 100, 100, 100, 100, 100, 100, 100, 100, 100, 1, 101};

  srand((unsigned int)time(NULL));

  P_skill player_skill;
  P_skill player_skill2;
  P_skill player_skill3;

<<<<<<< HEAD
=======
  /*strcpy(equip.isHpRing1, "equip");
  printf("%s\n", equip.isHpRing1);
  exit(EXIT_SUCCESS);*/

>>>>>>> origin/main
  do{
    printf("MAIN MENU\n");
    printf("1:<<<LOAD GAME>>>\n");
    printf("2:<<<NEW  GAME>>>\n");
    printf("3:<<<DELETE SAVE DATA>>>\n");
    printf("1か2か3を入力してください(ゲームを起動しない場合はcを入力してください)\n");
    input = _getch();
    if ( input == '1' ){
      load = 1;
<<<<<<< HEAD
      save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip, load);
=======
      save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &equip, load);
>>>>>>> origin/main
    }
    else if ( input == '2' ){
      //new gameでは、player.stage_clearは0
      //prologue();
      start_time = time(NULL);
      printf("start_time:%d\n", start_time);
      game_start(&player, &player2, &player3);
      load = 0;
<<<<<<< HEAD
      game_story1(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip, &area, &slime, &kobalt, &goblin);
      save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip, load);
=======
      game_story1(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &equip, &area, &slime, &kobalt, &goblin);
      save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &equip, load);
>>>>>>> origin/main
    }
    else if ( input == '3' ){
      delete_savedata();
    }
    else if ( input == '' ){
      printf("強制終了\n");
      exit(EXIT_FAILURE);
    }
    else if ( input == 'c' ){
      printf("ゲームを終了します・・・\n");
      exit(EXIT_SUCCESS);
    }
  }while ( input != '1' && input != '2' && input != '3' );

  //printf("%d\n", player.stage_clear);
  load = 0;
  if ( player.stage_clear == 1 || player.stage_clear == 1.1 ){
    //start_time = time(NULL);
<<<<<<< HEAD
    game_story2(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items,&pEquip, &p2Equip, &p3Equip,&area,&zombie,&slime,&goblin_normal,&kobalt,&zombiedog,&onmoraki);//図書館ステージ
    save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip, load);
=======
    game_story2(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items,&equip,&area,&zombie,&slime,&goblin_normal,&kobalt,&zombiedog,&onmoraki);//図書館ステージ
    save_load(&player, &player2, &player3, &player_skill, &player_skill2, &player_skill3, &items, &equip, load);
>>>>>>> origin/main
  }
  else if ( player.stage_clear == 2 ){
    printf("Wait・・・\n");
  }

  return 0;
}
