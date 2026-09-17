# TASK-007 – Abstrakte Basisklasse und konkrete Gerätetypen

## Ausgangssituation

`Device` übernimmt aktuell zwei Rollen:

1. gemeinsame Basis für alle Gerätetypen,
2. selbst instanziierbarer konkreter Gerätetyp.

Dadurch ist beispielsweise Folgendes möglich:

```cpp
std::make_unique<Device>(...)
```

Architektonisch stellt sich aber die Frage:

> Gibt es in DeviceHub wirklich ein allgemeines „Device“, oder sollte jedes Objekt immer einen konkreten Gerätetyp besitzen?

`TemperatureSensor` besitzt bereits eigenes Verhalten. Die anderen Geräte werden momentan jedoch direkt als `Device` erzeugt.

## Ziel

`Device` soll nur noch die gemeinsame Basis der Gerätehierarchie darstellen und nicht mehr direkt instanziiert werden können.

Für einfache Geräte ohne zusätzliche Daten soll ein eigener konkreter Gerätetyp entstehen.

## Lernziele

- abstrakte Basisklassen verstehen
- reine virtuelle Funktionen kennenlernen
- Unterschied zwischen abstrakter und konkreter Klasse verstehen
- Compilerfehler beim Instanziieren abstrakter Klassen interpretieren
- gemeinsame Daten und typabhängiges Verhalten sinnvoll trennen
- bestehende Polymorphie weiterverwenden

## Anforderungen

1. `Device` wird zu einer abstrakten Basisklasse.

2. Verwende dafür eine bereits vorhandene virtuelle Funktion, deren Implementierung jeder konkrete Gerätetyp bereitstellen muss.

3. Direkte Erzeugung eines `Device` muss anschließend vom Compiler verhindert werden.

4. Erstelle einen konkreten Gerätetyp für einfache Geräte, die aktuell keine zusätzlichen Daten benötigen.

   Beispiele dafür sind momentan:

   - GPIO Controller
   - CAN Controller

   Den Namen dieser Klasse darfst du selbst festlegen.

5. Der neue Gerätetyp:

   - erbt öffentlich von `Device`,
   - besitzt vorerst keine zusätzlichen Membervariablen,
   - implementiert die erforderliche virtuelle Funktion,
   - gibt die gemeinsamen Geräteinformationen aus.

6. `TemperatureSensor` bleibt ein konkreter Gerätetyp und soll weiterhin zusätzlich seine Temperatur ausgeben.

7. Passe `main()` so an, dass kein `Device` mehr direkt erzeugt wird.

8. Der `DeviceManager` soll nicht verändert werden müssen. Er arbeitet weiterhin ausschließlich mit:

```cpp
std::unique_ptr<Device>
```

## Vor der Implementierung untersuchen

Beantworte dir dabei diese Fragen:

1. Wie kennzeichnet man eine reine virtuelle Funktion?

2. Warum macht bereits eine einzige reine virtuelle Funktion die gesamte Klasse abstrakt?

3. Kann eine abstrakte Klasse trotzdem:

   - Konstruktoren besitzen?
   - Membervariablen besitzen?
   - implementierte Memberfunktionen besitzen?

4. Wer ruft den Konstruktor von `Device` auf, wenn `Device` selbst nicht mehr instanziiert werden darf?

5. Warum kann `DeviceManager` weiterhin `std::unique_ptr<Device>` speichern?

6. Welche Funktion wird bei folgendem Aufruf ausgeführt?

```cpp
device->printDeviceInfo();
```

7. Was passiert, wenn eine neue abgeleitete Klasse die reine virtuelle Funktion nicht implementiert?

## Randbedingungen

- Keine Änderungen am Ownership-Modell.
- Keine neuen Smart-Pointer-Typen.
- Kein `dynamic_cast`, `typeid` oder eigener Type-Enum.
- Keine zusätzliche Gerätehierarchie auf Vorrat entwickeln.
- Der neue konkrete Gerätetyp soll nur das aktuelle Problem lösen.
- `printCommonInfo()` darf weiterhin zur Vermeidung von Code-Duplizierung verwendet werden.

## Erwartetes Verhalten

Die Ausgabe soll funktional gleich bleiben:

```text
ID: 0 | CPU Temperatur | ENABLED | OFFLINE
ID: 1 | GPIO Controller | DISABLED | ONLINE
ID: 2 | CAN Controller | DISABLED | OFFLINE
ID: 3 | Temperature Sensor | ENABLED | ONLINE | 20°C
```

Der wichtige Unterschied liegt diesmal in der Architektur:

- `Device` beschreibt nur noch die gemeinsame Schnittstelle.
- Tatsächlich erzeugt werden ausschließlich konkrete Gerätetypen.

## Definition of Done

- Das Projekt baut ohne Fehler.
- `Device` kann nicht mehr direkt instanziiert werden.
- Alle gespeicherten Objekte besitzen einen konkreten Typ.
- Der neue einfache Gerätetyp wird korrekt ausgegeben.
- `TemperatureSensor` funktioniert weiterhin polymorph.
- `DeviceManager` kennt keine konkreten Gerätetypen.
- Du kannst erklären, warum ein Pointer auf eine abstrakte Klasse erlaubt ist, ein Objekt dieser Klasse aber nicht.

## Abgabe

Implementiere die Aufgabe selbst und pushe danach einen Commit wie:

```text
Task007 to review
```

Danach folgt das Code-Review vor dem Taggen.
