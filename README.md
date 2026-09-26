# Custom Start Button (Windhawk Mod)

Replace the Windows Start button with your own custom image or photo on Windows 10 and Windows 11, while preserving 100% of Start Menu functionality.

**Author**: RobsHs ([github.com/robshs](https://github.com/robshs))

---

## Features

* **Custom Image**: PNG, JPG, JPEG, BMP, GIF, or WEBP support.
* **100% Functionality Intact**:
  * Left click: opens Start Menu.
  * Right click: opens Win+X Quick Link menu.
  * Windows key and shortcuts (Win+A, Win+S, Win+X) work seamlessly.
* **Image Scaling**: Contain (Fit), Cover (Fill), Stretch, and Original.
* **Border Radius**: 0% (square) to 50% (circle) using hardware-accelerated clipping.
* **Hover & Pressed Transitions**: Hardware-accelerated scale, brightness, and opacity effects (respects Windows animation settings).
* **Multi-Monitor**: Automatically supports secondary taskbars.
* **Safe Fallback**: Instantly restores default Windows logo if image path is invalid or missing.
* **Dual Architecture**:
  * Windows 11: Taskbar XAML Island visual tree hook and DirectComposition.
  * Windows 10: Win32 `Shell_TrayWnd` child window subclassing with GDI+ double-buffered anti-aliasing.

---

## Installation & Usage

1. Install [Windhawk](https://windhawk.net/).
2. Open Windhawk and create a new local mod or open the mod editor.
3. Paste the contents of `mod.wh.cpp`.
4. Click **Compile** (`Ctrl+B`).
5. Open the mod **Settings**:
   * Set **Custom image path** (e.g. `%USERPROFILE%\Pictures\my-logo.png`).
   * Set **Border radius** to `50` for a circular button.
   * Configure scaling and hover effects as desired.
6. Click **Save**: your Start button updates immediately.

---

## Project Structure

```
.
├── mod.wh.cpp             # Complete Windhawk mod file (ready to compile)
├── .gitignore
├── README.md
└── src/
    ├── config.h           # Configuration structure & enums
    ├── config.cpp         # Settings loader
    ├── windows_compat.h   # Windows OS build detection
    ├── windows_compat.cpp # OS version implementation
    ├── image_loader.h     # URI & path helpers
    ├── image_loader.cpp   # File & environment path expansion
    ├── start_button_win11.h # Windows 11 subsystem declarations
    ├── start_button_win10.h # Windows 10 subsystem declarations
    └── main.cpp           # Modular architecture demo
```

---

## License

This project is licensed under the MIT License.
