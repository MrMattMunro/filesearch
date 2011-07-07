/**
 * $RCSfile: WinMsgUtil.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.util;

import org.xvolks.jnative.JNative;
import org.xvolks.jnative.Type;
import org.xvolks.jnative.exceptions.NativeException;

public class WinMsgUtil {

	// 表示是否加载DLL
	private static boolean isloaded = false;
	static {
		if (!isloaded) {
			System.loadLibrary("FsUi");
			//System.loadLibrary("FileSearch");
			isloaded = true;
		}
	}

	public static String showCreateNew() {
		JNative p = null;
		String retnVal = "";
		int j = 0;
		try {
			System.out.println("start new JNative NotifyService");
			p = new JNative("FsUi.dll", "FsCreateIndex");
			p.setRetVal(Type.INT);
			System.out.println("JNative invoke start");
			p.invoke();
			System.out.println("JNative invoke end");
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
		return retnVal;
	}

	public static String notifyMsg() {
		JNative p = null;
		String retnVal = "";
		int j = 0;
		try {
			System.out.println("start new JNative NotifyService");
			p = new JNative("FileSearch.dll", "NotifyService");
			p.setRetVal(Type.PSTRUCT);
			System.out.println("JNative invoke start");
			p.invoke();
			System.out.println("JNative invoke end");
			retnVal = p.getRetVal();
		} catch (NativeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			if (p != null)
				try {
					p.dispose();
				} catch (NativeException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					// TODO Auto-generated catch block
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
		//notifyMsg();
		showCreateNew();
	}

}
