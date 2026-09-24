# TASK-008 – Device entfernen und Ownership übertragen

## Ausgangslage

Der `DeviceManager` verwaltet unterschiedliche konkrete Devices polymorph über
`std::unique_ptr<Device>`.

Beim Hinzufügen wird die Ownership an den `DeviceManager` übertragen. Bisher fehlt
jedoch eine saubere Möglichkeit, ein Device wieder aus dem Manager zu entnehmen.

Ein einfaches Löschen wäre möglich. Für diese Aufgabe soll das entfernte Device aber
an den Aufrufer zurückgegeben werden. Dadurch kann der Aufrufer selbst entscheiden,
ob das Device zerstört, weiterverwendet oder später erneut eingefügt wird.

## Lernziele

- exklusiven Besitz mit `std::unique_ptr` weiter vertiefen
- Ownership bewusst zwischen Objekten übertragen
- verstehen, warum ein `std::unique_ptr` nicht kopiert werden kann
- `std::move` gezielt und begründet einsetzen
- ein Element sicher aus einem `std::vector` entfernen
- Lebensdauer eines polymorphen Objekts nachvollziehen
- Fehlerfälle in einer API ausdrücken

## Aufgabe

Erweitere den `DeviceManager` um eine Funktion, die ein Device anhand seiner ID aus
dem Manager entfernt und die Ownership an den Aufrufer überträgt.

Nach erfolgreichem Entfernen gilt:

- Das Device befindet sich nicht mehr im `DeviceManager`.
- Der Aufrufer besitzt das vollständige konkrete Objekt.
- Das Objekt darf beim Entfernen nicht unnötig neu erzeugt oder kopiert werden.
- Polymorphie muss erhalten bleiben.

Wird keine passende ID gefunden, muss die Funktion diesen Fehlerfall eindeutig
ausdrücken.

## Anforderungen

1. Ergänze im `DeviceManager` eine passende öffentliche Funktion zum Entfernen eines
   Devices anhand seiner ID.
2. Wähle selbst einen geeigneten Rückgabetyp.
3. Übertrage bei Erfolg die bestehende Ownership aus dem Container an den Aufrufer.
4. Entferne anschließend den betreffenden Eintrag korrekt aus dem Container.
5. Behandle eine unbekannte ID, ohne ein Dummy-Device zu erzeugen.
6. Bestehende Funktionen und das polymorphe Verhalten müssen weiterhin funktionieren.
7. Ergänze in `main()` einen nachvollziehbaren Testablauf.

## Testablauf in `main()`

Dein Programm soll mindestens zeigen:

1. Mehrere unterschiedliche konkrete Devices werden hinzugefügt.
2. Die Anzahl vor dem Entfernen wird ausgegeben oder geprüft.
3. Ein vorhandenes Device wird entfernt.
4. Die Anzahl danach ist um eins kleiner.
5. Das entfernte Device kann über den zurückgegebenen Besitz weiterhin polymorph
   verwendet werden.
6. Das Entfernen einer unbekannten ID wird getestet.
7. Es ist erkennbar, wann das entfernte Objekt schließlich zerstört wird.

## Einschränkungen

- kein `new` oder `delete` im Anwendungscode
- keine Raw Pointer als Ownership-Lösung
- kein `shared_ptr`
- kein `dynamic_cast`, `typeid` oder eigener Typ-Enum zur Unterscheidung
- keine Kopie eines Devices als Ersatz für die Besitzübertragung
- keine Threads, Mutexes oder IPC
- keine neue große Klassenhierarchie

## Vor der Implementierung beantworten

1. Wer besitzt ein Device direkt vor dem Entfernen?
2. Wer soll es direkt nach erfolgreichem Entfernen besitzen?
3. Warum kann der Pointer nicht einfach aus dem Container kopiert werden?
4. Was würde passieren, wenn zuerst der Vektoreintrag gelöscht und erst danach auf
   dessen Pointer zugegriffen wird?
5. Muss für „nicht gefunden“ zwingend ein zusätzliches `std::optional` verwendet
   werden, oder kann ein möglicher Rückgabetyp diesen Zustand bereits ausdrücken?

## Recherchehinweise

Recherchiere bei Bedarf:

- Move-Semantik von `std::unique_ptr`
- moved-from state eines `std::unique_ptr`
- `std::vector::erase`
- Iterator-Gültigkeit nach `erase`
- Rückgabe eines `std::unique_ptr` aus einer Funktion

Suche zunächst nur nach den Konzepten. Übernimm keine fertige Gesamtlösung für die
Aufgabe.

## Definition of Done

- Das Projekt baut ohne Warnungen.
- Ein vorhandenes Device wird tatsächlich aus dem Manager entnommen.
- Die Ownership liegt anschließend eindeutig beim Aufrufer.
- Der konkrete dynamische Typ und das polymorphe Verhalten bleiben erhalten.
- Eine unbekannte ID wird korrekt behandelt.
- Es gibt keine manuelle Speicherverwaltung und keinen doppelten Besitz.
- Die fünf Verständnisfragen sind beantwortet.
- Die Änderungen sind in einem sauberen Commit mit der Nachricht
  `Task008 to review` gepusht.

Noch nicht taggen. Nach dem Push folgt zuerst das Review.
