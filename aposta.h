#include "apostador.h"

using namespace std;

class Aposta{
private:
  vector<Apostador> apostas;
  vector<int> numerosSorteados;
  vector<std::vector<int>> numerosSorteadosPorRodada;
  int rodadasDeSorteio = 0;
  int proximoId = 1000;

  bool verificaApostaValida(std::vector<int>& numeros);
  bool verificaApostasVencedoras(const std::vector<int>& numerosSorteados, const Apostador& aposta);
  void realizarSorteio();
  void apurarVencedores();
  void exibirNumerosApostados();

public:
  void iniciarNovaEdicao();
  void registrarNovaAposta();
  void listarApostas();
  void finalizarApostasExecutarSorteio();
  void fimDaApuracao();
  void menuInterface();
};
