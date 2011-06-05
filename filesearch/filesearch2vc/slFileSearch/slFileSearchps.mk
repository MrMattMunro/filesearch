
slFileSearchps.dll: dlldata.obj slFileSearch_p.obj slFileSearch_i.obj
	link /dll /out:slFileSearchps.dll /def:slFileSearchps.def /entry:DllMain dlldata.obj slFileSearch_p.obj slFileSearch_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del slFileSearchps.dll
	@del slFileSearchps.lib
	@del slFileSearchps.exp
	@del dlldata.obj
	@del slFileSearch_p.obj
	@del slFileSearch_i.obj
