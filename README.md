#### **[[ENGLISH]](#spanish)**

# ESP32 PinInfo

### Descripción
ESP32 PinInfo es un sketch de Arduino para placas ESP32 que muestra información sobre pines GPIO y especificaciones del microcontrolador. Soporta inglés y español, con tres modos: información de pines individuales, reporte con la informacion de todos los pines, y detalles del microcontrolador. Ideal para desarrolladores que exploran capacidades de ESP32.

### Características
- Muestra tipos de pines (ej., TX, SDA, A0), soporte ADC/touch, y valida el pin como entrada/salida.
- Detalla el microcontrolador: modelo, núcleos, frecuencia, memoria, flash, dirección MAC, y conectividad.
- Interfaz bilingüe (inglés/español).
- Modos interactivos con navegación por menú (regresa con "menu").
- Compatible con variantes de ESP32 (ESP32, S2, S3, C3) y probablemente otras no probadas.

### Requisitos
- Placa ESP32 (ej., ESP32 DevKit, ESP32-S3).
- Arduino IDE o IDE compatible.
- Núcleo ESP32 para Arduino (versión 2.0.17+).
- Monitor Serial a 115200 baudios, "Retorno de carro".

### Configuración
1. Instala el núcleo ESP32:
   - En Arduino IDE, añade `https://raw.githubusercontent.com/espressif/arduino-esp32/master/package_esp32_index.json` en Preferencias.
   - Ve a Administrador de Placas, busca "esp32" e instala.
2. Descarga `pin_info_dynamic.ino` desde este repositorio.
3. Abre el sketch en Arduino IDE.
4. Selecciona tu placa ESP32 (ej., "ESP32 Dev Module") en Herramientas > Placa.
5. Carga el sketch a tu placa.

### Uso
1. Abre el Monitor Serial (115200 baudios, Sin ajuste de línea).
2. Selecciona idioma (`e` para inglés, `s` para español).
3. Elige modo:
   - `1`: Ingresa números de pines o "menu" para volver al menú.
   - `2`: Muestra info de todos los pines, luego regresa al menú.
   - `3`: Muestra info del microcontrolador, luego regresa al menú.
4. Sigue las instrucciones para explorar detalles de pines o hardware.

### Ejemplo de Salida
**Modo 1: Pin 4**
```
Ingresa el número del pin (o 'menu' para volver al menú):
4
Información del Pin 4:
  Tipo de pin: RX2
  Soporta ADC (A10)
  Soporta Touch capacitivo (T0)
  Válido como salida (Output)
  Válido como entrada (Input)
_______________________________________________

Ingresa otro número de pin (o 'menu' para volver al menú):
```

**Modo 3: Info del Microcontrolador**
```
Modo: Mostrar info del microcontrolador
Información del Microcontrolador:
  Modelo del Chip: ESP32-D0WDQ6
  Revisión del Chip: 1
  Número de Núcleos: 2
  Frecuencia del CPU: 240 MHz
  Heap Total: 327680 bytes
  Heap Libre: 298456 bytes
  PSRAM Total: 0 bytes
  PSRAM Libre: 0 bytes
  Tamaño de Flash: 4194304 bytes
  Velocidad de Flash: 40000000 Hz
  Dirección MAC: 24B4C8A12345
  Conectividad: WiFi 802.11b/g/n, Bluetooth 4.2/BLE
```
## Contribuciones

Las contribuciones son bienvenidas. Si encuentras un problema o tienes una sugerencia, por favor abre un issue o envía un pull request.

#### **[[SPANISH]](#english)** 

# ESP32 PinInfo

### Description
ESP32 PinInfo is an Arduino sketch for ESP32 boards that displays information about GPIO pins and microcontroller specifications. It supports English and Spanish, offering three modes: individual pin info, all pins info, and microcontroller details. Perfect for developers exploring ESP32 capabilities.

### Features
- Shows pin types (e.g., TX, SDA, A0), ADC/touch support, and input/output validity.
- Displays microcontroller details: chip model, cores, CPU frequency, memory, flash, MAC address, and connectivity.
- Bilingual interface (English/Spanish).
- Interactive modes with menu navigation (return via "menu" command).
- Compatible with ESP32 variants (ESP32, S2, S3, C3).

### Requirements
- ESP32 board (e.g., ESP32 DevKit, ESP32-S3).
- Arduino IDE or compatible IDE.
- ESP32 core for Arduino (version 2.0.17+).
- Serial Monitor at 115200 baud, "No line ending".

### Setup
1. Install the ESP32 core:
   - In Arduino IDE, add `https://raw.githubusercontent.com/espressif/arduino-esp32/master/package_esp32_index.json` to Preferences.
   - Go to Boards Manager, search "esp32", and install.
2. Download `pin_info_dynamic.ino` from this repository.
3. Open the sketch in Arduino IDE.
4. Select your ESP32 board (e.g., "ESP32 Dev Module") under Tools > Board.
5. Upload the sketch to your board.

### Usage
1. Open Serial Monitor (115200 baud, No line ending).
2. Select language (`e` for English, `s` for Spanish).
3. Choose mode:
   - `1`: Enter pin numbers or "menu" to return to the menu.
   - `2`: View all pins info, then return to menu.
   - `3`: View microcontroller info, then return to menu.
4. Follow prompts to explore pin or hardware details.

### Example Output
**Mode 1: Pin 4**
```
Enter pin number (or 'menu' to return to menu):
4
Information for Pin 4:
  Pin type: RX2
  Supports ADC (A10)
  Supports capacitive touch (T0)
  Valid as output (Output)
  Valid as input (Input)
_______________________________________________

Enter another pin number (or 'menu' to return to menu):
```

**Mode 3: Microcontroller Info**
```
Mode: Show microcontroller info
Microcontroller Information:
  Chip Model: ESP32-D0WDQ6
  Chip Revision: 1
  Number of Cores: 2
  CPU Frequency: 240 MHz
  Total Heap: 327680 bytes
  Free Heap: 298456 bytes
  Total PSRAM: 0 bytes
  Free PSRAM: 0 bytes
  Flash Size: 4194304 bytes
  Flash Speed: 40000000 Hz
  MAC Address: 24B4C8A12345
  Connectivity: WiFi 802.11b/g/n, Bluetooth 4.2/BLE
```
## Contributions

Contributions are welcome. If you find a problem or have a suggestion, please open an issue or send a pull request.
