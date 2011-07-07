/**
 * $RCSfile: ExcelFileBean.java
 * $Revision: 1.0
 * $Date: Jan 19, 2011
 *
 * Copyright (C) 2010 SlFile, Inc. All rights reserved.
 *
 * This software is the proprietary information of SlFile, Inc.
 * Use is subject to license terms.
 */
package com.searchlocal.bean;

/**
 * excel文件
 * 
 * <p>Title: excel文件</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ExcelFileBean extends BaseFileBean {

	/** 标签名称 */
	private String sheetname;

	/** 行 */
	private int rownb;

	/**
	 * @return Returns the rownb.
	 */
	public int getRownb() {
		return rownb;
	}

	/**
	 * @param rownb
	 *            The rownb to set.
	 */
	public void setRownb(int rownb) {
		this.rownb = rownb;
	}

	/**
	 * @return Returns the sheetname.
	 */
	public String getSheetname() {
		return sheetname;
	}

	/**
	 * @param sheetname
	 *            The sheetname to set.
	 */
	public void setSheetname(String sheetname) {
		this.sheetname = sheetname;
	}

}
