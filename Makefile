CC       = CL.EXE
CFLAGS   = /MDd /W3 /Od
OFLAGS   = /MD /W3 /Ox
LFLAGS   = /subsystem:Windows /machine:i386 /manifest:no

SRCDIR   = Source
DEPDIR   = Dependency

SDL2     = $(DEPDIR)\SDL2\SDL2-2.0.5

INCL     = /I"$(SDL2)\include"
LIBS     = msvcrt.lib kernel32.lib SDL2.lib SDL2main.lib
LIBPATH  = /libpath:"$(SDL2)\lib\x86"

SRC      = $(SRCDIR)\main.c $(SRCDIR)\events.c $(SRCDIR)\graphics.c $(SRCDIR)\logic.c
EXE      = frog.exe


release:
	MKDIR Release
	$(CC) $(OFLAGS) $(INCL) $(SRC) $(LIBS) /link $(LFLAGS) $(LIBPATH) /out:"Release\$(EXE)"
	COPY /Y "$(SDL2)\lib\x86\SDL2.dll" Release
	DEL *.obj

debug:
	MKDIR Debug
	$(CC) $(CFLAGS) $(INCL) $(SRC) $(LIBS) /link $(LFLAGS) $(LIBPATH) /out:"Debug\$(EXE)"
	COPY /Y "$(SDL2)\lib\x86\SDL2.dll" Debug
	DEL *.obj

all: release debug

clean:
	-RMDIR /S/Q Debug Release