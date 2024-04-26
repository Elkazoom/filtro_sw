//===========================================================================================================
// Gerenciamento de Motores - Lógica de filtro
// Cristóvão Guimarães - 30/03/2023
//===========================================================================================================

//===========================================================================================================
// Declaração de variáveis Globais do programa 
//===========================================================================================================

float filtrado_anterior = 0;    //Valor calculado no ciclo anterior
float valor_lido = 0;           //Valor lido no conversor Digital-Analógico
float valor_filtrado = 0;       //Valor filtrado da entrada Digital-Analógica
float k=0.1;                   //Ganho ajustável (ganho > 1 - oscilação | Ganho < 1 - amortecimento/filtro) 
int count = 0;                  //Variável acumuladora 
int flag = 0;                   //Variável de controle de fluxo de lógica

//===========================================================================================================
// Inicia a função de ajustes iniciais da máquina 
//===========================================================================================================

void setup()             
{
  Serial.begin(9600);           //Declara uso da porta de comunicação (RS-232 Pinos: 1 TX | 2 RX)
  pinMode(13, OUTPUT);          //Informa que o pino 13 será utilizado como saída digital
}

//===========================================================================================================
// Inicia o loop "infinito"
//===========================================================================================================

void loop() {       
              
  valor_lido = analogRead(A1);            //Faz a leitura analógica do pini A1 do arduino

  valor_filtrado = (filtrado_anterior + (k * (valor_lido - filtrado_anterior))); //Aplica a lógica do filtro
  filtrado_anterior = valor_filtrado;                                            //Salva o valor filtrado calculado para ser usado como filtrado anterior no próximo ciclo

  Serial.print("Valor_filtrado:");        //Cria o "Label" do gráfico para a função ploter
  Serial.print(valor_filtrado);           //Envia o valor calculado filtrado
  Serial.print(",");                      //Quebra para envio de novo gráfico 
  Serial.print("Valor_lido:");            //Cria o "Label" do gráfico para a função ploter
  Serial.println(valor_lido);             //Envia o valor calculado filtrado

//===========================================================================================================
// A lógica abaixo é utilizada para gerar uma onda quadrada no pino 13 
//===========================================================================================================
  
  count++;                                //Contador acumulador 
  
  if(count == 70)                         //Verifica se contador atigiu o valor de estouto
  {
    if(flag == 1)                         //Caso a variavel de controle seja "1", coloca 5 volts na saída (pino 13 Arduino) 
    {
      digitalWrite(13, HIGH);             //Ativa o pino 13 com 5 volts na saída
      flag=0;                             //Muda a variável de controle para zero para o proximo estouro do contador
    }
    else
    {
      digitalWrite(13, LOW);              //Desabilita o pino 13 com 5 volts na saída
      flag=1;                             //Muda a variável de controle para 1 para o próximo estouro do contador
    }

    count=0;                              //Zera o contador para iniciar o novo ciclo
  }
 
  delay(10);                              //Aguarda 10 ms para reiniciar um novo loop
}
