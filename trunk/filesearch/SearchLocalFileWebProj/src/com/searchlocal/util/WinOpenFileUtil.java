/**
 * $RCSfile: WinOpenFileUtil.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.web.searchlocal.util;

import org.xvolks.jnative.JNative;
import org.xvolks.jnative.Type;
import org.xvolks.jnative.exceptions.NativeException;

/**
 * 调用打开文件接口
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class WinOpenFileUtil {

	// 表示是否加载DLL
	private static boolean isloaded = false;
	static {
		if (!isloaded) {
			System.loadLibrary("OpenfileAddin");
			isloaded = true;
		}
	}

	/** 
	 * 打开Word文件
	 */
	public static String openWordFile(String filepath, String page, String keyWord) {
		JNative p = null;
		String retnVal = "";
		try {
			p = new JNative("OpenfileAddin.dll", "openWordFile");
			int i = 0;
			p.setRetVal(Type.INT);
			p.setParameter(i++, Type.STRING, filepath);
			p.setParameter(i++, Type.INT, page);
			p.setParameter(i++, Type.STRING, keyWord);
			p.invoke();
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
		}
		return retnVal;
	}
	
	/** 
	 * 打开Excel文件
	 * 
	 * @param filepath 文件路径
	 * @param sheetName Sheet名称
	 * @param row 行
	 * @param keyWord 关键字
	 */
	public static String openExcelFile(String filepath, String sheetName, String row, String keyWord) {
		JNative p = null;
		String retnVal = "";
		try {
			p = new JNative("OpenfileAddin.dll", "openExcelFile");
			int i = 0;
			p.setRetVal(Type.INT);
			p.setParameter(i++, Type.STRING, filepath);
			p.setParameter(i++, Type.STRING, sheetName);
			p.setParameter(i++, Type.INT, row);
			p.setParameter(i++, Type.STRING, keyWord);
			p.invoke();
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
		}
		return retnVal;
	}

	/** 
	 * 打开Ppt文件
	 * 
	 * @param filepath 文件路径
	 * @param page 页
	 * @param keyWord 关键字
	 */
	public static String openPPTFile(String filepath, String page, String keyWord) {
		JNative p = null;
		String retnVal = "";
		try {
			p = new JNative("OpenfileAddin.dll", "openPPTFile");
			int i = 0;
			p.setRetVal(Type.INT);
			p.setParameter(i++, Type.STRING, filepath);
			p.setParameter(i++, Type.INT, page);
			p.setParameter(i++, Type.STRING, keyWord);
			p.invoke();
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
		}
		return retnVal;
	}
	
	/** 
	 * 打开Txt文件
	 * 
	 * @param filepath 文件路径
	 * @param row 行
	 * @param keyWord 关键字
	 */
	public static String openTxtFile(String filepath, String row, String keyWord) {
		JNative p = null;
		String retnVal = "";
		try {
			p = new JNative("OpenfileAddin.dll", "openTxtFile");
			int i = 0;
			p.setRetVal(Type.INT);
			p.setParameter(i++, Type.STRING, filepath);
			p.setParameter(i++, Type.INT, row);
			p.setParameter(i++, Type.STRING, keyWord);
			p.invoke();
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
		}
		return retnVal;
	}
	
	/** 
	 * 打开Pdf文件
	 * 
	 * @param pdfpath Pdf路径
	 * @param filepath 文件路径
	 * @param page 页
	 * @param keyWord 关键字
	 */
	public static String openPdfFile(String pdfpath, String filepath, String page, String keyWord) {
		JNative p = null;
		String retnVal = "";
		try {
			p = new JNative("OpenfileAddin.dll", "openPdfFile");
			int i = 0;
			p.setRetVal(Type.INT);
			p.setParameter(i++, Type.STRING, pdfpath);
			p.setParameter(i++, Type.STRING, filepath);
			p.setParameter(i++, Type.INT, page);
			p.setParameter(i++, Type.STRING, keyWord);
			p.invoke();
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
		}
		return retnVal;
	}



	// // /*
	// // * 返回值: -1.非密级文件 0.公开 2.内部文件 3.秘密 4.机密 5.绝密
	// // */
	// // DOCSLDLL_API
	// // int WINAPI GetSLType( //获取文件秘密级别
	// // __in char* lpFileName //文件路径
	// // );
	// public static int getSLType(String lpFileName) {
	// JNative n = null;
	// int retnVal = 0;
	// try {
	// System.out.println("start new JNative GetSLType");
	// n = new JNative("DocSLDLL.dll", "GetSLType");
	// int i = 0;
	// n.setRetVal(Type.INT);
	// n.setParameter(i++, Type.STRING, lpFileName);
	// System.out.println("JNative invoke start");
	// n.invoke();
	// System.out.println("JNative invoke end");
	// retnVal = Integer.parseInt(n.getRetVal());
	// } catch (NativeException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// } catch (IllegalAccessException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// } finally {
	// if (n != null)
	// try {
	// n.dispose();
	// } catch (NativeException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// } catch (IllegalAccessException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// }
	// return retnVal;
	// }

	public static void main(String[] args) {
		openWordFile("E:\\testdocfile\\文档搜索系统联调说明.doc","2","说明");
	}

}
