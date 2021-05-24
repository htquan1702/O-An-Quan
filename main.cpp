#include <graphics.h>
#include <conio.h>

#define MAXX 800
#define MAXY 550
#define BGC 3
#define BGC2 10
#define ARC 12
#define Y 270

struct Point {
    int x;
    int y;
};

char TxtSpace[] = "              ";
char TxtPlayer10[] = "Player 1: 0";
char TxtPlayer20[] = "Player 2: 0";

int HienTai = 0, DaiDan = 0;

int Abs(int x) {
    return x > 0 ? x : -x;
}

void BackGround() {
    int n = 8;
    setcolor(8);
    setfillstyle(1, BGC);
    for (int i = 1; i < n; i++)
        rectangle(i, i, MAXX - i, MAXY - i);
    bar(n + 1, n + 1, MAXX - n, MAXY - n);
}

Point tdd[] = {{0, 0},
               {0, 0},
               {-25, -25},
               {25, -25},
               {-25, 25},
               {25, 25},
               {0, -25},
               {-25, 0},
               {25, 0},
               {0, 25},
               {-12, -12},
               {12, -12},
               {-12, 12},
               {12, 12},
               {-12, -25},
               {12, -25},
               {-12, 25},
               {12, 25},
               {-25, -12},
               {25, -12},
               {-25, 12},
               {25, 12}};
Point tddq[] = {{0, 0},
                {35, -75},
                {35, -60},
                {35, -45},
                {35, -30},
                {35, -15},
                {35, 0},
                {35, 15},
                {35, 30},
                {35, 45},
                {35, 60},
                {35, 75},
                {20, -75},
                {20, -60},
                {20, -45},
                {20, -30},
                {20, -15},
                {20, 0},
                {20, 15},
                {20, 30},
                {20, 45},
                {20, 60},
                {20, 75}};

void VeDan(int soO, int soDan) {
    int n = (7 - Abs(6 - soO)) * 100;
    int m = Y - 50 + (soO / 6) * 100;
    circle(n + tdd[soDan].x, m + tdd[soDan].y, 3);
}

void VeQuan(int soO) {
    int n = (soO + 1) * 100;
    ellipse(n, Y, 0, 360, 10, 20);
    setfillstyle(1, 2);
    floodfill(n, Y, 8);
}

void XoaQuan() {
    setfillstyle(1, BGC2);
    setcolor(BGC2);
    if (HienTai == 0)
        pieslice(147, Y, 90, 270, 95);
    else
        pieslice(653, Y, -90, 90, 95);
}

void VeBan() {
    line(150, Y - 100, 650, Y - 100);
    line(150, Y + 100, 650, Y + 100);
    arc(150, Y, 90, 270, 100);
    arc(650, Y, -90, 90, 100);
    setfillstyle(1, 10);
    floodfill(400, Y, 8);
    for (int i = 0; i <= 5; i++)
        line(150 + 100 * i, Y - 100, 150 + 100 * i, Y + 100);
    line(150, Y, 650, Y);
    for (int i = 0; i < 12; i++) {
        if (i % 6) {
            for (int j = 1; j <= 5; j++)
                VeDan(i, j);
        } else
            VeQuan(i);
    }
}

void XoaO() {
    int n = (7 - Abs(6 - HienTai)) * 100;
    int m = Y - 50 + (HienTai / 6) * 100;
    setfillstyle(1, BGC2);
    bar(n - 48, m - 48, n + 49, m + 49);
}

void VeMuiTen() {
    int m, n = (7 - Abs(6 - HienTai)) * 100;
    int k = (HienTai / 6) * 2 - 1;
    m = Y + k * 110;
    setcolor(ARC);
    line(n, m, n, m + 30 * k);
    line(n, m, n + 10 * k, m + 10 * k);
    line(n, m, n - 10 * k, m + 10 * k);
}

void XoaMuiTen() {
    int m, n = (7 - Abs(6 - HienTai)) * 100;
    int k = (HienTai / 6) * 2 - 1;
    m = Y + k * 110;
    setcolor(BGC);
    line(n, m, n, m + 30 * k);
    line(n, m, n + 10 * k, m + 10 * k);
    line(n, m, n - 10 * k, m + 10 * k);
}

void ChonO() {
    int n = (7 - Abs(6 - HienTai)) * 100;
    int m = Y - 50 + (HienTai / 6) * 100;
    setcolor(1);
    line(n - 24, m - 44, n - 44, m - 44);
    line(n - 44, m - 44, n - 44, m - 24);
    line(n + 24, m + 44, n + 44, m + 44);
    line(n + 44, m + 44, n + 44, m + 24);
}

void BoChonO() {
    int n = (7 - Abs(6 - HienTai)) * 100;
    int m = Y - 50 + (HienTai / 6) * 100;
    setcolor(BGC2);
    line(n - 24, m - 44, n - 44, m - 44);
    line(n - 44, m - 44, n - 44, m - 24);
    line(n + 24, m + 44, n + 44, m + 44);
    line(n + 44, m + 44, n + 44, m + 24);
}

void UpdateScore(int Player, int Score) {
    char *text = new char[14];
    sprintf(text, "Player %d: %d ", 2 - Player, Score);
    setcolor(0);
    outtextxy(100, 50 + Player * 380, text);
    delete[] text;
}

void UpdateRemain(int Player, int Remain) {
    char *text = new char[15];
    sprintf(text, "Remaining: %d ", Remain);
    setcolor(1);
    outtextxy(100, 90 + Player * 380, text);
    delete[] text;
}

void ClearRemain(int Player) {
    outtextxy(100, 90 + Player * 380, TxtSpace);
}

void EndGame(int Score[]) {
    char *text = new char[17];
    setcolor(0);
    sprintf(text, "Player 1: %d", Score[1]);
    outtextxy(100, 170, text);
    sprintf(text, "Player 2: %d", Score[0]);
    outtextxy(100, 250, text);
    sprintf(text, "Winner: Player %d", Score[0] > Score[1] ? 2 : 1);
    outtextxy(100, 330, text);
    delete[] text;
}

class OAnQuan {
  private:
  public:
    int conQuan;
    int soDan;
    void veDan();
};

void OAnQuan::veDan() {
    int n, m;
    setcolor(8);
    if (HienTai % 6 == 0) {
        n = (HienTai + 1) * 100;
        circle(n + (1 - HienTai / 3) * tddq[this->soDan].x, Y + tddq[this->soDan].y, 3);
    } else {
        int n = (7 - Abs(6 - HienTai)) * 100;
        int m = Y - 50 + (HienTai / 6) * 100;
        circle(n + tdd[this->soDan].x, m + tdd[this->soDan].y, 3);
    }
}

int main() {
    initwindow(MAXX + 9, MAXY + 13);
    BackGround();
    OAnQuan oaq[12];
    char c;
    int Player = 1, tmp, DaChon = 0, Game = 1;
    int Score[2] = {0, 0};
    settextstyle(10, 0, 3);
    setbkcolor(BGC);
    int mx;
    for (int i = 0; i < 12; i++) {
        if (i % 6 == 0) {
            oaq[i].soDan = 0;
            oaq[i].conQuan = 1;
        } else
            oaq[i].soDan = 5;
    }
    setlinestyle(0, 0, 2);
    VeBan();
    HienTai = 7;
    setcolor(0);
    outtextxy(100, 50, TxtPlayer20);
    outtextxy(100, 430, TxtPlayer10);
    while (true) {
        VeMuiTen();
        while (DaChon != 2) {
            c = getch();
            switch (c) {
            case 75:
                if (DaChon == 0) {
                    XoaMuiTen();
                    do {
                        HienTai -= (1 - 2 * Player);
                        if (HienTai == Player * 12)
                            HienTai = Player * 2 + 5;
                    } while (oaq[HienTai].soDan == 0);
                    VeMuiTen();
                } else {
                    DaChon = 2;
                    mx = Player * 2 - 1;
                }
                break;
            case 77:
                if (DaChon == 0) {
                    XoaMuiTen();
                    do {
                        HienTai += (1 - 2 * Player);
                        if (HienTai == 6)
                            HienTai = Player * 10 + 1;
                    } while (oaq[HienTai].soDan == 0);
                    VeMuiTen();
                } else {
                    DaChon = 2;
                    mx = 1 - Player * 2;
                }
                break;
            case 13:
                if (DaChon == 0) {
                    UpdateRemain(Player, oaq[HienTai].soDan);
                    ChonO();
                    DaChon = 1;
                } else {
                    ClearRemain(Player);
                    BoChonO();
                    DaChon = 0;
                }
                break;
            }
        }
        DaChon = 0;
        XoaMuiTen();
        DaiDan = oaq[HienTai].soDan;
        oaq[HienTai].soDan = 0;
        XoaO();
        while (true) {
            delay(400);
            if (DaiDan == 0) {
                HienTai += mx;
                if (HienTai == 12)
                    HienTai = 0;
                else if (HienTai == -1)
                    HienTai = 11;
                if (HienTai % 6) {
                    XoaO();
                    DaiDan = oaq[HienTai].soDan;
                    UpdateRemain(Player, DaiDan);
                    if (DaiDan == 0) {
                        do {
                            HienTai += mx;
                            if (HienTai == 12)
                                HienTai = 0;
                            else if (HienTai == -1)
                                HienTai = 11;
                            if (HienTai % 6 == 0) {
                                if (oaq[HienTai].conQuan) {
                                    if (oaq[HienTai].soDan >= 5) {
                                        Score[Player] += (oaq[HienTai].soDan + 10);
                                        UpdateScore(Player, Score[Player]);
                                        oaq[HienTai].soDan = 0;
                                        oaq[HienTai].conQuan = 0;
                                        XoaQuan();
                                        if (oaq[6 - HienTai].soDan == 0 && oaq[6 - HienTai].conQuan == 0)
                                            Game = 0;
                                    } else
                                        break;
                                } else if (oaq[HienTai].soDan > 0) {
                                    Score[Player] += oaq[HienTai].soDan;
                                    UpdateScore(Player, Score[Player]);
                                    oaq[HienTai].soDan = 0;
                                    XoaQuan();
                                    if (oaq[6 - HienTai].soDan == 0 && oaq[6 - HienTai].conQuan == 0)
                                        Game = 0;
                                } else
                                    break;
                            } else if (oaq[HienTai].soDan > 0) {
                                Score[Player] += oaq[HienTai].soDan;
                                UpdateScore(Player, Score[Player]);
                                oaq[HienTai].soDan = 0;
                                XoaO();
                            } else
                                break;
                            HienTai += mx;
                            if (HienTai == 12)
                                HienTai = 0;
                            else if (HienTai == -1)
                                HienTai = 11;
                            DaiDan = oaq[HienTai].soDan;
                            delay(400);
                        } while (DaiDan == 0);
                        break;
                    }
                    oaq[HienTai].soDan = 0;
                    delay(400);
                } else
                    break;
            }
            DaiDan--;
            UpdateRemain(Player, DaiDan);
            HienTai += mx;
            if (HienTai == 12)
                HienTai = 0;
            else if (HienTai == -1)
                HienTai = 11;
            oaq[HienTai].soDan++;
            oaq[HienTai].veDan();
        }
        if (!Game)
            break;
        ClearRemain(Player);
        Player = 1 - Player;
        tmp = 1;
        do {
            HienTai = 6 * Player + tmp;
            tmp++;
        } while (oaq[HienTai].soDan == 0 && tmp <= 5);
        if (oaq[HienTai].soDan == 0) {
            Score[Player] -= 5;
            UpdateScore(Player, Score[Player]);
            setcolor(8);
            for (int i = 1 + 6 * Player; i < 6 + 6 * Player; i++) {
                VeDan(i, 1);
                oaq[i].soDan = 1;
            }
        }
    }
    for (int i = 1; i < 6; i++)
        Score[0] += oaq[i].soDan;
    for (int i = 7; i < 12; i++)
        Score[1] += oaq[i].soDan;
    cleardevice();
    BackGround();
    setcolor(0);
    EndGame(Score);
    getch();
    closegraph();
    return 0;
}
