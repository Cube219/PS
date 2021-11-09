#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll M = 1099511627776;

ll n;
vector<pair<ll, ll>> icnt, ccnt;

void init()
{
    // ll s = 1611516670;
    // ll cnt = 0;
    // // [0, i * 3500000) ¥‹¿ß
    // for(int i = 0; i < 350125310; ++i) {
    //     if(i % 3500000 == 0) {
    //         cout <<"icnt.emplace_back(" << cnt << ", " << s << ");\n";
    //     }
    //
    //     if((s & 1) == 0) cnt++;
    //     s = (s + (s >> 20) + 12345) % M;
    // }
    //
    // cout << "-----\n";
    //
    // cnt = 0;
    // s = 516914;
    // for(int i = 0; i < 350125310; ++i) {
    //     if(i % 3500000 == 0) {
    //         cout << "ccnt.emplace_back(" << cnt << ", " << s << ");\n";
    //     }
    //
    //     if((s & 1) == 0) cnt++;
    //     s = (s + (s >> 20) + 12345) % M;
    //     if(s == 516914) break;
    // }

    icnt.emplace_back(0, 1611516670);
    icnt.emplace_back(1747444, 396925287501);
    icnt.emplace_back(3500189, 121352198450);
    icnt.emplace_back(5255599, 31059159172);
    icnt.emplace_back(7012600, 1473880836);
    icnt.emplace_back(8749837, 393049629374);
    icnt.emplace_back(10504170, 120078616969);
    icnt.emplace_back(12253837, 30643671327);
    icnt.emplace_back(14003713, 1337854506);
    icnt.emplace_back(15765017, 389219300036);
    icnt.emplace_back(17517443, 118826730177);
    icnt.emplace_back(19266808, 30230116928);
    icnt.emplace_back(21014793, 1202088386);
    icnt.emplace_back(22779772, 385396290797);
    icnt.emplace_back(24530608, 117578737596);
    icnt.emplace_back(26290106, 29823565243);
    icnt.emplace_back(28039980, 1069184517);
    icnt.emplace_back(29790824, 381653883227);
    icnt.emplace_back(31539440, 116353077724);
    icnt.emplace_back(33294427, 29421766079);
    icnt.emplace_back(35042602, 937685173);
    icnt.emplace_back(36790658, 377951024021);
    icnt.emplace_back(38537905, 115137995242);
    icnt.emplace_back(40295186, 29024687081);
    icnt.emplace_back(42047577, 807311470);
    icnt.emplace_back(43800494, 374279864915);
    icnt.emplace_back(45554672, 113930757179);
    icnt.emplace_back(47300064, 28628336896);
    icnt.emplace_back(49048470, 677744489);
    icnt.emplace_back(50807120, 370631416795);
    icnt.emplace_back(52565703, 112739509636);
    icnt.emplace_back(54307539, 28238833269);
    icnt.emplace_back(56054526, 549348706);
    icnt.emplace_back(57810409, 367015953407);
    icnt.emplace_back(59564033, 111550530977);
    icnt.emplace_back(61310834, 27846447475);
    icnt.emplace_back(63053853, 421224956);
    icnt.emplace_back(64811970, 363408147688);
    icnt.emplace_back(66572916, 110368043254);
    icnt.emplace_back(68325128, 27461307851);
    icnt.emplace_back(70077203, 295498034);
    icnt.emplace_back(71819695, 359867831507);
    icnt.emplace_back(73576656, 109212377002);
    icnt.emplace_back(75326103, 27081123855);
    icnt.emplace_back(77082751, 170920662);
    icnt.emplace_back(78838699, 356359888735);
    icnt.emplace_back(80589335, 108060955255);
    icnt.emplace_back(82331992, 26705339517);
    icnt.emplace_back(84074594, 47523507);
    icnt.emplace_back(85828888, 352885175757);
    icnt.emplace_back(87569836, 106926639410);
    icnt.emplace_back(89312604, 26330992892);
    icnt.emplace_back(91057196, 1092995098244);
    icnt.emplace_back(92805710, 349429498174);
    icnt.emplace_back(94568344, 105793488505);
    icnt.emplace_back(96324826, 25961451963);
    icnt.emplace_back(98083970, 1082589280689);
    icnt.emplace_back(99838569, 346025778782);
    icnt.emplace_back(101581032, 104671892500);
    icnt.emplace_back(103331017, 25594158522);
    icnt.emplace_back(105080523, 1072246754882);
    icnt.emplace_back(106829714, 342629778882);
    icnt.emplace_back(108592027, 103566955958);
    icnt.emplace_back(110332245, 25231034137);
    icnt.emplace_back(112082235, 1062021621551);
    icnt.emplace_back(113829130, 339280017533);
    icnt.emplace_back(115569496, 102467773271);
    icnt.emplace_back(117331203, 24872773390);
    icnt.emplace_back(119089313, 1051933443521);
    icnt.emplace_back(120841856, 335974803789);
    icnt.emplace_back(122603662, 101383583168);
    icnt.emplace_back(124354613, 24517570166);
    icnt.emplace_back(126098295, 1041931361613);
    icnt.emplace_back(127847228, 332683062482);
    icnt.emplace_back(129606264, 100301802920);
    icnt.emplace_back(131349588, 24163185055);
    icnt.emplace_back(133105067, 1031952315675);
    icnt.emplace_back(134863343, 329422477452);
    icnt.emplace_back(136605753, 99233116795);
    icnt.emplace_back(138356744, 23812246615);
    icnt.emplace_back(140110603, 1022070324749);
    icnt.emplace_back(141866017, 326184975600);
    icnt.emplace_back(143615170, 98174372077);
    icnt.emplace_back(145367505, 23463541077);
    icnt.emplace_back(147114826, 1012251211594);
    icnt.emplace_back(148871301, 322960539867);
    icnt.emplace_back(150621711, 97121853126);
    icnt.emplace_back(152364134, 23120152916);
    icnt.emplace_back(154118719, 1002581823366);
    icnt.emplace_back(155866648, 319796451817);
    icnt.emplace_back(157608612, 96085200428);
    icnt.emplace_back(159359016, 22781111509);
    icnt.emplace_back(161105359, 993034836731);
    icnt.emplace_back(162854633, 316686383532);
    icnt.emplace_back(164610470, 95066537244);
    icnt.emplace_back(166351004, 22447550903);
    icnt.emplace_back(168104811, 983642184332);
    icnt.emplace_back(169850933, 313598890214);
    icnt.emplace_back(171601945, 94047870750);
    icnt.emplace_back(173341991, 22113125701);
    icnt.emplace_back(175085228, 974225187667);
    ccnt.emplace_back(0, 516914);
    ccnt.emplace_back(1737487, 351561528195);
    ccnt.emplace_back(3488423, 106484690902);
    ccnt.emplace_back(5235360, 26188998812);
    ccnt.emplace_back(6985593, 1088996717416);
    ccnt.emplace_back(8729657, 348123400096);
    ccnt.emplace_back(10483788, 105363635318);
    ccnt.emplace_back(12235285, 25820803537);
    ccnt.emplace_back(13985929, 1078628800049);
    ccnt.emplace_back(15740162, 344710855764);
    ccnt.emplace_back(17487179, 104240729349);
    ccnt.emplace_back(19238491, 25452913977);
    ccnt.emplace_back(20988439, 1068269484544);
    ccnt.emplace_back(22734908, 341322667685);
    ccnt.emplace_back(24482873, 103131766532);
    ccnt.emplace_back(26233754, 25088592230);
    ccnt.emplace_back(27985816, 1058010632332);
    ccnt.emplace_back(29720204, 337970286299);
    ccnt.emplace_back(31476082, 102035300196);
    ccnt.emplace_back(33229916, 24729177565);
    ccnt.emplace_back(34971436, 1047889963499);
    ccnt.emplace_back(36721997, 334645380582);
    ccnt.emplace_back(38464747, 100949520763);
    ccnt.emplace_back(40214488, 24373364596);
    ccnt.emplace_back(41968071, 1037870710119);
    ccnt.emplace_back(43720622, 331375096954);
    ccnt.emplace_back(45467671, 99876148217);
    ccnt.emplace_back(47215420, 24021666524);
    ccnt.emplace_back(48968485, 1027967326352);
    ccnt.emplace_back(50723617, 328125899423);
    ccnt.emplace_back(52478367, 98811843402);
    ccnt.emplace_back(54219259, 23673429866);
    ccnt.emplace_back(55967759, 1018161416409);
    ccnt.emplace_back(57729766, 324914460100);
    ccnt.emplace_back(59481940, 97760131531);
    ccnt.emplace_back(61238573, 23329839298);
    ccnt.emplace_back(62987230, 1008486331820);
    ccnt.emplace_back(64740620, 321731539797);
    ccnt.emplace_back(66494917, 96714327280);
    ccnt.emplace_back(68239021, 22987726358);
    ccnt.emplace_back(69988721, 998852854893);
    ccnt.emplace_back(71742391, 318590340795);
    ccnt.emplace_back(73483871, 95683283946);
    ccnt.emplace_back(75229783, 22647907766);
    ccnt.emplace_back(76979292, 989283985222);
    ccnt.emplace_back(78732310, 315457718244);
    ccnt.emplace_back(80473435, 94657250065);
    ccnt.emplace_back(82227144, 22313612218);
    ccnt.emplace_back(83980153, 979870636290);
    ccnt.emplace_back(85728012, 312367545222);
    ccnt.emplace_back(87472621, 93648737970);
    ccnt.emplace_back(89214526, 21982287521);
    ccnt.emplace_back(90964902, 970540944452);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // s(350125310) = 516914
    // period: 182129209
    // cycle even cnt: 91029304
    // 0~350125310 = 175147925

    init();

    ll s = 1611516670;
    ll res = 0;

    cin >> n;
    if(n <= 350125310) {
        res += icnt[n / 3500000].first;
        s = icnt[n / 3500000].second;
        n %= 3500000;
        for(int i = 0; i < n; ++i) {
            if((s & 1) == 0) res++;
            s = (s + (s >> 20) + 12345) % M;
        }
    } else {
        res += 175147925;
        n -= 350125310;
        res += n / 182129209 * 91029304;
        n %= 182129209;

        res += ccnt[n / 3500000].first;
        s = ccnt[n / 3500000].second;
        n %= 3500000;
        for(int i = 0; i < n; ++i) {
            if((s & 1) == 0) res++;
            s = (s + (s >> 20) + 12345) % M;
        }
    }

    cout << res;

    return 0;
}
