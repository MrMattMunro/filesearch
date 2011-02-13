/**
 * $RCSfile: MakeShortCut.java
 * $Revision: 1.0
 * $Date: Jun 28, 2010
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.util;

import java.io.*;

import com.searchlocal.constants.Constant;

/**
 * 设置快键方式
 * 
 * <p>Title: 生成快捷方式</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class MakeShortCut {

	/** 系统名称 */
	public static String osName = System.getProperty("os.name");

	/** 消息体 */
	private static MenuMessageUtil msg = new MenuMessageUtil();

	private static String slfilejs = "slfile.js";

	private static String updatejs = "update.js";

	public static void create() {
		
		MakeShortCut sc = new MakeShortCut();
		File installDir = new File(Constant.datapath);
		// slFile快捷方式
		String shorcutname = msg.getMsgbyId(Constant.searchapp_localsearch);
		sc.createSlfileShortcut(installDir, "slfile.exe", shorcutname);
		File file = new File(installDir + File.separator + slfilejs);
		if (file.exists()) {
			file.delete();
		}
		// 生成自动更新
		sc.createUpdateShortcut(installDir, "update.exe", "update");
		file = new File(installDir + File.separator + updatejs);
		if (file.exists()) {
			file.delete();
		}
	}

	/**
	 * 本地搜索快捷方式
	 * 
	 * @param installDir 文件路径
	 * @param runnable 可执行性文件(***.exe)
	 * @param folder 文件夹名称(本级文件夹名称)
	 * @param name 快捷方式名称
	 * @return
	 */
	public boolean createSlfileShortcut(File installDir, String runnable, String name) {
		String command = null;
		if (osName.indexOf("9") != -1)
			command = "command.com   /c   cscript.exe   /nologo   ";
		else
			command = "cmd.exe   /c   cscript.exe   /nologo   ";
		if (command != null)
			try {
				File shortcutMaker = new File(installDir, slfilejs);
				PrintStream out = new PrintStream(new FileOutputStream(shortcutMaker));
				out.println("WScript.Echo(\"Creating   shortcuts...\");");
				out.println("Shell   =   new   ActiveXObject(\"WScript.Shell\");");
				out.println("ProgramsPath   =   Shell.SpecialFolders(\"AllUsersStartMenu\");");
				/** 创建菜单快捷方式 */
				out.println("fso   =   new   ActiveXObject(\"Scripting.FileSystemObject\");");
				out.println("link   =   Shell.CreateShortcut(ProgramsPath   +   \"\\\\" + name
						+ ".lnk\");");
				out.println("link.Arguments   =   \"\";");
				out.println("link.Description   =   \"" + name + "\";");
				out.println("link.HotKey   =   \"\";");
				out.println("link.IconLocation   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + "icos\\\\search.ico,0\";");
				out.println("link.TargetPath   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + runnable + "\";");
				out.println("link.WindowStyle   =   1;");
				out.println("link.WorkingDirectory   =   \""
						+ escaped(installDir.getAbsolutePath()) + "\";");
				out.println("link.Save();");
				/** 创建桌面快捷方式 */
				out.println("DesktopPath   =   Shell.SpecialFolders(\"AllUsersDesktop\");");
				out.println("link   =   Shell.CreateShortcut(DesktopPath   +   \"\\\\" + name
						+ ".lnk\");");
				out.println("link.Arguments   =   \"\";");
				out.println("link.Description   =   \"" + name + "\";");
				out.println("link.HotKey   =   \"\";");
				out.println("link.IconLocation   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + "icos\\\\search.ico,0\";");
				out.println("link.TargetPath   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + runnable + "\";");
				out.println("link.WindowStyle   =   1;");
				out.println("link.WorkingDirectory   =   \""
						+ escaped(installDir.getAbsolutePath()) + "\";");
				out.println("link.Save();");
				out.println("WScript.Echo(\"Shortcuts   created.\");");
				/** ********* */
				/** 所有用户自动启动 */
				out.println("DesktopPath   =   Shell.SpecialFolders(\"AllUsersStartup\");");
				out.println("link   =   Shell.CreateShortcut(DesktopPath   +   \"\\\\" + name
						+ ".lnk\");");
				out.println("link.Arguments   =   \"\";");
				out.println("link.Description   =   \"" + name + "\";");
				out.println("link.HotKey   =   \"\";");
				out.println("link.IconLocation   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + "icos\\\\search.ico,0\";");
				out.println("link.TargetPath   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + runnable + "\";");
				out.println("link.WindowStyle   =   1;");
				out.println("link.WorkingDirectory   =   \""
						+ escaped(installDir.getAbsolutePath()) + "\";");
				out.println("link.Save();");
				out.println("WScript.Echo(\"Shortcuts   created.\");");
				/** ********* */
				out.close();
				Process p = Runtime.getRuntime().exec(command + "  " + slfilejs, null, installDir);
				p.waitFor();
				int rv = p.exitValue();
				if (rv == 0) {
					return true;
				} else {
					return false;
				}
			} catch (Exception e) {
				return false;
			}
		else
			return false;
	}

	/**
	 * 本地搜索自动更新快捷方式
	 * 
	 * @param installDir 文件路径
	 * @param runnable 可执行性文件(***.exe)
	 * @param folder 文件夹名称(本级文件夹名称)
	 * @param name 快捷方式名称
	 * @return
	 */
	public boolean createUpdateShortcut(File installDir, String runnable, String name) {
		String command = null;
		if (osName.indexOf("9") != -1)
			command = "command.com   /c   cscript.exe   /nologo   ";
		else
			command = "cmd.exe   /c   cscript.exe   /nologo   ";
		if (command != null)
			try {
				File shortcutMaker = new File(installDir, updatejs);
				PrintStream out = new PrintStream(new FileOutputStream(shortcutMaker));
				out.println("WScript.Echo(\"Creating   shortcuts...\");");
				out.println("Shell   =   new   ActiveXObject(\"WScript.Shell\");");
				out.println("ProgramsPath   =   Shell.SpecialFolders(\"AllUsersStartMenu\");");
				/** 创建菜单快捷方式 */
				out.println("fso   =   new   ActiveXObject(\"Scripting.FileSystemObject\");");
				out.println("link   =   Shell.CreateShortcut(ProgramsPath   +   \"\\\\" + name
						+ ".lnk\");");
				out.println("link.Arguments   =   \"\";");
				out.println("link.Description   =   \"" + name + "\";");
				out.println("link.HotKey   =   \"\";");
				out.println("link.IconLocation   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + "icos\\\\update.ico,0\";");
				out.println("link.TargetPath   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + runnable + "\";");
				out.println("link.WindowStyle   =   1;");
				out.println("link.WorkingDirectory   =   \""
						+ escaped(installDir.getAbsolutePath()) + "\";");
				out.println("link.Save();");
				/** ********* */
				/** 所有用户自动启动 */
				out.println("DesktopPath   =   Shell.SpecialFolders(\"AllUsersStartup\");");
				out.println("link   =   Shell.CreateShortcut(DesktopPath   +   \"\\\\" + name
						+ ".lnk\");");
				out.println("link.Arguments   =   \"\";");
				out.println("link.Description   =   \"" + name + "\";");
				out.println("link.HotKey   =   \"\";");
				out.println("link.IconLocation   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + "icos\\\\update.ico,0\";");
				out.println("link.TargetPath   =   \"" + escaped(installDir.getAbsolutePath())
						+ "\\\\" + runnable + "\";");
				out.println("link.WindowStyle   =   1;");
				out.println("link.WorkingDirectory   =   \""
						+ escaped(installDir.getAbsolutePath()) + "\";");
				out.println("link.Save();");
				out.println("WScript.Echo(\"Shortcuts   created.\");");
				/** ********* */
				out.close();
				Process p = Runtime.getRuntime().exec(command + "  " + updatejs, null, installDir);
				p.waitFor();
				int rv = p.exitValue();
				if (rv == 0) {
					return true;
				} else {
					return false;
				}
			} catch (Exception e) {
				return false;
			}
		else
			return false;
	}

	public String escaped(String s) {
		String r = "";
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) == '\\')
				r = r + '\\';
			r = r + s.charAt(i);
		}
		return r;
	}
}
