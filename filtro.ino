// Configurações do filtro passa-baixa
float cutoff_freq = 50;  // Frequência de corte desejada em Hz
float sampling_freq = 512;  // Frequência de amostragem em Hz
float alpha;
float outputStages[3];
float prevOutputs[3];

void setup() {
  Serial.begin(115200);
  // Cálculo de alpha baseado nas frequências
  alpha = (2 * 3.1416 * cutoff_freq) / (sampling_freq + 2 * 3.1416 * cutoff_freq);

}

void loop() {
  if (Serial.available()) {
    float inputSignal = Serial.parseFloat();
    Serial.read(); // Limpa o buffer

    // Aplica o filtro IIR em três estágios
    for (int i = 0; i < 3; i++) {
      if (i == 0) {
        // Primeira etapa: o input é o sinal original
        outputStages[i] = alpha * inputSignal + (1 - alpha) * prevOutputs[i];
      } else {
        // As etapas subsequentes usam a saída da etapa anterior
        outputStages[i] = alpha * outputStages[i - 1] + (1 - alpha) * prevOutputs[i];
      }
    }

    // Envia a saída do terceiro estágio
    Serial.println(outputStages[2]);

    // Atualiza as saídas anteriores para a próxima iteração
    for (int i = 0; i < 3; i++) {
      prevOutputs[i] = outputStages[i];
    }
  }
}
