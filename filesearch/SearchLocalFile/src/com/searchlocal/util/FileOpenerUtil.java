/**
 * $RCSfile: FileOpenerUtil.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import com.searchlocal.bean.FileOpenerBean;
import com.searchlocal.constants.Constant;
import com.searchlocal.param.FileOpenerParam;

/**
 * 打开文件工具的位置
 * 
 * <p>Title: html文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileOpenerUtil {
	
	/** 打开文件软件列表 */
	public static Properties prop = new Properties();

	/**
	 * @param args
	 */
	public FileOpenerUtil(FileOpenerParam openerparam) {
		try {
			if (null != openerparam) {
				prop.put("word", openerparam.getWorddir());
				prop.put("excel", openerparam.getExceldir());
				prop.put("ppt", openerparam.getPptdir());
				prop.put("pdf", openerparam.getPdfdir());
				prop.put("txt", openerparam.getTxtdir());
				prop.put("ie", openerparam.getIedir());
				OutputStream out = new FileOutputStream(Constant.path
						+ "com\\searchlocal\\properties\\fileopener.properties");
				prop.store(out, "fileopener");
				out.close();
			} else {
				FileInputStream in = new FileInputStream(Constant.path
						+ "com\\searchlocal\\properties\\fileopener.properties");
				prop.load(in);
			}

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static String getOpenerbyId(String openerId) {
		String opener = "";
		Object temp = prop.get(openerId);
		if (temp != null) {
			opener = (String) temp;
		}
		return opener;
	}
	
	/**
	 * 取得打开文件的软件列表
	 * 
	 * @return List 打开文件的软件列表
	 */
	public static List<FileOpenerBean> getFileOpenerList() {
		List<FileOpenerBean> returnList = new ArrayList<FileOpenerBean>();
		
		String[] driver = new String[] { "C", "D", "E", "F"};
		String iepath = ":\\Program Files\\Internet Explorer\\IEXPLORE.EXE";
		String officepath = RegistTableUtil.getExcelInstallRoot();
		String pdfpath = RegistTableUtil.getAdobeInstallRoot();
		String txtpath = ":\\WINDOWS\\system32\\notepad.exe";
		String chmpath = ":\\WINDOWS\\hh.exe";

		String excelexe = "EXCEL.EXE";
		String wordexe = "WINWORD.EXE";
		String pptexe = "POWERPNT.EXE";
		String pdfexe = "AcroRd32.exe";

		// word path
		String wordfilepath = officepath + wordexe;
		FileOpenerBean wordBean = new FileOpenerBean();
		wordBean.setFileType(Constant.FileNameClassify.WORD);
		wordBean.setExePath(wordfilepath);
		
		// excel path
		String excelfilepath = officepath + excelexe;
		FileOpenerBean excelBean = new FileOpenerBean();
		excelBean.setFileType(Constant.FileNameClassify.EXCEL);
		excelBean.setExePath(excelfilepath);

		// ppt path
		String pptfilepath = officepath + pptexe;
		FileOpenerBean pptBean = new FileOpenerBean();
		pptBean.setFileType(Constant.FileNameClassify.PPT);
		pptBean.setExePath(pptfilepath);

		// pdf path
		String pdffilepath = pdfpath + File.separator + pdfexe;
		FileOpenerBean pdfBean = new FileOpenerBean();
		pdfBean.setFileType(Constant.FileNameClassify.PDF);
		pdfBean.setExePath(pdffilepath);

		for (int i = 0; i < driver.length; i++) {
			try {
				// ie path
				String iefilepath = driver[i] + iepath;
				File tempFile = new File(iefilepath);
				if(tempFile.exists()){
					FileOpenerBean ieBean = new FileOpenerBean();
					ieBean.setFileType(Constant.FileNameClassify.HTML);
					ieBean.setExePath(iefilepath);
					returnList.add(ieBean);
				}
				// txt path
				String txtfilepath = driver[i] + txtpath;
				tempFile = new File(txtfilepath);
				if(tempFile.exists()){
					FileOpenerBean txtBean = new FileOpenerBean();
					txtBean.setFileType(Constant.FileNameClassify.TXT);
					txtBean.setExePath(iefilepath);
					returnList.add(txtBean);
				}
				
				// chm path
				String chmfilepath = driver[i] + chmpath;
				File chnfile = new File(chmfilepath);
				if (chnfile.exists()) {
					FileOpenerBean chmBean = new FileOpenerBean();
					chmBean.setFileType(Constant.FileNameClassify.CHM);
					chmBean.setExePath(chmfilepath);
					returnList.add(chmBean);
				}
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
		
		// 向列表加入打开文件列表
		returnList.add(wordBean);
		returnList.add(excelBean);
		returnList.add(pptBean);
		returnList.add(pdfBean);

		return returnList;
	}
}
