package com.searchlocal.util;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.regex.Pattern;

import com.searchlocal.constants.Constant;

public class FileUtil {

	/** 
	 * 取得所有第二层目录的个数，以确定并发线程的数量
	 * 
	 * @param param 搜索参数
	 * @param filecon 文件容器
	 */
	public static int getSubFileNums(String folderPath) {
		// 第一层目录
		File file = new File(folderPath);
		File[] subFiles = file.listFiles();
		int sub1filelength = subFiles.length;

		// 第一层目录的子目录和文件总数
		int count = 1;
		if (null != subFiles) {
			for (int i = 0; i < sub1filelength; i++) {
				File[] subiFiles = subFiles[i].listFiles();
				if (null != subiFiles) {
					int subilength = subiFiles.length;
					count = count + subilength;
				}
			}
		}
		// 当第一层目录和文件总数超20时，定为20
		count = count > 20 ? 20 : count;
		return count;
	}

	public static void delFolder(String folderPath, boolean isdelroot) {
		try {
			delAllFile(folderPath);
			if (isdelroot) {
				java.io.File myFilePath = new java.io.File(folderPath);
				myFilePath.delete();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static boolean delAllFile(String path) {
		boolean flag = false;
		File file = new File(path);
		if (!file.exists()) {
			return flag;
		}
		if (!file.isDirectory()) {
			return flag;
		}
		String[] tempList = file.list();
		File temp = null;
		for (int i = 0; i < tempList.length; i++) {
			if (path.endsWith(File.separator)) {
				temp = new File(path + tempList[i]);
			} else {
				temp = new File(path + File.separator + tempList[i]);
			}
			if (temp.isFile()) {
				temp.delete();
			}
			if (temp.isDirectory()) {
				delAllFile(path + File.separator + tempList[i]);
				delFolder(path + File.separator + tempList[i], true);
				flag = true;
			}
		}
		return flag;
	}

	public static void copyFile(File in, File out) {
		try {
		
			if(!out.exists()){
				out.createNewFile();
			}
			FileInputStream fis = new FileInputStream(in);
			FileOutputStream fos = new FileOutputStream(out);
			
			byte[] buf = new byte[1024];
			int i = 0;
			while ((i = fis.read(buf)) != -1) {
				fos.write(buf, 0, i);
			}
			fis.close();
			fos.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**  
	 * 读取文本内容  
	 * @param textname 文本名称  
	 * @param textPath 文本路径
	 * @return  
	 */
	public static String deleteNullLine(String filepath) {
		File file = new File(filepath);
		try {
			BufferedReader br = new BufferedReader(new java.io.FileReader(file));
			StringBuffer sb = new StringBuffer();
			String line = br.readLine();
			while (line != null && !line.trim().equals("")) {
				sb.append(line);
				sb.append("\r\n");
				line = br.readLine();
			}
			br.close();
			
			File dicfile = new File(filepath);
			if(dicfile.exists()){
			   dicfile.delete();
			}
			FileUtil.appendText(filepath, sb.toString());
		} catch (IOException e) {
			e.printStackTrace();
		}
		return "";
	}
	
	/**  
	 * 读取文本内容  
	 * @param textname 文本名称  
	 * @param textPath 文本路径
	 * @return  
	 */
	public static String readText(String filepath) {
		File file = new File(filepath);
		try {
			BufferedReader br = new BufferedReader(new java.io.FileReader(file));
			StringBuffer sb = new StringBuffer();
			String line = br.readLine();
			sb.append("\r\n");
			while (line != null) {
				sb.append(line);
				sb.append("\r\n");
				line = br.readLine();
			}
			br.close();
			return sb.toString();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return "";
	}

	/**  
	 * 将内容写到文本中  
	 * @param textname　文本名称  
	 * @param date 写入的内容  
	 * @return  
	 */
	public static boolean writeText(String textname, String date, String textPath) {
		boolean flag = false;
		File filePath = new File(textPath);
		if (!filePath.exists()) {
			filePath.mkdirs();
		}
		try {
			FileWriter fw = new FileWriter(textPath + File.separator + textname);
			fw.write(date);
			flag = true;
			if (fw != null)
				fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		return flag;
	}

	/**  
	 * 在文档后附加内容  
	 * 
	 * @param textName  
	 * @param content  
	 * @param textPath  
	 * @return  
	 */
	public static boolean appendText(String filepath, String content) {
		boolean flag = false;
		try {
			FileWriter fw = new FileWriter(filepath, true);
			fw.append(content);
			flag = true;
			if (fw != null){
				fw.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return flag;
	}
	

	/**
	 * @return Returns the param.
	 */
	public static FileOutputStream getFileStreamOut(String datapath, int fileClassify) {
		File file = new File(Constant.datapath + datapath + fileClassify + Constant.suffixname);
		FileOutputStream out = null;
		try {
			if (!file.exists()) {
				file.createNewFile();
			}
			out = new FileOutputStream(file, true);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return out;
	}
	
	public static boolean is2007Doc(String path) {
		
		return true;
	}
	
	public static boolean showALlFile(String path) {
		boolean flag = false;
		File file = new File(path);
		if (!file.exists()) {
			return flag;
		}
		if (!file.isDirectory()) {
			return flag;
		}
		String[] tempList = file.list();
		File temp = null;
		for (int i = 0; i < tempList.length; i++) {
			if (path.endsWith(File.separator)) {
				temp = new File(path + tempList[i]);
			} else {
				temp = new File(path + File.separator + tempList[i]);
			}
			if (temp.isFile()) {
				String apath = temp.getAbsolutePath();
				int index = apath.indexOf("slfile");
				//System.out.println(temp.getAbsolutePath().substring(index).replaceAll("\\", "."));
				String s = Pattern.compile("\\\\").matcher(temp.getAbsolutePath().substring(index)).replaceAll(".");
				System.out.println(s + "=1.2.0");
			}
			if (temp.isDirectory()) {
				showALlFile(temp.getAbsolutePath());
			}
		}
		return flag;
	}
	
	public static void main(String[] args){
		
//		C:\Program Files\slfile\icos\1.ico
//		C:\Program Files\slfile\icos\2.ico
//		C:\Program Files\slfile\icos\3.ico
//		C:\Program Files\slfile\icos\4.ico
//		C:\Program Files\slfile\icos\search.ico
//		C:\Program Files\slfile\icos\titleico.jpg
//		C:\Program Files\slfile\jre-6u11-windows-i586-p.exe
//		C:\Program Files\slfile\licence.dat
//		C:\Program Files\slfile\slfile.exe
//		C:\Program Files\slfile\\unist.exe
		showALlFile("C:\\Program Files\\slfile\\tomcat\\webapps\\slfile");
		showALlFile("C:\\Program Files\\slfile\\dic");
		
	}

}