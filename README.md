
# Secure File Transfer Simulation

Technology: C++ Programming (Win32 SDK, DLL)

* Project Overview

  A Windows-based simulation project that demonstrates the concept of cryptography
  and system-level programming using the Win32 SDK.
  
  The project implements Caesar Cipher and XOR Cipher for encryption/decryption and
  performs file handling via Windows system calls instead of standard C library functions.
  
  The cryptographic logic is modularized into a Dynamic Link Library (DLL), making the
  functionality reusable by multiple client applications.
  
  This project showcases low-level programming, system calls, and DLL development in
  a practical and secure context.

* Key Features

  + File-based Encryption & Decryption
      * Supports secure encryption/decryption of text files.
  
  + Multiple Algorithms Implemented
      * Caesar Cipher (character shift-based substitution)
      * XOR Cipher (bitwise XOR with user-defined key)

  + System-Level File Handling
      * Uses Win32 SDK APIs (CreateFile, ReadFile, WriteFile, CloseHandle) instead
        of high-level C++ functions.

  + DLL Integration
      * Exported reusable functions through a custom DLL.
      * Client applications dynamically load and use encryption/decryption services.

  + Low-Level Programming Practice
      * Worked extensively with pointers, buffers, and string processing.
      * Strengthened debugging skills with Visual Studio and Windows tools.

* Skills Highlighted

  * Proficiency in C programming and Win32 SDK system programming.
  * Experience in DLL creation, exporting/importing functions, and client integration.
  * Strong understanding of Windows API for file I/0 and process handling.
  * Practical knowledge of cryptographic techniques (Caesar & XOR cipher).
  * Hands-on with modular project development and secure file transfer concepts.


* Example Usage

  * Encrypt a file
  encrypt.exe input.txt output.enc key
  
  * Decrypt a file
  decrypt.exe output.enc recovered.txt key

