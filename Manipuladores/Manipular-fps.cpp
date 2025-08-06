#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
namespace fs=std::filesystem;

// pasta do free fire, se mudar o jogo troca aqui
std::string DIR_FF="/data/data/com.termux/files/home/storage/shared/Android/data/com.freefireth/files";

// função que troca um valor por outro dentro do texto do arquivo
void troca(std::string &c,std::string de,std::string pa,bool &m){
size_t p=0; // posição no texto
while((p=c.find(de,p))!=std::string::npos){
c.replace(p,de.length(),pa); // troca a parada
p+=pa.length();
m=true; // marcou que mudou
}
}

int main(){
std::cout<<"fps booster modo porco on\n";
while(1){ // loop infinito pq sim
for(auto &e:fs::recursive_directory_iterator(DIR_FF)) // varre tudo
if(fs::is_regular_file(e)){ // se for arquivo normal
std::ifstream in(e.path(),std::ios::binary);if(!in)continue; // tenta abrir, se falhar ignora
std::string txt((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());in.close(); // le o arquivo todo na memoria
bool m=false; // flag de modificação
troca(txt,"30","60",m); // 30 vira 60
troca(txt,"60","90",m); // 60 vira 90
troca(txt,"90","120",m); // 90 vira 120
if(m){ // se mudou alguma coisa
std::ofstream out(e.path(),std::ios::binary|std::ios::trunc); // abre pra sobrescrever
out.write(txt.data(),txt.size()); // grava o novo conteudo
out.close();
std::cout<<"alterado: "<<e.path()<<"\n"; // fala qual arquivo mexeu
}
}
std::this_thread::sleep_for(std::chrono::seconds(3)); // espera 3s e repete
}
}
