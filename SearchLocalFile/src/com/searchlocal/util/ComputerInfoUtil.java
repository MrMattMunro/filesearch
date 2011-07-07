package com.searchlocal.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.InputStreamReader;

public class ComputerInfoUtil {

	public ComputerInfoUtil() {
		super();
	}

	public static String getCurrentEncryPtString() {
		String sn = getSerialNumber("C");
		String date = "";
		date = TimeProtocol.traditionalClient();
		if (StringUtils.isNull(date)) {
			date = DateUtil.getNowDate();
		}
		return date + sn;
	}

	/**  
	 * 取得C盘的序列号和过期的日期
	 */
	public static String getEncryPtString() {
		String sn = getSerialNumber("C");
		String date = DateUtil.getNextDate();
		return date + sn;
	}

	private static String getSerialNumber(String drive) {
		String result = "";
		try {
			File file = File.createTempFile("realhowto", ".vbs");
			file.deleteOnExit();
			FileWriter fw = new java.io.FileWriter(file);

			String vbs = "Set objFSO = CreateObject(\"Scripting.FileSystemObject\")\n"
					+ "Set colDrives = objFSO.Drives\n" + "Set objDrive = colDrives.item(\""
					+ drive + "\")\n" + "Wscript.Echo objDrive.SerialNumber"; // see
																				// note
			fw.write(vbs);
			fw.close();
			Process p = Runtime.getRuntime().exec("cscript //NoLogo " + file.getPath());
			BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line;
			while ((line = input.readLine()) != null) {
				result += line;
			}
			input.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return result.trim();
	}

}
