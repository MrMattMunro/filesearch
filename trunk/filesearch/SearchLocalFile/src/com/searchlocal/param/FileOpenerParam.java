/**
 * $RCSfile: FileOpenerParam.java
 * $Revision: 1.0
 * $Date: Jan 30, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.param;

/**
 * 打开文件Exe文件位置
 * 
 * <p>Title: 打开文件Exe文件位置</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class FileOpenerParam {

	/** Html打开软件路径 */
	private String iedir;

	/** Word打开软件路径 */
	private String worddir;

	/** Excel打开软件路径 */
	private String exceldir;

	/** Ppt打开软件路径 */
	private String pptdir;

	/**Pdf打开软件路径 */
	private String pdfdir;

	/**Txt打开软件路径 */
	private String txtdir;

	/**
	 * 取得iedir
	 * 
	 * @return String iedir 
	 */
	public String getIedir() {
		return iedir;
	}

	/**
	 * 设定iedir 
	 * 
	 * @param String iedir 
	 */
	public void setIedir(String iedir) {
		this.iedir = iedir;
	}

	/**
	 * 取得worddir
	 * 
	 * @return String worddir 
	 */
	public String getWorddir() {
		return worddir;
	}

	/**
	 * 设定worddir 
	 * 
	 * @param String worddir 
	 */
	public void setWorddir(String worddir) {
		this.worddir = worddir;
	}

	/**
	 * 取得exceldir
	 * 
	 * @return String exceldir 
	 */
	public String getExceldir() {
		return exceldir;
	}

	/**
	 * 设定exceldir 
	 * 
	 * @param String exceldir 
	 */
	public void setExceldir(String exceldir) {
		this.exceldir = exceldir;
	}

	/**
	 * 取得pptdir
	 * 
	 * @return String pptdir 
	 */
	public String getPptdir() {
		return pptdir;
	}

	/**
	 * 设定pptdir 
	 * 
	 * @param String pptdir 
	 */
	public void setPptdir(String pptdir) {
		this.pptdir = pptdir;
	}

	/**
	 * 取得pdfdir
	 * 
	 * @return String pdfdir 
	 */
	public String getPdfdir() {
		return pdfdir;
	}

	/**
	 * 设定pdfdir 
	 * 
	 * @param String pdfdir 
	 */
	public void setPdfdir(String pdfdir) {
		this.pdfdir = pdfdir;
	}

	/**
	 * 取得txtdir
	 * 
	 * @return String txtdir 
	 */
	public String getTxtdir() {
		return txtdir;
	}

	/**
	 * 设定txtdir 
	 * 
	 * @param String txtdir 
	 */
	public void setTxtdir(String txtdir) {
		this.txtdir = txtdir;
	}

}
