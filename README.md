# 🎮 Guess Pixel — micro-bit (C++/CODAL)

A two-player micro:bit game written in **C++** using the **Lancaster CODAL** toolchain.  
Player 1 selects a secret pixel. Player 2 moves a cursor to guess it. A correct guess shows a 😊.

## 🧩 How it works
- Player 1 picks a target LED (secret).
- Player 2 moves a cursor with buttons:
  - **A**: move left
  - **B**: move right
  - **A+B**: confirm guess
- Correct → show **smiley**.

---

## 🚀 How to build/run

### Lancaster University CODAL template
**1. Clone Lancaster micro:bit CODAL template** repository using: 
```bash
git clone https://github.com/lancaster-university/codal-microbit-v2.git
```
**2. Replace** the default `main.cpp` with either: 
- `SetterPlayer.cpp` → **Player 1** (chooses pixel). 
- `GuesserPlayer.cpp` → **Player 2** (guesses pixel).  

**3. Build** using:
```bash
python3 build.py
```
**4. Copy** the generated `.hex` to the **MICROBIT** USB drive.



---

## 🎛 Controls (default)

| Button          | Action |
|---------------|--------|
| **A**   | Move cursor left / up |
| **B**   | Move cursor right / down |
| **A+B**  | Select / Guess current pixel|

---

## 📌 Note

This game requires **two micro:bits** — one for the player setting the secret pixel and one for the player guessing. 

---

