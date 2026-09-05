# TASK-002 – DeviceManager und STL-Container

## Ziel

Der DeviceHub soll nicht mehr nur einzelne `Device`-Objekte in `main()`
kennen.

Stattdessen soll eine neue Klasse `DeviceManager` mehrere Devices verwalten.

Aktuelle Architektur:

DeviceHub
├── Device
└── DeviceManager
        |
        └── mehrere Devices

Der `DeviceManager` soll Devices speichern, suchen und ausgeben können.

Noch keine Vererbung, Smart Pointer oder Threads.

---

# Lerninhalt

Mit dieser Aufgabe werden folgende C++-Themen praktisch behandelt:

- `std::vector`
- Range-based `for`
- Referenzen
- `const`-Referenzen
- `const` Member-Funktionen
- Container und Objekt-Lifetime
- `std::optional`
- Header-/Source-Aufteilung
- Trennung von Verantwortlichkeiten

Zusätzlich wiederholen wir:

- Klassen
- Konstruktoren
- `enum class`
- `std::string`
- CMake

---

# Projektstruktur

Die bestehende Struktur wird erweitert:

devicehub/
├── CMakeLists.txt
├── TASK-001.md
├── TASK-002.md
└── src/
    ├── main.cpp
    ├── Device.hpp
    ├── Device.cpp
    ├── DeviceManager.hpp
    └── DeviceManager.cpp

---

# Anforderungen

## 1. DeviceManager

Erstelle eine neue Klasse:

    DeviceManager

Sie soll mehrere `Device`-Objekte verwalten.

Überlege selbst, welcher STL-Container dafür geeignet ist.

Für diese Aufgabe soll letztendlich verwendet werden:

    std::vector

Bevor du ihn verwendest, solltest du aber verstehen:

- Was speichert `std::vector`?
- Wem gehören die darin gespeicherten Objekte?
- Was passiert beim Hinzufügen eines Elements?
- Was bedeutet es, wenn der Vector wächst?

Diese Fragen müssen noch nicht vollständig vor der Implementierung
beantwortet werden. Wir werden sie beim Review behandeln.

---

## 2. Devices hinzufügen

Der `DeviceManager` soll eine Funktion besitzen, über die ein Device
hinzugefügt werden kann.

Konzeptionell:

    DeviceManager manager;

    Device cpu(...);

    manager.addDevice(cpu);

Die genaue Funktionssignatur sollst du selbst bestimmen.

Überlege insbesondere:

Soll `addDevice()` das Device bekommen als:

    Device

oder

    Device&

oder

    const Device&

Pointer oder Smart Pointer sollen für TASK-002 noch nicht verwendet werden.

---

## 3. Anzahl der Devices

Der `DeviceManager` soll zurückgeben können, wie viele Devices aktuell
gespeichert sind.

Beispiel:

    manager.getDeviceCount()

Bei drei Devices soll entsprechend `3` zurückgegeben werden.

Überlege selbst, welcher Rückgabetyp sinnvoll ist.

Hinweis:

Schau dir an, welchen Typ `std::vector::size()` zurückgibt.

---

## 4. Alle Devices ausgeben

Alle gespeicherten Devices sollen ausgegeben werden können.

Dabei soll mindestens einmal ein:

    range-based for loop

verwendet werden.

Beispielhafte Ausgabe:

    ID: 0 | CPU Temperature | ENABLED
    ID: 1 | GPIO Controller | DISABLED
    ID: 2 | CAN Interface | ERROR

Die genaue Formatierung ist frei.

Achte beim Range-based Loop bewusst darauf, ob du schreibst:

    for (Device device : ...)
    
oder:

    for (Device& device : ...)
    
oder:

    for (const Device& device : ...)

Entscheide selbst, welche Variante für eine reine Ausgabe sinnvoll ist.

---

## 5. Device anhand der ID suchen

Der `DeviceManager` soll nach einem Device anhand seiner ID suchen können.

Konzeptionell:

    manager.findDevice(...)

Problem:

Ein Device mit dieser ID muss nicht existieren.

Beispiel:

    findDevice(1)      -> Device existiert
    findDevice(9999)   -> Device existiert nicht

Für diese Aufgabe soll dafür:

    std::optional

verwendet werden.

Bevor du implementierst, informiere dich kurz über:

    std::optional

und überlege:

Was könnte `std::optional` hier ausdrücken?

Die genaue Form des Rückgabetyps sollst du zunächst selbst überlegen.

---

# Wichtige Designfrage

Bei `findDevice()` entsteht eine interessante Entscheidung.

Möglich wäre konzeptionell:

    std::optional<Device>

oder eine Variante, bei der wir nicht das komplette Device kopieren.

Überlege zunächst selbst:

- Was passiert bei `std::optional<Device>`?
- Bekomme ich das ursprüngliche Device?
- Oder bekomme ich eine Kopie?
- Was wäre problematisch, wenn ich das gefundene Device später verändern möchte?

Noch keine Pointer-Lösung googeln oder einbauen.

Wenn du an dieser Stelle unsicher wirst, frag nach.

Diese Frage werden wir gemeinsam behandeln.

---

# main()

`main()` soll nicht mehr selbst die Verwaltung der Devices übernehmen.

Erzeuge einen:

    DeviceManager

und mindestens drei Devices.

Zum Beispiel:

- CPU Temperature
- GPIO Controller
- CAN Interface

Füge sie dem Manager hinzu.

Anschließend:

1. Anzahl der Devices ausgeben
2. alle Devices ausgeben
3. nach einer existierenden ID suchen
4. nach einer nicht existierenden ID suchen
5. beide Fälle sinnvoll behandeln

---

# CMake

`DeviceManager.cpp` muss Teil des Builds werden.

Die bestehende C++20-Konfiguration bleibt bestehen.

Build weiterhin mit:

    cmake -S . -B build
    cmake --build build

Wenn nur C++-Dateien geändert wurden, reicht normalerweise:

    cmake --build build

---

# Erlaubt

- `std::vector`
- `std::optional`
- `std::string`
- `enum class`
- Referenzen
- `const`
- Range-based for loops
- Konstruktoren
- STL
- Google
- cppreference
- Compiler-Fehlermeldungen
- Dokumentation

---

# Noch nicht verwenden

- `new`
- `delete`
- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`
- Vererbung
- Templates
- Threads
- Mutex
- IPC

Insbesondere:

Nicht versuchen, das Ownership-Problem bereits mit Smart Pointern zu lösen.

Wir wollen zuerst sehen, wie sich normale C++-Objekte in einem Container
verhalten.

---

# Hinweise

## std::vector

Falls die Syntax vergessen wurde, suche beispielsweise nach:

    cppreference std::vector

Wichtige Operationen für diese Aufgabe könnten sein:

    push_back(...)
    size()

Nicht einfach alle verfügbaren Vector-Funktionen lernen.

---

## std::optional

`std::optional<T>` kann konzeptionell ausdrücken:

    entweder T vorhanden
    oder kein T vorhanden

Beispielsweise:

    std::optional<int>

kann einen Integer enthalten oder leer sein.

Wie wir das sinnvoll mit `Device` kombinieren, soll Teil der Aufgabe sein.

---

# Fragen für das spätere Review

Nach deiner Implementierung solltest du über folgende Fragen nachdenken können:

1. Wem gehören die Devices im `std::vector`?

2. Wird bei `addDevice()` ein Device kopiert?

3. Was ist der Unterschied zwischen:

       for (Device device : devices)

   und:

       for (const Device& device : devices)

4. Was passiert mit einem `std::vector`, wenn seine Kapazität nicht mehr
   ausreicht?

5. Was bedeutet das für Referenzen auf Elemente innerhalb des Vectors?

6. Warum ist `std::optional` für `findDevice()` interessant?

7. Was bedeutet es, wenn `std::optional<Device>` zurückgegeben wird?

Du musst diese Fragen nicht beantworten, bevor du programmierst.

Wir behandeln sie anhand deiner tatsächlichen Implementierung.

---

# Definition of Done

TASK-002 ist abgeschlossen, wenn:

- [ ] `DeviceManager.hpp` existiert
- [ ] `DeviceManager.cpp` existiert
- [ ] `DeviceManager` verwendet `std::vector`
- [ ] Devices können hinzugefügt werden
- [ ] mindestens drei Devices werden verwaltet
- [ ] Anzahl der Devices kann abgefragt werden
- [ ] Range-based for loop wird verwendet
- [ ] Devices können anhand ihrer ID gesucht werden
- [ ] `std::optional` wird für den Suchfall verwendet
- [ ] vorhandene ID wird korrekt behandelt
- [ ] nicht vorhandene ID wird korrekt behandelt
- [ ] `const` und Referenzen wurden bewusst eingesetzt
- [ ] CMake baut das gesamte Projekt
- [ ] Programm läuft ohne Fehler

---

# Git / Abschluss

Wenn TASK-002 nach dem Code Review abgeschlossen ist:

    git tag -a task-002-complete -m "TASK-002 completed"

Danach den Tag pushen.

Noch nicht taggen, bevor das Review abgeschlossen ist.

---

# Danach

Nach TASK-002 führen wir ein Code Review durch.

Dabei schauen wir uns insbesondere an:

- Kopien von Objekten
- Referenzen
- Lifetime
- Verhalten von `std::vector`
- Iterator-/Reference-Invalidation
- `std::optional`
- Ownership

Diese Erkenntnisse bilden die Grundlage für die nächsten Aufgaben,
in denen wir uns schrittweise Smart Pointern, RAII und Move Semantics
nähern.