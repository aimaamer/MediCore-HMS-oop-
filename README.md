**MEDICORE HOSPITAL MANAGEMENT SYSTEM**

MediCore is a comprehensive C++ Hospital Management System designed as an Object-Oriented Programming (OOP) project.
It manages three primary user roles, **Patients, Doctors, and Administrators**, and handles appointments, billing, prescriptions, and medical records through file storage. 

**Core Functionality :**

Multi-Role User Management: The system supports three distinct user roles—Patient, Doctor, and Admin—each with tailored menus for tasks like booking appointments, writing prescriptions, and managing hospital staff.

Persistent File-Based System: All hospital data is stored in and retrieved from .txt files, ensuring that every change is immediately saved and restored upon program restart.

Strict Technical Constraints: To meet academic requirements, the project is built without std::string, std::vector, or built-in string functions like strcmp(), relying instead on manual character array processing and custom template-based storage.

Robust Security & Validation: The system features a Validator class for strict input checks (IDs, dates, and contacts) and implements a session lock after 3 failed login attempts, which are then logged to a security_log.txt.

**How to Compile & Run Visual Studio (Windows)** — Recommended Create a new Empty C++ Project. Add all .h and .cpp files to the project. Link SFML: Go to Project → Properties → C/C++ → Additional Include Directories → add the SFML include/ path. Go to Linker → Additional Library Directories → add the SFML lib/ path. Go to Linker → Input → Additional Dependencies → add: sfml-graphics.lib sfml-window.lib sfml-system.lib sfml-audio.lib Copy the SFML .dll files into your project's output folder (same folder as the .exe). Make sure the assets/ folder and all .txt data files are in the same directory as the executable. Press Ctrl+F5 / F5 to build and run.

