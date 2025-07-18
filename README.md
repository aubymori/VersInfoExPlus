# VersInfoExPlus
This is a fork of [VersInfoEx](https://www.codeproject.com/Articles/118909/Windows-7-File-properties-Version-Tab-Shell-Extens)
that aims to be as accurate to the Windows XP Version tab as possible.

## Changes from VersInfoEx
- Don't display the file description and legal copyright duplicately in
  the list box
- Use localized names for the list box value names, rather than the internal version
  info names
- Fix dialog layout to be completely accurate; the old one was eyeballed
- Japanese translation

## Installation
1. Grab [the latest release](https://github.com/aubymori/VersInfoExPlus/releases/tag/1.1.0) and put
   VersInfoExPlus.dll in a safe spot where it won't be deleted.
2. Open an administrator command prompt and navigate to that folder using `cd`.
3. Run `regsvr32 .\VersInfoExPlus.dll`.

## Uninstallation
1. Open an administrator command prompt and navigate to the folder where
   VersInfoExPlus.dll resides using `cd`.
2. Run `regsvr32 /u .\VersInfoExPlus.dll`.
3. Delete VersInfoExPlus.dll.