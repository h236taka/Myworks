#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <conio.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <mbctype.h>
#include <mbstring.h>
#include "rpg.h"

void prologue(void){
  printf("ここは私立元町学園・・・\n");
  sleep(1);
  printf("学生は平穏で怠惰な学園生活を送っていた\n");
  sleep(1);
  printf("しかし・・・\n");
  sleep(1);
}

int check_player_name(Player **st){
  int i, error_count, char_count;

  error_count = 0;
  for ( i = 0; (*st) -> name[i] != '\0'; i++ ){
    //エラー判定が正確ではないがまだ正しく判定してくれるものであるから採用
    if ( isalnum( (*st) -> name[i] ) == 0 ){
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }

    //以下未完のエラー処理
    /*if ( (*st) -> name[i] >= 0x40 && (*st) -> name[i] <= 0x7e){

    }
    else{
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }*/

    //全角文字（漢字）の１文字を判定
    /*if ( _ismbblead( (*st) -> name[i] ) != 0 ){
      if ( (*st) -> name[i] == '\0' ){
        break;
      }
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }
    else if ( _ismbbtrail( (*st) -> name[i] ) != 0 ){
      error_count++;
      printf("入力された文字がエラーです\n");
      char_count = 100;  //エラー値
      return char_count;
    }*/

  }

  if ( error_count == 0 ){
    // LC_CTYPE をネイティブロケールに変更
    if( setlocale( LC_CTYPE, "" ) == NULL ){
      fputs( "ロケールの設定に失敗しました。\n", stderr );
      exit( EXIT_FAILURE );
    }

    mbstate_t mbstate = {0};

    char_count = 0;
    for( i = 0; (*st) -> name[i] != '\0'; ++i ){
      size_t len1 = mbrlen( &(*st) -> name[i], 1, &mbstate );

      //printf("%zu\n", len1);

      if( len1 == (size_t)-1 ){
        // 有効な文字列ではない
        perror( "" );
        exit( EXIT_FAILURE );
      }
      if( len1 != (size_t)-2 ){
        // マルチバイト文字を構成するバイト列の途中でないなら、
        // １文字としてカウント
        char_count++;
      }
    }
    //ネイティブスケールをデフォルトに戻す
    setlocale( LC_CTYPE, "C" );
    //printf("len:%d\n", char_count);
  }

  return char_count;
}

void game_start(Player *st, Player *st2, Player *st3){
  int input, len, char_count;

  printf("ゲームスタート！！\n");
  sleep(1);

  //主人公
  do {
    printf("あなたの名前を入力してください(5文字以内かつ半角英数字)\n");
    scanf("%s", st -> name);
    /*len = (int)strlen( st -> name);
    //printf("len:%d\n", len);
    if ( len > 12 ){
      printf("名前の文字数がオーバーしています!\n");
    }*/
    char_count = check_player_name(&st);
  }while ( char_count > 5 );

  printf("名前は%sでよろしいですか？\n", st -> name);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください！\n");
  do {
    input = _getch();
    if ( input == '2' ){
      do{
        printf("あなたの名前を入力してください(5文字以内かつ半角英数字)\n");
        scanf("%s", st -> name);

        char_count = check_player_name(&st);
      } while ( char_count > 5 );
      setlocale( LC_CTYPE, "C" );
      printf("名前は%sでよろしいですか？\n", st -> name);
      printf("1:yes 2:no\n");
      printf("1か2を入力してください！\n");
      input = _getch();
    }
  } while( input != '1' );

  sleep(1);
  //2人目
  do {
    printf("２人目の名前を入力してください(5文字以内かつ半角英数字)\n");
    scanf("%s", st2 -> name);
    char_count = check_player_name(&st2);
  } while ( char_count > 5 );

  printf("名前は%sでよろしいですか？\n", st2 -> name);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください！\n");
  do {
    input = _getch();
    if ( input == '2' ){
      do{
        printf("２人目の名前を入力してください(5文字以内かつ半角英数字)\n");
        scanf("%s", st2 -> name);

        char_count = check_player_name(&st2);
      } while ( char_count > 5 );
      setlocale( LC_CTYPE, "C" );
      printf("名前は%sでよろしいですか？\n", st2 -> name);
      printf("1:yes 2:no\n");
      printf("1か2を入力してください！\n");
      input = _getch();
    }
  } while( input != '1' );

  sleep(1);

  do {
    printf("３人目の名前を入力してください(5文字以内かつ半角英数字)\n");
    scanf("%s", st3 -> name);
    char_count = check_player_name(&st3);
  } while ( char_count > 5 );

  printf("名前は%sでよろしいですか？\n", st3 -> name);
  printf("1:yes 2:no\n");
  printf("1か2を入力してください！\n");
  do {
    input = _getch();
    if ( input == '2' ){
      do{
        printf("３人目の名前を入力してください(5文字以内かつ半角英数字)\n");
        scanf("%s", st3 -> name);

        char_count = check_player_name(&st3);
      } while ( char_count > 5 );
      setlocale( LC_CTYPE, "C" );
      printf("名前は%sでよろしいですか？\n", st3 -> name);
      printf("1:yes 2:no\n");
      printf("1か2を入力してください！\n");
      input = _getch();
    }
  } while( input != '1' );

  sleep(1);

}

void map_tutorial(void){
  int input;

  do{
    printf("RPGパートにおけるダンジョン探索のチュートリアルを紹介します\n");
    sleep(2);
    printf("ダンジョンに入ると画面上には3Dダンジョン画面と2Dマップが表示されます\n");
    sleep(2);
    printf("ダンジョンを移動するにはカーソルキー(方向キー、矢印キー)を押してください\n");
    sleep(2);
    printf("また、ダンジョン探索時にメニュー画面を開きたいときはmを押すことでメニュー画面が開かれます\n");
    sleep(1);
    printf("最後にオートマッピング機能について説明します\n");
    sleep(1);
    printf("ダンジョンを進むと自動的にマップが記録されていきます\n");
    sleep(1);
    printf("マップはメニュー画面から見ることが出来て、マップの*は既に訪れた箇所、Pは現在地を表しています\n");
    sleep(1);

    printf("チュートリアルをもう一回見ますか?\n");
    printf("1.YES 2.NO\n");
    printf("1か2を入力してください\n");
    input = _getch();

  }while ( input == '1' );

  printf("\n");
}

void full_recover(Player **st, Player **st2, Player **st3){
  (*st) -> badstatus = GOOD;
  (*st2) -> badstatus = GOOD;
  (*st3) -> badstatus = GOOD;

  (*st) -> hp = (*st) -> maxhp;
  (*st) -> mp = (*st) -> maxmp;
  (*st2) -> hp = (*st2) -> maxhp;
  (*st2) -> mp = (*st2) -> maxmp;
  (*st3) -> hp = (*st3) -> maxhp;
  (*st3) -> mp = (*st3) -> maxmp;
}

<<<<<<< HEAD
void game_story1(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *pEquip, Equip *p2Equip, Equip *p3Equip, Area *area, Enemy *slime, Enemy *kobalt, Enemy *goblin){
=======
void game_story1(Player *st, Player *st2, Player *st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *equip, Area *area, Enemy *slime, Enemy *kobalt, Enemy *goblin){
>>>>>>> origin/main

  st -> hp = 30;
  st -> maxhp = 30;
  st -> mp = 7;
  st -> maxmp = 7;
  st -> atk = 1;
  st -> magic = 1;
  st -> str = 1;
  st -> agi = 1;
  st -> luk = 1;
  st -> lv = 1;
  st -> exp = 0;
  st -> sumexp = 0;
  st -> nextexp = 10;
  st -> leftoverexp = 0;
  st -> gold = 0;
  //badstatus = 0:正常
  //badstatus = 1:死亡
  //badstatus = 2:毒状態
  //badstatus = 3; 麻痺
  //badstatus = 4; 魅了
  //badstatus = 5; 魔封
  //badstatus = 6; 石化
  //badstatus = 7; 混乱
  //badstatus = 8; 睡眠
  //badstatus = 9; 呪い
  st -> badstatus = GOOD;
  //攻撃耐性
  st -> physical_attack = 100;
  st -> gun_attack = 100;
  st -> fire = 200;
  st -> ice = 50;
  st -> elec = 100;
  st -> wave = 100;
  st -> almighty = 100;
  st -> death = 100;
  st -> expel = 50;
  st -> poison = 100;
  st -> palyze = 100;
  st -> charm = 100;
  st -> close = 100;
  st -> stone = 100;
  st -> panic = 100;
  st -> sleep = 100;
  st -> curse = 100;
  st -> stage_clear = 0;

  st2 -> hp = 32;
  st2 -> maxhp = 32;
  st2 -> mp = 5;
  st2 -> maxmp = 5;
  st2 -> atk = 1;
  st2 -> magic = 1;
  st2 -> str = 1;
  st2 -> agi = 1;
  st2 -> luk = 1;
  st2 -> lv = 1;
  st2 -> exp = 0;
  st2 -> sumexp = 0;
  st2 -> nextexp = 10;
  st2 -> leftoverexp = 0;
  st2 -> gold = 0;
  st2 -> badstatus = GOOD;
  //攻撃耐性
  st2 -> physical_attack = 100;
  st2 -> gun_attack = 100;
  st2 -> fire = 50;
  st2 -> ice = 200;
  st2 -> elec = 100;
  st2 -> wave = 100;
  st2 -> almighty = 100;
  st2 -> death = 100;
  st2 -> expel = 50;
  st2 -> poison = 100;
  st2 -> palyze = 100;
  st2 -> charm = 100;
  st2 -> close = 100;
  st2 -> stone = 100;
  st2 -> panic = 100;
  st2 -> sleep = 100;
  st2 -> curse = 100;
  st2 -> stage_clear = 0;

  st3 -> hp = 25;
  st3 -> maxhp = 25;
  st3 -> mp = 10;
  st3 -> maxmp = 10;
  st3 -> atk = 1;
  st3 -> magic = 1;
  st3 -> str = 1;
  st3 -> agi = 1;
  st3 -> luk = 1;
  st3 -> lv = 1;
  st3 -> exp = 0;
  st3 -> sumexp = 0;
  st3 -> nextexp = 10;
  st3 -> leftoverexp = 0;
  st3 -> gold = 0;
  //badstatus = 0:正常
  //badstatus = 1:死亡
  //badstatus = 2:毒状態
  st3 -> badstatus = GOOD;
  //攻撃耐性
  st3 -> physical_attack = 100;
  st3 -> gun_attack = 100;
  st3 -> fire = 100;
  st3 -> ice = 100;
  st3 -> elec = 50;
  st3 -> wave = 200;
  st3 -> almighty = 100;
  st3 -> death = 100;
  st3 -> expel = 50;
  st3 -> poison = 100;
  st3 -> palyze = 100;
  st3 -> charm = 100;
  st3 -> close = 100;
  st3 -> stone = 100;
  st3 -> panic = 100;
  st3 -> sleep = 100;
  st3 -> curse = 100;
  st3 -> stage_clear = 0;

  /*printf("放課後・・・\n");
  sleep(2);
  printf("%s「%s、どっか遊びに行かない？」\n", st2 -> name, st -> name);
  sleep(2);
  printf("%s「自分も行きたい！」\n", st3 -> name);
  sleep(2);
  printf("%s「じゃあ、３人でゲーセン行こう！」\n", st2 -> name);
  sleep(2);
  printf("その時・・・\n");
  sleep(2);
  printf("窓から見える外の景色が一変した\n");
  sleep(2);
  printf("%s「何か雰囲気変わった？」\n", st3 -> name);
  sleep(2);
  printf("%s「確かに、%sも何か感じる？」\n", st2 -> name, st -> name);
  sleep(2);
  printf("\a");
  printf("クラスメイト「キャー－」\n");
  sleep(1);
  printf("クラスメイト「廊下に化け物が・・・」\n");
  sleep(2);
  printf("\a");
  printf("%s %s「廊下に行ってみよう！」\n", st2 -> name, st3 -> name);
  sleep(1);
  printf("3人は廊下へと向かった・・・\n");
  sleep(2);
  printf("ここからRPGパートが始まります\n");
  printf("その前に３人のステータスを表示します\n");
  sleep(2);*/
  display_status(&st, &st2, &st3);

  printf("\n");
  sleep(2);

  map_tutorial();
  sleep(1);
<<<<<<< HEAD
  area1_map(&area, &st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip, &slime, &kobalt, &goblin);
=======
  area1_map(&area, &st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &equip, &slime, &kobalt, &goblin);
>>>>>>> origin/main

  sleep(2);

  printf("\a");
  //printf("---STAGE1 CLEARED!!---\n");
  st -> stage_clear = 1;

  full_recover(&st,&st2,&st3);

  //printf("st:HP:%d\n", st -> hp);
  //printf("st2:HP:%d\n", st2 -> hp);
  //printf("st3:HP:%d\n", st3 -> hp);

}

<<<<<<< HEAD
void game_story2(Player *st, Player *st2, Player * st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *pEquip, Equip *p2Equip, Equip *p3Equip, Area *area, Enemy *zombie, Enemy *slime, Enemy *goblin_normal, Enemy *kobalt, Enemy *zombiedog, Enemy *onmoraki){
=======
void game_story2(Player *st, Player *st2, Player * st3, P_skill *player_skill, P_skill *player_skill2, P_skill *player_skill3, Items *items, Equip *equip, Area *area, Enemy *zombie, Enemy *slime, Enemy *goblin_normal, Enemy *kobalt, Enemy *zombiedog, Enemy *onmoraki){
>>>>>>> origin/main
  int input;
  int tmp;

  if ( st -> stage_clear == 1 ){
    /*printf("%s達は渡り廊下での戦いを終えて教室に戻ってきた。\n", st -> name);
    sleep(2);
    printf("クラスメイト「何が何だか分からないけど、凄かったよ!」\n");
    sleep(2);
    printf("クラスメイト「そういえば、校長先生が%s達を呼んでいたよ。」\n", st -> name);
    sleep(2);
    printf("%s「校長室に行ってみよう!」\n", st2 -> name);
    sleep(2);

    printf("校長室...\n");
    sleep(2);
    printf("校長先生「来てくれたか！」\n");
    sleep(2);
    printf("校長「単刀直入に言おう、君たちに何とかしてほしいんだ。」\n");
    sleep(2);
    printf("校長「学校からも出られないし、インターネットも使えないから連絡も取れない。」\n");
    sleep(2);
    printf("校長「電気や水道は使えるが、不便極まりない事には変わりない。」\n");
    sleep(2);
    printf("校長「どうやら君たちは凄い力を手に入れて、悪魔どもと戦う術を持っているそうだね」\n");
    sleep(2);
    printf("校長「その力で我々を元の世界に戻してくれ！ 引き受けてくれるね？」\n");

    do{
      printf("校長のお願いを引き受けますか？\n");
      printf("1. YES 2. NO\n");
      input = _getch();

      if ( input == '1' ){
        //OK
      }
      else if ( input == '2' ){
        printf("校長「君たちしかいないんだ！」\n");
        printf("\n");
      }

    }while ( input != '1' );

    sleep(2);
    printf("校長「ありがとう！」\n");
    sleep(2);
    printf("校長「早速だが、君たちには図書館の解放を行ってほしい！」\n");
    sleep(2);
    printf("校長「宜しく頼むよ。」\n");
    sleep(2);*/
  }

  full_recover(&st,&st2,&st3);

  do{
    sleep(1);
    printf("\n");
    printf("%sはどうしますか?\n", st -> name);
    input = school_command();

    if ( input == '1' ){
      printf("%s達は保健室へ行った...\n", st -> name);
      sleep(1);
      do{
        printf("\n");
        printf("---保健室---\n");
        printf("1.回復する\n");
        printf("2.道具を買う\n");
        printf("3.保健室を出る\n");
        input = _getch();

        if ( input == '1' ){
          sleep(1);
          full_recover(&st,&st2,&st3);
          printf("%s達は全回復した！\n", st -> name);
        }
        else if ( input == '2' ){
          goods_shop(&st,&items);
        }
      } while ( input != '3' );

    }
    else if ( input == '2' ){
      printf("%s達は美術室へ行った...\n", st -> name);
      sleep(1);
      do {
        printf("\n");
        printf("---美術室---\n");
        printf("1.装備を購入する\n");
        printf("2.装備を売却する\n");
        printf("3.美術室を出る\n");
        input = _getch();

        if ( input == '1' ){
<<<<<<< HEAD
          equip_shop(&st,&st2,&st3,&pEquip,&p2Equip,&p3Equip);
        }

      } while ( input != '3' );

=======
          equip_shop(&st,&st2,&st3,&equip);
        }

      } while ( input != '3' );
      
>>>>>>> origin/main
    }
    else if ( input == '3' ){

    }
    else if ( input == '4' ){
<<<<<<< HEAD
      area2_map(&area, &st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip, &zombie,&slime,&goblin_normal,&kobalt,&zombiedog,&onmoraki);
=======
      area2_map(&area, &st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &equip, &zombie,&slime,&goblin_normal,&kobalt,&zombiedog,&onmoraki);
>>>>>>> origin/main
    }
    else if ( input == '5' ){
      exit(EXIT_SUCCESS);
    }
    else if ( input == '6' ){
      st -> stage_clear = 1.1;
<<<<<<< HEAD
      school_save(&st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &pEquip, &p2Equip, &p3Equip);
=======
      school_save(&st, &st2, &st3, &player_skill, &player_skill2, &player_skill3, &items, &equip);
>>>>>>> origin/main
    }

  } while ( area -> event2a == 0 );

  printf("\a");
  printf("---STAGE2 CLEARED!!---\n");
  st -> stage_clear  = 2;

  st -> hp = st -> maxhp;
  st -> mp = st -> maxmp;

}
