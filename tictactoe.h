/**
        author : LKN
**/

#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>

#define fi first
#define se second

using namespace std;

HANDLE color;
bool login = false;
int pos = 0, demm = 0, time_limit = 0, color_board = 15;
bool background = true, sound = true;
bool music_background, music_sound, computer = false, time_mode = false;

void print_menu(char s[100][100], int x, int n) {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        for (int i = 1; i <= n; i++) {
                if (i == x)
                        SetConsoleTextAttribute(color, 16);
                cout << s[i] << '\n';
                SetConsoleTextAttribute(color, 15);
        }
}

struct account {
        char username[101][101], password[101][101], name[101][101], achievement[101][101][101];
        int nacc, nachievement[101];

        void init() {
                for (int i = 0; i <= 100; i++)
                        nachievement[i] = 0;
                for (int i = 0; i <= 100; i++)
                        for (int j = 0; j <= 100; j++)
                                username[i][j] = password[i][j] = 0;

                for (int i = 0; i <= 100; i++)
                        for (int j = 0; j <= 100; j++)
                                for (int k = 0; k <= 100; k++)
                                        achievement[i][j][k] = 0;
        }

        bool acc_check(char tmp[101], char username[101][101]) {
                for (int i = 1; i <= nacc; i++) {
                        bool kt = true;
                        for (int j = 0; j <= 100; j++)
                                if (username[i][j] != tmp[j]) {
                                        kt = false;
                                        break;
                                }

                        if (kt) {
                                pos = i;
                                return true;
                        }
                }
                return false;
        }

        void input_data() {
                ifstream fi("D:\\LKN\\Tic Tac Toe\\ACCOUNT.txt");
                fi >> nacc;
                for (int i = 1; i <= nacc; i++)
                        fi >> username[i];
                for (int i = 1; i <= nacc; i++)
                        fi >> password[i];
                for (int i = 1; i <= nacc; i++)
                        fi >> name[i];

                for (int i = 1; i <= nacc; i++)
                        fi >> nachievement[i];
                char tmp[101];
                fi.getline(tmp, 101);
                for (int i = 1; i <= nacc; i++) {
                        for (int j = 1; j <= nachievement[i]; j++)
                               fi.getline(achievement[i][j], 101);
                }

                fi.close();
        }

        void output_data() {


                fstream fo;
                fo.open("D:\\LKN\\Tic Tac Toe\\ACCOUNT.txt");
                fo << nacc << '\n';
                for (int i = 1; i <= nacc; i++)
                        fo << username[i] << '\n';
                for (int i = 1; i <= nacc; i++)
                        fo << password[i] << '\n';
                for (int i = 1; i <= nacc; i++)
                        fo << name[i] << '\n';

                for (int i = 1; i <= nacc; i++)
                        fo << nachievement[i] << " ";
                fo << '\n';
                for (int i = 1; i <= nacc; i++)
                        for (int j = 1; j <= nachievement[i]; j++)
                                fo << achievement[i][j] << '\n';
                fo.close();
        }

        void create_account() {
                system("cls");

                //cout << "ESC : Exit" << '\n';

                cout << "REGISTER" << '\n';
                nacc++;
                while (true) {
                        char tmp[101] = "";
                        system("cls");
                        cout << "Username : ";
                        cin >> tmp;
                        if (!acc_check(tmp, username)) {
                                for (int i = 0; i <= 100; i++)
                                        username[nacc][i] = tmp[i];
                                break;
                        }
                        else {
                                cout << "This Username Is Already Chosen" << '\n';
                                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                char button = getch();
                        }
                }
                cout << "Password : ";
                cin >> password[nacc];
                cout << "Please Enter Your Name : ";
                cin >> name[nacc];

                output_data();
        }

        void acc_login() {
                char tmp1[101] = "", tmp2[101] = "";
                while (true) {
                        system("cls");
                        cout << "LOGIN" << '\n';
                        cout << "Username : ";
                        cin >> tmp1;
                        cout << "Password : ";
                        cin >> tmp2;

                        if (acc_check(tmp1, username) && acc_check(tmp2, password)) {
                                cout << "LOGIN SUCCESSFUL !" << '\n';
                                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                char button = getch();
                                login = true;
                                break;
                        }
                        else {
                                cout << "Wrong Username Or Password" << '\n';
                                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                char button = getch();
                        }
                }
        }
};

struct board {
        char grid[101][101], player[3] = {0, 'X', 'O'};
        char name[3][101] {"", "", ""};
        bool check[101][101], win = false, time_out = false, out = false;
        int n = 3, ntrace = 0;
        pair <int, int> trace[1000];

        void init() {
                color = GetStdHandle(STD_OUTPUT_HANDLE);

                for (int i = 1; i <= 7; i++)
                        for (int j = 1; j <= 7; j++) {
                                grid[i][j] = 0;
                                check[i][j] = true;
                        }
                for (int i = 1; i <= 50; i++)
                        trace[i].fi = trace[i].se = 0;

                ntrace = 0;
                time_out = false;
        }

        bool check_tie() {
                for (int i = 1; i <= n; i++)
                        for (int j = 1; j <= n; j++)
                                if (check[i][j])
                                        return false;
                return true;
        }

        bool check_win(int x, int y, char symbol) {
                int cnt;

                //straight horizontal
                cnt = 1;
                for (int i = 1; i <= 2; i++)
                        if (y+i <= n && grid[x][y+i] == symbol)
                                cnt++;
                        else break;
                for (int i = 1; i <= 2; i++)
                        if (y-i >= 1 && grid[x][y-i] == symbol)
                                cnt++;
                        else break;
                if (cnt == n) return true;

                //straight vertical
                cnt = 1;
                for (int i = 1; i <= 2; i++)
                        if (x+i <= n && grid[x+i][y] == symbol)
                                cnt++;
                        else break;
                for (int i = 1; i <= 2; i++)
                        if (x-i >= 1 && grid[x-i][y] == symbol)
                                cnt++;
                        else break;
                if (cnt >= n) return true;

                //diagonal 1
                cnt = 1;
                for (int i = 1; i <= 2; i++)
                        if (x+i <= n && y+i <= n && grid[x+i][y+i] == symbol)
                                cnt++;
                        else break;
                for (int i = 1; i <= 2; i++)
                        if (x-i >= 1 && y-i >= 1 && grid[x-i][y-i] == symbol)
                                cnt++;
                        else break;
                if (cnt >= n) return true;

                //diagonal 2
                cnt = 1;
                for (int i = 1; i <= 2; i++)
                        if (x-i >= 1 && y+i <= n && grid[x-i][y+i] == symbol)
                                cnt++;
                        else break;
                for (int i = 1; i <= 2; i++)
                        if (y-i >= 1 && x+i <= n && grid[x+i][y-i] == symbol)
                                cnt++;
                        else break;
                if (cnt >= n) return true;

                return false;
        }

        bool evaluate(char symbol) {
                for (int i = 1; i <= n; i++)
                        for (int j = 1; j <= n; j++)
                                if (check_win(i, j, symbol))
                                        return true;
        }

        int minimax(int depth, bool turn, int x) {
                if (x == 2) {
                        if (evaluate(player[1]))
                                return -10;
                }
                else if (evaluate(player[2]))
                                return -10;

                if (evaluate(player[x]))
                        return 10;

                if (check_tie())
                        return 0;

                if (check) {
                        int MAX = -1000;
                        for (int i = 1; i <= n; i++)
                                for (int j = 1; j <= n; j++)
                                        if (check[i][j]) {
                                                check[i][j] = false;
                                                grid[i][j] = player[x];
                                                MAX = max(MAX, minimax(depth+1, !turn, x));

                                                grid[i][j] = 0;
                                                check[i][j] = true;
                                        }
                        return MAX;
                }
                else {
                        int MAX = 1000;
                        for (int i = 1; i <= n; i++)
                                for (int j = 1; j <= n; j++)
                                        if (check[i][j]) {
                                                check[i][j] = false;
                                                if (2 == x)
                                                        grid[i][j] = player[1];
                                                else
                                                        grid[i][j] = player[2];
                                                MAX = min(MAX, minimax(depth+1, !turn, x));

                                                grid[i][j] = 0;
                                                check[i][j] = true;
                                        }
                        return MAX;
                }
        }

        pair <int, int> best_moves(int x) {
                int MAX = -1000;
                pair <int, int> res;
                res.fi = 0;
                res.se = 0;

                for (int i = 1; i <= n; i++)
                        for (int j = 1; j <= n; j++)
                                if (check[i][j]) {
                                        grid[i][j] = player[x];
                                        check[i][j] = false;

                                        int val = minimax(0, false, x);

                                        grid[i][j] = 0;
                                        check[i][j] = true;

                                        if (val > MAX) {
                                                res.fi = i;
                                                res.se = j;
                                                MAX = val;
                                        }
                                }
                return res;
        }

        void print_horizontal() {
                color = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(color, color_board);
                cout << " ";
                for (int i = 1; i <= n; i++)
                        cout << "------- ";
                cout << '\n';
        }

        void print_vertical(int x, int y, int z) {
                color = GetStdHandle(STD_OUTPUT_HANDLE);
                for (int i = 1; i <= 3; i++) {
                        for (int j = 1; j <= n; j++) {
                                SetConsoleTextAttribute(color, color_board);
                                cout << "|";

                                if (z == x && j == y)
                                        SetConsoleTextAttribute(color, 16);

                                if (i != 2)
                                        cout << "       ";
                                else {
                                        cout << "   ";
                                        if (grid[z][j] == 0)
                                                cout << " ";
                                        else
                                                cout << grid[z][j];
                                        cout << "   ";
                                }
                        }
                        SetConsoleTextAttribute(color, color_board);
                        cout << "|";
                        cout << '\n';
                }

        }

        void print_board(int x, int y) {
                color = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(color, 15);
                if (!time_mode)
                        cout << "ESC : Exit     S : Save Game     D : Suggestion Move" << '\n';
                else
                        cout << "ESC : Exit     D : Suggestion Move" << '\n';
                for (int i = 1; i <= n; i++) {
                        print_horizontal();
                        print_vertical(x, y, i);
                }
                print_horizontal();
                SetConsoleTextAttribute(color, 15);
        }

        void save_game(int x, int y) {
                fstream fo;

                fo.open("D:\\LKN\\Tic Tac Toe\\SAVE GAME.txt");
                fo << n << '\n';
                for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++)
                                if (grid[i][j] != 0)
                                        fo << grid[i][j] << " ";
                                else
                                        fo << 0 << " ";
                        fo << '\n';
                }

                for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++)
                                fo << check[i][j] << " ";
                        fo << '\n';
                }

                fo << ntrace << '\n';
                for (int i = 1; i <= ntrace; i++)
                        fo << trace[i].fi << " " << trace[i].se << '\n';

                fo << player[1] << " " << player[2] << '\n';
                fo << name[1] << '\n';
                fo << name[2] << '\n';

                fo.close();

                color = GetStdHandle(STD_OUTPUT_HANDLE);
                system("cls");
                print_board(x, y);
                cout << "GAME SAVED !" << '\n';
                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                char button = getch();
        }

        void movement(int &x, int &y, char symbol) {
                color = GetStdHandle(STD_OUTPUT_HANDLE);

                time_out = false;
                system("cls");
                print_board(x, y);
                clock_t start;
                double duration;
                start = std::clock();
                while (true) {
                        bool suggestion = false;
                        char button = getch();
                        if (time_mode && ((clock()-start)/(double)CLOCKS_PER_SEC) > time_limit) {
                                time_out = true;
                                break;
                        }
                        if (sound)
                                music_sound = PlaySound(TEXT("tick.wav"), NULL, SND_ASYNC);

                        if (button == 13) {
                                if (check[x][y]) {
                                        system("cls");
                                        grid[x][y] = symbol;
                                        check[x][y] = false;
                                        win = check_win(x, y, symbol);
                                        ntrace++;
                                        trace[ntrace].fi = x; trace[ntrace].se = y;
                                        print_board(0, 0);
                                        break;
                                }
                                else {
                                        cout << "INVALID MOVE !" << '\n';
                                        button = getch();
                                }
                        }

                        if (button == 27) {
                                out = true;
                                break;
                        }

                        if (button == 100) {
                                int num;
                                if (player[1] == symbol)
                                        num = 1;
                                else num = 2;
                                pair <int, int> res = best_moves(num);
                                system("cls");
                                x = res.fi; y = res.se;
                                print_board(x, y);
                                cout << "Suggestion Move : " << '\n';
                                cout << "COL : " << res.fi << " ROW : " << res.se << '\n';
                                suggestion = true;
                        }
                        else if (!time_mode && button == 115)
                                save_game(x, y);
                        else if (button = -32) {
                                button = getch();
                                if (time_mode && ((clock()-start)/(double)CLOCKS_PER_SEC) > time_limit) {
                                        time_out = true;
                                        break;
                                }
                                if (sound)
                                        music_sound = PlaySound(TEXT("tick.wav"), NULL, SND_ASYNC);

                                if (button == 72)
                                        if (x > 1)
                                                x--;

                                if (button == 80)
                                        if (x < n)
                                                x++;

                                if (button == 75)
                                        if (y > 1)
                                                y--;

                                if (button == 77)
                                        if (y < n)
                                                y++;
                        }

                        if (!suggestion) {
                                system("cls");
                                print_board(x, y);
                        }

                }
        }

        void play(account &acc) {
                color = GetStdHandle(STD_OUTPUT_HANDLE);

                bool p1 = true;
                int x, y, cnt1 = 0, cnt2 = 0;
                x = y = n/2 + 1;
                out = false;
                while (true) {
                        if (p1) {
                                cnt1++;
                                movement(x, y, player[1]);
                                if (out) break;
                                p1 = false;
                                if (win) {
                                        cout << name[1] << " Won In " << cnt1 << " Moves" << '\n';
                                        if (login) {
                                                acc.nachievement[pos]++;
                                                int tmp = acc.nachievement[pos], tmp1 = 0;
                                                acc.achievement[pos][tmp][0] = 'Y';
                                                acc.achievement[pos][tmp][1] = 'o';
                                                acc.achievement[pos][tmp][2] = 'u';
                                                acc.achievement[pos][tmp][3] = ' ';
                                                acc.achievement[pos][tmp][4] = 'W';
                                                acc.achievement[pos][tmp][5] = 'o';
                                                acc.achievement[pos][tmp][6] = 'n';
                                                acc.achievement[pos][tmp][7] = ' ';
                                                while (name[2][tmp1] != 0)
                                                        tmp1++;
                                                for (int i = 8; i <= 8+tmp1-1; i++)
                                                        acc.achievement[pos][tmp][i] = name[2][i-8];
                                                acc.achievement[pos][tmp][8+tmp1] = ' ';
                                                acc.achievement[pos][tmp][tmp1+9] = 'I';
                                                acc.achievement[pos][tmp][tmp1+10] = 'n';
                                                acc.achievement[pos][tmp][tmp1+11] = ' ';
                                                tmp1 = tmp1 + 12;

                                                char kitu[101];
                                                int dem = 100;
                                                while (cnt1 > 0) {
                                                        kitu[dem] = (cnt1 % 10) +'0';
                                                        cnt1 = cnt1/10;
                                                        dem--;
                                                }

                                                for (int i = 1; i <= 100-dem; i++)
                                                        acc.achievement[pos][tmp][tmp1+i-1] = kitu[dem+i];

                                                tmp1 = tmp1 + 100-dem;
                                                acc.achievement[pos][tmp][tmp1] = ' ';
                                                acc.achievement[pos][tmp][tmp1+1] = 'M';
                                                acc.achievement[pos][tmp][tmp1+2] = 'o';
                                                acc.achievement[pos][tmp][tmp1+3] = 'v';
                                                acc.achievement[pos][tmp][tmp1+4] = 'e';
                                                acc.achievement[pos][tmp][tmp1+5] = 's';

                                                acc.output_data();
                                        }
                                        cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                        char button = getch();
                                        break;
                                }
                                if (time_mode && time_out) {
                                        cout << "TIME OUT!" << '\n';
                                        cout << name[2] << " Won In " << cnt2 << " Moves" << '\n';
                                        cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                        char button = getch();
                                        break;
                                }
                        }
                        else {
                                cnt2++;
                                if (!computer)
                                        movement(x, y, player[2]);
                                else {
                                        pair <int, int> res = best_moves(2);
                                        grid[res.fi][res.se] = player[2];
                                        check[res.fi][res.se] = false;
                                        win = check_win(res.fi, res.se, player[2]);
                                        ntrace++;
                                        trace[ntrace].fi = res.fi; trace[ntrace].se = res.se;
                                        print_board(0, 0);
                                }
                                if (out) break;
                                p1 = true;
                                if (win) {
                                        cout << name[2] << " Won In " << cnt2 << " Moves" << '\n';
                                        cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                        char button = getch();
                                        break;
                                }
                                if (time_mode && time_out) {
                                        cout << "TIME OUT!" << '\n';
                                        cout << name[1] << " Won In " << cnt1 << " Moves" << '\n';
                                        cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                        char button = getch();
                                        break;
                                }
                        }
                        if (check_tie()) {
                                cout << "IT'S A TIE !" << '\n';
                                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                char button = getch();
                                break;
                        }
                }
                if (out) init();
        }

        void replay() {
                char tmp[8][8];

                //init
                for (int i = 1; i <= n; i++)
                        for (int j = 1; j <= n; j++) {
                                tmp[i][j] = grid[i][j];
                                grid[i][j] = 0;
                        }

                //trace
                for (int i = 1; i <= ntrace; i++) {
                        int x = trace[i].fi, y = trace[i].se;
                        grid[x][y] = tmp[x][y];

                        system("cls");
                        print_board(0, 0);
                        cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                        char button = getch();
                }
        }

        void gamereplay() {
                color = GetStdHandle(STD_OUTPUT_HANDLE);

                char s[100][100] {"", "YES", "NO"};
                int x = 1;

                system("cls");
                cout << "Do You Want To Watch Replay ? " << '\n';
                print_menu(s, x, 2);

                while (true) {
                        char button = getch();
                        if (button == 13) {
                                switch (x) {
                                        case 1 : {
                                                replay();
                                                break;
                                        }

                                        case 2 : {

                                                break;
                                        }
                                }
                                break;
                        }

                        if (button == -32) {
                                button = getch();

                                if (button == 72)
                                        if (x > 1)
                                                x--;

                                if (button == 80)
                                        if (x < 2)
                                                x++;
                        }

                        system("cls");
                        cout << "Do You Want To Watch Replay ? " << '\n';
                        print_menu(s, x, 2);
                }
        }
};

void player_name(board &a) {
        system("cls");

        if (!login) {
                cout << "PLayer 1 Please Enter Your Name : ";
                cin >> a.name[1];
        }
        if (!computer) {
                cout << "Player 2 Please Enter Your Name : ";
                cin >> a.name[2];
        }
        else {
                a.name[2][0] = 'C';
                a.name[2][1] = 'o';
                a.name[2][2] = 'm';
                a.name[2][3] = 'p';
                a.name[2][4] = 'u';
                a.name[2][5] = 't';
                a.name[2][6] = 'e';
                a.name[2][7] = 'r';
        }
}

void choose_grid(board &a) {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        int x = 1;

        system("cls");
        cout << "Choose The Grid Size : ";
        cin >> a.n;
}

void player_icons(board &a) {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        char s[100][100] {"", "Player 1 Icon : ", "Player 2 Icon : "};
        int x = 1;

        system("cls");
        for (int i = 1; i <= 2; i++) {
                if (i == x)
                        SetConsoleTextAttribute(color, 16);
                cout << s[i] << a.player[i] << '\n';
                SetConsoleTextAttribute(color, 15);
        }

        while (true) {
                char button = getch();

                if (button == 13) {
                        system("cls");
                        cout << "Enter the icon (1 character only) : ";
                        cin >> a.player[x];
                }

                if (button == 27)
                        break;

                if (button == -32) {
                        button = getch();

                        if (button == 72)
                                if (x > 1)
                                        x--;

                        if (button == 80)
                                if (x < 2)
                                        x++;;
                }

                system("cls");
                for (int i = 1; i <= 2; i++) {
                        if (i == x)
                                SetConsoleTextAttribute(color, 16);
                        cout << s[i] << a.player[i] << '\n';
                        SetConsoleTextAttribute(color, 15);
                }
        }
}

void board_color() {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        char s[100][100] {"", "BLUE", "GREEN", "AQUA", "RED", "PURPLE", "YELLOW", "WHITE", "GRAY", "LIGHT BLUE", "LIGHT GREEN", "LIGHT AQUA", "LIGHT RED", "LIGHT PURPLE", "LIGHT YELLOW", "BRIGHT WHITE"};
        int x = 1;

        system("cls");
        cout << "Choose The Color Of The Board :" << '\n';
        print_menu(s, x, 15);

        while (true) {
                char button = getch();

                if (button == 13) {
                        color_board = x;
                        break;
                }

                if (button == -32) {
                        button = getch();

                        if (button == 72)
                                if (x > 1)
                                        x--;

                        if (button == 80)
                                if (x < 15)
                                        x++;
                }

                system("cls");
                cout << "Choose The Color Of The Board :" << '\n';
                print_menu(s, x, 15);
        }
}

void sound_setting() {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        char s[100][100] {"", "1) Background music : ", "2) Sound effect : "};
        int x = 1;
        system("cls");
        cout << "ESC : Exit" << '\n';
        for (int i = 1; i <= 2; i++) {
                if (i == x)
                        SetConsoleTextAttribute(color, 16);
                cout << s[i];
                if (i == 1) {
                        if (background)
                                cout << "On" << '\n';
                        else cout << "Off" << '\n';
                }
                else
                        if (sound)
                                cout << "On" << '\n';
                        else cout << "Off" << '\n';
                SetConsoleTextAttribute(color, 15);
        }

        while (true) {
                char button = getch();

                if (button == 13) {
                        switch (x) {
                                case 1 : {
                                        if (background) {
                                                background = false;
                                                music_background = PlaySound(TEXT("tick.wav"), NULL, SND_ASYNC);
                                        }
                                        else {
                                                background = true;
                                                music_background = PlaySound(TEXT("ANCA.wav"), NULL, SND_ASYNC);
                                        }
                                        break;
                                }

                                case 2 : {
                                        if (sound)
                                                sound = false;
                                        else
                                                sound = true;
                                        break;
                                }
                        }
                }

                if (button == 27)
                        break;

                if (button == -32) {
                        button = getch();

                        if (button == 72)
                                if (x > 1)
                                        x--;

                        if (button == 80)
                                if (x < 2)
                                        x++;
                }

                system("cls");
                cout << "ESC : Exit" << '\n';
                for (int i = 1; i <= 2; i++) {
                        if (i == x)
                                SetConsoleTextAttribute(color, 16);
                        cout << s[i];
                        if (i == 1) {
                                if (background)
                                        cout << "On" << '\n';
                                else cout << "Off" << '\n';
                        }
                        else
                        if (sound)
                                cout << "On" << '\n';
                        else cout << "Off" << '\n';
                        SetConsoleTextAttribute(color, 15);
                }
        }
}

void game_setting(board &a, account &acc) {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        char s[100][100] {"", "1) Choose The Grid Size", "2) Change The Color Of The Board Background", "3) Change The Player Icons", "4) Turn On/Off Sound And Background Music"};
        int x = 1;

        system("cls");
        cout << "MENU :" << '\n';
        print_menu(s, x, 4);

        while (true) {
                char button = getch();
                if (button == 13) {
                        switch (x) {
                                case 1 : {
                                        choose_grid(a);
                                        break;
                                }
                                case 2 : {
                                        board_color();
                                        break;
                                }
                                case 3 : {
                                        player_icons(a);
                                        break;
                                }
                                case 4 : {
                                        sound_setting();
                                        break;
                                }
                        }
                }

                if (button == 27)
                        break;

                if (button == -32) {
                        button = getch();

                        if (button == 72)
                                if (x > 1)
                                        x--;

                        if (button == 80)
                                if (x < 4)
                                        x++;
                }

                system("cls");
                cout << "MENU :" << '\n';
                print_menu(s, x, 4);
        }
}

void game_interface(board &a, account &acc) {
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        char s[100][100] {"", "Start Game", "Load Save Game", "Restriction Time Mode", "Play Against Computer", "Account Statistical Outcome (Achievement)", "Setting", "Exit (Log Out)"};
        int x = 1;

        system("cls");
        if (!login)
                cout << "                                                         You're Not Logged In" << '\n';
        else
                cout << "                                                                " << acc.name[pos] << "(" << acc.username[pos] << ")" << '\n';
        print_menu(s, x, 7);

        while (true) {
                bool kt = false;
                char button = getch();

                if (button == 13) {
                        switch (x) {
                                case 1 : {
                                        a.init();
                                        demm++;
                                        player_name(a);
                                        a.play(acc);
                                        if (!a.out)
                                                a.gamereplay();
                                        break;
                                }

                                case 2 : {
                                        ifstream fi("D:\\LKN\\Tic Tac Toe\\SAVE GAME.txt");

                                        fi >> a.n;
                                        for (int i = 1; i <= a.n; i++)
                                                for (int j = 1; j <= a.n; j++) {
                                                        fi >> a.grid[i][j];
                                                        if (a.grid[i][j] == '0')
                                                                a.grid[i][j] = 0;
                                                }
                                        for (int i = 1; i <= a.n; i++)
                                                for (int j = 1; j <= a.n; j++)
                                                        fi >> a.check[i][j];

                                        fi >> a.ntrace;
                                        for (int i = 1; i <= a.ntrace; i++)
                                                fi >> a.trace[i].fi >> a.trace[i].se;

                                        fi >> a.player[1] >> a.player[2];
                                        fi >> a.name[1];
                                        fi >> a.name[2];

                                        fi.close();

                                        a.play(acc);
                                        if (!a.out)
                                                a.gamereplay();

                                        break;
                                }

                                case 3 : {
                                        a.init();
                                        time_mode = true;
                                        system("cls");
                                        cout << "Enter Time Limit For Each Moves : ";
                                        cin >> time_limit;
                                        player_name(a);
                                        a.play(acc);
                                        if (!a.out)
                                                a.gamereplay();

                                        time_mode = false;
                                        break;
                                }

                                case 4 : {
                                        computer = true;
                                        a.init();
                                        player_name(a);
                                        a.play(acc);
                                        if (!a.out)
                                                a.gamereplay();

                                        computer = false;
                                        break;
                                }

                                case 5 : {
                                        system("cls");
                                        if (login) {
                                                cout << "Here Is Your Achievements :" << '\n';
                                                for (int i = 1; i <= acc.nachievement[pos]; i++)
                                                        cout << acc.achievement[pos][i] << '\n';

                                                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                                char button = getch();
                                        }
                                        else {
                                                cout << "You Need To Login To See Your Achievements" << '\n';
                                                cout << "PRESS ANY KEY TO CONTINUE" << '\n';
                                                char button = getch();
                                        }
                                        break;
                                }

                                case 6 : {
                                        game_setting(a, acc);
                                        break;
                                }

                                case 7 : {
                                        login = false;
                                        kt = true;
                                        break;
                                }
                        }
                        if (kt) break;
                }

                if (button == -32) {
                        button = getch();

                        if (button == 72)
                                if (x > 1)
                                        x--;

                        if (button == 80)
                                if (x < 7)
                                        x++;
                }

                system("cls");
                if (!login)
                        cout << "                                                         You're Not Logged In" << '\n';
                else
                        cout << "                                                                " << acc.name[pos] << "(" << acc.username[pos] << ")" << '\n';
                print_menu(s, x, 7);
        }
}

void game_login(board &a, account &acc) {
        acc.init();
        acc.input_data();
        color = GetStdHandle(STD_OUTPUT_HANDLE);

        char s[100][100] {"", "Play As Guest", "Login To An Existing Account", "Create Account", "Quit Game"};

        int x = 1;
        system("cls");
        print_menu(s, x, 4);

        while (true) {
                char button = getch();

                if (button == 13) {
                        switch (x) {
                                case 1 : {
                                        game_interface(a, acc);
                                        break;
                                }
                                case 2 : {
                                        acc.acc_login();
                                        if (login)
                                                for (int i = 0; i <= 100; i++)
                                                        a.name[1][i] = acc.name[pos][i];
                                        game_interface(a, acc);
                                        break;
                                }
                                case 3 : {
                                        acc.create_account();
                                        break;
                                }
                                case 4 : {
                                        acc.output_data();
                                        exit(0);
                                        break;
                                }
                        }
                }

                if (button == -32) {
                        button = getch();

                        if (button == 72)
                                if (x > 1)
                                        x--;

                        if (button == 80)
                                if (x < 4)
                                        x++;
                }

                system("cls");
                print_menu(s, x, 4);

        }
}
