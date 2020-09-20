// INIParser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <typeinfo>
#include <unordered_map>
using namespace std;

class INISection {

private:
    unordered_map<string, string> params;
public:
    string name;
    INISection(string name) : name(name) {
        cmatch result;// name = param
    }
    void addParam(string name, string value) {
        params[name] = value;
    }
    int getIntParam(string name){return atoi(params[name].c_str());}
    float getFloatParam(string name){return stof(params[name].c_str());}
    string getStringParam(string name){return params[name];}
    /*
     *
     * Попробовал сделать через шаблоны - не вышло, вопрос - как сделать через них?
    template<typename T>
    T getParam(string name){}

    template<>
    string getParam(string name){return params[name];}

    template<>
    int getParam(string name){return atoi(params[name].c_str());}

    template<>
    double getParam(string name){return stof(params[name].c_str());}

*/



};


class INIFile {
private:
    string location;
    ifstream ifile;
    vector<INISection> sections;
    //unordered_map<string, INISection> sections;
    void openFile() {
        ifile = ifstream(location);
    }
    void getParams() {
        string line;
        cmatch result;// [name]
        regex regular("([\[])"
                      "([\\w]+)(])");

        regex regular_param("([\\w]+)"
                            "(\x20=\x20)"
                            "([\\w.]+)"//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Исправить, чтобы считывал все до ;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                           //"([;]?[\\w]+)"
        );

        while (getline(ifile, line)) {
            string section_name;
            if (regex_match(line.c_str(), result, regular)) {
                section_name = result[2];
                INISection new_section = INISection(result[2]);
                while ((getline(ifile, line)) && (regex_search(line.c_str(), result, regular_param))) {
                    new_section.addParam(result[1], result[3]);
                }
                sections.push_back(new_section);
            }


        }
    }



public:
    INIFile(string location) : location(location){
        openFile();
        getParams();
    }
    int getIntParam(string parameter_name, string section_name){
        for(vector<INISection>::iterator iter = sections.begin(); iter != sections.end(); iter++){

            if(iter->name == section_name) return (*iter).getIntParam(parameter_name);
        }
        cout << "No mathes\n";
        throw("No mathes");
    }
    float getFloatParam(string parameter_name, string section_name){
        for(vector<INISection>::iterator iter = sections.begin(); iter != sections.end(); iter++){
            if(iter->name == section_name) return iter->getFloatParam(parameter_name);
        }
        cout << "No mathes\n";
        throw("No mathes");
    }
    string getStringParam(string parameter_name, string section_name){
        for(vector<INISection>::iterator iter = sections.begin(); iter != sections.end(); iter++){
            if(iter->name == section_name) return iter->getStringParam(parameter_name);
        }
        cout << "No mathes\n";
        throw("No mathes");
    }
    /*
    template <typename T>
    T getParam(string parameter_name, string section_name){
        return sections[section_name].getParam<T>(parameter_name);

    }*/


};





int  main(int argc, char* argv[])
{//Переделать специализацией
    string command;
    cin >> command;
    while(command != "exit"){

        if(command == "open"){
            cout << "Opening file, write path: ";
            string path;
            cin >> path;
            cout << "Filed opened, please select command: get, exit";
            INIFile cl = INIFile(path);
            cin >> command;
            while(command == "get"){
                cout << "Getting parameter from file, please write [section, name of parameter, type of parameter]: ";
                string section, name, type_;
                cin >> section >> name >> type_;
                if ("string" == type_) {
                    cout << cl.getStringParam(name, section) << endl;
                }
                if ("int" == type_) {
                    cout << cl.getIntParam(name, section) << endl;
                }
                if ("float" == type_) {
                    cout << cl.getFloatParam(name, section) << endl;
                }
                cout << "Write command(get, open, exit): ";
                cin >> command;
                if(command == "exit") return 0;
            }
            cout << "Write command(get, open, exit): ";
        }
        cin >> command;


    }

   // cout << "Parameter: "
   // cout << "Parameter: " << cl.getFloatParam("sgh", "Hello") <<endl;
   // cout << "Parameter: " << cl.getStringParam("sgh", "Hello") <<endl;
}

