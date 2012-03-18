
SLabelWordAddinps.dll: dlldata.obj SLabelWordAddin_p.obj SLabelWordAddin_i.obj
	link /dll /out:SLabelWordAddinps.dll /def:SLabelWordAddinps.def /entry:DllMain dlldata.obj SLabelWordAddin_p.obj SLabelWordAddin_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SLabelWordAddinps.dll
	@del SLabelWordAddinps.lib
	@del SLabelWordAddinps.exp
	@del dlldata.obj
	@del SLabelWordAddin_p.obj
	@del SLabelWordAddin_i.obj
