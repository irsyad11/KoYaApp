void fuzzySet() {
  // FuzzyInput
  FuzzyInput *suhu = new FuzzyInput(1);

  suhu->addFuzzySet(dingin);
  suhu->addFuzzySet(normal);
  suhu->addFuzzySet(panas);
  
  fuzzy->addFuzzyInput(suhu);

  // FuzzyInput
  FuzzyInput *kelembaban = new FuzzyInput(2);

  kelembaban->addFuzzySet(rendah);
  kelembaban->addFuzzySet(lembab);
  kelembaban->addFuzzySet(tinggi);
  
  fuzzy->addFuzzyInput(kelembaban);

  // FuzzyInput
  FuzzyInput *amonia = new FuzzyInput(3);

  amonia->addFuzzySet(aman);
  amonia->addFuzzySet(bahaya);
  
  fuzzy->addFuzzyInput(amonia);

  // FuzzyOutput
  FuzzyOutput *lampu = new FuzzyOutput(1);

  lampu->addFuzzySet(redup);
  lampu->addFuzzySet(sedang);
  lampu->addFuzzySet(terang);
  
  fuzzy->addFuzzyOutput(lampu);

  // FuzzyOutput
  FuzzyOutput *kipas = new FuzzyOutput(2);

  kipas->addFuzzySet(kipasA);
  kipas->addFuzzySet(kipasP);
  
  fuzzy->addFuzzyOutput(kipas);

  // FuzzyOutput
  FuzzyOutput *fogger = new FuzzyOutput(3);

  fogger->addFuzzySet(foggerA);
  fogger->addFuzzySet(foggerP);
  
  fuzzy->addFuzzyOutput(fogger);
}
