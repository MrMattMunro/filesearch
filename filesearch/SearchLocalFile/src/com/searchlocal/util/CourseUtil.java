package com.searchlocal.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URLDecoder;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class CourseUtil {

	public CourseUtil() {
		super();
	}

	public static void restart(String installpath) {
//		try {
//			// 重启程序
//			List pids = getShutDownPids();
//			installpath = installpath.substring(1);
//			installpath = URLDecoder.decode(installpath, "UTF-8");
//			Runtime.getRuntime().exec(installpath);
//		    // 启动
//			shutdown(pids);
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
	}

	public static void shutdown() {
		List pids = getShutDownPids();
		shutdown(pids);
	}

	public static void shutdown(List pids) {
		try {
			Runtime.getRuntime().exec("tasklist");
			StringBuffer ids = new StringBuffer();
			for (Iterator iter = pids.iterator(); iter.hasNext();) {
				String pid = (String) iter.next();
				ids.append(" /PID ");
				ids.append(pid);
			}
			ids.append(" /F");
			// TASKKILL /PID 1230 /PID 1241 /PID 1253 /T
			Runtime.getRuntime().exec("TASKKILL " + ids.toString());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static List getShutDownPids() {
		List tokillPids = new ArrayList();
		try {
			Process p = Runtime.getRuntime().exec("tasklist");
			BufferedReader bw = new BufferedReader(new InputStreamReader(p
					.getInputStream()));
			String process = "";

			while ((process = bw.readLine()) != null) {
				if (process.indexOf(".exe") != -1
						&& process.indexOf("Console") != -1) {
					int startindex = process.indexOf(".exe") + 4;
					int endindex = process.indexOf("Console");
					if (process.indexOf("javaw") == -1 && process.indexOf("java") != -1) {
						tokillPids.add(process.substring(startindex, endindex).trim());
					}
					if (process.indexOf("slfile") != -1) {
						tokillPids.add(process.substring(startindex, endindex)
								.trim());
					}

					if (process.indexOf("mysql") != -1) {
						tokillPids.add(process.substring(startindex, endindex)
								.trim());
					}

					if (process.indexOf("cmd") != -1) {
						tokillPids.add(process.substring(startindex, endindex)
								.trim());
					}
					
					if (process.indexOf("update") != -1) {
						tokillPids.add(process.substring(startindex, endindex)
								.trim());
					}
				}
			}
			// TASKKILL /PID 1230 /PID 1241 /PID 1253 /T

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return tokillPids;
	}
}
