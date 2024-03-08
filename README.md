# Avstandsbasert Varslingssystem

Dette prosjektet innebærer utvikling av et varslingssystem som bruker ultralydsensorer til å måle avstanden til objekter og gir lydsignalvarsel basert på denne avstanden. Systemet er utformet for å assistere i forskjellige praktiske applikasjoner, inkludert hjelpemidler for synshemmede, sikkerhetssystemer, eller automatiske navigasjonssystemer for robotikk.

## Funksjoner

- **Avstandsmåling**: Bruker en HC-SR04 ultralydsensor for å måle avstanden til nærmeste objekt.
- **Lydsignalvarsling**: En buzzer gir lydsignalvarsler. Frekvensen på lydsignalet er invers proporsjonal med avstanden til objektet, slik at nærmere objekter produserer hyppigere pip.
- **Deteksjon av Stasjonære Objekter**: Systemet kan identifisere om et objekt er stasjonært basert på gjennomsnittlige avstandsmålinger over tid.
- **Hastighetsberegning**: Beregner hastigheten til et objekt som nærmer seg eller fjerner seg fra sensoren.

## Komponenter

- Arduino UNO
- HC-SR04 Ultralydsensor
- Piezo Buzzer
- Kabler og koblingsbrett

## Oppsett

1. **Koble til Komponentene**:
   - `TRIG_PIN` på HC-SR04 kobles til pin 12 på Arduino.
   - `ECHO_PIN` på HC-SR04 kobles til pin 11 på Arduino.
   - `BUZZER_PIN` kobles til pin 10 på Arduino.

2. **Programvareoppsett**:
   - Last opp den vedlagte koden til din Arduino UNO ved hjelp av Arduino IDE.
   - Åpne Serial Monitor for å se avstandsmålinger og status for stasjonære objekter.

## Programvare

Kodeeksemplet inneholder funksjoner for å måle avstand, detektere stasjonære objekter, beregne objekthastigheter, og produsere lydsignaler basert på målte avstander. Den bruker også `millis()` for ikke-blokkerende forsinkelser, noe som gjør det mulig å utføre avstandsmålinger og lydsignalproduksjon samtidig.

### Viktige Funksjoner

- **`setup()`**: Initialiserer pins og starter seriell kommunikasjon.
- **`loop()`**: Utfører kontinuerlige avstandsmålinger, oppdaterer buzzerens oppførsel basert på avstand, og beregner hastigheten til bevegelige objekter.
- **`checkIfStationary(long currentDistance)`**: Sjekker om et objekt er stasjonært basert på avstandsmålinger.

## Bruksområder

- **Hjelpemidler for synshemmede**: Kan brukes som en del av en navigasjonshjelp for å varsle brukeren om nærliggende objekter.
- **Automatisk Navigasjonssystemer for Robotikk**: Hjelper roboter med å unngå hindringer og navigere i omgivelsene.
- **Sikkerhetssystemer**: Kan fungere som et enkelt inntrengingsvarsel i sikkerhetssensitive områder.

## Utvikling og Bidrag

Vi oppfordrer utviklere og teknologi-entusiaster til å bidra til dette prosjektet. Forbedringer, ny funksjonalitet, og ulike applikasjoner av dette varslingssystemet er velkomne.

### Lisens

Dette prosjektet er lisensiert under MIT-lisensen. Se `LICENSE` filen for detaljer.
