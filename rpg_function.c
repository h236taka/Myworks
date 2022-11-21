#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <wchar.h>
#include "rpg.h"

extern time_t start_time, end_time;
extern int play_time;

//主人公のbadstatus表示
void display_condition(Player ***st){

  if ( (**st) -> badstatus == GOOD ){
    printf("STATUS:GOOD\n");
  }
  else if ( (**st) -> badstatus == DEAD ){
    printf("STATUS:DEAD\n");
  }
  else if ( (**st) -> badstatus == POISON ){
    printf("STATUS:POISON\n");
  }
}

void display_status(Player **st, Player **st2, Player **st3){

  printf("パーティの能力を表示します\n");
  printf("\n");

  //主人公
  printf("%sの能力は・・・\n", (*st) -> name);
  printf("%s LV:%d EXP:%d NEXT EXP:%d\n", (*st) -> name, (*st) -> lv, (*st) -> sumexp, (*st) -> nextexp);
  printf("HP:%d/%d MP:%d/%d\n", (*st) -> hp, (*st) -> maxhp, (*st) -> mp, (*st) -> maxmp);

  display_condition(&st);

  printf("力:%d\n", (*st) -> atk);
  printf("魔:%d\n", (*st) -> magic);
  printf("体:%d\n", (*st) -> str);
  printf("速:%d\n", (*st) -> agi);
  printf("運:%d\n", (*st) -> luk);
  printf("GOLD:%d\n", (*st) -> gold);

  //２人目
  printf("%sの能力は・・・\n", (*st2) -> name);
  printf("%s LV:%d EXP:%d NEXT EXP:%d\n", (*st2) -> name, (*st2) -> lv, (*st2) -> sumexp, (*st2) -> nextexp);
  printf("HP:%d/%d MP:%d/%d\n", (*st2) -> hp, (*st2) -> maxhp, (*st2) -> mp, (*st2) -> maxmp);

  display_condition(&st2);

  printf("力:%d\n", (*st2) -> atk);
  printf("魔:%d\n", (*st2) -> magic);
  printf("体:%d\n", (*st2) -> str);
  printf("速:%d\n", (*st2) -> agi);
  printf("運:%d\n", (*st2) -> luk);

  //３人目
  printf("%sの能力は・・・\n", (*st3) -> name);
  printf("%s LV:%d EXP:%d NEXT EXP:%d\n", (*st3) -> name, (*st3) -> lv, (*st3) -> sumexp, (*st3) -> nextexp);
  printf("HP:%d/%d MP:%d/%d\n", (*st3) -> hp, (*st3) -> maxhp, (*st3) -> mp, (*st3) -> maxmp);

  display_condition(&st3);

  printf("力:%d\n", (*st3) -> atk);
  printf("魔:%d\n", (*st3) -> magic);
  printf("体:%d\n", (*st3) -> str);
  printf("速:%d\n", (*st3) -> agi);
  printf("運:%d\n", (*st3) -> luk);

  printf("\n");
}

void recover_event(Player **st){

  (*st) -> hp = (*st) -> maxhp;
  (*st) -> mp = (*st) -> maxmp;
  //printf("%sは全回復した!\n", (*st) -> name);
  //printf("%s HP:%d/%d MP:%d/%d\n", (*st) -> name, (*st) -> hp, (*st) -> maxhp, (*st) -> mp, (*st) -> maxmp);

}

//セーブデータのバイト数をreturn
//long 型よりもさらに大きな数を表現できる型
long long int getFileSize(const char *fileName){
  struct stat st;

  if ( stat(fileName, &st) != 0 ){
    return -1LL;
  }

  //ファイルであるかチェック
  if ( (st.st_mode & S_IFMT) != S_IFREG ){
    return -1LL;
  }

  return st.st_size;
}

void save_load(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, int load){
  int save_count, load_count, input, savedata_num, savedata_lv1, savedata_lv2, savedata_lv3, temp, hours, minutes;
  char savedata_name1[7], savedata_name2[7], savedata_name3[7];
  FILE *fp;
  const char *file;

  Save_data_players save_data_players;

  if ( load == 1 ){       //load
    do{
      load_count = 0;

      printf("\n");
      printf("何番のセーブデータを読み込みますか？\n");

      if ( ( fp = fopen( "save1.dat", "rb" ) ) == NULL ){
        //can't open file. So create new file
        fp = fopen( "save1.dat", "wb+");
        printf("1:\n");
      }
      else{
        if ( getFileSize( "save1.dat") == 0 ){                   //fileのbyteが０ならデータがない
          //printf("セーブデータを読み込めませんでした・・・\n");
          printf("1:\n");
        }
        else{
          fread(&save_data_players, sizeof(Save_data_players), 1, fp);
          strcpy(savedata_name1, save_data_players.name);
          savedata_lv1 = save_data_players.lv;

          //printf("playtime:%d\n", save_data_players.playtime);
          temp = save_data_players.playtime;
          //temp -= 1000;
          if ( temp >= 3600 ){
            hours = temp / 3600;
            minutes = temp % 3600 / 60;
          }
          else{
            hours = 0;
            printf("seconds:%d\n", temp);
            minutes = 0;
            while ( temp >= 60 ){
              temp -= 60;
              minutes++;
            }
          }

          if ( minutes < 10 ){
            printf("1:%s LV%d プレイ時間 %d:0%d\n", savedata_name1, savedata_lv1, hours, minutes);
            fclose(fp);
          }
          else{
            printf("1:%s LV%d プレイ時間 %d:%d\n", savedata_name1, savedata_lv1, hours, minutes);
            fclose(fp);
          }

        }
      }

      if ( ( fp = fopen( "save2.dat", "rb" ) ) == NULL ){
        //can't open file. So create new file
        fp = fopen( "save2.dat", "wb+");
        printf("2:\n");
      }
      else{
        if ( getFileSize( "save2.dat") == 0 ){                   //fileのbyteが０ならデータがない
            //printf("セーブデータを読み込めませんでした・・・\n");
            printf("2:\n");
        }
        else{
          fread(&save_data_players, sizeof(Save_data_players), 1, fp);
          strcpy(savedata_name2, save_data_players.name);
          savedata_lv2 = save_data_players.lv;

          temp = save_data_players.playtime;
          temp -= 1000;
          if ( temp >= 3600 ){
            hours = temp / 3600;
            minutes = temp % 3600 / 60;
          }
          else{
            hours = 0;
            minutes = temp / 60 % 60;
          }

          if ( minutes < 10 ){
            printf("1:%s LV%d プレイ時間 %d:0%d\n", savedata_name1, savedata_lv1, hours, minutes);
            fclose(fp);
          }
          else{
            printf("1:%s LV%d プレイ時間 %d:%d\n", savedata_name1, savedata_lv1, hours, minutes);
            fclose(fp);
          }

        }
      }

      if ( ( fp = fopen( "save3.dat", "rb" ) ) == NULL ){
        //can't open file. So create new file
        fp = fopen( "save3.dat", "wb+");
        printf("3:\n");
      }
      else{
        if ( getFileSize( "save3.dat") == 0 ){                   //fileのbyteが０ならデータがない
            //printf("セーブデータを読み込めませんでした・・・\n");
            printf("3:\n");
        }
        else{
          fread(&save_data_players, sizeof(Save_data_players), 1, fp);
          strcpy(savedata_name3, save_data_players.name);
          savedata_lv3 = save_data_players.lv;

          temp = save_data_players.playtime;
          temp -= 1000;
          if ( temp >= 3600 ){
            hours = temp / 3600;
            minutes = temp % 3600 / 60;
          }
          else{
            hours = 0;
            minutes = temp / 60 % 60;
          }

          if ( minutes < 10 ){
            printf("1:%s LV%d プレイ時間 %d:0%d\n", savedata_name1, savedata_lv1, hours, minutes);
            fclose(fp);
          }
          else{
            printf("1:%s LV%d プレイ時間 %d:%d\n", savedata_name1, savedata_lv1, hours, minutes);
            fclose(fp);
          }

        }
      }

      printf("1~3の数字を入力してください!\n");
      printf("セーブデータの読み込みを中止するときはnを入力してください!\n");
      input = _getch();

      if ( input == '1' ){
        //ファイル処理
        if ( ( fp = fopen( "save1.dat", "rb" ) ) == NULL ){
          printf("セーブデータがありません\n");
        }
        else{
          //セーブデータの読み込み
          if ( getFileSize( "save1.dat") == 0 ){                   //fileのbyteが０ならデータがない
              printf("セーブデータを読み込めませんでした・・・\n");
          }
          else{
            fread(&save_data_players, sizeof(Save_data_players), 1, fp);
            fclose(fp);
            load_count++;
          }
        }
      }
      else if ( input == '2' ){
        //ファイル処理
        if ( ( fp = fopen( "save2.dat", "rb" ) ) == NULL ){
          printf("セーブデータがありません\n");
        }
        else{
          //セーブデータの読み込み
          if ( getFileSize( "save2.dat") == 0 ){
              printf("セーブデータを読み込めませんでした・・・\n");
          }
          else{
            fread(&save_data_players, sizeof(Save_data_players), 1, fp);
            fclose(fp);
            load_count++;
          }
        }
      }
      else if ( input == '3' ){
        //ファイル処理
        if ( ( fp = fopen( "save2.dat", "rb" ) ) == NULL ){
          printf("セーブデータがありません\n");
        }
        else{
          //セーブデータの読み込み
          if ( getFileSize( "save3.dat") == 0 ){
              printf("セーブデータを読み込めませんでした・・・\n");
          }
          else{
            fread(&save_data_players, sizeof(Save_data_players), 1, fp);
            fclose(fp);
            load_count++;
          }
        }
      }
      else if ( input == 'n' ){
        printf("セーブデータのロードを中止します・・・\n");
        //st -> stage_clear = 0;
        return;
      }
      else{
        load_count = 0;
      }
    }while ( load_count == 0 );

    printf("SaveDataをLoadしています・・・・\n");
    sleep(2);
    printf("Loadが完了しました!\n");
    start_time = time(NULL);

    //主人公のセーブデータ
    strcpy(st -> name, save_data_players.name);
    st -> hp = save_data_players.hp;
    st -> maxhp = save_data_players.maxhp;
    st -> mp = save_data_players.mp;
    st -> maxmp = save_data_players.maxmp;
    st -> atk = save_data_players.atk;
    st -> magic = save_data_players.magic;
    st -> str = save_data_players.str;
    st -> agi = save_data_players.agi;
    st -> luk = save_data_players.luk;
    st -> lv = save_data_players.lv;
    st -> exp = save_data_players.exp;
    st -> sumexp = save_data_players.sumexp;
    st -> nextexp = save_data_players.nextexp;
    st -> gold = save_data_players.gold;
    st -> badstatus = save_data_players.badstatus;
    st -> physical_attack = save_data_players.physical_attack;
    st -> gun_attack = save_data_players.gun_attack;
    st -> fire = save_data_players.fire;
    st -> ice = save_data_players.ice;
    st -> elec = save_data_players.elec;
    st -> wave = save_data_players.wave;
    st -> almighty = save_data_players.almighty;
    st -> death = save_data_players.death;
    st -> expel = save_data_players.expel;
    st -> poison = save_data_players.poison;
    st -> palyze = save_data_players.palyze;
    st -> charm = save_data_players.charm;
    st -> close = save_data_players.close;
    st -> stone = save_data_players.stone;
    st -> panic = save_data_players.panic;
    st -> sleep = save_data_players.sleep;
    st -> curse = save_data_players.curse;
    st -> stage_clear = save_data_players.stage_clear;
    st -> playtime = save_data_players.playtime;
    player_skill -> recover1 = save_data_players.recover1;
    player_skill -> cure_poison = save_data_players.cure_poison;

    //２人目のセーブデータ
    strcpy(st2 -> name, save_data_players.name2);
    st2 -> hp = save_data_players.hp2;
    st2 -> maxhp = save_data_players.maxhp2;
    st2 -> mp = save_data_players.mp2;
    st2 -> maxmp = save_data_players.maxmp2;
    st2 -> atk = save_data_players.atk2;
    st2 -> magic = save_data_players.magic2;
    st2 -> str = save_data_players.str2;
    st2 -> agi = save_data_players.agi2;
    st2 -> luk = save_data_players.luk2;
    st2 -> lv = save_data_players.lv2;
    st2 -> exp = save_data_players.exp2;
    st2 -> sumexp = save_data_players.sumexp2;
    st2 -> nextexp = save_data_players.nextexp2;
    st2-> badstatus = save_data_players.badstatus2;
    st2 -> physical_attack = save_data_players.physical_attack2;
    st2 -> gun_attack = save_data_players.gun_attack2;
    st2 -> fire = save_data_players.fire2;
    st2 -> ice = save_data_players.ice2;
    st2 -> elec = save_data_players.elec2;
    st2 -> wave = save_data_players.wave2;
    st2 -> almighty = save_data_players.almighty2;
    st2 -> death = save_data_players.death2;
    st2 -> expel = save_data_players.expel2;
    st2 -> poison = save_data_players.poison2;
    st2 -> palyze = save_data_players.palyze2;
    st2 -> charm = save_data_players.charm2;
    st2 -> close = save_data_players.close2;
    st2 -> stone = save_data_players.stone2;
    st2 -> panic = save_data_players.panic2;
    st2 -> sleep = save_data_players.sleep2;
    st2 -> curse = save_data_players.curse2;
    st2 -> stage_clear = save_data_players.stage_clear2;
    player_skill2 -> recover1 = save_data_players.recover1_2;
    player_skill2 -> cure_poison = save_data_players.cure_poison_2;

    //３人目のセーブデータ
    strcpy(st3 -> name, save_data_players.name3);
    st3 -> hp = save_data_players.hp3;
    st3 -> maxhp = save_data_players.maxhp3;
    st3 -> mp = save_data_players.mp3;
    st3 -> maxmp = save_data_players.maxmp3;
    st3 -> atk = save_data_players.atk3;
    st3 -> magic = save_data_players.magic3;
    st3 -> str = save_data_players.str3;
    st3 -> agi = save_data_players.agi3;
    st3 -> luk = save_data_players.luk3;
    st3 -> lv = save_data_players.lv3;
    st3 -> exp = save_data_players.exp3;
    st3 -> sumexp = save_data_players.sumexp3;
    st3 -> nextexp = save_data_players.nextexp3;
    st3 -> badstatus = save_data_players.badstatus3;
    st3 -> physical_attack = save_data_players.physical_attack3;
    st3 -> gun_attack = save_data_players.gun_attack3;
    st3 -> fire = save_data_players.fire3;
    st3 -> ice = save_data_players.ice3;
    st3 -> elec = save_data_players.elec3;
    st3 -> wave = save_data_players.wave3;
    st3 -> almighty = save_data_players.almighty3;
    st3 -> death = save_data_players.death3;
    st3 -> expel = save_data_players.expel3;
    st3 -> poison = save_data_players.poison3;
    st3 -> palyze = save_data_players.palyze3;
    st3 -> charm = save_data_players.charm3;
    st3 -> close = save_data_players.close3;
    st3 -> stone = save_data_players.stone3;
    st3 -> panic = save_data_players.panic3;
    st3 -> sleep = save_data_players.sleep3;
    st3 -> curse = save_data_players.curse3;
    st3 -> stage_clear = save_data_players.stage_clear3;
    player_skill3 -> recover1 = save_data_players.recover1_3;
    player_skill3 -> cure_poison = save_data_players.cure_poison_3;

  }
  else{              //save
    sleep(2);
    printf("今の状態をSaveしますか?\n");
    printf("1:yes 2:no\n");
    printf("1か2を入力してください!\n");
    input = _getch();
    if ( input == '1' ){

      end_time = time(NULL);
      printf("start_time:%d\n", start_time);
      printf("end_time:%d\n", end_time);
      play_time = difftime(end_time, start_time);  //endとstartの差分
      printf("play_time:%d\n", play_time);
      //play_time = difftime(end_time, start_time);

      //プレイヤーデータの代入(主人公)
      strcpy(save_data_players.name, st -> name);
      save_data_players.hp = st -> hp;
      save_data_players.maxhp = st -> maxhp;
      save_data_players.mp = st -> mp;
      save_data_players.maxmp = st -> maxmp;
      save_data_players.atk = st -> atk;
      save_data_players.magic = st -> magic;
      save_data_players.str = st -> str;
      save_data_players.agi = st -> agi;
      save_data_players.luk = st -> luk;
      save_data_players.lv = st -> lv;
      save_data_players.exp = st -> exp;
      save_data_players.sumexp = st -> sumexp;
      save_data_players.nextexp = st -> nextexp;
      save_data_players.gold = st -> gold;
      save_data_players.badstatus = st -> badstatus;
      save_data_players.physical_attack = st -> physical_attack;
      save_data_players.gun_attack = st -> gun_attack;
      save_data_players.fire = st -> fire;
      save_data_players.ice = st -> ice;
      save_data_players.elec = st -> elec;
      save_data_players.wave = st -> wave;
      save_data_players.almighty = st -> almighty;
      save_data_players.death = st -> death;
      save_data_players.expel = st -> expel;
      save_data_players.poison = st -> poison;
      save_data_players.palyze = st -> palyze;
      save_data_players.charm = st -> charm;
      save_data_players.close = st -> close;
      save_data_players.stone = st -> stone;
      save_data_players.panic = st -> panic;
      save_data_players.sleep = st -> sleep;
      save_data_players.curse = st -> curse;
      save_data_players.stage_clear = st -> stage_clear;

      if ( save_data_players.playtime == 0 ){
        printf("First Play\n");
        save_data_players.playtime = play_time;
      }
      else{
        printf("Continue Play\n");
        save_data_players.playtime += play_time;
      }
      //save_data_players.playtime = play_time;
      save_data_players.recover1 = player_skill -> recover1;
      save_data_players.cure_poison = player_skill -> cure_poison;

      //２人目のセーブデータの書き込み
      strcpy(save_data_players.name2, st2 -> name);
      save_data_players.hp2 = st2 -> hp;
      save_data_players.maxhp2 = st2 -> maxhp;
      save_data_players.mp2 = st2 -> mp;
      save_data_players.maxmp2 = st2 -> maxmp;
      save_data_players.atk2 = st2 -> atk;
      save_data_players.magic2 = st2 -> magic;
      save_data_players.str2 = st2 -> str;
      save_data_players.agi2 = st2 -> agi;
      save_data_players.luk2 = st2 -> luk;
      save_data_players.lv2 = st2 -> lv;
      save_data_players.exp2 = st2 -> exp;
      save_data_players.sumexp2 = st2 -> sumexp;
      save_data_players.nextexp2 = st2 -> nextexp;
      save_data_players.badstatus2 = st2 -> badstatus;
      save_data_players.physical_attack2 = st2 -> physical_attack;
      save_data_players.gun_attack2 = st2 -> gun_attack;
      save_data_players.fire2 = st2 -> fire;
      save_data_players.ice2 = st2 -> ice;
      save_data_players.elec2 = st2 -> elec;
      save_data_players.wave2 = st2 -> wave;
      save_data_players.almighty2 = st2 -> almighty;
      save_data_players.death2 = st2 -> death;
      save_data_players.expel2 = st2 -> expel;
      save_data_players.poison2 = st2 -> poison;
      save_data_players.palyze2 = st2 -> palyze;
      save_data_players.charm2 = st2 -> charm;
      save_data_players.close2 = st2 -> close;
      save_data_players.stone2 = st2 -> stone;
      save_data_players.panic2 = st2 -> panic;
      save_data_players.sleep2 = st2 -> sleep;
      save_data_players.curse2 = st2 -> curse;
      //save_data_players.stage_clear2 = st2 -> stage_clear;
      save_data_players.recover1_2 = player_skill2 -> recover1;
      save_data_players.cure_poison_2 = player_skill2 -> cure_poison;

      //３人目のセーブデータの書き込み
      strcpy(save_data_players.name3, st3 -> name);
      save_data_players.hp3 = st3 -> hp;
      save_data_players.maxhp3 = st3 -> maxhp;
      save_data_players.mp3 = st3 -> mp;
      save_data_players.maxmp3 = st3 -> maxmp;
      save_data_players.atk3 = st3 -> atk;
      save_data_players.magic3 = st3 -> magic;
      save_data_players.str3 = st3 -> str;
      save_data_players.agi3 = st3 -> agi;
      save_data_players.luk3 = st3 -> luk;
      save_data_players.lv3 = st3 -> lv;
      save_data_players.exp3 = st3 -> exp;
      save_data_players.sumexp3 = st3 -> sumexp;
      save_data_players.nextexp3 = st3 -> nextexp;
      save_data_players.badstatus3 = st3 -> badstatus;
      save_data_players.physical_attack3 = st3 -> physical_attack;
      save_data_players.gun_attack3 = st3 -> gun_attack;
      save_data_players.fire3 = st3 -> fire;
      save_data_players.ice3 = st3 -> ice;
      save_data_players.elec3 = st3 -> elec;
      save_data_players.wave3 = st3 -> wave;
      save_data_players.almighty3 = st3 -> almighty;
      save_data_players.death3 = st3 -> death;
      save_data_players.expel3 = st3 -> expel;
      save_data_players.poison3 = st3 -> poison;
      save_data_players.palyze3 = st3 -> palyze;
      save_data_players.charm3 = st3 -> charm;
      save_data_players.close3 = st3 -> close;
      save_data_players.stone3 = st3 -> stone;
      save_data_players.panic3 = st3 -> panic;
      save_data_players.sleep3 = st3 -> sleep;
      save_data_players.curse3 = st3 -> curse;
      //save_data_players.stage_clear3 = st3 -> stage_clear;
      save_data_players.recover1_3 = player_skill3 -> recover1;
      save_data_players.cure_poison_3 = player_skill3 -> cure_poison;

      do{
        save_count = 0;
        printf("\n");
        printf("何番のセーブデータにセーブしますか？\n");
        printf("1:\n");
        printf("2:\n");
        printf("3:\n");
        printf("1~3の数字を入力してください!\n");
        printf("セーブを中止する場合はnを入力してください!\n");
        savedata_num = _getch();

        if ( savedata_num == '1' ){
          //ファイル処理
          if ( ( fp = fopen( "save1.dat", "wb" ) ) == NULL ){
            printf("セーブデータがありません\n");
          }
          else{
            //セーブデータの書き込み
            fwrite(&save_data_players, sizeof(Save_data_players), 1, fp);
            fclose(fp);
            save_count++;
          }
        }
        else if ( savedata_num  == '2' ){
          //ファイル処理
          if ( ( fp = fopen( "save2.dat", "wb" ) ) == NULL ){
            printf("セーブデータがありません\n");
          }
          else{
            //セーブデータの書き込み
            fwrite(&save_data_players, sizeof(Save_data_players), 1, fp);
            fclose(fp);
            save_count++;
          }
        }
        else if ( savedata_num == '3' ){
          //ファイル処理
          if ( ( fp = fopen( "save3.dat", "wb" ) ) == NULL ){
            printf("セーブデータがありません\n");
          }
          else{
            //セーブデータの書き込み
            fwrite(&save_data_players, sizeof(Save_data_players), 1, fp);
            fclose(fp);
            save_count++;
          }
        }
        else if ( savedata_num == 'n' ){
          printf("セーブを中止します・・・\n");
          return;
        }
        else{
          save_count = 0;
        }
      }while ( save_count == 0 );

      printf("Save中です・・・\n");
      sleep(2);
      printf("Saveが完了しました!\n");
      printf("\n");
      start_time = time(NULL);
    }
  }

}
