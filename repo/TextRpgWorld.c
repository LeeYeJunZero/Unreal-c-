#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MONSTERS 4
#define MAX_PLAYER_LEVEL 10

// ���� ����ü
typedef struct {
    char* name;
    int max_health;
    int health;
    int attack;
    int experience;
} Monster;

// �÷��̾� ����ü
typedef struct {
    int level;
    int health;
    int max_health;
    int attack;
    int experience;
} Player;

// ���� ���� �ʱ�ȭ �Լ�
Monster* init_monsters() {
    Monster* monsters = (Monster*)malloc(MAX_MONSTERS * sizeof(Monster));
    if (monsters == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);
    }

    // ���� ���� �ʱ�ȭ
    monsters[0].name = "�õ庹�� Ƽ��뿡�� ó���ϰ� �й��ع��� ������";
    monsters[0].max_health = 10;
    monsters[0].health = monsters[0].max_health;
    monsters[0].attack = 3;
    monsters[0].experience = 5;

    monsters[1].name = "�õ庹�� Ƽ��� ������ 46�� ���氣 ������ �索���� �ΰ��ִ� �����";
    monsters[1].max_health = 15;
    monsters[1].health = monsters[1].max_health;
    monsters[1].attack = 5;
    monsters[1].experience = 10;

    monsters[2].name = "����跲�������ΰ���������跲���Ǹ�";
    monsters[2].max_health = 50;
    monsters[2].health = monsters[2].max_health;
    monsters[2].attack = 8;
    monsters[2].experience = 20;

    monsters[3].name = " �������ī�����ް�տ��º��̱۷��긦��86���õ庹��Ƽ��롹";
    monsters[3].max_health = 40;
    monsters[3].health = monsters[3].max_health;
    monsters[3].attack = 14;
    monsters[3].experience = 31;

    return monsters;
}

// �÷��̾� ���� �ʱ�ȭ �Լ�
Player* init_player() {
    Player* player = (Player*)malloc(sizeof(Player));
    if (player == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1);
    }

    // �÷��̾� ���� �ʱ�ȭ
    player->level = 1;
    player->max_health = 20;
    player->health = player->max_health;
    player->attack = 5;
    player->experience = 0;

    return player;
}

// �޸� ���� �Լ�
void free_memory(Player* player, Monster* monsters) {
    free(player);
    free(monsters);
}

// ���� �Լ�
void battle(Player* player, Monster* monster) {
    printf("    %s�� �������ϴ�!\n", monster->name);

    while (1) {
        printf("\n  ����� ü��: %d / %d\n", player->health, player->max_health);
        printf("    %s�� ü��: %d / %d\n", monster->name, monster->health, monster->max_health);

        printf("    1. �����ϱ�     2. ȸ���ϱ�     3. ��������\n");

        int choice;
        scanf_s("%d", &choice);

        if (choice == 1) {
            // �÷��̾� ����
            int damage = rand() % 4 + 2; // 2~5 ������ ������ ����
            int critical = rand() % 10; // 10% Ȯ���� ũ��Ƽ��
            if (critical == 0) {
                damage += 6; // ũ��Ƽ�� �߻� �� +6�� ����
                printf("    ũ��Ƽ��!!!!! ");
            }
            printf("    ����� ���Ϳ��� %d�� ���ظ� �������ϴ�.\n", damage);
            monster->health -= damage;

            // ���Ͱ� ���� ����ִ��� Ȯ��
            if (monster->health <= 0) {
                printf("    ���� ����Ʈ�Ƚ��ϴ�!\n");
                player->experience += monster->experience;
                printf("    ���� ����: %d, ���� �������� �ʿ��� ����ġ: %d\n", player->level, (player->level * 10 - player->experience));
                break;
            }

            // ���� ����
            damage = 5; // ���� ���ݷ��� �����̶�� ����
            printf("    %s�� ��ſ��� %d�� ���ظ� �������ϴ�.\n", monster->name, damage);
            player->health -= damage;

            // �÷��̾ ���� ����ִ��� Ȯ��
            if (player->health <= 0) {
                printf("\n\n\n");
                printf("      ######  #######  ######     ##    ##  ########  ######  \n");
                printf("    ##    ## ##      ##    ##   ## ##   ##  ##       ##    ## \n");
                printf("    ##       ##      ##        ##   ##  ##  ##       ##       \n");
                printf("    ##       #####   ##       ##     ## ##  ######    ######  \n");
                printf("    ##       ##      ##       ######### ##  ##       ##    ## \n");
                printf("     ######  #######  ######  ##     ## ##  ########  ######  \n");
                printf("\n\n\n");
                printf("                    ���� ����\n");
                printf("                    ������������\n");
                printf("\n\n\n");
               
                break;
            }
        }
        else if (choice == 2) {
            // ȸ���ϱ�
            player->health += 5; // ȸ������ ����
            printf("    ����� ü���� ȸ���Ǿ����ϴ�. ���� ü��: %d / %d\n", player->health, player->max_health);
        }
        else if (choice == 3) {
            // ��������
            int flee = rand() % 10; // 70% Ȯ���� ������
            if (flee < 7) {
                printf("    ����� �����ϰ� �������� �����ƽ��ϴ�.\n");
                break;
            }
            else {
                printf("       ������ �����߽��ϴ�! ������ �����ϸ� �´°� ������ ��ġ���� �����Դϴ�.\n");
                int damage = 5; // ���� ���ݷ��� ����
                player->health -= damage;

                // �÷��̾ ���� ����ִ��� Ȯ��
                if (player->health <= 0) {
                    printf("    ����� �������� �й��߽��ϴ�.\n");
                    break;
                }
            }
        }
        else {
            printf("    �߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
        }
    }
}

// �÷��̾� ������ �Լ�
void level_up(Player* player) {
    player->level++;
    player->max_health += 2; // ������ �� �ִ� ü�� 2 ����
    player->health = player->max_health; // ���� ü���� �ִ� ü������ ����
    printf("���� ��! �ִ� ü���� �����߽��ϴ�. ���� ����: %d, �ִ� ü��: %d\n", player->level, player->max_health);
}

int main() {
    srand(time(NULL));

    printf("        #   #         #####      #         #           ######          \n");
    printf("        #   #         #          #         #          #      #   \n");
    printf("        #   #         #          #         #          #      #    \n");
    printf("        #####         #####      #         #          #      #     \n");
    printf("        #   #         #          #         #          #      #     \n");
    printf("        #   #         #          #         #          #      #      \n");
    printf("        #   #         #####      #######   ########    ######                    \n");
    printf("             Welcome to RPG World!                    \n");

    while (1) {
        printf("    1. ���� ����\n    2. ����\n");
        int choice;
        scanf_s("%d", &choice);
        fflush(stdin);

        if (choice == 1) {
            Player* player = init_player();
            Monster* monsters = init_monsters();

            int walk_count = 0;

            while (player->level <= MAX_PLAYER_LEVEL) {
                printf("\n  �÷��̾� ����: %d, ����ġ: %d\n", player->level, player->experience);

                Monster monster;
                if (player->level >= 7 && walk_count >= 7 && rand() % 10 < 3) {
                    monster = monsters[3];
                }
                else {
                    monster = monsters[rand() % 3];
                }
                battle(player, &monster);

                if (player->experience >= player->level * 10) { // �÷��̾ ����ġ�� ����� ȹ���Ͽ� ������ ���� ���� ��
                    level_up(player); // ������
                    printf("    ���� �������� �ʿ��� ����ġ: %d\n", (player->level * 10 - player->experience));
                }

                if (player->health <= 0) {
                    printf("    ���� ����\n");
                    break;
                }

                if (player->level > MAX_PLAYER_LEVEL) {
                    printf("    ���� �õ庹��Ƽ��븶�� ��ſ��� ����� ���� ������ ���������ϴ�..\n");
                    break;
                }

                walk_count++;

                printf("1. ��� �ȱ�\n2. �޽��ϱ�\n");
                scanf_s("%d", &choice);
                fflush(stdin);

                switch (choice) {
                case 1:
                    printf("    ����� �ѹ��ѹ� �Ȱ��ֽ��ϴ�...\n");
                    printf("    ��ġ�ѹ���");
                    break;
                case 2:
                    printf("    ����� �޽��� ���մϴ�.\n");
                    player->health += 10;
                    if (player->health > player->max_health) {
                        player->health = player->max_health;
                    }
                    printf("    ü���� ȸ���Ǿ����ϴ� ! ���� ü��: %d / %d\n", player->health, player->max_health);
                    break;
                default:
                    printf("    �߸��� �Է��Դϴ�.\n");
                    break;
                }
            }

            free_memory(player, monsters); // �޸� ����
        }
        else if (choice == 2) {
            printf("������ �����մϴ�.\n");
            break;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n");
        }
    }

    return 0;
}
