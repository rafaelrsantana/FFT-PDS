// Configurações do filtro passa-baixa
float cutoff_freq = 20;  // Frequência de corte desejada em Hz
float sampling_freq = 1024;  // Frequência de amostragem em Hz
float alpha;
float outputStages[2];
float prevOutputs[2];

void setup() {
  Serial.begin(115200);
  // Cálculo de alpha baseado nas frequências
  alpha = (2 * 3.1416 * cutoff_freq) / (sampling_freq + 2 * 3.1416 * cutoff_freq);

}

void loop() {
  if (Serial.available()) {
    float inputSignal = Serial.parseFloat();
    Serial.read(); 

  
    for (int i = 0; i < 2; i++) {
      if (i == 0) {
        
        outputStages[i] = alpha * inputSignal + (1 - alpha) * prevOutputs[i];
      } else {
        
        outputStages[i] = alpha * outputStages[i - 1] + (1 - alpha) * prevOutputs[i];
      }
    }

    // Envia a saída do terceiro estágio
    Serial.println(outputStages[1]);

    // Atualiza as saídas anteriores para a próxima iteração
    for (int i = 0; i < 2; i++) {
      prevOutputs[i] = outputStages[i];
    }
  }
}
