#include <stdio.h>
#include <stdlib.h>

struct Player {
    int x;
    int y;
    int hp;
    int atk;
    int exp;
    int lv;
    int vk;
    int st;
    int jst;
};

struct Enemy {
    int hp;
    int atk;
};

int map[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
};
int rows = 3;
int cols = 3;

void exit_game() {
    printf("Bye~\n");
    exit(0);
}

void v_sheng() {
    printf("你确定要用金石头吗？1:要，其他:不要\n");
    int flag;
    scanf("%d",&flag);
    if (flag == 1) {
        printf("感谢你的游玩，我们下次再见~\n");
        printf("程序员：秋风，提供灵感：白纸编程\n");
        exit_game();
    }
}

struct Enemy create_enemy(int hp, int atk) {
    struct Enemy enemy;
    enemy.hp = hp;
    enemy.atk = atk;
    return enemy;
}

void on_fight_victory(struct Player *player) {
    int exp = 10;
    player->exp += exp;
    printf("你战胜了怪物，获得了%d经验值\n", exp);
    // 检查是否可以升级
    int upgrade_exp = 3; // 升1级需要的经验值
    if(player->exp >= upgrade_exp) {
        // 能够连续升级的次数
        int lv = player->exp / upgrade_exp;
        // 升级后剩余的经验值
        int left = player->exp % upgrade_exp;
        player->lv += lv;
        player->exp = left;
        printf("你升级了，当前等级%d，剩余经验%d\n",player->lv,player->exp);
    }
}

void player_fight_enemy(struct Player *player, struct Enemy *enemy) {
    // 多回合战斗
    while (player->hp > 0 && enemy->hp > 0) {
        enemy->hp -= player->atk;
        printf("怪物受到了你的攻击，减少了%d生命值，怪物还剩%d生命值\n", player->atk,enemy->hp);
        player->hp -= enemy->atk;
        printf("你受到了怪物的攻击，减少了%d生命值，你还剩%d生命值\n", enemy->atk,player->hp);
    }
    // 如果是主角生命值不足，游戏结束
    if (player->hp <= 0) {
        printf("你打不过怪物，游戏结束\n");
        exit_game();
    }
    // 怪物生命值不足，战斗胜利
    if (enemy->hp <= 0) {
        on_fight_victory(player);
    }
}

void map_cell_1() {
    printf("这是一个热闹平和的小村庄\n");
    printf("村民告诉你，村子右边出现了一只史莱姆，下面出现了一只野兽，对了，你能帮我捡4个金石头吗？在2,2的地方可以捡到石头！每两个石头可以拿到一个金石头。我会报答你的!\n");
}

void map_cell_c() {
    printf("你需要捡4个金石头吗，在2,2的地方可以捡到石头！每两个石头可以拿到一个金石头。\n");
}

int cell_2_fought = 0;
void map_cell_2(struct Player *player) {
    if(cell_2_fought == 1){
        printf("这是村口东部的小树林，这里刚才似乎发生了一场激烈的战斗\n");
        return ;
    }
    printf("这是村口东部的小树林，有一只史莱姆在悠闲的吃草\n");
    printf("是否攻击它？1:攻击, 其他:取消攻击\n");
    int flag;
    scanf("%d", &flag);
    if (flag == 1) {
        printf("你攻击了史莱姆\n");
        // 让主角和史莱姆战斗起来
        struct Enemy slime = create_enemy(6, 1);
        player_fight_enemy(player, &slime);
        cell_2_fought = 1;
    }
}

void map_cell_3() {
    printf("这里是一块麦田\n");
    printf("有一个人在这里种田\n");
    printf("那个人告诉你，麦田左边出现了一只野兽\n");
}

int cell_4_fought = 0;
void map_cell_4(struct Player *player) {
    if(cell_4_fought == 1){
        printf("这是一座桥，这里刚才似乎发生了一场激烈的战斗\n");
        return ;
    }

    printf("这是一座桥，有一只野兽在睡觉\n");

    printf("它发现了你，是否攻击它？1:攻击, 其他:取消攻击（逃跑）\n");
    int flag_4;
    scanf("%d", &flag_4);
    if (flag_4 == 1) {
        printf("你攻击了野兽\n");
        // 让主角和野兽战斗起来
        struct Enemy slime = create_enemy(10, 2);
        player_fight_enemy(player, &slime);
        cell_2_fought = 1;
    }
}

void map_cell_5() {
    printf("这里是一座小镇\n");
    printf("一个人告诉你，小镇的上面出现了一只史莱姆，左边出现了一只野兽\n");
}

void map_cell_6(struct Player *player) {
    printf("这里是一座森林\n");
    printf("一个人告诉你，你要血吗？1:要, 其他:不要\n");
    int flag,vc,vr,vre;
    vr = 0;
    vre = 0;
    scanf("%d", &flag);
    if (flag == 1) {
        vc = player->hp;
        if (player->hp >10) {
            vre = 1;
            player->hp = 10;
            printf("那个人说不行，并扣了你%d生命值,你现在只有10生命值了\n",vc - player->hp);
            vr = 1;
        }

        if (vre == 0) {
            player->hp += 1;
            printf("你增加了1生命值,你还剩%d生命值\n",player->hp);
        }

        if (vr == 0) {
            player->hp += 3;
            printf("你增加了%d生命值，你还剩%d生命值\n",player->hp - vc,player->hp);
        
        }
    }
}

void map_cell_7() {
    printf("这里是一条马路\n");
    printf("一个人在车上告诉你，这条马路的上面出现了一只史莱姆\n");
}

void map_cell_8() {
    printf("这里是一条高速公路\n");
    printf("一个人告诉你，这条高速公路的右边出现了一个刷怪处，哎呀不讲了，要被罚款了！我走了\n");
}

void sheng_li() {
    printf("一位村民跑过来说谢谢你，这个给你\n");
    printf("你获得了[金石头]，你要用吗，金石头使用后可以让游戏胜利,1:要，其他:不要\n");
    int flag;
    scanf("%d",&flag);
    if (flag == 1) {
        v_sheng();
    }
}

void map_cell_9(struct Player *player) {
    printf("这是一个刷怪处，有一个刷怪笼\n");
    printf("是否攻击刷怪笼？1:攻击, 其他:取消攻击\n");
    int flag;
    scanf("%d", &flag);
    if (flag == 1) {
        printf("你攻击了刷怪笼，刷怪笼产出了一大堆怪物\n");
        // 让主角和刷怪笼产出的怪物们战斗起来
        struct Enemy slime = create_enemy(15, 2);
        player_fight_enemy(player, &slime);
        player->hp += 3;
        printf("你增加了3生命值，你还剩%d生命值\n",player->hp);
        player->vk += 1;
        if (player->vk >= 2) {
            player->vk = player->vk - 2;
            player->st += 1;
            printf("你获得了一块金石头，你还要%d个石头才能获得村民的奖励\n",4 - player->st);
            if (player->st >= 4) {
                player->jst = 1;
                sheng_li();
            }
        }
    }
}

void on_map_cell(struct Player *player) {
    int cell = map[player->y][player->x];
    switch (cell) {
        case 1: map_cell_1(); break;
        case 2: map_cell_2(player); break;
        case 3: map_cell_3(); break;
        case 4: map_cell_4(player); break;
        case 5: map_cell_5(); break;
        case 6: map_cell_6(player); break;
        case 7: map_cell_7(); break;
        case 8: map_cell_8(); break;
        case 9: map_cell_9(player); break;
        default:
            printf("这个地方什么也没有~\n");
            break;
    }
}

void jz(struct Player *player) {
    if (player->jst == 1) {
        v_sheng();
    } else {
        printf("你没有金石头\n");
    }
}

void move_player(struct Player *player, int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows) {
        printf("已经到达地图边界，你无法继续朝这个方向移动\n");
        return;
    }
    player->x = x;
    player->y = y;
    printf("你来到了坐标(%d, %d)的位置\n", player->x, player->y);
    // 当玩家移动到这个地方的时候，执行on_map_cell方法
    on_map_cell(player);
}

void listen_move(struct Player *player) {
    printf("请输入要前进的方向（8:向上、4:向左、5:向下、6:向右）：\n");
    int dir;
    scanf("%d", &dir);
    int x = player->x;
    int y = player->y;

    switch (dir) {
        case 8:
            printf("你选择了朝上方走\n");
            move_player(player, x, y - 1);
            break;
        case 4:
            printf("你选择了朝左边走\n");
            move_player(player, x - 1, y);
            break;
        case 5:
            printf("你选择了朝下方走\n");
            move_player(player, x, y + 1);
            break;
        case 6:
            printf("你选择了朝右边走\n");
            move_player(player, x + 1, y);
            break;
        default:
            printf("无效输入\n");
            return;
    }
}

void listen_input(struct Player *player) {
    printf("请输入要执行的操作,1:查看四周,2:移动,3:使用金石头,9:退出游戏\n");
    int type;
    scanf("%d", &type);
    switch (type) {
    case 1: on_map_cell(player); break;
    case 2: listen_move(player); break;
    case 3: jz(player); break;
    case 9: exit_game(); break;
    
    default:
        break;
    }
}

struct Player init_player() {
    struct Player player;
    player.x = 0; 
    player.y = 0;
    player.hp = 10;
    player.atk = 5;
    player.exp = 0;
    player.lv = 1;
    player.vk = 0;
    player.st = 0;
    player.jst = 0;
    return player;
}

int main() {
    struct Player player = init_player();
    map_cell_c();
    while (1) {
        listen_input(&player);
    }
    return 0;
}
