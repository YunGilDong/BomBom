//---------------------------------------------------------------------------
// wzFile.h
// Author       : Park Dong Ro
// LastModify   : 2004.12
// Comment      :
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef WZ_FILE_H
#define WZ_FILE_H
//---------------------------------------------------------------------------

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __WIN32__
#include <vcl.h>
#include <sys/locking.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#endif


int  file_lock(int fd, short lock_mode);
int  file_unlock(int fd);
int  file_islocked(int fd, short lock_mode);
int  file_force_unlock(const char *file);
long fsize(const char *file );
int  createFile(const char *path);
void closeFile(int fd);
int  readFile(const char *path, long offset, void *buf, int size);
int  writeNewFile(const char *path, long offset, void *buf, int size);
int  writeFile(const char *path, long offset, void *buf, int size);
int  writeFile(int fd, long offset, void *buf, int size);
//void selectFolder(char *path, char *folderName);
void moveFiles( const char *srcDir, const char *dstDir,
                const char *tag, const char *extention);
void copyFiles( const char *srcDir, const char *dstDir,
                const char *tag, const char *extention);
                
#ifdef __WIN32__
AnsiString FileTimeToStr(const FILETIME *lpFileTime);
bool getFileDate(char *fileName, FILETIME *pft);
bool setFileDate(char *fileName, FILETIME *pft);
bool getFileVersion (char *filename, VS_FIXEDFILEINFO *pvsf);
int  makeDirectory(const char *dir);
int  removeSubDirectorys(const char *dir, const char *startStr);
int  removeDirectory(const char *dir);
#endif                

	
//---------------------------------------------------------------------------
#endif


