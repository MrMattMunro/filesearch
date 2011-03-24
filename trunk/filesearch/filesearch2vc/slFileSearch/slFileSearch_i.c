/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 24 19:58:47 2011
 */
/* Compiler settings for F:\rw\slsearch\workdir\filesearch\filesearch2vc\slFileSearch\slFileSearch.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_SLFILESEARCHLib = {0x5E4FE5A2,0x476F,0x4DAF,{0x8B,0x42,0xCA,0x95,0x90,0xD6,0x28,0x44}};


#ifdef __cplusplus
}
#endif

