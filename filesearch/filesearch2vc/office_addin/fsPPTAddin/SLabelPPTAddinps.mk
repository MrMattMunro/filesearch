
SLabelPPTAddinps.dll: dlldata.obj SLabelPPTAddin_p.obj SLabelPPTAddin_i.obj
	link /dll /out:SLabelPPTAddinps.dll /def:SLabelPPTAddinps.def /entry:DllMain dlldata.obj SLabelPPTAddin_p.obj SLabelPPTAddin_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SLabelPPTAddinps.dll
	@del SLabelPPTAddinps.lib
	@del SLabelPPTAddinps.exp
	@del dlldata.obj
	@del SLabelPPTAddin_p.obj
	@del SLabelPPTAddin_i.obj
