# TASK-001 – Das erste Device

## Ziel

Den ersten kleinen Baustein des späteren DeviceHub implementieren.

Aktuelle Architektur:

DeviceHub
└── Device

Noch keine Vererbung, Pointer, Threads oder Linux-Systemprogrammierung.

---

## Lerninhalt

Mit dieser Aufgabe werden folgende C++-Grundlagen aufgefrischt:

- Klassen und Objekte
- Konstruktoren
- Header-/Source-Trennung
- `private` / `public`
- Getter
- `const`
- Referenzen
- `std::string`
- `enum class`
- Stack-Objekte
- grundlegende Object Lifetime
- grundlegendes CMake

---

## Projektstruktur

Das Projekt soll ungefähr folgende Struktur haben:

devicehub/
├── .gitignore
├── README.md
├── CMakeLists.txt
├── TASK-001.md
└── src/
    ├── main.cpp
    ├── Device.hpp
    └── Device.cpp

Der Ordner `build/` soll nicht in Git eingecheckt werden.

---

## Anforderungen

### 1. Klasse Device

Eine Klasse `Device` implementieren.

Ein Device besitzt mindestens:

- ID
- Name
- Status

Die konkreten C++-Datentypen dafür selbst auswählen.

---

### 2. Device Status

Der Status darf kein `bool` sein.

Stattdessen soll ein `enum class` verwendet werden.

Mindestens folgende Zustände sollen existieren:

- Enabled
- Disabled
- Error

---

### 3. Konstruktor

`Device` soll einen Konstruktor besitzen.

Über den Konstruktor müssen mindestens folgende Werte gesetzt werden können:

- ID
- Name

Überlege selbst, welchen initialen Status ein neu erzeugtes Device haben soll.

---

### 4. Zugriff auf Device-Daten

Die Informationen eines Devices sollen über Member-Funktionen ausgelesen werden können.

Mindestens:

- ID
- Name
- Status

Dabei soll auf sinnvolle Verwendung von `const` geachtet werden.

Insbesondere überlegen:

Soll ein Name-Getter

    std::string getName() const;

oder

    const std::string& getName() const;

zurückgeben?

Die Entscheidung soll begründet werden können.

---

### 5. main()

In `main()` mindestens zwei `Device`-Objekte erzeugen.

Zum Beispiel:

- CPU Temperature
- GPIO Controller

Die Devices als normale lokale Objekte erzeugen.

Noch kein:

- `new`
- `delete`
- `unique_ptr`
- `shared_ptr`

Anschließend die Informationen der Devices auf der Konsole ausgeben.

---

## CMake

Das Projekt muss mit CMake gebaut werden können.

C++20 verwenden.

Bevorzugt:

    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

Build beispielsweise mit:

    cmake -S . -B build
    cmake --build build

---

## Erlaubt

- `std::string`
- `enum class`
- Konstruktoren
- Referenzen
- `const`
- normale Stack-Objekte
- Standardbibliothek
- Google
- cppreference
- Compiler-Fehlermeldungen
- Dokumentation

---

## Noch nicht verwenden

- raw `new` / `delete`
- Smart Pointer
- Vererbung
- Templates
- Threads
- IPC
- große DeviceHub-Architektur

Keine unnötigen Abstraktionen wie:

- `IDevice`
- `DeviceFactory`
- `DeviceRegistry`

Wir bauen zunächst nur eine kleine `Device`-Klasse.

---

## Definition of Done

TASK-001 ist abgeschlossen, wenn:

- [ ] Projekt wird mit CMake erfolgreich konfiguriert
- [ ] Projekt kompiliert mit C++20
- [ ] `Device.hpp` und `Device.cpp` sind getrennt
- [ ] `Device` besitzt ID, Name und Status
- [ ] Status verwendet `enum class`
- [ ] Konstruktor initialisiert mindestens ID und Name
- [ ] Getter sind vorhanden
- [ ] `const` wurde sinnvoll eingesetzt
- [ ] mindestens zwei `Device`-Objekte werden in `main()` erzeugt
- [ ] Device-Informationen werden ausgegeben
- [ ] kein `new` / `delete` verwendet
- [ ] Programm läuft ohne Fehler

---

## Danach

Nach Abschluss:

1. Code nicht weiter optimieren.
2. Aktuellen Stand zum Review geben.
3. Gemeinsam Code Review durchführen.
4. Fehler/Verbesserungen zuerst verstehen.
5. Erst danach TASK-002 beginnen.