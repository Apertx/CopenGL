@ECHO OFF

SET CC=tcc
SET CFLAGS=-c -D__OPTIMIZE__ -Wall -Werror -Wunsupported -Wwrite-strings -Wimplicit-function-declaration
SET LDFLAGS=-lOPENGL32 -lGLU32 -Wl,-subsystem=windows

SET SOURCE_FILES=main texture wrap_wnd

SET BACKUP_DIR=backup\
SET BUILD_DIR=build\
SET OBJ_DIR=%BUILD_DIR%obj\
SET TARGET=%BUILD_DIR%app.exe
SET UPDATED=0
SET OBJECTS=

:Main
	ECHO [I] Start: %TIME%

	IF NOT EXIST %BACKUP_DIR% (
		MKDIR %BACKUP_DIR%
		ECHO [I] %BACKUP_DIR% created
	)
	IF NOT EXIST %BUILD_DIR% (
		MKDIR %BUILD_DIR%
		ECHO [I] %BUILD_DIR% created
	)
	IF NOT EXIST %OBJ_DIR% (
		MKDIR %OBJ_DIR%
		ECHO [I] %OBJ_DIR% created
	)

	SETLOCAL ENABLEDELAYEDEXPANSION||GOTO ErrorExpansion
	FOR %%s IN (%SOURCE_FILES%) DO (
		IF EXIST %OBJ_DIR%%%s.o (
			IF NOT EXIST %TARGET% (
				DEL /Q %OBJ_DIR%%%s.o
			) ELSE (
				IF EXIST %BACKUP_DIR%%%s.c (
					FC /LB1 %%s.c %BACKUP_DIR%%%s.c>NUL||DEL /Q %OBJ_DIR%%%s.o
				) ELSE (
					DEL /Q %OBJ_DIR%%%s.o
				)
			)
		)
		IF NOT EXIST %OBJ_DIR%%%s.o (
			COPY /Y %%s.c %BACKUP_DIR%%%s.c>NUL
			%CC% %CFLAGS% %%s.c -o%OBJ_DIR%%%s.o||GOTO ErrorCompile
			ECHO [I] %%s recompiled
			SET UPDATED=1
		)
		SET OBJECTS=!OBJECTS! %OBJ_DIR%%%s.o
	)

	IF %UPDATED% EQU 1 (
		%CC% %LDFLAGS%%OBJECTS% -o%TARGET%||GOTO ErrorLink
	) ELSE (
		ECHO [I] Compilation skipped
	)
	ENDLOCAL

	ECHO [I] Successfully completed
	START %TARGET%
	GOTO TheEnd

:ErrorExpansion
	ECHO [E] DelayExpansion is not supported (Windows 2000 and later)
	GOTO TheEnd

:ErrorCompile
	ECHO [E] Compilation failed
	GOTO TheEnd

:ErrorLink
	ECHO [E] Linking failed
	GOTO TheEnd

:TheEnd
	ECHO [I] Close: %TIME%
