#include "percolator/percolator.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// OJO con la semántica nueva:
//  - las búsquedas cortan en la PRIMERA celda de la última fila que sacan de
//    la pila/cola, así que ya no recorren todo el componente. No se puede
//    afirmar "tal celda quedó visitada"; lo que sí es determinista es el
//    índice de salida que devuelven y el camino que reconstruye findPath.
//  - si (0,0) no conecta con la última fila, la búsqueda truena en su
//    assert(false). Todo test que corra DFS/BFS tiene que abrir un camino
//    real hasta abajo.
//  - (0,0) ya no se abre sola: hay que abrirla a mano.

// Columna recta 0 -> 3 -> 6. El caso mínimo.
static void dfsReachesBottom() {
  int n{3};
  percolator p(n);
  p.openGate(0, 0);
  p.openGate(1, 0);
  p.openGate(2, 0);

  int exit{p.runDfsFromInjection()};
  assert(exit == 6);
  assert(exit / n == n - 1); // salió por la última fila

  std::vector<int> path = p.findPath(exit / n, exit % n);
  std::vector<int> expected{6, 3, 0}; // destino -> ... -> origen
  assert(path == expected);

  std::cout << "dfsReachesBottom ok\n";
}

// Camino que dobla: (0,0) -> (0,1) -> (1,1) -> (2,1), con (1,0) cerrada
// para forzar el quiebre. Valida que los parents se encadenen bien.
static void dfsPathBends() {
  int n{3};
  percolator p(n);
  p.openGate(0, 0);
  p.openGate(0, 1);
  p.openGate(1, 1);
  p.openGate(2, 1);

  int exit{p.runDfsFromInjection()};
  assert(exit == 7);

  std::vector<int> path = p.findPath(exit / n, exit % n);
  std::vector<int> expected{7, 4, 1, 0};
  assert(path == expected);

  std::cout << "dfsPathBends ok\n";
}

// Grid lleno 3x3: hay muchas rutas hasta abajo y las dos búsquedas eligen
// distinto. BFS debe dar la corta (3 celdas); DFS se va por la orilla
// derecha y devuelve 5. Este es el único test que distingue un algoritmo
// del otro.
static void bfsIsShorterThanDfs() {
  int n{3};
  percolator p(n);
  for (int i{0}; i < n * n; i++) {
    p.openGate(i / n, i % n);
  }

  int dfsExit{p.runDfsFromInjection()};
  std::vector<int> dfsPath = p.findPath(dfsExit / n, dfsExit % n);
  std::vector<int> expectedDfs{8, 5, 2, 1, 0};
  assert(dfsExit == 8);
  assert(dfsPath == expectedDfs);

  int bfsExit{p.runBfsFromInjection()};
  std::vector<int> bfsPath = p.findPath(bfsExit / n, bfsExit % n);
  std::vector<int> expectedBfs{6, 3, 0};
  assert(bfsExit == 6);
  assert(bfsPath == expectedBfs);

  assert(bfsPath.size() < dfsPath.size());

  std::cout << "path dfs: ";
  for (int idx : dfsPath) {
    std::cout << idx << " ";
  }
  std::cout << "\npath bfs: ";
  for (int idx : bfsPath) {
    std::cout << idx << " ";
  }
  std::cout << "\nbfsIsShorterThanDfs ok\n";
}

// gateStatus es monótono (no hay closeGate), así que esto no prueba que
// visited se "reduzca". Prueba que la 2a corrida re-explora desde cero: al
// abrir la columna 1 la ruta cambia, y el índice de salida tiene que cambiar
// con ella. Si resetVisited no corriera, seguiría devolviendo 6.
static void growsBetweenRuns() {
  int n{3};
  percolator p(n);
  p.openGate(0, 0);
  p.openGate(1, 0);
  p.openGate(2, 0);

  int firstExit{p.runDfsFromInjection()};
  assert(firstExit == 6);

  p.openGate(0, 1);
  p.openGate(1, 1);
  p.openGate(2, 1);

  int secondExit{p.runDfsFromInjection()};
  assert(secondExit == 7); // la columna nueva se explora primero ahora

  std::vector<int> path = p.findPath(secondExit / n, secondExit % n);
  std::vector<int> expected{7, 4, 1, 0};
  assert(path == expected);

  std::cout << "growsBetweenRuns ok\n";
}

// injectionReaches() es el guardia que protege a las búsquedas de su propio
// assert(false). Acá se verifica que diga la verdad en los dos sentidos.
// En el caso negativo NO se corre DFS a propósito: tronaría, y con razón.
static void injectionReachesGuardsTheSearch() {
  int n{3};

  percolator noRoute(n);
  noRoute.openGate(0, 0);
  noRoute.openGate(0, 2); // columna percolante que nunca toca a (0,0)
  noRoute.openGate(1, 2);
  noRoute.openGate(2, 2);
  assert(noRoute.percolates() == true); // percola...
  assert(noRoute.injectionReaches() == false); // ...pero no desde la inyección

  percolator withRoute(n);
  withRoute.openGate(0, 0);
  withRoute.openGate(1, 0);
  withRoute.openGate(2, 0);
  assert(withRoute.injectionReaches() == true);

  std::cout << "injectionReachesGuardsTheSearch ok\n";
}

// Celda abierta pero jamás alcanzada. findPath debe abortar en su assert de
// isVisited, no regresar un camino inventado. El DFS previo sí llega abajo,
// así que el que truena es findPath, no la búsqueda.
static void unvisitedPathAborts() {
  int n{3};
  percolator p(n);
  p.openGate(0, 0);
  p.openGate(1, 0);
  p.openGate(2, 0);
  p.openGate(0, 2); // aislada

  int exit{p.runDfsFromInjection()};
  assert(exit == 6);

  std::cout << "pidiendo camino de celda no visitada...\n" << std::flush;
  p.findPath(0, 2); // debe tronar aquí
  std::cout << "esto no deberia imprimirse\n";
}

// El punto real de la conversión a std::stack: esto reventaba el stack en
// ~362-363 con la versión recursiva. En heap no debe tronar.
static void deep(int n) {
  percolator p(n);
  for (int i{0}; i < n * n; i++) {
    p.openGate(i / n, i % n); // grid lleno -> peor caso de profundidad
  }
  std::cout << "deep n=" << n << " (" << (n * n) << " celdas), lanzando DFS\n"
            << std::flush;

  int exit{p.runDfsFromInjection()};
  assert(exit / n == n - 1);

  std::vector<int> path = p.findPath(exit / n, exit % n);
  assert(path.front() == exit);
  assert(path.back() == 0); // se encadenó hasta la inyección

  std::cout << "deep sobrevivio (camino de " << path.size() << " celdas)\n";
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    dfsReachesBottom();
    dfsPathBends();
    bfsIsShorterThanDfs();
    growsBetweenRuns();
    injectionReachesGuardsTheSearch();
    return 0;
  }
  if (argc == 3 && std::string(argv[1]) == "deep") {
    deep(std::atoi(argv[2]));
    return 0;
  }
  if (argc == 2 && std::string(argv[1]) == "badpath") {
    unvisitedPathAborts();
    return 0;
  }
  std::cout << "uso: ./test            (dfs + bfs + reset + findPath)\n"
            << "     ./test deep N     (grid lleno, prueba de profundidad)\n"
            << "     ./test badpath    (findPath en celda no visitada, debe "
               "tronar)\n";
  return 1;
}
