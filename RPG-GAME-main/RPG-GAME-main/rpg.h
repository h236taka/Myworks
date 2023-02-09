#ifndef RPG_H
#define RPG_H

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

//マクロ定義
#define NAME_LEN 50
#define ENEMY_NAME 100
#define COMMAND 2
//#define POINT 2
#define S_COMMAND 3

#define GOOD 0
#define DEAD 1
#define POISON 2
#define PALYZE 3
#define CHARM 4
#define CLOSE 5
#define STONE 6
#define PANIC 7
#define SLEEP 8
#define CURSE 9

//型定義

typedef struct enemy {
  char name[ENEMY_NAME];
  int hp;
  int maxhp;
  int mp;
  int maxmp;
  int atk;
  int magic;
  int str;
  int agi;
  int luk;
  int lv;
  int exp;
  int gold;
  int badstatus;
  int physical_attack; //物理攻撃
  int gun_attack; //銃攻撃
  int fire;       //火炎攻撃
  int ice;        //氷結攻撃
  int elec;       //電撃攻撃
  int wave;       //衝撃攻撃
  int almighty;   //万能攻撃
  int death;      //呪殺攻撃
  int expel;      //破魔攻撃
  int poison;     //毒耐性
  int palyze;     //麻痺耐性
  int charm;      //魅了耐性
  int close;      //魔封耐性
  int stone;      //石化耐性
  int panic;      //混乱耐性
  int sleep;      //睡眠耐性
  int curse;      //呪い耐性
  int boss_count;
  int enemy_id;  //敵識別ID
} Enemy;

//playerのスキル
typedef struct player_skill {   //値が1ならば習得済み
  int recover1; //ケディア
  int cure_poison; //毒治療
  int recover2; //回復:LV2
  int recover3; //回復:LV3
} P_skill;

typedef struct player {
  char name[NAME_LEN];
  int hp;
  int maxhp;
  int mp;
  int maxmp;
  int atk;
  int magic;
  int str;
  int agi;
  int luk;
  int lv;
  int exp;
  int sumexp;
  int nextexp;
  int leftoverexp;
  int gold;
  int badstatus;
  int physical_attack; //物理攻撃
  int gun_attack; //銃攻撃
  int fire;       //火炎攻撃
  int ice;        //氷結攻撃
  int elec;       //電撃攻撃
  int wave;       //衝撃攻撃
  int almighty;   //万能攻撃
  int death;      //呪殺攻撃
  int expel;      //破魔攻撃
  int poison;     //毒耐性
  int palyze;     //麻痺耐性
  int charm;      //魅了耐性
  int close;      //魔封耐性
  int stone;      //石化耐性
  int panic;      //混乱耐性
  int sleep;      //睡眠耐性
  int curse;      //呪い耐性
  double stage_clear;
  int playtime;
  int recover1;
  int cure_poison;
} Player;

typedef struct map {
  int x;   //x座標
  int y;   //y座標
  int walk_step;  //歩数
} Map;

typedef struct area {
  double dangeonId;  //ダンジョン識別ID
  int event1a;
  int event1b;
  int event1c;
  int event1d;
  int boss1;
  int event2a;
  int encount; //敵とエンカウントするか否か 0ならばエンカウントしない 1ならばエンカウント
} Area;

//パーティのセーブデータ
typedef struct save_data_players{
  char name[NAME_LEN];
  int hp;
  int maxhp;
  int mp;
  int maxmp;
  int atk;
  int magic;
  int str;
  int agi;
  int luk;
  int lv;
  int exp;
  int sumexp;
  int nextexp;
  int leftoverexp;
  int gold;
  int badstatus;
  int physical_attack; //物理攻撃
  int gun_attack; //銃攻撃
  int fire;       //火炎攻撃
  int ice;        //氷結攻撃
  int elec;       //電撃攻撃
  int wave;       //衝撃攻撃
  int almighty;   //万能攻撃
  int death;      //呪殺攻撃
  int expel;      //破魔攻撃
  int poison;     //毒耐性
  int palyze;     //麻痺耐性
  int charm;      //魅了耐性
  int close;      //魔封耐性
  int stone;      //石化耐性
  int panic;      //混乱耐性
  int sleep;      //睡眠耐性
  int curse;      //呪い耐性
  double stage_clear;
  int playtime;
  int recover1;
  int cure_poison;
  //２人目
  char name2[NAME_LEN];
  int hp2;
  int maxhp2;
  int mp2;
  int maxmp2;
  int atk2;
  int magic2;
  int str2;
  int agi2;
  int luk2;
  int lv2;
  int exp2;
  int sumexp2;
  int nextexp2;
  int leftoverexp2;
  int badstatus2;
  int physical_attack2; //物理攻撃
  int gun_attack2; //銃攻撃
  int fire2;       //火炎攻撃
  int ice2;        //氷結攻撃
  int elec2;       //電撃攻撃
  int wave2;       //衝撃攻撃
  int almighty2;   //万能攻撃
  int death2;      //呪殺攻撃
  int expel2;      //破魔攻撃
  int poison2;     //毒耐性
  int palyze2;     //麻痺耐性
  int charm2;      //魅了耐性
  int close2;      //魔封耐性
  int stone2;      //石化耐性
  int panic2;      //混乱耐性
  int sleep2;      //睡眠耐性
  int curse2;      //呪い耐性
  int stage_clear2;
  int recover1_2;
  int cure_poison_2;
  //３人目
  char name3[NAME_LEN];
  int hp3;
  int maxhp3;
  int mp3;
  int maxmp3;
  int atk3;
  int magic3;
  int str3;
  int agi3;
  int luk3;
  int lv3;
  int exp3;
  int sumexp3;
  int nextexp3;
  int leftoverexp3;
  int badstatus3;
  int physical_attack3; //物理攻撃
  int gun_attack3; //銃攻撃
  int fire3;       //火炎攻撃
  int ice3;        //氷結攻撃
  int elec3;       //電撃攻撃
  int wave3;       //衝撃攻撃
  int almighty3;   //万能攻撃
  int death3;      //呪殺攻撃
  int expel3;      //破魔攻撃
  int poison3;     //毒耐性
  int palyze3;     //麻痺耐性
  int charm3;      //魅了耐性
  int close3;      //魔封耐性
  int stone3;      //石化耐性
  int panic3;      //混乱耐性
  int sleep3;      //睡眠耐性
  int curse3;      //呪い耐性
  int stage_clear3;
  int recover1_3;
  int cure_poison_3;
} Save_data_players;

typedef struct items {
  int medicine;      //傷薬
  int lifestone;     //魔石
  int antipoison;    //アンタイポイズン
  int bead;          //宝玉
} Items;

typedef struct equip {
  int HpRing1;  //味方1人の最大HPを5%増加
  int isHpRing1;  //
  int MpRing1;  //味方1人の最大MPを5%増加
  int isMpRing1;
} Equip;

typedef struct save_data_items {
  int medicine;
  int lifestone;
  int antipoison;
  int bead;
} Save_data_items;

//rpg_save_load.c
<<<<<<< HEAD
void save_load(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *pEquip, Equip *p2Equip, Equip *p3Equip, int load);

void school_save(Player **st, Player **st2, Player **st3, P_skill **player_skill, P_skill **player_skill2, P_skill **player_skill3, Items **items, Equip **pEquip, Equip **p2Equip, Equip **p3Equip);
=======
void save_load(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *equip, int load);

void school_save(Player **st, Player **st2, Player **st3, P_skill **player_skill, P_skill **player_skill2, P_skill **player_skill3, Items **items, Equip **equip);
>>>>>>> origin/main

long long int getFileSize(const char *fileName);

void delete_savedata();

void display_condition(Player ***st);

void display_status(Player **st, Player **st2, Player **st3);

int school_command();

void buy_goods(Player ***st, Items ***items, int goods_number, int price);

void goods_shop(Player **st, Items **items);

<<<<<<< HEAD
void buy_equips(Player ***st, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, int equip_number, int price);

void equip_shop(Player **st, Player **st2, Player **st3, Equip **pEquip, Equip **p2Equip, Equip **p3Equip);
=======
void buy_equips(Player ***st, Equip ***equip, int equip_number, int price);

void equip_shop(Player **st, Player **st2, Player **st3, Equip **equip);
>>>>>>> origin/main

void prologue(void);

int check_player_name(Player **st);

void game_start(Player *player, Player *player2, Player *player3);

//rpg.c -> rpg_story.c
<<<<<<< HEAD
void game_story1(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *pEquip, Equip *p2Equip, Equip *p3Equip, Area *area, Enemy *enemy, Enemy *enemy1, Enemy *enemy2);
=======
void game_story1(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *equip, Area *area, Enemy *enemy, Enemy *enemy1, Enemy *enemy2);
>>>>>>> origin/main

void map_tutorial(void);

//HP,MP,STATUS全回復
void full_recover(Player **st, Player **st2, Player **st3);

<<<<<<< HEAD
void game_story2(Player *st, Player *st2, Player * st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *pEquip, Equip *p2Equip, Equip *p3Equip, Area *area, Enemy *zombie, Enemy *slime, Enemy *goblin_normal, Enemy *kobalt, Enemy *zombiedog, Enemy *onmoraki);

//map.c
void area1_map(Area **area, Player **st, Player **st2, Player **st3, P_skill **player_skill, P_skill **player_skill2, P_skill **player_skill3, Items **items, Equip **pEquip, Equip **p2Equip, Equip **p3Equip, Enemy **slime, Enemy **kobalt, Enemy **goblin);

void area2_map(Area **area, Player **st, Player **st2, Player **st3, P_skill **player_skill, P_skill **player_skill2, P_skill **player_skill3, Items **items, Equip **pEquip, Equip **p2Equip, Equip **p3Equip, Enemy **zombie, Enemy **slime, Enemy **goblin_normal, Enemy **kobalt, Enemy **zombiedog, Enemy **onmoraki);

void player_move(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Map *map, Area ***area, int area_data_line, int area_data_len, int area_data[area_data_line][area_data_len], int automap_area[area_data_line][area_data_len]);

//about menu function in map.c
void display_menu(Player ****st, Player ****st2, Player ****st3, P_skill ****player_skill, P_skill ****player_skill2, P_skill ****player_skill3, Items ****items, Equip ****pEquip, Equip ****p2Equip, Equip ****p3Equip, Map **map, Area ****area, int area_data_line, int area_data_len, int automap_area[area_data_line][area_data_len]);
=======
void game_story2(Player *st, Player *st2, Player * st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *equip, Area *area, Enemy *zombie, Enemy *slime, Enemy *goblin_normal, Enemy *kobalt, Enemy *zombiedog, Enemy *onmoraki);

//map.c
void area1_map(Area **area, Player **st, Player **st2, Player **st3, P_skill **player_skill, P_skill **player_skill2, P_skill **player_skill3, Items **items, Equip **equip, Enemy **slime, Enemy **kobalt, Enemy **goblin);

void area2_map(Area **area, Player **st, Player **st2, Player **st3, P_skill **player_skill, P_skill **player_skill2, P_skill **player_skill3, Items **items, Equip **equip, Enemy **zombie, Enemy **slime, Enemy **goblin_normal, Enemy **kobalt, Enemy **zombiedog, Enemy **onmoraki);

void player_move(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Map *map, Area ***area, int area_data_line, int area_data_len, int area_data[area_data_line][area_data_len], int automap_area[area_data_line][area_data_len]);

//about menu function in map.c
void display_menu(Player ****st, Player ****st2, Player ****st3, P_skill ****player_skill, P_skill ****player_skill2, P_skill ****player_skill3, Items ****items, Equip ****equip, Map **map, Area ****area, int area_data_line, int area_data_len, int automap_area[area_data_line][area_data_len]);
>>>>>>> origin/main

void menu_hp_graphycal_display(Player *****st, Player *****st2, Player *****st3);

void menu_mp_graphycal_display(Player *****st, Player *****st2, Player *****st3);

void menu_display_condition(Player *****st, int battle_display_condition_count);

void menu_player_effective(Player *******st);

void menu_player_status(Player ******st);

int menu_item_useselect(Player *******st, Player *******st2, Player *******st3, Items *******items);

void menu_use_items_effect(Player *******st, Player *******st2, Player *******st3, int item_number, int item_target);

void menu_item_use(Player ******st, Player ******st2, Player ******st3, Items ******items, int command);

void item_menu(Player *****st, Player *****st2, Player *****st3, Items *****items);

<<<<<<< HEAD
void equip_change(Player ******st, Equip ******pEquip, Equip ******p2Equip, Equip ******p3Equip);

void equip_menu(Player *****st, Player *****st2, Player *****st3, Equip *****pEquip, Equip *****p2Equip, Equip *****p3Equip);
=======
void equip_change(Player ******st, Equip ******equip);

void equip_menu(Player *****st, Player *****st2, Player *****st3, Equip *****equip);
>>>>>>> origin/main

void status_menu(Player *****st, Player *****st2, Player *****st3);

void map_menu(Map ***map, Area *****area, int area_data_line, int area_data_len, int automap_area[area_data_line][area_data_len]);

//map.c -> rpg_battle_same_enemy.c
<<<<<<< HEAD
void game_battle(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Enemy ***enemy, int encount_pattern);
=======
void game_battle(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Enemy ***enemy, int encount_pattern);
>>>>>>> origin/main

int player_attack(Player ****st, Enemy ****enemy, int *enemy_deadcount);

double enemy_attack(Player *****st, Player *****st2, Player *****st3, Enemy *****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double enemy_copy_attack(Player *****st, Player *****st2, Player *****st3, Enemy **enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

void enemy_data_copy(Enemy ****enemy, Enemy *enemy_copy);

int battle_escape(Player ****st);

void poison_effect(Player ****st);

void player_badstatus_recover(Player ****st);

void display_gameover(void);

//rpg_battle_encount_pattern5.c
<<<<<<< HEAD
void game_battle_encount_pattern5(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Enemy ***enemy, Enemy ***enemy1, int encount_pattern);
=======
void game_battle_encount_pattern5(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Enemy ***enemy, Enemy ***enemy1, int encount_pattern);
>>>>>>> origin/main

void enemy_full_recover5(Enemy ****enemy, Enemy ****enemy1);

//rpg_battle_encount_pattern6.c

<<<<<<< HEAD
void game_battle_encount_pattern6(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Enemy ***enemy, Enemy ***enemy1, Enemy ***enemy2, int encount_pattern);
=======
void game_battle_encount_pattern6(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Enemy ***enemy, Enemy ***enemy1, Enemy ***enemy2, int encount_pattern);
>>>>>>> origin/main

void enemy_full_recover6(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2);

//rpg_battle_encount_pattern7.c

<<<<<<< HEAD
void game_battle_encount_pattern7(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***pEquip, Equip ***p2Equip, Equip ***p3Equip, Enemy ***enemy, Enemy ***enemy1, Enemy ***enemy2, Enemy ***enemy3, int encount_pattern);
=======
void game_battle_encount_pattern7(Player ***st, Player ***st2, Player ***st3, P_skill ***player_skill, P_skill ***player_skill2, P_skill ***player_skill3, Items ***items, Equip ***equip, Enemy ***enemy, Enemy ***enemy1, Enemy ***enemy2, Enemy ***enemy3, int encount_pattern);
>>>>>>> origin/main

void enemy_full_recover7(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3);

//to check enemy_deadcount
int battle_error_enemydeadcount1(Enemy ****enemy);

int battle_error_enemydeadcount2(Enemy ****enemy, Enemy *enemy_copy1);

int battle_error_enemydeadcount3(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2);

int battle_error_enemydeadcount4(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, Enemy *enemy_copy3);

int battle_error_enemydeadcount5(Enemy ****enemy, Enemy ****enemy1);

int battle_error_enemydeadcount6(Enemy ****enemy, Enemy ****enemy1, Enemy****enemy2);

int battle_error_enemydeadcount7(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3);

//about battle turns in rpg_battle.c (playerの行動ごとに消費するターン数を計算)
double calculate_player_turn(double player_turn, double turn_decrease);

double calculate_enemy_turn(double enemy_turn, double turn_decrease);

void display_player_turn(Player ****st, double player_turn);

void display_enemy_turn(Enemy ****enemy, double enemy_turn);

void display_enemy_copy_turn(Enemy *enemy_copy1, double enemy_turn);

//rpg_battle_display.c (To show graphycal battle)
//select target to attack enemies
int player_normal_attack_target2(Enemy ****enemy, Enemy *enemy_copy1);

int player_normal_attack_target3(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2);

int player_normal_attack_target4(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, Enemy *enemy_copy3);

int player_normal_attack_target5(Enemy ****enemy, Enemy ****enemy1);

int player_normal_attack_target6(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2);

int player_normal_attack_target7(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3);

//display about players
void hp_graphycal_display(Player ****st, Player ****st2, Player ****st3);

void mp_graphycal_display(Player ****st, Player ****st2, Player ****st3);

void battle_display_condition(Player ****st, int battle_display_condition_count);

//display about enemies

//(敵１体)
void encount_pattern1_layout(Enemy ****enemy, int encount_pattern);
//(同じ敵２体)
void encount_pattern2_layout(Enemy ****enemy, Enemy *enemy_copy1, int encount_pattern);
//(同じ敵3体)
void encount_pattern3_layout(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, int encount_pattern);

void encount_pattern4_layout(Enemy ****enemy, Enemy *enemy_copy1, Enemy *enemy_copy2, Enemy *enemy_copy3, int encount_pattern);

void encount_pattern5_layout(Enemy ****enemy, Enemy ****enemy1, int encount_pattern);

void encount_pattern6_layout(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, int encount_pattern);

void encount_pattern7_layout(Enemy ****enemy, Enemy ****enemy1, Enemy ****enemy2, Enemy ****enemy3, int encount_pattern);

//battle_skill.c ( about players and enemies skills function and to decide enemies move pattern)
int player_ability(Player ****st, Player ****st2, Player ****st3, P_skill ****player_skill, int use_skill_count, int skill_target, int skill_user);

int skill_target_select(Player ****st, Player ****st2, Player ****st3, int use_skill_count);

int battle_player_skill_list(P_skill ****player_skill);

<<<<<<< HEAD
double enemy_attack_skill(Player ******st, Equip ******pEquip, Equip ******p2Equip, Equip ******p3Equip, Enemy ******enemy, int player_guard, int player_guard2, int player_guard3, int attack_skill_number);

int enemy_skill_target(Player ******st, Player ******st2, Player ******st3);

double use_enemy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****pEquip, Equip *****p2Equip, Equip *****p3Equip, Enemy *****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double use_enemy_copy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****pEquip, Equip *****p2Equip, Equip *****p3Equip, Enemy **enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double enemy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****pEquip, Equip ****p2Equip, Equip ****p3Equip, Enemy ****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double enemy_copy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****pEquip, Equip ****p2Equip, Equip ****p3Equip, Enemy *enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn);
=======
double enemy_attack_skill(Player ******st, Equip ******equip, Enemy ******enemy, int player_guard, int player_guard2, int player_guard3, int attack_skill_number);

int enemy_skill_target(Player ******st, Player ******st2, Player ******st3);

double use_enemy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****equip, Enemy *****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double use_enemy_copy_skill(Player *****st, Player *****st2, Player *****st3, Equip *****equip, Enemy **enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double enemy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****equip, Enemy ****enemy, int player_guard, int player_guard2, int player_guard3, double enemy_turn);

double enemy_copy_attack_pattern(Player ****st, Player ****st2, Player ****st3, Equip ****equip, Enemy *enemy_copy1, int player_guard, int player_guard2, int player_guard3, double enemy_turn);
>>>>>>> origin/main

//rpg_levelup.c ( check levelup and skills whatever players learned)
void player_skill_check(Player ******st, P_skill ******player_skill);

void status_lvup(Player *****st, P_skill *****player_skill);

void special_status_lvup(Player *****st);

void level_up(Player ****st, P_skill ****player_skill);

//item.c
int battle_item_useselect(Items *****items, Player *****st, Player *****st2, Player *****st3);

void use_items_effect(Player *****st, Player *****st2, Player *****st3, int item_number, int item_target);

int battle_item_use(Items ****items, Player ****st, Player ****st2, Player ****st3);

int item_drop_caluculate(int i, int drop_base, int drop_per);

void item_drop(Player ****st, Player ****st2, Player ****st3, Enemy ****enemy, Items ****items, int encount_pattern);

// about events which often happens on the map(dungeon)
void recover_event(Player **st);

#endif
