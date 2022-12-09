#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
string buatkatayangbaru (string katayanglama)
{
    string katayangbaru = "";
    int sizekatalama = katayanglama.length(); 
    for (int i = 0; i < sizekatalama; i++)
    {
        char masinghuruf = katayanglama[i];
        int decimalmasinghuruf = int(masinghuruf);
        
        if (decimalmasinghuruf >= 65 and decimalmasinghuruf <= 90)
            katayangbaru += (char(decimalmasinghuruf + 32));
        else if (decimalmasinghuruf >= 97 and decimalmasinghuruf <= 122 or decimalmasinghuruf >= 48 and decimalmasinghuruf <= 57)
            katayangbaru += masinghuruf;
    }
    return katayangbaru;
}

int main()
{
    vector <string> masingkata;
    ifstream fileinput;
    fileinput.open("input.txt");

    if (!fileinput.is_open())
    {
        cout << " tidak dalam satu file ini" << endl;
        return 0;
    }

    while (!fileinput.eof())
    {
        string katadariinput;
        fileinput >> katadariinput;
        katadariinput = buatkatayangbaru(katadariinput);
        if (katadariinput.length() != 0)
            masingkata.push_back(katadariinput);
    }
    fileinput.close();

    
    string tojson = "";
    tojson += "{\n";
    cout << "kata\t\t\t" << "jumlah\t" << "histogram" << endl;
    for (auto i = masingkata.begin(); i != masingkata.end(); i++)
    {
        vector <string>::iterator it = find(masingkata.begin(), masingkata.end(), *i);
        if (it-masingkata.begin() == i-masingkata.begin())
        {
            int jumlahberulang = count(masingkata.begin(), masingkata.end(), *i);
            cout << *i << ((*i).length() > 7 ? "\t\t":"\t\t\t") << jumlahberulang << "\t";
            for (int j = 0; j < jumlahberulang; j++)
                cout << "#";
            cout << endl;
            tojson += "\t\"";
            tojson += *i;
            tojson += "\": ";
            tojson += to_string(jumlahberulang);
            tojson += ",\n";
        }
    }
    tojson.erase(tojson.length()-2, 1);
    tojson += "}";
    ofstream filejson;
    filejson.open("output.json");
    filejson << tojson;
    filejson.close();

    return 0;
}