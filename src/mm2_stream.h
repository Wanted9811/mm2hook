#pragma once
#include "mm2_common.h"

namespace MM2
{
    class Stream {
    protected:
        static MM2FnHook<void> $DumpOpenFiles;

        static MM2FnHook<Stream*> $Open;
        static MM2FnHook<Stream*> $Create;

        static MM2FnHook<int> $Read;
        static MM2FnHook<int> $Write;
        static MM2FnHook<int> $GetCh;
        static MM2FnHook<int> $PutCh;
        static MM2FnHook<int> $Seek;
        static MM2FnHook<int> $Tell;
        static MM2FnHook<int> $Close;
        static MM2FnHook<int> $Size;
        static MM2FnHook<int> $Flush;
    public:
        AGE_API static void DumpOpenFiles(void) {
            $DumpOpenFiles();
        };

        AGE_API static Stream* Open(LPCSTR filename, bool isZipFile) {
            return $Open(filename, isZipFile);
        };

        AGE_API static Stream* Create(LPCSTR filename) {
            return $Create(filename);
        };

        AGE_API int Read(LPVOID dstBuf, int size) {
            return $Read(this, dstBuf, size);
        };

        AGE_API int Write(const LPVOID srcBuf, int size) {
            return $Write(this, srcBuf, size);
        };

        AGE_API int GetCh(void) {
            return $GetCh(this);
        };

        AGE_API int PutCh(unsigned char ch) {
            return $PutCh(this, ch);
        };

        AGE_API int Seek(int offset) {
            return $Seek(this, offset);
        };

        AGE_API int Tell(void) {
            return $Tell(this);
        };

        AGE_API int Close(void) {
            return $Close(this);
        };

        AGE_API int Size(void) {
            return $Size(this);
        };

        AGE_API int Flush(void) {
            return $Flush(this);
        };
    };
}