#include <iostream>
#include <windows.h>
#include <conio.h>
#include <climits>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void move(int &px, int &py, int &ex, int &ey, int consolewidth, int consoleheight, int &score, int &level, int &health, int &ex1, int &ey1, bool &enemy1moveright, int &ex3, int &ey3, bool &enemy3moveright, bool &moveUpperRight, bool &enemy3movedown, int &ex2, int &ey2, bool &enemy2moveright, bool &moveUpperLeft, bool &enemy2movedown, int &enemy1Health, int &enemy2Health, int &enemy3Health, bool &level2reached, bool &level3reached, string headingcolor, int Playerbullets[2][100], int enemybullets[2][100], int &enemyBulletCount, int &playerBulletCount, bool &pillActive, int &pillX, int &pillY);
void printMaze(int consolewidth, int consoleheight, int &score, int &level, int &health);
void Menu(int consolewidth, int consoleheight);
void Gameover(int consolewidth, int consoleheight);
void printObstacles(int consolewidth, int consoleheight);
bool checkObstacles(int x, int y);
bool pauseMenu(int consolewidth, int consoleheight);
void saveRegion(int x, int y, int w, int h, CHAR_INFO *buffer);
void restoreRegion(int x, int y, int w, int h, CHAR_INFO *buffer);
void move_enemy(int &ex1, int &ey1, bool &enemy1moveright, int &ex3, int &ey3, int consolewidth, bool &enemy3moveright, bool &moveUpperRight, bool &enemy3movedown, int &ex2, int &ey2, bool &enemy2moveright, bool &moveUpperLeft, bool &enemy2movedown, int &enemy1Health, int &enemy2Health, int &enemy3Health, int &level, int consoleheight, bool &level2reached, bool &level3reached, string headingcolor, int py, int px, int score, int health);
void moveEnemy2(int &ex2, int &ey2, int consolewidth, bool &enemy2moveright, bool &moveUpperLeft, bool &enemy2movedown);
void moveEnemy3(int &ex3, int &ey3, int consolewidth, bool &enemy3moveright, bool &moveUpperRight, bool &enemy3movedown, int consoleheight);
void moveEnemy1(int &ex1, int &ey1, int consolewidth, bool &enemy1moveright);
void maximizeWindow();

// ---------- player functions -------------
void printplayer(int px, int py);
void printenemy(int ex, int ey);
void erase_player_enemy(int px, int py);
void erase_dead_enemy(int &ex1, int &ey1, int &ex3, int &ey3, int &ex2, int &ey2, int &enemy1Health, int &enemy2Health, int &enemy3Health);
void eraseEnemyFull(int &ex, int &ey);
void Start(int consolewidth, int consoleheight);

// --------- player firing ----------
void playerFire(int px, int py, int Playerbullets[2][100], int &playerBulletCount);
void movePlayerBullets(int Playerbullets[2][100], int &playerBulletCount,
                       int &score,
                       int &enemy1Health, int &enemy2Health, int &enemy3Health,
                       int level,
                       int ey1, int ex1,
                       int ey3, int ex3,
                       int ey2, int ex2, int px, int py, int health, bool enemy1moveright, bool enemy2moveright, bool enemy3moveright, bool moveUpperLeft, bool moveUpperRight, bool enemy2movedown, bool enemy3movedown, bool level2reached, bool level3reached);

// --------- enemy firing ----------
void enemyFire(int ex, int ey, int Enemybullets[2][100], int &enemyBulletCount);
void moveEnemyBullets(int Enemybullets[2][100], int &enemyBulletCount, int &health, int px, int py, int consoleheight, int score, int level, int ex1, int ey1, int ex2, int ey2, int ex3, int ey3, int enemy1Health, int enemy2Health, int enemy3Health, bool enemy1moveright, bool enemy2moveright, bool enemy3moveright, bool moveUpperLeft, bool moveUpperRight, bool enemy2movedown, bool enemy3movedown, bool level2reached, bool level3reached);
// ------------ default functions -----------------
void setcolor(string hexcolor);
void gotoxy(int x, int y);
int random(int lower, int upper);
void getconsolemeasures(int &width, int &height);
void hideCursor();
void showCursor();
void maze();
void win(int consolewidth, int consoleheight);
void moveHealthPill(int &health, int px, int py, int consoleheight,
                    bool &pillActive, int &pillX, int &pillY, DWORD &lastPillMove);
void spawnHealthPill(int consolewidth, int health,
                     bool &pillActive, int &pillX, int &pillY);
// file handling functions
bool loadGameData(int &px, int &py, int &score, int &level, int &health, int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3, int &enemy1Health, int &enemy2Health, int &enemy3Health, bool &enemy1moveright, bool &enemy2moveright, bool &enemy3moveright, bool &moveUpperLeft, bool &moveUpperRight, bool &enemy2movedown, bool &enemy3movedown, bool &level2reached, bool &level3reached);
int resumeGame(int consolewidth, int consoleheight);

bool saveGameDataWithHeaders(int px, int py, int score, int level, int health, int ex1, int ey1, int ex2, int ey2, int ex3, int ey3, int enemy1Health, int enemy2Health, int enemy3Health, bool enemy1moveright, bool enemy2moveright, bool enemy3moveright, bool moveUpperLeft, bool moveUpperRight, bool enemy2movedown, bool enemy3movedown, bool level2reached, bool level3reached);

//---------------------------------------------------------------MAIN-------------------------------------------------------------
main()
{

    // -------------------------- variables
    int consolewidth, consoleheight, Playerbullets[2][100], Enemybullets[2][100], playerBulletCount = 0, enemyBulletCount = 0, score = 0, level = 1, health = 100;
    getconsolemeasures(consolewidth, consoleheight);
    bool level2reached = false, level3reached = false;
    bool enemy1moveright = true, moveUpperRight = true, moveUpperLeft = true, enemy3moveright = false, enemy3movedown = false, enemy2moveright = true, enemy2movedown = true, playerInvincible = false;
    string headingcolor = "06";
    bool pillActive = false;
    int pillX, pillY;
    char pill = '+';

    // ---- initial settings ----
    int ex1 = consolewidth / 2, ey1 = 6, ex3 = 1, ey3 = 7, ex2 = consolewidth - 7, ey2 = 8, enemy1Health = 5, enemy2Health = 5, enemy3Health = 5;
    int px = 1, py = consoleheight - 3, ex = consolewidth - 6, ey = 6;
    system("cls");
    hideCursor();
    Start(consolewidth, consoleheight);
    showCursor();
    int choice = resumeGame(consolewidth, consoleheight);
    if (choice == 2)
    {
        loadGameData(px, py, score, level, health,
                     ex1, ey1, ex2, ey2, ex3, ey3,
                     enemy1Health, enemy2Health, enemy3Health,
                     enemy1moveright, enemy2moveright, enemy3moveright,
                     moveUpperLeft, moveUpperRight,
                     enemy2movedown, enemy3movedown,
                     level2reached, level3reached);
    }
    else
    {
    };
    hideCursor();
    setcolor(headingcolor);
    printMaze(consolewidth, consoleheight, score, level, health);
    printObstacles(consolewidth, consoleheight);
    move(px, py, ex, ey, consolewidth, consoleheight, score, level, health, ex1, ey1, enemy1moveright, ex3, ey3, enemy3moveright, moveUpperRight, enemy3movedown, ex2, ey2, enemy2moveright, moveUpperLeft, enemy2movedown, enemy1Health, enemy2Health, enemy3Health, level2reached, level3reached, headingcolor, Playerbullets, Enemybullets, enemyBulletCount, playerBulletCount, pillActive, pillX, pillY);
    showCursor();
}
// =============================== main movement ======================================

// ======================================(+++++++++++++++++++++ over all movement ++++++++++++++++++++++)============================================================
void move(int &px, int &py, int &ex, int &ey, int consolewidth, int consoleheight, int &score, int &level, int &health, int &ex1, int &ey1, bool &enemy1moveright, int &ex3, int &ey3, bool &enemy3moveright, bool &moveUpperRight, bool &enemy3movedown, int &ex2, int &ey2, bool &enemy2moveright, bool &moveUpperLeft, bool &enemy2movedown, int &enemy1Health, int &enemy2Health, int &enemy3Health, bool &level2reached, bool &level3reached, string headingcolor, int Playerbullets[2][100], int Enemybullets[2][100], int &enemyBulletCount, int &playerBulletCount, bool &pillActive, int &pillX, int &pillY)
{
    printplayer(px, py);
    DWORD lastEnemyMove = GetTickCount();
    DWORD enemyDelay = 150;
    DWORD lastShot = 0;
    DWORD lastPillMove = 0;
    while (true)
    {
        gotoxy(3, 1);
        setcolor("06");
        cout << "Health : " << health << "   ";
        gotoxy(consolewidth - 15, 1);
        cout << "Score : " << score << "   ";

        // ================= PLAYER-ENEMY COLLISION
        if (enemy1Health > 0)
        {
            if ((px >= ex1 - 4 && px <= ex1 + 4) && (py >= ey1 - 2 && py <= ey1 + 2))
            {
                health -= 40;
                if (health < 0)
                    health = 0;
                erase_player_enemy(px, py);
                py = consoleheight - 3;
            }
        }

        if (level >= 2 && enemy2Health > 0)
        {
            if ((px >= ex2 - 4 && px <= ex2 + 4) && (py >= ey2 - 2 && py <= ey2 + 2))
            {
                health -= 40;
                if (health < 0)
                    health = 0;
                erase_player_enemy(px, py);
                py = consoleheight - 3;
            }
        }

        if (level >= 3 && enemy3Health > 0)
        {
            if ((px >= ex3 - 4 && px <= ex3 + 4) && (py >= ey3 - 2 && py <= ey3 + 2))
            {
                health -= 40;
                if (health < 0)
                    health = 0;
                erase_player_enemy(px, py);
                py = consoleheight - 3;
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
            }
            bool wantExit = pauseMenu(consolewidth, consoleheight);
            if (wantExit)
            {
                setcolor("04");
                Gameover(consolewidth, consoleheight);
                setcolor("07");
                showCursor();
                saveGameDataWithHeaders(px, py, score, level, health,
                                        ex1, ey1, ex2, ey2, ex3, ey3,
                                        enemy1Health, enemy2Health, enemy3Health,
                                        enemy1moveright, enemy2moveright, enemy3moveright,
                                        moveUpperLeft, moveUpperRight,
                                        enemy2movedown, enemy3movedown,
                                        level2reached, level3reached);
                exit(0);
            }
        }
        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && px < consolewidth - 6 && !checkObstacles(px + 5, py - 2) && !checkObstacles(px + 5, py - 1) && !checkObstacles(px + 5, py))
        {
            erase_player_enemy(px, py);
            px++;
            printplayer(px, py);
        }
        else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && px > 1 && !checkObstacles(px - 1, py - 2) && !checkObstacles(px - 1, py - 1) && !checkObstacles(px - 1, py))
        {
            erase_player_enemy(px, py);
            px--;
            printplayer(px, py);
        }
        else if ((GetAsyncKeyState(VK_UP) & 0x8000) && py > 6 && !checkObstacles(px, py - 3) && !checkObstacles(px + 1, py - 3) && !checkObstacles(px + 2, py - 3) && !checkObstacles(px + 3, py - 3) && !checkObstacles(px + 4, py - 3))
        {
            erase_player_enemy(px, py);
            py--;
            printplayer(px, py);
        }
        else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && py < consoleheight - 2 && !checkObstacles(px, py + 1) && !checkObstacles(px + 1, py + 1) && !checkObstacles(px + 2, py + 1) && !checkObstacles(px + 3, py + 1) && !checkObstacles(px + 4, py + 1))
        {
            erase_player_enemy(px, py);
            py++;
            printplayer(px, py);
        }
        if (GetTickCount() - lastEnemyMove >= enemyDelay)
        {
            move_enemy(ex1, ey1, enemy1moveright,
                       ex3, ey3, consolewidth,
                       enemy3moveright, moveUpperRight, enemy3movedown,
                       ex2, ey2, enemy2moveright,
                       moveUpperLeft, enemy2movedown,
                       enemy1Health, enemy2Health, enemy3Health,
                       level, consoleheight,
                       level2reached, level3reached,
                       headingcolor,
                       py, px, score, health);
            lastEnemyMove = GetTickCount();
        }
        // playerfire
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            if (GetTickCount() - lastShot > 120)
            {
                playerFire(px, py, Playerbullets, playerBulletCount);
                lastShot = GetTickCount();
            }
        }
        movePlayerBullets(Playerbullets, playerBulletCount,
                          score,
                          enemy1Health, enemy2Health, enemy3Health,
                          level,
                          ey1, ex1,
                          ey3, ex3,
                          ey2, ex2,
                          px, py, health,
                          enemy1moveright, enemy2moveright, enemy3moveright,
                          moveUpperLeft, moveUpperRight,
                          enemy2movedown, enemy3movedown,
                          level2reached, level3reached);

        if (enemy1Health > 0)
            enemyFire(ex1, ey1, Enemybullets, enemyBulletCount);
        if (level >= 2 && enemy2Health > 0)
            enemyFire(ex1, ey1, Enemybullets, enemyBulletCount);
        if (level >= 3 && enemy3Health > 0)
            enemyFire(ex3, ey3, Enemybullets, enemyBulletCount);

        moveEnemyBullets(Enemybullets, enemyBulletCount,
                         health, px, py, consoleheight,
                         score, level,
                         ex1, ey1, ex2, ey2, ex3, ey3,
                         enemy1Health, enemy2Health, enemy3Health,
                         enemy1moveright, enemy2moveright, enemy3moveright,
                         moveUpperLeft, moveUpperRight,
                         enemy2movedown, enemy3movedown,
                         level2reached, level3reached);
        if (health <= 0)
        {
            Gameover(consolewidth, consoleheight);
            showCursor();
            exit(0);
        }
        spawnHealthPill(consolewidth, health,
                        pillActive, pillX, pillY);

        moveHealthPill(health, px, py, consoleheight,
                       pillActive, pillX, pillY,
                       lastPillMove);

        Sleep(20);
    }
}
bool checkObstacles(int x, int y)
{
    CHAR ch = ' ';
    DWORD read;
    COORD pos = {(SHORT)x, (SHORT)y};
    ReadConsoleOutputCharacterA(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &ch,
        1,
        pos,
        &read);
    return (ch == '#');
}

// =============================== printing headers ======================================================
// -------------- maze print ----------------
void printMaze(int consolewidth, int consoleheight, int &score, int &level, int &health)
{
    system("cls");
    int primarywidth = 0;
    int primaryheight = 0;

    while (primaryheight < consoleheight)
    {
        if (primaryheight == consoleheight)
        {
            break;
        }
        if (primaryheight == 0 || primaryheight == 3)
        {
            while (primarywidth < consolewidth)
            {
                gotoxy(primarywidth, primaryheight);
                cout << "_";
                primarywidth++;
            }
            primarywidth = 0;
            primaryheight++;
        }
        else if (primaryheight > 0 && primaryheight <= consoleheight - 1 && primaryheight != 3)
        {
            while (primaryheight > 0 && primaryheight <= consoleheight - 1)
            {

                gotoxy(primarywidth, primaryheight);
                if (primarywidth == 0)
                {
                    cout << "|";
                    primarywidth++;
                }
                else if (primarywidth == consolewidth - 1)
                {
                    cout << "|";
                    primaryheight++;
                    primarywidth = 0;
                }
                else
                {
                    if (primaryheight == 3 || primaryheight == consoleheight - 1)
                    {
                        cout << "_";
                    }
                    else
                    {
                        cout << " ";
                    }
                    primarywidth++;
                }
            }
        }
        else if (primaryheight == consoleheight)
        {
            break;
        }
    }
    gotoxy(consolewidth / 2 - 7, 2);
    cout << "Biriyani Hunter";
    gotoxy(consolewidth - 15, 1);
    cout << "Score : " << score;
    gotoxy(consolewidth - 15, 2);
    cout << "Level : " << level;
    gotoxy(3, 1);
    cout << "Health : " << health;
}
// ------------- print obstacles ----------
void printObstacles(int consolewidth, int consoleheight)
{
    setcolor("04");
    gotoxy(consolewidth / 6 - 10, consoleheight / 2 - 8);
    cout << "#############";
    gotoxy(consolewidth / 6 - 10, consoleheight / 2 - 7);
    cout << "#############";
    gotoxy(consolewidth / 6 - 10, consoleheight / 2 - 6);
    cout << "#############";
    gotoxy(consolewidth / 6 - 10, consoleheight / 2 - 5);
    cout << "#############";
    gotoxy(consolewidth / 6 - 10, consoleheight / 2 - 4);
    cout << "#############";
    gotoxy(consolewidth / 6 - 10, consoleheight / 2 - 3);
    cout << "#############";
    for (int i = 0; i < 30; i++)
    {
        gotoxy(consolewidth / 2 - 4, consoleheight / 2 - 8);
        cout << "####";
        consoleheight++;
    }
    consoleheight -= 30;
    for (int i = 0; i < 15; i++)
    {
        gotoxy(5 * consolewidth / 6 - 10, consoleheight / 2 - 8);
        cout << "#############";
        consoleheight++;
    }
    consoleheight -= 15;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(consolewidth / 2 - 25, consoleheight / 2 + 3);
        cout << "#######";
        consoleheight++;
    }
    consoleheight -= 10;
    for (int i = 0; i < 10; i++)
    {
        gotoxy(consolewidth / 2 + 10, consoleheight / 2 + 5);
        cout << "#########";
        consoleheight++;
    }
    consoleheight -= 10;
}

// ------------- game over printing -------------------------
void Gameover(int consolewidth, int consoleheight)
{
    system("cls");
    setcolor("04");

    int artWidth = 110;
    int artHeight = 6;

    int startX = (consolewidth - artWidth) / 2;
    int startY = (consoleheight - artHeight) / 2;
    SetConsoleOutputCP(CP_UTF8);

    gotoxy(startX, startY);
    cout << "  █████████    █████████   ██████   ██████ ██████████       ███████    █████   █████ ██████████ ███████████    ";
    gotoxy(startX, startY + 1);
    cout << "  ███░░░░░███  ███░░░░░███ ░░██████ ██████ ░░███░░░░░█     ███░░░░░███ ░░███   ░░███ ░░███░░░░░█░░███░░░░░███ ";
    gotoxy(startX, startY + 2);
    cout << " ███     ░░░  ░███    ░███  ░███░█████░███  ░███  █ ░     ███     ░░███ ░███    ░███  ░███  █ ░  ░███    ░███ ";
    gotoxy(startX, startY + 3);
    cout << "░███          ░███████████  ░███░░███ ░███  ░██████      ░███      ░███ ░███    ░███  ░██████    ░██████████  ";
    gotoxy(startX, startY + 4);
    cout << "░███    █████ ░███░░░░░███  ░███ ░░░  ░███  ░███░░█      ░███      ░███ ░░███   ███   ░███░░█    ░███░░░░░███ ";
    gotoxy(startX, startY + 5);
    cout << "░░███  ░░███  ░███    ░███  ░███      ░███  ░███ ░   █   ░░███     ███   ░░░█████░    ░███ ░   █ ░███    ░███ ";
    gotoxy(startX, startY + 6);
    cout << " ░░█████████  █████   █████ █████     █████ ██████████    ░░░███████░      ░░███      ██████████ █████   █████";
    gotoxy(startX, startY + 7);
    cout << "  ░░░░░░░░░  ░░░░░   ░░░░░ ░░░░░     ░░░░░ ░░░░░░░░░░       ░░░░░░░         ░░░      ░░░░░░░░░░ ░░░░░   ░░░░░  ";
    setcolor("07");
    Sleep(2000);
    system("cls");
}

// ============================================ player handling ========================================================
// ------ print player ------------
void printplayer(int px, int py)
{
    setcolor("02");
    gotoxy(px, py - 2);
    cout << " O";
    gotoxy(px, py - 1);
    cout << "/|\\==";
    gotoxy(px, py);
    cout << "/ \\";
}

// ---------- erase player/enemy -----------
void erase_player_enemy(int px, int py)
{

    gotoxy(px, py);
    cout << "   ";
    gotoxy(px, py - 1);
    cout << "     ";
    gotoxy(px, py - 2);
    cout << "   ";
}

// ======================================(++++++++++++++++++++++++++++ Enemy handling ++++++++++++++++++++++++++++++++++++)=======================================================
// ===================== Enemy 1 handlilng =======================================
// -------------- printing enemy 1 -------------------
// ------ enemy player ------------
void printenemy(int ex, int ey)
{
    setcolor("01");
    gotoxy(ex, ey - 2);
    cout << " +";
    gotoxy(ex, ey - 1);
    cout << "/|\\==";
    gotoxy(ex, ey);
    cout << "/ \\";
}

void moveEnemy1(int &ex1, int &ey1, int consolewidth, bool &enemy1moveright)
{
    if (enemy1moveright)
    {
        erase_player_enemy(ex1, ey1);
        ex1++;
        printenemy(ex1, ey1);
        if (ex1 == consolewidth - 8)
        {
            enemy1moveright = false;
        }
    }
    else
    {
        erase_player_enemy(ex1, ey1);
        ex1--;
        printenemy(ex1, ey1);
        if (ex1 == 1)
        {
            enemy1moveright = true;
        }
    }
}

// -------------------- moving enemy 2 ----------------------
void moveEnemy2(int &ex2, int &ey2, int consolewidth, bool &enemy2moveright, bool &moveUpperLeft, bool &enemy2movedown)
{
    if (moveUpperLeft)
    {
        erase_player_enemy(ex2, ey2);
        ex2--;
        printenemy(ex2, ey2);
        if (ex2 == 5 * consolewidth / 6 - 15)
        {
            moveUpperLeft = false;
            enemy2movedown = true;
        }
        return;
    }
    else if (enemy2movedown)
    {
        erase_player_enemy(ex2, ey2);
        ey2++;
        printenemy(ex2, ey2);
        if (ey2 == 14)
        {
            enemy2movedown = false;
            enemy2moveright = false;
        }
        return;
    }
    else if (enemy2moveright)
    {
        erase_player_enemy(ex2, ey2);
        ex2++;
        printenemy(ex2, ey2);
        if (checkObstacles(ex2 + 5, ey2))
        {
            enemy2moveright = false;
        }
    }
    else
    {
        erase_player_enemy(ex2, ey2);
        ex2--;
        printenemy(ex2, ey2);
        if (checkObstacles(ex2 - 1, ey2))
        {
            enemy2moveright = true;
        }
    }
}

// ----------------- moving enemy 3 -------------------
void moveEnemy3(int &ex3, int &ey3, int consolewidth, bool &enemy3moveright, bool &moveUpperRight, bool &enemy3movedown, int consoleheight)
{
    if (moveUpperRight)
    {
        erase_player_enemy(ex3, ey3);
        ex3++;
        printenemy(ex3, ey3);
        if (ex3 == consolewidth / 6 + 3)
        {
            moveUpperRight = false;
            enemy3movedown = true;
        }
        return;
    }
    else if (enemy3movedown)
    {
        erase_player_enemy(ex3, ey3);
        ey3++;
        printenemy(ex3, ey3);
        if (ey3 == consoleheight / 2 - 8)
        {
            enemy3movedown = false;
            enemy3moveright = true;
        }
        return;
    }
    else if (enemy3moveright)
    {
        erase_player_enemy(ex3, ey3);
        ex3++;
        printenemy(ex3, ey3);
        if (checkObstacles(ex3 + 5, ey3))
        {
            enemy3moveright = false;
        }
    }

    else
    {
        erase_player_enemy(ex3, ey3);
        ex3--;
        printenemy(ex3, ey3);
        if (checkObstacles(ex3 - 1, ey3))
        {
            enemy3moveright = true;
        }
    }
}

// --------------- moving all enemies in one function -----------------------
void move_enemy(
    int &ex1, int &ey1, bool &enemy1moveright,
    int &ex3, int &ey3, int consolewidth,
    bool &enemy3moveright, bool &moveUpperRight, bool &enemy3movedown,
    int &ex2, int &ey2, bool &enemy2moveright, bool &moveUpperLeft, bool &enemy2movedown,
    int &enemy1Health, int &enemy2Health, int &enemy3Health,
    int &level, int consoleheight,
    bool &level2reached, bool &level3reached,
    string headingcolor, int py, int px, int score, int health)
{
    // ================= LEVEL 1 → LEVEL 2 =================
    if (level == 1 && enemy1Health <= 0)
    {
        eraseEnemyFull(ex1, ey1);
        level = 2;
        level2reached = true;
      
    }

    // ================= LEVEL 2 → LEVEL 3 =================
    if (level == 2 && enemy1Health <= 0 && enemy2Health <= 0)
    {
        eraseEnemyFull(ex1, ey1);
        eraseEnemyFull(ex2, ey2);
        level = 3;
        level3reached = true;
    }
    if (enemy1Health <= 0)
    {
        eraseEnemyFull(ex1, ey1);
    }
    if (enemy2Health <= 0)
    {
        eraseEnemyFull(ex2, ey2);
    }

    if (enemy3Health <= 0)
    {
        eraseEnemyFull(ex3, ey3);
    }
    // ================= LEVEL 2 SPAWN =================
    if (level == 2 && level2reached)
    {
        enemy1Health = 5;
        enemy2Health = 5;

        ex1 = consolewidth / 2;
        ey1 = 6;

        ex2 = consolewidth - 7;
        ey2 = 8;

        enemy1moveright = true;

        moveUpperLeft = true;
        enemy2movedown = false;
        enemy2moveright = false;

        level2reached = false;
          saveGameDataWithHeaders(px, py, score, level, health,
                                ex1, ey1, ex2, ey2, ex3, ey3,
                                enemy1Health, enemy2Health, enemy3Health,
                                enemy1moveright, enemy2moveright, enemy3moveright,
                                moveUpperLeft, moveUpperRight,
                                enemy2movedown, enemy3movedown,
                                level2reached, level3reached);
    }

    // ================= LEVEL 3 SPAWN =================
    if (level == 3 && level3reached)
    {
        enemy1Health = 5;
        enemy2Health = 5;
        enemy3Health = 5;

        ex1 = consolewidth / 2;
        ey1 = 6;

        ex2 = consolewidth - 7;
        ey2 = 8;

        ex3 = 1;
        ey3 = 7;

        enemy1moveright = true;

        moveUpperLeft = true;
        enemy2movedown = false;
        enemy2moveright = false;

        moveUpperRight = true;
        enemy3movedown = false;
        enemy3moveright = false;

        level3reached = false;
          saveGameDataWithHeaders(px, py, score, level, health,
                                ex1, ey1, ex2, ey2, ex3, ey3,
                                enemy1Health, enemy2Health, enemy3Health,
                                enemy1moveright, enemy2moveright, enemy3moveright,
                                moveUpperLeft, moveUpperRight,
                                enemy2movedown, enemy3movedown,
                                level2reached, level3reached);
    }

    // ================= WIN =================
    if (level == 3 &&
        enemy1Health <= 0 &&
        enemy2Health <= 0 &&
        enemy3Health <= 0)
    {
        system("cls");
        win(consolewidth, consoleheight);
        Sleep(3000);
        exit(0);
    }

    // ================= MOVE BY LEVEL =================
    if (enemy1Health > 0)
        moveEnemy1(ex1, ey1, consolewidth, enemy1moveright);

    if (level >= 2 && enemy2Health > 0)
        moveEnemy2(ex2, ey2, consolewidth,
                   enemy2moveright, moveUpperLeft, enemy2movedown);

    if (level >= 3 && enemy3Health > 0)
        moveEnemy3(ex3, ey3, consolewidth,
                   enemy3moveright, moveUpperRight, enemy3movedown, consoleheight);

    gotoxy(consolewidth - 15, 2);
    setcolor(headingcolor);
    cout << "Level : " << level;
}
void eraseEnemyFull(int &ex, int &ey)
{
    gotoxy(ex, ey);
    cout << "   ";
    gotoxy(ex, ey - 1);
    cout << "     ";
    gotoxy(ex, ey - 2);
    cout << "   ";
}

// ============================================= pause game =====================================================================================
bool pauseMenu(int consolewidth, int consoleheight)
{
    CHAR_INFO savedBuffer[22 * 5];
    int bx = consolewidth / 2 - 10;
    int by = consoleheight / 2 - 2;
    int bw = 22;
    int bh = 5;
    saveRegion(bx, by, bw, bh, savedBuffer);

    setcolor("0E");
    gotoxy(bx, by);
    cout << "====================";
    gotoxy(bx, by + 1);
    cout << "      GAME PAUSED    ";
    gotoxy(bx, by + 2);
    cout << "  ENTER = Continue   ";
    gotoxy(bx, by + 3);
    cout << "  ESC   = Exit Game  ";
    gotoxy(bx, by + 4);
    cout << "====================";
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            while (GetAsyncKeyState(VK_RETURN) & 0x8000)
            {
            }
            restoreRegion(bx, by, bw, bh, savedBuffer);
            return false;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
            }
            for (int i = 0; i < 5; i++)
            {
                gotoxy(bx, by + i);
                cout << "                    ";
            }
            return true;
        }
        Sleep(50);
    }
}
// ------------- saving region of pause menu to print after continue ----------------
void saveRegion(int x, int y, int w, int h, CHAR_INFO *buffer)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = {(SHORT)w, (SHORT)h};
    COORD bufferCoord = {0, 0};
    SMALL_RECT readRegion = {
        (SHORT)x,
        (SHORT)y,
        (SHORT)(x + w - 1),
        (SHORT)(y + h - 1)};

    ReadConsoleOutput(
        hConsole,
        buffer,
        bufferSize,
        bufferCoord,
        &readRegion);
}

// ---------------- again printing saved region after continuing game ----------------
void restoreRegion(int x, int y, int w, int h, CHAR_INFO *buffer)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = {(SHORT)w, (SHORT)h};
    COORD bufferCoord = {0, 0};
    SMALL_RECT writeRegion = {
        (SHORT)x,
        (SHORT)y,
        (SHORT)(x + w - 1),
        (SHORT)(y + h - 1)};

    WriteConsoleOutput(
        hConsole,
        buffer,
        bufferSize,
        bufferCoord,
        &writeRegion);
}

// ============================================== Default functions =============================================================================
// ------------ setting color -----------------
void setcolor(string hexcolor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = stoi(hexcolor, nullptr, 16);
    SetConsoleTextAttribute(hConsole, color);
}
// ------------------- gotoxy function -------------
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// --------------------- getting random number -------------
int random(int lower, int upper)
{
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<> dist(lower, upper);
    int randomNum = dist(gen);
    return randomNum;
}
// ----------------- getting console measures ------------------------
void getconsolemeasures(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// ------------------------------- cursor handling -------------------------------------------
void hideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void showCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void setCursorSize(int size)
{
    if (size < 1)
        size = 1;
    if (size > 100)
        size = 100;
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(out, &cursorInfo);
}
// ========================================= (++++++++++++++++++++++++++ Player firing ++++++++++++++++++++++++++) =============================================================
void playerFire(int px, int py, int Playerbullets[2][100], int &playerBulletCount)
{
    if (playerBulletCount >= 100)
        return;

    Playerbullets[0][playerBulletCount] = px + 2;
    Playerbullets[1][playerBulletCount] = py - 3;
    playerBulletCount++;
}

// ---------------- moving player bullets ----------------
void movePlayerBullets(int Playerbullets[2][100], int &playerBulletCount,
                       int &score,
                       int &enemy1Health, int &enemy2Health, int &enemy3Health,
                       int level,
                       int ey1, int ex1,
                       int ey3, int ex3,
                       int ey2, int ex2, int px, int py, int health, bool enemy1moveright, bool enemy2moveright, bool enemy3moveright, bool moveUpperLeft, bool moveUpperRight, bool enemy2movedown, bool enemy3movedown, bool level2reached, bool level3reached)
{
    for (int i = 0; i < playerBulletCount; i++)
    {
        gotoxy(Playerbullets[0][i], Playerbullets[1][i]);
        cout << " ";

        Playerbullets[1][i]--;

        // obstacle
        if (Playerbullets[1][i] < 4 ||
            checkObstacles(Playerbullets[0][i], Playerbullets[1][i]))
        {
            Playerbullets[0][i] = Playerbullets[0][playerBulletCount - 1];
            Playerbullets[1][i] = Playerbullets[1][playerBulletCount - 1];
            playerBulletCount--;
            i--;
            continue;
        }

        //  enemy 1
        if (level >= 1 &&
            Playerbullets[1][i] >= ey1 - 2 && Playerbullets[1][i] <= ey1 &&
            Playerbullets[0][i] >= ex1 && Playerbullets[0][i] <= ex1 + 4 &&
            enemy1Health > 0)
        {
            enemy1Health--;
            score += 10;
            cout << "\a";
            saveGameDataWithHeaders(px, py, score, level, health,
                                    ex1, ey1, ex2, ey2, ex3, ey3,
                                    enemy1Health, enemy2Health, enemy3Health,
                                    enemy1moveright, enemy2moveright, enemy3moveright,
                                    moveUpperLeft, moveUpperRight,
                                    enemy2movedown, enemy3movedown,
                                    level2reached, level3reached);

            Playerbullets[0][i] = Playerbullets[0][playerBulletCount - 1];
            Playerbullets[1][i] = Playerbullets[1][playerBulletCount - 1];
            playerBulletCount--;
            i--;
            continue;
        }

        // ---- enemy 2 ----
        if (level >= 2 &&
            Playerbullets[1][i] >= ey2 - 2 && Playerbullets[1][i] <= ey2 &&
            Playerbullets[0][i] >= ex2 && Playerbullets[0][i] <= ex2 + 4 &&
            enemy2Health > 0)
        {
            enemy2Health--;
            score += 10;
            saveGameDataWithHeaders(px, py, score, level, health,
                                    ex1, ey1, ex2, ey2, ex3, ey3,
                                    enemy1Health, enemy2Health, enemy3Health,
                                    enemy1moveright, enemy2moveright, enemy3moveright,
                                    moveUpperLeft, moveUpperRight,
                                    enemy2movedown, enemy3movedown,
                                    level2reached, level3reached);
            cout << "\a";

            Playerbullets[0][i] = Playerbullets[0][playerBulletCount - 1];
            Playerbullets[1][i] = Playerbullets[1][playerBulletCount - 1];
            playerBulletCount--;
            i--;
            continue;
        }

        // ---- enemy 3 ----
        if (level >= 3 &&
            Playerbullets[1][i] >= ey3 - 2 && Playerbullets[1][i] <= ey3 &&
            Playerbullets[0][i] >= ex3 && Playerbullets[0][i] <= ex3 + 4 &&
            enemy3Health > 0)
        {
            enemy3Health--;
            score += 10;
            cout << "\a";
            saveGameDataWithHeaders(px, py, score, level, health,
                                    ex1, ey1, ex2, ey2, ex3, ey3,
                                    enemy1Health, enemy2Health, enemy3Health,
                                    enemy1moveright, enemy2moveright, enemy3moveright,
                                    moveUpperLeft, moveUpperRight,
                                    enemy2movedown, enemy3movedown,
                                    level2reached, level3reached);

            Playerbullets[0][i] = Playerbullets[0][playerBulletCount - 1];
            Playerbullets[1][i] = Playerbullets[1][playerBulletCount - 1];
            playerBulletCount--;
            i--;
            continue;
        }

        gotoxy(Playerbullets[0][i], Playerbullets[1][i]);
        cout << "|";
    }
}

// ========================================= (++++++++++++++++++++++++++ Enemy firing ++++++++++++++++++++++++++) =============================================================
void enemyFire(int ex, int ey, int Enemybullets[2][100], int &enemyBulletCount)
{
    if (random(1, 20) != 1)
        return;
    if (enemyBulletCount >= 100)
        return;

    Enemybullets[0][enemyBulletCount] = ex + 2;
    Enemybullets[1][enemyBulletCount] = ey + 1;
    enemyBulletCount++;
}
// ---------------- moving enemy bullets ----------------
void moveEnemyBullets(int Enemybullets[2][100], int &enemyBulletCount,
                      int &health, int px, int py, int consoleheight, int score, int level, int ex1, int ey1, int ex2, int ey2, int ex3, int ey3, int enemy1Health, int enemy2Health, int enemy3Health, bool enemy1moveright, bool enemy2moveright, bool enemy3moveright, bool moveUpperLeft, bool moveUpperRight, bool enemy2movedown, bool enemy3movedown, bool level2reached, bool level3reached)
{
    static DWORD lastHitTime = 0;

    for (int i = 0; i < enemyBulletCount; i++)
    {
        gotoxy(Enemybullets[0][i], Enemybullets[1][i]);
        cout << " ";

        Enemybullets[1][i]++;

        // ---- obstacle / bottom ----
        if (Enemybullets[1][i] > consoleheight - 2 ||
            checkObstacles(Enemybullets[0][i], Enemybullets[1][i]))
        {
            Enemybullets[0][i] = Enemybullets[0][enemyBulletCount - 1];
            Enemybullets[1][i] = Enemybullets[1][enemyBulletCount - 1];
            enemyBulletCount--;
            i--;
            continue;
        }

        // ---- hit player ----
        if (Enemybullets[1][i] >= py - 2 && Enemybullets[1][i] <= py &&
            Enemybullets[0][i] >= px && Enemybullets[0][i] <= px + 4)
        {
            if (GetTickCount() - lastHitTime > 300)
            {
                health -= 20;
                lastHitTime = GetTickCount();
                saveGameDataWithHeaders(px, py, score, level, health,
                                        ex1, ey1, ex2, ey2, ex3, ey3,
                                        enemy1Health, enemy2Health, enemy3Health,
                                        enemy1moveright, enemy2moveright, enemy3moveright,
                                        moveUpperLeft, moveUpperRight,
                                        enemy2movedown, enemy3movedown,
                                        level2reached, level3reached);
            }

            Enemybullets[0][i] = Enemybullets[0][enemyBulletCount - 1];
            Enemybullets[1][i] = Enemybullets[1][enemyBulletCount - 1];
            enemyBulletCount--;
            i--;
            continue;
        }

        gotoxy(Enemybullets[0][i], Enemybullets[1][i]);
        cout << "!";
    }
}
void win(int consolewidth, int consoleheight)
{
    system("cls");
    setcolor("0A");
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 6);
    cout << "█████ █████    ███████    █████  █████    █████   ███   █████ █████ ██████   █████ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 5);
    cout << "░░███ ░░███   ███░░░░░███ ░░███  ░░███    ░░███   ░███  ░░███ ░░███ ░░██████ ░░███ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 4);
    cout << " ░░███ ███   ███     ░░███ ░███   ░███     ░███   ░███   ░███  ░███  ░███░███ ░███ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 3);
    cout << "  ░░█████   ░███      ░███ ░███   ░███     ░███   ░███   ░███  ░███  ░███░░███░███ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 2);
    cout << "   ░░███    ░███      ░███ ░███   ░███     ░░███  █████  ███   ░███  ░███ ░░██████ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 1);
    cout << "    ░███    ░░███     ███  ░███   ░███      ░░░█████░█████░    ░███  ░███  ░░█████ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2);
    cout << "    █████    ░░░███████░   ░░████████         ░░███ ░░███      █████ █████  ░░█████";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 1);
    cout << "   ░░░░░       ░░░░░░░      ░░░░░░░░           ░░░   ░░░      ░░░░░ ░░░░░    ░░░░░ ";
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 3);
    cout << "                    ENJOY YOUR BIRIYANI!                     " << endl;
    setcolor("07");
}
void Start(int consolewidth, int consoleheight)
{
    setcolor("0A");
    SetConsoleOutputCP(CP_UTF8);
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 6);
    cout << "███████████  █████ ███████████   █████ █████   █████████   ██████   █████ █████" << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 5);
    cout << "░░███░░░░░███░░███ ░░███░░░░░███ ░░███ ░░███   ███░░░░░███ ░░██████ ░░███ ░░███ " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 4);
    cout << " ░███    ░███ ░███  ░███    ░███  ░░███ ███   ░███    ░███  ░███░███ ░███  ░███ " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 3);
    cout << " ░██████████  ░███  ░██████████    ░░█████    ░███████████  ░███░░███░███  ░███ " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 2);
    cout << " ░███░░░░░███ ░███  ░███░░░░░███    ░░███     ░███░░░░░███  ░███ ░░██████  ░███ " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 - 1);
    cout << " ░███    ░███ ░███  ░███    ░███     ░███     ░███    ░███  ░███  ░░█████  ░███ " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2);
    cout << " ███████████  █████ █████   █████    █████    █████   █████ █████  ░░█████ █████" << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 1);
    cout << "░░░░░░░░░░░  ░░░░░ ░░░░░   ░░░░░    ░░░░░    ░░░░░   ░░░░░ ░░░░░    ░░░░░ ░░░░░ " << endl
         << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 3);
    cout << " █████   █████ █████  █████ ██████   █████ ███████████ ██████████ ███████████   " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 4);
    cout << "░░███   ░░███ ░░███  ░░███ ░░██████ ░░███ ░█░░░███░░░█░░███░░░░░█░░███░░░░░███  " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 5);
    cout << " ░███    ░███  ░███   ░███  ░███░███ ░███ ░   ░███  ░  ░███  █ ░  ░███    ░███  " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 6);
    cout << " ░███████████  ░███   ░███  ░███░░███░███     ░███     ░██████    ░██████████   " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 7);
    cout << " ░███░░░░░███  ░███   ░███  ░███ ░░██████     ░███     ░███░░█    ░███░░░░░███  " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 8);
    cout << " ░███    ░███  ░███   ░███  ░███  ░░█████     ░███     ░███ ░   █ ░███    ░███  " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 9);
    cout << " █████   █████ ░░████████   █████  ░░█████    █████    ██████████ █████   █████ " << endl;
    gotoxy(consolewidth / 2 - 40, consoleheight / 2 + 10);
    cout << "░░░░░   ░░░░░   ░░░░░░░░   ░░░░░    ░░░░░    ░░░░░    ░░░░░░░░░░ ░░░░░   ░░░░░  " << endl;
    gotoxy(consolewidth / 2 - 25, consoleheight / 2 + 12);

    cout << "       KILL THE ENEMIES AND SAVE THE BIRIYANI            " << endl;

    Sleep(5000);
    system("cls");

    setcolor("0B");
    gotoxy(consolewidth / 2 - 30, 11);
    cout << "================ GAME INSTRUCTIONS ================";
    gotoxy(consolewidth / 2 - 30, 12);
    cout << "-> Move Left  : LEFT ARROW KEY";
    gotoxy(consolewidth / 2 - 30, 13);
    cout << "-> Move Right : RIGHT ARROW KEY";
    gotoxy(consolewidth / 2 - 30, 14);
    cout << "-> Move Up    : UP ARROW KEY";
    gotoxy(consolewidth / 2 - 30, 15);
    cout << "-> Move Down  : DOWN ARROW KEY";
    gotoxy(consolewidth / 2 - 30, 16);
    cout << "-> Fire Gun   : SPACE BAR";
    gotoxy(consolewidth / 2 - 30, 17);
    cout << "-> Pause Game : ESC KEY";
    gotoxy(consolewidth / 2 - 30, 18);
    cout << "-> Total Levels : 3";
    gotoxy(consolewidth / 2 - 30, 19);

    cout << "-> Each enemy dies after 5 hits";
    gotoxy(consolewidth / 2 - 30, 20);
    cout << "-> Enemy bullet reduces 20 health";
    gotoxy(consolewidth / 2 - 30, 21);

    cout << "->WIN CONDITION: Kill all enemies in Level 3";
    gotoxy(consolewidth / 2 - 30, 22);
    cout << "===================================================";
    gotoxy(consolewidth / 2 - 20, consoleheight - 4);
    Sleep(5000);
    cout << " Press any key to start the game...";
    getch();
    system("cls");
}
void spawnHealthPill(int consolewidth, int health,
                     bool &pillActive, int &pillX, int &pillY)
{
    if (pillActive)
        return;

    if (health == 10 || health == 40)
    {
        pillX = random(1, consolewidth - 2);
        pillY = 4;
        pillActive = true;
    }
}

void moveHealthPill(int &health, int px, int py, int consoleheight,
                    bool &pillActive, int &pillX, int &pillY,
                    DWORD &lastPillMove)
{
    if (!pillActive)
        return;

    // FALL SPEED CONTROL (slow)
    if (GetTickCount() - lastPillMove < 200)
        return;

    lastPillMove = GetTickCount();

    // erase old position
    gotoxy(pillX, pillY);
    cout << " ";

    pillY++;

    // ---- obstacle check ----
    if (checkObstacles(pillX, pillY))
    {
        pillActive = false;
        return;
    }

    // ---- reached bottom ----
    if (pillY >= consoleheight - 2)
    {
        pillActive = false;
        return;
    }

    // ---- collision with player ----
    if (pillY >= py - 2 && pillY <= py &&
        pillX >= px && pillX <= px + 4)
    {
        health += 10;
        if (health > 100)
            health = 100;

        pillActive = false;
        return;
    }

    setcolor("02");
    gotoxy(pillX, pillY);
    cout << "+";
}

// ------------------------------------file handling ---------------------------------------
// saving
bool saveGameDataWithHeaders(int px, int py, int score, int level, int health,
                             int ex1, int ey1, int ex2, int ey2, int ex3, int ey3,
                             int enemy1Health, int enemy2Health, int enemy3Health,
                             bool enemy1moveright, bool enemy2moveright, bool enemy3moveright,
                             bool moveUpperLeft, bool moveUpperRight,
                             bool enemy2movedown, bool enemy3movedown,
                             bool level2reached, bool level3reached)
{
    fstream saveFile;
    saveFile.open("biriyani_hunter_save.txt" , ios :: out);
    if (!saveFile.is_open())
    {
        return false;
    }

    saveFile << "px,py,score,level,health,"
             << "ex1,ey1,enemy1Health,enemy1moveright,"
             << "ex2,ey2,enemy2Health,enemy2moveright,moveUpperLeft,enemy2movedown,"
             << "ex3,ey3,enemy3Health,enemy3moveright,moveUpperRight,enemy3movedown,"
             << "level2reached,level3reached" << endl;

    saveFile << px << "," << py << "," << score << "," << level << "," << health << ","
             << ex1 << "," << ey1 << "," << enemy1Health << "," << enemy1moveright << ","
             << ex2 << "," << ey2 << "," << enemy2Health << "," << enemy2moveright << ","
             << moveUpperLeft << "," << enemy2movedown << ","
             << ex3 << "," << ey3 << "," << enemy3Health << "," << enemy3moveright << ","
             << moveUpperRight << "," << enemy3movedown << ","
             << level2reached << "," << level3reached;

    saveFile.close();
    return true;
}
// ----------------------- loading game data
bool loadGameData(int &px, int &py, int &score, int &level, int &health,
                  int &ex1, int &ey1, int &ex2, int &ey2, int &ex3, int &ey3,
                  int &enemy1Health, int &enemy2Health, int &enemy3Health,
                  bool &enemy1moveright, bool &enemy2moveright, bool &enemy3moveright,
                  bool &moveUpperLeft, bool &moveUpperRight,
                  bool &enemy2movedown, bool &enemy3movedown,
                  bool &level2reached, bool &level3reached)
{
    fstream file;
    file.open("biriyani_hunter_save.txt", ios::in);

    if (!file.is_open())
    {
        return false;
    }

    string headerLine, dataLine;
    getline(file, headerLine);

    if (getline(file, dataLine))
    {
        stringstream ss(dataLine);
        string token;

        getline(ss, token, ',');
        px = stoi(token);
        getline(ss, token, ',');
        py = stoi(token);
        getline(ss, token, ',');
        score = stoi(token);
        getline(ss, token, ',');
        level = stoi(token);
        getline(ss, token, ',');
        health = stoi(token);

        getline(ss, token, ',');
        ex1 = stoi(token);
        getline(ss, token, ',');
        ey1 = stoi(token);
        getline(ss, token, ',');
        enemy1Health = stoi(token);
        getline(ss, token, ',');
        enemy1moveright = (stoi(token) == 1);

        getline(ss, token, ',');
        ex2 = stoi(token);
        getline(ss, token, ',');
        ey2 = stoi(token);
        getline(ss, token, ',');
        enemy2Health = stoi(token);
        getline(ss, token, ',');
        enemy2moveright = (stoi(token) == 1);
        getline(ss, token, ',');
        moveUpperLeft = (stoi(token) == 1);
        getline(ss, token, ',');
        enemy2movedown = (stoi(token) == 1);

        getline(ss, token, ',');
        ex3 = stoi(token);
        getline(ss, token, ',');
        ey3 = stoi(token);
        getline(ss, token, ',');
        enemy3Health = stoi(token);
        getline(ss, token, ',');
        enemy3moveright = (stoi(token) == 1);
        getline(ss, token, ',');
        moveUpperRight = (stoi(token) == 1);
        getline(ss, token, ',');
        enemy3movedown = (stoi(token) == 1);

        getline(ss, token, ',');
        level2reached = (stoi(token) == 1);
        getline(ss, token, ',');
        level3reached = (stoi(token) == 1);
    }

    file.close();
    return true;
}
int resumeGame(int consolewidth, int consoleheight)
{
    int choice;
    setcolor("09");
    gotoxy(consolewidth / 2-11, consoleheight / 2-3);
    cout << "1.New Game";
    gotoxy(consolewidth / 2-14, consoleheight / 2 + 1-3);
    cout << "2.Resume Game";
    gotoxy(consolewidth / 2-12, consoleheight / 2 + 2-3);
    cout << "Choose 1/2: ";
    while (true)
    {
        cin >> choice;
        if (choice == 1 || choice == 2)
            break;
        gotoxy(consolewidth / 2, consoleheight / 2 + 3);
        cout << "Invalid choice! Choose again: ";
    }
    gotoxy(consolewidth / 2, consoleheight / 2);
    cout << "                   ";
    gotoxy(consolewidth / 2, consoleheight / 2 + 1);
    cout << "                   ";
    gotoxy(consolewidth / 2, consoleheight / 2 + 2);
    cout << "                   ";
    return choice;
}
