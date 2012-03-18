
SLabelExcelAddinps.dll: dlldata.obj SLabelExcelAddin_p.obj SLabelExcelAddin_i.obj
	link /dll /out:SLabelExcelAddinps.dll /def:SLabelExcelAddinps.def /entry:DllMain dlldata.obj SLabelExcelAddin_p.obj SLabelExcelAddin_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SLabelExcelAddinps.dll
	@del SLabelExcelAddinps.lib
	@del SLabelExcelAddinps.exp
	@del dlldata.obj
	@del SLabelExcelAddin_p.obj
	@del SLabelExcelAddin_i.obj
