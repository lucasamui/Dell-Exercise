#include "aposta.h"

using namespace std;

int main(){
  Aposta aposta;
  int escolha;

  bool continuar = true;
  
  while (continuar) {
    aposta.menuInterface();
    cin >> escolha;

    switch (escolha) {

      case 1:
        aposta.iniciarNovaEdicao();
        break;
      case 2:
        aposta.registrarNovaAposta();
        break;
      case 3:
        aposta.listarApostas();
        break;
      case 4:
        aposta.finalizarApostasExecutarSorteio();
        break;
      case 5:
        continuar = false;
        break;
      default:
        cout << "Opção inválida. Tente novamente." << endl;
    }
  }
  return 0;
}
