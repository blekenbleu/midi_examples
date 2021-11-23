/**
 * Simple example MIDI class
 * author: chegewara
 */

#include "midiusb.h"   // ESP32TinyUSB
#include "song.h"

MIDIusb midi;

void setup() {
  Serial.begin(115200);
  midi.begin("midi ino");	// name that e.g. MidiView sees
  delay(1000);
/* Either this: */
  Serial.write("sizeof(song) = ");
  Serial.println(sizeof(song));
  if(midi.setSong(song, sizeof(song))) {
    Serial.write("invoking midi.playSong()\n");
    midi.playSong();
  } else Serial.write("midi.setSong() returned false\n");
 
}


// example melody as an array of note values
uint8_t note_sequence[] =
{
  74,78,81,86,90,93,98,102,57,61,66,69,73,78,81,85,88,92,97,100,97,92,
  88,85,81,78,74,69,66,62,57,62,66,69,74,78,81,86, 90,93,97,102,97,93,
  90,85,81,78,73,68,64,61,56,61,64,68,74,78,81,86,90,93,98,102
};

void midi_task(void)
{
  static uint32_t note_pos = 0;   // position in note_sequence[]
  static int previous = sizeof(note_sequence) - 1;
  static uint32_t start_ms = 0;

  if (0 == start_ms) {
    Serial.write("midi_task() invoked.\nsizeof(note_sequence) = ");
    Serial.println(sizeof(note_sequence));
  }

  // send a note every 1000 ms
  if (millis() - start_ms < 286)
    return; // not enough time

  start_ms += 286;

  // Send Note On for current position at full velocity (127) on channel 1.
  midi.noteON(note_sequence[note_pos], 127);

  // Send Note Off for previous note.
  midi.noteOFF(note_sequence[previous]);

  // Increment position
  previous = note_pos;
  note_pos++;

  // If we are at the end of the sequence, start over.
  if (note_pos >= sizeof(note_sequence)) {
    note_pos = 0;
//  Serial.write("\nmidi_task() looping..");
  }
}

void loop() {
  midi_task();      // or this
}
