void fuzzyRule() {
  //  Fuzzy Rule

//  Membangun Rule 1
  FuzzyRuleAntecedent *suhuDinginDanKelembabanRendah = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanRendah->joinWithAND(dingin, rendah);
  FuzzyRuleAntecedent *amoniaAman = new FuzzyRuleAntecedent();
  amoniaAman->joinSingle(aman);
  FuzzyRuleAntecedent *suhuDinginDanKelembabanRendahDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanRendahDanAmoniaAman->joinWithAND(suhuDinginDanKelembabanRendah, amoniaAman);

  FuzzyRuleConsequent *thenLampuTerangDanKipasAktifDanFoggerAktif = new FuzzyRuleConsequent();
  thenLampuTerangDanKipasAktifDanFoggerAktif->addOutput(terang);
  thenLampuTerangDanKipasAktifDanFoggerAktif->addOutput(kipasA);
  thenLampuTerangDanKipasAktifDanFoggerAktif->addOutput(foggerA);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, suhuDinginDanKelembabanRendahDanAmoniaAman, thenLampuTerangDanKipasAktifDanFoggerAktif);
  fuzzy->addFuzzyRule(fuzzyRule1);

  
//  Membangun Rule 2
  FuzzyRuleAntecedent *amoniaBahaya = new FuzzyRuleAntecedent();
  amoniaBahaya->joinSingle(bahaya);
  FuzzyRuleAntecedent *suhuDinginDanKelembabanRendahDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanRendahDanAmoniaBahaya->joinWithAND(suhuDinginDanKelembabanRendah, amoniaBahaya);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, suhuDinginDanKelembabanRendahDanAmoniaBahaya, thenLampuTerangDanKipasAktifDanFoggerAktif);
  fuzzy->addFuzzyRule(fuzzyRule2);

//  Membangun Rule 3
  FuzzyRuleAntecedent *suhuDinginDanKelembabanLembab = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanLembab->joinWithAND(dingin, lembab);
  FuzzyRuleAntecedent *suhuDinginDanKelembabanLembabDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanLembabDanAmoniaAman->joinWithAND(suhuDinginDanKelembabanLembab, amoniaAman);

  FuzzyRuleConsequent *thenLampuTerangDanKipasPadamDanFoggerPadam = new FuzzyRuleConsequent();
  thenLampuTerangDanKipasPadamDanFoggerPadam->addOutput(terang);
  thenLampuTerangDanKipasPadamDanFoggerPadam->addOutput(kipasP);
  thenLampuTerangDanKipasPadamDanFoggerPadam->addOutput(foggerP);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, suhuDinginDanKelembabanLembabDanAmoniaAman, thenLampuTerangDanKipasPadamDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule3);

//  Membangun Rule 4
  FuzzyRuleAntecedent *suhuDinginDanKelembabanLembabDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanLembabDanAmoniaBahaya->joinWithAND(suhuDinginDanKelembabanLembab, amoniaBahaya);
 
  FuzzyRuleConsequent *thenLampuTerangDanKipasAktifDanFoggerPadam = new FuzzyRuleConsequent();
  thenLampuTerangDanKipasAktifDanFoggerPadam->addOutput(terang);
  thenLampuTerangDanKipasAktifDanFoggerPadam->addOutput(kipasP);
  thenLampuTerangDanKipasAktifDanFoggerPadam->addOutput(foggerP);

  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, suhuDinginDanKelembabanLembabDanAmoniaBahaya, thenLampuTerangDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule4);

//  Membangun rule 5
  FuzzyRuleAntecedent *suhuDinginDanKelembabanTinggi = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanTinggi->joinWithAND(dingin, tinggi);
  FuzzyRuleAntecedent *suhuDinginDanKelembabanTinggiDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuDinginDanKelembabanTinggiDanAmoniaAman->joinWithAND(suhuDinginDanKelembabanTinggi, amoniaAman);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, suhuDinginDanKelembabanTinggiDanAmoniaAman, thenLampuTerangDanKipasPadamDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule5);

//  Membangun Rule 6
  FuzzyRuleAntecedent *suhuDinginDanKelembabanTinggiDanAmoniaBahaya = new FuzzyRuleAntecedent(); 
  suhuDinginDanKelembabanTinggiDanAmoniaBahaya->joinWithAND(suhuDinginDanKelembabanTinggi, amoniaBahaya);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, suhuDinginDanKelembabanTinggiDanAmoniaBahaya, thenLampuTerangDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule6);

//  Membangun Rule 7
  FuzzyRuleAntecedent *suhuNormalDanKelembabanRendah = new FuzzyRuleAntecedent(); 
  suhuNormalDanKelembabanRendah->joinWithAND(normal, rendah);
  FuzzyRuleAntecedent *suhuNormalDanKelembabanRendahDanAmoniaAman = new FuzzyRuleAntecedent(); 
  suhuNormalDanKelembabanRendahDanAmoniaAman->joinWithAND(suhuNormalDanKelembabanRendah, amoniaAman);

  FuzzyRuleConsequent *thenLampuRedupDanKipasAktifDanFoggerAktif = new FuzzyRuleConsequent();
  thenLampuRedupDanKipasAktifDanFoggerAktif->addOutput(redup);
  thenLampuRedupDanKipasAktifDanFoggerAktif->addOutput(kipasA);
  thenLampuRedupDanKipasAktifDanFoggerAktif->addOutput(foggerA);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, suhuNormalDanKelembabanRendahDanAmoniaAman, thenLampuRedupDanKipasAktifDanFoggerAktif);
  fuzzy->addFuzzyRule(fuzzyRule7);

//  membangun Rule 8
  FuzzyRuleAntecedent *suhuNormalDanKelembabanRendahDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuNormalDanKelembabanRendahDanAmoniaBahaya->joinWithAND(suhuNormalDanKelembabanRendah, amoniaBahaya);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, suhuNormalDanKelembabanRendahDanAmoniaBahaya, thenLampuRedupDanKipasAktifDanFoggerAktif);
  fuzzy->addFuzzyRule(fuzzyRule8);

//  membangun Rule 9
  FuzzyRuleAntecedent *suhuNormalDanKelembabanLembab = new FuzzyRuleAntecedent(); 
  suhuNormalDanKelembabanLembab->joinWithAND(normal, lembab);
  FuzzyRuleAntecedent *suhuNormalDanKelembabanLembabDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuNormalDanKelembabanLembabDanAmoniaAman->joinWithAND(suhuNormalDanKelembabanLembab, amoniaAman);

  FuzzyRuleConsequent *thenLampuRedupDanKipasPadamDanFoggerPadam = new FuzzyRuleConsequent();
  thenLampuRedupDanKipasPadamDanFoggerPadam->addOutput(redup);
  thenLampuRedupDanKipasPadamDanFoggerPadam->addOutput(kipasP);
  thenLampuRedupDanKipasPadamDanFoggerPadam->addOutput(foggerP);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, suhuNormalDanKelembabanLembabDanAmoniaAman, thenLampuRedupDanKipasPadamDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule9);

//  membangun Rule 10
  FuzzyRuleAntecedent *suhuNormalDanKelembabanLembabDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuNormalDanKelembabanLembabDanAmoniaBahaya->joinWithAND(suhuNormalDanKelembabanLembab, amoniaBahaya);

  FuzzyRuleConsequent *thenLampuRedupDanKipasAktifDanFoggerPadam = new FuzzyRuleConsequent();
  thenLampuRedupDanKipasAktifDanFoggerPadam->addOutput(redup);
  thenLampuRedupDanKipasAktifDanFoggerPadam->addOutput(kipasA);
  thenLampuRedupDanKipasAktifDanFoggerPadam->addOutput(foggerP);

  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, suhuNormalDanKelembabanLembabDanAmoniaBahaya, thenLampuRedupDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule10);

//  membangun Rule 11
  FuzzyRuleAntecedent *suhuNormalDanKelembabanTinggi = new FuzzyRuleAntecedent();
  suhuNormalDanKelembabanTinggi->joinWithAND(normal, tinggi);
  FuzzyRuleAntecedent *suhuNormalDanKelembabanTinggiDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuNormalDanKelembabanTinggiDanAmoniaAman->joinWithAND(suhuNormalDanKelembabanTinggi, amoniaAman);

  FuzzyRuleConsequent *thenLampuSedangDanKipasPadamDanFoggerPadam = new FuzzyRuleConsequent();
  thenLampuSedangDanKipasPadamDanFoggerPadam->addOutput(sedang);
  thenLampuSedangDanKipasPadamDanFoggerPadam->addOutput(kipasP);
  thenLampuSedangDanKipasPadamDanFoggerPadam->addOutput(foggerP);

  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, suhuNormalDanKelembabanTinggiDanAmoniaAman, thenLampuSedangDanKipasPadamDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule11);

//  membangun rule 12
  FuzzyRuleAntecedent *suhuNormalDanKelembabanTinggiDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuNormalDanKelembabanTinggiDanAmoniaBahaya->joinWithAND(suhuNormalDanKelembabanTinggi, amoniaBahaya);

  FuzzyRuleConsequent *thenLampuSedangDanKipasAktifDanFoggerPadam = new FuzzyRuleConsequent();
  thenLampuSedangDanKipasAktifDanFoggerPadam->addOutput(sedang);
  thenLampuSedangDanKipasAktifDanFoggerPadam->addOutput(kipasA);
  thenLampuSedangDanKipasAktifDanFoggerPadam->addOutput(foggerP);

  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, suhuNormalDanKelembabanTinggiDanAmoniaBahaya, thenLampuSedangDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule12);

//  membangun RUle 13
  FuzzyRuleAntecedent *suhuPanasDanKelembabanRendah = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanRendah->joinWithAND(panas, rendah);
  FuzzyRuleAntecedent *suhuPanasDanKelembabanRendahDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanRendahDanAmoniaAman->joinWithAND(suhuPanasDanKelembabanRendah, amoniaAman);

  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, suhuPanasDanKelembabanRendahDanAmoniaAman, thenLampuRedupDanKipasAktifDanFoggerAktif);
  fuzzy->addFuzzyRule(fuzzyRule13);

//  membangun Rule 14
  FuzzyRuleAntecedent *suhuPanasDanKelembabanRendahDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanRendahDanAmoniaBahaya->joinWithAND(suhuPanasDanKelembabanRendah, amoniaBahaya);

  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, suhuPanasDanKelembabanRendahDanAmoniaBahaya, thenLampuRedupDanKipasAktifDanFoggerAktif);
  fuzzy->addFuzzyRule(fuzzyRule14);

//  membangun Rule 15
  FuzzyRuleAntecedent *suhuPanasDanKelembabanLembab = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanLembab->joinWithAND(panas, lembab);
  FuzzyRuleAntecedent *suhuPanasDanKelembabanLembabDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanLembabDanAmoniaAman->joinWithAND(suhuPanasDanKelembabanLembab, amoniaAman);

  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, suhuPanasDanKelembabanLembabDanAmoniaAman, thenLampuRedupDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule15);

//  membangun RUle16
  FuzzyRuleAntecedent *suhuPanasDanKelembabanLembabDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanLembabDanAmoniaBahaya->joinWithAND(suhuPanasDanKelembabanLembab, amoniaBahaya);

  FuzzyRule *fuzzyRule16 = new FuzzyRule(16, suhuPanasDanKelembabanLembabDanAmoniaBahaya, thenLampuRedupDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule16);

//  membangun Rule17
  FuzzyRuleAntecedent *suhuPanasDanKelembabanTinggi = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanTinggi->joinWithAND(panas, tinggi);
  FuzzyRuleAntecedent *suhuPanasDanKelembabanTinggiDanAmoniaAman = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanTinggiDanAmoniaAman->joinWithAND(suhuPanasDanKelembabanTinggi, amoniaAman);

  FuzzyRule *fuzzyRule17 = new FuzzyRule(17, suhuPanasDanKelembabanTinggiDanAmoniaAman, thenLampuRedupDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule17);

//  membangun Rule 18
  FuzzyRuleAntecedent *suhuPanasDanKelembabanTinggiDanAmoniaBahaya = new FuzzyRuleAntecedent();
  suhuPanasDanKelembabanTinggiDanAmoniaBahaya->joinWithAND(suhuPanasDanKelembabanTinggi, amoniaBahaya);

  FuzzyRule *fuzzyRule18 = new FuzzyRule(18, suhuPanasDanKelembabanTinggiDanAmoniaBahaya, thenLampuRedupDanKipasAktifDanFoggerPadam);
  fuzzy->addFuzzyRule(fuzzyRule18);
  
}
