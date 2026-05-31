#include <Arduino.h>

// Définition des broches de l'ESP32
#define MICRO_PIN 36 // Broche d'entrée analogique (SVP / GPIO 36) pour le micro
#define DAC_PIN 25   // Broche de sortie analogique pure (DAC1 / GPIO 25) pour l'ampli

// Seuil du filtre (Noise Gate) : en dessous de cette valeur d'écart, on coupe le son
#define SEUIL_BRUIT 80 

void setup() {
  // Initialisation du port série à 115200 bauds pour la communication avec Teleplot
  Serial.begin(115200);
  
  // Configuration de la broche du micro en entrée
  pinMode(MICRO_PIN, INPUT);
  
  // Atténuation à 11dB pour permettre à l'ADC de lire toute la plage de tension de 0V à 3.3V
  analogSetPinAttenuation(MICRO_PIN, ADC_11db);
  
  // Initialisation du DAC à sa valeur centrale (128 sur une plage de 0 à 255)
  // Cela correspond au silence électrique (la tension moyenne de base)
  dacWrite(DAC_PIN, 128); 
}

void loop() {
  // 1. LECTURE DU MICRO
  // On lit la valeur brute de l'ADC (un entier entre 0 et 4095)
  int valeurMicro = analogRead(MICRO_PIN);
  
  // 2. CALCUL DE L'ÉCART (L'ONDE SONORE)
  // On calcule l'écart par rapport au niveau théorique de silence (2000).
  // 'ecart' peut être positif (onde qui pousse) ou négatif (onde qui tire).
  int ecart = valeurMicro - 2000;
  
  // On prend la valeur absolue (toujours positive) pour mesurer l'intensité globale du bruit
  int ecartAbsolu = abs(ecart);
  
  // Par défaut, on prépare un signal au repos (silence = 128)
  int signalAmplifie = 128;

  // 3. FILTRAGE ET AMPLIFICATION LOGICIELLE
  // Si l'intensité du bruit dépasse notre seuil, on considère que l'utilisateur parle
  if (ecartAbsolu > SEUIL_BRUIT) {
    
    // Équation magique : On prend le centre du DAC (128) et on y ajoute l'écart du micro.
    // Le fait de diviser par 16 fait passer le signal du micro (12 bits) au format DAC (8 bits).
    // Comme on multiplie ici par 2 pour booster le volume, l'opération finale revient à faire (ecart / 8)
    signalAmplifie = 128 + (ecart * 2);
    
    // Anti-saturation HAUTE : Si le calcul dépasse 255, on le bloque à 255 (maximum du DAC)
    if (signalAmplifie > 255) signalAmplifie = 255;
    
    // Anti-saturation BASSE : Si le calcul descend en dessous de 0, on le bloque à 0 (minimum du DAC)
    if (signalAmplifie < 0)   signalAmplifie = 0;
    
  } else {
    // Si l'intensité est sous le seuil, "Noise Gate" : on force le silence absolu à 128
    signalAmplifie = 128;
  }
  
  // 4. ENVOI PHYSIQUE DU SON
  // Le DAC génère instantanément la tension correspondante sur la broche 25 vers le LM386
  dacWrite(DAC_PIN, signalAmplifie);
  

}