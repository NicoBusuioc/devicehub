# TASK-003 – Device-Zustand verwalten

## Ziel

Der `DeviceHub` soll nicht nur Devices speichern und finden können, sondern auch den Zustand eines bereits vorhandenen Devices ändern können.

Jedes `Device` bekommt dafür einen Zustand:

- `Online`
- `Offline`

Ein neu erzeugtes Device soll standardmäßig `Offline` sein.

---

## Lerninhalt

In dieser Aufgabe beschäftigen wir uns vor allem mit:

- `enum class`
- Objektzustand innerhalb einer Klasse
- `const` bei Getter-Funktionen
- Objekte in einem `std::vector` verändern
- Unterschied zwischen:
  - Objekt/Kopie
  - Referenz
  - `const`-Referenz
- Rückgabewerte zur Fehlerbehandlung

---

## Anforderungen

### 1. Device-Zustand

Erweitere `Device` um einen geeigneten Typ für den Zustand eines Gerätes.

Benötigte Zustände:

```text
Online
Offline
```

Verwende dafür einen `enum class`.

Ein neu erzeugtes `Device` soll standardmäßig den Zustand `Offline` haben.

---

### 2. Zugriff auf den Zustand

`Device` soll Möglichkeiten bereitstellen, um:

- den aktuellen Zustand auszulesen
- den Zustand zu verändern

Überlege dabei selbst:

- Welche Funktionen brauchst du?
- Welche davon sollten `const` sein?
- Welche Parameterübergabe ist hier sinnvoll?

---

### 3. DeviceHub erweitern

Erweitere `DeviceHub` um folgende Funktion:

```cpp
bool setDeviceState(unsigned int id, DeviceState state);
```

Die Funktion soll anhand der ID das entsprechende Device suchen.

Wenn das Device gefunden wurde:

- Zustand ändern
- `true` zurückgeben

Wenn kein Device mit dieser ID existiert:

- nichts verändern
- `false` zurückgeben

---

### 4. Devices ausgeben

Erweitere `printAllDevices()`, sodass zusätzlich der aktuelle Zustand jedes Devices ausgegeben wird.

Beispiel:

```text
ID: 1, Name: Temperature Sensor, State: Online
ID: 2, Name: Door Sensor, State: Offline
```

Die genaue Formatierung ist dir überlassen.

---

## Randbedingungen

Für diese Aufgabe:

- bestehende Funktion `findDevice()` nicht entfernen
- Signatur von `findDevice()` nicht verändern
- keine zusätzliche `findDevice()`-Overload einbauen
- kein Pointer-basierter Workaround
- keine neue Bibliothek für dieses Problem verwenden

Wichtig:

```cpp
std::optional<Device> findDevice(unsigned int id) const;
```

liefert aktuell ein `Device` als Wert zurück.

Überlege beim Implementieren von `setDeviceState()` genau, ob du damit direkt das ursprüngliche Objekt im `DeviceHub` verändern kannst.

---

## Hinweise

Achte beim Durchlaufen des `std::vector<Device>` darauf, **was deine Schleifenvariable tatsächlich ist**.

Zum Beispiel gibt es einen wesentlichen Unterschied zwischen:

```cpp
Device device
```

und

```cpp
Device& device
```

und

```cpp
const Device& device
```

Versuche zunächst selbst zu erklären, was bei jeder Variante passiert und welche Variante du brauchst, wenn das originale Objekt im Vector verändert werden soll.

Ich gebe hier bewusst keine vollständige Implementierung vor.

---

## Testfälle

### Fall 1 – Standardzustand

Device erzeugen und hinzufügen.

Erwartung:

```text
State: Offline
```

### Fall 2 – Zustand ändern

Vorhandenes Device auf `Online` setzen.

Erwartung:

```text
setDeviceState(...) == true
```

und die anschließende Ausgabe zeigt:

```text
State: Online
```

### Fall 3 – Unbekannte ID

Versuche den Zustand einer nicht vorhandenen ID zu ändern.

Erwartung:

```text
setDeviceState(...) == false
```

Das Programm soll normal weiterlaufen.

---

## Definition of Done

TASK-003 ist abgeschlossen, wenn:

- `DeviceState` als `enum class` vorhanden ist
- jedes neue Device standardmäßig `Offline` ist
- der Zustand gelesen werden kann
- der Zustand verändert werden kann
- `DeviceHub::setDeviceState()` funktioniert
- ein vorhandenes Device tatsächlich im Container verändert wird
- eine unbekannte ID sauber mit `false` behandelt wird
- `printAllDevices()` den Zustand mit ausgibt
- das Projekt ohne Compiler- oder Linkerfehler baut
- die bestehenden Funktionen aus TASK-001 und TASK-002 weiterhin funktionieren

Nach der Implementierung folgt das Code Review, bevor TASK-003 getaggt wird.
