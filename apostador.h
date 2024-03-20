#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <chrono>
#include <random>
#include <string>
#include <sstream>

using namespace std;

class Apostador{
private:
string nome;
string cpf;
vector<int> numeros;
int id;

public:
  Apostador(string _nome, string _cpf, vector<int> _numeros, int _id);

  string getNome() const { return nome; }
  string getCPF() const { return cpf; }
  vector<int> getNumeros() const { return numeros; }
  int getId() const { return id; }
};
