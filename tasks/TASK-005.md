TASK-005 – Polymorphe Speicherung und Ownership

Ziel:
DeviceManager soll unterschiedliche von Device abgeleitete Typen verwalten können,
ohne Object Slicing.

Lernziele:
- Ownership verstehen
- unique_ptr kennenlernen
- Ownership mit std::move übertragen
- Lifetime von Objekten verstehen
- polymorphe Speicherung vorbereiten

Anforderungen:
- DeviceManager besitzt die Devices
- unterschiedliche abgeleitete Device-Typen müssen vollständig erhalten bleiben
- kein Object Slicing
- bestehende Funktionen wie getDeviceCount(), printAllDevices() und Suche entsprechend anpassen
- noch keine unnötige Einführung von virtual/abstract, solange sie für diesen Schritt nicht benötigt wird

Wichtig:
Die konkrete Container- und API-Lösung soll selbst erarbeitet werden.