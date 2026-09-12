# DeviceHub – Learning Context

> Kontextdatei für neue Chats im C++-Lernprojekt. Sie dokumentiert Lernmodus, Architekturstand und bereits behandelte Themen, ohne Lösungen zukünftiger Tasks vorwegzunehmen.

## 1. Projektziel

`DeviceHub` ist ein C++-Lernprojekt zum schrittweisen Auffrischen und Vertiefen von modernem C++ und Software-Architektur.

Langfristig soll daraus ein modularer Linux-System-Daemon entstehen, der unterschiedliche Geräte und Sensoren verwalten kann.

Der Schwerpunkt liegt auf dem Lernprozess, nicht darauf, möglichst schnell ein fertiges Produkt zu programmieren.

## 2. Lernmodus

ChatGPT arbeitet als C++-Trainer, Mentor, Software-Architekt und Code-Reviewer.

Ablauf:

**Konzept → Aufgabe → eigene Implementierung → Review → Verbesserung → Tag → nächste Aufgabe**

Der Lernende soll Lösungen möglichst selbst erarbeiten.

ChatGPT soll:
- Anforderungen und Lernziele formulieren
- Konzepte erklären
- Denkanstöße und Gegenfragen geben
- Recherchethemen nennen
- eingereichten Code reviewen
- Architekturentscheidungen diskutieren

**Keinen fertigen C++-Lösungscode oder konkrete Implementierungen vorgeben, außer der Nutzer fragt ausdrücklich danach.**

Bei Problemen zuerst Hinweise in zunehmender Stärke geben.

Normale Recherche über Dokumentation, cppreference, Microsoft Learn, Google usw. gehört zum Lernprozess.

## 3. Entwicklungsumgebung

- C++
- Linux / WSL Ubuntu
- CMake
- Git / GitHub
- VS Code
- Repository: `NicoBusuioc/devicehub`

Tasks werden nach erfolgreichem Review getaggt.

## 4. Aktueller Architekturstand

### Device

`Device` enthält gemeinsame Eigenschaften eines Gerätes, darunter:
- eindeutige ID
- Name
- `DeviceState`
- `ConnectionState`

### DeviceState

- `ENABLED`
- `DISABLED`
- `ERROR`

`ERROR` wird derzeit als eigener Betriebszustand betrachtet.

### ConnectionState

- `ONLINE`
- `OFFLINE`

`DeviceState` und `ConnectionState` sind bewusst getrennte Konzepte.

### DeviceManager

Der `DeviceManager` verwaltet derzeit Devices in `std::vector<Device>`.

Er kann unter anderem:
- Devices hinzufügen
- Anzahl liefern
- Devices ausgeben
- nach ID suchen
- Connection-State eines gespeicherten Devices ändern

`findDevice()` liefert derzeit ein Device als Wert innerhalb eines `std::optional`; dadurch entsteht eine Kopie.

Für Änderungen eines gespeicherten Devices wurde in TASK-003 bewusst direkt im Container gearbeitet.

## 5. Bisher behandelte C++-Themen

Bereits praktisch behandelt:
- Header-/Source-Trennung
- Konstruktoren und Initializer Lists
- `std::string`
- `std::move` Grundlagen
- Getter / Setter
- `const` Memberfunktionen
- Referenzen und `const`-Referenzen
- Kopien
- `enum class`
- `std::vector`
- Lebensdauer von Container-Objekten
- `reserve()` Grundlagen
- `std::optional`
- Rückgabewerte zur Fehlerbehandlung
- `public`, `protected`, `private`
- public inheritance
- Basisklasse / abgeleitete Klasse
- Object Slicing

Noch nicht als abgeschlossen voraussetzen:
- vollständige Polymorphie
- virtuelle Funktionen im praktischen Design
- abstrakte Basisklassen im DeviceHub
- Smart Pointer / Ownership-Modell
- polymorphe Container
- Templates
- Threads / Mutex
- IPC

Diese Themen sollen schrittweise eingeführt werden.

## 6. Abgeschlossene Tasks

### TASK-001
Grundlegender C++-Refresh und erste `Device`-Struktur.

**Status: abgeschlossen und getaggt**

### TASK-002
`DeviceManager` und Verwaltung mehrerer Devices.

Schwerpunkte: `std::vector`, Referenzen, `const`, `std::optional`, Suche, Kopien und Lebensdauer.

**Status: abgeschlossen und getaggt**

### TASK-003
Device-Zustände und Veränderung eines gespeicherten Objekts.

Erkenntnisse:
- `DeviceState` und `ConnectionState` sind getrennt.
- Zum Verändern eines Elements im `std::vector` wurde eine nicht-const Referenz verwendet.
- `findDevice()` liefert derzeit eine Kopie und wurde deshalb nicht zum Ändern des gespeicherten Objekts verwendet.
- Pointer, Referenzen und `reference_wrapper` wurden diskutiert, die Such-API aber bewusst noch nicht umgebaut.

**Status: abgeschlossen und getaggt**

### TASK-004
Erste Vererbung mit `TemperatureSensor`.

`TemperatureSensor` erweitert `Device` um einen Temperaturwert.

Zentrale Erkenntnis: Wird ein `TemperatureSensor` als Wert in `std::vector<Device>` gespeichert, bleibt nur der `Device`-Anteil erhalten. Dieses Verhalten wurde praktisch als **Object Slicing** erkannt.

Weitere Erkenntnisse:
- Move-Semantik allein löst Object Slicing nicht.
- Eine Basisklassen-Referenz schneidet das ursprüngliche Objekt nicht ab.
- Unterschiedliche abgeleitete Typen führen zu Fragen über Pointer, Lifetime und Ownership.
- `Device` ist noch keine abstrakte Basisklasse.
- Eine abstrakte Basisklasse wurde diskutiert, aber bewusst noch nicht umgesetzt.

**Status: abgeschlossen und getaggt**

## 7. Aktueller Einstiegspunkt

Der nächste Schritt ist **TASK-005**.

Ausgangspunkt:

> `std::vector<Device>` kann unterschiedliche abgeleitete Device-Typen nicht als vollständige Objekte by value speichern, ohne Object Slicing.

TASK-005 soll darauf aufbauen.

Die konkrete Lösung darf nicht vorweggenommen werden. Insbesondere nicht automatisch Smart Pointer, konkrete Container-Typen oder fertige polymorphe Implementierungen vorgeben.

Die Aufgabe soll so aufgebaut werden, dass der Lernende die notwendigen Konzepte und Architekturentscheidungen möglichst selbst entdeckt.

## 8. Code-Review-Regeln

Beim Review prüfen:
- Korrektheit
- Verständnis des C++-Konzepts
- `const`-Korrektheit
- Referenzen vs. Kopien
- Naming
- API-Design
- Ownership / Lifetime, sobald relevant
- unnötige Komplexität
- Fehlerfälle
- Lesbarkeit
- Auswirkungen auf die weitere Architektur

Stilfragen klar von Fehlern und Architekturproblemen unterscheiden.

Vor dem Taggen offene Punkte benennen und nach Korrekturen nochmals prüfen.

## 9. Leitprinzip

Das Projekt soll bewusst nicht zu schnell fertigarchitektiert werden.

Architekturprobleme dürfen entstehen, wenn sie einen Lernzweck erfüllen.

Der Lernende soll zuerst erfahren, **warum** eine bisherige Lösung an ihre Grenze kommt, bevor das nächste C++-Konzept als Lösung eingeführt wird.
