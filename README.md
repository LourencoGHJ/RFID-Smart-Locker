# Caixa Inteligente RFID

[![Arduino](https://img.shields.io/badge/Platform-Arduino%20Uno-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![RFID](https://img.shields.io/badge/Technology-RFID-blue)](https://en.wikipedia.org/wiki/Radio-frequency_identification)

Projeto desenvolvido no âmbito da **Prova de Aptidão Profissional (PAP)** do curso profissional de **Técnico de Gestão e Programação de Sistemas Informáticos**, no ano letivo **2022/2023**, na Escola Secundária da Boa Nova — Leça da Palmeira.

A **Caixa Inteligente RFID** é um protótipo de cacifo/armário com controlo de acesso por cartões de proximidade RFID. Um Arduino lê o UID do cartão e, de acordo com os identificadores definidos no programa, apresenta o resultado num LCD e controla indicadores luminosos, sinal sonoro e um trinco elétrico.

---

## Acesso rápido

| Recurso | Acesso |
|---|---|
| Código-fonte Arduino | [pap Gui atualizada 30.ino](./pap%20Gui%20atualizada%2030.ino) |
| Bibliotecas incluídas | [Ver pasta libraries](./libraries/) |
| Licença | [LICENSE](./LICENSE) |

## Fotografias

As fotografias anteriormente guardadas na pasta `img/` foram removidas do repositório.

## Objetivo

Recriar, com recurso a uma placa Arduino, o funcionamento básico de um armário inteligente com cartão de acesso. O utilizador aproxima um cartão do leitor RFID; o sistema verifica o identificador e apresenta o resultado através de um ecrã LCD, sinais sonoros e indicadores luminosos.

## Funcionamento do sistema

1. O sistema inicia o leitor RFID e apresenta no LCD a instrução para aproximar um cartão.
2. Quando é detetado um cartão, o Arduino lê o respetivo UID.
3. O UID é apresentado no Monitor Série e comparado com os valores definidos no código.
4. **Cartão autorizado:** apresenta uma mensagem de boas-vindas, emite sinais sonoros, acende o LED azul e ativa o módulo de relé que comanda o trinco elétrico.
5. **UID configurado como não autorizado:** apresenta uma mensagem de acesso negado, utiliza o LED vermelho e mantém o relé desligado.
6. Após o tratamento do cartão, o LCD regressa ao ecrã inicial.

> **Nota sobre o comportamento atual:** o sketch publicado contém uma condição para um UID autorizado e outra para um UID específico configurado como não autorizado. Não existe uma condição geral `else` para todos os cartões desconhecidos; não se deve assumir que qualquer cartão não configurado ativa a rotina de recusa.

## Componentes e materiais

### Eletrónica
- Arduino Uno R3
- Leitor RFID MFRC522 e cartões/tags de proximidade
- Display LCD I2C
- Módulo relé de 5 V
- Mini trinco elétrico solenoide de 12 V
- LED azul e LED vermelho
- Buzzer passivo de 5 V
- Resistências, breadboard e cabos jumper

### Estrutura
- Madeira/tábuas para a caixa
- Dobradiças, parafusos e pega para a porta
- Tinta

A lista reúne os materiais documentados no projeto académico.

## Ligações identificadas no código

| Componente | Pino Arduino |
|---|---:|
| RFID — SS/SDA | 10 |
| RFID — RST | 9 |
| LED azul | 6 |
| LED vermelho | 5 |
| Módulo relé | 8 |
| Buzzer | 7 |

O MFRC522 comunica por SPI. O LCD é inicializado no endereço I2C `0x27`, com dimensão configurada de `20x4`.

**Atenção à alimentação:** o trinco indicado é de 12 V e não deve ser ligado diretamente a um pino do Arduino. A comutação deve ser feita através do módulo/circuito de potência apropriado e de uma alimentação adequada. O repositório não contém um esquema elétrico completo do protótipo; confirma a cablagem física antes de alimentar o circuito.

## Bibliotecas e dependências

O sketch inclui:

- `LiquidCrystal_I2C` — controlo do LCD através de I2C.
- `SPI` — comunicação SPI, incluída no ambiente Arduino.
- `MFRC522` — comunicação com o leitor RFID.

A pasta `libraries/` contém código de bibliotecas de terceiros, incluindo uma biblioteca LiquidCrystal e a biblioteca MFRC522. Nota: a biblioteca LCD incluída na pasta tem o nome `LiquidCrystal`, enquanto o sketch inclui `LiquidCrystal_I2C.h`; confirma a biblioteca I2C compatível no Arduino IDE antes de compilar. Não assumas que a pasta incluída, por si só, fornece exatamente esse cabeçalho.

## Executar o projeto

1. Instala o [Arduino IDE](https://www.arduino.cc/en/software).
2. Instala as bibliotecas necessárias para `LiquidCrystal_I2C.h` e `MFRC522.h`.
3. Liga o circuito de acordo com a montagem física e com os pinos indicados acima.
4. Abre [pap Gui atualizada 30.ino](./pap%20Gui%20atualizada%2030.ino) no Arduino IDE.
5. Seleciona **Arduino Uno** e a porta série correta.
6. Compila e carrega o programa para a placa.
7. Abre o Monitor Série a **9600 baud** para observar os UID dos cartões lidos.
8. Confirma os UID definidos no código antes de testar o acesso.
9. Testa o LCD, LEDs, buzzer, relé e trinco, garantindo uma alimentação adequada.

## Código-fonte e comportamento documentado

O repositório contém atualmente um sketch principal: [`pap Gui atualizada 30.ino`](./pap%20Gui%20atualizada%2030.ino).

O código define os pinos indicados na tabela e compara os UID lidos com identificadores escritos diretamente no programa. A mensagem de boas-vindas está personalizada no sketch. Os tempos de sinalização e de ativação do relé estão definidos através de chamadas `delay()`.

## Limitações conhecidas

- Os UID dos cartões estão definidos diretamente no código.
- Existe um UID autorizado e um UID específico configurado como não autorizado.
- Não está implementada uma gestão dinâmica de utilizadores/cartões.
- Não há evidência, no código publicado, de armazenamento persistente de cartões.
- Não está incluído um esquema elétrico completo do protótipo.
- O comportamento deve ser validado no hardware real; a documentação do repositório não substitui testes físicos.

## Possíveis melhorias

- Tratar todos os cartões não reconhecidos como acesso recusado.
- Permitir adicionar/remover cartões sem alterar o código.
- Organizar os UID autorizados numa estrutura de dados.
- Substituir bloqueios longos com `delay()` por controlo temporal não bloqueante.
- Documentar integralmente ligações, alimentação e circuito do trinco.
- Adicionar evidências de testes e um vídeo de demonstração.

Estas são propostas de evolução e não funcionalidades confirmadas como implementadas.

## Contexto académico

- **Projeto:** Caixa com leitor de Cartões de Proximidade RFID
- **Tipo:** Prova de Aptidão Profissional (PAP)
- **Curso:** Técnico de Gestão e Programação de Sistemas Informáticos
- **Instituição:** Escola Secundária da Boa Nova — Leça da Palmeira
- **Ano letivo:** 2022/2023
- **Relatório:** não incluído neste repositório.

## Referências

As referências indicadas na documentação académica incluem:

- [Fechadura eletrónica com Arduino e RFID — Fazedores](https://blog.fazedores.com/fechadura-eletronica-com-arduino-e-rfid/)
- [Arduino Based RFID Door Lock — The DIY Life](https://www.the-diy-life.com/arduino-based-rfid-door-lock-make-your-own/)
- [Vídeo de apoio — YouTube](https://youtube.com/watch?v=EJKUcGIfNDU)
- [Vídeo de apoio — YouTube](https://youtube.com/watch?v=7bYDdpop7EI)
- [Vídeo de apoio — YouTube](https://youtube.com/watch?v=nAcTO1LELN0)

---

Projeto académico desenvolvido em 2022/2023. O código e as fotografias são disponibilizados neste repositório para consulta e demonstração do trabalho realizado.
