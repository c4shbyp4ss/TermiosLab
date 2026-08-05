# TermiosLab
Uma coleção de pequenos exercícios em C focados em **`termios.h` e controle de terminal (raw mode)**.  
Cada exercício isola um conceito específico da biblioteca, tornando este repositório uma referência pessoal para aprender e revisitar programação de terminal em C — e uma base direta para os projetos interativos do [GridForge](#).

---

## Exercícios

| # | Nome | Descrição | Status |
|---|------|-----------|--------|
| 01 | [RawKeys](#01-rawkeys) | Leitor de teclas básico, sem esperar Enter | ✅ Concluído |
| 02 | [SilentInput](#02-silentinput) | Leitura de teclas sem eco na tela | ✅ Concluído |
| 03 | [SafeExit](#03-safeexit) | Restauração garantida do terminal original | 🔲 Pendente |
| 04 | [ArrowSense](#04-arrowsense) | Detecção de setas do teclado | 🔲 Pendente |
| 05 | [PulseCounter](#05-pulsecounter) | Loop não-bloqueante com contador em tempo real | 🔲 Pendente |
| 06 | [TimeoutWait](#06-timeoutwait) | Leitura com tempo limite (`VTIME`) | 🔲 Pendente |
| 07 | [EchoEditor](#07-echoeditor) | Mini editor de um caractere com Backspace manual | 🔲 Pendente |
| 08 | [EchoToggle](#08-echotoggle) | Ligar/desligar eco em tempo real, sem sair do modo raw | 🔲 Pendente |
| 09 | [TermCore](#09-termcore) | Módulo de terminal reutilizável (`terminal.h`/`terminal.c`) | 🔲 Pendente |
| 10 | [GridLoop](#10-gridloop) | Protótipo de loop de jogo/visualizador para o GridForge | 🔲 Pendente |

---

## 01. RawKeys
> ✅ Concluído

Ativa o modo raw do terminal e imprime o código ASCII de cada tecla pressionada, sem esperar pelo Enter. Encerra ao receber a tecla `q`.

**Conceitos praticados:** `tcgetattr`/`tcsetattr`, desligar `ICANON`, `read()` byte a byte, restauração da configuração original ao final.

```
Iniciando exibidor de teclas...
 [ Bem-Vindo ao RawKeys ]

Cod.Tecla: 97
Cod.Tecla: 66
Cod.Tecla: 10
Cod.Tecla: 113

Obrigado por utilizar o RawKeys!!
```

---

## 02. SilentInput
> ✅ Concluído

Mesma base do RawKeys, mas com o eco do terminal desligado — as teclas digitadas não aparecem sozinhas na tela, apenas a mensagem impressa pelo próprio programa.

**Conceitos praticados:** flag `ECHO`, separação entre o que o *terminal* mostra e o que o *programa* recebe.

```
Recebi a tecla, codigo: 97
Recebi a tecla, codigo: 66
```

---

## 03. SafeExit
> 🔲 Pendente

Garante que o terminal volta ao estado original em três cenários: saída normal do `main()`, saída forçada via `exit(1)` no meio do código, e (opcional) captura de `SIGINT` (Ctrl+C).

**Conceitos praticados:** `atexit()`, `signal()`, salvar a `struct termios` original antes de qualquer modificação, verificação com `stty -a`.

```
Modo raw ativo.
^C
Terminal restaurado antes de encerrar.
```

---

## 04. ArrowSense
> 🔲 Pendente

Detecta as sequências de escape geradas pelas setas do teclado (`ESC` + `[` + `A`/`B`/`C`/`D`) e imprime qual direção foi pressionada.

**Conceitos praticados:** sequências de escape ANSI, leitura de múltiplos bytes em sequência, diferenciação entre tecla `ESC` isolada e início de sequência.

```
Seta para cima
Seta para direita
Seta para baixo
```

---

## 05. PulseCounter
> 🔲 Pendente

Loop não-bloqueante (`VMIN=0, VTIME=0`) que incrementa um contador a cada ~100ms independente do teclado, mas soma 10 instantaneamente se a tecla espaço for pressionada.

**Conceitos praticados:** `VMIN`/`VTIME` em leitura não-bloqueante, `usleep`, loops de simulação/animação em terminal.

```
Simulando passo 42... (nenhuma tecla)
Tecla capturada: (espaco)   (passo 53)
```

---

## 06. TimeoutWait
> 🔲 Pendente

Configura `VMIN=0, VTIME=10` para esperar até 1 segundo por uma tecla; se nenhuma chegar nesse intervalo, imprime aviso de tempo esgotado e tenta novamente.

**Conceitos praticados:** diferença entre leitura não-bloqueante e leitura com tempo limite, valor de retorno de `read()`.

```
Aguardando tecla (1s)...
tempo esgotado
Aguardando tecla (1s)...
Tecla recebida: 'x'
```

---

## 07. EchoEditor
> 🔲 Pendente

Simula manualmente o comportamento de apagar com Backspace (código 127), que o modo canônico faz sozinho mas que em modo raw precisa ser reimplementado.

**Conceitos praticados:** sequência `\b \b` para apagar visualmente, eco manual de caracteres imprimíveis.

```
Digite algo: ola mund_
```

---

## 08. EchoToggle
> 🔲 Pendente

Liga e desliga o eco do terminal durante a execução do programa (tecla `e` alterna o estado), sem nunca sair do modo raw.

**Conceitos praticados:** reconfiguração de `termios` em tempo de execução, `tcsetattr` chamado múltiplas vezes no mesmo processo.

```
Eco desligado
Eco ligado
Eco desligado
```

---

## 09. TermCore
> 🔲 Pendente

Módulo reutilizável de terminal, separando toda a lógica de `termios` em `terminal.h`/`terminal.c`, seguindo a arquitetura modular usada nos outros repositórios.

**Conceitos praticados:** modularização (`src/`+`include/`), zero lógica de terminal em `main.c`, funções como `terminal_ativar_raw()`, `terminal_restaurar()`, `terminal_ler_tecla()`.

```bash
gcc -Iinclude src/main.c src/terminal.c -o programa
```

---

## 10. GridLoop
> 🔲 Pendente

Combina modo raw, leitura não-bloqueante, detecção de setas, tecla de saída e restauração garantida em um único esqueleto de loop — a base de entrada reaproveitável para os visualizadores do GridForge.

**Conceitos praticados:** integração de todos os conceitos anteriores em um único programa, uso do módulo `TermCore`.

```
Loop iniciado. Setas para navegar, 'q' para sair.
Seta para cima
Passo 128 simulado.
Encerrando, terminal restaurado.
```

---

## Compilando
Cada exercício fica na sua própria pasta com seu próprio `Makefile`.

```bash
cd 01-rawkeys
make
./rawkeys
```

---

## Objetivo
Este repositório documenta minha jornada de aprendizado com `termios.h` e controle de terminal em C.  
O objetivo não é apenas código funcionando, mas entender *por que* cada flag existe — para depois aplicar esse controle de teclado nos visualizadores interativos do GridForge.

---
*Parte da minha trilha de aprendizado em C*
