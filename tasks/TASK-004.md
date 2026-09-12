# TASK-004 – Unterschiedliche Device-Typen

## Ziel

Bisher verwaltet der `DeviceManager` ausschließlich Objekte vom Typ `Device`.

In einem realen DeviceHub können Geräte jedoch unterschiedliche Aufgaben haben. Ein Temperatursensor besitzt beispielsweise andere Eigenschaften und anderes Verhalten als ein GPIO-Gerät.

In dieser Aufgabe soll deshalb erstmals ein konkreter Gerätetyp auf Basis von `Device` entstehen.

## Lernziele

- Vererbung in C++
- Basisklasse und abgeleitete Klasse
- Konstruktoren bei Vererbung
- Zugriff auf geerbte öffentliche Funktionen
- Unterschied zwischen Basisobjekt und abgeleitetem Objekt
- Grenzen der aktuellen Container-Struktur erkennen

## Aufgabe 1 – Erster konkreter Device-Typ

Erstelle einen neuen Gerätetyp **TemperatureSensor**.

Ein `TemperatureSensor` ist ein `Device`, besitzt aber zusätzlich einen aktuellen Temperaturwert als Gleitkommazahl.

Er soll:
- die bestehenden Eigenschaften eines `Device` verwenden
- einen Temperaturwert speichern
- den Temperaturwert auslesen
- den Temperaturwert verändern können

Entscheide selbst, welche Konstruktoren und Funktionen dafür notwendig sind.

## Aufgabe 2 – Direkter Funktionstest

Erzeuge zunächst in `main()` einen `TemperatureSensor` unabhängig vom `DeviceManager`.

Teste:
- Zugriff auf geerbte Eigenschaften/Funktionen
- Temperatur setzen
- Temperatur wieder auslesen

## Aufgabe 3 – DeviceManager untersuchen

Versuche danach, deinen `TemperatureSensor` über die bestehende Schnittstelle zum `DeviceManager` hinzuzufügen.

Beobachte genau:

- Baut der Code?
- Kann der Manager das Objekt aufnehmen?
- Welche Informationen sind danach vorhanden?
- Kannst du über das gespeicherte Objekt weiterhin auf den Temperaturwert zugreifen?

Wenn etwas nicht wie erwartet funktioniert, ändere **nicht sofort die Architektur**. Untersuche zuerst die Ursache.

## Wichtig

TASK-004 implementiert noch nicht die endgültige Lösung für heterogene Devices.

Insbesondere sollst du nicht vorsorglich:
- den Container komplett umbauen
- Smart Pointer einführen
- eine neue Ownership-Architektur entwickeln

Falls die aktuelle Architektur an eine Grenze stößt, ist diese Erkenntnis Teil der Aufgabe.

## Eigene Recherche

Falls nötig, recherchiere selbst in normalen C++-Quellen und Dokumentation. Relevante Themen können sein:

- C++ inheritance
- base class / derived class
- constructors and inheritance
- object slicing

Versuche zuerst selbst zu verstehen, was passiert. Fertigen Lösungscode bekommst du von mir nur, wenn du ausdrücklich danach fragst.

## Definition of Done

TASK-004 ist für das Review bereit, wenn:

- `TemperatureSensor` existiert
- `TemperatureSensor` auf `Device` aufbaut
- ein Temperaturwert gespeichert, gelesen und verändert werden kann
- der direkte Test in `main()` funktioniert
- du versucht hast, den `TemperatureSensor` mit dem bestehenden `DeviceManager` zu verwenden
- du erklären kannst, was dabei mit den zusätzlichen Daten des `TemperatureSensor` passiert
- das Ergebnis bzw. ein auftretendes Architekturproblem nachvollziehbar getestet wurde

**Noch nicht taggen.**

Nach deiner Implementierung machen wir das Code-Review und entscheiden daraus den nächsten Architektur-Schritt.
