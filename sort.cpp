#include<iostream>
#include<algorithm>
#include<stdexcept>
#include"Vec.h"
#include"Str.h"
using std::sort;
using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::string;
using std::domain_error;
using std::istream;
struct wordtime {
    Str word;
    int time = 0;
};
Vec<struct wordtime> wt;
Vec<Str>::size_type count(Vec<Str>& sen)
{
    typedef Vec<Str>::size_type senlen;
    senlen len = sen.size();
    if (len == 0)
        throw domain_error("No words entered.Please try again!");
    return len;
}
int cal(Vec<Str>& sen)
{
    int i = 0;
    int cnt = 0;
    while (i < sen.size())
    {
        bool flag = 0;
        for (int j = 0; j < cnt; j++)
        {
            if (strcompare(sen[i], wt[j].word))
            {
                wt[j].time++;
                flag = 1;
            }
        }
        if (!flag)
        {
            struct wordtime temp;
            temp.time = 1;
            temp.word = sen[i];
            wt.push_back(temp);
            cnt++;
        }
        i++;
    }
    return cnt;
}
istream& read_sen(istream& in, Vec<Str>& sen)
{
    if (in)
    {
        sen.clear();
        Str word;
        while (in >> word)
        {
            sen.push_back(word);
            in.clear();
            word.clear();
        }
        return in;
    }
}
bool cmp(const wordtime& a, const wordtime& b)
{
    return a.word < b.word;
}
void output(int cnt)
{
    int maxx = 0;
    for (int i = 0; i < cnt; i++)
    {
        maxx = (maxx > wt[i].word.size() ? maxx : wt[i].word.size());
    }
    for (int i = 0; i < cnt; i++)
    {
        cout << wt[i].word << Str(maxx + 1 - wt[i].word.size(), ' ') << wt[i].time << endl;
    }
}
int main()
{
    Vec<Str> sentence;
    cout << "Enter some text:";
    read_sen(cin, sentence);
    try {
        int cnt = cal(sentence);
        sort(wt.begin(), wt.end(),cmp);
        output(cnt);
    }
    catch (domain_error e) {
        cout << e.what();
        return 1;
    }
    return 0;
}