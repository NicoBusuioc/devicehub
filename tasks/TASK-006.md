# TASK-006 – Virtuelle Funktionen und dynamische Bindung

## Ausgangssituation

Der `DeviceManager` speichert inzwischen unterschiedliche Gerätetypen ohne Object Slicing:

```cpp
std::vector<std::unique_ptr<Device>>
```

Die Objekte bleiben vollständig erhalten. Trotzdem kennt `printAllDevices()` aktuell nur die Informationen der Basisklasse `Device`.

Um die Temperatur auszugeben, muss `main()` momentan:

- wissen, dass das Gerät ein `TemperatureSensor` sein könnte,
- einen `dynamic_cast` durchführen,
- anschließend `getTemperature()` aufrufen.

Das ist problematisch: Wenn später zehn Gerätetypen existieren, müsste der aufrufende Code jeden konkreten Typ kennen.

## Ziel

Jedes Gerät soll selbst bestimmen können, wie seine Informationen ausgegeben werden.

Der `DeviceManager` soll über einen `Device`-Pointer arbeiten und trotzdem automatisch das Verhalten des tatsächlichen Objekttyps aufrufen.

## Lernziele

- virtuelle Memberfunktionen verstehen
- statische und dynamische Bindung unterscheiden
- `override` korrekt einsetzen
- polymorphes Verhalten über Basisklassen-Pointer verwenden
- verstehen, warum der virtuelle Destruktor bereits wichtig ist
- `dynamic_cast` vermeiden, wenn eigentlich polymorphes Verhalten benötigt wird

## Anforderungen

1. `Device` erhält eine geeignete `const`-Memberfunktion zur Ausgabe seiner Informationen.

2. Diese Funktion muss polymorph aufrufbar sein.

3. `TemperatureSensor` implementiert eigenes Verhalten für diese Funktion.

4. Bei einem normalen `Device` werden weiterhin mindestens diese Informationen ausgegeben:

   - ID
   - Name
   - `DeviceState`
   - `ConnectionState`

5. Bei einem `TemperatureSensor` wird zusätzlich die Temperatur ausgegeben.

6. `DeviceManager::printAllDevices()`:

   - kennt nur `Device`,
   - prüft keine konkreten Gerätetypen,
   - verwendet keinen `dynamic_cast`,
   - ruft die neue polymorphe Funktion auf.

7. Der `dynamic_cast`-Block in `main()` wird für die Ausgabe nicht mehr benötigt.

8. `Device` soll in diesem Task noch instanziierbar bleiben. Die Basisklasse wird also noch nicht abstrakt gemacht.

## Zu untersuchen

Bevor du implementierst, beantworte dir diese Fragen:

1. Welches Schlüsselwort braucht die Funktion in der Basisklasse, damit der tatsächliche Objekttyp entscheidet, welche Implementierung ausgeführt wird?

2. Welches Schlüsselwort sollte die abgeleitete Klasse verwenden, damit der Compiler die Überschreibung kontrolliert?

3. Müssen Funktionsname, Parameter und `const` exakt zusammenpassen?

4. Warum funktioniert der Aufruf über `Device*`, obwohl das tatsächliche Objekt ein `TemperatureSensor` ist?

5. Was würde passieren, wenn das entscheidende Schlüsselwort in der Basisklasse fehlt?

## Randbedingungen

- Keine Typprüfung über `dynamic_cast`, `typeid` oder eigene Type-Enums.
- Keine neuen Smart-Pointer-Typen.
- Der bestehende Ownership-Ansatz bleibt erhalten.
- Noch keine abstrakte Basisklasse.
- Keine fertige Gerätehierarchie für zukünftige Typen entwickeln.

## Erwartetes Verhalten

Sinngemäß:

```text
ID: 0 | CPU Temperatur | ENABLED | OFFLINE
ID: 1 | GPIO Controller | ENABLED | OFFLINE
ID: 2 | CAN Controller | ENABLED | OFFLINE
ID: 3 | Temperature Sensor | ENABLED | OFFLINE | Temperature: 20
```

Das genaue Format darf selbst bestimmt werden.

## Definition of Done

- Projekt baut ohne Fehler.
- Normale `Device`-Objekte werden korrekt ausgegeben.
- `TemperatureSensor` ergänzt automatisch die Temperatur.
- `DeviceManager` kennt `TemperatureSensor` nicht.
- Für die Ausgabe ist kein `dynamic_cast` mehr erforderlich.
- Die dynamische Auswahl der richtigen Funktion kann erklärt werden.

