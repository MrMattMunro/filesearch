package com.searchlocal.util;

import java.io.IOException;
import java.io.InputStream;
import java.io.StringWriter;

/**
 * 取系统注册表信息工具（可以用来完成取得软件安装目录等功能）
 */
public class RegistTableUtil {

	// 查询注册表命令
	private static final String REGQUERY_UTIL = "reg query ";
	private static final String REGSTR_TOKEN = "REG_SZ";
	private static final String ADOBE_REGSTR_TOKEN = "REG";

	// 根据Office优先级来检索
	private final static String[] OFFICE_VERSION = { "12.0", "11.0", "10.0", "9.0", "8.0" };

	private static String EXCEL_PATH_CMD = REGQUERY_UTIL
			+ "\"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Office\\";

	// 根据ADOBE优先级来检索
	private final static String[] ADOBE_VERSION = { "9.0", "8.0", "7.0" };
	private static final String ADOBE_PATH_CMD = REGQUERY_UTIL
			+ "\"HKEY_LOCAL_MACHINE\\SOFTWARE\\Adobe\\Acrobat Reader\\";
	
	//  根据JDK优先级来检索*/
	private final static String[] JDK_VERSION = { "1.6.0_11", "1.6", "1.7", "1.5" };

	private static String JAVA_PATH_CMD = REGQUERY_UTIL
			+ "\"HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment\\";

	/**
	 * 测试
	 */
	public static void main(String[] args) {
		System.out.println(getJavaInstallRoot());
		System.out.println(getExcelInstallRoot());
		System.out.println(getAdobeInstallRoot());
		System.out.println(getSys32Root());
	}
	
	/**
	 * 取得System32目录
	 */
	public static String getSys32Root() {
		String javaInstallPath = getJavaInstallRoot();
		return javaInstallPath.substring(0,1) + ":\\Windows\\System32";
	}
	
	/**
	 * 取得java的安装目录
	 */
	public static String getJavaInstallRoot() {
		String javaInstallRoot = null;
		for (int i = 0; i < JDK_VERSION.length; i++) {
			String jdkVersion = JDK_VERSION[i];
			try {
				Process process = Runtime.getRuntime().exec(JAVA_PATH_CMD + jdkVersion + "\"");
				StreamReader reader = new StreamReader(process.getInputStream());
				reader.start();
				process.waitFor();
				reader.join();
				String result = reader.getResult();
				int p = result.indexOf("REG_SZ");
				if (p == -1) {
					continue;
				}
				int end = result.indexOf("MicroVersion");
				if (end == -1) {
					continue;
				}
				javaInstallRoot = result.substring(p + 6, end).trim();
				break;
			} catch (Exception e) {
				return null;
			}

		}
		return javaInstallRoot;
	}

	/**
	 * 取得Adobe安装目录
	 */
	public static String getAdobeInstallRoot() {
		String adobeInstallRoot = null;
		for (int i = 0; i < ADOBE_VERSION.length; i++) {
			try {
				Process process = Runtime.getRuntime().exec(
						ADOBE_PATH_CMD + ADOBE_VERSION[i] + "\\InstallPath" + "\"");
				StreamReader reader = new StreamReader(process.getInputStream());

				reader.start();
				process.waitFor();
				reader.join();
				String result = reader.getResult();
				result = result.replaceAll("_SZ", "");
				int p = result.lastIndexOf(ADOBE_REGSTR_TOKEN);
				if (p == -1) {
					continue;
				}
				adobeInstallRoot = result.substring(p + ADOBE_REGSTR_TOKEN.length()).trim();
				break;
			} catch (Exception e) {
				return null;
			}
		}
		return adobeInstallRoot;
	}
	
	/**
	 * 取得Office安装目录
	 */
	public static String getExcelInstallRoot() {
		String officeInstallRoot = null;
		for (int i = 0; i < OFFICE_VERSION.length; i++) {
			try {
				Process process = Runtime.getRuntime().exec(
						EXCEL_PATH_CMD + OFFICE_VERSION[i] + "\\Excel\\InstallRoot" + "\"");
				StreamReader reader = new StreamReader(process.getInputStream());

				reader.start();
				process.waitFor();
				reader.join();
				String result = reader.getResult();
				int p = result.indexOf(REGSTR_TOKEN);
				if (p == -1) {
					continue;
				}
				officeInstallRoot = result.substring(p + REGSTR_TOKEN.length()).trim();
				break;
			} catch (Exception e) {
				return null;
			}
		}
		return officeInstallRoot;
	}

	static class StreamReader extends Thread {
		private InputStream is;

		private StringWriter sw;

		StreamReader(InputStream is) {
			this.is = is;
			sw = new StringWriter();
		}
		public void run() {
			try {
				int c;
				while ((c = is.read()) != -1)
					sw.write(c);
			} catch (IOException e) {
				;
			}
		}

		String getResult() {
			return sw.toString();
		}
	}

}
