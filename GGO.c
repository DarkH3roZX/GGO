#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// Structures
typedef struct {
	int powerLevel;
	int encryption;
	int index;
	int gold;
	int diamond;
	int wins;
	int loses;
	int goldBoost;
	int highestDamage;
	
	char username[21];
	char password[101];
} User;

typedef struct {
	char name[21];
	
	int level;
	int owned;
	int index;
	int amount;
	int attack;
	int hp;
	int defense;
	int elementPower;
} Inventory;

typedef struct {
	char name[31];
	
	int index;
	int role;
	int rarity;
	int element[7];
	int weapon;
} Character;

typedef struct {
	char name[21];

	int hp;
	int attack;
	int defense;
} Enemy;

/*
typedef struct {
	char nm[31];
	
	int in, ro, ra, e1, e2, e3, e4, e5, e6, e7, we;
} FileWrite;
*/
/*
typedef struct {
	char nm[21];

	int hp, atk, def;
} FileWrite;
*/

// Function Prototypes
void logo();
void exitMenu();
void notEnoughDiamond();
void moneyPrint(User player[], int userIndex);
void fileUpdate(FILE *accounts, User player[], int totalData);
void inventoryUpdate(FILE *fptr, Inventory playerInventory[], char fileName[]);
int cardFinder(int star);
int damageRandomizer(int damage);
int powerLevelCounter(User player[], Inventory playerInventory[], int recursiveNumber);
bool passwordCheck(int userIndex, User player[], char password[]);

int main() {
	// Int Variables
	int i, j, k;
	int turn;
	int swap;
	int temp;
	int cardGot;
	int heroIndex;
	int gachaIndex;
	int turnIndex;
	int recursiveNumber;
	int totalCards;
	int totalItems;
	int totalOwnedCharacter;
	int totalEnemies;
	int totalCharacters;
	int totalData;
	int userIndex;
	int loginWarp;
	int menuWarp;
	int inventoryWarp;
	int gameMenuWarp;
	int punchingBagWarp;
	int punchingBagWarp2;
	int convertAmount;
	int converterWarp;
	int OneVsOneWarp;
	int OneVsOneWarp2;
	int sizeOfTeam;
	int shopWarp;
	int rng1;
	int rng2;
	int rng3;
	int cardIndex;
	int star;
	int oneStarAmount;
	int twoStarAmount;
	int threeStarAmount;
	int fourStarAmount;
	int fiveStarAmount;
	int sixStarAmount;
	int validTeam;
	int characterTurn;
	int validUpgradeWarp;
	int punchingBagHP;
	int enemyIndex;
	int enemyIndexCounter;
	int enemyDamage;
	int enemyHP;
	int enemyDeffense;
	int playerDamage;
	int playerHP;
	int basicAttackAmount;
	int elementalAttackAmount;
	int highestDamage;
	int elementalCharge;
	int elementalSkillCounter;
	int elementalRoleType;
	int teamSizeInput;
	int printedComa;
	int missingGold;
	int missingCard;

	int teamMembers[4];
	int typeAmounts[6];
	int cardDoneIndex[8];
	int sorterIndex[1000];
	int sorterPowerLevel[1000];

	int cardAmounts[6][6];
	
	// Float Variables
	float caster;

	// File Pointers
	FILE *enemies;
	FILE *accounts;
	FILE *characters;
	FILE *fptr;
	
	// Char Variables
	char goldGenerator;
	char YorNstatement; // Yes or No statement
	
	char punchingBagHPStr[6];
	char characterName[21];
	char enemyName[21];
	char upgradeWarp[21];
	char upgradeName[21];
	char fileName[101];
	char username[21];
	char password[101];
	char confirmPassword[101];
	
	
	// Bool Flags
	bool validHP;
	bool validLogin;
	bool validChange;
	bool validGacha;
	bool validStart;
	bool validLost;
	bool isElementalActive;
	bool canEnter1v1;
	bool canEnterPunchingBag;
	
	// Structure Variables
	User player[1000];
	Character heroes[24];
	Inventory playerInventory[24];
	Enemy enemy[6];
	
	// Randomizer Seed
	srand(time(NULL));
	
	/*
	Main Code
	*/
	
	// File Print Code
	/*
	FileWrite fw;
	
	characters = fopen("characters.evan", "wb");
	
	for (i = 0; i < 24; i++) {
		scanf("%s %d %d %d %d %d %d %d %d %d %d %d", fw.nm, &fw.in, &fw.ro, &fw.ra, &fw.e1, &fw.e2, &fw.e3, &fw.e4, &fw.e5, &fw.e6, &fw.e7, &fw.we);
		fwrite(&fw, sizeof(fw), 1, characters);
	}
	
	fclose(characters);
	*/
	/*
	FileWrite fw;
	
	enemies = fopen("enemies.evan", "wb");
	
	for (i = 0; i < 6; i++) {
		scanf("%s %d %d %d", fw.nm, &fw.hp, &fw.atk, &fw.def);
		fwrite(&fw, sizeof(fw), 1, enemies);
	}
	
	fclose(enemies);
	*/
	
	// File Open
	accounts = fopen("accounts.evan", "rb");
	characters = fopen("characters.evan", "rb");
	enemies = fopen("enemies.evan", "rb");
	
	// Check if file is empty
	if (accounts == NULL) {
		fclose(accounts);
		accounts = fopen("accounts.evan", "wb");
		fclose(accounts);
		accounts = fopen("accounts.evan", "rb");
	}
	
	if (characters == NULL) {
		printf("Error! characters.evan not found!");
		getchar();
		
		return -1;
	}
	
	if (enemies == NULL) {
		printf("Error! enemies.evan not found!");
		getchar();
		
		return -1;
	}
	
	// Input File content into array
	rewind(accounts);
	rewind(characters);
	rewind(enemies);
	
	totalData = 0;
	totalCharacters = 0;
	totalEnemies = 0;
	
	while (!feof(characters)) {
		fread(&heroes[totalCharacters], sizeof(heroes[totalCharacters]), 1, characters);
		
		if (!feof(characters))
			totalCharacters++;
	}
	
	while (!feof(accounts)) {
		fread(&player[totalData], sizeof(player[totalData]), 1, accounts);
		
		if (!feof(accounts))
			totalData++;
	}

	while (!feof(enemies)) {
		fread(&enemy[totalEnemies], sizeof(enemy[totalEnemies]), 1, enemies);
		
		if (!feof(enemies))
			totalEnemies++;
	}
	
	// Close all the file
	fclose(accounts);
	fclose(characters);
	fclose(enemies);
	
	do
	{
		// Login Menu
		do
		{
			do
			{
				system("cls");
				logo();
				
				printf("1. Login\n");
				printf("2. Register\n");
				printf("3. Exit\n\n");
				
				printf("Where do you want to go : ");
				scanf("%d", &loginWarp);
				while (getchar() != '\n');
			}
			while (loginWarp != 1 && loginWarp != 2 && loginWarp != 3);
			
			// Login
			if (loginWarp == 1) {
				system("cls");
				logo();
				
				// Reset
				validLogin = true;
				userIndex = -1;
				
				// Username Input
				printf(" LOGIN \n");
				printf("=======\n\n");
				
				printf("Username : ");
				scanf("%s", username);
				while (getchar() != '\n');
				
				// Username Check
				for (i = 0; i < 1000; i++) {
					if (strcmp(player[i].username, username) == 0) {
						userIndex = i;
						break;
					}
				}
				
				// Password Input
				printf("Password : ");
				scanf("%s", password);
				while (getchar() != '\n');
				
				// Password Check
				validLogin = passwordCheck(userIndex, player, password);
				
				if (validLogin) {
					printf("\nLogin Success, press \'Enter\' to continue!");
					getchar();
				}
				else {
					printf("\nIncorrect Password");
					getchar();
					
					continue;
				}
				
				
				strcpy(fileName, "data/");
				strcat(fileName, player[userIndex].username);
				strcat(fileName, ".evan");
				
				// Input Player Inventory Data
				totalItems = 0;
				fptr = fopen(fileName, "rb");
				rewind(fptr);

				if (fptr == NULL) {
					printf("Error! User data not found!");
					getchar();
					
					return -1;
				}
				
				while (!feof(fptr)) {
					fread(&playerInventory[totalItems], sizeof(playerInventory[totalItems]), 1, fptr);
					
					if (!feof(fptr))
						totalItems++;
				}
				
				fclose(fptr);
			}
			
			// Register
			else if (loginWarp == 2) {
				system("cls");
				logo();
				
				validLogin = true;
				
				// Username Input
				printf(" REGISTER \n");
				printf("==========\n\n");
				
				printf("Username : ");
				scanf("%s", username);
				while (getchar() != '\n');
				
				// Check if username is taken or not
				for (i = 0; i < 1000; i++) {
					if (strcmp(username, player[i].username) == 0) {
						validLogin = false;
						
						printf("Username already taken!");
						getchar();
						
						break;
					}
				}
				
				if (validLogin == false)
					continue;
				
				// Password Input
				printf("Password : ");
				scanf("%s", password);
				while (getchar() != '\n');
				
				printf("Confirm Password : ");
				scanf("%s", confirmPassword);
				while (getchar() != '\n');
				
				// Check if password and confirm password is the same
				if (strcmp(password, confirmPassword) != 0) {
					validLogin = false;
					
					printf("\nPassword and confirm password is different!");
					getchar();
					continue;
				}
				
				// Input account data
				accounts = fopen("accounts.evan", "ab");
				
				strcpy(player[totalData].username, username);
				
				player[totalData].gold = 0;
				player[totalData].diamond = 0;
				player[totalData].encryption = rand() % 21 + 4;
				player[totalData].index = totalData;
				player[totalData].powerLevel = 0;
				player[totalData].wins = 0;
				player[totalData].loses = 0;
				player[totalData].highestDamage = 0;
				player[totalData].goldBoost = 1;
				
				// Password Encryption
				for (i = 0; i < strlen(password); i++) {
					if (islower(password[i])) // 97
						password[i] = 97 + (password[i] - 97 + player[totalData].encryption) % 26;
					else if (isupper(password[i])) // 65
						password[i] = 65 + (password[i] - 65 + player[totalData].encryption) % 26;
					else if (isdigit(password[i])) // 48
						password[i] = 48 + (password[i] - 48 + player[totalData].encryption) % 10;
				}
				
				strcpy(player[totalData].password, password);
				fwrite(&player[totalData], sizeof(player[totalData]), 1, accounts);
				fclose(accounts);
				
				userIndex = totalData;
				totalData++;

				// Creates data folder
				mkdir("data", 0777);
				
				// Creates a user file
				strcpy(fileName, "data/");
				strcat(fileName, username);
				strcat(fileName, ".evan");
				
				fptr = fopen(fileName, "wb");

				if (fptr == NULL) {
					printf("Error! \"data\" folder not found!");
					getchar();
					
					return -1;
				}
				
				// Input Account File
				for (i = 0; i < 24; i++) {
					playerInventory[i].owned = 0;
					playerInventory[i].amount = 0;
					playerInventory[i].index = i;
					playerInventory[i].level = 1;
					
					// Character Stats Printing
					switch (i) {
						case 0:
						case 1:
						case 2:
						case 3:
						case 4:
							playerInventory[i].attack = 96;
							playerInventory[i].defense = 10;
							playerInventory[i].elementPower = 96;
							playerInventory[i].hp = 876;
							
							break;
							
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
							playerInventory[i].attack = 120;
							playerInventory[i].defense = 14;
							playerInventory[i].elementPower = 120;
							playerInventory[i].hp = 1218;
							
							break;
							
						case 11:
						case 12:
						case 13:
						case 14:
						case 15:
						case 16:
							playerInventory[i].attack = 218;
							playerInventory[i].defense = 19;
							playerInventory[i].elementPower = 218;
							playerInventory[i].hp = 2448;
							
							break;
							
						case 17:
						case 18:
						case 19:
						case 20:
							playerInventory[i].attack = 264;
							playerInventory[i].defense = 23;
							playerInventory[i].elementPower = 264;
							playerInventory[i].hp = 3345;
							
							break;
							
						case 21:
						case 22:
							playerInventory[i].attack = 420;
							playerInventory[i].defense = 28;
							playerInventory[i].elementPower = 420;
							playerInventory[i].hp = 5233;
							
							break;
							
						case 23:
							playerInventory[i].attack = 687;
							playerInventory[i].defense = 35;
							playerInventory[i].elementPower = 687;
							playerInventory[i].hp = 7777;
							
							break;
					}

					// Name Printing
					switch (i) {
						case 0:
							strcpy(playerInventory[i].name, "traveler");
							playerInventory[i].defense += 2;
							
							break;
						case 1:
							strcpy(playerInventory[i].name, "amber");
							playerInventory[i].attack += 2;
							
							break;
						case 2:
							strcpy(playerInventory[i].name, "kaeya");
							playerInventory[i].attack += 2;
							
							break;
						case 3:
							strcpy(playerInventory[i].name, "lisa");
							playerInventory[i].elementPower += 2;
							
							break;
						case 4:
							strcpy(playerInventory[i].name, "noelle");
							playerInventory[i].hp += 312;
							
							break;
						case 5:
							strcpy(playerInventory[i].name, "barbara");
							playerInventory[i].elementPower += 3;
							
							break;
						case 6:
							strcpy(playerInventory[i].name, "bennett");
							playerInventory[i].elementPower += 3;
							
							break;
						case 7:
							strcpy(playerInventory[i].name, "fischl");
							playerInventory[i].attack += 16;
							
							break;
						case 8:
							strcpy(playerInventory[i].name, "razor");
							playerInventory[i].defense += 3;
							playerInventory[i].attack += 14;
							
							break;
						case 9:
							strcpy(playerInventory[i].name, "sucrose");
							playerInventory[i].elementPower += 3;
							
							break;
						case 10:
							strcpy(playerInventory[i].name, "xiangling");
							playerInventory[i].hp += 312;
							
							break;
						case 11:
							strcpy(playerInventory[i].name, "diluc");
							playerInventory[i].attack += 5;
							
							break;
						case 12:
							strcpy(playerInventory[i].name, "keqing");
							playerInventory[i].attack += 5;
							
							break;
						case 13:
							strcpy(playerInventory[i].name, "mona");
							playerInventory[i].elementPower += 5;
							
							break;
						case 14:
							strcpy(playerInventory[i].name, "qiqi");
							playerInventory[i].elementPower += 5;
							
							break;
						case 15:
							strcpy(playerInventory[i].name, "venti");
							playerInventory[i].elementPower += 5;
							
							break;
						case 16:
							strcpy(playerInventory[i].name, "zhongli");
							playerInventory[i].hp += 312;
							
							break;
						case 17:
							strcpy(playerInventory[i].name, "guardian");
							playerInventory[i].elementPower += 10;
							
							break;
						case 18:
							strcpy(playerInventory[i].name, "stong");
							playerInventory[i].hp += 312;
							
							break;
						case 19:
							strcpy(playerInventory[i].name, "odading");
							playerInventory[i].attack += 10;
							
							break;
						case 20:
							strcpy(playerInventory[i].name, "steve");
							playerInventory[i].defense += 2;
							
							break;
						case 21:
							strcpy(playerInventory[i].name, "x");
							playerInventory[i].elementPower += 1;
							
							break;
						case 22:
							strcpy(playerInventory[i].name, "supra");
							playerInventory[i].hp += 312;
							
							break;
						case 23:
							strcpy(playerInventory[i].name, "king");
							break;
					}
					
					fwrite(&playerInventory[i], sizeof(playerInventory[i]), 1, fptr);
				}
				
				fclose(fptr);
				
				// Username registered word
				printf("\nUsername Registered!\n");
				printf("Press \'Enter\' to continue");
				getchar();
			}
			
			// Exit
			else if (loginWarp == 3) {
				system("cls");
				logo();
				exitMenu();
				
				return 0;
			}
		}
		while (validLogin == false);
		
		// Cheat Tester
		/*
		player[userIndex].gold += 100000000;
		player[userIndex].diamond += 100000000;
		
		for (i = 0; i < 24; i++) {
			playerInventory[i].owned = 1;
			playerInventory[i].amount = 10000;
		}
		*/
		
		// Main Menu
		do
		{
			// Main Menu
			do
			{
				system("cls");
				logo();
				
				printf(" %s \n", player[userIndex].username);
				
				for (i = 0; i < strlen(player[userIndex].username) + 2; i++)
					printf("=");
				
				puts("");
				moneyPrint(player, userIndex);
				
				printf("1. Game Menu\n");
				printf("2. Inventory Menu\n");
				printf("3. Instructions\n");
				printf("4. Leaderboard\n");
				printf("5. Statistics\n");
				printf("6. Change Password\n");
				printf("7. Log Out\n");
				printf("8. Exit\n\n");
				
				printf("Where do you want to go : ");
				scanf("%d", &menuWarp);
				while (getchar() != '\n');
			}
			while (menuWarp != 1 && menuWarp != 2 && menuWarp != 3 && menuWarp != 4 && menuWarp != 5 && menuWarp != 6 && menuWarp != 7 && menuWarp != 8);
			
			// Game Menu
			if (menuWarp == 1) {
				do
				{
					do
					{
						system("cls");
						logo();
						
						printf(" Game Menu \n");
						printf("===========\n\n");
						
						moneyPrint(player, userIndex);
						
						printf("1. Get Gold\n");
						printf("2. Gold & Diamond Converter\n");
						printf("3. 1v1 arena\n");
						printf("4. Punching bag arena\n");
						printf("5. Chest shop\n");
						printf("6. Main Menu\n\n");
						
						printf("Where do you want to go : ");
						scanf("%d", &gameMenuWarp);
						while (getchar() != '\n');
					}
					while (gameMenuWarp != 1 && gameMenuWarp != 2 && gameMenuWarp != 3 && gameMenuWarp != 4 && gameMenuWarp != 5 && gameMenuWarp != 6);
					
					// Get Gold
					if (gameMenuWarp == 1) {
						do
						{
							// Banner
							system("cls");
							printf(" Gold Generator \n");
							printf("================\n");
							printf("Gold = %lld\n\n", player[userIndex].gold);
							
							printf("Type \'x\' and press \'Enter\' to go back to game menu\n");
							printf("Press \'Enter\' to get gold\n");
							printf("Input : ");
							goldGenerator = getchar();

							// Gold increase code
							if (goldGenerator != 'x') {
								player[userIndex].gold += player[userIndex].goldBoost;
							}
						}
						while (goldGenerator != 'x');
						
						fileUpdate(accounts, player, totalData);
					}
					
					// Gold and Diamond Converter
					else if (gameMenuWarp == 2) {
						do
						{
							// Converter Menu
							do
							{
								system("cls");
								printf(" Converter Chamber \n");
								printf("===================\n\n");
								
								moneyPrint(player, userIndex);
								
								printf("1. Gold to Diamond\n");
								printf("2. Diamond to Gold\n");
								printf("3. Game Menu\n\n");
								
								printf("Your choice : ");
								scanf("%d", &converterWarp);
								while (getchar() != '\n');
							}
							while (converterWarp != 1 && converterWarp != 2 && converterWarp != 3);
							
							// Gold to diamond
							if (converterWarp == 1) {
								// Banner
								system("cls");
								printf(" Gold to Diamond \n");
								printf("=================\n\n");
								
								printf("1 diamond = 1000 gold	|	Gold = %lld\n", player[userIndex].gold);
								moneyPrint(player, userIndex);
								
								// Amount Input
								printf("How many diamonds you want to get : ");
								scanf("%d", &convertAmount);
								while (getchar() != '\n');
								
								// Check whether the gold is enough or not
								if (convertAmount > player[userIndex].gold / 1000) {
									printf("Not enough gold");
									getchar();
									
									continue;
								}
								
								// Converting code
								player[userIndex].gold -= convertAmount * 1000;
								player[userIndex].diamond += convertAmount;
								
								// Receipt
								printf("You get %d diamond\n", convertAmount);
								printf("Press \'Enter\' to continue");
								getchar();
							}
							
							// Diamond to gold
							else if (converterWarp == 2) {
								// Banner
								system("cls");
								printf(" Diamond to Gold \n");
								printf("=================\n\n");
								
								printf("1000 gold = 1 diamond	|	Diamond = %d\n", player[userIndex].diamond);
								moneyPrint(player, userIndex);
								
								// Amount Input
								printf("How many diamonds you want to spend : ");
								scanf("%d", &convertAmount);
								while (getchar() != '\n');
								
								// Check whether the diamond is enough or not
								if (convertAmount > player[userIndex].diamond) {
									printf("Not enough diamond");
									getchar();
									
									continue;
								}
								
								// Converting code
								player[userIndex].gold += convertAmount * 1000;
								player[userIndex].diamond -= convertAmount;
								
								// Receipt
								printf("You get %d gold\n", convertAmount * 1000);
								printf("Press \'Enter\' to continue");
								getchar();
							}
							
							fileUpdate(accounts, player, totalData);
						}
						while (converterWarp != 3);
					}
					
					// 1v1 Arena
					else if (gameMenuWarp == 3) {
						// Check if player can enter the 1v1 or not
						canEnter1v1 = false;
						totalOwnedCharacter = 0;

						for (i = 0; i < 24; i++) {
							if (playerInventory[i].owned == 1) {
								canEnter1v1 = true;
								totalOwnedCharacter++;
							}
						}

						if (!canEnter1v1) {
							printf("\nYou need to at least have 1 character before going for a 1v1 battle");
							getchar();

							continue;
						}

						do
						{
							do
							{
								// Banner
								system("cls");
								logo();

								printf(" 1v1 Arena \n");
								printf("===========\n\n");

								// UI
								printf("Choose a difficulty!\n");
								printf("1. Easy\n");
								printf("2. Normal\n");
								printf("3. Hard\n\n");

								printf("Input 4 to go back to main menu!\n\n");

								printf("Your choice : ");
								scanf("%d", &OneVsOneWarp);
								while (getchar() != '\n');
							}
							while (OneVsOneWarp != 1 && OneVsOneWarp != 2 && OneVsOneWarp != 3 && OneVsOneWarp != 4);
							
							if (OneVsOneWarp != 4) {
								do
								{
									// Banner
									system("cls");
									logo();

									printf(" 1v1 Arena \n");
									printf("===========\n\n");

									printf("How much character you want to invite to battle (1-4): ");
									scanf("%d", &teamSizeInput);
									while (getchar() != '\n');

									if (teamSizeInput <= 0 || teamSizeInput >= 5) {
										printf("Team size has to be between 1-4!");
										getchar();

										continue;
									}

									if (teamSizeInput > totalOwnedCharacter) {
										printf("You don\'t have enough character to play!");
										getchar();

										continue;
									}

									break;
								}
								while (true);

								// Character Pick Scene
								// Banner
								system("cls");
								logo();
								
								// Owned Character Printing
								printf("Characters Owned:\n");
								
								for (i = 0; i < 24; i++) {
									if (playerInventory[i].owned == 1)
										printf("%s Lv. %d (%d*)\n", heroes[i].name, playerInventory[i].level, heroes[i].rarity);
								}
								
								puts("");
	
								// Character picking scene
								for (i = 0; i < teamSizeInput; i++) {
									do
									{
										validTeam = 1;
	
										// UI
										if (teamSizeInput > 1)
											printf("Pick character %d to fight : ", i + 1);
										else
											printf("Pick a character to fight : ");

										scanf("%s", characterName);
										while (getchar() != '\n');
	
										// Check the character index
										for (j = 0; j < 24; j++) {
											if (strcmp(characterName, heroes[j].name) == 0) {
												temp = j;
	
												break;
											}
	
											// If the character doesn't exist
											if (j == 23) {
												validTeam = 0;
											}
										}
	
										if (validTeam == 0) {
											printf("Character name invalid!");
											getchar();
	
											continue;
										}
										
										// If player doesn't own the character
										if (playerInventory[temp].owned == 0) {
											printf("Character unowned!");
											getchar();
	
											continue;
										}
	
										// If character is only in the team
										if (i > 0) {
											for (j = 0; j < i; j++) {
												if (temp == teamMembers[j]) {
													validTeam = 2;
	
													break;
												}
											}
										}
	
										if (validTeam == 2) {
											printf("Character already in a team!");
											getchar();
	
											continue;
										}
	
										teamMembers[i] = temp;
										break;
									}
									while (true);
								}
							}
							
							// Easy Mode
							if (OneVsOneWarp == 1) {
								rng1 = 5; // rng1 is the amount of rounds
								enemyIndexCounter = 0;
							}

							// Normal Mode
							else if (OneVsOneWarp == 2) {
								rng1 = 5; // rng1 is the amount of rounds
								enemyIndexCounter = 2;
							}

							// Hard Mode
							else if (OneVsOneWarp == 3) {
								rng1 = 5; // rng1 is the amount of rounds
								enemyIndexCounter = 4;
							}
							
							if (OneVsOneWarp != 4) {
								// Game Reseter
								turnIndex = 0;
								elementalSkillCounter = 0;
								validLost = false;
								isElementalActive = false;
								elementalCharge = 0;
								playerHP = playerInventory[teamMembers[turnIndex]].hp;
								
								// Main Game
								for (i = 0; i < rng1; i++) {
									rng2 = rand() % 4;
	
									if (rng2 == 0)
										enemyIndex = enemyIndexCounter + 1; // If player gets a stronger enemy
									else
										enemyIndex = enemyIndexCounter; // If player gets a normal enemy
									
									enemyHP = enemy[enemyIndex].hp;
									enemyDeffense = enemy[enemyIndex].defense;
									
									// Banner
									do
									{
										do
										{
											system("cls");
											logo();
	
											printf(" Round %d \n", i + 1);
											printf("==========\n\n");
											
											printedComa = 0;

											if (teamSizeInput != 1) {
												printf("Team Members Remaining : \n");
												
												for (j = 0; j < teamSizeInput; j++) {
													if (j == turnIndex)
														continue;
													
													if (j >= turnIndex)
														printf("%s", heroes[teamMembers[j]].name);
													else
														printf("%s (Died)", heroes[teamMembers[j]].name);

													if (printedComa < teamSizeInput - 2) {
														printf(", ");

														printedComa++;
													}
												}
											
												puts("\n");
											}
	
											printf("%s \n", heroes[teamMembers[turnIndex]].name);
											printf("VS.\n");
											printf("%s \n\n", enemy[enemyIndex].name);
	
											printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
											printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);
	
											// UI
											printf("What do you want to do?\n");
											printf("1. Basic Attack\n");
											printf("2. Elemental Attack\n");
											printf("3. Defend\n");
											printf("4. Use Elemental Skill (%d/100)\n", elementalCharge);
											printf("5. Run\n\n");
	
											printf("Your Choice : ");
											scanf("%d", &OneVsOneWarp2);
											while (getchar() != '\n');
										}
										while (OneVsOneWarp2 != 1 && OneVsOneWarp2 != 2 && OneVsOneWarp2 != 3 && OneVsOneWarp2 != 4 && OneVsOneWarp2 != 5);
	
										// Basic Attack
										if (OneVsOneWarp2 == 1) {
											rng3 = rand() % 3;
											// 0 = enemy is defending
											// else = enemy is attacking

											if (rng3 == 0)
												caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].attack) * 100 / (float)(100 + enemy[enemyIndex].defense);
											else
												caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].attack) * 100 / (float)(100 + 2 * enemy[enemyIndex].defense);
											
											if (isElementalActive) {
												if (elementalRoleType == 0)
													playerDamage = (int)caster + ((int)caster * 3 / 10);
												else if (elementalRoleType == 4)
													playerDamage = (int)caster * 22 / 10;
												else
													playerDamage = (int)caster;
											}
											else
												playerDamage = (int)caster;
											
											enemyHP -= playerDamage;

											if (enemyHP < 0)
												enemyHP = 0;

											// Banner
											system("cls");
											logo();
	
											printf(" Round %d \n", i + 1);
											printf("==========\n\n");

											if (teamSizeInput != 1) {
												printedComa = 0;

												printf("Team Members Remaining : \n");
												
												for (j = 0; j < teamSizeInput; j++) {
													if (j == turnIndex)
														continue;
													
													if (j >= turnIndex)
														printf("%s", heroes[teamMembers[j]].name);
													else
														printf("%s (Died)", heroes[teamMembers[j]].name);

													if (printedComa < teamSizeInput - 2) {
														printf(", ");

														printedComa++;
													}
												}
											
												puts("\n");
											}
	
											printf("%s \n", heroes[teamMembers[turnIndex]].name);
											printf("VS.\n");
											printf("%s \n\n", enemy[enemyIndex].name);
	
											printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
											printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

											if (elementalRoleType == 4 && isElementalActive) {
												printf("Enemy took %d damage!\n", (int)caster);
												printf("Enemy got poisoned and got %d extra damage!\n", (int)caster * 22 / 10 - (int)caster);
											}
											else {
												printf("Enemy Took %d damage\n", playerDamage);
												
												if (isElementalActive)
													printf("Elemental skill still active!\n");
											}
											
											if (rng3 == 0)
												printf("Enemy is defending while you are attacking!\n");

											getchar();

											if (rng3 != 0 && enemyHP != 0) {
												caster = damageRandomizer(enemy[enemyIndex].attack) * 100 / (float)(100 + playerInventory[teamMembers[turnIndex]].defense);

												if (isElementalActive) {
													if (elementalRoleType == 0)
														enemyDamage = (int)caster - (int)caster * 3 / 10;
													else if (elementalRoleType == 1)
														enemyDamage = (int)caster / 5;
													else
														enemyDamage = (int)caster;
												}
												else
													enemyDamage = (int)caster;
												
												playerHP -= enemyDamage;

												if (playerHP < 0)
													playerHP = 0;

												// Banner
												system("cls");
												logo();

												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;

													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}

												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);

												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("%s attacks, you took %d damage!\n", enemy[enemyIndex].name, enemyDamage);

												getchar();
											}

											if (isElementalActive)
												elementalSkillCounter--;
											
											if (!isElementalActive || elementalRoleType == 4)
												elementalCharge += 20;
											
											if (elementalSkillCounter == 0)
												isElementalActive = false;
											
											if (elementalCharge > 100)
												elementalCharge = 100;
										}

										// Elemental Attack
										else if (OneVsOneWarp2 == 2) {
											rng3 = rand() % 3;
											// 0 = enemy is defending
											// else = enemy is attacking

											if (rng3 == 0)
												caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].elementPower) * 100 / (float)(100 + enemy[enemyIndex].defense);
											else
												caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].elementPower) * 100 / (float)(100 + 2 * enemy[enemyIndex].defense);
										
											if (isElementalActive) {
												if (elementalRoleType == 0)
													playerDamage = (int)caster + ((int)caster * 3 / 10);
												else if (elementalRoleType == 4)
													playerDamage = (int)caster * 22 / 10;
												else
													playerDamage = (int)caster;
											}
											else
												playerDamage = (int)caster;
											
											enemyHP -= playerDamage;

											if (enemyHP < 0)
												enemyHP = 0;

											// Banner
											system("cls");
											logo();
	
											printf(" Round %d \n", i + 1);
											printf("==========\n\n");

											if (teamSizeInput != 1) {
												printedComa = 0;

												printf("Team Members Remaining : \n");
												
												for (j = 0; j < teamSizeInput; j++) {
													if (j == turnIndex)
														continue;
													
													if (j >= turnIndex)
														printf("%s", heroes[teamMembers[j]].name);
													else
														printf("%s (Died)", heroes[teamMembers[j]].name);

													if (printedComa < teamSizeInput - 2) {
														printf(", ");

														printedComa++;
													}
												}
											
												puts("\n");
											}
	
											printf("%s \n", heroes[teamMembers[turnIndex]].name);
											printf("VS.\n");
											printf("%s \n\n", enemy[enemyIndex].name);
	
											printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
											printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

											if (elementalRoleType == 4 && isElementalActive) {
												printf("Enemy took %d damage!\n", (int)caster);
												printf("Enemy got poisoned and got %d extra damage!\n", (int)caster * 22 / 10 - (int)caster);
											}
											else {
												printf("Enemy Took %d damage\n", playerDamage);
												
												if (isElementalActive)
													printf("Elemental skill still active!\n");
											}
											
											if (rng3 == 0)
												printf("Enemy is defending while you are attacking!\n");

											getchar();

											if (rng3 != 0 && enemyHP != 0) {
												caster = damageRandomizer(enemy[enemyIndex].attack) * 100 / (float)(100 + playerInventory[teamMembers[turnIndex]].defense);

												if (isElementalActive) {
													if (elementalRoleType == 0)
														enemyDamage = (int)caster - (int)caster * 3 / 10;
													else if (elementalRoleType == 1)
														enemyDamage = (int)caster / 5;
													else
														enemyDamage = (int)caster;
												}
												else
													enemyDamage = (int)caster;
												
												playerHP -= enemyDamage;

												if (playerHP < 0)
													playerHP = 0;

												// Banner
												system("cls");
												logo();

												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;

													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}

												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);

												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("%s attacks, you took %d damage!\n", enemy[enemyIndex].name, enemyDamage);

												getchar();
											}

											if (isElementalActive)
												elementalSkillCounter--;
											
											if (!isElementalActive || elementalRoleType == 4)
												elementalCharge += 20;
											
											if (elementalSkillCounter == 0)
												isElementalActive = false;
											
											if (elementalCharge > 100)
												elementalCharge = 100;
										}
	
										// Defend
										else if (OneVsOneWarp2 == 3) {
											caster = damageRandomizer(enemy[enemyIndex].attack) * 100 / (float)(100 + 5 * playerInventory[teamMembers[turnIndex]].defense);

											if (isElementalActive) {
												if (elementalRoleType == 0)
													enemyDamage = (int)caster - (int)caster * 3 / 10;
												else if (elementalRoleType == 1)
													enemyDamage = (int)caster / 5;
												else
													enemyDamage = (int)caster;
											}
											else
												enemyDamage = (int)caster;
											
											playerHP -= enemyDamage;

											if (playerHP < 0)
												playerHP = 0;

											// Banner
											system("cls");
											logo();

											printf(" Round %d \n", i + 1);
											printf("==========\n\n");

											if (teamSizeInput != 1) {
												printedComa = 0;

												printf("Team Members Remaining : \n");
												
												for (j = 0; j < teamSizeInput; j++) {
													if (j == turnIndex)
														continue;
													
													if (j >= turnIndex)
														printf("%s", heroes[teamMembers[j]].name);
													else
														printf("%s (Died)", heroes[teamMembers[j]].name);

													if (printedComa < teamSizeInput - 2) {
														printf(", ");

														printedComa++;
													}
												}
											
												puts("\n");
												}

											printf("%s \n", heroes[teamMembers[turnIndex]].name);
											printf("VS.\n");
											printf("%s \n\n", enemy[enemyIndex].name);

											printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
											printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

											printf("%s attacks, you took %d damage!\n", enemy[enemyIndex].name, enemyDamage);

											if (isElementalActive)
												printf("Elemental Skill is active!\n");

											getchar();

											if (isElementalActive)
												elementalSkillCounter--;
											
											if (!isElementalActive || elementalRoleType == 4)
												elementalCharge += 40;
											
											if (elementalSkillCounter == 0)
												isElementalActive = false;
											
											if (elementalCharge > 100)
												elementalCharge = 100;
										}
	
										// Elemental Skill
										else if (OneVsOneWarp2 == 4) {
											if (elementalCharge != 100) {
												printf("Elemental Power not fully charged");
												getchar();
												continue;
											}
											
											// All Around Elemental Skill
											if (heroes[teamMembers[turnIndex]].role == 0) {
												elementalSkillCounter = 3;
												elementalRoleType = 0;
												isElementalActive = true;

												// Banner
												system("cls");
												logo();
		
												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;

													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}
		
												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);
		
												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("Elemental skill active!\n");
												printf("For 3 turns, attack and defend increased by 30%%\n");
												getchar();
											}
	
											// Tank Elemental Skill (reduces damage for 3 hits)
											else if (heroes[teamMembers[turnIndex]].role == 1) {
												elementalSkillCounter = 4;
												elementalRoleType = 1;
												isElementalActive = true;

												// Banner
												system("cls");
												logo();
		
												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;

													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}
		
												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);
		
												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("Elemental skill active!\n");
												printf("For 2 turns, damage reduced by 80%%\n");
												getchar();
											}
	
											// Fighter Elemental Skill (triple damage)
											else if (heroes[teamMembers[turnIndex]].role == 2) {
												caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].attack) * 100 / (float)(100 + enemy[enemyIndex].defense);
												playerDamage = (int)caster * 3;
												enemyHP -= playerDamage;

												if (enemyHP < 0)
													enemyHP = 0;

												// Banner
												system("cls");
												logo();
		
												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;

													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}
		
												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);
		
												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("Elemental skill! (triple damage)\n");
												printf("Enemy Took %d damage\n", playerDamage);
												getchar();
											}
	
											// Assassin Elemental Skill (triple attack)
											else if (heroes[teamMembers[turnIndex]].role == 3) {
												for (j = 0; j < 3; j++) {
													caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].attack) * 100 / (float)(100 + enemy[enemyIndex].defense);
													playerDamage = (int)caster;
													enemyHP -= playerDamage;

													if (enemyHP < 0)
														enemyHP = 0;

													// Banner
													system("cls");
													logo();
			
													printf(" Round %d \n", i + 1);
													printf("==========\n\n");

													if (teamSizeInput != 1) {
														printedComa = 0;

														printf("Team Members Remaining : \n");
														
														for (k = 0; k < teamSizeInput; k++) {
															if (k == turnIndex)
																continue;
															
															if (k >= turnIndex)
																printf("%s", heroes[teamMembers[k]].name);
															else
																printf("%s (Died)", heroes[teamMembers[k]].name);

															if (printedComa < teamSizeInput - 2) {
																printf(", ");

																printedComa++;
															}
														}
													
														puts("\n");
													}
			
													printf("%s \n", heroes[teamMembers[turnIndex]].name);
													printf("VS.\n");
													printf("%s \n\n", enemy[enemyIndex].name);
			
													printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
													printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

													printf("Elemental skill ");

													if (j == 0)
														printf("1st attack!\n");
													else if (j == 1)
														printf("2nd attack!\n");
													else if (j == 2)
														printf("3rd attack!\n");

													printf("Enemy Took %d damage\n", playerDamage);
													getchar();

													if (enemyHP == 0)
														break;
												}
											}
											
											// Mage Elemental Skill (poison)
											else if (heroes[teamMembers[turnIndex]].role == 4) {
												elementalSkillCounter = 2;
												elementalRoleType = 4;
												isElementalActive = true;

												caster = damageRandomizer(playerInventory[teamMembers[turnIndex]].elementPower) * 100 / (float)(100 + enemy[enemyIndex].defense);
												playerDamage = (int)caster * 22 / 10;
												enemyHP -= playerDamage;

												if (enemyHP < 0)
													enemyHP = 0;

												// Prevents HP To go super high
												if (playerHP > playerInventory[teamMembers[turnIndex]].hp)
													playerHP = playerInventory[teamMembers[turnIndex]].hp;

												// Banner
												system("cls");
												logo();
		
												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;

													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}
		
												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);
		
												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("Elemental skill!\n");
												printf("Enemy took %d damage!\n", (int)caster);
												printf("Enemy got poisoned and got %d extra damage!\n", (int)caster * 22 / 10 - (int)caster);
												
												getchar();
											}

											if (enemyHP != 0) {
												if (isElementalActive) {
													caster = damageRandomizer(enemy[enemyIndex].attack) * 100 / (float)(100 + playerInventory[teamMembers[turnIndex]].defense);
													enemyDamage = (int)caster;

													if (elementalRoleType == 0)
														enemyDamage = (int)caster / 10 * 3;
													else if (elementalRoleType == 1)
														enemyDamage = (int)caster / 5;

													playerHP -= enemyDamage;

													if (elementalRoleType == 1)
														elementalSkillCounter--;
												}
												else {
													caster = damageRandomizer(enemy[enemyIndex].attack) * 100 / (float)(100 + playerInventory[teamMembers[turnIndex]].defense);
													enemyDamage = (int)caster;
													playerHP -= enemyDamage;
												}

												// To prevent player hp become 0
												if (playerHP < 0)
													playerHP = 0;

												// Banner
												system("cls");
												logo();

												printf(" Round %d \n", i + 1);
												printf("==========\n\n");

												if (teamSizeInput != 1) {
													printedComa = 0;
													
													printf("Team Members Remaining : \n");
													
													for (j = 0; j < teamSizeInput; j++) {
														if (j == turnIndex)
															continue;
														
														if (j >= turnIndex)
															printf("%s", heroes[teamMembers[j]].name);
														else
															printf("%s (Died)", heroes[teamMembers[j]].name);

														if (printedComa < teamSizeInput - 2) {
															printf(", ");

															printedComa++;
														}
													}
												
													puts("\n");
												}

												printf("%s \n", heroes[teamMembers[turnIndex]].name);
												printf("VS.\n");
												printf("%s \n\n", enemy[enemyIndex].name);

												printf("%s\'s HP : %d\n", heroes[teamMembers[turnIndex]].name, playerHP);
												printf("%s\'s HP : %d\n\n", enemy[enemyIndex].name, enemyHP);

												printf("%s attacks, you took %d damage!\n", enemy[enemyIndex].name, enemyDamage);

												getchar();
											}

											// Elemental charge reset
											elementalCharge = 0;
										}

										// If enemy dies
										if (enemyHP == 0) {
											if (i == rng1 - 1) {
												printf("You WIN the challenge!\n");

												if (OneVsOneWarp == 1) {
													printf("You get 1000 gold! ");

													player[userIndex].gold += 1000;
												}
												else if (OneVsOneWarp == 2) {
													printf("You get 100 diamond! ");

													player[userIndex].diamond += 100;
												}
												else if (OneVsOneWarp == 3) {
													printf("You get 500 diamond! ");

													player[userIndex].diamond += 500;
												}

												// Gold Boost Updater
												if (OneVsOneWarp == 1 && player[userIndex].goldBoost < 5) {
													printf("\nNow you\'ll get 5 gold each click in gold generator!\n");
													player[userIndex].goldBoost = 5;
												}
												else if (OneVsOneWarp == 2 && player[userIndex].goldBoost < 20) {
													printf("\nNow you\'ll get 20 gold each click in gold generator!\n");
													player[userIndex].goldBoost = 20;
												}
												else if (OneVsOneWarp == 3 && player[userIndex].goldBoost < 100) {
													printf("\nNow you\'ll get 100 gold each click in gold generator!\n");
													player[userIndex].goldBoost = 100;
												}
												
												printf("Press \'Enter\' to go back to main menu!");

												player[userIndex].wins++;
											}
											else {
												printf("Round %d complete!, ", i + 1);

												if (OneVsOneWarp == 1) {
													printf("You get 1000 gold! ");

													player[userIndex].gold += 1000;
												}
												else if (OneVsOneWarp == 2) {
													printf("You get 100 diamond! ");

													player[userIndex].diamond += 100;
												}
												else if (OneVsOneWarp == 3) {
													printf("You get 500 diamond! ");

													player[userIndex].diamond += 500;
												}

												printf("press \'Enter\' to go to round %d!", i + 2);
											}	

											getchar();

											if (elementalRoleType == 4 && isElementalActive) {
												elementalSkillCounter = 0;
												isElementalActive = false;
											}

											fileUpdate(accounts, player, totalData);

											continue;
										}

										// If all player dies
										if (playerHP == 0 && turnIndex == teamSizeInput - 1) {
											validLost = true;
											player[userIndex].loses++;
											elementalCharge = 0;
											isElementalActive = false;
											elementalSkillCounter = 0;
	
											printf("%s died!\n", heroes[teamMembers[turnIndex]].name);
											printf("YOU LOSE!");
											getchar();

											fileUpdate(accounts, player, totalData);
	
											break;
										}
	
										// If player dies
										if (playerHP == 0) {
											printf("\n%s died, %s is ready to substitute!", heroes[teamMembers[turnIndex]].name, heroes[teamMembers[turnIndex + 1]].name);
											getchar();
	
											turnIndex++;
											playerHP = playerInventory[teamMembers[turnIndex]].hp;
											elementalCharge = 0;
											isElementalActive = false;
											elementalSkillCounter = 0;
										}

										if (OneVsOneWarp2 == 5) {
											printf("You ran, better luck next time!");
											getchar();

											player[userIndex].loses++;

											break;
										}
									}
									while (enemyHP > 0);
	
									if (validLost || OneVsOneWarp2 == 5)
										break;
								}
							}
						}
						while (OneVsOneWarp != 4);
					}
					
					// Punching bag arena
					else if (gameMenuWarp == 4) {
						do
						{
							canEnterPunchingBag = false;
							
							for (i = 0; i < 24; i++) {
								if (playerInventory[i].owned == 1) {
									canEnterPunchingBag = true;
									
									break;
								}
							}
							
							if (!canEnterPunchingBag) {
								printf("\nYou need to have at least 1 character to enter the punching bag arena!");
								getchar();
								
								break;
							}
							
							do
							{
								// Banner
								system("cls");
								printf(" Punching Bag Arena \n");
								printf("====================\n\n");

								// Player Warp UI
								printf("Where do you want to go?\n");
								printf("1. Punching Bag\n");
								printf("2. Game Menu\n\n");

								printf("Your Choice : ");
								scanf("%d", &punchingBagWarp);
								while (getchar() != '\n');
							}
							while (punchingBagWarp != 1 && punchingBagWarp != 2);

							if (punchingBagWarp == 1) {
								do
								{
									validHP = true;

									// Banner
									system("cls");
									printf(" Punching Bag Arena \n");
									printf("====================\n\n");

									// UI
									printf("How tough you want the punching bag to be?\n");
									printf("(Note: HP must be between 30-10000)!\n\n");

									printf("Input HP : ");
									scanf("%s", punchingBagHPStr);
									while (getchar() != '\n');
									
									// Valid HP Checker
									for (i = 0; i < strlen(punchingBagHPStr); i++) {
										if (!isdigit(punchingBagHPStr[i])) {
											validHP = false;
											break;
										}
									}

									punchingBagHP = atoi(punchingBagHPStr);
								}
								while (punchingBagHP < 30 || punchingBagHP > 10000 || !validHP);

								// Character Picking
								do
								{
									validStart = true;

									// Banner
									system("cls");
									printf(" Punching Bag Arena \n");
									printf("====================\n\n");
									
									printf("Characters Owned:\n");
								
									for (i = 0; i < 24; i++) {
										if (playerInventory[i].owned == 1)
											printf("%s Lv. %d (%d*)\n", heroes[i].name, playerInventory[i].level, heroes[i].rarity);
									}
									
									puts("");
									
									// UI
									printf("Choose a character to enter punching bag : ");
									scanf("%s", characterName);
									while (getchar() != '\n');
									
									// Valid character name check
									for (i = 0; i < 24; i++) {
										if (strcmp(characterName, heroes[i].name) == 0) {
											heroIndex = i;
											break;
										}

										if (i == 23) {
											printf("Character name not exist!");
											getchar();

											validStart = false;

											break;
										}
									}

									if (!validStart)
										continue;

									// Valid Owned Check
									if (playerInventory[heroIndex].owned != 1) {
										printf("You don't own that character!");
										getchar();

										continue;
									}

									break;
								}
								while (true);
								
								elementalAttackAmount = 0;
								basicAttackAmount = 0;
								highestDamage = 0;

								// Punching bag arena
								while (punchingBagHP > 0) {
									do
									{
										// Banner
										system("cls");
										printf(" Punching Bag Arena \n");
										printf("====================\n\n");

										printf("Character : %s\n", heroes[heroIndex].name);
										printf("Punching Bag HP : %d\n\n", punchingBagHP);

										// Punching Bag Attack UI
										printf("How do you wanna attack?\n");
										printf("1. Use Basic Attack\n");
										printf("2. Use Elemental Attack\n");
										printf("3. Exit Arena\n\n");

										printf("Input : ");
										scanf("%d", &punchingBagWarp2);
										while (getchar() != '\n');
									}
									while (punchingBagWarp2 != 1 && punchingBagWarp2 != 2 && punchingBagWarp2 != 3);
									
									// If player uses basic attack
									if (punchingBagWarp2 == 1) {
										playerDamage = damageRandomizer(playerInventory[heroIndex].attack);
										punchingBagHP -= playerDamage;
										basicAttackAmount++;
									}
									
									// If player uses magic attack
									else if (punchingBagWarp2 == 2) {
										playerDamage = damageRandomizer(playerInventory[heroIndex].elementPower);
										punchingBagHP -= playerDamage;
										elementalAttackAmount++;
									}
									
									// If player exits
									else if (punchingBagWarp2 == 3) {
										printf("You exited punching bag arena");
										getchar();
										
										break;
									}
									
									if (punchingBagHP <= 0)
										punchingBagHP = 0;
									
									// Banner
									system("cls");
									printf(" Punching Bag Arena \n");
									printf("====================\n\n");

									printf("Character : %s\n", heroes[heroIndex].name);
									printf("Punching Bag HP : %d\n\n", punchingBagHP);

									// Punching Bag Attack UI
									printf("How do you wanna attack?\n");
									printf("1. Use Basic Attack\n");
									printf("2. Use Elemental Attack\n");
									printf("3. Exit Arena\n\n");
									
									// If player uses basic attack
									if (punchingBagWarp2 == 1)
										printf("%s uses basic attack!\n", heroes[heroIndex].name);

									// If player uses magic attack
									else if (punchingBagWarp2 == 2)
										printf("%s uses elemental attack!\n", heroes[heroIndex].name);
									
									printf("Punching bag took %d damage!", playerDamage);
									getchar();

									if (highestDamage < playerDamage)
										highestDamage = playerDamage;

									// If punching bag destroyed
									if (punchingBagHP <= 0) {
										// Banner
										system("cls");
										printf(" Punching Bag Arena \n");
										printf("====================\n\n");

										printf("Character : %s\n", heroes[heroIndex].name);
										printf("Punching Bag HP : %d\n\n", punchingBagHP);
										
										printf("You use basic attack %d times\n", basicAttackAmount);
										printf("You use elemental attack %d times\n", elementalAttackAmount);
										printf("The highest damage that you did to the punching bag is %d!\n\n", highestDamage);

										printf("Punching bag destroyed!");
										getchar();
									}
								}
							}
						}
						while (punchingBagWarp != 2);
					}
					
					// Chest Shop
					else if (gameMenuWarp == 5) {
						do
						{
							do
							{
								// Banner
								system("cls");
								printf(" Chest Shop \n");
								printf("============\n\n");
								
								moneyPrint(player, userIndex);
								
								printf("Chests:\n");
								printf("1. Bronze Chest (500 gold)\n");
								printf("2. Silver Chest (50 diamond)\n");
								printf("3. Gold Chest (250 diamond)\n");
								printf("4. Diamond Chest (1000 diamond)\n\n");
								
								printf("Type 5 to go back to game menu\n\n");
								
								printf("Your choice : ");
								scanf("%d", &shopWarp);
								while (getchar() != '\n');
							}
							while (shopWarp != 1 && shopWarp != 2 && shopWarp != 3 && shopWarp != 4 && shopWarp != 5);
							
							// Bronze Chest
							if (shopWarp == 1) {
								// Check if the diamond is enough or no
								if (player[userIndex].gold < 500) {
									printf("\nNot enough gold!\n");
									printf("Press \'Enter\' to go back!");
									getchar();

									continue;
								}
								
								system("cls");
								
								player[userIndex].gold -= 500;
								printf("You got:\n");
								
								for (i = 0; i < 2; i++) {
									star = i + 1;
									cardIndex = cardFinder(star);
									playerInventory[cardIndex].owned = 1;
									
									// Bronze chest gacha code
									if (i == 0) {
										printf("10 %s (1*)", heroes[cardIndex].name);
										
										playerInventory[cardIndex].amount += 10;
									}
									else {
										printf("1 %s (2*)", heroes[cardIndex].name);
										
										playerInventory[cardIndex].amount++;
									}
									
									getchar();
								}
							}
							
							// Silver Chest
							else if (shopWarp == 2) {
								// Check if the diamond is enough or no
								if (player[userIndex].diamond < 50) {
									notEnoughDiamond();
									continue;
								}
								
								system("cls");
								
								player[userIndex].diamond -= 50;
								
								// Gacha System
								gachaIndex = 0;
								rng1 = rand() % 100;

								// If player gets the 1% chance 3*
								if (rng1 == 0) {
									do
									{
										typeAmounts[0] = rand() % 2 + 1;
										typeAmounts[1] = rand() % 2 + 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] != 3);
								}

								// If the player gets the other 99%
								else {
									do
									{
										typeAmounts[0] = rand() % 3 + 1;
										typeAmounts[1] = rand() % 3 + 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] != 4);
								}

								for (i = 0; i < 2; i++) {
									do
									{
										validGacha = true;
										totalCards = 0;

										for (j = 0; j < typeAmounts[i]; j++) {
											if (i == 0) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 50;
													totalCards = 50;
												}
												else {
													cardAmounts[i][j] = rand() % 49 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
											else if (i == 1) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 4;
													totalCards = 4;
												}
												else {
													cardAmounts[i][j] = rand() % 3 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
										}

										if (i == 0 && totalCards != 50)
											validGacha = false;

										if (i == 1 && totalCards != 4)
											validGacha = false;
									}
									while (validGacha == false);
								}

								// Gacha Making
								for (i = 0; i < 4; i++) {
									if (typeAmounts[gachaIndex] == 0)
										gachaIndex++;
									
									star = gachaIndex + 1;

									// Check if card ever exist or no
									do
									{
										validGacha = true;
										cardIndex = cardFinder(star);
										
										if (i > 0) {
											for (j = 0; j < i; j++) {
												if (cardIndex == cardDoneIndex[j]) {
													validGacha = false;
													break;
												}
											}
										}
									}
									while (validGacha == false);

									if (star == 3) {
										printf("1 %s (3*)\n", heroes[cardIndex].name);
										playerInventory[cardIndex].amount++;
									}
									else {
										printf("%d %s (%d*)\n", cardAmounts[gachaIndex][typeAmounts[gachaIndex] - 1], heroes[cardIndex].name, gachaIndex + 1);
										playerInventory[cardIndex].amount += cardAmounts[gachaIndex][typeAmounts[gachaIndex] - 1];
									}

									cardDoneIndex[i] = cardIndex;
									playerInventory[cardIndex].owned = 1;
									typeAmounts[gachaIndex]--;
									
									getchar();
								}
							}
							
							// Gold Chest
							else if (shopWarp == 3) {
								// Check if the diamond is enough or no
								if (player[userIndex].diamond < 250) {
									notEnoughDiamond();
									continue;
								}
								
								system("cls");
								
								player[userIndex].diamond -= 250;
								
								// Gacha System
								gachaIndex = 0;
								rng1 = rand() % 100;

								// If player gets the 1% chance 4*
								if (rng1 == 0) {
									do
									{
										typeAmounts[0] = rand() % 3 + 1;
										typeAmounts[1] = rand() % 3 + 1;
										typeAmounts[2] = rand() % 3 + 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] + typeAmounts[2] != 5);
								}

								// If the player gets the other 99%
								else {
									do
									{
										typeAmounts[0] = rand() % 4 + 1;
										typeAmounts[1] = rand() % 4 + 1;
										typeAmounts[2] = rand() % 4 + 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] + typeAmounts[2] != 6);
								}

								for (i = 0; i < 3; i++) {
									do
									{
										validGacha = true;
										totalCards = 0;

										for (j = 0; j < typeAmounts[i]; j++) {
											if (i == 0) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 200;
													totalCards = 200;
												}
												else {
													cardAmounts[i][j] = rand() % 199 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
											else if (i == 1) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 50;
													totalCards = 50;
												}
												else {
													cardAmounts[i][j] = rand() % 49 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
											else if (i == 2) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 4;
													totalCards = 4;
												}
												else {
													cardAmounts[i][j] = rand() % 3 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
										}

										if (i == 0 && totalCards != 200)
											validGacha = false;
										if (i == 1 && totalCards != 50)
											validGacha = false;
										if (i == 2 && totalCards != 4)
											validGacha = false;
									}
									while (validGacha == false);
								}

								// Gacha Making
								for (i = 0; i < 6; i++) {
									if (typeAmounts[gachaIndex] == 0)
										gachaIndex++;
									
									star = gachaIndex + 1;

									// Check if card ever exist or no
									do
									{
										validGacha = true;
										cardIndex = cardFinder(star);
										
										if (i > 0) {
											for (j = 0; j < i; j++) {
												if (cardIndex == cardDoneIndex[j]) {
													validGacha = false;
													break;
												}
											}
										}
									}
									while (validGacha == false);

									if (star == 4) {
										printf("1 %s (4*)\n", heroes[cardIndex].name);
										playerInventory[cardIndex].amount++;
									}
									else {
										printf("%d %s (%d*)\n", cardAmounts[gachaIndex][typeAmounts[gachaIndex] - 1], heroes[cardIndex].name, gachaIndex + 1);
										playerInventory[cardIndex].amount += cardAmounts[gachaIndex][typeAmounts[gachaIndex] - 1];
									}

									cardDoneIndex[i] = cardIndex;
									playerInventory[cardIndex].owned = 1;
									typeAmounts[gachaIndex]--;
									
									getchar();
								}
							}
							
							// Diamond Chest
							else if (shopWarp == 4) {
								// Check if the diamond is enough or no
								if (player[userIndex].diamond < 1000) {
									notEnoughDiamond();
									continue;
								}
								
								system("cls");
								
								player[userIndex].diamond -= 1000;
								
								// Gacha System
								gachaIndex = 0;
								rng1 = rand() % 100;
								rng2 = rand() % 100;

								// If the player is super lucky
								if (rng1 == 0 && rng2 == 0) {
									do
									{
										typeAmounts[0] = rand() % 4 + 1;
										typeAmounts[1] = rand() % 4 + 1;
										typeAmounts[2] = rand() % 4 + 1;
										typeAmounts[3] = rand() % 4 + 1;
										typeAmounts[4] = 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] + typeAmounts[2] + typeAmounts[3] != 6);
								}

								// If player gets the 1% chance 5*
								else if (rng1 == 0) {
									do
									{
										typeAmounts[0] = rand() % 4 + 1;
										typeAmounts[1] = rand() % 4 + 1;
										typeAmounts[2] = rand() % 4 + 1;
										typeAmounts[3] = rand() % 4 + 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] + typeAmounts[2] + typeAmounts[3] != 7);
								}

								// If the player gets the other 99%
								else {
									do
									{
										typeAmounts[0] = rand() % 5 + 1;
										typeAmounts[1] = rand() % 5 + 1;
										typeAmounts[2] = rand() % 5 + 1;
										typeAmounts[3] = rand() % 4 + 1;
									} 
									while (typeAmounts[0] + typeAmounts[1] + typeAmounts[2] + typeAmounts[3] != 8);
								}

								for (i = 0; i < 4; i++) {
									do
									{
										validGacha = true;
										totalCards = 0;

										for (j = 0; j < typeAmounts[i]; j++) {
											if (i == 0) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 1000;
													totalCards = 1000;
												}
												else {
													cardAmounts[i][j] = rand() % 999 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
											else if (i == 1) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 200;
													totalCards = 200;
												}
												else {
													cardAmounts[i][j] = rand() % 199 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
											else if (i == 2) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 50;
													totalCards = 50;
												}
												else {
													cardAmounts[i][j] = rand() % 49 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
											else if (i == 3) {
												if (typeAmounts[i] == 1) {
													cardAmounts[i][j] = 10;
													totalCards = 10;
												}
												else {
													cardAmounts[i][j] = rand() % 9 + 1;
													totalCards += cardAmounts[i][j];
												}
											}
										}

										if (i == 0 && totalCards != 1000)
											validGacha = false;
										if (i == 1 && totalCards != 200)
											validGacha = false;
										if (i == 2 && totalCards != 50)
											validGacha = false;
										if (i == 3 && totalCards != 10)
											validGacha = false;
									}
									while (validGacha == false);
								}

								// Gacha Making
								for (i = 0; i < 8; i++) {
									if (typeAmounts[gachaIndex] == 0 || gachaIndex == 4)
										gachaIndex++;
									
									star = gachaIndex + 1;

									// Check if card ever exist or no
									do
									{
										validGacha = true;
										cardIndex = cardFinder(star);
										
										if (i > 0) {
											for (j = 0; j < i; j++) {
												if (cardIndex == cardDoneIndex[j]) {
													validGacha = false;
													break;
												}
											}
										}
									}
									while (validGacha == false);

									if (star == 5) {
										printf("1 %s (5*)\n", heroes[cardIndex].name);
										playerInventory[cardIndex].amount++;
									}
									else if (star == 6) {
										printf("1 %s (6*)\n", heroes[cardIndex].name);
										printf("CONGRATS ON WINNING A LEGEND CARD!!!\n");
										playerInventory[cardIndex].amount++;
									}
									else {
										printf("%d %s (%d*)\n", cardAmounts[gachaIndex][typeAmounts[gachaIndex] - 1], heroes[cardIndex].name, gachaIndex + 1);
										playerInventory[cardIndex].amount += cardAmounts[gachaIndex][typeAmounts[gachaIndex] - 1];
									}

									cardDoneIndex[i] = cardIndex;
									playerInventory[cardIndex].owned = 1;
									typeAmounts[gachaIndex]--;
									
									getchar();
								}
							}
							
							// Gacha end word
							if (!(shopWarp != 1 && shopWarp != 2 && shopWarp != 3 && shopWarp != 4)) {
								printf("Chest opening ended, press \'Enter\' to continue");
								getchar();
							}

							// File Update
							player[userIndex].powerLevel = powerLevelCounter(player, playerInventory, 23);

							fileUpdate(accounts, player, totalData);
							inventoryUpdate(fptr, playerInventory, fileName);
						}
						while (shopWarp != 5);
					}
				}
				while (gameMenuWarp != 6);
			}
			
			// Inventory Menu
			else if (menuWarp == 2) {
				// Banner
				do
				{
					system("cls");
					logo();
					
					printf(" %s\'s Inventory \n", player[userIndex].username);
					
					for (i = 0; i < strlen(player[userIndex].username) + 14; i++)
						printf("=");
					
					puts("\n");
					
					// List Printf
					printf("%-18s | %-7s | %-12s | %-12s | %-8s | %-8s | %-8s | %-8s | %-8s\n", "Name", "Level", "Role", "Status", "Amount", "Atk", "HP", "Def", "Element Power");
					printf("=========================================================================================================================\n");
					
					for (i = 0; i < 24; i++) {
						printf("%-18s | %-7d | ", heroes[i].name, playerInventory[i].level);
						
						if (heroes[i].role == 0)
							printf("%-12s | ", "All Around");
						if (heroes[i].role == 1)
							printf("%-12s | ", "Tank");
						if (heroes[i].role == 2)
							printf("%-12s | ", "Fighter");
						if (heroes[i].role == 3)
							printf("%-12s | ", "Assassin");
						if (heroes[i].role == 4)
							printf("%-12s | ", "Mage");
						
						if (playerInventory[i].owned == 0)
							printf("%-12s | ", "Not Owned");
						else
							printf("%-12s | ", "Owned");
						
						printf("%-8d | %-8d | %-8d | %-8d | %-8d", playerInventory[i].amount, playerInventory[i].attack, playerInventory[i].hp, playerInventory[i].defense, playerInventory[i].elementPower);
							
						puts("");
					}
					puts("");
					
					printf("Where do you want to go?\n");
					printf("1. Upgrade Card\n");
					printf("2. Main Menu\n\n");

					do
					{
						printf("Your choice : ");
						scanf("%d", &inventoryWarp);
						while (getchar() != '\n');
					}
					while (inventoryWarp != 1 && inventoryWarp != 2);

					if (inventoryWarp == 1) {
						// Banner
						do
						{
							system("cls");
							logo();

							validUpgradeWarp = 1;

							// Player picks a card that wants to be upgraded
							printf("What card name you want to upgrade : ");
							scanf("%s", upgradeName);
							while (getchar() != '\n');

							// Name Check
							if (strcmp(upgradeName, "traveler") == 0)
								heroIndex = 0;
							else if (strcmp(upgradeName, "amber") == 0)
								heroIndex = 1;
							else if (strcmp(upgradeName, "kaeya") == 0)
								heroIndex = 2;
							else if (strcmp(upgradeName, "lisa") == 0)
								heroIndex = 3;
							else if (strcmp(upgradeName, "noelle") == 0)
								heroIndex = 4;
							else if (strcmp(upgradeName, "barbara") == 0)
								heroIndex = 5;
							else if (strcmp(upgradeName, "bennett") == 0)
								heroIndex = 6;
							else if (strcmp(upgradeName, "fischl") == 0)
								heroIndex = 7;
							else if (strcmp(upgradeName, "razor") == 0)
								heroIndex = 8;
							else if (strcmp(upgradeName, "sucrose") == 0)
								heroIndex = 9;
							else if (strcmp(upgradeName, "xiangling") == 0)
								heroIndex = 10;
							else if (strcmp(upgradeName, "diluc") == 0)
								heroIndex = 11;
							else if (strcmp(upgradeName, "keqing") == 0)
								heroIndex = 12;
							else if (strcmp(upgradeName, "mona") == 0)
								heroIndex = 13;
							else if (strcmp(upgradeName, "qiqi") == 0)
								heroIndex = 14;
							else if (strcmp(upgradeName, "venti") == 0)
								heroIndex = 15;
							else if (strcmp(upgradeName, "zhongli") == 0)
								heroIndex = 16;
							else if (strcmp(upgradeName, "guardian") == 0)
								heroIndex = 17;
							else if (strcmp(upgradeName, "stong") == 0)
								heroIndex = 18;
							else if (strcmp(upgradeName, "odading") == 0)
								heroIndex = 19;
							else if (strcmp(upgradeName, "steve") == 0)
								heroIndex = 20;
							else if (strcmp(upgradeName, "x") == 0)
								heroIndex = 21;
							else if (strcmp(upgradeName, "supra") == 0)
								heroIndex = 22;
							else if (strcmp(upgradeName, "king") == 0)
								heroIndex = 23;
							else {
								validUpgradeWarp = 0;

								break;
							}
							
							// Level Check
							switch (heroIndex) {
								case 0:
								case 1:
								case 2:
								case 3:
								case 4:
								case 5:
								case 6:
								case 7:
								case 8:
								case 9:
								case 10:
								case 11:
								case 12:
								case 13:
								case 14:
								case 15:
								case 16:
								case 17:
								case 18:
								case 19:
								case 20:
									if (playerInventory[heroIndex].level == 10)
										validUpgradeWarp = 2;
									
									break;
									
								case 21:
								case 22:
									if (playerInventory[heroIndex].level == 5)
										validUpgradeWarp = 2;
									
									break;
									
								case 23:
									if (playerInventory[heroIndex].level == 3)
										validUpgradeWarp = 2;
									
									break;
							}

							if (validUpgradeWarp == 2)
								break;
							
							// Gold and Card check
							if (playerInventory[heroIndex].level == 1) {
								if (player[userIndex].gold < 100) {
									validUpgradeWarp = 3;
									missingGold = 100;

									break;
								}
								if (playerInventory[heroIndex].amount < 4) {
									validUpgradeWarp = 4;
									missingCard = 4;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 2) {
								if (player[userIndex].gold < 200) {
									validUpgradeWarp = 3;
									missingGold = 200;

									break;
								}
								if (playerInventory[heroIndex].amount < 10) {
									validUpgradeWarp = 4;
									missingCard = 10;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 3) {
								if (player[userIndex].gold < 500) {
									validUpgradeWarp = 3;
									missingGold = 500;

									break;
								}
								if (playerInventory[heroIndex].amount < 20) {
									validUpgradeWarp = 4;
									missingCard = 20;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 4) {
								if (player[userIndex].gold < 1000) {
									validUpgradeWarp = 3;
									missingGold = 1000;

									break;
								}
								if (playerInventory[heroIndex].amount < 50) {
									validUpgradeWarp = 4;
									missingCard = 50;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 5) {
								if (player[userIndex].gold < 2000) {
									validUpgradeWarp = 3;
									missingGold = 2000;

									break;
								}
								if (playerInventory[heroIndex].amount < 100) {
									validUpgradeWarp = 4;
									missingCard = 100;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 6) {
								if (player[userIndex].gold < 5000) {
									validUpgradeWarp = 3;
									missingGold = 5000;

									break;
								}
								if (playerInventory[heroIndex].amount < 200) {
									validUpgradeWarp = 4;
									missingCard = 200;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 7) {
								if (player[userIndex].gold < 10000) {
									validUpgradeWarp = 3;
									missingGold = 10000;

									break;
								}
								if (playerInventory[heroIndex].amount < 500) {
									validUpgradeWarp = 4;
									missingCard = 500;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 8) {
								if (player[userIndex].gold < 20000) {
									validUpgradeWarp = 3;
									missingGold = 20000;

									break;
								}
								if (playerInventory[heroIndex].amount < 1000) {
									validUpgradeWarp = 4;
									missingCard = 1000;

									break;
								}
							}
							else if (playerInventory[heroIndex].level == 9) {
								if (player[userIndex].gold < 50000) {
									validUpgradeWarp = 3;
									missingGold = 50000;

									break;
								}
								if (playerInventory[heroIndex].amount < 2000) {
									validUpgradeWarp = 4;
									missingCard = 2000;

									break;
								}
							}

							break;
						}
						while (1 < 0);

						// Valid upgrade input
						if (validUpgradeWarp == 0)
							printf("Card doesn't exist!");
						else if (validUpgradeWarp == 2)
							printf("Character is already at max level!");
						else if (validUpgradeWarp == 3)
							printf("Not enough golds!, You need %d golds.", missingGold);
						else if (validUpgradeWarp == 4)
							printf("Not enough cards!, You need %d cards.", missingCard);
						else if (validUpgradeWarp == 1) {
							// Inventory Updater
							// Resources
							if (playerInventory[heroIndex].level == 1) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 100);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 4);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 2);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 80);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 2);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 21);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 304);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 21);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 9);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 223);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 9);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 36);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 471);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 36);
									}
									else if (heroes[heroIndex].rarity == 5) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 110);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 1171);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 110);
									}
									else if (heroes[heroIndex].rarity == 6) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 357);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 3412);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 357);
									}

									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 100;
								playerInventory[heroIndex].amount -= 4;
							}
							else if (playerInventory[heroIndex].level == 2) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 200);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 10);

									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 4);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 85);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 4);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 23);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 306);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 23);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 11);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 224);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 11);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 38);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 473);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 38);
									}
									else if (heroes[heroIndex].rarity == 5) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 111);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 1173);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 111);
									}
									else if (heroes[heroIndex].rarity == 6) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 455);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 6388);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 455);
									}

									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 200;
								playerInventory[heroIndex].amount -= 10;
							}
							else if (playerInventory[heroIndex].level == 3) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 500);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 20);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 8);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 93);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 8);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 25);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 308);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 25);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 13);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 225);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 13);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 40);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 475);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 40);
									}
									else if (heroes[heroIndex].rarity == 5) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 160);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 1493);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 160);
									}
									
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 500;
								playerInventory[heroIndex].amount -= 20;
							}
							else if (playerInventory[heroIndex].level == 4) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 1000);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 50);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 10);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 98);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 10);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 27);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 310);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 27);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 15);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 226);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 15);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 42);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 477);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 42);
									}
									else if (heroes[heroIndex].rarity == 5) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 162);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 1495);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 162);
									}
									
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 1000;
								playerInventory[heroIndex].amount -= 50;
							}
							else if (playerInventory[heroIndex].level == 5) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 2000);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 100);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 18);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 244);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 18);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 7);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 178);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 7);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 29);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 376);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 29);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 43);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 467);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 43);
									}
									
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 2000;
								playerInventory[heroIndex].amount -= 100;
							}
							else if (playerInventory[heroIndex].level == 6) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 5000);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 200);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 19);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 245);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 19);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 8);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 179);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 8);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 30);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 377);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 30);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 44);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 468);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 44);
									}
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 5000;
								playerInventory[heroIndex].amount -= 200;
							}
							else if (playerInventory[heroIndex].level == 7) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 10000);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 500);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 20);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 246);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 20);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 9);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 180);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 9);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 31);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 378);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 31);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 45);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 469);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 45);
									}
									
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;
								
								player[userIndex].gold -= 10000;
								playerInventory[heroIndex].amount -= 500;
							}
							else if (playerInventory[heroIndex].level == 8) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 20000);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 1000);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 21);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 247);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 21);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 10);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 181);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 10);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 32);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 379);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 32);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 46);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 470);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 46);
									}
									
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 20000;
								playerInventory[heroIndex].amount -= 1000;
							}
							else if (playerInventory[heroIndex].level == 9) {
								do
								{
								// Banner
									system("cls");

									printf(" Upgrade to level %d? \n", playerInventory[heroIndex].level + 1);
									printf("==========================");
									
									puts("\n");

									printf("Your gold : %d -> %d\n", player[userIndex].gold, player[userIndex].gold - 50000);
									printf("Card amount : %d -> %d\n", playerInventory[heroIndex].amount, playerInventory[heroIndex].amount - 2000);
									
									if (heroes[heroIndex].rarity == 1) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 22);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 248);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 22);
									}
									else if (heroes[heroIndex].rarity == 2) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 11);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 182);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 11);
									}
									else if (heroes[heroIndex].rarity == 3) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 33);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 380);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 33);
									}
									else if (heroes[heroIndex].rarity == 4) {
										printf("Attack : %d -> %d\n", playerInventory[heroIndex].attack, playerInventory[heroIndex].attack + 47);
										printf("HP : %d -> %d\n", playerInventory[heroIndex].hp, playerInventory[heroIndex].hp + 471);
										printf("Deffense : %d -> %d\n", playerInventory[heroIndex].defense, playerInventory[heroIndex].defense + 1);
										printf("Element Power : %d -> %d\n\n", playerInventory[heroIndex].elementPower, playerInventory[heroIndex].elementPower + 47);
									}
									
									printf("Are you sure you want to upgrade?\n");
									printf("(y = yes, n = no)\n\n");

									printf("Input : ");
									scanf("%c", &YorNstatement);
									while (getchar() != '\n');
								}
								while (YorNstatement != 'y' && YorNstatement != 'n');

								if (YorNstatement == 'n')
									continue;

								player[userIndex].gold -= 50000;
								playerInventory[heroIndex].amount -= 2000;
							}

							// Stats
							if (playerInventory[heroIndex].level == 1) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 80;
									playerInventory[heroIndex].attack += 2;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 2;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 304;
									playerInventory[heroIndex].attack += 21;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 21;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 223;
									playerInventory[heroIndex].attack += 9;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 9;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 471;
									playerInventory[heroIndex].attack += 36;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 36;
								}
								else if (heroes[heroIndex].rarity == 5) {
									playerInventory[heroIndex].hp += 1171;
									playerInventory[heroIndex].attack += 110;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 110;
								}
								else if (heroes[heroIndex].rarity == 6) {
									playerInventory[heroIndex].hp += 3412;
									playerInventory[heroIndex].attack += 357;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 357;
								}
							}
							else if (playerInventory[heroIndex].level == 2) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 85;
									playerInventory[heroIndex].attack += 4;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 4;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 306;
									playerInventory[heroIndex].attack += 23;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 23;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 224;
									playerInventory[heroIndex].attack += 11;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 11;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 473;
									playerInventory[heroIndex].attack += 38;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 38;
								}
								else if (heroes[heroIndex].rarity == 5) {
									playerInventory[heroIndex].hp += 1173;
									playerInventory[heroIndex].attack += 111;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 111;
								}
								else if (heroes[heroIndex].rarity == 6) {
									playerInventory[heroIndex].hp += 6388;
									playerInventory[heroIndex].attack += 455;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 455;
								}
							}
							else if (playerInventory[heroIndex].level == 3) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 93;
									playerInventory[heroIndex].attack += 8;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 8;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 308;
									playerInventory[heroIndex].attack += 25;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 25;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 225;
									playerInventory[heroIndex].attack += 13;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 13;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 475;
									playerInventory[heroIndex].attack += 40;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 40;
								}
								else if (heroes[heroIndex].rarity == 5) {
									playerInventory[heroIndex].hp += 1493;
									playerInventory[heroIndex].attack += 160;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 160;
								}
							}
							else if (playerInventory[heroIndex].level == 4) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 98;
									playerInventory[heroIndex].attack += 10;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 10;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 310;
									playerInventory[heroIndex].attack += 27;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 27;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 226;
									playerInventory[heroIndex].attack += 15;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 15;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 477;
									playerInventory[heroIndex].attack += 42;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 42;
								}
								else if (heroes[heroIndex].rarity == 5) {
									playerInventory[heroIndex].hp += 1495;
									playerInventory[heroIndex].attack += 162;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 162;
								}
							}
							else if (playerInventory[heroIndex].level == 5) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 244;
									playerInventory[heroIndex].attack += 18;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 18;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 178;
									playerInventory[heroIndex].attack += 7;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 7;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 376;
									playerInventory[heroIndex].attack += 29;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 29;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 467;
									playerInventory[heroIndex].attack += 43;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 43;
								}
							}
							else if (playerInventory[heroIndex].level == 6) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 245;
									playerInventory[heroIndex].attack += 19;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 19;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 179;
									playerInventory[heroIndex].attack += 8;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 8;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 377;
									playerInventory[heroIndex].attack += 30;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 30;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 468;
									playerInventory[heroIndex].attack += 44;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 44;
								}
							}
							else if (playerInventory[heroIndex].level == 7) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 246;
									playerInventory[heroIndex].attack += 20;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 20;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 180;
									playerInventory[heroIndex].attack += 9;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 9;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 378;
									playerInventory[heroIndex].attack += 31;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 31;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 469;
									playerInventory[heroIndex].attack += 45;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 45;
								}
							}
							else if (playerInventory[heroIndex].level == 8) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 247;
									playerInventory[heroIndex].attack += 21;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 21;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 181;
									playerInventory[heroIndex].attack += 10;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 10;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 379;
									playerInventory[heroIndex].attack += 32;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 32;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 470;
									playerInventory[heroIndex].attack += 46;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 46;
								}
							}
							else if (playerInventory[heroIndex].level == 9) {
								if (heroes[heroIndex].rarity == 1) {
									playerInventory[heroIndex].hp += 248;
									playerInventory[heroIndex].attack += 22;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 22;
								}
								else if (heroes[heroIndex].rarity == 2) {
									playerInventory[heroIndex].hp += 182;
									playerInventory[heroIndex].attack += 11;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 11;
								}
								else if (heroes[heroIndex].rarity == 3) {
									playerInventory[heroIndex].hp += 380;
									playerInventory[heroIndex].attack += 33;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 33;
								}
								else if (heroes[heroIndex].rarity == 4) {
									playerInventory[heroIndex].hp += 471;
									playerInventory[heroIndex].attack += 47;
									playerInventory[heroIndex].defense += 1;
									playerInventory[heroIndex].elementPower += 47;
								}
							}
							
							playerInventory[heroIndex].level++;

							// File Update
							inventoryUpdate(fptr, playerInventory, fileName);
							fileUpdate(accounts, player, totalData);

							printf("%s upgraded to level %d!", playerInventory[heroIndex].name, playerInventory[heroIndex].level);
						}
						
						getchar();
					}
				}
				while (inventoryWarp != 2);	
			}
			
			// Instructions
			else if (menuWarp == 3) {
				system("cls");
				logo();

				printf(" Welcome To Genshin Get Overpowered \n");
				printf("=======================================\n\n");

				printf("	This is Genshin Get Overpowered or you can call GGO. The objective of this game is to get\n");
				printf("as overpowered as possible and try to beat all the difficulties as quickly as possible. \n");
				printf("The more power level, the more overpowered you are. In order to get more power\n");
				printf("level, you must get more characters and upgrade them. In order to upgrade cards, you\n");
				printf("have to collect enough card and golds.\n\n");

				printf("	There are 2 resources in GGO. The resources are gold and diamond. The value of\n");
				printf("1 diamond is equal to 1000 gold. You can convert your 1000 golds to 1 diamond or vice\n");
				printf("versa in the gold and diamond converter. You can only open chests with diamond and\n");
				printf("upgrade characters with gold.\n\n");

				printf("	There are 4 main roles and 1 special role in this game. The main role includes Tank,\n");
				printf("Fighter, Assassin, and Mage. The special role is All-around which only 1 character have it.\n");
				printf("Each role gives you benefits.\n");
				printf("- Tank grants you extra HP\n");
				printf("- Fighter grants you extra defense and some of them grants you extra damage\n");
				printf("- Assassin grants you extra attack damage\n");
				printf("- Mage grants you extra elemental damage\n");
				printf("- All-around grants you all bonus\n\n");

				printf("	In the 1v1 arena, you can use elemental skills. Each role has a different elemental skills.\n");
				printf("If the role is same, the skill then applies to all heroes, no matter what the name is.\n");
				printf("- Tank elemental skill reduces your damage by 75%% for 3 turns\n");
				printf("- Fighter elemental skill increases your damage 3x\n");
				printf("- Assassin elemental skill makes you attack 3 times in 1 turn\n");
				printf("- Mage elemental skill poisons the enemy for 3 turns\n");
				printf("- All-around elemental skill grants you an extra attack and defend by 30%% for 2 rounds\n\n");

				printf("There are 3 ways to get gold:\n");
				printf("1. Clicking \'Enter\' in gold generator\n");
				printf("2. Winning a 1v1 battle\n");
				printf("3. Convert the diamond to gold\n\n");

				printf("By clicking enter, you get 1 gold each click. But, if you beat 1v1 at any difficulty once, you get an\n");
				printf("additional gold per click.\n");
				printf("- Your gold per click is increased to 5 after beating easy\n");
				printf("- Your gold per click is increased to 20 after beating normal\n");
				printf("- Your gold per click is increased to 100 after beating hard\n\n");

				printf("	There are 6 rarity levels. The 6 star is a super rare character. If you manage to\n");
				printf("get 1, it means that you are super lucky. The max level of 1-4* character is 10, 5* max\n");
				printf("level is 5, and 6* max level is 3.\n\n");

				printf(" Chest Loots \n");
				printf("=============\n\n");

				printf("Bronze:\n");
				printf("-> 10 1*\n");
				printf("-> 1 2*\n\n");

				printf("Silver:\n");
				printf("-> 50 1*\n");
				printf("-> 4 2*\n");
				printf("-> 1 percent chance of 3*\n\n");

				printf("Gold:\n");
				printf("-> 200 1*\n");
				printf("-> 50 2*\n");
				printf("-> 4 3*\n");
				printf("-> 1 percent chance of 4*\n\n");

				printf("Diamond:\n");
				printf("-> 1000 1*\n");
				printf("-> 200 2*\n");
				printf("-> 50 3*\n");
				printf("-> 10 4*\n");
				printf("-> 1 percent chance of 5*\n");
				printf("-> 0.01 percent chance of 6*\n\n");

				printf("Press \'Enter\' to go back to main menu");
				getchar();
			}
			
			// Leaderboard
			else if (menuWarp == 4) {
				// Banner
				system("cls");
				logo();

				printf(" Leaderboards \n");
				printf("==============\n\n");

				// File Update
				player[userIndex].powerLevel = powerLevelCounter(player, playerInventory, 23);
				fileUpdate(accounts, player, totalData);

				// Sorting a leaderboard
				for (i = 0; i < totalData; i++) {
					sorterPowerLevel[i] = player[i].powerLevel;
					sorterIndex[i] = player[i].index;
				}
				
				for (i = 0; i < totalData; i++) {
					swap = 0;
					
					for (j = 0; j < totalData - 1; j++) {
						if (sorterPowerLevel[i] < sorterPowerLevel[j + 1]) {
							temp = sorterPowerLevel[i];
							sorterPowerLevel[i] = sorterPowerLevel[i + 1];
							sorterPowerLevel[i + 1] = temp;

							temp = sorterIndex[j];
							sorterIndex[j] = sorterIndex[j + 1];
							sorterIndex[j + 1] = temp;

							swap++;
						}
					}
					
					if (swap == 0)
						break;
				}

				// Printing a leaderboard
				printf("%-6s | %-24s | %-20s \n", "Rank", "Name", "Power Level");
				printf("=======================================================================\n");

				for (i = 0; i < totalData; i++)
					printf("%-6d | %-24s | %-20d \n", i + 1, player[sorterIndex[i]].username, player[sorterIndex[i]].powerLevel);

				printf("\nPress \'Enter\' to go back to main menu");
				getchar();
			}
			
			// Statistics
			else if (menuWarp == 5) {
				// Banner
				system("cls");
				logo();
				
				printf(" %s\'s Stats \n", player[userIndex].username);
				
				for (i = 0; i < strlen(player[userIndex].username) + 10; i++)
					printf("=");
				
				puts("\n");
				
				printf("Wins           : %d\n", player[userIndex].wins);
				printf("Loses          : %d\n\n", player[userIndex].loses);
				
				printf("Rank : ");
				
				if (powerLevelCounter(player, playerInventory, 23) < 100)
					printf("Noob\n");
				else if (powerLevelCounter(player, playerInventory, 23) >= 100 && powerLevelCounter(player, playerInventory, 23) < 10000)
					printf("Semi Noob\n");
				else if (powerLevelCounter(player, playerInventory, 23) >= 10000 && powerLevelCounter(player, playerInventory, 23) < 1000000)
					printf("Intermediate\n");
				else if (powerLevelCounter(player, playerInventory, 23) >= 1000000 && powerLevelCounter(player, playerInventory, 23) < 10000000)
					printf("Pro\n");
				else if (powerLevelCounter(player, playerInventory, 23) >= 10000000)
					printf("Ultimate\n");
				
				player[userIndex].powerLevel = powerLevelCounter(player, playerInventory, 23);

				printf("Power Level    : %d\n", player[userIndex].powerLevel);
				printf("1* card amount : %d\n", playerInventory[0].amount + playerInventory[1].amount + playerInventory[2].amount + playerInventory[3].amount + playerInventory[4].amount);
				printf("2* card amount : %d\n", playerInventory[5].amount + playerInventory[6].amount + playerInventory[7].amount + playerInventory[8].amount + playerInventory[9].amount + playerInventory[10].amount);
				printf("3* card amount : %d\n", playerInventory[11].amount + playerInventory[12].amount + playerInventory[13].amount + playerInventory[14].amount + playerInventory[15].amount + playerInventory[16].amount);
				printf("4* card amount : %d\n", playerInventory[17].amount + playerInventory[18].amount + playerInventory[19].amount + playerInventory[20].amount);
				printf("5* card amount : %d\n", playerInventory[21].amount + playerInventory[22].amount);
				printf("6* card amount : %d\n\n", playerInventory[23].amount);
				
				printf("Press \'Enter\' to go back to main menu!");
				getchar();
			}
			
			// Change Password
			else if (menuWarp == 6) {
				// Banner
				system("cls");
				logo();
				
				printf(" Change Password \n");
				printf("=================\n\n");
				
				// Password Print
				printf("Current Password : ");
				scanf("%s", password);
				while (getchar() != '\n');
				
				// Check if the password is valid or not
				validChange = passwordCheck(userIndex, player, password);
				
				if (validChange == false) {
					printf("Incorrect Password!");
					getchar();
					
					continue;
				}
				
				// Print the new password
				printf("New Password : ");
				scanf("%s", password);
				while (getchar() != '\n');
				
				printf("Confirm New Password : ");
				scanf("%s", confirmPassword);
				while (getchar() != '\n');
				
				// Check if the password and the confirm is the same
				if (strcmp(password, confirmPassword) != 0) {
					printf("Password and the confirm password is different!");
					getchar();
					
					continue;
				}
				
				// Password Encryptor
				for (i = 0; i < strlen(password); i++) {
					if (islower(password[i])) // 97
						password[i] = 97 + (password[i] - 97 + player[userIndex].encryption) % 26;
					else if (isupper(password[i])) // 65
						password[i] = 65 + (password[i] - 65 + player[userIndex].encryption) % 26;
					else if (isdigit(password[i])) // 48
						password[i] = 48 + (password[i] - 48 + player[userIndex].encryption) % 10;
				}
				
				strcpy(player[userIndex].password, password);
				fileUpdate(accounts, player, totalData);

				printf("\nPassword has been chanegd! Press \'Enter\' to go back!");
				getchar();
			}
		}
		while (menuWarp != 7 && menuWarp != 8);
	}
	while (menuWarp != 8);
	
	system("cls");
	logo();
	exitMenu();
	
	return 0;
}

void logo() {
	printf("  /==========//   /==========//   //=======\\\\                            \n");
	printf(" //              //              //         \\\\    \\\\                   \n");
	printf("//     /        //     /        //    /-\\    \\\\    \\\\                 \n");
	printf("\\\\     \\\\=======\\\\     \\\\=======\\\\    \\  \\    \\\\===[]=====]  \n");
	printf(" \\\\     \\   \\\\   \\\\     \\   \\\\   \\\\    \\-/    //   //         \n");
	printf("  \\\\         \\\\   \\\\         \\\\   \\\\         //   //             \n");
	printf("   \\===========\\   \\===========\\   \\\\=======//                       \n");
	printf("=============================================================              \n\n");
}

void exitMenu() {
	printf(" Thanks for playing! \n");
	printf("=====================\n\n");
	
	printf(" Credits \n");
	printf("=========\n\n");
	
	printf("Creator:\n");
	printf("Evan Louis Sutanto\n\n");

	printf("Creator Supervisor:\n");
	printf("Jonathan Owen Kuntjoro\n\n");

	printf("Prototype Designer:\n");
	printf("Evan Louis Sutanto\n");
	printf("Jonathan Owen Kuntjoro\n\n");

	printf("Tester:\n");
	printf("Evan Louis Sutanto\n");
	printf("Jonathan Owen Kuntjoro\n\n");

	printf("Supporter:\n");
	printf("VA Private Tutoring\n\n");

	printf("=========\n\n");

	printf("Press \'Enter\' to exit!");
	getchar();
}

void notEnoughDiamond() {
	printf("\nNot enough diamond!\n");
	printf("Press \'Enter\' to go back!");
	getchar();
}

void moneyPrint(User player[], int userIndex) {
	printf("Gold : %d\n", player[userIndex].gold);
	printf("Diamond : %d\n\n", player[userIndex].diamond);
}

void fileUpdate(FILE *accounts, User player[], int totalData) {
	int i;
	
	accounts = fopen("accounts.evan", "wb");
	
	for (i = 0; i < totalData; i++)
		fwrite(&player[i], sizeof(player[i]), 1, accounts);
	
	fclose(accounts);
}

void inventoryUpdate(FILE *fptr, Inventory playerInventory[], char fileName[]) {
	int i;
	
	fptr = fopen(fileName, "wb");
	
	for (i = 0; i < 24; i++)
		fwrite(&playerInventory[i], sizeof(playerInventory[i]), 1, fptr);
	
	fclose(fptr);
}

int cardFinder(int star) {
	if (star == 1)
		return rand() % 5;
	else if (star == 2)
		return rand() % 6 + 5;
	else if (star == 3)
		return rand() % 6 + 11;
	else if (star == 4)
		return rand() % 4 + 17;
	else if (star == 5)
		return rand() % 2 + 21;
	else if (star == 6)
		return 23;
}

int damageRandomizer(int damage) {
	int maxDamage = damage * 1.15;

	if (maxDamage - damage > 0)
		return rand() % (maxDamage - damage) + damage;
	else
		return damage;
}

int powerLevelCounter(User player[], Inventory playerInventory[], int recursiveNumber) {
	if (recursiveNumber == 0)
		return playerInventory[0].amount;
	else if (recursiveNumber > 0 && recursiveNumber < 5)
		return playerInventory[recursiveNumber].amount + powerLevelCounter(player, playerInventory, recursiveNumber - 1);
	else if (recursiveNumber > 4 && recursiveNumber < 11)
		return 10 * playerInventory[recursiveNumber].amount + powerLevelCounter(player, playerInventory, recursiveNumber - 1);
	else if (recursiveNumber > 10 && recursiveNumber < 17)
		return 100 * playerInventory[recursiveNumber].amount + powerLevelCounter(player, playerInventory, recursiveNumber - 1);
	else if (recursiveNumber > 16 && recursiveNumber < 21)
		return 10000 * playerInventory[recursiveNumber].amount + powerLevelCounter(player, playerInventory, recursiveNumber - 1);
	else if (recursiveNumber == 21 || recursiveNumber == 22)
		return 100000 * playerInventory[recursiveNumber].amount + powerLevelCounter(player, playerInventory, recursiveNumber - 1);
	else if (recursiveNumber == 23)
		return 10000000 * playerInventory[recursiveNumber].amount + powerLevelCounter(player, playerInventory, recursiveNumber - 1);
}

bool passwordCheck(int userIndex, User player[], char password[]) {
	int i;
	
	for (i = 0; i < strlen(player[userIndex].password); i++) {
		if (isupper(password[i]) && 65 + (password[i] - 65 + player[userIndex].encryption) % 26 != player[userIndex].password[i])
			return false;
		else if (islower(password[i]) && 97 + (password[i] - 97 + player[userIndex].encryption) % 26 != player[userIndex].password[i])
			return false;
		else if (isdigit(password[i]) && 48 + (password[i] - 48 + player[userIndex].encryption) % 10 != player[userIndex].password[i])
			return false;
		else if (!(isdigit(password[i]) || isalpha(password[i])) && password[i] != player[userIndex].password[i])
			return false;
	}
	
	if (strlen(password) != strlen(player[userIndex].password))
		return false;
	
	return true;
}
