/**
        Author : LKN
**/

#include <bits/stdc++.h>
#include "tictactoe.h"
#include <unistd.h>

using namespace std;

void title() {
cout<<"        `..-:/:                 `:--.``                            `-://+ooosy." << '\n';
cout<<".soooo++/:--y+        `-::-` `h+://++oooos+            -/+++/- :h+/:-.``  `y/   .--.     `::-." << '\n';
cout<<"/y.         oy///+:`+so/::/h-/y-`        /h``.-:`   `os/-.`.-so+s.```````` oy+so///+os/` y+:/+oooo+-" << '\n';
cout<<"so.`````````+:.../dy/`   ` soy+.`````````+so+/:/h. :y/`````` +yso.```````.`+y:`      `:y/d:.     `+y" << '\n';
cout<<"h/-...```.:/o-`` /s-`````.`/dd//:-.```..`o-`    os-h:`````.../hy+--:-```-sho-``````````.yh:.``````/h" << '\n';
cout<<"dhyho-```:hmy-```/:.```-+oo+dyhdd:-```+hy+.`````.hd+.```-shhoodyddmy-..`.yh:.```:++:-```-s-```:+/:/d" << '\n';
cout<<".//ys-..`-hys-```+-..`:dhoshy` .h:-..`odd:.``-.``/h:-...yh:/sho ../h:-..`so-..`/dyhd/-.``+-..`-:+hmh" << '\n';
cout<<"   +y:....yms-..`+-..`+h       -h:-...smy-..`+-.`.o:-..:h-        .d/:--.++-..`ss  ys-..`/-.....-h: " << '\n';
cout<<"   /y:---.ymo-..`o:--./h- .//` :y:---.ymo-..-s:-.`:/:--.oy:-/+.    d+:--.+o:--.+y``h+---./:---::/d. " << '\n';
cout<<"   -h/:--.smo:--.o/:--.:oso/y+ /y:::--yd/--.-:----.+:::-.:///so    ho:::./s/:--./ss+:---:/:--:osyd+`" << '\n';
cout<<"   .d/:::-om+:::.sy/::::--:-y/ +s/::-:hy:----------:o/:::::::h/    ss/::::ys/:::---:::::o/:::----/h/" << '\n';
cout<<"    d+///-od+/::-ymy+/////::h: so///:/ho:::::///:::.+s+////:+d`    /y/////ymy+/////////ys///////-od`" << '\n';
cout<<"    do++osyd+///:y+smhso++osd. ys++++oh+//::yddy///::smdyssshy     -dsyhhdd+ydyo++++oydddhyysoo++h+ " << '\n';
cout<<"    ymmdhsodyyyyyd: .+shddhs/  /hhhhhdy+++++h:-dssyhddo-+ooo+.      oyo/-.   -oyddddy+. -:/osyhdmh` " << '\n';
cout<<"     `     -++++/:                   -dmmmddy  :so/:-`" << '\n';
cout << '\n'; cout << '\n'; cout << '\n';
cout << "                                      PRESS ANY KEY TO CONTINUE" << '\n';
        char button;
        button = getch();
}

signed main() {
        board a;
        account acc;
        music_background = PlaySound(TEXT("ANCA.wav"), NULL, SND_ASYNC);

        system("cls");
        title();

        //GAME
        //game_interface(a, acc);
        game_login(a, acc);

        return 0;
}
