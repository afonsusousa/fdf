# 🏔️ FdF - Fil de Fer

A 3D wireframe viewer created for the 42 School curriculum. FdF (Fil de Fer) takes a file containing a grid of coordinates and height values and renders it in a 3D graphical representation using the MinilibX library.

This repository contains both the mandatory requirements and a bonus version with additional visual effects and an interactive UI.

---

## Features

### ✅ Implemented
- **Parsing:** Reads `.fdf` maps and translates the 2D data grid into a 3D environment, including color values.
- **Rendering:** Uses a custom implementation of Bresenham's line algorithm to draw the wireframes.
- **Projections:** 
  - Isometric (Default)
  - Orthographic
  - Cylindrical
  - Spherical
- **Transforms:** Smooth zoom, continuous X/Y/Z rotations, translation (panning), and Z-altitude (scale) modifications.
- **Interactive GUI (Bonus):** On-screen menu displaying current control states, projection modes, and an axis visualizer.
- **Visual Effects (Bonus):** 
  - *Wave / Ripple:* Vertex manipulation that creates movement across the grid.
  - *Bend:* Modifies the rendering matrix to create bending effects.
  - *Auto-rotation / DVD Bounce:* Pre-programmed continuous movement/rotation effects.
- **Event Handling:** Mouse and Keyboard (X11) hooks for movement and controls.
- **Audio (Bonus):** Background audio/sound effects integration.

---

## 📸 Screenshots

| Isometric View | Polar Projection |
| :---: | :---: |
| ![Isometric View](screenshots/isometric.png) | ![Polar View](screenshots/polar.png) |

| Wave Effect | Interactive GUI Menu |
| :---: | :---: |
| ![Wave Effect](screenshots/wave.png) | ![GUI Menu](screenshots/gui.png) |

---

## 🎥 Video Demo

![FdF Demo](screenshots/demo.gif)

---

## 🛠️ Compilation & Usage

### Prerequisites
You will need `make`, `gcc` (or `clang`), and the standard MinilibX dependencies (X11 and math libraries).

### Build
To compile the mandatory version:
```bash
make
```

To compile the bonus version:
```bash
make bonus
```

### Execution
Run the program by passing a valid `.fdf` map as an argument:
```bash
./fdf maps/42.fdf
```
*(Use `./fdf_bonus maps/42.fdf` if you compiled the bonus version)*

---

## Controls (Bonus)

Here are the primary keyboard mappings for navigating the 3D environment:

| Action | Key / Mouse |
| :--- | :--- |
| **Move/Pan** | `UP`, `DOWN`, `LEFT`, `RIGHT` (Arrow Keys) |
| **Zoom In/Out** | `+` (Plus) / `-` (Minus) or Scroll Wheel |
| **Rotate X Axis** | `W` / `S` |
| **Rotate Y Axis** | `A` / `D` |
| **Rotate Z Axis** | `Z` / `X` |
| **Scale Altitude (Z)**| `Page Up` / `Page Down` |
| **Change Projection** | `I` (Isometric), `O` (Orthographic), `G` (Spherical), `C` (Cylindrical) |
| **Reset View** | `R` |
| **Toggle Rendering Mode** | `M` |
| **Exit** | `ESC` or `Q` |
