package com.searchlocal.util;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.Socket;

public class TimeProtocol {

	private static String ip = "www.google.com";

	public TimeProtocol() {
	}

	public static String traditionalClient() {

		boolean isnetwork = false;
		String date = "";
		BufferedReader in = null;
		try {
			Process p = Runtime.getRuntime().exec("cmd /c ping -n 1 " + ip); // 此处1变大可以增加精确度，但影响测试速度
			in = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String temp = null;
			StringBuffer strBuffer = new StringBuffer();
			while ((temp = (in.readLine())) != null) {
				strBuffer.append(temp);
			}

			if (strBuffer.toString().matches(".*\\(\\d?\\d% loss\\).*")) {
				isnetwork = true;
			}
			if (isnetwork) {
				date = getInternetDate();
			}
		} catch (IOException e) {
			// TODO 注意消除资源(关闭I/O等)
			e.printStackTrace();
		} finally {
			if (in != null) {
				try {
					in.close();
				} catch (IOException e) {
					// TODO 注意消除资源(关闭I/O等)
					e.printStackTrace();
				}
			}
		}
		return date;
	}

	public static String getInternetDate() {
		try {
			Socket s = new Socket();
			InetSocketAddress sa = new InetSocketAddress("time-a.nist.gov", 13);
			s.connect(sa);
			ByteArrayOutputStream ba = new ByteArrayOutputStream();
			byte buf[] = new byte[256];
			InputStream is = s.getInputStream();
			int nread = 1;
			while (nread > 0) {
				nread = is.read(buf);
				if (nread > 0)
					ba.write(buf, 0, nread);
			}
			is.close();
			s.close();
			String data = new String(ba.toByteArray());
			data = data.substring(7, 15);
			data = data.replaceAll("-", "");
			return "20" + data;
		} catch (Exception e) {
			return "";
		}
	}

	public static void main(String[] args) {
		traditionalClient();
	}
}