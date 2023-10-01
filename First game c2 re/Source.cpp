#include <iostream>
#include <conio.h>
#include <Windows.h>

#define MAP_SIZE   100
#define PLAYER	   '@'
#define CLIFF	   'O'
#define RIVER      'R'
#define PORTAL     'P'
#define COIN	   'c'
#define EMPTY_1	   ' '
#define EMPTY_2    '='
#define HEALTH     'h'
#define TRAP       '0'
#define ENEMY      'e'
#define SHOP       's'
#define DOOR       'd'
#define SKEY       'k'
#define GAME       'g'
#define LOMBARD    'l'

struct Character
{
	int x, y, lives, coins, key;
	char name[30];
};

char map[MAP_SIZE][MAP_SIZE];
Character player = { 1, 1, 5, 0, 0, "Игрок" };
Character enemies[100];
int enemy_count = 0;
int level = 0;
int difficulty = 2;
int damage = 1;
int maxlives = 3;
const int ESC = 27;

HANDLE hConsole;

int start()
{
	SetConsoleTextAttribute(hConsole, 15);
	char v;
	printf("Чтобы пройти обучение нажмите 1\n");
	v = _getch();
	switch (v)
	{
	case '1':
		printf("Обозначения:\n");
		printf("Игрок - '@'\n");
		printf("Враги - 'е'\n");
		printf("Монеты - 'с'\n");
		printf("Аптечка - 'h'\n");
		printf("Магазин - 's'\n");
		printf("Портал - 'р'\n");
		printf("Магазин ключей - 'k'\n");
		printf("Мини-игра - 'g'\n");
		printf("Дверь - 'd'\n");
		printf("Ломбард - 'l'\n\n");
		printf("Также далее вам предложат выбрать уровень сложности, всего их три:\n");
		printf("Лёгкий (в начале у вас 5 жизней и враги видят вас через 3 клетки)\n");
		printf("Средний (в начале у вас 4 жизни и враги видят вас через 5 клеток)\n");
		printf("Сложный (в начале у вас 3 жизни и враги видят вас через 7 клеток)\n");
		system("pause");
	default:
		break;
	}
	system("cls");
	printf("Нажмите 1 - чтобы выбрать лёгкий уровень сложность, 2 - чтобы выбрать средний уровень сложности, 3 - чтобы выбрать сложный уровень сложности\n");
	v = _getch();
	switch (v)
	{
	case '1':
		difficulty = 1;
		printf("Вы выбрали лёгкий уровень сложности\n");
		break;
	case '2':
		difficulty = 2;
		printf("Вы выбрали средний уровень сложности\n");
		break;
	case '3':
		difficulty = 3;
		printf("Вы выбрали сложный уровень сложности\n");
		break;
	default:
		break;
	}
	system("pause");
	system("cls");
	return 0;
}

int lombard()
{
	int kurs = 0;
	int cost = 0;
	char v1;
	char v2;
	char v3;
	printf("Вы вошли в ломбард\n");
	printf("Здесь вы можете обменять своё оружие и жизни на деньги\n");
	printf("Нажмите 1 чтобы продать оружие (или броню) или нажмите 2 чтобы обменять жизни\n");
	v1 = _getch();
	switch (v1)
	{
	case '1':
		printf("Нажмите 1 чтобы продать кинжал, нажмите 2 чтобы продать мечь, нажмите 3 чтобы продать лук, нажмите 4 чтобы продать броню\n");
		v2 = _getch();
		switch (v2)
		{
		case '1':
			printf("Нажмите 1 чтобы продать кинжал за 4 монеты\n");
			v3 = _getch();
			switch (v3)
			{
			case '1':
				if (damage == 3)
				{
					printf("Вы продали кинжал и получили 4 монеты\n");
					player.coins += 4;
					damage = 1;
					system("pause");
					return 0;
				}
				else
				{
					printf("У вас нет кинжала\n");
					system("pause");
					return 0;
				}
			default:
				return 0;
			}
		case '2':
			printf("Нажмите 1 чтобы продать мечЬ за 10 монет\n");
			v3 = _getch();
			switch (v3)
			{
			case '1':
				if (damage == 5)
				{
					printf("Вы продали кинжал и получили 10 монет\n");
					player.coins += 10;
					damage = 1;
					system("pause");
					return 0;
				}
				else
				{
					printf("У вас нет меча\n");
					system("pause");
					return 0;
				}
			default:
				return 0;
			}
		case '3':
			printf("Нажмите 1 чтобы продать автомат за 15 монет\n");
			v3 = _getch();
			switch (v3)
			{
			case '1':
				if (damage == 3)
				{
					printf("Вы продали автомат и получили 15 монет\n");
					player.coins += 15;
					damage = 1;
					system("pause");
					return 0;
				}
				else
				{
					printf("У вас нет автомата\n");
					system("pause");
					return 0;
				}
			default:
				return 0;
			}
		case '4':
			printf("Нажмите 1 чтобы продать броню за 13 монет\n");
			v3 = _getch();
			switch (v3)
			{
			case '1':
				if (damage == 7)
				{
					printf("Вы продали кинжал и получили 13 монет\n");
					player.coins += 13;
					maxlives = 3;
					system("pause");
					return 0;
				}
				else
				{
					printf("У вас нет брони\n");
					system("pause");
					return 0;
				}
			default:
				return 0;
			}
		}
	case '2':
		kurs = rand() % 5;
		if (kurs == 0)
			cost = 2;
		if (kurs == 1)
			cost = 3;
		if (kurs == 2)
			cost = 4;
		if (kurs == 3)
			cost = 5;
		if (kurs == 4)
			cost = 8;
		printf("Курс жизни - деньги сейчас составляет %i монет за одну жизнь\n", cost);
		printf("Нажмите 1 чтобы обменять жизнь на деньги\n");
		v3 = _getch();
		switch (v3)
		{
		case '1':
			if (player.lives < 2)
			{
				printf("У вас не достаточно жизней\n");
				system("pause");
				return 0;
			}
			printf("Вы обменяли жизни на монеты\n");
			player.coins += cost;
			player.lives--;
			system("pause");
			return 0;
		}
	}
	return 0;
}

int game()
{
	char vib;
	int mon = 0;
	int vmon = 0;
	int num_1 = 0;
	int num_2 = 0;
	int bone_11 = 0;
	int bone_21 = 0;
	int sbone_1 = 0;
	int bone_12 = 0;
	int bone_22 = 0;
	int sbone_2 = 0;
	system("cls");
	printf("Вы вошли в Таверну\n");
	while (player.coins > 0)
	{
		printf("Есть 2 режима игры\nПервый: Два игрока бросают кости, у кого выпадает большее число тот и выигрывает\nВторой: Вы выбираете 2 числа и бросаете кости, если те числа которые вы загадали выпадают вы выигрываете в 3 раза больше монет чем поставили (можно поставить определённое количество монет)\n");
		vib = _getch();
		switch (vib)
		{
		case '1':
			system("cls");
			printf("Вы выбрали 1 режим игры\n");
			printf("Правила игры: Вы выбираете кол-во монет, затем вы и другой игрок бросаете кости, если вам выпадает большее число, то вы выигрываете в 2 раза больше монет\n");
			printf("Выберите кол-во монет, на коорые будете играть\n");
			scanf_s("%i", &mon);
			if (mon > player.coins)
			{
				printf("У вас не достаточно монет\n");
				system("pause");
				system("cls");
				return 0;
			}
			bone_11 = rand() % 6 + 1;
			bone_21 = rand() % 6 + 1;
			printf("Вашему противнику выпали числа %i и %i\n", bone_11, bone_21);
			sbone_1 = bone_11 + bone_21;
			system("pause");
			bone_12 = rand() % 6 + 1;
			bone_22 = rand() % 6 + 1;
			printf("Вам выпали числа %i и %i\n", bone_12, bone_22);
			sbone_2 = bone_12 + bone_22;
			if (sbone_1 > sbone_2)
			{
				printf("Вы проиграли %i монет\n", mon);
				player.coins -= mon;
				system("pause");
				system("cls");
			}
			else
			{
				printf("Вы выиграли %i монет\n", mon);
				player.coins += mon;
				system("pause");
				system("cls");
			}
			break;
		case '2':
			system("cls");
			printf("Вы выбрали 2 режим игры\n");
			printf("Правила игры: Вы выбираете кол-во монет на которые будете играть, далее вы загадываете 2 числа и бросаете кости, если одно из этих чисел выпадает, вы получаете в 2 раза больше монет, если выпадают 2 загаданных числа, вы получаете в 3 раза больше монет\n");
			printf("Выберете кол-во монет: 10 (1), 20 (2), 30(3)\n");
			scanf_s("%i", &vmon);
			if (player.coins < (vmon * 10))
			{
				printf("У вас не достаточно монет\n");
				system("pause");
				return 0;
			}
			if (vmon > 3 || vmon < 0)
			{
				printf("Вы выбрали не допустимое кол-во монет\n");
				system("pause");
				return 0;
			}
			printf("Загадайте 2 числа (не больше 6)\n");
			scanf_s("%i%i", &num_1, &num_2);
			if (num_1 > 7 || num_2 > 7 || num_1 < 0 || num_2 < 0 || num_1 == num_2)
			{
				printf("Вы загадали не допустимые числа\n");
				system("pause");
				return 0;
			}
			bone_11 = rand() % 6 + 1;
			bone_21 = rand() % 6 + 1;
			printf("Выпали числа %i и %i \n", bone_11, bone_21);
			if (bone_11 == num_1 || bone_21 == num_1 || bone_11 == num_2 || bone_21 == num_2)
			{
				printf("Вы получили %i монет\n", vmon * 20);
				system("pause");
				player.coins += (vmon * 20);
			}
			if (bone_11 == num_1 && bone_21 == num_2 || bone_11 == num_2 && bone_21 == num_1)
			{
				printf("Вы получили %i монет\n", vmon * 30);
				system("pause");
				player.coins += (vmon * 30);
			}
			if (bone_11 != num_1 && bone_11 != num_2 && bone_21 != num_1 && bone_21 != num_2)
			{
				printf("Вы проиграли %i монет\n", vmon * 10);
				player.coins -= (vmon * 10);
				system("pause");
			}
			break;
		case ESC:
			return 0;
		default:
			break;
		}
	}
	return 0;
}

int readMap(const char filename[])
{
	FILE* file;
	if (fopen_s(&file, filename, "rt") != 0)
	{
		printf("Не получилось открыть файл карты.\n");
		system("pause");
		return 1;
	}

	for (int y = 0; y < 20; y++)
		fgets(map[y], MAP_SIZE, file);
	fscanf_s(file, "%i", &enemy_count);

	for (int i = 0; i < enemy_count; i++)
	{
		fscanf_s(file, "%i%i%i%i%i%s", &enemies[i].x, &enemies[i].y, &enemies[i].lives, &enemies[i].coins, &enemies[i].key, enemies[i].name, 30);
	}

	fclose(file);
	return 0;
}

int goNextLevel()
{
	level++;
	if (level == 6)
		level = 1;
	player.key = 0;
	switch (level)
	{
	case 1:
		if (readMap("level1.txt") != 0) return 1;
		player = { 1, 1, player.lives, player.coins };
		break;
	case 2:
		if (readMap("level2.txt") != 0) return 1;
		player = { 1, 1, player.lives, player.coins };
		break;
	case 3:
		if (readMap("level3.txt") != 0) return 1;
		player = { 1, 1, player.lives, player.coins };
		break;
	case 4:
		if (readMap("level4.txt") != 0) return 1;
		player = { 1, 1, player.lives, player.coins };
		break;
	case 5:
		if (readMap("level5.txt") != 0) return 1;
		player = { 1, 1, player.lives, player.coins };
		break;
	}
	return 0;
}

int Shop()
{
	int shop;
	int vsh;
	int vsh2;
	bool sh = true;
	while (sh == true)
	{
		printf("У вас монет: %i \n", player.coins);
		printf("Привет, ты хочешь увеличить урон(1) или повысить здоровье(2)?\n");
		shop = _getch();
		switch (shop)
		{
		case '1':
			printf("У меня есть для тебя кинжал(1), мечЬ(2), автомат(3)\n");
			vsh = _getch();
			switch (vsh)
			{
			case '1':
				printf("Стоимость: 13 монет\nУрон: 3 жизни\nНажмите 1 чтобы купить\n");
				vsh2 = _getch();
				switch (vsh2)
				{
				case '1':
					if (player.coins < 13)
					{
						printf("У вас не достаточно монет\n");
						system("pause");
						return 0;
					}
					printf("Вы купили кинжал\n");
					damage = 3;
					player.coins -= 13;
					system("pause");
					return 0;
				case ESC:
					return 0;
					break;
				}
			case '2':
				printf("Стоимость: 22 монеты\nУрон: 5 жизней\nНажмите 1 чтобы купить\n");
				vsh2 = _getch();
				switch (vsh2)
				{
				case '1':
					if (player.coins < 22)
					{
						printf("У вас не достаточно монет\n");
						system("pause");
						return 0;
					}
					printf("Вы купили мечЬ\n");
					damage = 5;
					player.coins -= 22;
					system("pause");
					return 0;
				case ESC:
					return 0;
					break;
				}
			case '3':
				printf("Стоимость: 40 монет\nУрон: 7 жизней\nНажмите 1 чтобы купить\n");
				vsh2 = _getch();
				switch (vsh2)
				{
				case '1':
					if (player.coins < 40)
					{
						printf("У вас не достаточно монет\n");
						system("pause");
						return 0;
					}
					printf("Вы купили автомаt\n");
					damage = 7;
					player.coins -= 40;
					system("pause");
					return 0;
				case ESC:
					return 0;
					break;
				}
			case ESC:
				return 0;
				break;
			}
		case '2':
			printf("У меня есть броня(1) и аптечка(2)\n");
			vsh = _getch();
			switch (vsh)
			{
			case '1':
				printf("Стоимость: 35 монет\nС помощью брони вы сможете восстанавливать жизни до 5\nНажмите 1 чтобы купить\n");
				vsh2 = _getch();
				switch (vsh2)
				{
				case '1':
					if (player.coins < 35)
					{
						printf("У вас не достаточно монет\n");
						system("pause");
						return 0;
					}
					printf("Вы купили броню\n");
					maxlives = 5;
					player.coins -= 35;
					system("pause");
					return 0;
				case ESC:
					return 0;
					break;
				}
			case '2':
				printf("Стоимость: 17 монет\nЖизни: +1\nНажмите 1 чтобы купить\n");
				vsh2 = _getch();
				switch (vsh2)
				{
				case '1':
					if (player.lives < maxlives)
					{
						printf("Вы не можете восстановить больше жизней\n");
						system("pause");
						return 0;
					}
					if (player.coins < 17)
					{
						printf("У вас не достаточно монет\n");
						system("pause");
						return 0;
					}
					printf("Вы купили аптечку\n");
					player.lives++;
					player.coins -= 17;
					system("pause");
					return 0;
				case ESC:
					return 0;
					break;
				}
			case ESC:
				return 0;
				break;
			}
		case ESC:
			return 0;
			break;
		}
	}
	return 0;
}

int Skey()
{
	int csk = 10;
	char sk;
	if (player.key >= 1)
		return 0;
	else
	{
		printf("Эй\n");
		if (level == 1)
		{
			Sleep(500);
			printf("Эй парень, ключ не хочешь?? Всего 10 монет!\n");
			csk = 10;
		}
		printf("Эй\n");
		if (level == 2)
		{
			Sleep(750);
			printf("Эй парень, ключ не хочешь?? Всего 16 монет!\n");
			csk = 16;
		}
		if (level == 3)
		{
			Sleep(1000);
			printf("Эй парень, ключ не хочешь?? Всего 20 монет!\n");
			csk = 20;
		}

	}
	printf("Нажмите 1 чтобы купить ключ\n");
	sk = _getch();
	switch (sk)
	{
	case '1':
		if (player.coins < csk)
		{
			printf("У вас не достаточно монет\n");
			system("pause");
			break;
		}
		printf("Вы купили ключ, вы можете использовать его для открытия дверей\n");
		player.key++;
		player.coins -= csk;
		system("pause");
		break;
	default:
		printf("Ну, нет так нет!\n");
		system("pause");
		break;
	}
	return 0;
}

bool canGoTo(int x, int y)
{
	if (map[y][x] == EMPTY_1 ||
		map[y][x] == EMPTY_2 ||
		map[y][x] == PORTAL ||
		map[y][x] == HEALTH ||
		map[y][x] == TRAP ||
		map[y][x] == COIN ||
		map[y][x] == SHOP ||
		map[y][x] == SKEY ||
		map[y][x] == GAME ||
		map[y][x] == LOMBARD
		) return true;
	if (map[y][x] == DOOR && player.key >= 1) return true;
	else return false;
}

int checkAction()
{
	int myenemy;
	bool isEnemy = false;
	for (int i = 0; i < enemy_count; i++)
	{
		if (player.x == enemies[i].x && player.y == enemies[i].y && enemies[i].lives > 0)
		{
			isEnemy = true;
			myenemy = i;
			break;
		}
	}

	if (isEnemy)
	{
		for (int i = 0; i < enemy_count; i++)
		{
			int j = 0;
			char at;
			printf("Перед вами %s!!!\n", enemies[myenemy].name);
			printf("Нажимайте [ЛЮБАЯ КЛАВАИША] чтобы атаковать!\n");
			while (true)
			{
				j = rand() % 2;
				at = _getch();
				switch (at)
				{
				default:
					printf("Вы ударили врага и нанесли ему %i урона\n", damage);
					enemies[myenemy].lives -= damage;
					if (enemies[myenemy].lives <= 0)
					{
						printf("Вы убили %s и получили %i монет\n", enemies[myenemy].name, enemies[myenemy].coins);
						player.coins += enemies[myenemy].coins;
						isEnemy = false;
						system("pause");
						return 0;
					}
					if (j == 1)
					{
						printf("Враг ударил вас\n");
						player.lives--;
					}
				}
			}
		}
	}

	switch (map[player.y][player.x])
	{
	case EMPTY_1:
		break;
	case EMPTY_2:
		break;
	case PORTAL:
		if (goNextLevel() != 0)
			return 1;
		break;
	case COIN:
		player.coins++;
		map[player.y][player.x] = EMPTY_1;
		break;
	case HEALTH:
		if (player.lives < maxlives)
		{
			player.lives++;
			map[player.y][player.x] = EMPTY_1;
		}
		break;
	case TRAP:
		player.lives--;
		map[player.y][player.x] = EMPTY_1;
		break;
	case SKEY:
		Skey();
		if (player.key >= 1)
			map[player.y][player.x] = EMPTY_1;
		break;
	case SHOP:
		Shop();
		break;
	case GAME:
		game();
		break;
	case LOMBARD:
		lombard();
		break;
	}
	return 0;
}

void enemyTurn()
{
	for (int i = 0; i < enemy_count; i++)
	{
		if (enemies[i].lives <= 0)
			continue;

		int direction = -1;          // -1 - направление не выбрано, 0 ^, 1 >, 2 v, 3 <
		int dirand = rand() % 9;     // Ввод рандомного хода
		int d = rand() % 4;          // Направление рандомного хода

		int dx = 0, dy = 0;          // Разницы по кордам

		float detect;
		detect = sqrt((player.x - enemies[i].x) * (player.x - enemies[i].x) + (player.y - enemies[i].y) * (player.y - enemies[i].y));

		if (difficulty == 1)
			if (detect <= 3)
			{
				dx = player.x - enemies[i].x;
				dy = player.y - enemies[i].y;

				if (dirand == 0)
				{
					switch (d)
					{
					case 0:
						if (canGoTo(enemies[i].x, enemies[i].y - 1))
							enemies[i].y--;
						break;

					case 2:
						if (canGoTo(enemies[i].x, enemies[i].y + 1))
							enemies[i].y++;
						break;

					case 1:
						if (canGoTo(enemies[i].x + 1, enemies[i].y))
							enemies[i].x++;
						break;

					case 3:
						if (canGoTo(enemies[i].x - 1, enemies[i].y))
							enemies[i].x--;
						break;
					}
					break;
				}

				if (abs(dx) > abs(dy)) //Расчёт разницы 
				{
					if (dx > 0)
						direction = 1;
					else
						direction = 3;
				}
				else
				{
					if (dy > 0)
						direction = 2;
					else
						direction = 0;
				}
			}

		if (difficulty == 2)
			if (detect <= 5)
			{
				dx = player.x - enemies[i].x;
				dy = player.y - enemies[i].y;

				if (dirand == 0)
				{
					switch (d)
					{
					case 0:
						if (canGoTo(enemies[i].x, enemies[i].y - 1))
							enemies[i].y--;
						break;

					case 2:
						if (canGoTo(enemies[i].x, enemies[i].y + 1))
							enemies[i].y++;
						break;

					case 1:
						if (canGoTo(enemies[i].x + 1, enemies[i].y))
							enemies[i].x++;
						break;

					case 3:
						if (canGoTo(enemies[i].x - 1, enemies[i].y))
							enemies[i].x--;
						break;
					}
					break;
				}
				
				if (abs(dx) > abs(dy)) //Расчёт разницы 
				{
					if (dx > 0)
						direction = 1;
					else
						direction = 3;
				}
				else
				{
					if (dy > 0)
						direction = 2;
					else
						direction = 0;
				}
			}

		if (difficulty == 3)
			if (detect <= 7)
			{
				dx = player.x - enemies[i].x;
				dy = player.y - enemies[i].y;

				if (dirand == 0)
				{
					switch (d)
					{
					case 0:
						if (canGoTo(enemies[i].x, enemies[i].y - 1))
							enemies[i].y--;
						break;

					case 2:
						if (canGoTo(enemies[i].x, enemies[i].y + 1))
							enemies[i].y++;
						break;

					case 1:
						if (canGoTo(enemies[i].x + 1, enemies[i].y))
							enemies[i].x++;
						break;

					case 3:
						if (canGoTo(enemies[i].x - 1, enemies[i].y))
							enemies[i].x--;
						break;
					}
					break;
				}

				if (abs(dx) > abs(dy)) //Расчёт разницы 
				{
					if (dx > 0)
						direction = 1;
					else
						direction = 3;
				}
				else
				{
					if (dy > 0)
						direction = 2;
					else
						direction = 0;
				}
			}

		if (direction == -1)
			direction = rand() % 4;

		switch (direction)
		{
		case 0:
			if (canGoTo(enemies[i].x, enemies[i].y - 1))
				enemies[i].y--;
			break;

		case 2:
			if (canGoTo(enemies[i].x, enemies[i].y + 1))
				enemies[i].y++;
			break;

		case 1:
			if (canGoTo(enemies[i].x + 1, enemies[i].y))
				enemies[i].x++;
			break;

		case 3:
			if (canGoTo(enemies[i].x - 1, enemies[i].y))
				enemies[i].x--;
			break;
		}

		if (player.x == enemies[i].x && player.y == enemies[i].y)
			if (checkAction() != 0)
				exit(1);
	}
}

void printMap()
{
	SetConsoleTextAttribute(hConsole, 15);
	printf("Текущий уровень: %i\n", level);
	printf("У вас жизней: %i\n", player.lives);
	printf("У вас монет: %i\n", player.coins);
	if (player.key == 0)
		printf("У вас ключей: 0\n\n");
	if (player.key == 1)
		printf("У вас 1 ключ\n\n");
	if (player.key > 1)
		printf("У вас %i ключa\n\n", player.key);
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (x == player.x && y == player.y)
			{
				if (map[y][x] == EMPTY_1)
				{
					SetConsoleTextAttribute(hConsole, 46);
					printf("%c", PLAYER);
				}
				if (map[y][x] == EMPTY_2)
				{
					SetConsoleTextAttribute(hConsole, 174);
					printf("%c", PLAYER);
				}
				if (map[y][x] == SHOP)
				{
					SetConsoleTextAttribute(hConsole, 46);
					printf("%c", PLAYER);
				}
				if (map[y][x] == GAME)
				{
					SetConsoleTextAttribute(hConsole, 46);
					printf("%c", PLAYER);
				}
				if (map[y][x] == HEALTH)
				{
					SetConsoleTextAttribute(hConsole, 46);
					printf("%c", PLAYER);
				}
				if (map[y][x] == SKEY)
				{
					SetConsoleTextAttribute(hConsole, 46);
					printf("%c", PLAYER);
				}
				if (map[y][x] == DOOR)
				{
					SetConsoleTextAttribute(hConsole, 46);
					printf("%c", PLAYER);
				}
			}
			else
			{
				int eni;
				bool isEnemy = false;
				for (int i = 0; i < enemy_count; i++)
				{
					if (x == enemies[i].x && y == enemies[i].y && enemies[i].lives > 0)
					{
						isEnemy = true;
						eni = i;
						break;
					}
				}
				if (isEnemy)
				{
					SetConsoleTextAttribute(hConsole, 36);
					printf("%c", ENEMY);
				}
				else
				{

					switch (map[y][x])
					{
					case EMPTY_1:
						SetConsoleTextAttribute(hConsole, 34);
						printf("%c", map[y][x]);
						break;
					case EMPTY_2:
						SetConsoleTextAttribute(hConsole, 170);
						printf(" ");
						break;
					case PORTAL:
						SetConsoleTextAttribute(hConsole, 37);
						printf("%c", map[y][x]);
						break;
					case CLIFF:
						SetConsoleTextAttribute(hConsole, 135);
						printf(" ");
						break;
					case RIVER:
						SetConsoleTextAttribute(hConsole, 153);
						printf(" ");
						break;
					case TRAP:
						SetConsoleTextAttribute(hConsole, 135);
						printf(" ");
						break;
					case HEALTH:
						SetConsoleTextAttribute(hConsole, 47);
						printf("%c", map[y][x]);
						break;
					case COIN:
						SetConsoleTextAttribute(hConsole, 44);
						printf("%c", map[y][x]);
						break;
					case SHOP:
						SetConsoleTextAttribute(hConsole, 33);
						printf("%c", map[y][x]);
						break;
					case DOOR:
						SetConsoleTextAttribute(hConsole, 32);
						printf("%c", map[y][x]);
						break;
					case SKEY:
						SetConsoleTextAttribute(hConsole, 33);
						printf("%c", map[y][x]);
						break;
					case GAME:
						SetConsoleTextAttribute(hConsole, 33);
						printf("%c", map[y][x]);
						break;
					case LOMBARD:
						SetConsoleTextAttribute(hConsole, 33);
						printf("%c", map[y][x]);
						break;
					default:
						SetConsoleTextAttribute(hConsole, 15);
						printf("%c", map[y][x]);
						break;
					}
				}
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void savegame()
{
	FILE* savefile;
	if (fopen_s(&savefile, "save.txt", "wt") != 0)
	{
		printf("Не получилось сохранить игру\n");
		system("pause");
		return;
	}

	fprintf(savefile, "%i %i %i %i %i %i %i", level, player.x, player.y, player.lives, damage, player.coins, player.key);
	fclose(savefile);
}

void loadgame()
{
	FILE* savefile;
	if (fopen_s(&savefile, "save.txt", "rt") != 0)
	{
		printf("Не получилось загрузить игру\n");
		system("pause");
		return;
	}
	int x, y;
	fscanf_s(savefile, "%i%i%i%i%i%i%i", &level, &x, &y, &player.lives, &damage, &player.coins, &player.key);

	level--;
	goNextLevel();

	player.x = x;
	player.y = y;

	fclose(savefile);
}

int main()
{
	srand(1);
	maxlives = 3;
	system("chcp 1251");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	start();

	if (difficulty == 1)
		player.lives = 5;
	if (difficulty == 2)
		player.lives = 4;
	if (difficulty == 3)
		player.lives = 3;

	damage = 1;
	level = 0;
	if (goNextLevel() != 0)
		return 1;

	char key;

	bool quit = false;

	while (!quit)
	{
		system("cls");
		printMap();

		key = _getch();
		switch (key)
		{
		case 'w':
			if (canGoTo(player.x, player.y - 1))
				player.y--;
			break;

		case 's':
			if (canGoTo(player.x, player.y + 1))
				player.y++;
			break;

		case 'd':
			if (canGoTo(player.x + 1, player.y))
				player.x++;
			break;

		case 'a':
			if (canGoTo(player.x - 1, player.y))
				player.x--;
			break;

		case 'p':
			savegame();
			break;

		case 'l':
			loadgame();
			break;

		case ESC:
			quit = true;
			return 0;
		}

		if (checkAction() != 0)
			return 1;

		if (player.lives <= 0)
		{
			quit = true;
		}

		enemyTurn();

	}

	system("cls");

	if (player.lives <= 0)
	{
		printf("Вы потеряли все жизни. Игра окончена.\n\n");
	}

	system("pause");
	return 0;
}