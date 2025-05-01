// Buffer para almacenar la entrada del Monitor Serial
String inputBuffer = "";

// Idioma seleccionado (0: inglés, 1: español)
int language = -1;

// Modo seleccionado (0: menú, 1: individual, 2: todos los pines, 3: info del microcontrolador)
int mode = 0;

// Estructura para mensajes en ambos idiomas
struct Messages {
  String selectLanguage;
  String selectMode;
  String enterPinPrompt;
  String invalidPin;
  String pinInfoHeader;
  String pinType;
  String supportsADC;
  String noADC;
  String supportsTouch;
  String noTouch;
  String validOutput;
  String validInput;
  String nextPinPrompt;
  String invalidMode;
  String microcontrollerInfoHeader;
  String chipModel;
  String chipRevision;
  String chipCores;
  String cpuFrequency;
  String heapTotal;
  String heapFree;
  String psramTotal;
  String psramFree;
  String flashSize;
  String flashSpeed;
  String macAddress;
  String connectivity;
  String notAvailable;
};

// Mensajes en inglés
const Messages englishMessages = {
  "Select language (e for English, s for Spanish):",
  "Select mode:\n\r 1) Enter pins individually \n\r 2) Show all pins info \n\r 3) Show microcontroller info",
  "Enter pin number (or 'menu' to return to menu):",
  "Error: Pin %d is not a valid GPIO (max: %d)",
  "Information for Pin %d:",
  "  Pin type: %s",
  "  Supports ADC (A%d)",
  "  Does not support ADC",
  "  Supports capacitive touch (T%d)",
  "  Does not support capacitive touch",
  "  Valid as output (Output)",
  "  Valid as input (Input)",
  "Enter another pin number (or 'menu' to return to menu):",
  "Select 1, 2, or 3.",
  "Microcontroller Information:",
  "  Chip Model: %s\n\r",
  "  Chip Revision: %d\n\r",
  "  Number of Cores: %d\n\r",
  "  CPU Frequency: %d MHz\n\r",
  "  Total Heap: %d bytes\n\r",
  "  Free Heap: %d bytes\n\r",
  "  Total PSRAM: %d bytes\n\r",
  "  Free PSRAM: %d bytes\n\r",
  "  Flash Size: %d bytes\n\r",
  "  Flash Speed: %d Hz\n\r",
  "  MAC Address: %s",
  "  Connectivity: %s",
  "  Pin not available on this board"
};

// Mensajes en español
const Messages spanishMessages = {
  "Selecciona idioma (e para inglés, s para español):",
  "Selecciona modo:\n\r 1) Ingresar pines individualmente \n\r 2) Mostrar info de todos los pines \n\r 3) Mostrar info del microcontrolador\n\r",
  "Ingresa el número del pin (o 'menu' para volver al menú):",
  "Error: Pin %d no es un GPIO válido (max: %d)",
  "Información del Pin %d:",
  "  Tipo de pin: %s",
  "  Soporta ADC (A%d)",
  "  No soporta ADC",
  "  Soporta Touch capacitivo (T%d)",
  "  No soporta Touch capacitivo",
  "  Válido como salida (Output)",
  "  Válido como entrada (Input)",
  "Ingresa otro número de pin (o 'menu' para volver al menú):",
  "Selecciona 1, 2 o 3.",
  "Información del Microcontrolador:",
  "  Modelo del Chip: %s\n\r",
  "  Revisión del Chip: %d\n\r",
  "  Número de Núcleos: %d\n\r",
  "  Frecuencia del CPU: %d MHz\n\r",
  "  Heap Total: %d bytes\n\r",
  "  Heap Libre: %d bytes\n\r",
  "  PSRAM Total: %d bytes\n\r",
  "  PSRAM Libre: %d bytes\n\r",
  "  Tamaño de Flash: %d bytes\n\r",
  "  Velocidad de Flash: %d Hz\n\r",
  "  Dirección MAC: %s\n\r",
  "  Conectividad: %s\n\r",
  "  Pin no disponible en esta placa"
};

// Función para identificar el tipo de pin basado en pins_arduino.h
String pinTypeToString(int pinType) {
  String types = "";
  if (pinType == TX) { types += "TX "; }
  if (pinType == RX) { types += "RX "; }
#ifdef TX1
  if (pinType == TX1) { types += "TX1 "; }
#endif
#ifdef RX1
  if (pinType == RX1) { types += "RX1 "; }
#endif
#ifdef TX2
  if (pinType == TX2) { types += "TX2 "; }
#endif
#ifdef RX2
  if (pinType == RX2) { types += "RX2 "; }
#endif
  if (pinType == SDA) { types += "SDA "; }
  if (pinType == SCL) { types += "SCL "; }
#ifdef SDA1
  if (pinType == SDA1) { types += "SDA1 "; }
#endif
#ifdef SCL1
  if (pinType == SCL1) { types += "SCL1 "; }
#endif
  if (pinType == SS) { types += "SS "; }
  if (pinType == MOSI) { types += "MOSI "; }
  if (pinType == MISO) { types += "MISO "; }
  if (pinType == SCK) { types += "SCK "; }
  if (pinType == BUILTIN_LED || pinType == LED_BUILTIN) { types += "LED_BUILTIN "; }
#ifdef RGB_BUILTIN
  if (pinType == RGB_BUILTIN) { types += "RGB_BUILTIN "; }
#endif
#ifdef NEOPIXEL
  if (pinType == NEOPIXEL) { types += "NEOPIXEL "; }
#endif
  if (pinType == DAC1) { types += "DAC1 "; }
  if (pinType == DAC2) { types += "DAC2 "; }
  if (types == "") { types = "Normal"; }
  return types;
}

// Función para mostrar información de un solo pin
void printPinInfo(int pin) {
  const Messages& msg = (language == 1) ? spanishMessages : englishMessages;
  
  // Validar entrada
  if (pin < 0 || pin >= SOC_GPIO_PIN_COUNT) {
    Serial.printf(msg.invalidPin.c_str(), pin, SOC_GPIO_PIN_COUNT - 1);
    Serial.println("");
    return;
  }
  
  // Mostrar información del pin
  Serial.printf(msg.pinInfoHeader.c_str(), pin);
  Serial.println("");
  
  // Obtener tipo de pin
  Serial.printf(msg.pinType.c_str(), pinTypeToString(pin).c_str());
  Serial.println("");
  
  // Verificar soporte para ADC
  int8_t adcChannel = digitalPinToAnalogChannel(pin);
  if (adcChannel >= 0) {
    Serial.printf(msg.supportsADC.c_str(), adcChannel);
    Serial.println("");
  } else {
    Serial.println(msg.noADC);
  }
  
  // Verificar soporte para touch capacitivo
  int8_t touchChannel = digitalPinToTouchChannel(pin);
  if (touchChannel >= 0) {
    Serial.printf(msg.supportsTouch.c_str(), touchChannel);
    Serial.println("");
  } else {
    Serial.println(msg.noTouch);
  }
  
  // Verificar capacidades de entrada/salida
  bool isValid = false;
  if (GPIO_IS_VALID_OUTPUT_GPIO(pin)) {
    Serial.println(msg.validOutput);
    isValid = true;
  }
  if (GPIO_IS_VALID_GPIO(pin)) {
    Serial.println(msg.validInput);
    isValid = true;
  }
  if (!isValid) {
    Serial.println(msg.notAvailable);
  }
  
  Serial.println("_______________________________________________");
}

// Función para mostrar información de todos los pines
void printAllPinsInfo() {
  const Messages& msg = (language == 1) ? spanishMessages : englishMessages;
  for (int pin = 0; pin < SOC_GPIO_PIN_COUNT; pin++) {
    printPinInfo(pin);
    Serial.println();
  }
  Serial.println(msg.nextPinPrompt);
}

// Función para mostrar información del microcontrolador
void printMicrocontrollerInfo() {
  const Messages& msg = (language == 1) ? spanishMessages : englishMessages;
  Serial.println(msg.microcontrollerInfoHeader);
  
  // Modelo y revisión del chip
  Serial.printf(msg.chipModel.c_str(), ESP.getChipModel());
  Serial.printf(msg.chipRevision.c_str(), ESP.getChipRevision());
  
  // Número de núcleos
  Serial.printf(msg.chipCores.c_str(), ESP.getChipCores());
  
  // Frecuencia del CPU
  Serial.printf(msg.cpuFrequency.c_str(), ESP.getCpuFreqMHz());
  
  // Memoria (Heap y PSRAM)
  Serial.printf(msg.heapTotal.c_str(), ESP.getHeapSize());
  Serial.printf(msg.heapFree.c_str(), ESP.getFreeHeap());
  Serial.printf(msg.psramTotal.c_str(), ESP.getPsramSize());
  Serial.printf(msg.psramFree.c_str(), ESP.getFreePsram());
  
  // Flash
  Serial.printf(msg.flashSize.c_str(), ESP.getFlashChipSize());
  Serial.printf(msg.flashSpeed.c_str(), ESP.getFlashChipSpeed());
  
  // Dirección MAC
  uint64_t mac = ESP.getEfuseMac();
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%04X%08X", (uint16_t)(mac >> 32), (uint32_t)mac);
  Serial.printf(msg.macAddress.c_str(), macStr);
  
  // Conectividad (basado en el modelo del chip)
  String connectivity = "";
  String chipModel = ESP.getChipModel();
  if (chipModel.startsWith("ESP32-S3") || chipModel.startsWith("ESP32-C3")) {
    connectivity = "WiFi 802.11b/g/n, Bluetooth LE 5.0";
  } else if (chipModel.startsWith("ESP32-S2")) {
    connectivity = "WiFi 802.11b/g/n";
  } else {
    connectivity = "WiFi 802.11b/g/n, Bluetooth 4.2/BLE";
  }
  Serial.printf(msg.connectivity.c_str(), connectivity.c_str());
}

void setup() {
  // Iniciar Serial
  Serial.begin(115200);
  delay(3000);
  
  // Selección de idioma
  Serial.println("Select language / Selecciona idioma:");
  Serial.println("  e: English / Inglés");
  Serial.println("  s: Spanish / Español");
  while (language == -1) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == 'e' || c == 'E') {
        language = 0;
        Serial.println("Language set to English");
      } else if (c == 's' || c == 'S') {
        language = 1;
        Serial.println("Idioma establecido a Español");
      } else {
        Serial.println("Select language / Selecciona idioma:");
        Serial.println("  e: English / Inglés");
        Serial.println("  s: Spanish / Español");
      }
    }
  }
  
  // Mostrar menú inicial
  const Messages& msg = (language == 1) ? spanishMessages : englishMessages;
  Serial.println(msg.selectMode);
  mode = 0; // Asegurar que empezamos en el menú
}

void loop() {
  const Messages& msg = (language == 1) ? spanishMessages : englishMessages;
  
  // Mostrar menú si mode == 0
  if (mode == 0) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '1') {
        mode = 1;
        Serial.println(language == 0 ? "Mode: Enter pins individually" : "Modo: Ingresar pines individualmente");
        Serial.println(msg.enterPinPrompt);
      } else if (c == '2') {
        mode = 2;
        Serial.println(language == 0 ? "Mode: Show all pins info" : "Modo: Mostrar info de todos los pines");
        printAllPinsInfo();
        mode = 0; // Volver al menú tras mostrar todos los pines
        Serial.println(msg.selectMode);
      } else if (c == '3') {
        mode = 3;
        Serial.println(language == 0 ? "Mode: Show microcontroller info" : "Modo: Mostrar info del microcontrolador");
        printMicrocontrollerInfo();
        mode = 0; // Volver al menú tras mostrar info
        Serial.println();
        Serial.println(msg.selectMode);
      } else {
        Serial.println(msg.invalidMode);
      }
    }
  }
  
  // Modo individual: leer entrada del Monitor Serial
  if (mode == 1 && Serial.available()) {
    char c = Serial.read();
    
    // Si es un dígito, añadir al buffer
    if (isdigit(c)) {
      inputBuffer += c;
    } else {
      // Si se ingresa un carácter no numérico, procesar el buffer
      if (inputBuffer.length() > 0) {
        // Verificar si el usuario ingresó "menu"
        inputBuffer.trim();
        if (inputBuffer.equalsIgnoreCase("menu")) {
          mode = 0;
          inputBuffer = "";
          Serial.println(msg.selectMode);
        } else {
          // Procesar como número de pin
          int pin = inputBuffer.toInt();
          printPinInfo(pin);
          inputBuffer = "";
          Serial.println();
          Serial.println(msg.nextPinPrompt);
        }
      }
    }
  }
}
