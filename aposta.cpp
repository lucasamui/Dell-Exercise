#include "aposta.h"

using namespace std;

bool validarCPF(string cpf) {  // bool validar  cpf
  if (cpf.size() != 11)
    return false;

  int soma = 0, resto;
  for (int i = 0; i < 9; i++)
    soma += (cpf[i] - '0') * (10 - i);
  resto = soma % 11;
  if (resto < 2)
    resto = 0;
  else
    resto = 11 - resto;
  if (resto != (cpf[9] - '0'))
    return false;

  soma = 0;
  for (int i = 0; i < 10; i++)
    soma += (cpf[i] - '0') * (11 - i);
  resto = soma % 11;
  if (resto < 2)
    resto = 0;
  else
    resto = 11 - resto;
  if (resto != (cpf[10] - '0'))
    return false;

  return true;
}

void Aposta::iniciarNovaEdicao(){
  apostas.clear();
  numerosSorteados.clear();
  rodadasDeSorteio = 0;
  proximoId = 1000;
  cout << "Todas as apostas foram reiniciadas." << "\n";
}

void Aposta::registrarNovaAposta(){
  string nome, cpf;
  vector<int> numeros;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "REGISTRAR NOVA APOSTA\n";
  cout << endl << "Nome: ";
  getline(cin, nome);

  cout << "Digite seu CPF: "; 
  getline(cin, cpf);
  
  if (!validarCPF(cpf)) {
    cout << "CPF inválido. Tente novamente." << endl;
    return;
  }

  cout << "Digite 5 números (entre 1 e 50) separados por espaços ou digite 'Surpresinha' para gerar automaticamente: ";
  
  string entrada;
  getline(cin, entrada); 

  if (entrada == "Surpresinha") {  // função surpresinha 
    random_device seed;
    mt19937 seedUse(seed()); 
    uniform_int_distribution<> intervalo(1, 50); 

    while (numeros.size() < 5) {
      int numeroAleatorio = intervalo(seedUse);
      if (find(numeros.begin(), numeros.end(), numeroAleatorio) == numeros.end()) {
        numeros.push_back(numeroAleatorio); // adiciona se não for duplicado
      }
    }
  } else {
    stringstream ss(entrada); //string para stream
    int num;
    while (ss >> num) {
      numeros.push_back(num);
      if (ss.peek() == ' ') ss.ignore();
    }
  }

  if (!verificaApostaValida(numeros)) {
    cout << "Aposta inválida! Certifique-se de que você digitou corretamente." << endl;
    return;
  }

  apostas.push_back(Apostador(nome, cpf, numeros, proximoId++));
  cout << "Aposta registrada com sucesso." << endl;
}

bool Aposta::verificaApostaValida(vector<int>& numeros) {
    if (numeros.size() != 5)
        return false;

    sort(numeros.begin(), numeros.end());
    for (size_t i = 0; i < numeros.size() - 1; ++i) {
      if (numeros[i] < 1 || numeros[i] > 50 || numeros[i] == numeros[i + 1])
        return false;
    }
    if (numeros.back() < 1 || numeros.back() > 50)
        return false;

    return true;
}

void Aposta::listarApostas() {
    cout << "Lista de apostas registradas:" << endl << endl;
    for (const auto& aposta : apostas) {
        cout << "id: #" << aposta.getId() << ", Nome: " << aposta.getNome() << ", CPF: " << aposta.getCPF() << ", Números: ";
        for (const auto& numero : aposta.getNumeros())
            cout << numero << " ";
            cout << endl;
    }
}

void Aposta::finalizarApostasExecutarSorteio() {
    char confirmacao;
    cout << "Deseja finalizar as apostas e executar o sorteio? (s/n): ";
    cin >> confirmacao;

    if (confirmacao == 's' || confirmacao == 'S') {
        realizarSorteio();
        apurarVencedores();
        fimDaApuracao();
    }
}

void Aposta::realizarSorteio() {

    vector<int> todosNumeros; // lista numeros 1 a 50
    for (int i = 1; i <= 50; ++i) {
        todosNumeros.push_back(i);
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // embaralha numeros
    shuffle(todosNumeros.begin(), todosNumeros.end(), default_random_engine(seed));

    for (int i = 0; i < 5; ++i) {  // seleciona os 5 primeiros numeros
      numerosSorteados.push_back(todosNumeros[i]);
    }

    numerosSorteadosPorRodada.push_back(numerosSorteados); 
}


bool Aposta::verificaApostasVencedoras(const vector<int>& numerosSorteados, const Apostador& aposta) {
    int acertos = 0;
    for (const auto& numero : aposta.getNumeros()) {
        if (find(numerosSorteados.begin(), numerosSorteados.end(), numero) != numerosSorteados.end())
            ++acertos;
    }
    return acertos == 5;
}

void Aposta::apurarVencedores() {
    vector<Apostador> vencedores;
    ++rodadasDeSorteio; 

    for (const auto& aposta : apostas) {
        if (verificaApostasVencedoras(numerosSorteados, aposta))
            vencedores.push_back(aposta);
    }

    if (vencedores.empty()) {
        if (rodadasDeSorteio < 25) {
            cout << "Nenhuma aposta vencedora encontrada. Realizando mais uma rodada de sorteio." << endl;
            realizarSorteio();
            apurarVencedores();
        } else {
            cout << "Nenhuma aposta vencedora encontrada após 25 rodadas de sorteio." << endl;
        }
    } else {
        cout << "Apostas vencedoras:" << endl;
        for (const auto& vencedor : vencedores) {
           cout << "Id: #" << vencedor.getId() << ", Nome: " << vencedor.getNome() << ", CPF: " << vencedor.getCPF() << endl;
        }
    }
}

void Aposta::fimDaApuracao() {
    cout << "Numeros sorteados: ";
    for (int i = 0; i < rodadasDeSorteio; ++i) {
        cout << "Rodada " << (i + 1) << ": ";
        for (int j = 0; j < 5; ++j) {
            cout << numerosSorteados[i * 5 + j] << " ";  
        }
        cout << endl;
    }
    cout << "Rodadas de sorteio realizadas: " << rodadasDeSorteio << endl;
}

void Aposta::menuInterface(){
  cout << "\nMENU:" << endl;
  cout << "1. Reiniciar" << endl;
  cout << "2. Registrar Nova Aposta" << endl;
  cout << "3. Listar Apostas" << endl;
  cout << "4. Finalizar Apostas e Executar o Sorteio" << endl;
  cout << "5. Encerrar programa" << endl;
  cout << "Escolha uma opção: ";
}
