/* 

SCANNER DE PROCESSOS, ESTO USANDO  PARA  COLETAR DADOS DOS  PROCESSO DO FF VIA TERMUX, SO RECOMENDO SE 
ESTIVER USANDO UM TABLET OU CELULAR COMPATIVEL  COM JANELA  FLUTUANTE, ESTE SCRIPT E APENAS PARA DESENVOLVEDORES
VEREM MELHOR OS PROCESSO

*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<dirent.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<thread>
#include<chrono>
#include<algorithm>

using namespace std;

struct Proc {
 int pid;
 string nome, estado, user;
};

string get_estado(const string& pid) {
 ifstream f("/proc/" + pid + "/status");
 string linha;
 while (getline(f, linha)) {
  if (linha.find("State:") == 0)
   return linha.substr(linha.find_first_not_of(" \t", 6));
 }
 return "?";
}

string get_nome(const string& pid) {
 ifstream f("/proc/" + pid + "/cmdline");
 string cmd;
 getline(f, cmd);
 return cmd.empty() ? "[init]" : cmd;
}

string get_user(const string& pid) {
 ifstream f("/proc/" + pid + "/status");
 string linha;
 while (getline(f, linha)) {
  if (linha.find("Uid:") == 0) {
   istringstream ss(linha);
   string tag;
   int uid;
   ss >> tag >> uid;
   passwd* pw = getpwuid(uid);
   return pw ? pw->pw_name : to_string(uid);
  }
 }
 return "?";
}

vector<Proc> scan() {
 vector<Proc> ps;
 DIR* d = opendir("/proc");
 if (!d) return ps;
 dirent* e;
 while ((e = readdir(d)) != NULL) {
  string pid = e->d_name;
  if (all_of(pid.begin(), pid.end(), ::isdigit)) {
   ps.push_back({
    stoi(pid),
    get_nome(pid),
    get_estado(pid),
    get_user(pid)
   });
  }
 }
 closedir(d);
 return ps;
}

void limpar() {
 cout << "\033[2J\033[1;1H";
}

void printar(const vector<Proc>& lista) {
 cout << "\033[1;32mPID\t\033[1;34mUSER\t\t\033[1;35mESTADO\t\t\033[1;36mNOME\n";
 cout << "\033[0m===============================================================\n";
 for (auto& p : lista) {
  cout << "\033[1;32m" << p.pid << "\t";
  cout << "\033[1;34m" << p.user << "\t\t";
  cout << "\033[1;35m" << p.estado << "\t";
  cout << "\033[1;36m" << p.nome << "\n";
 }
 cout << "\033[0m";
}

int main() {
 while (true) {
  limpar();
  auto procs = scan();
  sort(procs.begin(), procs.end(), [](auto& a, auto& b) {
   return a.pid < b.pid;
  });
  printar(procs);
  this_thread::sleep_for(chrono::milliseconds(800));
 }
}
