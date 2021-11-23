#include <iostream>
#include <string>

using namespace std;

int itc_len(string str){
    long long kol = 0;
    for(long long i = 0; str[i] != '\0'; i++){
        kol++;
    }
    return kol;
}

unsigned long long itc_toInt(string s){
    long long num = 0;
    for(long long i = 0; i < itc_len(s); i++){
        num += s[i] - 48;
        num *= 10;
    }
    num /= 10;
    return num;
}

string itc_toString(unsigned long long num){
    string newstr = "";
    string answ = "";
    if(num == 0) return "0";
    while(num > 0){
        newstr += num % 10 + 48;
        num /= 10;
    }
    for(long long i = itc_len(newstr) - 1; i >=0; i--){
        answ += newstr[i];
    }
    return answ;
}

string itc_slice_str(string str, int start, int last){
    string newstr = "";
    if(last > itc_len(str)) last = itc_len(str) - 1;
    for(int i = start; i <= last; i++) newstr += str[i];
    return newstr;
}

long long itc_abs(long long num){
    if(num >= 0){
        return num;
    }
    else{
        return num * -1;
    }
}

double itc_pow (long long n, long long i){
    long long num = n;
    if (i == 0){
        n = 1;
        return n;
    }
    else{
        for (long long pow = 1; pow < itc_abs(i); pow++){
            n = n * num;
        }
        if(i > 0) return n;
        return 1.00 / n;
    }
}

unsigned long long itc_bin_num(unsigned long long number){
    long long binnum = 0;
    long long kol = 0;
    while(number > 0){
        binnum += number % 2 * itc_pow(10, kol);
        number /= 2;

        kol++;
    }
    return binnum;
}

string itc_DecToBin(string str){
    string newstr = "";
    string numstr = "";
    long long num = 0;
    for(long long i = 0; str[i] != '\0'; i++){
        if(str[i] >= '0' && str[i] <= '9'){
            while(str[i] >= '0' && str[i] <= '9'){
                numstr += str[i];
                i++;
            }
            for(long long j = 0; numstr[j] != '\0'; j++){
                num += numstr[j] - 48;
                num *= 10;
            }
            num /= 10;
            num = itc_bin_num(num);
            newstr += itc_toString(num);
            num = 0;
            numstr = "";
        }
        if(i < itc_len(str))
        newstr += str[i];
    }
    return newstr;
}

string itc_decToBase(unsigned long long num, unsigned long long base){
    string newstr = "";
    string answer = "";
    while(num > 0){
        if(num % base >= 10){
             newstr += (num % base) % 10 + 65;
        }
        else newstr += (num % base) + 48;
        num /= base;
    }
    for(long long i = itc_len(newstr) - 1; i >= 0; i--){
        answer += newstr[i];
    }
    return answer;
}

string itc_removeSpace(string str){
    string newstr = "";
    for(unsigned long long i = 0; i < itc_len(str); i++){
        if(str[i] != ' ') newstr += str[i];
    }
    return newstr;
}

string itc_toUpper(string str){
    for(long long i = 0; i < itc_len(str); i++){
        if(str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
    }
    return str;
}

int main()
{
    string fnum = "-inf";//вводимое число
    string buffstr = "";//дробная часть
    string newstr = "";//целая часть
    string sdvigstr;//порядок строкой
    unsigned long long buffer;//буфер
    unsigned long long digitSum = 0;//сумма цифр
    long long sdvig;//порядок
    bool flag = false;//флаг
    fnum = itc_removeSpace(fnum);
    //cin >> fnum;

    cout << itc_toUpper(fnum) << endl;


    //////////////////////////ТОЧКА НАЧАЛА ПРОГРАММЫ//////////////////////////////////
    for(unsigned long long i = 0; i < itc_len(fnum); i++){ //проверяем, если в числе все нули
        if(fnum[i] != '0' && fnum[i] > '0' && fnum[i] <= '9') {
            flag = true;
            i = itc_len(fnum);
        }
    }
    //проверка на бесконечность
    if(itc_toUpper(fnum) == "+INF" || itc_toUpper(fnum) == "INF" || itc_toUpper(fnum) == "+INFINITY" || itc_toUpper(fnum) == "INFINITY")
        cout << "01111111100000000000000000000000";
    else if(itc_toUpper(fnum) == "-INFINITY" || itc_toUpper(fnum) == "-INF")
        cout << "11111111000000000000000000000000";
    else if(fnum == "NaN" || fnum == "nan" || fnum == "NAN") cout << "01111111111111111111111111111111";
    else if(fnum == "-NaN" || fnum == "-nan" || fnum == "-NAN") cout << "11111111111111111111111111111111";
    else if(!flag){ //проверка на ноль
        if(fnum[0] == '-') cout << "10000000000000000000000000000000";
        else cout << "00000000000000000000000000000000";
    }
    else{
    //если нет точки, то искуственно добавляем её 1 = 1.0
    flag = false;
    for(unsigned long long i = 0; i < itc_len(fnum); i++){
        if(fnum[i] == '.'){
            flag = true;
            i = itc_len(fnum);
        }
    }

    if(!flag){
            fnum += ".0";
    }
    ///////////////////////////////////////////////////////

    //выделение целой части
    for(unsigned long long i = 0; fnum[i] != '.' && i < itc_len(fnum); i++){
        if (i == 0 && fnum[0] == '-') i++;
        buffstr += fnum[i];
        buffer = i;
        digitSum++;
    }
    //перевод целой части
    newstr = itc_decToBase(itc_toInt(buffstr), 2);
    buffer += 2;
    buffstr = "";
    sdvig = itc_len(newstr) - 1;
    //////////////////////////////////////////////////////////////////

    //выделение дробной части
    for(unsigned long long i = buffer; i < itc_len(fnum) && i < 19; i++){
        buffstr += fnum[i];
        digitSum++;
    }
    cout << buffstr << endl;
    //убираем нули сзади дробной части
    for(long long i = itc_len(buffstr) - 1; i >= 0; i--){
        if(buffstr[i] != '0'){
            buffstr = itc_slice_str(buffstr, 0, i);
            i = 0;
            digitSum--;
        }
        else if(i == 0) { buffstr = itc_slice_str(buffstr, 0, 0); digitSum = 2; }
        else { buffstr = itc_slice_str(buffstr, 0, i); digitSum--; }
    }
    buffer = itc_toInt(buffstr);
    string test = "";

    //перевод дробной части
    for(unsigned long long i = 0; i < 100; i++){
        buffer *= 2;
        if(itc_len(itc_toString(buffer)) > itc_len(buffstr)){
            newstr += "1";
            cout << buffer << endl;
            test += "1";
            buffer = itc_toInt(itc_slice_str(itc_toString(buffer), 1, itc_len(buffstr)));
            cout << buffer;
            cout << "    " << test << endl;
        }
        else{
            newstr += "0";
            test += "0";
            cout << buffer;
            cout << "    " << test << endl;
        }
    }

    buffstr = "";
    /////////////////////////////////////////////////////////////////////////////////////////
    flag = false;
    cout << endl;
        //счёт сдвига точки
    if(newstr[0] == '0'){
        buffer = 0;
        sdvig = -1;
        for(long long i = 1; newstr[i] != 1 && i < itc_len(newstr); i++) {
            buffer = i;
            sdvig--;
            if(newstr[i] == '1') {
                flag = true;
                i = itc_len(newstr);
            }
            cout << newstr[i];
        }
        cout << "                                               bebra" << endl;
        if(!flag) sdvig = 0;
        else newstr = itc_slice_str(newstr, buffer, itc_len(newstr));
    }
    cout << "sdviiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiig       " << sdvig << endl;
    sdvig += 127;
    cout << sdvig << "            sdsjadpoqjdopqjwdpoqjpwdjqpowjdq"<<endl;
    sdvigstr = itc_DecToBin(itc_toString(sdvig));




    //знак
    if(fnum[0] == '-') buffstr += "1";
    else buffstr += "0";


    cout << buffstr << endl;
    //порядок
    for(long long i = 0; i < 8 - itc_len(sdvigstr) ; i++){
        buffstr += "0";
    }

    buffstr += sdvigstr;
    cout << buffstr << endl;
    //мантисса
    for(long long i = 0; i < itc_len(newstr) && itc_len(buffstr) < 32; i++){
        if(i == 0 && newstr[i] == '1' && itc_len(newstr ) > 1) i++;
        if(i == 0 && fnum[0] == '-') i++;
        buffstr += newstr[i];
    }
    while(itc_len(buffstr) < 32){
        buffstr += "0";
    }
    cout << newstr << endl;
    cout << buffstr;
    }
}
